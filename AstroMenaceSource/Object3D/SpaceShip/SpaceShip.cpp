/************************************************************************************

	AstroMenace (Hardcore 3D space shooter with spaceship upgrade possibilities)
	Copyright © 2006-2012 Michael Kurinnoy, Viewizard


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


/// подключаем нужные файлы
#include "SpaceShip.h"
#include "../../Game.h"


extern bool PlayerFighterLeftEng;
extern bool PlayerFighterRightEng;
extern CProjectile *StartProjectile;
extern CProjectile *EndProjectile;


//-----------------------------------------------------------------------------
// Конструктор, инициализация всех переменных
//-----------------------------------------------------------------------------
CSpaceShip::CSpaceShip(void)
{
	// никуда не двигаемся
	Velocity = VECTOR3D(0.0f, 0.0f, 0.0f);

	// болтание объекта, в случае кораблей болтаем всю модель
	DeviationOn = false;
	DeviationObjQuantity = 1;
	Deviation = new VECTOR3D[DeviationObjQuantity];
	NeedDeviation = new float[DeviationObjQuantity];
	CurentDeviation = new float[DeviationObjQuantity];
	CurentDeviationSum = new float[DeviationObjQuantity];

	Deviation[0] = VECTOR3D(0.0f, 1.0f, 0.0f);
	NeedDeviation[0] = vw_Randf0*0.1f;
	CurentDeviation[0] = CurentDeviationSum[0] = 0.0f;

	// и никуда не нужно поворачивать
	NeedRotate = VECTOR3D(0.0f, 0.0f, 0.0f);
	RotationSpeed = VECTOR3D(1.0f, 1.0f, 1.0f);

	// скорость
	MaxSpeed = Speed = NeedSpeed = 0.0f;
	SpeedLR = NeedSpeedLR = SpeedUD = NeedSpeedUD = 0.0f;
	SpeedByCamFB = NeedSpeedByCamFB = SpeedByCamLR = NeedSpeedByCamLR = SpeedByCamUD = NeedSpeedByCamUD = 0.0f;

	// ускорение, пока нет двигателей - его нет...
	MaxAcceler = MaxSpeedRotate = Acceler = AccelerLR = AccelerUD = AccelerByCamFB = AccelerByCamLR = AccelerByCamUD = 0.0f;
	// даем максимальное ускорение
	NeedAcceler = NeedAccelerLR = NeedAccelerUD = NeedAccelerByCamFB = NeedAccelerByCamLR = NeedAccelerByCamUD = 1.0f;



	// двигатели не установлены
	EngineDestroyType = false;
	EngineQuantity = EngineLeftQuantity = EngineRightQuantity = 0;
	Engine = EngineLeft = EngineRight = 0;
	EngineLocation = EngineLeftLocation = EngineRightLocation = 0;
	NeedStopRotation = false;


	// никуда не двигаемся
	MoveForward = MoveBackward = MoveLeft = MoveRight = MoveUp = MoveDown = 0.0f;

	// оружие пока не установлено
	WeaponQuantity = 0;
	WeaponSetFire = 0;
	WeaponLocation = 0;
	WeaponType = 0;
	Weapon = 0;
	WeaponYAngle = 0;
	WeaponFireType = 2;
	WeaponGroupCurrentFireNum = -1;
	WeaponGroupCurrentFireDelay = 0.0f;

	BossWeaponQuantity = 0;
	BossWeaponSetFire = 0;
	BossWeaponLocation = 0;
	BossWeaponType = 0;
	BossWeapon = 0;
	BossWeaponYAngle = 0;
	BossWeaponFireType = 2;
	BossWeaponGroupCurrentFireNum = -1;
	BossWeaponGroupCurrentFireDelay = 0.0f;

	WeaponFlare = 0;

	// подключаем к своему списку
	Next = Prev = 0;
	AttachSpaceShip(this);

}



//-----------------------------------------------------------------------------
// Деструктор
//-----------------------------------------------------------------------------
CSpaceShip::~CSpaceShip(void)
{


	if (WeaponSetFire != 0) {delete [] WeaponSetFire; WeaponSetFire = 0;}
	if (WeaponLocation != 0) {delete [] WeaponLocation; WeaponLocation = 0;}
	if (WeaponType != 0) {delete [] WeaponType; WeaponType = 0;}
	if (WeaponYAngle != 0) {delete [] WeaponYAngle; WeaponYAngle = 0;}
	if (Weapon != 0)
	{
		for (int i=0; i<WeaponQuantity; i++)
			if (Weapon[i] != 0){delete Weapon[i]; Weapon[i] = 0;}

		delete [] Weapon; Weapon = 0;
	}
	if (BossWeaponSetFire != 0) {delete [] BossWeaponSetFire; BossWeaponSetFire = 0;}
	if (BossWeaponLocation != 0) {delete [] BossWeaponLocation; BossWeaponLocation = 0;}
	if (BossWeaponType != 0) {delete [] BossWeaponType; BossWeaponType = 0;}
	if (BossWeaponYAngle != 0) {delete [] BossWeaponYAngle; BossWeaponYAngle = 0;}
	if (BossWeapon != 0)
	{
		for (int i=0; i<BossWeaponQuantity; i++)
			if (BossWeapon[i] != 0){delete BossWeapon[i]; BossWeapon[i] = 0;}

		delete [] BossWeapon; BossWeapon = 0;
	}
	if (WeaponFlare != 0) {delete WeaponFlare; WeaponFlare = 0;}

	if (EngineLocation != 0) {delete [] EngineLocation; EngineLocation = 0;}
	if (Engine != 0)
	{
		for (int i=0; i<EngineQuantity; i++)
			if (Engine[i] != 0)
			{
				if (!EngineDestroyType)
				{
					Engine[i]->IsSuppressed = true;
					Engine[i]->DestroyIfNoParticles = true;
				}
				else
				{
					delete Engine[i]; Engine[i] = 0;
				}
			}
		delete [] Engine; Engine = 0;
	}

	if (EngineLeftLocation != 0) {delete [] EngineLeftLocation; EngineLeftLocation = 0;}
	if (EngineLeft != 0)
	{
		for (int i=0; i<EngineLeftQuantity; i++)
			if (EngineLeft[i] != 0)
			{
				if (!EngineDestroyType)
				{
					EngineLeft[i]->IsSuppressed = true;
					EngineLeft[i]->DestroyIfNoParticles = true;
				}
				else
				{
					delete EngineLeft[i]; EngineLeft[i] = 0;
				}
			}
		delete [] EngineLeft; EngineLeft = 0;
	}

	if (EngineRightLocation != 0) {delete [] EngineRightLocation; EngineRightLocation = 0;}
	if (EngineRight != 0)
	{
		for (int i=0; i<EngineRightQuantity; i++)
			if (EngineRight[i] != 0)
			{
				if (!EngineDestroyType)
				{
					EngineRight[i]->IsSuppressed = true;
					EngineRight[i]->DestroyIfNoParticles = true;
				}
				else
				{
					delete EngineRight[i]; EngineRight[i] = 0;
				}
			}
		delete [] EngineRight; EngineRight = 0;
	}


	DetachSpaceShip(this);

}










//-----------------------------------------------------------------------------
// Установка положения объекта
//-----------------------------------------------------------------------------
void CSpaceShip::SetLocation(VECTOR3D NewLocation)
{
	// вызываем родительскую функцию
	::CObject3D::SetLocation(NewLocation);


	// если оружие вообще есть
	if (Weapon != 0)
	for (int i=0; i<WeaponQuantity; i++)
	{
		if (Weapon[i] != 0) Weapon[i]->SetLocation(NewLocation + WeaponLocation[i]);
	}
	if (BossWeapon != 0)
	for (int i=0; i<BossWeaponQuantity; i++)
	{
		if (BossWeapon[i] != 0) BossWeapon[i]->SetLocation(NewLocation + BossWeaponLocation[i]);
	}
	if (WeaponFlare != 0)
	{
		WeaponFlare->SetLocation(NewLocation + WeaponFlareLocation);
	}


	// положение двигателей
	if (Engine != 0)
	for (int i=0; i<EngineQuantity; i++)
	{
		if (Engine[i] != 0)
		{
			Engine[i]->MoveSystem(NewLocation + EngineLocation[i]);
			Engine[i]->SetStartLocation(EngineLocation[i] + NewLocation);
		}
	}
	if (EngineLeft != 0)
	for (int i=0; i<EngineLeftQuantity; i++)
	{
		if (EngineLeft[i] != 0)
		{
			EngineLeft[i]->MoveSystem(NewLocation + EngineLeftLocation[i]);
			EngineLeft[i]->SetStartLocation(EngineLeftLocation[i] + NewLocation);
		}
	}
	if (EngineRight != 0)
	for (int i=0; i<EngineRightQuantity; i++)
	{
		if (EngineRight[i] != 0)
		{
			EngineRight[i]->MoveSystem(NewLocation + EngineRightLocation[i]);
			EngineRight[i]->SetStartLocation(EngineRightLocation[i] + NewLocation);
		}
	}
}




//-----------------------------------------------------------------------------
// Установка положения объекта, для аркадного режима
//-----------------------------------------------------------------------------
void CSpaceShip::SetLocationArcadePlayer(VECTOR3D NewLocation)
{
	// вызываем родительскую функцию
	::CObject3D::SetLocation(NewLocation);


	// если оружие вообще есть
	if (Weapon != 0)
	for (int i=0; i<WeaponQuantity; i++)
	{
		if (Weapon[i] != 0) Weapon[i]->SetLocation(NewLocation + WeaponLocation[i]);
	}
	if (BossWeapon != 0)
	for (int i=0; i<BossWeaponQuantity; i++)
	{
		if (BossWeapon[i] != 0) BossWeapon[i]->SetLocation(NewLocation + BossWeaponLocation[i]);
	}
	if (WeaponFlare != 0)
	{
		WeaponFlare->SetLocation(NewLocation + WeaponFlareLocation);
	}


	// положение двигателей
	if (Engine != 0)
	for (int i=0; i<EngineQuantity; i++)
	if (Engine[i] != 0)
	{
		Engine[i]->MoveSystem(NewLocation + EngineLocation[i]);
		Engine[i]->SetStartLocation(NewLocation + EngineLocation[i]);
	}
	if (EngineLeft != 0)
	for (int i=0; i<EngineLeftQuantity; i++)
	if (EngineLeft[i] != 0)
	{
		EngineLeft[i]->MoveSystem(NewLocation + EngineLeftLocation[i]);
		EngineLeft[i]->SetStartLocation(NewLocation + EngineLeftLocation[i]);
	}
	if (EngineRight != 0)
	for (int i=0; i<EngineRightQuantity; i++)
	if (EngineRight[i] != 0)
	{
		EngineRight[i]->MoveSystem(NewLocation + EngineRightLocation[i]);
		EngineRight[i]->SetStartLocation(NewLocation + EngineRightLocation[i]);
	}
}






//-----------------------------------------------------------------------------
// Установка углов поворота объекта
//-----------------------------------------------------------------------------
void CSpaceShip::SetRotation(VECTOR3D NewRotation, bool NeedWeaponRotate)
{
	// вызываем родительскую функцию
	::CObject3D::SetRotation(NewRotation);



	// оружие
	if (Weapon != 0)
	for (int i=0; i<WeaponQuantity; i++)
	{
		Matrix33CalcPoint(&(WeaponLocation[i]), OldInvRotationMat);
		Matrix33CalcPoint(&(WeaponLocation[i]), CurrentRotationMat);

		if (Weapon[i] != 0)
		// если нужно поворачивать, или не нужно и в этом оружие наведение не используем (ракетная система)
		if (NeedWeaponRotate || (!NeedWeaponRotate && !Weapon[i]->NeedRotateOnTargeting))
		{
			Weapon[i]->SetRotation(NewRotation);
			Weapon[i]->SetLocation(Location + WeaponLocation[i]);
		}
	}
	if (BossWeapon != 0)
	for (int i=0; i<BossWeaponQuantity; i++)
	{
		Matrix33CalcPoint(&(BossWeaponLocation[i]), OldInvRotationMat);
		Matrix33CalcPoint(&(BossWeaponLocation[i]), CurrentRotationMat);

		if (BossWeapon[i] != 0)
		// если нужно поворачивать, или не нужно и в этом оружие наведение не используем (ракетная система)
		if (NeedWeaponRotate || (!NeedWeaponRotate && !BossWeapon[i]->NeedRotateOnTargeting))
		{
			BossWeapon[i]->SetRotation(NewRotation);
			BossWeapon[i]->SetLocation(Location + BossWeaponLocation[i]);
		}
	}
	if (WeaponFlare != 0)
	{
		Matrix33CalcPoint(&WeaponFlareLocation, OldInvRotationMat);
		Matrix33CalcPoint(&WeaponFlareLocation, CurrentRotationMat);
		WeaponFlare->SetRotation(NewRotation);
		WeaponFlare->SetLocation(Location + WeaponFlareLocation);
	}




	// двигатели
	if (Engine != 0)
	for (int i=0; i<EngineQuantity; i++)
	{
		Matrix33CalcPoint(&(EngineLocation[i]), OldInvRotationMat);
		Matrix33CalcPoint(&(EngineLocation[i]), CurrentRotationMat);

		if (Engine[i] != 0)
		{
			if (Engine[i]->SpeedOnCreation == -1.0f)
			{
				Engine[i]->MoveSystem(EngineLocation[i] + Location);
				Engine[i]->SetStartLocation(EngineLocation[i] + Location);
				Engine[i]->RotateSystemAndParticlesByAngle(Rotation);
			}
			else
			{
				Engine[i]->MoveSystemLocation(EngineLocation[i] + Location);
				Engine[i]->RotateSystemByAngle(Rotation);
			}
		}
	}
	if (EngineLeft != 0)
	for (int i=0; i<EngineLeftQuantity; i++)
	{
		Matrix33CalcPoint(&(EngineLeftLocation[i]), OldInvRotationMat);
		Matrix33CalcPoint(&(EngineLeftLocation[i]), CurrentRotationMat);

		if (EngineLeft[i] != 0)
		{
			EngineLeft[i]->MoveSystemLocation(EngineLeftLocation[i] + Location);
			EngineLeft[i]->SetStartLocation(EngineLeftLocation[i] + Location);
			EngineLeft[i]->RotateSystemByAngle(Rotation);
		}
	}
	if (EngineRight != 0)
	for (int i=0; i<EngineRightQuantity; i++)
	{
		Matrix33CalcPoint(&(EngineRightLocation[i]), OldInvRotationMat);
		Matrix33CalcPoint(&(EngineRightLocation[i]), CurrentRotationMat);

		if (EngineRight[i] != 0)
		{
			EngineRight[i]->MoveSystemLocation(EngineRightLocation[i] + Location);
			EngineRight[i]->SetStartLocation(EngineRightLocation[i] + Location);
			EngineRight[i]->RotateSystemByAngle(Rotation);
		}
	}
}








//-----------------------------------------------------------------------------
// Обновление данных объектa Object3D
//-----------------------------------------------------------------------------
bool CSpaceShip::Update(float Time)
{
	// вызываем родительскую функцию
	// если там передали удалить - выходим
	if (!::CObject3D::Update(Time)) return false;
	// быстро вызвали еще раз... время не изменилось, или почти не изменилось
	if (TimeDelta == 0.0f) return true;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// обработка скрипта
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (StartTimeSheet != 0)
	if (!StartTimeSheet->InUse)
	{
		StartTimeSheet->InUse = true;

		NeedSpeed = StartTimeSheet->Speed;
		NeedAcceler = StartTimeSheet->Acceler;
		NeedSpeedLR = StartTimeSheet->SpeedLR;
		NeedAccelerLR = StartTimeSheet->AccelerLR;
		NeedSpeedUD = StartTimeSheet->SpeedUD;
		NeedAccelerUD = StartTimeSheet->AccelerUD;

		NeedSpeedByCamFB = StartTimeSheet->SpeedByCamFB;
		NeedAccelerByCamFB = StartTimeSheet->AccelerByCamFB;
		NeedSpeedByCamLR = StartTimeSheet->SpeedByCamLR;
		NeedAccelerByCamLR = StartTimeSheet->AccelerByCamLR;
		NeedSpeedByCamUD = StartTimeSheet->SpeedByCamUD;
		NeedAccelerByCamUD = StartTimeSheet->AccelerByCamUD;


		NeedRotate = StartTimeSheet->Rotation;
		RotationSpeed = StartTimeSheet->RotationAcceler;



		if (Weapon != 0)
		for (int i=0; i<WeaponQuantity; i++)
		{
			if (Weapon[i] != 0)
				WeaponSetFire[i] = StartTimeSheet->Fire;
		}
		if (BossWeapon != 0)
		for (int i=0; i<BossWeaponQuantity; i++)
		{
			if (BossWeapon[i] != 0)
				BossWeaponSetFire[i] = StartTimeSheet->BossFire;
		}
	}




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// если у корабля есть спец средства против ракет...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (WeaponFlare != 0)
	{
		// проверка, есть ли вражеские ракеты?
		bool NeedFlare = false;
		CProjectile *tmpProjectile = StartProjectile;
		while (!NeedFlare && tmpProjectile!=0)
		{
			CProjectile *tmpProjectile2 = tmpProjectile->Next;

			if ((ObjectStatus == 1 && tmpProjectile->ObjectStatus > 1) ||
				// снаряды врагов - с союзниками или игроком
				(ObjectStatus > 1 && tmpProjectile->ObjectStatus == 1) ||
				// снаряды игрока со всеми, кроме игрока
				(ObjectStatus != 3 && tmpProjectile->ObjectStatus == 3))
			if (tmpProjectile->ProjectileType == 1)
			{
				NeedFlare = true;
			}

			tmpProjectile = tmpProjectile2;
		}


		tmpProjectile = StartProjectile;
		if (NeedFlare)
		while (tmpProjectile!=0)
		{
			CProjectile *tmpProjectile2 = tmpProjectile->Next;
			// если навелись на этот объект ракетой
			// т.к. только у ракеты тут не ноль
			if (tmpProjectile->Target == this)
			{
				// начинаем отстреливать фларес
				WeaponFlareSetFire = true;
			}

			tmpProjectile = tmpProjectile2;
		}
		else
			WeaponFlareSetFire = false;
	}







	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// обработка указателей действия, нужно для управления кораблем игрока
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (ObjectStatus == 3)
	{
		if (MoveForward > 0.0f || MoveBackward > 0.0f)
		{
			NeedSpeed = MaxSpeed*MoveForward-MaxSpeed*MoveBackward;
		}
		else NeedSpeed = 0.0f;

		if (MoveLeft > 0.0f || MoveRight > 0.0f)
		{
			NeedRotate.y = MaxAcceler*MaxSpeed*MoveRight-MaxAcceler*MaxSpeed*MoveLeft;
		}
		else NeedRotate.y = 0.0f;

		if (MoveUp > 0.0f || MoveDown > 0.0f)
		{
			NeedRotate.x = MaxAcceler*MaxSpeed*MoveUp-MaxAcceler*MaxSpeed*MoveDown;
		}
		else NeedRotate.x = 0.0f;
	}





	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// повотор
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// выключаем двигатели, если нужно - включим
	if (EngineLeft != 0)
	for (int i=0; i<EngineLeftQuantity; i++)
	{
		if (EngineLeft[i] != 0) EngineLeft[i]->IsSuppressed = true;
	}
	if (EngineRight != 0)
	for (int i=0; i<EngineRightQuantity; i++)
	{
		if (EngineRight[i] != 0) EngineRight[i]->IsSuppressed = true;
	}



	// если нужно поворачивать
	if ( !(ObjectStatus == 3) )
	{
		if (NeedRotate.x != 0.0f || NeedRotate.y != 0.0f || NeedRotate.z != 0.0f)
		{
			// Находим допустимый поворот по углу
			VECTOR3D tmpRotate(0.0f, 0.0f, 0.0f);

			// угол по x
			if (NeedRotate.x != 0.0f)
			{
				float Sign = 1.0f;
				if (NeedRotate.x < 0.0f) Sign = -1.0f;
				// вычисляем скорость поворота по данным двигателя
				tmpRotate.x = Sign*MaxSpeedRotate*RotationSpeed.x*TimeDelta;
				// смотрим, если уже повернули - снимаем
				if (Sign == 1.0f)
				{if (tmpRotate.x >= NeedRotate.x) {tmpRotate.x = NeedRotate.x; NeedRotate.x = 0.0f;}}
				else {if (tmpRotate.x <= NeedRotate.x) {tmpRotate.x = NeedRotate.x; NeedRotate.x = 0.0f;}}
				// меняем значение
				if (NeedRotate.x != 0.0f) NeedRotate.x -= tmpRotate.x;
			}

			// угол по y
			if (NeedRotate.y != 0.0f)
			{
				float Sign = 1.0f;
				if (NeedRotate.y < 0.0f) Sign = -1.0f;
				// вычисляем скорость поворота по данным двигателя
				tmpRotate.y = Sign*MaxSpeedRotate*RotationSpeed.y*TimeDelta;
				// смотрим, если уже повернули - снимаем
				if (Sign == 1.0f)
				{
					if (tmpRotate.y >= NeedRotate.y)
					{
						tmpRotate.y = NeedRotate.y;
						NeedRotate.y = 0.0f;
					}
				}
				else
				{
					if (tmpRotate.y <= NeedRotate.y)
					{
						tmpRotate.y = NeedRotate.y;
						NeedRotate.y = 0.0f;
					}
				}
				// меняем значение
				if (NeedRotate.y != 0.0f) NeedRotate.y -= tmpRotate.y;

				// включаем двигатель на поворот
				if (NeedRotate.y > 0.0f)
				{
					if (EngineLeft != 0)
					for (int i=0; i<EngineLeftQuantity; i++)
					{
						if (EngineLeft[i] != 0) EngineLeft[i]->IsSuppressed = false;
					}
				}
				else
				{
					if (EngineRight != 0)
					for (int i=0; i<EngineRightQuantity; i++)
					{
						if (EngineRight[i] != 0) EngineRight[i]->IsSuppressed = false;
					}
				}
				// создаем эффект торможения другим двигателем
				NeedStopRotation = true;
			}


			// угол по z
			if (NeedRotate.z != 0.0f)
			{
				float Sign = 1.0f;
				if (NeedRotate.z < 0.0f) Sign = -1.0f;
				// вычисляем скорость поворота по данным двигателя
				tmpRotate.z = Sign*MaxSpeedRotate*RotationSpeed.z*TimeDelta;
				// смотрим, если уже повернули - снимаем
				if (Sign == 1.0f)
				{if (tmpRotate.z >= NeedRotate.z) {tmpRotate.z = NeedRotate.z; NeedRotate.z = 0.0f;}}
				else {if (tmpRotate.z <= NeedRotate.z) {tmpRotate.z = NeedRotate.z; NeedRotate.z = 0.0f;}}
				// меняем значение
				if (NeedRotate.z != 0.0f) NeedRotate.z -= tmpRotate.z;

				// включаем двигатель на поворот
				if (NeedRotate.z < 0.0f)
				{
					if (EngineLeft != 0)
					for (int i=0; i<EngineLeftQuantity; i++)
					{
						if (EngineLeft[i] != 0) EngineLeft[i]->IsSuppressed = false;
					}
				}
				else
				{
					if (EngineRight != 0)
					for (int i=0; i<EngineRightQuantity; i++)
					{
						if (EngineRight[i] != 0) EngineRight[i]->IsSuppressed = false;
					}
				}
				// создаем эффект торможения другим двигателем
				NeedStopRotation = true;
			}


			// установка поворота там же сохраняем, какой общий поворот модели
			SetRotation(tmpRotate);

		}
		else
		{
			if (NeedStopRotation)
			{

				if (EngineLeft != 0)
				for (int i=0; i<EngineLeftQuantity; i++)
				{
					if (EngineLeft[i] != 0) EngineLeft[i]->IsSuppressed = false;
				}
				if (EngineRight != 0)
				for (int i=0; i<EngineRightQuantity; i++)
				{
					if (EngineRight[i] != 0) EngineRight[i]->IsSuppressed = false;
				}

				NeedStopRotation = false;
			}
			else
			{
				if (EngineLeft != 0)
				for (int i=0; i<EngineLeftQuantity; i++)
				{
					if (EngineLeft[i] != 0) EngineLeft[i]->IsSuppressed = true;
				}
				if (EngineRight != 0)
				for (int i=0; i<EngineRightQuantity; i++)
				{
					if (EngineRight[i] != 0) EngineRight[i]->IsSuppressed = true;
				}
			}
		}
	}
	else
	{

			if (EngineLeft != 0)
			for (int i=0; i<EngineLeftQuantity; i++)
			{
				if (EngineLeft[i] != 0) EngineLeft[i]->IsSuppressed = !PlayerFighterLeftEng;
			}

			if (EngineRight != 0)
			for (int i=0; i<EngineRightQuantity; i++)
			{
				if (EngineRight[i] != 0) EngineRight[i]->IsSuppressed = !PlayerFighterRightEng;
			}
	}










	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ускорение-замедление
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// вперед-назад
	// если нужно разогнаться, или управление на игроке - и нужно стремиться к нулю
	if (NeedSpeed != 0.0f || (ObjectStatus == 3 && Speed != 0.0f))
	{
		float Sign = 1.0f;
		// нужно двигать назад
		if (NeedSpeed < 0.0f) Sign = -1.0f;

		// "ровняем" скорость под модель
		if (Sign == 1.0f)
		{Clamp(NeedSpeed, 0.0f, MaxSpeed);}
		else
		{Clamp(NeedSpeed, -MaxSpeed, 0.0f);}

		// случай, когда нужно затормозить а не менять направление
		if (Sign == 1.0f)
		{if (NeedSpeed < Speed) Sign = -1.0f;}
		else
		{if (NeedSpeed > Speed) Sign = 1.0f;}


		// даем полный газ, учитывая сколько процентов можем выдать
		Acceler = Sign*MaxAcceler*NeedAcceler;

		// считаем текущую скорость
		Speed = Speed + Acceler*TimeDelta;

		// смотрим, если уже разогнались - снимаем
		if (Sign == 1.0f)
		{if (NeedSpeed <= Speed) {Speed = NeedSpeed; NeedSpeed = 0.0f;}}
		else {if (NeedSpeed >= Speed) {Speed = NeedSpeed; NeedSpeed = 0.0f;}}


		// если нужны двигатели торможения - включаем маневровые
		if (Sign == -1.0f)
		{
			if (EngineLeft != 0)
			for (int i=0; i<EngineLeftQuantity; i++)
			{
				if (EngineLeft[i] != 0) EngineLeft[i]->IsSuppressed = false;
			}
			if (EngineRight != 0)
			for (int i=0; i<EngineRightQuantity; i++)
			{
				if (EngineRight[i] != 0) EngineRight[i]->IsSuppressed = false;
			}
		}
	}
	// влево-вправо
	if (NeedSpeedLR != 0.0f)
	{
		float Sign = 1.0f;
		// нужно двигать назад
		if (NeedSpeedLR < 0.0f) Sign = -1.0f;

		// "ровняем" скорость под модель
		if (Sign == 1.0f)
		{Clamp(NeedSpeedLR, 0.0f, MaxSpeed);}
		else
		{Clamp(NeedSpeedLR, -MaxSpeed, 0.0f);}

		// случай, когда нужно затормозить а не менять направление
		if (Sign == 1.0f)
		{if (NeedSpeedLR < SpeedLR) Sign = -1.0f;}
		else
		{if (NeedSpeedLR > SpeedLR) Sign = 1.0f;}


		// даем полный газ, учитывая сколько процентов можем выдать
		AccelerLR = Sign*MaxAcceler*NeedAccelerLR;

		// считаем текущую скорость
		SpeedLR = SpeedLR + AccelerLR*TimeDelta;

		// смотрим, если уже разогнались - снимаем
		if (Sign == 1.0f)
		{if (NeedSpeedLR <= SpeedLR) {SpeedLR = NeedSpeedLR; NeedSpeedLR = 0.0f;}}
		else {if (NeedSpeedLR >= SpeedLR) {SpeedLR = NeedSpeedLR; NeedSpeedLR = 0.0f;}}

	}
	// вверх-вниз
	if (NeedSpeedUD != 0.0f)
	{
		float Sign = 1.0f;
		// нужно двигать назад
		if (NeedSpeedUD < 0.0f) Sign = -1.0f;

		// "ровняем" скорость под модель
		if (Sign == 1.0f)
		{Clamp(NeedSpeedUD, 0.0f, MaxSpeed);}
		else
		{Clamp(NeedSpeedUD, -MaxSpeed, 0.0f);}

		// случай, когда нужно затормозить а не менять направление
		if (Sign == 1.0f)
		{if (NeedSpeedUD < SpeedUD) Sign = -1.0f;}
		else
		{if (NeedSpeedUD > SpeedUD) Sign = 1.0f;}


		// даем полный газ, учитывая сколько процентов можем выдать
		AccelerUD = Sign*MaxAcceler*NeedAccelerUD;

		// считаем текущую скорость
		SpeedUD = SpeedUD + AccelerUD*TimeDelta;

		// смотрим, если уже разогнались - снимаем
		if (Sign == 1.0f)
		{if (NeedSpeedUD <= SpeedUD) {SpeedUD = NeedSpeedUD; NeedSpeedUD = 0.0f;}}
		else {if (NeedSpeedUD >= SpeedUD) {SpeedUD = NeedSpeedUD; NeedSpeedUD = 0.0f;}}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ускорение-замедление по вектору камеры
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// вперед-назад
	if (NeedSpeedByCamFB != 0.0f)
	{
		float Sign = 1.0f;
		// нужно двигать назад
		if (NeedSpeedByCamFB < 0.0f) Sign = -1.0f;

		// "ровняем" скорость под модель
		if (Sign == 1.0f)
		{Clamp(NeedSpeedByCamFB, 0.0f, MaxSpeed);}
		else
		{Clamp(NeedSpeedByCamFB, -MaxSpeed, 0.0f);}

		// случай, когда нужно затормозить а не менять направление
		if (Sign == 1.0f)
		{if (NeedSpeedByCamFB < SpeedByCamFB) Sign = -1.0f;}
		else
		{if (NeedSpeedByCamFB > SpeedByCamFB) Sign = 1.0f;}


		// даем полный газ, учитывая сколько процентов можем выдать
		AccelerByCamFB = Sign*MaxAcceler*NeedAccelerByCamFB;

		// считаем текущую скорость
		SpeedByCamFB = SpeedByCamFB + AccelerByCamFB*TimeDelta;

		// смотрим, если уже разогнались - снимаем
		if (Sign == 1.0f)
		{if (NeedSpeedByCamFB <= SpeedByCamFB) {SpeedByCamFB = NeedSpeedByCamFB; NeedSpeedByCamFB = 0.0f;}}
		else {if (NeedSpeedByCamFB >= SpeedByCamFB) {SpeedByCamFB = NeedSpeedByCamFB; NeedSpeedByCamFB = 0.0f;}}
	}
	// влево-вправо
	if (NeedSpeedByCamLR != 0.0f)
	{
		float Sign = 1.0f;
		// нужно двигать назад
		if (NeedSpeedByCamLR < 0.0f) Sign = -1.0f;

		// "ровняем" скорость под модель
		if (Sign == 1.0f)
		{Clamp(NeedSpeedByCamLR, 0.0f, MaxSpeed);}
		else
		{Clamp(NeedSpeedByCamLR, -MaxSpeed, 0.0f);}

		// случай, когда нужно затормозить а не менять направление
		if (Sign == 1.0f)
		{if (NeedSpeedByCamLR < SpeedByCamLR) Sign = -1.0f;}
		else
		{if (NeedSpeedByCamLR > SpeedByCamLR) Sign = 1.0f;}


		// даем полный газ, учитывая сколько процентов можем выдать
		AccelerByCamLR = Sign*MaxAcceler*NeedAccelerByCamLR;

		// считаем текущую скорость
		SpeedByCamLR = SpeedByCamLR + AccelerByCamLR*TimeDelta;

		// смотрим, если уже разогнались - снимаем
		if (Sign == 1.0f)
		{if (NeedSpeedByCamLR <= SpeedByCamLR) {SpeedByCamLR = NeedSpeedByCamLR; NeedSpeedByCamLR = 0.0f;}}
		else {if (NeedSpeedByCamLR >= SpeedByCamLR) {SpeedByCamLR = NeedSpeedByCamLR; NeedSpeedByCamLR = 0.0f;}}

	}
	// вверх-вниз
	if (NeedSpeedByCamUD != 0.0f)
	{
		float Sign = 1.0f;
		// нужно двигать назад
		if (NeedSpeedByCamUD < 0.0f) Sign = -1.0f;

		// "ровняем" скорость под модель
		if (Sign == 1.0f)
		{Clamp(NeedSpeedByCamUD, 0.0f, MaxSpeed);}
		else
		{Clamp(NeedSpeedByCamUD, -MaxSpeed, 0.0f);}

		// случай, когда нужно затормозить а не менять направление
		if (Sign == 1.0f)
		{if (NeedSpeedByCamUD < SpeedByCamUD) Sign = -1.0f;}
		else
		{if (NeedSpeedByCamUD > SpeedByCamUD) Sign = 1.0f;}


		// даем полный газ, учитывая сколько процентов можем выдать
		AccelerByCamUD = Sign*MaxAcceler*NeedAccelerByCamUD;

		// считаем текущую скорость
		SpeedByCamUD = SpeedByCamUD + AccelerByCamUD*TimeDelta;

		// смотрим, если уже разогнались - снимаем
		if (Sign == 1.0f)
		{if (NeedSpeedByCamUD <= SpeedByCamUD) {SpeedByCamUD = NeedSpeedByCamUD; NeedSpeedByCamUD = 0.0f;}}
		else {if (NeedSpeedByCamUD >= SpeedByCamUD) {SpeedByCamUD = NeedSpeedByCamUD; NeedSpeedByCamUD = 0.0f;}}
	}













	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// смотрим, есть ли команда открыть огонь
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Weapon != 0)
	{
		// если залп или игрок (игроку регулируем сами)
		if (WeaponFireType == 1 || ObjectStatus == 3)
		{
			for (int i=0; i<WeaponQuantity; i++)
				if (Weapon[i] != 0)
					if (WeaponSetFire[i])
						Weapon[i]->WeaponFire(Time);
		}
		else// переменный огонь
		{

			int PrimCount = 0;
			float PrimTime = 0.0f;
			int FirstWeapon = 6;
			int LastWeapon = 0;

			WeaponGroupCurrentFireDelay -= TimeDelta;

			// находим кол-во оружия
			for (int i=0; i<WeaponQuantity; i++)
			if (Weapon[i] != 0)
			{
				PrimCount++;
				PrimTime += Weapon[i]->NextFireTime;
				if (FirstWeapon > i) FirstWeapon = i;
				if (LastWeapon < i) LastWeapon = i;
			}
			// если еще не было начальной установки
			if (WeaponGroupCurrentFireNum == -1) WeaponGroupCurrentFireNum = FirstWeapon;


			// стреляем
			for (int i=0; i<WeaponQuantity; i++)
			if (Weapon[i] != 0)
			if (WeaponSetFire[i])
			{
				if (WeaponGroupCurrentFireNum == i &&
					WeaponGroupCurrentFireDelay <= 0.0f)
				{
					Weapon[i]->WeaponFire(Time);

					WeaponGroupCurrentFireDelay = PrimTime/(PrimCount*PrimCount);
					WeaponGroupCurrentFireNum ++;
					if (WeaponGroupCurrentFireNum > LastWeapon) WeaponGroupCurrentFireNum = FirstWeapon;

					// если такого оружия нет, берем что есть
					if (Weapon[WeaponGroupCurrentFireNum] == 0)
					{
						bool exit = false;
						while (!exit)
						{
							WeaponGroupCurrentFireNum ++;
							if (WeaponGroupCurrentFireNum > LastWeapon) WeaponGroupCurrentFireNum = FirstWeapon;
							if (Weapon[WeaponGroupCurrentFireNum] != 0) exit = true;
						}
					}

				}
			}

		}
	}
	if (BossWeapon != 0)
	{
		// если залп
		if (BossWeaponFireType == 1)
		{
			for (int i=0; i<BossWeaponQuantity; i++)
				if (BossWeapon[i] != 0)
					if (BossWeaponSetFire[i])
						BossWeapon[i]->WeaponFire(Time);
		}
		else// переменный огонь
		{

			int PrimCount = 0;
			float PrimTime = 0.0f;
			int FirstWeapon = 6;
			int LastWeapon = 0;

			BossWeaponGroupCurrentFireDelay -= TimeDelta;

			// находим кол-во оружия
			for (int i=0; i<BossWeaponQuantity; i++)
			if (BossWeapon[i] != 0)
			{
				PrimCount++;
				PrimTime += BossWeapon[i]->NextFireTime;
				if (FirstWeapon > i) FirstWeapon = i;
				if (LastWeapon < i) LastWeapon = i;
			}
			// если еще не было начальной установки
			if (BossWeaponGroupCurrentFireNum == -1) BossWeaponGroupCurrentFireNum = FirstWeapon;


			// стреляем
			for (int i=0; i<BossWeaponQuantity; i++)
			if (BossWeapon[i] != 0)
			if (BossWeaponSetFire[i])
			{
				if (BossWeaponGroupCurrentFireNum == i &&
					BossWeaponGroupCurrentFireDelay <= 0.0f)
				{
					BossWeapon[i]->WeaponFire(Time);

					BossWeaponGroupCurrentFireDelay = PrimTime/(PrimCount*PrimCount);
					BossWeaponGroupCurrentFireNum ++;
					if (BossWeaponGroupCurrentFireNum > LastWeapon) BossWeaponGroupCurrentFireNum = FirstWeapon;

					// если такого оружия нет, берем что есть
					if (BossWeapon[BossWeaponGroupCurrentFireNum] == 0)
					{
						bool exit = false;
						while (!exit)
						{
							BossWeaponGroupCurrentFireNum ++;
							if (BossWeaponGroupCurrentFireNum > LastWeapon) BossWeaponGroupCurrentFireNum = FirstWeapon;
							if (BossWeapon[BossWeaponGroupCurrentFireNum] != 0) exit = true;
						}
					}

				}
			}

		}
	}

	if (WeaponFlare != 0)
	{
		if (WeaponFlareSetFire)
				WeaponFlare->WeaponFire(Time);
	}





	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// небольшая девиация-болтание корпуса
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (DeviationOn)
	for (int i=0; i<DeviationObjQuantity; i++)
	{
		float Sign = 1.0f;
		// нужно двигать
		if (NeedDeviation[i] < 0.0f) Sign = -1.0f;
		if (Sign == 1.0f)
		{if (NeedDeviation[i] < CurentDeviationSum[i]) Sign = -1.0f;}
		else
		{if (NeedDeviation[i] > CurentDeviationSum[i]) Sign = 1.0f;}

		CurentDeviation[i] = Sign*0.035f*TimeDelta;

		if (Sign == 1.0f)
		{
			if (NeedDeviation[i] <= CurentDeviationSum[i]+CurentDeviation[i])
			{
				CurentDeviation[i] -= CurentDeviationSum[i]+CurentDeviation[i]-NeedDeviation[i];
				CurentDeviationSum[i] += CurentDeviation[i];
				NeedDeviation[i] = vw_Randf0*0.1f;
			}
			else CurentDeviationSum[i] += CurentDeviation[i];
		}
		else
		{
			if (NeedDeviation[i] >= CurentDeviationSum[i]+CurentDeviation[i])
			{
				CurentDeviation[i] += CurentDeviationSum[i]+CurentDeviation[i]-NeedDeviation[i];
				CurentDeviationSum[i] += CurentDeviation[i];
				NeedDeviation[i] = vw_Randf0*0.1f;
			}
			else CurentDeviationSum[i] += CurentDeviation[i];
		}

	}

	// только для корабля игрока - небольшое болтание во время полета
	if (ObjectStatus == 3)
	if (DeviationOn)
	{
		SetRotation((Deviation[0]^(CurentDeviation[0]*50.0f)), false);
	}




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// считаем вектор движения
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Velocity = Orientation^(Speed*TimeDelta);
	if (fabs(SpeedLR) > 0.01f)
	{
		VECTOR3D tmp(SpeedLR*TimeDelta,0.0f,0.0f);
		Matrix33CalcPoint(&tmp, CurrentRotationMat);
		Velocity += tmp;
	}
	if (fabs(SpeedUD) > 0.01f)
	{
		VECTOR3D tmp(0.0f,SpeedUD*TimeDelta,0.0f);
		Matrix33CalcPoint(&tmp, CurrentRotationMat);
		Velocity += tmp;
	}


	if (fabs(SpeedByCamFB) > 0.01f)
	{
		VECTOR3D tmp = GameCameraMovement^(SpeedByCamFB*TimeDelta);
		Velocity += tmp;
	}
	if (fabs(SpeedByCamLR) > 0.01f)
	{
		VECTOR3D tmp = GameCameraMovement^(SpeedByCamLR*TimeDelta);
		RotatePoint(&tmp, VECTOR3D(0.0,-90.0f,0.0f));
		Velocity += tmp;
	}
	if (fabs(SpeedByCamUD) > 0.01f)
	{
		VECTOR3D tmp = GameCameraMovement^(SpeedByCamUD*TimeDelta);
		RotatePoint(&tmp, VECTOR3D(90.0f,0.0f,0.0f));
		Velocity += tmp;
	}


	// если это не корабль игрока и включена девиация
	if (ObjectStatus != 3)
	if (DeviationOn) Velocity += Deviation[0]^CurentDeviation[0];



	// перемещение объекта, если нужно
	if (Velocity.x != 0.0f || Velocity.y != 0.0f  || Velocity.z != 0.0f )
	{
		// делаем сдвиг модели в указанную точку
		SetLocation(Location+Velocity);
	}





	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Делаем установку работы двигателей, согласуем со скоростью корабля
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Engine != 0)
	{
		float tmpSpeed = Speed;
		if (tmpSpeed>6.0f) tmpSpeed=6.0f;
		if (tmpSpeed<-6.0f) tmpSpeed=-6.0f;
		tmpSpeed/=2.0f;

		for (int i=0; i<EngineQuantity; i++)
		if (Engine[i] != 0)
		if (Engine[i]->SpeedOnCreation != -1.0f)
			Engine[i]->Speed = Engine[i]->SpeedOnCreation + tmpSpeed;

	}









	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// работа с оружием - наведение его на ближайшую цель
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// а нужно ли стерять
	bool NeedFire = false;
	if (Weapon != 0)
	for (int i=0; i<WeaponQuantity; i++)
	{
		if (Weapon[i] != 0)
		if (WeaponSetFire[i]) NeedFire = true;
	}
	bool NeedBossFire = false;
	if (BossWeapon != 0)
	for (int i=0; i<BossWeaponQuantity; i++)
	{
		if (BossWeapon[i] != 0)
		if (BossWeaponSetFire[i]) NeedBossFire = true;
	}



	// если не игрок игрок и есть режим действия - нужно "искать" противника
	if (ObjectStatus == 1 && NeedFire)
	{
		VECTOR3D NeedAngle = Rotation;

		// используем ID как маркер, чтобы не обрабатывать этот объект в процедуре
		int tmpID = ID;
		ID = 111111;

		// находим среднюю точку положение оружия
		VECTOR3D WeaponAvLocation(0.0f,0.0f,0.0f);
		int UsedWeaponQunt = 0;
		if (Weapon != 0)
		for (int i=0; i<WeaponQuantity; i++)
		if (Weapon[i] != 0)
		if (Weapon[i]->NeedRotateOnTargeting)
		{
			WeaponAvLocation = WeaponAvLocation + WeaponLocation[i] + Weapon[i]->FireLocation + Location;
			UsedWeaponQunt ++;
		}
		WeaponAvLocation.x = WeaponAvLocation.x / UsedWeaponQunt;
		WeaponAvLocation.y = WeaponAvLocation.y / UsedWeaponQunt;
		WeaponAvLocation.z = WeaponAvLocation.z / UsedWeaponQunt;


		int WeapNum = -1;
		VECTOR3D	FirePos(0.0f,0.0f,0.0f);
		if (Weapon != 0)
		{
			// находим номер
			for (int i=0; i<WeaponQuantity; i++)
			if (Weapon[i] != 0)
			if (Weapon[i]->NeedRotateOnTargeting)
			if (WeapNum == -1)
			{
				WeapNum = Weapon[0]->ObjectCreationType;
			}
			if (WeapNum == -1) WeapNum = 204; // номер самого простого из пиратского оружия


			int Count = 0;
			for (int i=0; i<WeaponQuantity; i++)
			if (Weapon[i] != 0)
			if (Weapon[i]->NeedRotateOnTargeting)
			{
				FirePos += WeaponLocation[i];
				Count++;
			}
			FirePos = FirePos^(1.0f/Count);
		}

		GetEnemyShipOnTargetOrientateion(ObjectStatus, WeaponAvLocation, Rotation,
				CurrentRotationMat, &NeedAngle,	WeapNum);

		// всему оружию ставим нужную ориентацию
		if (Weapon != 0)
		for (int i=0; i<WeaponQuantity; i++)
		{
			if (Weapon[i] != 0)
			if (Weapon[i]->NeedRotateOnTargeting)
			{
				NeedAngle.y = Weapon[i]->Rotation.y;
				NeedAngle.z = Weapon[i]->Rotation.z;

				Weapon[i]->SetRotation(Weapon[i]->Rotation^(-1));
				Weapon[i]->SetRotation(NeedAngle);
			}
		}

		ID = tmpID;
	}
	if (ObjectStatus == 1 && NeedBossFire)
	{
		VECTOR3D NeedAngle = Rotation;

		// используем ID как маркер, чтобы не обрабатывать этот объект в процедуре
		int tmpID = ID;
		ID = 111111;

		// находим среднюю точку положение оружия
		VECTOR3D WeaponAvLocation(0.0f,0.0f,0.0f);
		int UsedWeaponQunt = 0;
		if (BossWeapon != 0)
		for (int i=0; i<BossWeaponQuantity; i++)
		if (BossWeapon[i] != 0)
		if (BossWeapon[i]->NeedRotateOnTargeting)
		{
			WeaponAvLocation = WeaponAvLocation + BossWeaponLocation[i] + BossWeapon[i]->FireLocation + Location;
			UsedWeaponQunt ++;
		}
		WeaponAvLocation.x = WeaponAvLocation.x / UsedWeaponQunt;
		WeaponAvLocation.y = WeaponAvLocation.y / UsedWeaponQunt;
		WeaponAvLocation.z = WeaponAvLocation.z / UsedWeaponQunt;

		int WeapNum = -1;
		VECTOR3D	FirePos(0.0f,0.0f,0.0f);
		if (BossWeapon != 0)
		{
			// находим номер
			for (int i=0; i<BossWeaponQuantity; i++)
			if (BossWeapon[i] != 0)
			if (BossWeapon[i]->NeedRotateOnTargeting)
			if (WeapNum == -1)
			{
				WeapNum = BossWeapon[0]->ObjectCreationType;
			}
			if (WeapNum == -1) WeapNum = 204; // номер самого простого из пиратского оружия


			int Count = 0;
			for (int i=0; i<BossWeaponQuantity; i++)
			if (BossWeapon[i] != 0)
			if (BossWeapon[i]->NeedRotateOnTargeting)
			{
				FirePos += BossWeaponLocation[i];
				Count++;
			}
			FirePos = FirePos^(1.0f/Count);
		}

		GetEnemyShipOnTargetOrientateion(ObjectStatus, WeaponAvLocation, Rotation,
				CurrentRotationMat, &NeedAngle,	WeapNum);

		// всему оружию ставим нужную ориентацию
		if (BossWeapon != 0)
		for (int i=0; i<BossWeaponQuantity; i++)
		{
			if (BossWeapon[i] != 0)
			if (BossWeapon[i]->NeedRotateOnTargeting)
			{
				NeedAngle.y = BossWeapon[i]->Rotation.y;
				NeedAngle.z = BossWeapon[i]->Rotation.z;

				BossWeapon[i]->SetRotation(BossWeapon[i]->Rotation^(-1));
				BossWeapon[i]->SetRotation(NeedAngle);
			}
		}

		ID = tmpID;
	}





	// если в игре, а не в меню - иначе в оружейной дергается оружие
	if (GameStatus == GAME)
	// так стреляют только свои :)
	if (ObjectStatus == 2)
	{
		// используем ID как маркер, чтобы не обрабатывать этот объект в процедуре
		int tmpID = ID;
		ID = 111111;

		// ставим скорость наведения оружия
		float TargetingSpeed = 1.0f;

		// находим среднюю точку положение оружия
		VECTOR3D WeaponAvLocation(0.0f,0.0f,0.0f);
		int UsedWeaponQunt = 0;
		if (Weapon != 0)
		for (int i=0; i<WeaponQuantity; i++)
		if (Weapon[i] != 0)
		{
			WeaponAvLocation = WeaponAvLocation + WeaponLocation[i] + Weapon[i]->FireLocation + Location;
			UsedWeaponQunt ++;
		}
		WeaponAvLocation.x = WeaponAvLocation.x / UsedWeaponQunt;
		WeaponAvLocation.y = WeaponAvLocation.y / UsedWeaponQunt;
		WeaponAvLocation.z = WeaponAvLocation.z / UsedWeaponQunt;


		VECTOR3D NeedAngle = Rotation;

		// всему оружию ставим нужную ориентацию
		if (Weapon != 0)
		for (int i=0; i<WeaponQuantity; i++)
		{
			if (Weapon[i] != 0)
			if (Weapon[i]->NeedRotateOnTargeting)
			{
				NeedAngle = Rotation;
				// добавляем базовый угол, чтобы по умолчанию устанавливало его
				NeedAngle.y += WeaponYAngle[i];

					GetShipOnTargetOrientateion(ObjectStatus, Location + WeaponLocation[i] + Weapon[i]->FireLocation, Rotation,
						Length,	CurrentRotationMat, &NeedAngle, Width, true, true, Location + WeaponLocation[i] + Weapon[i]->FireLocation, Weapon[i]->ObjectCreationType);

				VECTOR3D NeedAngleTmp = NeedAngle;

				// учитываем скорость поворота по вертикали
				if (Weapon[i]->Rotation.x < NeedAngle.x)
				{
					float NeedAngle_x = Weapon[i]->Rotation.x+40.0f*TargetingSpeed*TimeDelta;
					if (NeedAngle_x > NeedAngle.x) NeedAngle_x = NeedAngle.x;
					NeedAngle.x = NeedAngle_x;

				}
				if (Weapon[i]->Rotation.x > NeedAngle.x)
				{
					float NeedAngle_x = Weapon[i]->Rotation.x-40.0f*TargetingSpeed*TimeDelta;
					if (NeedAngle_x < NeedAngle.x) NeedAngle_x = NeedAngle.x;
					NeedAngle.x = NeedAngle_x;
				}

				// учитываем скорость поворота по горизонтали
				float Min = 0.0f;
				float Max = 0.0f;
				GetShipWeaponSlotAngle(Setup.Profile[CurrentProfile].Ship, i, &Min, &Max);
				if (Weapon[i]->Rotation.y < NeedAngle.y)
				{
					float NeedAngle_y = Weapon[i]->Rotation.y+40.0f*TargetingSpeed*TimeDelta;
					if (NeedAngle_y > NeedAngle.y) NeedAngle_y = NeedAngle.y;
					NeedAngle.y = NeedAngle_y;
					// проверка на достижение предела поворота
					if (NeedAngle.y > Max+Rotation.y) NeedAngle.y = Max+Rotation.y;
				}
				if (Weapon[i]->Rotation.y > NeedAngle.y)
				{
					float NeedAngle_y = Weapon[i]->Rotation.y-40.0f*TargetingSpeed*TimeDelta;
					if (NeedAngle_y < NeedAngle.y) NeedAngle_y = NeedAngle.y;
					NeedAngle.y = NeedAngle_y;
					// проверка на достижение предела поворота
					if (NeedAngle.y < Min+Rotation.y) NeedAngle.y = Min+Rotation.y;
				}


				// если выключен прикол с поворотом - моментально поворачиваем ствол
				if (GameWeaponTargetingMode == 1) NeedAngle = NeedAngleTmp;


				// если это не ракетные системы, нужно повернуть
				if (Weapon[i]->ObjectCreationType < 16)
				{
					Weapon[i]->SetRotation(Weapon[i]->Rotation^(-1));
					Weapon[i]->SetRotation(NeedAngle);
				}
			}
		}

		ID = tmpID;
	}






	// если корабль игрока
	if (ObjectStatus == 3)
	{
		// используем ID как маркер, чтобы не обрабатывать этот объект в процедуре
		int tmpID = ID;
		ID = 111111;

		// ставим скорость наведения оружия
		float TargetingSpeed = GameTargetingMechanicSystem*1.0f;

		// находим среднюю точку положение оружия
		VECTOR3D WeaponAvLocation(0.0f,0.0f,0.0f);
		int UsedWeaponQunt = 0;
		if (Weapon != 0)
		for (int i=0; i<WeaponQuantity; i++)
		if (Weapon[i] != 0)
		{
			WeaponAvLocation = WeaponAvLocation + WeaponLocation[i] + Weapon[i]->FireLocation + Location;
			UsedWeaponQunt ++;
		}
		WeaponAvLocation.x = WeaponAvLocation.x / UsedWeaponQunt;
		WeaponAvLocation.y = WeaponAvLocation.y / UsedWeaponQunt;
		WeaponAvLocation.z = WeaponAvLocation.z / UsedWeaponQunt;


		VECTOR3D NeedAngle = Rotation;



// у оружия есть (для каждого слота в корабле свои)
// мин-макс и базовый (выставляет пользователь) углы поворота орудия
// передавать на проверку всегда базовый угол!!! не текущий!

/* типы наведения
1 - простое наведение всех орудий по кораблю
2 - простое наведение всех орудий по кораблю + доворот на центр
3 - наведение каждого орудия на свою цель
4 - наведение каждого орудия на свою цель + доворот

*/

		// т.к. у нас включена девиация, нужно принять меры
		float RotationMat2[9];
		memcpy(RotationMat2, CurrentRotationMat, sizeof(float)*9);
		VECTOR3D Rotation2 = Rotation;

		if (DeviationOn)
		{
			Rotation2 = Rotation - (Deviation[0]^(CurentDeviation[0]*50.0f));

			Matrix33CreateRotate(RotationMat2, Rotation2);
		}



		// всему оружию ставим нужную ориентацию
		if (Weapon != 0)
		for (int i=0; i<WeaponQuantity; i++)
		{
			if (Weapon[i] != 0)
			if (Weapon[i]->NeedRotateOnTargeting)
			{
				NeedAngle = Rotation2;
				// добавляем базовый угол, чтобы по умолчанию устанавливало его
				NeedAngle.y += WeaponYAngle[i];

				switch (GameTargetingSystem)
				{
				 	case 1:
						GetShipOnTargetOrientateion(ObjectStatus, WeaponAvLocation, Rotation2,
							Length, RotationMat2, &NeedAngle, Width, false, true, Location + WeaponLocation[i] + Weapon[i]->FireLocation, Weapon[i]->ObjectCreationType);
						break;
				 	case 2:
						GetShipOnTargetOrientateion(ObjectStatus, WeaponAvLocation, Rotation2,
							Length, RotationMat2, &NeedAngle, Width, true, true, Location + WeaponLocation[i] + Weapon[i]->FireLocation, Weapon[i]->ObjectCreationType);
						break;
				 	case 3:
						GetShipOnTargetOrientateion(ObjectStatus, Location + WeaponLocation[i] + Weapon[i]->FireLocation, Weapon[i]->Rotation,
							Length,	Weapon[i]->CurrentRotationMat, &NeedAngle, Weapon[i]->Width, false, true, Location + WeaponLocation[i] + Weapon[i]->FireLocation, Weapon[i]->ObjectCreationType);
						break;
				 	case 4:
						GetShipOnTargetOrientateion(ObjectStatus, Location + WeaponLocation[i] + Weapon[i]->FireLocation, VECTOR3D(Weapon[i]->Rotation.x,0,Weapon[i]->Rotation.z)+VECTOR3D(0,WeaponYAngle[i],0),
							Length,	Weapon[i]->CurrentRotationMat, &NeedAngle, Width, false, true, Location + WeaponLocation[i] + Weapon[i]->FireLocation, Weapon[i]->ObjectCreationType);
						break;
				}


				VECTOR3D NeedAngleTmp = NeedAngle;

				// учитываем скорость поворота по вертикали
				if (Weapon[i]->Rotation.x < NeedAngle.x)
				{
					float NeedAngle_x = Weapon[i]->Rotation.x+40.0f*TargetingSpeed*TimeDelta;
					if (NeedAngle_x > NeedAngle.x) NeedAngle_x = NeedAngle.x;
					NeedAngle.x = NeedAngle_x;

				}
				if (Weapon[i]->Rotation.x > NeedAngle.x)
				{
					float NeedAngle_x = Weapon[i]->Rotation.x-40.0f*TargetingSpeed*TimeDelta;
					if (NeedAngle_x < NeedAngle.x) NeedAngle_x = NeedAngle.x;
					NeedAngle.x = NeedAngle_x;
				}

				// учитываем скорость поворота по горизонтали
				float Min = 0.0f;
				float Max = 0.0f;
				GetShipWeaponSlotAngle(Setup.Profile[CurrentProfile].Ship, i, &Min, &Max);
				if (Weapon[i]->Rotation.y > NeedAngle.y)
				{
					float NeedAngle_y = Weapon[i]->Rotation.y+40.0f*TargetingSpeed*TimeDelta;
					if (NeedAngle_y > NeedAngle.y) NeedAngle_y = NeedAngle.y;
					NeedAngle.y = NeedAngle_y;
					// проверка на достижение предела поворота
					if (NeedAngle.y > Max+Weapon[i]->Rotation.y) NeedAngle.y = Max+Weapon[i]->Rotation.y;
				}
				if (Weapon[i]->Rotation.y < NeedAngle.y)
				{
					float NeedAngle_y = Weapon[i]->Rotation.y-40.0f*TargetingSpeed*TimeDelta;
					if (NeedAngle_y < NeedAngle.y) NeedAngle_y = NeedAngle.y;
					NeedAngle.y = NeedAngle_y;
					// проверка на достижение предела поворота
					if (NeedAngle.y < Min+Weapon[i]->Rotation.y) NeedAngle.y = Min+Weapon[i]->Rotation.y;
				}


				// если выключен прикол с поворотом - моментально поворачиваем ствол
				if (GameWeaponTargetingMode == 1) NeedAngle = NeedAngleTmp;


				Weapon[i]->SetRotation(Weapon[i]->Rotation^(-1));
				Weapon[i]->SetRotation(NeedAngle);
			}
		}

		ID = tmpID;
	}




	// объект в порядке - удалять не нужно
	return true;
}






