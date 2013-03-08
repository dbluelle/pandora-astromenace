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


/// подключаем нужные файлы
#include "Weapon.h"



// название типа оружия землян
const char *GetWeaponGroupTitle(int Num)
{
	switch (Num)
	{
		case 1:
		case 2:
		case 3:
		case 4:
			return "4_Kinetic";
		case 5:
		case 6:
		case 7:
			return "4_Ion";
		case 8:
		case 9:
		case 10:
			return "4_Plasma";
		case 11:
		case 12:
			return "4_Maser";
		case 13:	return "4_Antimatter";
		case 14:	return "4_Laser";
		case 15:	return "4_Gauss";

		case 16:
		case 17:
		case 18:
		case 19:
			return "4_Propelled";

		default:
			fprintf(stderr, "Error in GetWeaponGroupTitle function call, wrong Num.\n");
			break;
	}
	return 0;
}








struct WeaponData
{
	int		SoundNum;
	bool	NeedRotateOnTargeting;
	float	Strength;
	int		WeaponLevel;
	float	EnergyUse;
	int		Ammo;
	float	NextFireTime;
	int		ObjectNum;
	VECTOR3D	FireLocation;
	VECTOR3D	DestrFireLocation;
	const char	*NameVW3D;
	const char	*TextureName;
	const char	*TextureIllumName;
};


