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


#include "ParticleSystem.h"
#include "../Camera/Camera.h"
#include "../RendererInterface/RendererInterface.h"


eParticleSystem * StartParticleSystem = 0;
eParticleSystem * EndParticleSystem = 0;

bool ParticleSystemUseGLSL = false;
float ParticleSystemQuality = 1.0f;
eGLSL *ParticleSystemGLSL = 0;
int ParticleSystemUniformLocations[10];


//-----------------------------------------------------------------------------
//	Установка общих состояний
//-----------------------------------------------------------------------------
void vw_InitParticleSystems(bool UseGLSL, float Quality)
{
	ParticleSystemUseGLSL = UseGLSL;
	ParticleSystemQuality = Quality;

	// при первом присоединении устанавливаем шейдер
	if (ParticleSystemUseGLSL)
	{
		ParticleSystemGLSL = vw_FindShaderByName("ParticleSystem");
		ParticleSystemUniformLocations[0] = vw_GetUniformLocation(ParticleSystemGLSL, "ParticleTexture");
		ParticleSystemUniformLocations[1] = vw_GetUniformLocation(ParticleSystemGLSL, "CameraPoint");
	}
}




//-----------------------------------------------------------------------------
//	Присоеденяем ParticleSystem к списку
//-----------------------------------------------------------------------------
void vw_AttachParticleSystem(eParticleSystem * NewParticleSystem)
{
	if (NewParticleSystem == 0) return;

	// первый в списке...
	if (EndParticleSystem == 0)
	{
		NewParticleSystem->Prev = 0;
		NewParticleSystem->Next = 0;
		StartParticleSystem = NewParticleSystem;
		EndParticleSystem = NewParticleSystem;
	}
	else // продолжаем заполнение...
	{
		NewParticleSystem->Prev = EndParticleSystem;
		NewParticleSystem->Next = 0;
		EndParticleSystem->Next = NewParticleSystem;
		EndParticleSystem = NewParticleSystem;
	}
}




//-----------------------------------------------------------------------------
//	Удаляем ParticleSystem из списка
//-----------------------------------------------------------------------------
void vw_DetachParticleSystem(eParticleSystem * OldParticleSystem)
{
	if (OldParticleSystem == 0) return;

	// переустанавливаем указатели...
	if (StartParticleSystem == OldParticleSystem) StartParticleSystem = OldParticleSystem->Next;
	if (EndParticleSystem == OldParticleSystem) EndParticleSystem = OldParticleSystem->Prev;


	if (OldParticleSystem->Next != 0) OldParticleSystem->Next->Prev = OldParticleSystem->Prev;
		else if (OldParticleSystem->Prev != 0) OldParticleSystem->Prev->Next = 0;
	if (OldParticleSystem->Prev != 0) OldParticleSystem->Prev->Next = OldParticleSystem->Next;
		else if (OldParticleSystem->Next != 0) OldParticleSystem->Next->Prev = 0;
}




//-----------------------------------------------------------------------------
//	Удаляем все ParticleSystem в списке
//-----------------------------------------------------------------------------
void vw_ReleaseAllParticleSystems()
{
	// для всех ParticleSystem
	eParticleSystem *tmp = StartParticleSystem;
	while (tmp!=0)
	{
		eParticleSystem *tmp2 = tmp->Next;
		// удаляем и очищаем всю память, в релизе стоит DetachShip
		delete tmp; tmp = 0;
		tmp = tmp2;
	}

	StartParticleSystem = 0;
	EndParticleSystem = 0;

	ParticleSystemUseGLSL = false;
	ParticleSystemQuality = 1.0f;
	ParticleSystemGLSL = 0;
}








