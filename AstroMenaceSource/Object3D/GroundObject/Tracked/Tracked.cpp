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
#include "Tracked.h"



struct TrackedData
{
	float	Strength;
	int		WeaponQuantity;
	float	SpeedToRotate;
	const	char *Name;
	const	char *TextureName;
};

const int	PresetTrackedDataCount = 14;
TrackedData PresetTrackedData[PresetTrackedDataCount] =
{
	{250, 1,	60.0f,	"DATA/MODELS/TRACKED/tank-01.VW3D",	"DATA/MODELS/gr-01.VW2D"},
	{200, 2,	45.0f,	"DATA/MODELS/TRACKED/tank-03.VW3D",	"DATA/MODELS/gr-01.VW2D"},
	{300, 1,	45.0f,	"DATA/MODELS/TRACKED/tank-05.VW3D",	"DATA/MODELS/gr-06.VW2D"},
	{300, 1,	55.0f,	"DATA/MODELS/TRACKED/tank-06.VW3D",	"DATA/MODELS/gr-03.VW2D"},
	{400, 1,	60.0f,	"DATA/MODELS/TRACKED/tank-07.VW3D",	"DATA/MODELS/gr-06.VW2D"},
	{250, 1,	70.0f,	"DATA/MODELS/TRACKED/tank-08.VW3D",	"DATA/MODELS/gr-01.VW2D"},
	{400, 1,	60.0f,	"DATA/MODELS/TRACKED/tank-09.VW3D",	"DATA/MODELS/gr-01.VW2D"},
	{300, 1,	60.0f,	"DATA/MODELS/TRACKED/tank-10.VW3D",	"DATA/MODELS/gr-03.VW2D"},
	{350, 1,	60.0f,	"DATA/MODELS/TRACKED/tank-11.VW3D",	"DATA/MODELS/gr-03.VW2D"},
	{300, 1,	60.0f,	"DATA/MODELS/TRACKED/apc-01.VW3D",	"DATA/MODELS/gr-03.VW2D"},
	{400, 2,	60.0f,	"DATA/MODELS/TRACKED/apc-03.VW3D",	"DATA/MODELS/gr-03.VW2D"},
	{250, 4,	60.0f,	"DATA/MODELS/TRACKED/apc-aa-01.VW3D",	"DATA/MODELS/gr-03.VW2D"},
	{200, 2,	42.0f,	"DATA/MODELS/TRACKED/apc-aa-02.VW3D",	"DATA/MODELS/gr-02.VW2D"},
	{50,  1,	50.0f,	"DATA/MODELS/TRACKED/engineering-01.VW3D",	"DATA/MODELS/gr-03.VW2D"}
};



