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


#ifndef CoreSystem_H
#define CoreSystem_H

#include "../Base.h"


// проверка расширения файла (нужен для детекта wav-ogg, tga-jpg...)
bool 	vw_TestFileExtension(const char *name, const char *extension);

// открываем браузер
bool	vw_OpenBrouser(const char *url);



// работа со временем
void 	vw_InitTime();
void 	vw_InitTimeNum(int Num);
float 	vw_GetTime(int TimeThread = 0);
void 	vw_StopTime();
void 	vw_StartTime();
void 	vw_SetTimeThreadSpeed(int TimeThread=0, float NewSpeed=1.0f);
float 	vw_GetTimeThreadSpeed(int TimeThread=0);



// работа с клавиатурой
bool	vw_GetKeys(int Num);
void	vw_SetKeys(int Num, bool NewKeyStatus);
int 	GetMaxKeys();
const char* 	vw_VirtualCodeName(int Language, int Num);
const char* 	vw_KeyboardCodeName(int Num);
int 	vw_KeyboardNameCode(const char * Name);
// установка-получение юникода текущей нажатой клавиши
void 	vw_SetCurrentKeyUnicode(Uint16 NewKeyUnicod);
Uint16 	vw_GetCurrentKeyUnicode();

// работа с мышкой
int		vw_GetMousePos(int *X, int *Y);
bool	vw_GetWindowLBMouse(bool ResetStatus);
bool	vw_GetWindowRBMouse(bool ResetStatus);
void	vw_SetWindowLBMouse(bool NewStatus);
void	vw_SetWindowRBMouse(bool NewStatus);
void 	vw_SetWindowLBDoubleMouse(bool NewStatus);
bool 	vw_GetWindowLBDoubleMouse(bool ResetStatus);
void	vw_ChangeWheelStatus(int Value);
void	vw_ResetWheelStatus();
int		vw_GetWheelStatus();
void	vw_SetMousePos(int X, int Y);
void 	vw_SetMousePosRel(int X, int Y);
bool	vw_OnRect(RECT *MDetect);




#endif // CoreSystem_H
