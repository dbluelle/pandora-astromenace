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


const char *ButtonGameWeaponInfoType[4] =
{"3_Full",
"3_Flat",
"3_Slim",
"1_Off"};







void CreateMenuLanguageEntryLinks()
{

	switch (Setup.MenuLanguage)
	{
		default: //en
			vw_CreateEntryLinkVFS("DATA/DATA_EN/GAME/mission.tga", "DATA/GAME/mission.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/GAME/missionfailed.tga", "DATA/GAME/missionfailed.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/GAME/pause.tga", "DATA/GAME/pause.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/MENU/button_weaponry_in.tga", "DATA/MENU/button_weaponry_in.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/MENU/button_weaponry_out.tga", "DATA/MENU/button_weaponry_out.tga");
			break;

		case 2: //de
			vw_CreateEntryLinkVFS("DATA/DATA_DE/GAME/mission.tga", "DATA/GAME/mission.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/GAME/missionfailed.tga", "DATA/GAME/missionfailed.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/GAME/pause.tga", "DATA/GAME/pause.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/MENU/button_weaponry_in.tga", "DATA/MENU/button_weaponry_in.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/MENU/button_weaponry_out.tga", "DATA/MENU/button_weaponry_out.tga");
			break;

		case 3: //ru
			vw_CreateEntryLinkVFS("DATA/DATA_RU/GAME/mission.tga", "DATA/GAME/mission.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/GAME/missionfailed.tga", "DATA/GAME/missionfailed.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/GAME/pause.tga", "DATA/GAME/pause.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/MENU/button_weaponry_in.tga", "DATA/MENU/button_weaponry_in.tga");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/MENU/button_weaponry_out.tga", "DATA/MENU/button_weaponry_out.tga");
			break;
	}
	printf("\n");
}

void ReCreateMenuLanguageEntryLinks()
{
	// удаляем все симлинки текстур
	vw_DeleteEntryLinkVFS("DATA/GAME/mission.tga");
	vw_DeleteEntryLinkVFS("DATA/GAME/missionfailed.tga");
	vw_DeleteEntryLinkVFS("DATA/GAME/pause.tga");
	vw_DeleteEntryLinkVFS("DATA/MENU/button_weaponry_in.tga");
	vw_DeleteEntryLinkVFS("DATA/MENU/button_weaponry_out.tga");

	// создаем новые симлинки
	CreateMenuLanguageEntryLinks();

	// если текстура была загружена - выгружаем, и загружаем по новой

	if (vw_FindTextureByName("DATA/GAME/mission.tga"))
	{
		vw_ReleaseTexture(vw_FindTextureByName("DATA/GAME/mission.tga"));
		vw_SetTextureAlpha(0.0f, 0.0f, 0.0f);
		vw_SetTextureProp(RI_MAGFILTER_LINEAR | RI_MINFILTER_LINEAR | RI_MIPFILTER_NONE, RI_CLAMP_TO_EDGE,
						true, TX_ALPHA_EQUAL, false);
		vw_LoadTexture("DATA/GAME/mission.tga", NULL, true);
	}
	if (vw_FindTextureByName("DATA/GAME/missionfailed.tga"))
	{
		vw_ReleaseTexture(vw_FindTextureByName("DATA/GAME/missionfailed.tga"));
		vw_SetTextureAlpha(0.0f, 0.0f, 0.0f);
		vw_SetTextureProp(RI_MAGFILTER_LINEAR | RI_MINFILTER_LINEAR | RI_MIPFILTER_NONE, RI_CLAMP_TO_EDGE,
						true, TX_ALPHA_EQUAL, false);
		vw_LoadTexture("DATA/GAME/missionfailed.tga", NULL, true);
	}
	if (vw_FindTextureByName("DATA/GAME/pause.tga"))
	{
		vw_ReleaseTexture(vw_FindTextureByName("DATA/GAME/pause.tga"));
		vw_SetTextureAlpha(0.0f, 0.0f, 0.0f);
		vw_SetTextureProp(RI_MAGFILTER_LINEAR | RI_MINFILTER_LINEAR | RI_MIPFILTER_NONE, RI_CLAMP_TO_EDGE,
						true, TX_ALPHA_EQUAL, false);
		vw_LoadTexture("DATA/GAME/pause.tga", NULL, true);
	}
	if (vw_FindTextureByName("DATA/MENU/button_weaponry_in.tga"))
	{
		vw_ReleaseTexture(vw_FindTextureByName("DATA/MENU/button_weaponry_in.tga"));
		vw_SetTextureAlpha(0.0f, 0.0f, 0.0f);
		vw_SetTextureProp(RI_MAGFILTER_LINEAR | RI_MINFILTER_LINEAR | RI_MIPFILTER_NONE, RI_CLAMP_TO_EDGE,
						false, TX_ALPHA_EQUAL, false);
		vw_LoadTexture("DATA/MENU/button_weaponry_in.tga", NULL, false);
	}
	if (vw_FindTextureByName("DATA/MENU/button_weaponry_out.tga"))
	{
		vw_ReleaseTexture(vw_FindTextureByName("DATA/MENU/button_weaponry_out.tga"));
		vw_SetTextureAlpha(0.0f, 0.0f, 0.0f);
		vw_SetTextureProp(RI_MAGFILTER_LINEAR | RI_MINFILTER_LINEAR | RI_MIPFILTER_NONE, RI_CLAMP_TO_EDGE,
						false, TX_ALPHA_EQUAL, false);
		vw_LoadTexture("DATA/MENU/button_weaponry_out.tga", NULL, false);
	}
}




