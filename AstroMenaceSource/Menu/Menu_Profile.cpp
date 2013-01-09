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


#include "../Game.h"


// вот тут храним самый важный номер! - номер текущего профайла!!!
int	CurrentProfile=-1;


char NewProfileName[128] = "";
int NewProfileNamePos = 0;
float LastProfileNameTime = 0.0f;
float CurrentProfileNameTransp = 0.9f;
int	SoundOnProfileID = -1;

int SoundTaping = 0;



//------------------------------------------------------------------------------------
// создание новой записи
//------------------------------------------------------------------------------------
void NewRecord()
{
	// заносим в новый профайл (последний)
	int ProfileNum = -1;
	for (int i=4; i>=0; i--)
		if (!Setup.Profile[i].Used) ProfileNum = i;


	// выводим диалог - все заняты!
	if (ProfileNum == -1)
	{
		SetCurrentDialogBox(1);
		return;
	}

	if (strlen(NewProfileName)<=0) return;


	// пишем данные в профайл

	Setup.Profile[ProfileNum].Used = true;
	strcpy(Setup.Profile[ProfileNum].Name, NewProfileName);

	Setup.Profile[ProfileNum].NPCWeaponPenalty = 3;
	Setup.Profile[ProfileNum].NPCArmorPenalty = 2;
	Setup.Profile[ProfileNum].NPCTargetingSpeedPenalty = 2;
	Setup.Profile[ProfileNum].LimitedAmmo = 0;
	Setup.Profile[ProfileNum].DestroyableWeapon = 1;
	Setup.Profile[ProfileNum].WeaponTargetingMode = 0;
	Setup.Profile[ProfileNum].SpaceShipControlMode = 1;


	Setup.Profile[ProfileNum].Ship = 1;
	Setup.Profile[ProfileNum].ShipHullUpgrade = 1;
	Setup.Profile[ProfileNum].ShipHullCurrentStrength = 30;

	// сброс настроек оружия
	for (int i=0; i<6; i++)
	{
		Setup.Profile[ProfileNum].Weapon[i] = 0;
		Setup.Profile[ProfileNum].WeaponAmmo[i] = 0;
		Setup.Profile[ProfileNum].WeaponControl[i] = 0;
		Setup.Profile[ProfileNum].WeaponAltControl[i] = 0;
		Setup.Profile[ProfileNum].WeaponAltControlData[i] = 0;
		Setup.Profile[ProfileNum].WeaponSlotYAngle[i] = 0.0f;
	}
	// ставим 2 орудия первоначально


	Setup.Profile[ProfileNum].Weapon[2] = 1;
	Setup.Profile[ProfileNum].WeaponAmmo[2] = 3000;
	Setup.Profile[ProfileNum].WeaponControl[2] = 1;
	Setup.Profile[ProfileNum].Weapon[3] = 1;
	Setup.Profile[ProfileNum].WeaponAmmo[3] = 3000;
	Setup.Profile[ProfileNum].WeaponControl[3] = 1;
	Setup.Profile[ProfileNum].Weapon[4] = 16;
	Setup.Profile[ProfileNum].WeaponAmmo[4] = 200;
	Setup.Profile[ProfileNum].WeaponControl[4] = 2;

	Setup.Profile[ProfileNum].EngineSystem = 1;
	Setup.Profile[ProfileNum].TargetingSystem = 1;
	Setup.Profile[ProfileNum].AdvancedProtectionSystem = 1;
	Setup.Profile[ProfileNum].PowerSystem = 1;
	Setup.Profile[ProfileNum].TargetingMechanicSystem = 1;

	Setup.Profile[ProfileNum].Difficulty = 50;

	Setup.Profile[ProfileNum].PrimaryWeaponFireMode = 2;
	Setup.Profile[ProfileNum].SecondaryWeaponFireMode = 1;


	Setup.Profile[ProfileNum].Money = 200;
	Setup.Profile[ProfileNum].Experience = 0;

	// сброс настроек
	for (int i=0; i<100; i++)
	{
		Setup.Profile[ProfileNum].ByMissionExperience[i] = 0;
		Setup.Profile[ProfileNum].MissionReplayCount[i] = 0;
	}


	Setup.Profile[ProfileNum].OpenLevelNum = 0;// 1;


	// подготавливаем, для новой записи
	NewProfileNamePos = 0;
	memset(NewProfileName, 0, sizeof(NewProfileName));


	CurrentProfile = ProfileNum;
	Setup.LastProfile = CurrentProfile;
	// сразу ставим первую миссию все равно выбирать не из чего
	CurrentMission = 0;
	Setup.Profile[CurrentProfile].LastMission = CurrentMission;
	// ставим первый лист миссий
	StartMission = 0;
	EndMission = 4;

}




