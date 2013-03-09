/************************************************************************************

	AstroMenace (Hardcore 3D space shooter with spaceship upgrade possibilities)
	Copyright © 2006-2013 Michael Kurinnoy, Viewizard


	AstroMenace is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	AstroMenace is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with AstroMenace. If not, see <http://www.gnu.org/licenses/>.


	Web Site: http://www.viewizard.com/
	Project: http://sourceforge.net/projects/openastromenace/
	E-mail: viewizard@viewizard.com

*************************************************************************************/


#include "SpaceStars.h"
#include "../../Game.h"




//-----------------------------------------------------------------------------
// инициализация класса
//-----------------------------------------------------------------------------
CSpaceStars::CSpaceStars()
{
	Age = 0.0f;
	TimeLastUpdate = -1.0f;

	// положение системы
	Location = VECTOR3D( 0.0f, 0.0f, 0.0f);

	Size = 0.003f;
	CreationSize = VECTOR3D(5.21f,5.21f,5.21f);
	Texture = vw_FindTextureByName("DATA/GFX/flare1.tga");
	DeadZone = 5.2f;



	if (Setup.UseGLSL)
	{
		GLSL = vw_FindShaderByName("SpaceStars");
		UniformLocations[0] = vw_GetUniformLocation(GLSL, "ParticleTexture");
		UniformLocations[1] = vw_GetUniformLocation(GLSL, "ParticleAge");
	}



	// начальные установки для мартиц поворотов
	Matrix33Identity(CurrentRotationMat);
	Matrix33Identity(OldInvRotationMat);

	// настройка массива
	Start = 0;
	End = 0;


	unsigned int ParticlesCreated = 10000 - 4000*Setup.VisualEffectsQuality;

	// пока не создадим все необходимые частицы
	while (ParticlesCreated > 0)
	{
		// создаем новую частицу
		CStar *NewParticle = 0;
		NewParticle = new CStar; if (NewParticle == 0) return;


		// считаем значение альфы
		NewParticle->Alpha = 0.5f + 0.5f * vw_Randf1;
		// убираем переполнение
		Clamp( NewParticle->Alpha, 0.0f, 1.0f );
		// считаем дельту альфы
		NewParticle->AlphaDelta = (1.5f + 1.5f * vw_Randf1) / 3.0f;



		// выпускаем частицу возле места нахождения системы
		// в сфере
		VECTOR3D tmp;
		float minDist = CreationSize.x*CreationSize.x+CreationSize.y*CreationSize.y+CreationSize.z*CreationSize.z;
		// если зона больше чем радиус излучения - выключаем ее
		if (minDist <= DeadZone*DeadZone) DeadZone = 0.0f;

		// прибавляем к рандому, чтобы избежать вероятности появления всех трех нулей и деления на ноль в дальнейшем
		tmp.x = (vw_Randf0 + 0.00001f) * CreationSize.x;
		tmp.y = vw_Randf0 * CreationSize.y;
		tmp.z = vw_Randf0 * CreationSize.z;
		float ParticleDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
		while (ParticleDist > minDist || ParticleDist < DeadZone*DeadZone)
		{
			if (ParticleDist > minDist)
			{
				// ум. радиус
				VECTOR3D tmp1 = tmp;
				tmp1.Normalize();
				tmp1 = tmp1^(1/100.0f);
				tmp = tmp - tmp1;
			}
			if ( ParticleDist < DeadZone*DeadZone)
			{
				// ув. радиус
				VECTOR3D tmp1 = tmp;
				tmp1.Normalize();
				tmp1 = tmp1^(1/100.0f);
				tmp = tmp + tmp1;

				if (tmp.x > 0.0f)
				{if (tmp.x > CreationSize.x) tmp.x = CreationSize.x;}
				else
				{if (tmp.x < -CreationSize.x) tmp.x = -CreationSize.x;}
				if (tmp.y > 0.0f)
				{if (tmp.y > CreationSize.y) tmp.y = CreationSize.y;}
				else
				{if (tmp.y < -CreationSize.y) tmp.y = -CreationSize.y;}

				if (tmp.z > 0.0f)
				{if (tmp.z > CreationSize.z) tmp.z = CreationSize.z;}
				else
				{if (tmp.z < -CreationSize.z) tmp.z = -CreationSize.z;}
			}
			ParticleDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
		}

		Matrix33CalcPoint(&tmp, CurrentRotationMat);
		NewParticle->Location = Location + tmp;



		// подключаем частицу к системе
		Attach(NewParticle);

		// уменьшаем необходимое количество частиц
		ParticlesCreated--;
	}




	list = 0;
	tmpDATA = 0;
	VBO = 0;
	LastCameraAngleX = LastCameraAngleY = LastCameraAngleZ = 0.0f;
}