void CreateVoiceLanguageEntryLinks()
{

	switch (Setup.VoiceLanguage)
	{
		default: //en
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/Attention.wav", "DATA/VOICE/Attention.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/CeaseFire.wav", "DATA/VOICE/CeaseFire.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/EngineMalfunction.wav", "DATA/VOICE/EngineMalfunction.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/MissileDetected.wav", "DATA/VOICE/MissileDetected.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/PowerSupplyReestablished.wav", "DATA/VOICE/PowerSupplyReestablished.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/PrepareForAction.wav", "DATA/VOICE/PrepareForAction.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/ReactorMalfunction.wav", "DATA/VOICE/ReactorMalfunction.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/Warning.wav", "DATA/VOICE/Warning.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/WeaponDamaged.wav", "DATA/VOICE/WeaponDamaged.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/WeaponDestroyed.wav", "DATA/VOICE/WeaponDestroyed.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_EN/VOICE/WeaponMalfunction.wav", "DATA/VOICE/WeaponMalfunction.wav");
			break;

		case 2: //de
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/Attention.wav", "DATA/VOICE/Attention.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/CeaseFire.wav", "DATA/VOICE/CeaseFire.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/EngineMalfunction.wav", "DATA/VOICE/EngineMalfunction.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/MissileDetected.wav", "DATA/VOICE/MissileDetected.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/PowerSupplyReestablished.wav", "DATA/VOICE/PowerSupplyReestablished.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/PrepareForAction.wav", "DATA/VOICE/PrepareForAction.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/ReactorMalfunction.wav", "DATA/VOICE/ReactorMalfunction.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/Warning.wav", "DATA/VOICE/Warning.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/WeaponDamaged.wav", "DATA/VOICE/WeaponDamaged.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/WeaponDestroyed.wav", "DATA/VOICE/WeaponDestroyed.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_DE/VOICE/WeaponMalfunction.wav", "DATA/VOICE/WeaponMalfunction.wav");
			break;

		case 3: //ru
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/Attention.wav", "DATA/VOICE/Attention.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/CeaseFire.wav", "DATA/VOICE/CeaseFire.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/EngineMalfunction.wav", "DATA/VOICE/EngineMalfunction.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/MissileDetected.wav", "DATA/VOICE/MissileDetected.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/PowerSupplyReestablished.wav", "DATA/VOICE/PowerSupplyReestablished.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/PrepareForAction.wav", "DATA/VOICE/PrepareForAction.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/ReactorMalfunction.wav", "DATA/VOICE/ReactorMalfunction.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/Warning.wav", "DATA/VOICE/Warning.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/WeaponDamaged.wav", "DATA/VOICE/WeaponDamaged.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/WeaponDestroyed.wav", "DATA/VOICE/WeaponDestroyed.wav");
			vw_CreateEntryLinkVFS("DATA/DATA_RU/VOICE/WeaponMalfunction.wav", "DATA/VOICE/WeaponMalfunction.wav");
			break;
	}
	printf("\n");
}