//------------------------------------------------------------------------------------
// создание дубликата записи
//------------------------------------------------------------------------------------
void DuplicateRecord()
{
	// запоминаем номер профайла, с которого копировать
	int BaseProfileNum = CurrentProfile;

	// заносим в новый профайл (последний)
	int ProfileNum = -1;
	for (int i=4; i>=0; i--)
		if (!Setup.Profile[i].Used) ProfileNum = i;

	// выводим диалог - все заняты!
	if (ProfileNum == -1)
	{
		SetCurrentDialogBox(1);
		return;
	}


	// пишем данные в профайл (дублируем)

	Setup.Profile[ProfileNum].Used = true;
	strcpy(Setup.Profile[ProfileNum].Name, Setup.Profile[BaseProfileNum].Name);

	Setup.Profile[ProfileNum].NPCWeaponPenalty = Setup.Profile[BaseProfileNum].NPCWeaponPenalty;
	Setup.Profile[ProfileNum].NPCArmorPenalty = Setup.Profile[BaseProfileNum].NPCArmorPenalty;
	Setup.Profile[ProfileNum].NPCTargetingSpeedPenalty = Setup.Profile[BaseProfileNum].NPCTargetingSpeedPenalty;
	Setup.Profile[ProfileNum].LimitedAmmo = Setup.Profile[BaseProfileNum].LimitedAmmo;
	Setup.Profile[ProfileNum].DestroyableWeapon = Setup.Profile[BaseProfileNum].DestroyableWeapon;
	Setup.Profile[ProfileNum].WeaponTargetingMode = Setup.Profile[BaseProfileNum].WeaponTargetingMode;
	Setup.Profile[ProfileNum].SpaceShipControlMode = Setup.Profile[BaseProfileNum].SpaceShipControlMode;


	Setup.Profile[ProfileNum].Ship = Setup.Profile[BaseProfileNum].Ship;
	Setup.Profile[ProfileNum].ShipHullUpgrade = Setup.Profile[BaseProfileNum].ShipHullUpgrade;
	Setup.Profile[ProfileNum].ShipHullCurrentStrength = Setup.Profile[BaseProfileNum].ShipHullCurrentStrength;

	// сброс настроек оружия
	for (int i=0; i<6; i++)
	{
		Setup.Profile[ProfileNum].Weapon[i] = Setup.Profile[BaseProfileNum].Weapon[i];
		Setup.Profile[ProfileNum].WeaponAmmo[i] = Setup.Profile[BaseProfileNum].WeaponAmmo[i];
		Setup.Profile[ProfileNum].WeaponControl[i] = Setup.Profile[BaseProfileNum].WeaponControl[i];
		Setup.Profile[ProfileNum].WeaponAltControl[i] = Setup.Profile[BaseProfileNum].WeaponAltControl[i];
		Setup.Profile[ProfileNum].WeaponAltControlData[i] = Setup.Profile[BaseProfileNum].WeaponAltControlData[i];
		Setup.Profile[ProfileNum].WeaponSlotYAngle[i] = Setup.Profile[BaseProfileNum].WeaponSlotYAngle[i];
	}


	Setup.Profile[ProfileNum].EngineSystem = Setup.Profile[BaseProfileNum].EngineSystem;
	Setup.Profile[ProfileNum].TargetingSystem = Setup.Profile[BaseProfileNum].TargetingSystem;
	Setup.Profile[ProfileNum].AdvancedProtectionSystem = Setup.Profile[BaseProfileNum].AdvancedProtectionSystem;
	Setup.Profile[ProfileNum].PowerSystem = Setup.Profile[BaseProfileNum].PowerSystem;
	Setup.Profile[ProfileNum].TargetingMechanicSystem = Setup.Profile[BaseProfileNum].TargetingMechanicSystem;

	Setup.Profile[ProfileNum].Difficulty = Setup.Profile[BaseProfileNum].Difficulty;

	Setup.Profile[ProfileNum].PrimaryWeaponFireMode = Setup.Profile[BaseProfileNum].PrimaryWeaponFireMode;
	Setup.Profile[ProfileNum].SecondaryWeaponFireMode = Setup.Profile[BaseProfileNum].SecondaryWeaponFireMode;


	Setup.Profile[ProfileNum].Money = Setup.Profile[BaseProfileNum].Money;
	Setup.Profile[ProfileNum].Experience = Setup.Profile[BaseProfileNum].Experience;

	for (int i=0; i<100; i++)
	{
		Setup.Profile[ProfileNum].ByMissionExperience[i] = Setup.Profile[BaseProfileNum].ByMissionExperience[i];
		Setup.Profile[ProfileNum].MissionReplayCount[i] = Setup.Profile[BaseProfileNum].MissionReplayCount[i];
	}


	Setup.Profile[ProfileNum].OpenLevelNum = Setup.Profile[BaseProfileNum].OpenLevelNum;
	Setup.Profile[ProfileNum].LastMission = Setup.Profile[BaseProfileNum].LastMission;



	CurrentProfile = ProfileNum;
	Setup.LastProfile = CurrentProfile;
	CurrentMission = Setup.Profile[CurrentProfile].LastMission;
	// ставим нужный лист миссий
	StartMission = 0;
	EndMission = 4;
	if (CurrentMission != -1)
	while (!(StartMission<=CurrentMission && CurrentMission<=EndMission))
	{
		StartMission += 5;
		EndMission += 5;
	}

}