//-----------------------------------------------------------------------------
// Конструктор, инициализация всех переменных
//-----------------------------------------------------------------------------
void CTracked::Create(int TrackedNum)
{
	ObjectType = 5;
	MaxSpeed = 20.0f;
	MaxAcceler = 5.0f;
	MaxSpeedRotate = 20.0f;
	ObjectCreationType = TrackedNum;


	// ставим без оптимизации, иначе не увидим гусениц
	NeedCullFaces = false;

	LoadObjectData(PresetTrackedData[TrackedNum-1].Name, this, 0, 2.0f);

	for (int i=0; i<DrawObjectQuantity; i++)
	{
		Texture[i] = vw_FindTextureByName(PresetTrackedData[TrackedNum-1].TextureName);
	}
	ResistanceHull = 1.0f;
	ResistanceSystems = 1.0f;
	SpeedToRotate = PresetTrackedData[TrackedNum-1].SpeedToRotate;


	Strength = StrengthStart = PresetTrackedData[TrackedNum-1].Strength/GameNPCArmorPenalty;


	WeaponQuantity = PresetTrackedData[TrackedNum-1].WeaponQuantity;
	// начальные установки для оружия
	WeaponSetFire = new bool[WeaponQuantity];
	WeaponLocation = new VECTOR3D[WeaponQuantity];
	Weapon = new CWeapon*[WeaponQuantity];
	WeaponBound = new VECTOR3D[WeaponQuantity];
	for (int i=0; i<WeaponQuantity; i++)
	{
		WeaponSetFire[i] = false;
		Weapon[i] = 0;
	}


	// установка доп. текстуры и других настроек для каждой модели
	switch (TrackedNum)
	{
		case 1:
			WeaponLocation[0] = VECTOR3D(0.0f, 5.5f, 9.0f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(211);

			WheelQuantity = 16;
			WheelObjectsNum = new int[16];
			WheelObjectsNum[0] = 2;
			WheelObjectsNum[1] = 3;
			WheelObjectsNum[2] = 4;
			WheelObjectsNum[3] = 6;
			WheelObjectsNum[4] = 7;
			WheelObjectsNum[5] = 8;
			WheelObjectsNum[6] = 9;
			WheelObjectsNum[7] = 10;
			WheelObjectsNum[8] = 11;
			WheelObjectsNum[9] = 12;
			WheelObjectsNum[10] = 13;
			WheelObjectsNum[11] = 14;
			WheelObjectsNum[12] = 15;
			WheelObjectsNum[13] = 16;
			WheelObjectsNum[14] = 17;
			WheelObjectsNum[15] = 18;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 1;
			TargetHorizObject[1] = 5;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 5;
			TargetVertObjectMaxAngle = 50.0f;

			TrackObjectNum = 19;
			Texture[19] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;


		case 2:
			WeaponLocation[0] = VECTOR3D(0.1f, 6.1f, -0.4f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(204);
			WeaponLocation[1] = VECTOR3D(-0.1f, 6.1f, -0.4f);
			Weapon[1] = new CWeapon;
			Weapon[1]->Create(204);
			WeaponFireType = 2;

			WheelQuantity = 10;
			WheelObjectsNum = new int[10];
			WheelObjectsNum[0] = 1;
			WheelObjectsNum[1] = 2;
			WheelObjectsNum[2] = 3;
			WheelObjectsNum[3] = 4;
			WheelObjectsNum[4] = 5;
			WheelObjectsNum[5] = 6;
			WheelObjectsNum[6] = 7;
			WheelObjectsNum[7] = 8;
			WheelObjectsNum[8] = 9;
			WheelObjectsNum[9] = 10;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 11;
			TargetHorizObject[1] = 12;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 12;
			TargetVertObjectMaxAngle = 50.0f;

			TrackObjectNum = 13;
			Texture[13] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;


		case 3:
			WeaponLocation[0] = VECTOR3D(0.0f, 5.2f, 3.7f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(213);

			WheelQuantity = 14;
			WheelObjectsNum = new int[14];
			WheelObjectsNum[0] = 0;
			WheelObjectsNum[1] = 1;
			WheelObjectsNum[2] = 2;
			WheelObjectsNum[3] = 3;
			WheelObjectsNum[4] = 4;
			WheelObjectsNum[5] = 6;
			WheelObjectsNum[6] = 7;
			WheelObjectsNum[7] = 10;
			WheelObjectsNum[8] = 11;
			WheelObjectsNum[9] = 12;
			WheelObjectsNum[10] = 13;
			WheelObjectsNum[11] = 14;
			WheelObjectsNum[12] = 15;
			WheelObjectsNum[13] = 16;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 8;
			TargetHorizObject[1] = 9;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 9;
			TargetVertObjectMaxAngle = 50.0f;

			TrackObjectNum = 17;
			Texture[17] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 4:
			WeaponLocation[0] = VECTOR3D(0.0f, 5.3f, 6.5f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(208);

			WheelQuantity = 16;
			WheelObjectsNum = new int[16];
			WheelObjectsNum[0] = 2;
			WheelObjectsNum[1] = 3;
			WheelObjectsNum[2] = 4;
			WheelObjectsNum[3] = 5;
			WheelObjectsNum[4] = 6;
			WheelObjectsNum[5] = 7;
			WheelObjectsNum[6] = 8;
			WheelObjectsNum[7] = 9;
			WheelObjectsNum[8] = 10;
			WheelObjectsNum[9] = 11;
			WheelObjectsNum[10] = 12;
			WheelObjectsNum[11] = 13;
			WheelObjectsNum[12] = 14;
			WheelObjectsNum[13] = 15;
			WheelObjectsNum[14] = 16;
			WheelObjectsNum[15] = 17;

			TargetHorizObjectQuantity = 3;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 18;
			TargetHorizObject[1] = 19;
			TargetHorizObject[2] = 20;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 19;
			//TargetVertObject[1] = 20;
			TargetVertObjectMaxAngle = 50.0f;

			DrawObjectList[20].Location.z -= 1.0f;

			TrackObjectNum = 21;
			Texture[21] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 5:
			WeaponLocation[0] = VECTOR3D(0.0f, 5.8f, 4.5f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(208);

			WheelQuantity = 14;
			WheelObjectsNum = new int[14];
			WheelObjectsNum[0] = 1;
			WheelObjectsNum[1] = 2;
			WheelObjectsNum[2] = 3;
			WheelObjectsNum[3] = 4;
			WheelObjectsNum[4] = 5;
			WheelObjectsNum[5] = 6;
			WheelObjectsNum[6] = 7;
			WheelObjectsNum[7] = 10;
			WheelObjectsNum[8] = 11;
			WheelObjectsNum[9] = 12;
			WheelObjectsNum[10] = 13;
			WheelObjectsNum[11] = 14;
			WheelObjectsNum[12] = 15;
			WheelObjectsNum[13] = 16;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 9;
			TargetHorizObject[1] = 8;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 8;
			TargetVertObjectMaxAngle = 30.0f;

			TrackObjectNum = 17;
			Texture[17] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 6:
			WeaponLocation[0] = VECTOR3D(0.0f, 4.9f, 4.0f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(211);

			WheelQuantity = 16;
			WheelObjectsNum = new int[16];
			WheelObjectsNum[0] = 2;
			WheelObjectsNum[1] = 3;
			WheelObjectsNum[2] = 4;
			WheelObjectsNum[3] = 5;
			WheelObjectsNum[4] = 6;
			WheelObjectsNum[5] = 7;
			WheelObjectsNum[6] = 8;
			WheelObjectsNum[7] = 9;
			WheelObjectsNum[8] = 10;
			WheelObjectsNum[9] = 11;
			WheelObjectsNum[10] = 12;
			WheelObjectsNum[11] = 13;
			WheelObjectsNum[12] = 14;
			WheelObjectsNum[13] = 15;
			WheelObjectsNum[14] = 16;
			WheelObjectsNum[15] = 17;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 1;
			TargetHorizObject[1] = 18;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 18;
			TargetVertObjectMaxAngle = 50.0f;

			TrackObjectNum = 19;
			Texture[19] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 7:
			WeaponLocation[0] = VECTOR3D(0.0f, 7.6f, 5.5f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(212);

			WheelQuantity = 22;
			WheelObjectsNum = new int[22];
			WheelObjectsNum[0] = 1;
			WheelObjectsNum[1] = 2;
			WheelObjectsNum[2] = 3;
			WheelObjectsNum[3] = 4;
			WheelObjectsNum[4] = 5;
			WheelObjectsNum[5] = 6;
			WheelObjectsNum[6] = 7;
			WheelObjectsNum[7] = 8;
			WheelObjectsNum[8] = 9;
			WheelObjectsNum[9] = 10;
			WheelObjectsNum[10] = 11;
			WheelObjectsNum[11] = 12;
			WheelObjectsNum[12] = 13;
			WheelObjectsNum[13] = 14;
			WheelObjectsNum[14] = 15;
			WheelObjectsNum[15] = 16;
			WheelObjectsNum[16] = 19;
			WheelObjectsNum[17] = 20;
			WheelObjectsNum[18] = 21;
			WheelObjectsNum[19] = 22;
			WheelObjectsNum[20] = 23;
			WheelObjectsNum[21] = 24;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 18;
			TargetHorizObject[1] = 17;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 17;
			TargetVertObjectMaxAngle = 50.0f;

			TrackObjectNum = 25;
			Texture[25] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 8:
			WeaponLocation[0] = VECTOR3D(0.0f, 7.0f, 8.5f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(208);

			WheelQuantity = 16;
			WheelObjectsNum = new int[16];
			WheelObjectsNum[0] = 2;
			WheelObjectsNum[1] = 3;
			WheelObjectsNum[2] = 4;
			WheelObjectsNum[3] = 5;
			WheelObjectsNum[4] = 6;
			WheelObjectsNum[5] = 7;
			WheelObjectsNum[6] = 8;
			WheelObjectsNum[7] = 9;
			WheelObjectsNum[8] = 10;
			WheelObjectsNum[9] = 11;
			WheelObjectsNum[10] = 12;
			WheelObjectsNum[11] = 13;
			WheelObjectsNum[12] = 14;
			WheelObjectsNum[13] = 15;
			WheelObjectsNum[14] = 16;
			WheelObjectsNum[15] = 17;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 18;
			TargetHorizObject[1] = 19;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 19;
			TargetVertObjectMaxAngle = 50.0f;

			TrackObjectNum = 20;
			Texture[20] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 9:
			WeaponLocation[0] = VECTOR3D(0.0f, 6.7f, 6.8f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(211);
			Weapon[0]->NextFireTime = Weapon[0]->NextFireTime / 2.0f;

			WheelQuantity = 16;
			WheelObjectsNum = new int[16];
			WheelObjectsNum[0] = 1;
			WheelObjectsNum[1] = 2;
			WheelObjectsNum[2] = 3;
			WheelObjectsNum[3] = 4;
			WheelObjectsNum[4] = 5;
			WheelObjectsNum[5] = 6;
			WheelObjectsNum[6] = 7;
			WheelObjectsNum[7] = 8;
			WheelObjectsNum[8] = 9;
			WheelObjectsNum[9] = 10;
			WheelObjectsNum[10] = 11;
			WheelObjectsNum[11] = 12;
			WheelObjectsNum[12] = 13;
			WheelObjectsNum[13] = 14;
			WheelObjectsNum[14] = 15;
			WheelObjectsNum[15] = 16;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 18;
			TargetHorizObject[1] = 0;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 0;
			TargetVertObjectMaxAngle = 50.0f;

			TrackObjectNum = 19;
			Texture[19] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 10:
			WeaponLocation[0] = VECTOR3D(0.0f, 6.1f, 0.5f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(204);
			Weapon[0]->NextFireTime = Weapon[0]->NextFireTime / 2.0f;

			WheelQuantity = 16;
			WheelObjectsNum = new int[16];
			WheelObjectsNum[0] = 1;
			WheelObjectsNum[1] = 2;
			WheelObjectsNum[2] = 3;
			WheelObjectsNum[3] = 4;
			WheelObjectsNum[4] = 5;
			WheelObjectsNum[5] = 6;
			WheelObjectsNum[6] = 7;
			WheelObjectsNum[7] = 8;
			WheelObjectsNum[8] = 9;
			WheelObjectsNum[9] = 10;
			WheelObjectsNum[10] = 11;
			WheelObjectsNum[11] = 12;
			WheelObjectsNum[12] = 13;
			WheelObjectsNum[13] = 14;
			WheelObjectsNum[14] = 15;
			WheelObjectsNum[15] = 16;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 18;
			TargetHorizObject[1] = 0;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 0;
			TargetVertObjectMaxAngle = 50.0f;

			TrackObjectNum = 19;
			Texture[19] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 11:
			WeaponLocation[0] = VECTOR3D(2.2f, 5.4f, 7.0f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(209);
			WeaponLocation[1] = VECTOR3D(-2.2f, 5.4f, 7.0f);
			Weapon[1] = new CWeapon;
			Weapon[1]->Create(209);
			WeaponFireType = 3;

			WheelQuantity = 16;
			WheelObjectsNum = new int[16];
			WheelObjectsNum[0] = 1;
			WheelObjectsNum[1] = 2;
			WheelObjectsNum[2] = 3;
			WheelObjectsNum[3] = 4;
			WheelObjectsNum[4] = 5;
			WheelObjectsNum[5] = 6;
			WheelObjectsNum[6] = 7;
			WheelObjectsNum[7] = 8;
			WheelObjectsNum[8] = 9;
			WheelObjectsNum[9] = 10;
			WheelObjectsNum[10] = 11;
			WheelObjectsNum[11] = 12;
			WheelObjectsNum[12] = 13;
			WheelObjectsNum[13] = 14;
			WheelObjectsNum[14] = 15;
			WheelObjectsNum[15] = 16;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 0;
			TargetVertObjectMaxAngle = 55.0f;

			TrackObjectNum = 18;
			Texture[18] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 12:
			WeaponLocation[0] = VECTOR3D(0.55f, 5.0f, 2.0f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(206);
			Weapon[0]->NextFireTime = Weapon[0]->NextFireTime / 2.0f;
			WeaponLocation[1] = VECTOR3D(-0.55f, 5.0f, 2.0f);
			Weapon[1] = new CWeapon;
			Weapon[1]->Create(206);
			Weapon[1]->NextFireTime = Weapon[1]->NextFireTime / 2.0f;
			WeaponLocation[2] = VECTOR3D(1.65f, 5.0f, 2.0f);
			Weapon[2] = new CWeapon;
			Weapon[2]->Create(206);
			Weapon[2]->NextFireTime = Weapon[2]->NextFireTime / 2.0f;
			WeaponLocation[3] = VECTOR3D(-1.65f, 5.0f, 2.0f);
			Weapon[3] = new CWeapon;
			Weapon[3]->Create(206);
			Weapon[3]->NextFireTime = Weapon[3]->NextFireTime / 2.0f;
			WeaponFireType = 3;

			WheelQuantity = 16;
			WheelObjectsNum = new int[16];
			WheelObjectsNum[0] = 1;
			WheelObjectsNum[1] = 2;
			WheelObjectsNum[2] = 3;
			WheelObjectsNum[3] = 4;
			WheelObjectsNum[4] = 5;
			WheelObjectsNum[5] = 6;
			WheelObjectsNum[6] = 7;
			WheelObjectsNum[7] = 8;
			WheelObjectsNum[8] = 9;
			WheelObjectsNum[9] = 10;
			WheelObjectsNum[10] = 11;
			WheelObjectsNum[11] = 12;
			WheelObjectsNum[12] = 13;
			WheelObjectsNum[13] = 14;
			WheelObjectsNum[14] = 15;
			WheelObjectsNum[15] = 16;


			TargetVertObjectQuantity = 2;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 18;
			TargetVertObject[1] = 0;
			TargetVertObjectMaxAngle = 40.0f;

			TrackObjectNum = 19;
			Texture[19] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 13:
			WeaponLocation[0] = VECTOR3D(1.4f, 5.0f, 0.4f);
			Weapon[0] = new CWeapon;
			Weapon[0]->Create(206);
			Weapon[0]->NextFireTime = Weapon[0]->NextFireTime / 2.0f;
			WeaponLocation[1] = VECTOR3D(-1.4f, 5.0f, 0.4f);
			Weapon[1] = new CWeapon;
			Weapon[1]->Create(206);
			Weapon[1]->NextFireTime = Weapon[1]->NextFireTime / 2.0f;
			WeaponFireType = 3;

			WheelQuantity = 14;
			WheelObjectsNum = new int[14];
			WheelObjectsNum[0] = 2;
			WheelObjectsNum[1] = 3;
			WheelObjectsNum[2] = 4;
			WheelObjectsNum[3] = 5;
			WheelObjectsNum[4] = 6;
			WheelObjectsNum[5] = 7;
			WheelObjectsNum[6] = 8;
			WheelObjectsNum[7] = 9;
			WheelObjectsNum[8] = 10;
			WheelObjectsNum[9] = 11;
			WheelObjectsNum[10] = 12;
			WheelObjectsNum[11] = 13;
			WheelObjectsNum[12] = 14;
			WheelObjectsNum[13] = 15;

			TargetHorizObjectQuantity = 2;
			TargetHorizObject = new int[TargetHorizObjectQuantity];
			TargetHorizObject[0] = 0;
			TargetHorizObject[1] = 16;

			TargetVertObjectQuantity = 1;
			TargetVertObject = new int[TargetVertObjectQuantity];
			TargetVertObject[0] = 16;
			TargetVertObjectMaxAngle = 50.0f;

			TrackObjectNum = 17;
			Texture[17] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			break;

		case 14:
			WeaponLocation[0] = VECTOR3D(0.0f, 0.0f, 0.0f);

			WheelQuantity = 8;
			WheelObjectsNum = new int[8];
			WheelObjectsNum[0] = 0;
			WheelObjectsNum[1] = 2;
			WheelObjectsNum[2] = 3;
			WheelObjectsNum[3] = 4;
			WheelObjectsNum[4] = 5;
			WheelObjectsNum[5] = 6;
			WheelObjectsNum[6] = 7;
			WheelObjectsNum[7] = 8;

			TrackObjectNum = 10;
			Texture[10] = vw_FindTextureByName("DATA/MODELS/track.VW2D");
			TrackRotationDirection = -1;
			break;

	}


	// находим все данные по геометрии
	::CObject3D::InitByDrawObjectList();


	// установка остальных параметров девиации
	DeviationOn = false;
	DeviationObjQuantity = WheelQuantity;
	Deviation = new VECTOR3D[DeviationObjQuantity];
	NeedDeviation = new float[DeviationObjQuantity];
	CurentDeviation = new float[DeviationObjQuantity];
	CurentDeviationSum = new float[DeviationObjQuantity];
	DeviationObjNum = new int[DeviationObjQuantity];

	for (int i=0; i<DeviationObjQuantity; i++)
	{
		Deviation[i] = VECTOR3D(0.0f, 1.0f, 0.0f);
		NeedDeviation[i] = vw_Randf0*0.1f;
		CurentDeviation[i] = CurentDeviationSum[i] = 0.0f;
		DeviationObjNum[i] = WheelObjectsNum[i];
	}

	// делаем сдвиг поворота колес, чтобы смотрелось естественнее
	for (int i=0; i<WheelQuantity; i++)
		DrawObjectList[WheelObjectsNum[i]].Rotation.x = vw_fRandNum(360.0f);



	// вычисляем данные для нахождения точки стрельбы
	if (TargetHorizObject != 0)
	{
		BaseBound = DrawObjectList[TargetHorizObject[0]].Location;
	}

	if (TargetVertObject != 0)
	{
		if (TargetHorizObject != 0)
		{
			MiddleBound = DrawObjectList[TargetVertObject[0]].Location - DrawObjectList[TargetHorizObject[0]].Location;
		}
		else
		{
			MiddleBound = DrawObjectList[TargetVertObject[0]].Location;
		}
	}

	if (WeaponBound != 0)
	for (int i=0; i<WeaponQuantity; i++)
	{
		if (TargetVertObject != 0)
		{
			WeaponBound[i] = WeaponLocation[i] - DrawObjectList[TargetVertObject[0]].Location;
		}
		else
		if (TargetHorizObject != 0)
		{
			WeaponBound[i] = WeaponLocation[i] - DrawObjectList[TargetHorizObject[0]].Location;
		}
		else
		{
			WeaponBound[i] = WeaponLocation[i];
		}
	}

}