void ReCreateVoiceLanguageEntryLinks()
{
	// удаляем все симлинки голосовых файлов
	vw_DeleteEntryLinkVFS("DATA/VOICE/Attention.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/CeaseFire.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/EngineMalfunction.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/MissileDetected.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/PowerSupplyReestablished.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/PrepareForAction.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/ReactorMalfunction.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/Warning.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/WeaponDamaged.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/WeaponDestroyed.wav");
	vw_DeleteEntryLinkVFS("DATA/VOICE/WeaponMalfunction.wav");

	// чистим все что было загружено из голосовых файлов в буферы
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/Attention.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/CeaseFire.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/EngineMalfunction.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/MissileDetected.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/PowerSupplyReestablished.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/PrepareForAction.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/ReactorMalfunction.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/Warning.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/WeaponDamaged.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/WeaponDestroyed.wav"));
	vw_ReleaseBuffer(vw_FindBufferByName("DATA/VOICE/WeaponMalfunction.wav"));

	// создаем новые симлинки
	CreateVoiceLanguageEntryLinks();
}







void InterfaceMenu(float ContentTransp, float *ButtonTransp1, float *LastButtonUpdateTime1)
{

	RECT SrcRect, DstRect;
	SetRect(&SrcRect,0,0,2,2);
	SetRect(&DstRect,0,0,Setup.iAspectRatioWidth,768);
	vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/MENU/blackpoint.tga"), true, 0.5f*ContentTransp);

	int X1 = Setup.iAspectRatioWidth/2 - 375;
	int Y1 = 65;
	int Prir1 = 55;



	// выбор языка меню
	vw_DrawFont(X1, Y1, -280, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, vw_GetText("3_Menu_Language"));
	if (DrawButton128_2(X1+300, Y1-6, vw_GetText("1_Prev"), ContentTransp, false))
	{
		Setup.MenuLanguage--;
		if (Setup.MenuLanguage < 1) Setup.MenuLanguage = 3;

		ReCreateMenuLanguageEntryLinks();
		vw_SetTextLanguage(Setup.MenuLanguage-1);
	}
	if (DrawButton128_2(X1+616, Y1-6, vw_GetText("1_Next"), ContentTransp, false))
	{
		Setup.MenuLanguage++;
		if (Setup.MenuLanguage>3) Setup.MenuLanguage = 1;

		ReCreateMenuLanguageEntryLinks();
		vw_SetTextLanguage(Setup.MenuLanguage-1);
	}

	int Size, SizeI;
	switch (Setup.MenuLanguage)
	{
		default:
			Size = vw_FontSize("English");
			SizeI = (170-Size)/2;
			vw_DrawFont(X1+438+SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, "English");
			break;
		case 2:
			Size = vw_FontSize("Deutsch");
			SizeI = (170-Size)/2;
			vw_DrawFont(X1+438+SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, "Deutsch");
			break;
		case 3:
			Size = vw_FontSize("Русский");
			SizeI = (170-Size)/2;
			vw_DrawFont(X1+438+SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, "Русский");
			break;
	}




	// выбор языка голосовых сообщений
	Y1 += Prir1;
	vw_DrawFont(X1, Y1, -280, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, vw_GetText("3_Voice_Language"));
	if (DrawButton128_2(X1+300, Y1-6, vw_GetText("1_Prev"), ContentTransp, false))
	{
		Setup.VoiceLanguage--;
		if (Setup.VoiceLanguage < 1) Setup.VoiceLanguage = 3;

		ReCreateVoiceLanguageEntryLinks();
	}
	if (DrawButton128_2(X1+616, Y1-6, vw_GetText("1_Next"), ContentTransp, false))
	{
		Setup.VoiceLanguage++;
		if (Setup.VoiceLanguage>3) Setup.VoiceLanguage = 1;

		ReCreateVoiceLanguageEntryLinks();
	}

	switch (Setup.VoiceLanguage)
	{
		default:
			Size = vw_FontSize("English");
			SizeI = (170-Size)/2;
			vw_DrawFont(X1+438+SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, "English");
			break;
		case 2:
			Size = vw_FontSize("Deutsch");
			SizeI = (170-Size)/2;
			vw_DrawFont(X1+438+SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, "Deutsch");
			break;
		case 3:
			Size = vw_FontSize("Русский");
			SizeI = (170-Size)/2;
			vw_DrawFont(X1+438+SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, "Русский");
			break;
	}



	// выбор шрифта
	Y1 += Prir1;
	vw_DrawFont(X1, Y1, -280, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, vw_GetText("3_Menu_Font"));
	if (DrawButton128_2(X1+300, Y1-6, vw_GetText("1_Prev"), ContentTransp, Setup.FontNumber <= 0))
	{
		Setup.FontNumber --;
		if (Setup.FontNumber < 0) Setup.FontNumber = 0;

		// удаляем все символы и их текстуры
		vw_ReleaseAllFontCharsWithTextures();
		// инициализируем новый шрифт, вызывать vw_ShutdownFont не нужно
		vw_InitFont(FontList[Setup.FontNumber].FontFileName);
		vw_SetFontSize(Setup.FontSize);
		vw_SetFontOffsetY(8 - ceil(Setup.FontSize/2.0f) + 2);
		vw_GenerateFontChars(Setup.FontSize > 16 ? 512 : 256, 256, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+\():;%&`'*#$=[]@^{}_~><–—«»“”|абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЧЦШЩЪЫЬЭЮЯ©®ÄÖÜäöüß°§/");
	}
	if (DrawButton128_2(X1+616, Y1-6, vw_GetText("1_Next"), ContentTransp, Setup.FontNumber >= FontQuantity-1))
	{
		Setup.FontNumber ++;
		if (Setup.FontNumber > FontQuantity-1) Setup.FontNumber = FontQuantity-1;

		// удаляем все символы и их текстуры
		vw_ReleaseAllFontCharsWithTextures();
		// инициализируем новый шрифт, вызывать vw_ShutdownFont не нужно
		vw_InitFont(FontList[Setup.FontNumber].FontFileName);
		vw_SetFontSize(Setup.FontSize);
		vw_SetFontOffsetY(8 - ceil(Setup.FontSize/2.0f) + 2);
		vw_GenerateFontChars(Setup.FontSize > 16 ? 512 : 256, 256, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+\():;%&`'*#$=[]@^{}_~><–—«»“”|абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЧЦШЩЪЫЬЭЮЯ©®ÄÖÜäöüß°§/");
	}
	int Scale = 0;
	Size = vw_FontSize(FontList[Setup.FontNumber].FontTitle);
	if (Size > 170)
	{
		Scale = -170;
		Size = 170;
	}
	SizeI = (170-Size)/2;
	vw_DrawFont(X1+438+SizeI, Y1, Scale, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, FontList[Setup.FontNumber].FontTitle);




	// выбор размера шрифта
	Y1 += Prir1;
	vw_DrawFont(X1, Y1, -280, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, vw_GetText("3_Font_Size"));
	if (DrawButton128_2(X1+300, Y1-6, vw_GetText("1_Prev"), ContentTransp, Setup.FontSize <= 14))
	{
		Setup.FontSize --;
		if (Setup.FontSize < 14) Setup.FontSize = 14;

		// удаляем все символы и их текстуры
		vw_ReleaseAllFontCharsWithTextures();
		// инициализируем новый шрифт, вызывать vw_ShutdownFont не нужно
		vw_InitFont(FontList[Setup.FontNumber].FontFileName);
		vw_SetFontSize(Setup.FontSize);
		vw_SetFontOffsetY(8 - ceil(Setup.FontSize/2.0f) + 2);
		vw_GenerateFontChars(Setup.FontSize > 16 ? 512 : 256, 256, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+\():;%&`'*#$=[]@^{}_~><–—«»“”|абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЧЦШЩЪЫЬЭЮЯ©®ÄÖÜäöüß°§/");
	}
	if (DrawButton128_2(X1+616, Y1-6, vw_GetText("1_Next"), ContentTransp, Setup.FontSize >= 18))
	{
		Setup.FontSize ++;
		if (Setup.FontSize > 18) Setup.FontSize = 18;

		// удаляем все символы и их текстуры
		vw_ReleaseAllFontCharsWithTextures();
		// инициализируем новый шрифт, вызывать vw_ShutdownFont не нужно
		vw_InitFont(FontList[Setup.FontNumber].FontFileName);
		vw_SetFontSize(Setup.FontSize);
		vw_SetFontOffsetY(8 - ceil(Setup.FontSize/2.0f) + 2);
		vw_GenerateFontChars(Setup.FontSize > 16 ? 512 : 256, 256, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+\():;%&`'*#$=[]@^{}_~><–—«»“”|абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЧЦШЩЪЫЬЭЮЯ©®ÄÖÜäöüß°§/");
	}
	Scale = 0;
	Size = vw_FontSize("%i", Setup.FontSize);
	if (Size > 170)
	{
		Scale = -170;
		Size = 170;
	}
	SizeI = (170-Size)/2;
	vw_DrawFont(X1+438+SizeI, Y1, Scale, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, "%i", Setup.FontSize);






	// сброс подсказок
	Y1 += Prir1;
	vw_DrawFont(X1, Y1, -280, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, vw_GetText("3_Tipsandhints_Status"));
	// узнаем есть ли вообще что ресетить
	bool NeedReset = false;
	for (int i=0; i<10; i++)
		if (!Setup.NeedShowHint[i]) NeedReset = true;
	if (DrawButton128_2((int)X1+458, (int)Y1-6, vw_GetText("3_Reset"), ContentTransp, !NeedReset))
	if (NeedCheck == 0)
	{
		for (int i=0; i<10; i++) Setup.NeedShowHint[i] = true;
	}




	// вкл-выкл отображения счетчика фпс
	Y1 += Prir1;
	vw_DrawFont(X1, Y1, -280, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, vw_GetText("3_FPS_Сounter"));
	if (DrawButton128_2(X1+300, Y1-6, vw_GetText("1_Prev"), ContentTransp, false) || DrawButton128_2(X1+616, Y1-6, vw_GetText("1_Next"), ContentTransp, false))
	{
		Setup.ShowFPS = !Setup.ShowFPS;
	}
	Size = vw_FontSize(Setup.ShowFPS ? vw_GetText("1_On") : vw_GetText("1_Off"));
	SizeI = (170-Size)/2;
	vw_DrawFont(X1+438+SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, Setup.ShowFPS ? vw_GetText("1_On") : vw_GetText("1_Off"));




	// вид панелей с оружием в игре
	Y1 += Prir1;
	vw_DrawFont(X1, Y1, -280, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, vw_GetText("3_Weapon_Panels_View"));
	if (DrawButton128_2(X1+300, Y1-6, vw_GetText("1_Prev"), ContentTransp, Setup.GameWeaponInfoType==1))
	{
		Setup.GameWeaponInfoType--;
		if (Setup.GameWeaponInfoType < 1) Setup.GameWeaponInfoType = 1;
	}
	if (DrawButton128_2(X1+616, Y1-6, vw_GetText("1_Next"), ContentTransp, Setup.GameWeaponInfoType==4))
	{
		Setup.GameWeaponInfoType++;
		if (Setup.GameWeaponInfoType > 4) Setup.GameWeaponInfoType = 4;
	}
	Size = vw_FontSize(vw_GetText(ButtonGameWeaponInfoType[Setup.GameWeaponInfoType-1]));
	SizeI = (170-Size)/2;
	vw_DrawFont(X1+438+SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ContentTransp, vw_GetText(ButtonGameWeaponInfoType[Setup.GameWeaponInfoType-1]));















	int Prir = 100;
	int X;
	int Y = 165+Prir*4;


	X = Setup.iAspectRatioWidth/2 - 366;
	if (DrawButton200_2(X,Y+28, vw_GetText("1_Advanced"), ContentTransp, false))
	{
		if (GameStatus == GAME)
		{
			SetOptionsMenu(OPTIONS_ADVANCED);
			GameMenuStatus = 3;
		}
		else ComBuffer = OPTIONS_ADVANCED;
	}

	X = Setup.iAspectRatioWidth/2 - 100;
	if (DrawButton200_2(X,Y+28, vw_GetText("1_Video_&_Audio"), ContentTransp, false))
	{
		if (GameStatus == GAME)
		{
			SetOptionsMenu(OPTIONS);
			GameMenuStatus = 2;
		}
		else ComBuffer = OPTIONS;
	}

	X = Setup.iAspectRatioWidth/2 + 166;
	if (DrawButton200_2(X,Y+28, vw_GetText("1_Config_Controls"), ContentTransp, false))
	{
		if (GameStatus == GAME)
		{
			SetOptionsMenu(CONFCONTROL);
			GameMenuStatus = 5;
		}
		else ComBuffer = CONFCONTROL;
	}






	X = (Setup.iAspectRatioWidth - 384)/2;
	Y = Y+Prir;
	if (GameStatus == GAME)
	{
		if (DrawButton384(X,Y, vw_GetText("1_GAME_MENU"), ContentTransp, ButtonTransp1, LastButtonUpdateTime1))
		{
			GameMenuStatus = 1;
		}
	}
	else
	{
		if (DrawButton384(X,Y, vw_GetText("1_MAIN_MENU"), ContentTransp, ButtonTransp1, LastButtonUpdateTime1))
		{
			ComBuffer = MAIN_MENU;
		}
	}
}