//------------------------------------------------------------------------------------
// удаление записи
//------------------------------------------------------------------------------------
void DeleteRecord()
{
	if (CurrentProfile == -1) return;


	// проверяем, входит в таблицу рекордов или нет
	if (Setup.Profile[CurrentProfile].Experience != 0)
		AddTopScores(Setup.Profile[CurrentProfile].Experience, Setup.Profile[CurrentProfile].Name, false);



	// если это последняя запись...
	if (CurrentProfile == 4)
	{
		Setup.Profile[CurrentProfile].Used = false;
		CurrentProfile -= 1;
		goto exit;
	}
	// если после этой записи - ничего нет... тоже просто удаляем
	if (!Setup.Profile[CurrentProfile+1].Used)
	{
		Setup.Profile[CurrentProfile].Used = false;
		CurrentProfile -= 1;
		goto exit;
	}



	for (int i=CurrentProfile; i<4; i++)
	{
		memcpy(Setup.Profile+i, Setup.Profile+i+1, sizeof(GameProfile));
		Setup.Profile[i+1].Used = false;

	}


exit:

	// проверяем, текущий номер
	if (CurrentProfile == -1)
	if (Setup.Profile[0].Used) CurrentProfile = 0;
	Setup.LastProfile = CurrentProfile;

}