//-----------------------------------------------------------------------------
//	Прорисовываем все ParticleSystems
//-----------------------------------------------------------------------------
void vw_DrawAllParticleSystems()
{
	// текущая текстура
	eTexture *CurrentTexture = 0;

	// делаем все предустановки для прорисовки частиц, чтобы не менять каждый раз
	vw_SetTextureBlend(true, RI_BLEND_SRCALPHA, RI_BLEND_ONE);
	// включаем шейдер, если есть возможность
	if (ParticleSystemUseGLSL)
	{
		if (ParticleSystemGLSL != 0)
		{
			// получаем текущее положение камеры
			VECTOR3D CurrentCameraLocation;
			vw_GetCameraLocation(&CurrentCameraLocation);

			vw_UseShaderProgram(ParticleSystemGLSL);
			vw_Uniform1i(ParticleSystemGLSL, ParticleSystemUniformLocations[0], 0);
			vw_Uniform3f(ParticleSystemGLSL, ParticleSystemUniformLocations[1], CurrentCameraLocation.x, CurrentCameraLocation.y, CurrentCameraLocation.z);
		}
	}
	// выключаем изменение буфера глубины
	glDepthMask(GL_FALSE);



	// для всех
	eParticleSystem *tmp = StartParticleSystem;
	while (tmp!=0)
	{
		eParticleSystem *tmp2 = tmp->Next;

		if (CurrentTexture != tmp->Texture[0])
		{
			vw_SetTexture(0, tmp->Texture[0]);
			CurrentTexture = tmp->Texture[0];
		}
		tmp->Draw(&CurrentTexture);

		tmp = tmp2;
	}



	// включаем запись в буфер глубины
	glDepthMask(GL_TRUE);
	// выключаем шейдер
	if (ParticleSystemUseGLSL)
	{
		vw_StopShaderProgram();
	}

	vw_SetTextureBlend(false, 0, 0);
	// анбиндим текстуру
	vw_BindTexture(0, 0);
}






//-----------------------------------------------------------------------------
//	Прорисовываем блок ParticleSystems
//-----------------------------------------------------------------------------
void vw_DrawParticleSystems(eParticleSystem **DrawParticleSystem, int Quantity)
{
	if (DrawParticleSystem == 0) return;

	// текущая текстура
	eTexture *CurrentTexture = 0;

	// делаем все предустановки для прорисовки частиц, чтобы не менять каждый раз
	vw_SetTextureBlend(true, RI_BLEND_SRCALPHA, RI_BLEND_ONE);
	// включаем шейдер, если есть возможность
	if (ParticleSystemUseGLSL)
	{
		if (ParticleSystemGLSL != 0)
		{
			// получаем текущее положение камеры
			VECTOR3D CurrentCameraLocation;
			vw_GetCameraLocation(&CurrentCameraLocation);

			vw_UseShaderProgram(ParticleSystemGLSL);
			vw_Uniform1i(ParticleSystemGLSL, ParticleSystemUniformLocations[0], 0);
			vw_Uniform3f(ParticleSystemGLSL, ParticleSystemUniformLocations[1], CurrentCameraLocation.x, CurrentCameraLocation.y, CurrentCameraLocation.z);
		}
	}
	// выключаем изменение буфера глубины
	glDepthMask(GL_FALSE);



	for (int i=0; i<Quantity; i++)
	if (DrawParticleSystem[i] != 0)
	{
		if (CurrentTexture != DrawParticleSystem[i]->Texture[0])
		{
			vw_SetTexture(0, DrawParticleSystem[i]->Texture[0]);
			CurrentTexture = DrawParticleSystem[i]->Texture[0];
		}
		DrawParticleSystem[i]->Draw(&CurrentTexture);
	}


	// включаем запись в буфер глубины
	glDepthMask(GL_TRUE);
	// выключаем шейдер
	if (ParticleSystemUseGLSL)
	{
		vw_StopShaderProgram();
	}

	vw_SetTextureBlend(false, 0, 0);
	// анбиндим текстуру
	vw_BindTexture(0, 0);
}







//-----------------------------------------------------------------------------
//	Апдейтим все ParticleSystems
//-----------------------------------------------------------------------------
void vw_UpdateAllParticleSystems(float Time)
{
	// для всех
	eParticleSystem *tmp = StartParticleSystem;
	while (tmp!=0)
	{
		eParticleSystem *tmp2 = tmp->Next;
		if (!tmp->Update(Time))
		{
			delete tmp; tmp = 0;
		}
		tmp = tmp2;
	}
}