//-----------------------------------------------------------------------------
//	При разрушении класса
//-----------------------------------------------------------------------------
CSpaceStars::~CSpaceStars()
{
	// полностью освобождаем память от всех частиц в системе
	CStar *tmp = Start;
	while (tmp!=0)
	{
		CStar *tmp2 = tmp->Next;
		Detach(tmp);
		delete tmp; tmp = 0;
		tmp = tmp2;
	}

	if (VBO!=0){vw_DeleteVBO(*VBO); delete VBO; VBO=0;}
	if (tmpDATA!=0){delete [] tmpDATA; tmpDATA = 0;}
	if (list!=0){delete [] list; list = 0;}
}


//-----------------------------------------------------------------------------
//	подключить частицу к системе
//-----------------------------------------------------------------------------
void CSpaceStars::Attach(CStar * NewParticle)
{
	if (NewParticle == 0) return;

	// первый в списке...
	if (End == 0)
	{
		NewParticle->Prev = 0;
		NewParticle->Next = 0;
		Start = NewParticle;
		End = NewParticle;
	}
	else // продолжаем заполнение...
	{
		NewParticle->Prev = End;
		NewParticle->Next = 0;
		End->Next = NewParticle;
		End = NewParticle;
	}

}


//-----------------------------------------------------------------------------
//	отключить ее от системы
//-----------------------------------------------------------------------------
void CSpaceStars::Detach(CStar * OldParticle)
{
	if (OldParticle == 0) return;

	// переустанавливаем указатели...
	if (Start == OldParticle) Start = OldParticle->Next;
	if (End == OldParticle) End = OldParticle->Prev;


	if (OldParticle->Next != 0) OldParticle->Next->Prev = OldParticle->Prev;
		else if (OldParticle->Prev != 0) OldParticle->Prev->Next = 0;
	if (OldParticle->Prev != 0) OldParticle->Prev->Next = OldParticle->Next;
		else if (OldParticle->Next != 0) OldParticle->Next->Prev = 0;

}





//-----------------------------------------------------------------------------
// обновление системы
//-----------------------------------------------------------------------------
bool CSpaceStars::Update(float Time)
{
	// первый раз... просто берем время
	if (TimeLastUpdate == -1.0f) {TimeLastUpdate = Time;return true;}

	// Time - это абсолютное время, вычисляем дельту
	float TimeDelta = Time - TimeLastUpdate;
	// быстро вызвали еще раз... время не изменилось, или почти не изменилось
	if (TimeDelta == 0.0f) return true;

	TimeLastUpdate = Time;
	Age += TimeDelta;


	// эти расчеты делаем в шейдере, они нам не нужны
	if (!Setup.UseGLSL)
	{
		// для всех частиц
		CStar *tmp = Start;
		while (tmp!=0)
		{
			CStar *tmp2 = tmp->Next;
			// функция вернет false, если частица уже мертва
			if (!tmp->Update(TimeDelta))
			{
				Detach(tmp);
				delete tmp; tmp = 0;
			}
			tmp = tmp2;
		}

		// обновляем данные в массиве прорисовки
		if (tmpDATA != 0 && list != 0)
		{
			// для каждого меняем альфу
			int k=0;
			GLubyte A;
			GLubyte *tmpDATAub = (GLubyte *)tmpDATA;

			for (int i=0; i<PrimitCount; i++)
			{
				A = (GLubyte)(list[i]->Alpha*255);

#ifdef USE_GLES
				k+=3;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=6;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=6;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=6;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=6;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=6;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=3;
#else
				k+=3;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=6;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=6;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=6;
				tmpDATAub[k*sizeof(float)+3] = A;
				k+=3;
#endif
			}
		}
	}

    return true;
}