//------------------------------------------------------------------------------------
// ввод названия
//------------------------------------------------------------------------------------
void ProfileInputText()
{

	// пишем букву, если можем (т.к. у нас утф8 юникод, нужно как минимум 3 байта + 1 байт под \0 в конце строки)
	if (NewProfileNamePos < 124)
	if (vw_FontSize(NewProfileName)< 540)
	if (vw_GetCurrentKeyUnicode()) // если тут не ноль, а юникод - значит нажали
	{
		Uint16 NewChar = vw_GetCurrentKeyUnicode();
		vw_SetCurrentKeyUnicode(0); // сразу сбрасываем данные
		// делаем простое преобразование, без учета суррогатной пары
		char* str = NewProfileName + NewProfileNamePos;
		if (NewChar <= 0x7F)
		{
			*str = (char)NewChar;
			NewProfileNamePos++;
		}
		else if (NewChar <= 0x7FF)
		{
			*str++ = (char)(0xC0 | (NewChar >> 6));
			*str = (char)(0x80 | (NewChar & 0x3F));
			NewProfileNamePos+=2;
		}
		else
		{
			*str++ = (char)(0xE0 | (NewChar >> 12));
			*str++ = (char)(0x80 | ((NewChar >> 6) & 0x3F));
			*str = (char)(0x80 | (NewChar & 0x3F));
			NewProfileNamePos+=3;
		}

		if (vw_FindSoundByNum(SoundTaping) != 0)
			vw_FindSoundByNum(SoundTaping)->Stop(0.0f);

		SoundTaping = Audio_PlaySound2D(4,1.0f);

		vw_SetCurrentKeyUnicode(0);
	}



	// проверяем, может спец-код
	if (vw_GetKeys(SDLK_BACKSPACE))
	if (NewProfileNamePos>0)
	{
		// кривое решение на "пока", перебираем в поисках предпоследнего символа
		const char *ReversePoint = NewProfileName;
		const char *ReversePointPrevious = 0;
		while (strlen(ReversePoint) > 0)
		{
			unsigned CurrentChar;
			ReversePointPrevious = ReversePoint;
			ReversePoint = utf8_to_utf32(ReversePoint, &CurrentChar);
		}
		while (ReversePointPrevious != ReversePoint)
		{
			NewProfileName[NewProfileNamePos] = 0;
			NewProfileNamePos--;
			ReversePointPrevious++;
		}
		NewProfileName[NewProfileNamePos] = 0;

		if (vw_FindSoundByNum(SoundTaping) != 0)
			vw_FindSoundByNum(SoundTaping)->Stop(0.0f);
		SoundTaping = Audio_PlaySound2D(4,1.0f);

		vw_SetKeys(SDLK_BACKSPACE, false);
	}

	// ввод названия
	if (vw_GetKeys(SDLK_KP_ENTER) || vw_GetKeys(SDLK_RETURN))
	if (NewProfileNamePos>0)
	{
		NewRecord();
		//Audio_PlayMenuSound(4,1.0f);
		vw_SetKeys(SDLK_KP_ENTER, false);
		vw_SetKeys(SDLK_RETURN, false);
	}



	int X1 = Setup.iAspectRatioWidth/2 - 372;
	int Y1 = 230;

	// находим положения ввода
	int Size = vw_FontSize(NewProfileName);
	RECT SrcRect, DstRect;
	SetRect(&SrcRect,0,0,2,2);
	SetRect(&DstRect,X1+Size+2,Y1-2,X1+26+Size,Y1+24);
	vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/MENU/whitepoint.tga"),
		true, CurrentProfileNameTransp*MenuContentTransp);

	float DeltaTime = vw_GetTime() - LastProfileNameTime;
	LastProfileNameTime = vw_GetTime();
	CurrentProfileNameTransp -= 2.0f*DeltaTime;
	if (CurrentProfileNameTransp < 0.2f) CurrentProfileNameTransp = 0.9f;

}

















