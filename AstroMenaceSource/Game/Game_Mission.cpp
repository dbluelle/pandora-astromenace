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


#include "../Game.h"





float MissionTitleLifeTime = 0.0f;
float LastMissionTitleUpdateTime = 0.0f;
int MissionTitleNum = 0;

float MissionFailedLifeTime = 0.0f;
float LastMissionFailedUpdateTime = 0.0f;

extern float CurrentAlert3;


//------------------------------------------------------------------------------------
// установка времени отображения ShowTime миссии номер Num
//------------------------------------------------------------------------------------
void GameSetMissionTitleData(float ShowTime, int Num)
{
	MissionTitleLifeTime = ShowTime;
	LastMissionTitleUpdateTime = vw_GetTime();
	MissionTitleNum = Num;

	// пока ничего не показываем
	MissionFailedLifeTime = 0.0f;
	LastMissionFailedUpdateTime = vw_GetTime();
}




//------------------------------------------------------------------------------------
// считаем, сколько в ширину займет прорисовка номера
//------------------------------------------------------------------------------------
int CheckMissionTitleNum(char *Num)
{
	RECT SrcRect;
	SetRect(&SrcRect,0,0,0,0);
	int XSum = 0;

	// считаем
	for (size_t i=0; i<strlen(Num); i++)
	{
		char Char = Num[i];

		switch (Char)
		{
			case '1':	SetRect(&SrcRect,15,1,48,63); break;
			case '2':	SetRect(&SrcRect,48,1,86,63); break;
			case '3':	SetRect(&SrcRect,86,1,124,63); break;
			case '4':	SetRect(&SrcRect,124,1,160,63); break;
			case '5':	SetRect(&SrcRect,161,1,200,63); break;
			case '6':	SetRect(&SrcRect,200,1,238,63); break;
			case '7':	SetRect(&SrcRect,239,1,275,63); break;
			case '8':	SetRect(&SrcRect,276,1,315,63); break;
			case '9':	SetRect(&SrcRect,319,1,385,63); break;
			case '0':	SetRect(&SrcRect,360,1,399,63); break;
		}

		XSum += SrcRect.right - SrcRect.left;
	}

	return XSum;
}



//------------------------------------------------------------------------------------
// прорисовка номера
//------------------------------------------------------------------------------------
void DrawMissionTitleNum(int X, int Y, char *Num, float Transp)
{
	// здесь X - крайняя левая(!!!) точка
	// Y - крайняя верхняя точка (т.е. как и везде)

	RECT SrcRect, DstRect;
	int XStart = X;


	// рисуем
	for (size_t i=0; i<strlen(Num); i++)
	{
		char Char = Num[i];

		switch (Char)
		{
			case '1':	SetRect(&SrcRect,15,1,48,63); break;
			case '2':	SetRect(&SrcRect,48,1,86,63); break;
			case '3':	SetRect(&SrcRect,86,1,124,63); break;
			case '4':	SetRect(&SrcRect,124,1,160,63); break;
			case '5':	SetRect(&SrcRect,161,1,200,63); break;
			case '6':	SetRect(&SrcRect,200,1,238,63); break;
			case '7':	SetRect(&SrcRect,239,1,275,63); break;
			case '8':	SetRect(&SrcRect,276,1,315,63); break;
			case '9':	SetRect(&SrcRect,319,1,355,63); break;
			case '0':	SetRect(&SrcRect,360,1,399,63); break;
		}


		SetRect(&DstRect,XStart,Y,XStart+(SrcRect.right - SrcRect.left),Y+(SrcRect.bottom - SrcRect.top));
		vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/GAME/nums.tga"), true, Transp);
		XStart += SrcRect.right - SrcRect.left;
	}

}





//------------------------------------------------------------------------------------
// прорисовка номера миссии
//------------------------------------------------------------------------------------
void GameDrawMissionTitle()
{
	// нам тут делать нечего
	if (MissionTitleLifeTime <= 0.0f) return;

	float TimeDelta = vw_GetTime() - LastMissionTitleUpdateTime;
	LastMissionTitleUpdateTime = vw_GetTime();

	MissionTitleLifeTime -= TimeDelta;


	RECT SrcRect, DstRect;

	// преобразовываем число в строку
	char buffer[10];
	itoa10(MissionTitleNum, buffer);


	// вывод надписи Mission

	// считаем сколько в ширину надпись всего... 30 - пробел между надписью и номером
	int TotalW = 226+20+CheckMissionTitleNum(buffer);
	// находим откуда начинать рисовать
	int XStart = (Setup.iAspectRatioWidth-TotalW)/2;

	SetRect(&SrcRect,0,0,226,64);
	SetRect(&DstRect,XStart,352,XStart+226,352+64);

	if (MissionTitleLifeTime >= 1.0f)
	{
		vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/GAME/mission.tga"),
			true, 1.0f, 0.0f, RI_UL_CORNER, 1.0f, 1.0f, 1.0f);
		// вывод номера миссии
		DrawMissionTitleNum(XStart+226+20, 352+1, buffer, 1.0f);
	}
	else
	{
		vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/GAME/mission.tga"),
			true, MissionTitleLifeTime, 0.0f, RI_UL_CORNER, 1.0f, 1.0f, 1.0f);
		// вывод номера миссии
		DrawMissionTitleNum(XStart+226+20, 352+1, buffer, MissionTitleLifeTime);
	}


}






//------------------------------------------------------------------------------------
// установка времени отображения ShowTime миссия провалена
//------------------------------------------------------------------------------------
void GameSetMissionFailedData(float ShowTime)
{
	MissionFailedLifeTime = ShowTime;
	LastMissionFailedUpdateTime = vw_GetTime();
	// выводим курсор
	DrawGameCursor = true;
	// сброс кнопки мышки, чтобы случайно не нажали
	vw_GetWindowLBMouse(true);
}


//------------------------------------------------------------------------------------
// прорисовка миссия провалена
//------------------------------------------------------------------------------------
void GameDrawMissionFailed()
{
	// нам тут делать нечего
	if (MissionFailedLifeTime <= 0.0f) return;

	float TimeDelta = vw_GetTime() - LastMissionFailedUpdateTime;
	LastMissionFailedUpdateTime = vw_GetTime();

	// считаем только если не отображается меню
	if (GameContentTransp <= 0.0f)
		MissionFailedLifeTime -= TimeDelta;

	// все, время вышло... нужно сделать сброс и загрузить меню
	if (MissionFailedLifeTime <= 0.0f)
	{
		ComBuffer = 100;
		ExitGame();
	}

	RECT SrcRect, DstRect;

	// вывод надписи Mission
	SetRect(&SrcRect,0,0,512,84);
	SetRect(&DstRect,Setup.iAspectRatioWidth/2-256,342,Setup.iAspectRatioWidth/2+256,342+84);

	vw_DrawTransparent(&DstRect, &SrcRect, vw_FindTextureByName("DATA/GAME/missionfailed.tga"),
		true, 1.0f, 0.0f, RI_UL_CORNER, 1.0f, 1.0f, 1.0f);


	// выводим кнопки...

	int Y = 180+270;

	int X = Setup.iAspectRatioWidth/2 - 230;
	if (DrawButton200_2(X,Y, vw_GetText("1_QUIT"), 1.0f, false))
	{
		ComBuffer = 101;
		ExitGame();
	}


	X = Setup.iAspectRatioWidth/2 + 30;
	if (DrawButton200_2(X,Y, vw_GetText("1_RESTART"), 1.0f, false))
	{
		ComBuffer = GAME;
		ExitGame();
	}

}