//-----------------------------------------------------------------------------
// прорисовка системы
//-----------------------------------------------------------------------------
void CSpaceStars::Draw()
{
	// загрузка текстуры, уже должна быть подключена
	if (Texture == 0) return;

	VECTOR3D CurrentCameraRotation;
	vw_GetCameraRotation(&CurrentCameraRotation);


	// если еще нет последовательности, или камеру повернули - надо пересчитать прорисовку
	if ((tmpDATA == 0 && VBO == 0) || CurrentCameraRotation.x != LastCameraAngleX || CurrentCameraRotation.y != LastCameraAngleY || CurrentCameraRotation.z != LastCameraAngleZ)
	{

		if (list != 0){delete [] list; list = 0;}
		if (tmpDATA != 0){delete [] tmpDATA; tmpDATA = 0;}
		if (VBO!=0){vw_DeleteVBO(*VBO); delete VBO; VBO=0;}

		// находим реальное кол-во частиц на прорисовку
		CStar *tmp = Start;
		PrimitCount = 0;

		// сохраняем данные
		LastCameraAngleX = CurrentCameraRotation.x;
		LastCameraAngleY = CurrentCameraRotation.y;
		LastCameraAngleZ = CurrentCameraRotation.z;

		// получаем текущее положение камеры
		VECTOR3D CurrentCameraLocation;
		vw_GetCameraLocation(&CurrentCameraLocation);


		while (tmp!=0)
		{
			CStar *tmp2 = tmp->Next;
			// небольшая оптимизация, если попадает в сферу - рисуем, нет - значит не видно
			if (vw_SphereInFrustum(tmp->Location + CurrentCameraLocation, Size))
				PrimitCount++;
			tmp = tmp2;
		}

		// если рисовать нечего - выходим
		if (PrimitCount == 0) return;

		// список, в котором они будут упорядочены
		list = new CStar*[PrimitCount]; if (list == 0) return;
		int LenCount = 0;
		float *Len = 0;

		tmp = Start;
		while (tmp!=0)
		{
			CStar *tmp2 = tmp->Next;
			// небольшая оптимизация, если попадает в сферу - рисуем, нет - значит не видно
			if (vw_SphereInFrustum(tmp->Location + CurrentCameraLocation, Size))
			{
				list[LenCount] = tmp;
				LenCount++;
			}
			tmp = tmp2;
		}



		// если не поддерживаем/не включены шейдеры, или нет поддержки вбо
		// делаем старым способом, через временный буфер
		if (!Setup.UseGLSL)
		{
			// делаем массив для всех элементов
#ifdef USE_GLES
			// войдет RI_3f_XYZ | RI_2f_TEX | RI_4ub_COLOR
			tmpDATA = new float[6*(3+2+1)*PrimitCount]; if (tmpDATA == 0) return;
#else
			// войдет RI_3f_XYZ | RI_2f_TEX | RI_4ub_COLOR
			tmpDATA = new float[4*(3+2+1)*PrimitCount]; if (tmpDATA == 0) return;
#endif
			GLubyte *tmpDATAub = (GLubyte *)tmpDATA;

			// номер float'а в последовательности
			int k=0;

			for (int i=0; i<PrimitCount; i++)
			{
				// находим вектор камера-точка
				VECTOR3D nnTmp;
				// смотрим, если есть не нужно поворачивать, работаем с направлением
				nnTmp = list[i]->Location^(-1.0f);
				nnTmp.Normalize();
				// находим перпендикуляр к вектору nnTmp
				VECTOR3D nnTmp2;
				nnTmp2.x = 1.0f;
				nnTmp2.y = 1.0f;
				nnTmp2.z = -(nnTmp.x + nnTmp.y)/nnTmp.z;
				nnTmp2.Normalize();
				// находим перпендикуляр к векторам nnTmp и nnTmp2
				// файтически - a x b = ( aybz - byaz , azbx - bzax , axby - bxay );
				VECTOR3D nnTmp3;
				nnTmp3.x = nnTmp.y*nnTmp2.z - nnTmp2.y*nnTmp.z;
				nnTmp3.y = nnTmp.z*nnTmp2.x - nnTmp2.z*nnTmp.x;
				nnTmp3.z = nnTmp.x*nnTmp2.y - nnTmp2.x*nnTmp.y;
				nnTmp3.Normalize();

				// находим
				VECTOR3D tmpAngle1,tmpAngle2,tmpAngle3,tmpAngle4;

				tmpAngle1 = nnTmp3^(Size*1.5f);
				tmpAngle3 = nnTmp3^(-Size*1.5f);
				tmpAngle2 = nnTmp2^(Size*1.5f);
				tmpAngle4 = nnTmp2^(-Size*1.5f);


				GLubyte A = (GLubyte)(list[i]->Alpha*255);

				// собираем четырехугольник

#ifdef USE_GLES
				tmpDATA[k++] = list[i]->Location.x+tmpAngle3.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle3.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle3.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 0.0f;
				tmpDATA[k++] = 1.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle3.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle3.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle3.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 0.0f;
				tmpDATA[k++] = 1.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle2.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle2.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle2.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 0.0f;
				tmpDATA[k++] = 0.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle4.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle4.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle4.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 1.0f;
				tmpDATA[k++] = 1.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle1.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle1.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle1.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 1.0f;
				tmpDATA[k++] = 0.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle1.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle1.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle1.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 1.0f;
				tmpDATA[k++] = 0.0f;
#else
				tmpDATA[k++] = list[i]->Location.x+tmpAngle3.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle3.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle3.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 0.0f;
				tmpDATA[k++] = 1.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle2.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle2.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle2.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 0.0f;
				tmpDATA[k++] = 0.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle1.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle1.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle1.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 1.0f;
				tmpDATA[k++] = 0.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle4.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle4.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle4.z;		// Z
				tmpDATAub[k*sizeof(float)] = 204;
				tmpDATAub[k*sizeof(float)+1] = 204;
				tmpDATAub[k*sizeof(float)+2] = 255;
				tmpDATAub[k*sizeof(float)+3] = A;
				k++;
				tmpDATA[k++] = 1.0f;
				tmpDATA[k++] = 1.0f;
#endif
			}
		}
		else
		{
			// все нормально, работаем с шейдерами и вбо


			// делаем массив для всех элементов
#ifdef USE_GLES
			// войдет RI_3f_XYZ | RI_2f_TEX | RI_3f_NORMAL*/
			tmpDATA = new float[6*(3+2+3)*PrimitCount]; if (tmpDATA == 0) return;
#else
			// войдет RI_3f_XYZ | RI_2f_TEX | RI_3f_NORMAL*/
			tmpDATA = new float[4*(3+2+3)*PrimitCount]; if (tmpDATA == 0) return;
#endif
			// номер float'а в последовательности
			int k=0;

			for (int i=0; i<PrimitCount; i++)
			{
				// находим вектор камера-точка
				VECTOR3D nnTmp;
				// смотрим, если есть не нужно поворачивать, работаем с направлением
				nnTmp = list[i]->Location^(-1.0f);
				nnTmp.Normalize();
				// находим перпендикуляр к вектору nnTmp
				VECTOR3D nnTmp2;
				nnTmp2.x = 1.0f;
				nnTmp2.y = 1.0f;
				nnTmp2.z = -(nnTmp.x + nnTmp.y)/nnTmp.z;
				nnTmp2.Normalize();
				// находим перпендикуляр к векторам nnTmp и nnTmp2
				// файтически - a x b = ( aybz - byaz , azbx - bzax , axby - bxay );
				VECTOR3D nnTmp3;
				nnTmp3.x = nnTmp.y*nnTmp2.z - nnTmp2.y*nnTmp.z;
				nnTmp3.y = nnTmp.z*nnTmp2.x - nnTmp2.z*nnTmp.x;
				nnTmp3.z = nnTmp.x*nnTmp2.y - nnTmp2.x*nnTmp.y;
				nnTmp3.Normalize();

				// находим
				VECTOR3D tmpAngle1,tmpAngle2,tmpAngle3,tmpAngle4;

				tmpAngle1 = nnTmp3^(Size*1.5f);
				tmpAngle3 = nnTmp3^(-Size*1.5f);
				tmpAngle2 = nnTmp2^(Size*1.5f);
				tmpAngle4 = nnTmp2^(-Size*1.5f);


				// собираем четырехугольник
				tmpDATA[k++] = list[i]->Location.x+tmpAngle3.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle3.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle3.z;		// Z
				tmpDATA[k++] = 0.0f;// не задействован
				tmpDATA[k++] = 0.0f;// не задействован
				tmpDATA[k++] = list[i]->AlphaDelta;
				tmpDATA[k++] = 0.0f;
				tmpDATA[k++] = 1.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle2.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle2.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle2.z;		// Z
				tmpDATA[k++] = 0.0f;// не задействован
				tmpDATA[k++] = 0.0f;// не задействован
				tmpDATA[k++] = list[i]->AlphaDelta;
				tmpDATA[k++] = 0.0f;
				tmpDATA[k++] = 0.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle1.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle1.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle1.z;		// Z
				tmpDATA[k++] = 0.0f;// не задействован
				tmpDATA[k++] = 0.0f;// не задействован
				tmpDATA[k++] = list[i]->AlphaDelta;
				tmpDATA[k++] = 1.0f;
				tmpDATA[k++] = 0.0f;

				tmpDATA[k++] = list[i]->Location.x+tmpAngle4.x;	// X
				tmpDATA[k++] = list[i]->Location.y+tmpAngle4.y;		// Y
				tmpDATA[k++] = list[i]->Location.z+tmpAngle4.z;		// Z
				tmpDATA[k++] = 1.0f;// не задействован
				tmpDATA[k++] = 1.0f;// не задействован
				tmpDATA[k++] = list[i]->AlphaDelta;
				tmpDATA[k++] = 1.0f;
				tmpDATA[k++] = 1.0f;
			}

			if (CAPS->VBOSupported)
			{
				VBO = new unsigned int;
				if (!vw_BuildVBO(4*PrimitCount, tmpDATA, 8, VBO))
				{
					delete VBO; VBO = 0;
				}
				else
				{
					// только если поддерживае вбо, иначе им рисуем
					if (tmpDATA != 0){delete [] tmpDATA; tmpDATA = 0;}
				}
			}

			if (list != 0){delete [] list; list = 0;}
		}

		if (Len != 0){delete [] Len; Len = 0;}
	}





	if (PrimitCount > 0)
	{
		vw_SetTexture(0, Texture);
		vw_SetTextureBlend(true, RI_BLEND_SRCALPHA, RI_BLEND_ONE);


		// получаем текущее положение камеры
		VECTOR3D CurrentCameraLocation;
		vw_GetCameraLocation(&CurrentCameraLocation);
		CurrentCameraLocation += VECTOR3D(GameCameraGetDeviation()*0.9,-GameCameraGetDeviation()*0.5f,0.0f);


		vw_PushMatrix();
		vw_Translate(CurrentCameraLocation);



		if (!Setup.UseGLSL)
		{
#ifdef USE_GLES
			vw_SendVertices(RI_QUADS, 6*PrimitCount, RI_3f_XYZ | RI_4ub_COLOR | RI_1_TEX, tmpDATA, 6*sizeof(float));
#else
			vw_SendVertices(RI_QUADS, 4*PrimitCount, RI_3f_XYZ | RI_4ub_COLOR | RI_1_TEX, tmpDATA, 6*sizeof(float));
#endif
		}
		else
		{
			if (GLSL != 0)
			{
				vw_UseShaderProgram(GLSL);
				vw_Uniform1i(GLSL, UniformLocations[0], 0);
				vw_Uniform1f(GLSL, UniformLocations[1], Age);
			}

			vw_SendVertices(RI_QUADS, 4*PrimitCount, RI_3f_XYZ | RI_1_TEX | RI_3f_NORMAL, tmpDATA, 8*sizeof(float), VBO);

			if (GLSL != 0) vw_StopShaderProgram();
		}


		vw_PopMatrix();

		vw_SetTextureBlend(false, 0, 0);
	}





	vw_BindTexture(0, 0);
}