//------------------------------------------------------------------------------------
// выбор текущего профайла
//------------------------------------------------------------------------------------
void ProfileMenu()
{

	RECT SrcRect, DstRect;
	SetRect(&SrcRect,2,2,863-2,484-2);
	SetRect(&DstRect,Setup.iAspectRatioWidth/2-427,175-15,Setup.iAspectRatioWidth/2-427+863-4,175-15+484-4);
	vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/MENU/panel800_444_back.tga"), true, 0.9f*MenuContentTransp);


	int X1 = Setup.iAspectRatioWidth/2 - 372;
	int Y1 = 200;
	int Prir1 = 24;

	// надпись
	vw_DrawFont(X1, Y1, 0, 0, 1.0f, 1.0f,0.5f,0.0f, MenuContentTransp, vw_GetText("3_New_Pilot_Profile"));


	Y1 += 30;
	SetRect(&SrcRect,0,0,2,2);
	SetRect(&DstRect,X1-2,Y1-6,X1+2+590,Y1-2+30);
	vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/MENU/blackpoint.tga"), true, 0.2f*MenuContentTransp);
	SetRect(&DstRect,X1,Y1-4,X1+590,Y1-4+30);
	vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/MENU/blackpoint.tga"), true, 0.5f*MenuContentTransp);
	// кнопка, создания новой записи
	bool Off = false;
	if (strlen(NewProfileName)<=0) Off = true;
	if (DrawButton128_2(X1+616, Y1-6, vw_GetText("1_Create"), MenuContentTransp, Off))
	{
		NewRecord();
	}

	// ввод текста
	if (!isDialogBoxDrawing())
	if (MenuContentTransp == 1.0f) ProfileInputText();

	vw_DrawFont(X1, Y1, 0, 0, 1.0f, 1.0f,1.0f,1.0f, MenuContentTransp, NewProfileName);

	Y1 += Prir1;







	// список для выбора записи
	Y1 += Prir1;
	vw_DrawFont(X1, Y1, 0, 0, 1.0f, 1.0f,0.5f,0.0f, MenuContentTransp, vw_GetText("3_Pilots_Profiles"));
	int Size = vw_FontSize(vw_GetText("3_Money"));
	float WScale = 0;
	if (Size > 70)
	{
		Size = 70;
		WScale = -70;
	}
	int SizeI = Setup.iAspectRatioWidth/2+2 + (130 - Size)/2;
	vw_DrawFont(SizeI, Y1, WScale, 0, 1.0f, 1.0f,0.5f,0.0f, MenuContentTransp, vw_GetText("3_Money"));

	Size = vw_FontSize(vw_GetText("3_Experience"));
	WScale = 0;
	if (Size > 100)
	{
		Size = 100;
		WScale = -100;
	}
	SizeI = Setup.iAspectRatioWidth/2+132 + (130 - Size)/2;
	vw_DrawFont(SizeI, Y1, WScale, 0, 1.0f, 1.0f,0.5f,0.0f, MenuContentTransp, vw_GetText("3_Experience"));

	Size = vw_FontSize(vw_GetText("3_Difficulty"));
	WScale = 0;
	if (Size > 100)
	{
		Size = 100;
		WScale = -100;
	}
	SizeI = Setup.iAspectRatioWidth/2+262 + (130 - Size)/2;
	vw_DrawFont(SizeI, Y1, WScale, 0, 1.0f, 1.0f,0.5f,0.0f, MenuContentTransp, vw_GetText("3_Difficulty"));


	Y1 += 30;
	SetRect(&SrcRect,0,0,2,2);
	SetRect(&DstRect,X1-2,Y1-6,X1+2+750,Y1-2+230);
	vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/MENU/blackpoint.tga"), true, 0.2f*MenuContentTransp);
	SetRect(&DstRect,X1,Y1-4,X1+750,Y1-4+230);
	vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/MENU/blackpoint.tga"), true, 0.5f*MenuContentTransp);
	Y1 += 230;



	int TMPSoundOnProfileID = -1;
	int TmpY = Y1-230+8;
	for (int i=0; i<5; i++)
	{
		if (Setup.Profile[i].Used)
		{
			vw_DrawFont(X1+10, TmpY, 0, 0, 1.0f, 1.0f,1.0f,1.0f, MenuContentTransp, "%i.",i+1);

			if (vw_FontSize(Setup.Profile[i].Name) > 300)
			{
				vw_DrawFont(X1+50, TmpY, 0, 300, 1.0f, 1.0f,1.0f,1.0f, MenuContentTransp, Setup.Profile[i].Name);
				vw_DrawFont(X1+50+310, TmpY, 0, 0, 1.0f, 1.0f,1.0f,1.0f, MenuContentTransp, "...");
			}
			else
				vw_DrawFont(X1+50, TmpY, 0, 0, 1.0f, 1.0f,1.0f,1.0f, MenuContentTransp, Setup.Profile[i].Name);


			int Size = vw_FontSize("%i", Setup.Profile[i].Money);
			int SizeI = Setup.iAspectRatioWidth/2+2 + (130 - Size)/2;
			vw_DrawFont(SizeI, TmpY, 0, 0, 1.0f, 1.0f,1.0f,1.0f, MenuContentTransp, "%i", Setup.Profile[i].Money);
			Size = vw_FontSize("%i", Setup.Profile[i].Experience);
			SizeI = Setup.iAspectRatioWidth/2+132 + (130 - Size)/2;
			vw_DrawFont(SizeI, TmpY, 0, 0, 1.0f, 1.0f,1.0f,1.0f, MenuContentTransp, "%i", Setup.Profile[i].Experience);
			Size = vw_FontSize("%i%%", Setup.Profile[i].Difficulty);
			SizeI = Setup.iAspectRatioWidth/2+262 + (130 - Size)/2;
			vw_DrawFont(SizeI, TmpY, 0, 0, 1.0f, 1.0f,1.0f,1.0f, MenuContentTransp, "%i%%", Setup.Profile[i].Difficulty);


			// работаем с клавиатурой
			if ((MenuContentTransp >= 0.99f) && !isDialogBoxDrawing()) CurrentActiveMenuElement++;
			bool InFocusByKeyboard = false;
			if (CurrentKeyboardSelectMenuElement > 0)
			{
				if (CurrentKeyboardSelectMenuElement == CurrentActiveMenuElement)
				{
					InFocusByKeyboard = true;
				}
			}

			// проверяем, если стоим над записью
			SetRect(&SrcRect,0,0,2,2);
			SetRect(&DstRect,X1,Y1-233+46*i,X1+750,Y1-234+46+46*i);
			if (!isDialogBoxDrawing())
			if (vw_OnRect(&DstRect) || InFocusByKeyboard)
			{
				TMPSoundOnProfileID = i;
				CurrentCursorStatus = 1;
				// если только встали - нужно звуком это показать
				if (SoundOnProfileID != i)
				{
					SoundOnProfileID = i;
					// если задействуем клавиатуру - неиграем тут звук
					if (CurrentKeyboardSelectMenuElement == 0) Audio_PlaySound2D(5,1.0f);
				}

				if (vw_GetWindowLBMouse(true) || (InFocusByKeyboard && (vw_GetKeys(SDLK_KP_ENTER) || vw_GetKeys(SDLK_RETURN))))
				{
					// если другой - нужно сбросить миссию...
					if (CurrentProfile != i) CurrentMission = Setup.Profile[i].LastMission;
					CurrentProfile = i;
					Setup.LastProfile = CurrentProfile;
					// играем звук выбора
					Audio_PlaySound2D(6,1.0f);
					if (InFocusByKeyboard)
					{
						vw_SetKeys(SDLK_KP_ENTER, false);
						vw_SetKeys(SDLK_RETURN, false);
					}
				}

				if (CurrentProfile != i)
				{
					// переход по 2-му клику
					if (vw_GetWindowLBDoubleMouse(true))
					{
						CurrentProfile = i;
						Setup.LastProfile = CurrentProfile;
						// если другой - нужно сбросить миссию...
						CurrentMission = Setup.Profile[CurrentProfile].LastMission;
						ComBuffer = MISSION;
					}


					SetRect(&DstRect,X1+2,Y1-233+46*i,X1+748,Y1-235+46+46*i);
					if (CurrentProfile != i)
						vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/MENU/whitepoint.tga"), true, 0.1f*MenuContentTransp);
				}
				else
				{
					// переход по 2-му клику
					if (vw_GetWindowLBDoubleMouse(true))
					{
						ComBuffer = MISSION;
					}
				}
			}

		}
		else
		{
			float transp = 0.3f;
			vw_DrawFont(X1+10, TmpY, 0, 0, 1.0f, 1.0f,1.0f,1.0f, transp*MenuContentTransp, "%i.",i+1);
			vw_DrawFont(X1+50, TmpY, 0, 0, 1.0f, 1.0f,1.0f,1.0f, transp*MenuContentTransp, vw_GetText("3_empty"));
		}

		TmpY += 46;
	}
	// если не стоим над профайлами - нужно сбросить флаг
	if (TMPSoundOnProfileID == -1) SoundOnProfileID = -1;


	// подсветка выбранного...
	if (CurrentProfile != -1)
	{
		SetRect(&SrcRect,0,0,2,2);
		SetRect(&DstRect,X1+2,Y1-233+46*CurrentProfile,X1+748,Y1-235+46+46*CurrentProfile);
		vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/MENU/whitepoint.tga"), true, 0.1f*MenuContentTransp);
	}








	Y1 += Prir1;


	// кнопка создания дубликата
	Off = true;
	if (CurrentProfile >= 0) Off = false;
	if (DrawButton200_2(X1+6, Y1-6, vw_GetText("1_Duplicate"), MenuContentTransp, Off))
	{
		DuplicateRecord();
	}

	// кнопка удаления записи
	Off = true;
	if (CurrentProfile >= 0) Off = false;
	if (DrawButton128_2(X1+240, Y1-6, vw_GetText("1_Delete"), MenuContentTransp, Off))
	{
		SetCurrentDialogBox(2);
	}


	// кнопка установки сложности
	Off = true;
	if (CurrentProfile >= 0) Off = false;
	if (DrawButton200_2(X1+544, Y1-6, vw_GetText("1_Difficulty"), MenuContentTransp, Off))
	{
		ComBuffer = DIFFICULTY;
	}



	int X = Setup.iAspectRatioWidth/2 - 284;
	int Y = 165+100*5;
	if (DrawButton256(X,Y, vw_GetText("1_MAIN_MENU"), MenuContentTransp, &Button10Transp, &LastButton10UpdateTime))
	{
		ComBuffer = MAIN_MENU;
	}
	Off = true;
	if (CurrentProfile >= 0) Off = false;
	X = Setup.iAspectRatioWidth/2 + 28;
	if (DrawButton256(X,Y, vw_GetText("1_MISSIONS_LIST"), MenuContentTransp, &Button11Transp, &LastButton11UpdateTime, Off))
	{
		ComBuffer = MISSION;
	}





}