// оружие землян 1-99
const int	PresetEarthWeaponDataCount = 19;
WeaponData PresetEarthWeaponData[PresetEarthWeaponDataCount] =
{
	// Kinetic
	{9,  true, 25,	1,	1.5f,	3000,	0.4f, 4, VECTOR3D(0.0f, -0.613f, 2.0f), VECTOR3D(0.0f, -0.65f, 1.0f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text00.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum01.VW2D"},
	{10, true, 25,	1,	3,		1500,	0.6f, 10, VECTOR3D(0.0f, -0.613f, 2.93f), VECTOR3D(0.0f, -0.6f, 1.8f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text00.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum01.VW2D"},
	{11, true, 30,	2,	3.5,	1000,	0.7f, 12, VECTOR3D(0.0f, -0.613f, 3.33f), VECTOR3D(0.0f, -0.6f, 2.2f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text00.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum01.VW2D"},
	{12, true, 30,	2,	5,		7000,	0.3f, 7, VECTOR3D(0.0f, -0.613f, 2.33f), VECTOR3D(0.0f, -0.6f, 1.2f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text00.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum01.VW2D"},
	// Ion
	{13, true, 10,	1,	7,		1000,	0.7f, 0, VECTOR3D(0.0f, -0.43f, 2.13f), VECTOR3D(0.0f, -0.45f, 1.5f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text04.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum02.VW2D"},
	{14, true, 10,	1,	10,		2000,	0.9f, 3, VECTOR3D(0.0f, -0.53f, 1.86f), VECTOR3D(0.0f, -0.5f, 1.8f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text04.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum02.VW2D"},
	{15, true, 15,	2,	11.5,	3000,	1.0f, 5, VECTOR3D(0.0f, -0.63f, 2.26f), VECTOR3D(0.0f, -0.65f, 2.3f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text04.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum02.VW2D"},
	// Plasma
	{16, true, 10,	2,	20,		2000,	0.6f, 2, VECTOR3D(0.0f, -0.613f, 2.0f), VECTOR3D(0.0f, -0.65f, 1.8f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text06.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum03.VW2D"},
	{17, true, 15,	2,	30,		1000,	0.7f, 1, VECTOR3D(0.0f, -0.8f, 1.86f), VECTOR3D(0.0f, -0.8f, 1.8f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text06.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum03.VW2D"},
	{18, true, 10,	3,	50,		800,	0.9f, 6, VECTOR3D(0.0f, -0.613f, 1.2f), VECTOR3D(0.0f, -0.7f, 1.6f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text06.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum03.VW2D"},
	// Maser
	{19, true, 10,	3,	50,		800,	3.0f, 9, VECTOR3D(0.0f, -0.55f, 2.1f), VECTOR3D(0.0f, -0.55f, 1.4f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text07.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum03.VW2D"},
	{20, true, 15,	4,	80,		1000,	2.4f, 8, VECTOR3D(0.0f, -0.55f, 2.5f), VECTOR3D(0.0f, -0.55f, 1.8f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text07.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum03.VW2D"},
	// Antimatter
	{21, true, 20,	4,	50,		5000,	0.8f, 11, VECTOR3D(0.0f, -0.65f, 2.1f), VECTOR3D(0.0f, -0.65f, 1.9f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text09.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum02.VW2D"},
	// Laser
	{22, true, 15,	5,	150,	800,	1.2f, 13, VECTOR3D(0.0f, -0.6f, 2.5f), VECTOR3D(0.0f, -0.6f, 2.1f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text05.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum03.VW2D"},
	// Gauss
	{23, true, 20,	5,	150,	2000,	0.7f, 14, VECTOR3D(0.0f, -0.65f, 3.6f), VECTOR3D(0.0f, -0.55f, 2.2f), "DATA/MODELS/EARTHFIGHTER/weapons.VW3D", "DATA/MODELS/EARTHFIGHTER/sf-text08.VW2D", "DATA/MODELS/EARTHFIGHTER/sf-illum03.VW2D"},
	// Missiles
	{24, false, 30,	4,	5,		200,	3.0f, 0, VECTOR3D(0.0f, -0.8f, 4.7f), VECTOR3D(0.0f, -0.9f, 1.5f), "DATA/MODELS/EARTHFIGHTER/lnch1.VW3D", "DATA/MODELS/EARTHFIGHTER/lnch12.tga", ""},
	{25, false, 30,	4,	15,		400,	8.0f, 0, VECTOR3D(0.2f, -0.95f, 2.6f), VECTOR3D(0.0f, -0.6f, 1.0f), "DATA/MODELS/EARTHFIGHTER/lnch2.VW3D", "DATA/MODELS/EARTHFIGHTER/lnch12.tga", ""},
	{26, false, 25,	5,	10,		50,		8.0f, 0, VECTOR3D(0.0f, -0.95f, 4.0f), VECTOR3D(0.0f, -0.9f, 1.5f), "DATA/MODELS/EARTHFIGHTER/lnch3.VW3D", "DATA/MODELS/EARTHFIGHTER/lnch34.tga", ""},
	{27, false, 30,	5,	15,		25,		10.0f, 0, VECTOR3D(0.0f, -0.95f, 5.0f), VECTOR3D(0.0f, -0.9f, 1.8f), "DATA/MODELS/EARTHFIGHTER/lnch4.VW3D", "DATA/MODELS/EARTHFIGHTER/lnch34.tga", ""},
};




// оружие пришельцев 101-199
const int	PresetAlienWeaponDataCount = 10;
WeaponData PresetAlienWeaponData[PresetAlienWeaponDataCount] =
{
	// оружие пришельцев (как Kinetic1)
	{14, true, 1.0f,	1,	1,	5000,	0.7f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// оружие пришельцев (с наведением, как Kinetic2)
	{16, false, 1.0f,	1,	1,	2500,	3.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// оружие пришельцев (как Kinetic3)
	{17, true, 1.0f,	1,	1,	2500,	3.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// оружие пришельцев (с наведением, как Kinetic3)
	{17, false, 1.0f,	1,	1,	2500,	2.5f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// оружие пришельцев (как Kinetic2)
	{16, true, 1.0f,	1,	1,	2500,	3.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// оружие пришельцев для выброса мин (1 типа)
	{21, false, 1.0f,	1,	1,	50,		5.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// оружие пришельцев для выброса мин (2 типа)
	{21, false, 1.0f,	1,	1,	50,		5.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// оружие пришельцев (как Plasma3)
	{18, true, 10,	3,	50,		800,	0.9f, 6, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// оружие пришельцев (как Plasma2)
	{17, true, 15,	2,	25,		1000,	0.8f, 1, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// оружие пришельцев (как Laser) для больших кораблей
	{22, true, 15,	5,	150,	800,	1.2f, 13, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},



};





// оружие пиратов 201-299
const int	PresetPirateWeaponDataCount = 17;
WeaponData PresetPirateWeaponData[PresetPirateWeaponDataCount] =
{
	// турель для кораблей пиратов
	{9, false, 10,		1,	1,	3000,	0.7f, 4, VECTOR3D(0.0f, 1.5f, 1.0f), VECTOR3D(0.0f, 1.5f, 1.0f), "DATA/MODELS/TURRET/turret-01.VW3D", "DATA/MODELS/TURRET/turrets.tga", ""},
	// турель для кораблей пиратов
	{10, false, 10,		1,	1,	3000,	0.7f, 4, VECTOR3D(0.0f, 1.0f, 0.0f), VECTOR3D(0.0f, 1.0f, 0.0f), "DATA/MODELS/TURRET/turret-02.VW3D", "DATA/MODELS/TURRET/turrets.tga", ""},

	// оружие пиратов - отстрел фларес для больших кораблей
	{9, false, 1.0f,	1,	1,	2500,	4.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},

	// как Kinetic1
	{9, true, 10,		1,	1.7f,	3000,	0.7f, 4, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// как Missile1
	{24, false, 80,	4,	5,		200,	5.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// как Missile2
	{25, false, 30,	4,	5,		800,	8.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// как Ion2
	{14, true, 10,	1,	10,		2000,	0.9f, 3, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// как Antimatter
	{21, true, 20,	4,	50,		5000,	0.8f, 11, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// как Missile3 (торпеда)
	{26, false, 25,	5,	10,		200,	8.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// как Missile4 (бомба)
	{27, false, 30,	5,	15,		100,	10.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// как Kinetic2
	{10, true, 25,	1,	3,		1500,	0.6f, 10, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// как Kinetic3
	{11, true, 30,	2,	3.5,	500,	0.7f, 12, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// как Plasma2
	{17, true, 15,	2,	25,		1000,	0.8f, 1, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},

	// мина1 (простое наведение по высоте)
	{26, false, 1.0f,	1,	1,	2500,	4.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// мина2 (наведение по высоте + приближение)
	{26, false, 1.0f,	1,	1,	2500,	4.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// мина3 (наведение по высоте + стрельба снарядами)
	{27, false, 1.0f,	1,	1,	2500,	4.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},
	// мина4 (наведение по высоте + стрельба ракетами)
	{27, false, 1.0f,	1,	1,	2500,	4.0f, 0, VECTOR3D(0.0f, 0.0f, 0.0f), VECTOR3D(0.0f, 0.0f, 0.0f), "none", "none", "none"},


};

























//-----------------------------------------------------------------------------
// Конструктор, инициализация всех переменных
//-----------------------------------------------------------------------------
CWeapon::CWeapon(void)
{
	// друг
	ObjectStatus = 2;

	ObjectType = 9;

	// никогда не показываем линию
	ShowStrength = false;

	// уровень оружия, ставим самый слабый
	WeaponLevel = 1;
	// вес
	Weight = 500;
	// боекомплект
	Ammo = AmmoStart = 100;
	// задержка при стрельбе
	NextFireTime = 0.3f;
	// время последнего выстрела, ставим -10 секунд, чтобы сразу стрелять
	LastFireTime = -10.0f;

	EnergyUse = 1.0f;

	NeedRotateOnTargeting = true;

	LaserMaser = 0;
	LaserMaserSoundNum = 0;

	SwampNum = 0;

	SoundNum = 0;
	Fire = 0;
	FireLocation = VECTOR3D(0.0f, 0.0f, 0.0f);
	DestroyedFire = 0;
	DestroyedSmoke = 0;
	DestroyedFireLocation = VECTOR3D(0.0f, 0.0f, 0.0f);

	WeaponTurret = false;
	TargetHorizObject = -1;
	TargetHorizObjectCurrentAngle = 0.0f;
	TargetHorizObjectNeedAngle = 0.0f;
	TargetVertObject = -1;
	TargetVertObjectMaxAngle = 80.0f;
	TargetVertObjectMinAngle = 0.0f;
	TargetVertObjectCurrentAngle = 0.0f;
	TargetVertObjectNeedAngle = 0.0f;


	Next = Prev = 0;
	AttachWeapon(this);
}



//-----------------------------------------------------------------------------
// Конструктор, инициализация всех переменных
//-----------------------------------------------------------------------------
void CWeapon::Create(int WeaponNum)
{
	ObjectCreationType = WeaponNum;




	// 1-99 - это оружие землян
	if (WeaponNum >= 1 && WeaponNum <= 99)
	{
		// союзник
		ObjectStatus = 2;

		Strength = StrengthStart = PresetEarthWeaponData[WeaponNum-1].Strength;
		WeaponLevel = PresetEarthWeaponData[WeaponNum-1].WeaponLevel;
		Ammo = AmmoStart =  PresetEarthWeaponData[WeaponNum-1].Ammo;
		NextFireTime =  PresetEarthWeaponData[WeaponNum-1].NextFireTime;
		SoundNum = PresetEarthWeaponData[WeaponNum-1].SoundNum;
		NeedRotateOnTargeting = PresetEarthWeaponData[WeaponNum-1].NeedRotateOnTargeting;

		CurrentEnergyAccumulated = EnergyUse = PresetEarthWeaponData[WeaponNum-1].EnergyUse;
		FireLocation = PresetEarthWeaponData[WeaponNum-1].FireLocation;

		DestroyedFireLocation = PresetEarthWeaponData[WeaponNum-1].DestrFireLocation;
		Fire = new eParticleSystem;
		Fire->SetStartLocation(FireLocation);
		Fire->Direction = VECTOR3D(0.0f, 0.0f, 1.0f);
		SetWeaponFire(Fire, WeaponNum);

		LoadObjectData(PresetEarthWeaponData[WeaponNum-1].NameVW3D, this, PresetEarthWeaponData[WeaponNum-1].ObjectNum+1, 2.0f);

		for (int i=0; i<DrawObjectQuantity; i++)
		{
			Texture[i] = vw_FindTextureByName(PresetEarthWeaponData[WeaponNum-1].TextureName);
			if (WeaponNum < 16)
				TextureIllum[i] = vw_FindTextureByName(PresetEarthWeaponData[WeaponNum-1].TextureIllumName);
		}

		// находим все данные по геометрии
		::CObject3D::InitByDrawObjectList();

	}
	// 101-199 - это оружие пришельцев
	else
	if (WeaponNum >= 101 && WeaponNum <= 199)
	{
		// внутренний номер
		int IntWeaponNum = WeaponNum - 100;

		// враг
		ObjectStatus = 1;

		Strength = StrengthStart = PresetAlienWeaponData[IntWeaponNum-1].Strength;
		WeaponLevel = PresetAlienWeaponData[IntWeaponNum-1].WeaponLevel;
		Ammo = AmmoStart =  PresetAlienWeaponData[IntWeaponNum-1].Ammo;
		NextFireTime =  PresetAlienWeaponData[IntWeaponNum-1].NextFireTime;
		SoundNum = PresetAlienWeaponData[IntWeaponNum-1].SoundNum;
		NeedRotateOnTargeting = PresetAlienWeaponData[IntWeaponNum-1].NeedRotateOnTargeting;

		CurrentEnergyAccumulated = EnergyUse = PresetAlienWeaponData[IntWeaponNum-1].EnergyUse;
		FireLocation = PresetAlienWeaponData[IntWeaponNum-1].FireLocation;

	}
	// 201-299 - это оружие пиратов
	else
	if (WeaponNum >= 201 && WeaponNum <= 299)
	{
		// внутренний номер
		int IntWeaponNum = WeaponNum - 200;

		// враг
		ObjectStatus = 1;

		Strength = StrengthStart = PresetPirateWeaponData[IntWeaponNum-1].Strength;
		WeaponLevel = PresetPirateWeaponData[IntWeaponNum-1].WeaponLevel;
		Ammo = AmmoStart =  PresetPirateWeaponData[IntWeaponNum-1].Ammo;
		NextFireTime =  PresetPirateWeaponData[IntWeaponNum-1].NextFireTime;
		SoundNum = PresetPirateWeaponData[IntWeaponNum-1].SoundNum;
		NeedRotateOnTargeting = PresetPirateWeaponData[IntWeaponNum-1].NeedRotateOnTargeting;

		CurrentEnergyAccumulated = EnergyUse = PresetPirateWeaponData[IntWeaponNum-1].EnergyUse;
		FireLocation = PresetPirateWeaponData[IntWeaponNum-1].FireLocation;

		// турели пиратов
		switch (WeaponNum)
		{
			case 201:
				{
					WeaponTurret = true;
					TargetHorizObject = 0;
					TargetVertObject = 1;
					TargetVertObjectMaxAngle = 89.0f;
					TargetVertObjectMinAngle = 0.0f;

					LoadObjectData(PresetPirateWeaponData[IntWeaponNum-1].NameVW3D, this, 0, 2.0f);
					for (int i=0; i<DrawObjectQuantity; i++)
					{
						Texture[i] = vw_FindTextureByName(PresetPirateWeaponData[IntWeaponNum-1].TextureName);
						TextureIllum[i] = 0;
					}

					// находим все данные по геометрии
					::CObject3D::InitByDrawObjectList();
				}
				break;


			case 202:
				{
					WeaponTurret = true;
					TargetHorizObject = 0;
					TargetVertObject = 1;
					TargetVertObjectMaxAngle = 89.0f;
					TargetVertObjectMinAngle = 20.0f;

					LoadObjectData(PresetPirateWeaponData[IntWeaponNum-1].NameVW3D, this, 0, 2.0f);
					for (int i=0; i<DrawObjectQuantity; i++)
					{
						Texture[i] = vw_FindTextureByName(PresetPirateWeaponData[IntWeaponNum-1].TextureName);
						TextureIllum[i] = 0;
					}

					// находим все данные по геометрии
					::CObject3D::InitByDrawObjectList();
				}
				break;
		}

		if (WeaponNum == 201 || WeaponNum == 202)
		{
			// вычисляем данные для нахождения точки стрельбы
			if (TargetHorizObject != -1)
			{
				BaseBound = DrawObjectList[TargetHorizObject].Location;
			}

			if (TargetVertObject != -1)
			{
				if (TargetHorizObject != -1)
				{
					MiddleBound = DrawObjectList[TargetVertObject].Location - DrawObjectList[TargetHorizObject].Location;
				}
				else
				{
					MiddleBound = DrawObjectList[TargetVertObject].Location;
				}
			}


			if (TargetVertObject != -1)
			{
				WeaponBound = FireLocation - DrawObjectList[TargetVertObject].Location;
			}
			else
			if (TargetHorizObject != -1)
			{
				WeaponBound = FireLocation - DrawObjectList[TargetHorizObject].Location;
			}
			else
			{
				WeaponBound = FireLocation;
			}

		}



	}


}










//-----------------------------------------------------------------------------
// Деструктор
//-----------------------------------------------------------------------------
CWeapon::~CWeapon(void)
{
	if (Fire != 0)
	{
		Fire->IsSuppressed = true;
		Fire->DestroyIfNoParticles = true;
		Fire = 0;
	}
	if (DestroyedFire != 0)
	{
		DestroyedFire->IsSuppressed = true;
		DestroyedFire->DestroyIfNoParticles = true;
		DestroyedFire = 0;
	}
	if (DestroyedSmoke != 0)
	{
		DestroyedSmoke->IsSuppressed = true;
		DestroyedSmoke->DestroyIfNoParticles = true;
		DestroyedSmoke = 0;
	}
	// если лучевое оружие
	if (LaserMaser != 0)
	{
		delete LaserMaser; LaserMaser = 0;
		// убираем звук выстрела
		if (vw_FindSoundByNum(LaserMaserSoundNum) != 0)
			vw_FindSoundByNum(LaserMaserSoundNum)->Stop(0.15f);
	}

	DetachWeapon(this);
}









//-----------------------------------------------------------------------------
// выполнение действий
//-----------------------------------------------------------------------------
bool CWeapon::Update(float Time)
{

	// если лучевое оружие
	if (LaserMaser != 0)
	{
		if (LaserMaser->Lifetime <= 0.0f)
		{
			delete LaserMaser; LaserMaser = 0;
		}
	}


	// вызываем родительскую функцию
	// если там передали удалить - выходим
	if (!::CObject3D::Update(Time))
	{
		return false;
	}



	// если запущено - выключаем прорисовку эффекта выстрела (вспышка возле ствола)
	if (Fire != 0)
	if (!Fire->IsSuppressed)
	if (LastFireTime + TimeDelta <= Time)
	{
		Fire->IsSuppressed = true;
	}





	// для землян, создание эффекта повреждения оружия
	// если оружие только повредили...
	if (ObjectCreationType >= 1 && ObjectCreationType <= 99)
	if (Strength < StrengthStart)
	if (DestroyedFire == 0)
	{
		// горение
		DestroyedFire = new eParticleSystem;
		DestroyedFire->ColorStart.r = 1.00f;
		DestroyedFire->ColorStart.g = 0.70f;
		DestroyedFire->ColorStart.b = 0.30f;
		DestroyedFire->ColorEnd.r = 1.00f;
		DestroyedFire->ColorEnd.g = 0.00f;
		DestroyedFire->ColorEnd.b = 0.00f;
		DestroyedFire->AlphaStart = 1.00f;
		DestroyedFire->AlphaEnd   = 0.10f;
		DestroyedFire->SizeStart  = 0.20f;
		DestroyedFire->SizeVar    = 0.10f;
		DestroyedFire->SizeEnd    = 0.10f;
		DestroyedFire->Speed      = 8.00f;
		DestroyedFire->SpeedVar   = 2.00f;
		DestroyedFire->Theta      = 5.00f;
		DestroyedFire->Life       = 0.50f*Length/3.0f;
		DestroyedFire->ParticlesPerSec = 70;
		DestroyedFire->Texture[0] = vw_FindTextureByName("DATA/GFX/flare1.tga");
		DestroyedFire->CreationType = 1;
		DestroyedFire->CreationSize = VECTOR3D(Width/2.0f,Width/2.0f,0.1f);
		DestroyedFire->Direction = VECTOR3D(0.0f, 0.0f, -1.0f);
		DestroyedFire->SetStartLocation(DestroyedFireLocation);

		// небольшая поправка для ракетных систем

		if (ObjectCreationType == 16 || ObjectCreationType == 17)
		{
			DestroyedFire->DeadZone = Width/2.0f - 0.1f;
		}
		if (ObjectCreationType == 18)
		{
			DestroyedFire->CreationSize = VECTOR3D(Width/3.5f,Width/3.5f,0.1f);
			DestroyedFire->DeadZone = Width/3.5f - 0.1f;
		}
		if (ObjectCreationType == 19)
		{
			DestroyedFire->CreationSize = VECTOR3D(Width/3.0f,Width/3.0f,0.1f);
			DestroyedFire->DeadZone = Width/3.0f - 0.1f;
		}
	}


	// для землян, создание эффекта уничтоженного оружия
	// проверяем тут был ли выход из строя
	if (ObjectCreationType >= 1 && ObjectCreationType <= 99)
	if (Strength <= 0.0f)
	if (DestroyedSmoke == 0)
	{
		// дым
		DestroyedSmoke = new eParticleSystem;
		DestroyedSmoke->ColorStart.r = 1.00f;
		DestroyedSmoke->ColorStart.g = 1.00f;
		DestroyedSmoke->ColorStart.b = 1.00f;
		DestroyedSmoke->ColorEnd.r = 1.00f;
		DestroyedSmoke->ColorEnd.g = 1.00f;
		DestroyedSmoke->ColorEnd.b = 1.00f;
		DestroyedSmoke->AlphaStart = 0.20f;
		DestroyedSmoke->AlphaEnd   = 0.00f;
		DestroyedSmoke->SizeStart  = 0.25f;
		DestroyedSmoke->SizeVar    = 0.10f;
		DestroyedSmoke->SizeEnd    = 0.00f;
		DestroyedSmoke->Speed      = 0.00f;
		DestroyedSmoke->SpeedVar   = 0.00f;
		DestroyedSmoke->Theta      = 35.00f;
		DestroyedSmoke->Life       = 2.00f*Length/3.0f;
		DestroyedSmoke->ParticlesPerSec = 300;
		DestroyedSmoke->Texture[0] = vw_FindTextureByName("DATA/GFX/flare1.tga");
		DestroyedSmoke->CreationType = 0;
		DestroyedSmoke->CreationSize = VECTOR3D(Width/2.5f,Width/2.5f,0.1f);
		DestroyedSmoke->Direction = VECTOR3D(0.0f, 0.0f, -1.0f);
		DestroyedSmoke->SetStartLocation(DestroyedFireLocation);
	}







	// если это swamp - запуск других ракет
	if (ObjectCreationType == 17 && SwampNum > 0)
	if (LastFireTime + 0.15f < Time)
	if (Ammo > 0 || GameLimitedAmmo != 1)
	{
		LastFireTime = Time;

		// ум. кол-во боеприпасов, если нужно
		if (GameLimitedAmmo == 0)	Ammo -= 1;

		// общий - пенальти, если не игрок
		float CurrentPenalty = GameNPCWeaponPenalty*1.0f;
		// если игрок - ничего не надо...
		if (ObjectStatus >= 2) CurrentPenalty = 1.0f;

		switch (SwampNum)
		{
			case 9: FireLocation = VECTOR3D(-0.5f, -0.5f, 2.6f); break;
			case 8: FireLocation = VECTOR3D(0.5f, -0.8f, 2.6f); break;
			case 7: FireLocation = VECTOR3D(-0.5f, -0.8f, 2.6f); break;
			case 6: FireLocation = VECTOR3D(0.5f, -0.5f, 2.6f); break;
			case 5: FireLocation = VECTOR3D(-0.2f, -0.95f, 2.6f); break;
			case 4: FireLocation = VECTOR3D(0.2f, -0.65f, 2.6f); break;
			case 3: FireLocation = VECTOR3D(-0.2f, -0.3f, 2.6f); break;
			case 2: FireLocation = VECTOR3D(0.2f, -0.65f, 2.6f); break;
			case 1: FireLocation = VECTOR3D(0.2f, -0.3f, 2.6f); break;
		}
		Matrix33CalcPoint(&FireLocation, CurrentRotationMat);

		// создаем снаряд
		CProjectile *Projectile  = 0;
		Projectile  = new CProjectile;
		Projectile->Create(ObjectCreationType);
		Projectile->SetLocation(Location+FireLocation);
		Projectile->SetRotation(Rotation);
		for (int i=0; i<Projectile->GraphicFXQuantity; i++)
		{
			Projectile->GraphicFX[i]->Direction = Fire->Direction^-1;
			// учитываем пенальти для визуальных эффектов
			if (CurrentPenalty == 2)
				Projectile->GraphicFX[i]->ParticlesPerSec -= (int)(Projectile->GraphicFX[i]->ParticlesPerSec*0.33f);
			if (CurrentPenalty == 3)
				Projectile->GraphicFX[i]->ParticlesPerSec -= (int)(Projectile->GraphicFX[i]->ParticlesPerSec*0.5f);
			Projectile->GraphicFX[i]->Speed = Projectile->GraphicFX[i]->Speed/CurrentPenalty;
			Projectile->GraphicFX[i]->Life = Projectile->GraphicFX[i]->Life*CurrentPenalty;
			Projectile->GraphicFX[i]->AttractiveValue = Projectile->GraphicFX[i]->AttractiveValue/(CurrentPenalty*CurrentPenalty);
		}
		Projectile->ObjectStatus = ObjectStatus;
		// учитываем пенальти для снаряда
		Projectile->SpeedStart = Projectile->SpeedEnd = Projectile->SpeedStart/CurrentPenalty;
		Projectile->Age = Projectile->Lifetime = Projectile->Age*CurrentPenalty;
		Projectile->DamageHull = Projectile->DamageHull/CurrentPenalty;
		Projectile->DamageSystems = Projectile->DamageSystems/CurrentPenalty;


		// звук...
		if (SoundNum != 0)
		{
			float fVol = 1.0f;
			Audio_PlaySound3D(SoundNum, fVol, Projectile->Location, false);
		}


		SwampNum--;
	}





	// если это фларес - выпускаем остальные
	// SwampNum в этом случае используем с другой целью
	if (ObjectCreationType == 203 && SwampNum > 0)
	if (LastFireTime + 0.4f < Time)
	if (Ammo > 0 || GameLimitedAmmo != 1)
	{
		LastFireTime = Time;

		// ум. кол-во боеприпасов, если нужно
		if (GameLimitedAmmo == 0)	Ammo -= 1;

		// общий - пенальти, если не игрок
		float CurrentPenalty = 1.0f;


		// создаем снаряд
		CProjectile *Projectile  = 0;
		Projectile  = new CProjectile;
		Projectile->Create(ObjectCreationType);
		Projectile->SetLocation(Location+FireLocation);
		Projectile->SetRotation(Rotation+VECTOR3D(vw_Randf0*30.0f,0.0f,vw_Randf0*30.0f));

		for (int i=0; i<Projectile->GraphicFXQuantity; i++)
		{
			Projectile->GraphicFX[i]->Direction = Orientation^-1;
			// учитываем пенальти для визуальных эффектов
			if (CurrentPenalty == 2)
				Projectile->GraphicFX[i]->ParticlesPerSec -= (int)(Projectile->GraphicFX[i]->ParticlesPerSec*0.33f);
			if (CurrentPenalty == 3)
				Projectile->GraphicFX[i]->ParticlesPerSec -= (int)(Projectile->GraphicFX[i]->ParticlesPerSec*0.5f);
			Projectile->GraphicFX[i]->Speed = Projectile->GraphicFX[i]->Speed/CurrentPenalty;
			Projectile->GraphicFX[i]->Life = Projectile->GraphicFX[i]->Life*CurrentPenalty;
			Projectile->GraphicFX[i]->AttractiveValue = Projectile->GraphicFX[i]->AttractiveValue/(CurrentPenalty*CurrentPenalty);
		}
		Projectile->ObjectStatus = ObjectStatus;
		// учитываем пенальти для снаряда
		Projectile->SpeedStart = Projectile->SpeedEnd = Projectile->SpeedStart/CurrentPenalty;
		Projectile->Age = Projectile->Lifetime = Projectile->Age*CurrentPenalty;
		Projectile->DamageHull = Projectile->DamageHull/CurrentPenalty;
		Projectile->DamageSystems = Projectile->DamageSystems/CurrentPenalty;


		// звук...
		if (SoundNum != 0)
		{
			float fVol = 1.0f;
			Audio_PlaySound3D(SoundNum, fVol, Projectile->Location, false);
		}

		SwampNum--;
	}








	// для турелей
	if (WeaponTurret)
	{

		// если нужно наводить на цель
		//if (Fire != 0)
		{
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// наводим на цель, если есть возможность
			//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			// находимся в начальном состоянии поворота ствола
			VECTOR3D NeedAngle(TargetVertObjectNeedAngle,TargetHorizObjectNeedAngle,0);
			GetTurretOnTargetOrientateion(ObjectStatus, Location+FireLocation, Rotation,
					CurrentRotationMat,	&NeedAngle, ObjectCreationType);

			// наводим на цель
			TargetHorizObjectNeedAngle = NeedAngle.y;
			TargetVertObjectNeedAngle = NeedAngle.x;
		}
		/*else
		{
			// устанавливаем в начальное положение
			TargetHorizObjectNeedAngle = 0.0f;
			TargetVertObjectNeedAngle = 0.0f;
		}*/






		// собственно повороты элементов модели на углы

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// поворот башни по горизонтале
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if (TargetHorizObject != -1)
		if (TargetHorizObjectNeedAngle != TargetHorizObjectCurrentAngle)
		{
			if (fabsf(TargetHorizObjectNeedAngle-TargetHorizObjectCurrentAngle) > 180.0f)
			{
				if (TargetHorizObjectCurrentAngle - TargetHorizObjectNeedAngle > 180.0f) TargetHorizObjectCurrentAngle -= 360.0f;
				if (TargetHorizObjectNeedAngle - TargetHorizObjectCurrentAngle > 180.0f) TargetHorizObjectCurrentAngle += 360.0f;
			}

			// находим угол, на который нужно повернуть
			float NeedRotate = TargetHorizObjectCurrentAngle;

			if (TargetHorizObjectNeedAngle>TargetHorizObjectCurrentAngle)
			{
				NeedRotate += 80.0f*TimeDelta/GameNPCTargetingSpeedPenalty;
				if (NeedRotate > TargetHorizObjectNeedAngle) NeedRotate = TargetHorizObjectNeedAngle;
			}
			else
			{
				NeedRotate -= 80.0f*TimeDelta/GameNPCTargetingSpeedPenalty;
				if (NeedRotate < TargetHorizObjectNeedAngle) NeedRotate = TargetHorizObjectNeedAngle;
			}

			// устанавливаем текущий поворот
			TargetHorizObjectCurrentAngle = NeedRotate;

			// поворачиваем все объекты
			for (int i=0; i<DrawObjectQuantity; i++)
			{
				VECTOR3D tmp = DrawObjectList[i].Location-DrawObjectList[TargetHorizObject].Location;

				RotatePointInv(&tmp, DrawObjectList[i].Rotation^(-1.0f));

				DrawObjectList[i].Rotation.y = -NeedRotate;

				RotatePoint(&tmp, DrawObjectList[i].Rotation);

				DrawObjectList[i].Location = tmp+DrawObjectList[TargetHorizObject].Location;
			}
		}






		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// поворот стволов по вертикали
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if (TargetVertObject != -1)
		if (TargetVertObjectNeedAngle != TargetVertObjectCurrentAngle)
		{

			// находим угол, на который нужно повернуть
			float NeedRotate = TargetVertObjectCurrentAngle;
			if (TargetVertObjectNeedAngle>TargetVertObjectCurrentAngle)
			{
				NeedRotate += 80.0f*TimeDelta/GameNPCTargetingSpeedPenalty;
				if (NeedRotate > TargetVertObjectNeedAngle) NeedRotate = TargetVertObjectNeedAngle;
				if (NeedRotate > TargetVertObjectMaxAngle) NeedRotate = TargetVertObjectMaxAngle;
			}
			else
			{
				NeedRotate -= 80.0f*TimeDelta/GameNPCTargetingSpeedPenalty;
				if (NeedRotate < TargetVertObjectNeedAngle) NeedRotate = TargetVertObjectNeedAngle;
				if (NeedRotate < TargetVertObjectMinAngle) NeedRotate = TargetVertObjectMinAngle;
			}

			// устанавливаем текущий поворот
			TargetVertObjectCurrentAngle = NeedRotate;

			// поворачиваем все объекты
			VECTOR3D tmp = DrawObjectList[TargetVertObject].Location-DrawObjectList[TargetVertObject].Location;

			RotatePointInv(&tmp, DrawObjectList[TargetVertObject].Rotation^(-1.0f));

			DrawObjectList[TargetVertObject].Rotation.x = -NeedRotate;

			RotatePoint(&tmp, DrawObjectList[TargetVertObject].Rotation);

			DrawObjectList[TargetVertObject].Location = tmp+DrawObjectList[TargetVertObject].Location;
		}


		// турель
		VECTOR3D RotationBase = Rotation;
		VECTOR3D BaseBoundTMP = BaseBound;
		RotatePoint(&BaseBoundTMP, RotationBase);

		VECTOR3D RotationMiddle = Rotation;
		VECTOR3D MiddleBoundTMP = MiddleBound;
		if (TargetHorizObject != -1)
		{
			RotationMiddle = DrawObjectList[TargetHorizObject].Rotation+Rotation;
		}
		RotatePoint(&MiddleBoundTMP, RotationMiddle);

		VECTOR3D RotationWeapon = Rotation;
		if (TargetVertObject != -1)
		{
			RotationWeapon = DrawObjectList[TargetVertObject].Rotation+Rotation;
		}

		VECTOR3D WeaponBoundTMP = WeaponBound;
		RotatePoint(&WeaponBoundTMP, RotationWeapon);

		FireLocation = BaseBoundTMP + MiddleBoundTMP + WeaponBoundTMP;


		// особый случай, испускаем без вращающихся частей (антиматерия, ион)
		if (TargetHorizObject == -1 && TargetVertObject == -1)
		{
			RotationWeapon = VECTOR3D(TargetVertObjectNeedAngle, TargetHorizObjectNeedAngle, 0.0f)+Rotation;
		}

		Orientation = VECTOR3D(0.0f, 0.0f, 1.0f);
		RotatePoint(&Orientation, RotationWeapon);
	}




	// объект в порядке - удалять не нужно
	return true;

}













//-----------------------------------------------------------------------------
// Установка положения
//-----------------------------------------------------------------------------
void CWeapon::SetRotation(VECTOR3D NewRotation)
{

	// вызываем родительскую функцию
	::CObject3D::SetRotation(NewRotation);


	if (!WeaponTurret)
	{
		// положение точки выстрела
		Matrix33CalcPoint(&FireLocation, OldInvRotationMat);
		Matrix33CalcPoint(&FireLocation, CurrentRotationMat);

		if (Fire != 0)
		{
			Fire->MoveSystem(Location + FireLocation);
			Fire->SetStartLocation(Location + FireLocation);
			Fire->RotateSystemByAngle(Rotation);
		}
	}
	else
	{
		// турель
		VECTOR3D RotationBase = Rotation;
		VECTOR3D BaseBoundTMP = BaseBound;
		RotatePoint(&BaseBoundTMP, RotationBase);

		VECTOR3D RotationMiddle = Rotation;
		VECTOR3D MiddleBoundTMP = MiddleBound;
		if (TargetHorizObject != -1)
		{
			RotationMiddle = DrawObjectList[TargetHorizObject].Rotation + Rotation;
		}
		RotatePoint(&MiddleBoundTMP, RotationMiddle);

		VECTOR3D RotationWeapon = Rotation;
		if (TargetVertObject != -1)
		{
			RotationWeapon = DrawObjectList[TargetVertObject].Rotation + Rotation;
		}

		VECTOR3D WeaponBoundTMP = WeaponBound;
		RotatePoint(&WeaponBoundTMP, RotationWeapon);

		FireLocation = BaseBoundTMP + MiddleBoundTMP + WeaponBoundTMP;

		// особый случай, испускаем без вращающихся частей (антиматерия, ион)
		if (TargetHorizObject == -1 && TargetVertObject == -1)
		{
			RotationWeapon = VECTOR3D(TargetVertObjectNeedAngle, TargetHorizObjectNeedAngle, 0.0f)+Rotation;
		}

		Orientation = VECTOR3D(0.0f, 0.0f, 1.0f);
		RotatePoint(&Orientation, RotationWeapon);
	}




	if (DestroyedFire != 0)
	{
		Matrix33CalcPoint(&DestroyedFireLocation, OldInvRotationMat);
		Matrix33CalcPoint(&DestroyedFireLocation, CurrentRotationMat);
		DestroyedFire->MoveSystem(Location + DestroyedFireLocation);
		DestroyedFire->SetStartLocation(Location + DestroyedFireLocation);
		DestroyedFire->RotateSystemByAngle(Rotation);
	}
	// тут DestroyedFireLocation не считаем, т.к. все равно всегда создаем DestroyedFire
	if (DestroyedSmoke != 0)
	{
		DestroyedSmoke->MoveSystemLocation(Location + DestroyedFireLocation);
		DestroyedSmoke->RotateSystemByAngle(Rotation);
	}
	// если лучевое оружие
	if (LaserMaser != 0)
	{
		Matrix33CalcPoint(&LaserMaser->ProjectileCenter, OldInvRotationMat);
		Matrix33CalcPoint(&LaserMaser->ProjectileCenter, CurrentRotationMat);
		LaserMaser->SetLocation(Location+FireLocation+LaserMaser->ProjectileCenter);
		LaserMaser->SetRotation(NewRotation);
	}
}







//-----------------------------------------------------------------------------
// Установка положения
//-----------------------------------------------------------------------------
void CWeapon::SetLocation(VECTOR3D NewLocation)
{
	// вызываем родительскую функцию
	::CObject3D::SetLocation(NewLocation);

	// положение утечки
	if (Fire != 0)
	{
		Fire->MoveSystem(NewLocation + FireLocation);
		Fire->SetStartLocation(NewLocation + FireLocation);
	}
	if (DestroyedFire != 0)
	{
		DestroyedFire->MoveSystem(NewLocation + DestroyedFireLocation);
		DestroyedFire->SetStartLocation(NewLocation + DestroyedFireLocation);
	}
	if (DestroyedSmoke != 0)
	{
		DestroyedSmoke->MoveSystemLocation(NewLocation + DestroyedFireLocation);
	}

	// если лучевое оружие
	if (LaserMaser != 0)
	{
		LaserMaser->SetLocation(Location+FireLocation+LaserMaser->ProjectileCenter);
	}



	// звук... для мазеров-лазеров нужно учитывать перемещение
	if (LaserMaserSoundNum != 0)
	{
		// уже играем, нужно изменить данные
		if (vw_FindSoundByNum(LaserMaserSoundNum) != 0)
			vw_FindSoundByNum(LaserMaserSoundNum)->SetLocation(Location.x, Location.y, Location.z);
	}

}







//-----------------------------------------------------------------------------
// Выстрел
//-----------------------------------------------------------------------------
bool CWeapon::WeaponFire(float Time)
{

	// если оружие не установлено - нам тут делать нечего
	if (ObjectCreationType == 0) return false;


	// общий - пенальти, если не игрок
	float CurrentPenalty = GameNPCWeaponPenalty*1.0f;
	// если игрок или свои - ничего не надо...
	if (ObjectStatus >= 2) CurrentPenalty = 1.0f;


	// если фларес - тоже ничего не надо
	if (ObjectCreationType == 203) CurrentPenalty = 1.0f;


	// проверяем по времени, можем стрелять или нет
	// делаем ее тут, чтобы "правильно" озвучивать проблемы стрельбы
	if (Time < LastFireTime + NextFireTime*CurrentPenalty) return false;
	// запоминаем время стрельбы
	LastFireTime = Time;



	// для оружия землян, делаем небольшие проверки...
	if (ObjectCreationType >= 1 && ObjectCreationType <= 99)
	{

		// для поврежденного оружия проверяем... может быть осечка в стрельбе
		bool Misfire = false;
		if (Strength < StrengthStart)
		if (Strength/StrengthStart > vw_Randf1)
		{
			Misfire = true;
		}


		// если оружие уничтожено или уже нечем стрелять - нам тут делать нечего
		if (Strength <= 0.0f || Ammo == 0 || Misfire)
		{
			// перед тем как уйти, ставим проигрывание звука "проблема с оружием"

			float fVol = 1.0f;

			switch (ObjectCreationType)
			{
				// Kinetic
				case 1:
				case 2:
				case 3:
				case 4:
					Audio_PlaySound3D(1, fVol, Location, false);
					break;

				// Ion
				case 5:
				case 6:
				case 7:
				// Plasma
				case 8:
				case 9:
				case 10:
					Audio_PlaySound3D(2, fVol, Location, false);
					break;

				// Maser
				case 11:
				case 12:
				// Laser
				case 14:
					Audio_PlaySound3D(3, fVol, Location, false);

					break;
				// Antimatter
				case 13:
				// Gauss
				case 15:
					Audio_PlaySound3D(4, fVol, Location, false);
					break;

				// ракета
				case 16:
				// рой
				case 17:
				// торпеда
				case 18:
				// бомба
				case 19:
					Audio_PlaySound3D(5, fVol, Location, false);
					break;
			}

			return false;
		}




		// только для игрока! проверяем заряд энергии для выстрела
		if (ObjectStatus == 3)
		{
			if (CurrentEnergyAccumulated < EnergyUse) return false;
			else CurrentEnergyAccumulated = 0.0f;
		}

		// ум. кол-во боеприпасов, если нужно
		if (GameLimitedAmmo == 0) Ammo -= 1;


		// делаем вспышку возле ствола для всего оружия землят (только землян), если это не ракетная установка
		if (ObjectCreationType < 16)
			Fire->IsSuppressed = false;

	}











	VECTOR3D RotationWeapon = Rotation;
	if (WeaponTurret)
	{
		// турель
		VECTOR3D RotationBase = Rotation;
		VECTOR3D BaseBoundTMP = BaseBound;
		RotatePoint(&BaseBoundTMP, RotationBase);

		VECTOR3D RotationMiddle = Rotation;
		VECTOR3D MiddleBoundTMP = MiddleBound;
		if (TargetHorizObject != -1)
		{
			RotationMiddle = DrawObjectList[TargetHorizObject].Rotation + Rotation;
		}
		RotatePoint(&MiddleBoundTMP, RotationMiddle);

		if (TargetVertObject != -1)
		{
			RotationWeapon = DrawObjectList[TargetVertObject].Rotation + Rotation;
		}

		VECTOR3D WeaponBoundTMP = WeaponBound;
		RotatePoint(&WeaponBoundTMP, RotationWeapon);

		FireLocation = BaseBoundTMP + MiddleBoundTMP + WeaponBoundTMP;


		// особый случай, испускаем без вращающихся частей (антиматерия, ион)
		if (TargetHorizObject == -1 && TargetVertObject == -1)
		{
			RotationWeapon = VECTOR3D(TargetVertObjectNeedAngle, TargetHorizObjectNeedAngle, 0.0f)+Rotation;
		}

	}









	// создаем снаряд
	CProjectile *Projectile  = 0;
	Projectile  = new CProjectile;
	Projectile->Create(ObjectCreationType);


	// если лучевое оружие, немного все делаем по другому
	// или это испускатель мин
	if (Projectile->ProjectileType == 2)
	{
		if (LaserMaser != 0){delete LaserMaser; LaserMaser = 0;}
		LaserMaser = Projectile;
		Matrix33CalcPoint(&LaserMaser->ProjectileCenter, CurrentRotationMat);
		LaserMaser->SetLocation(Location+FireLocation+LaserMaser->ProjectileCenter);
	}
	else// если это снаряд, его нужно немного вынести, так лучше смотрится
	{
		if (Projectile->ProjectileType == 0)
		{
			VECTOR3D ADDPOS(0,0,4.0f);
			if (WeaponTurret) ADDPOS = VECTOR3D(0,0,2.0f);

			RotatePoint(&ADDPOS, RotationWeapon);

			Projectile->SetLocation(Location+FireLocation+ADDPOS);
		}
		else // для ракет и мин все без изменения
			Projectile->SetLocation(Location+FireLocation);
	}






	// если это мина, то нужно делать немного по другому
	if (Projectile->ProjectileType == 3 || Projectile->ProjectileType == 4)
	{
		Projectile->SetRotation(RotationWeapon);
		for (int i=0; i<Projectile->GraphicFXQuantity; i++)
		{
			Projectile->GraphicFX[i]->Direction = Orientation;
			// учитываем пенальти для визуальных эффектов
			Projectile->GraphicFX[i]->ParticlesPerSec = (int)(Projectile->GraphicFX[i]->ParticlesPerSec);

			Projectile->GraphicFX[i]->Speed = Projectile->GraphicFX[i]->Speed;
			Projectile->GraphicFX[i]->Life = Projectile->GraphicFX[i]->Life;
			Projectile->GraphicFX[i]->AttractiveValue = Projectile->GraphicFX[i]->AttractiveValue;
		}
		Projectile->ObjectStatus = ObjectStatus;
		// учитываем пенальти для снаряда
		Projectile->SpeedStart = Projectile->SpeedEnd = Projectile->SpeedStart/CurrentPenalty;
		Projectile->Age = Projectile->Lifetime = Projectile->Age;
		Projectile->DamageHull = Projectile->DamageHull/CurrentPenalty;
		Projectile->DamageSystems = Projectile->DamageSystems/CurrentPenalty;

		// приводим к типу снаряда (0-обычный или 1-уничтожаемый)
		Projectile->ProjectileType = Projectile->ProjectileType - 3;
	}
	else
	{
		Projectile->SetRotation(RotationWeapon);
		for (int i=0; i<Projectile->GraphicFXQuantity; i++)
		{
			Projectile->GraphicFX[i]->Direction = Orientation;//Fire->Direction^-1;
			// учитываем пенальти для визуальных эффектов
			Projectile->GraphicFX[i]->ParticlesPerSec = (int)(Projectile->GraphicFX[i]->ParticlesPerSec/CurrentPenalty);

			Projectile->GraphicFX[i]->Speed = Projectile->GraphicFX[i]->Speed/CurrentPenalty;
			Projectile->GraphicFX[i]->Life = Projectile->GraphicFX[i]->Life*CurrentPenalty;
			Projectile->GraphicFX[i]->AttractiveValue = Projectile->GraphicFX[i]->AttractiveValue/(CurrentPenalty*CurrentPenalty);
		}
		Projectile->ObjectStatus = ObjectStatus;
		// учитываем пенальти для снаряда
		Projectile->SpeedStart = Projectile->SpeedEnd = Projectile->SpeedStart/CurrentPenalty;
		Projectile->Age = Projectile->Lifetime = Projectile->Age*CurrentPenalty;
		Projectile->DamageHull = Projectile->DamageHull/CurrentPenalty;
		Projectile->DamageSystems = Projectile->DamageSystems/CurrentPenalty;
	}






	// звук...
	if (SoundNum != 0)
	{
		float fVol = 1.0f;
		if (LaserMaser != 0) LaserMaserSoundNum = LaserMaserSoundNum;

		LaserMaserSoundNum = Audio_PlaySound3D(SoundNum, fVol, Location+FireLocation, false);
		// если не надо сохранять
		if (LaserMaser == 0) LaserMaserSoundNum = 0;
	}






	// если это груповой выстрел:

	// нужно создать еще 9 ракет
	if (ObjectCreationType == 17)
		SwampNum = 9;

	// нужно создать еще 4 фларес
	if (ObjectCreationType == 203)
		SwampNum = 4;






	// выстрел был
	return true;
}


