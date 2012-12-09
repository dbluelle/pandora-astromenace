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




float CreditsCurrentPos = 0.0f;
float LastCreditsCurrentPosUpdateTime = 0.0f;




void CreditsMenu()
{

	// делаем движение
	CreditsCurrentPos -= 40.0f*(vw_GetTime() - LastCreditsCurrentPosUpdateTime);
	LastCreditsCurrentPosUpdateTime = vw_GetTime();

	// зацикливание
	if (CreditsCurrentPos <= -3340) CreditsCurrentPos = 0.0f;




	RECT SrcRest, DstRest;


	int Y1 = 690+(int)CreditsCurrentPos;
	int Y2 = 690+25+(int)CreditsCurrentPos;
	int Offset1 = 25;
	int Offset2 = 90;


	float ttt = 0.0f;

	int SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_PROJECT_LEADER")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_PROJECT_LEADER"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Michael_Kurinnoy")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Michael_Kurinnoy"));



	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_2D_ARTWORK")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_2D_ARTWORK"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Tatiana_Savitskaya")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Tatiana_Savitskaya"));


	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_3D_MODELS")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_3D_MODELS"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Max_Shelekhov")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Max_Shelekhov"));

	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Oleg_Linkov")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Oleg_Linkov"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Egor_Kurteanu")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Egor_Kurteanu"));




	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_PLANETARY_TEXTURES")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_PLANETARY_TEXTURES"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Alex_(Esgaroth)_Reuter")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Alex_(Esgaroth)_Reuter"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Robert_Stein")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Robert_Stein"));





	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_MUSIC")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_MUSIC"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Alexander_Matchugovsky")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Alexander_Matchugovsky"));


	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_SOUND_EFFECTS")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_SOUND_EFFECTS"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Michael_Sirotkin")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Michael_Sirotkin"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Alexander_Matchugovsky")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Alexander_Matchugovsky"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Alexander_Vassilyevsky")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Alexander_Vassilyevsky"));


	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_VOICE")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_VOICE"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Petra_Schulten_(de)")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Petra_Schulten_(de)"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Elena_Zavalishina_(en,_ru)")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Elena_Zavalishina_(en,_ru)"));







	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_WEB_PROGRAMMING")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_WEB_PROGRAMMING"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Pavel_Voylov")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Pavel_Voylov"));



	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_TRANSLATORS")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_TRANSLATORS"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Bernd_Dau_(de)")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Bernd_Dau_(de)"));

	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Michael_Kurinnoy_(en,_ru)")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Michael_Kurinnoy_(en,_ru)"));


	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_TESTERS")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_TESTERS"));
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Dmitriy_Schigolev")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Dmitriy_Schigolev"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Ivan_Bobrov")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Ivan_Bobrov"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Vadim_Sosenko")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Vadim_Sosenko"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Dmitriy_Tatarinov")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Dmitriy_Tatarinov"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Alexey_Mosesov")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Alexey_Mosesov"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Bernd_Dau")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Bernd_Dau"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Ryan_Foster")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Ryan_Foster"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Jason_Crowell")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Jason_Crowell"));


	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_SPECIAL_THANKS_TO")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_SPECIAL_THANKS_TO"));
	// система частиц + хорошие объяснения позволили быстро сделать свою
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Richard_Benson")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Richard_Benson"));
	Y1 += Offset1;
	Y2 += Offset1;
	// помогал с железом
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Alexey_Madalinskiy")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Alexey_Madalinskiy"));
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Olga_Zhuravleva")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Olga_Zhuravleva"));
	Y1 += Offset1;
	Y2 += Offset1;
	// выбор названия игры
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Nick_OConnell")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Nick_OConnell"));
	Y1 += Offset1;
	Y2 += Offset1;
	// помог с mac os x версией
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_Mikhail_Storcheous")))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, vw_GetText("10_Mikhail_Storcheous"));




	Y1 += Offset2;
	Y2 += Offset2;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("TTF FONTS"))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, "TTF FONTS");

	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("Ubuntu Font Family (http://font.ubuntu.com)"))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Ubuntu Font Family (http://font.ubuntu.com)");
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("Copyright © 2010,2011 Canonical Ltd."))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Copyright © 2010,2011 Canonical Ltd.");


	Y1 += Offset1+15;
	Y2 += Offset1+15;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("GNU FreeFont (http://www.gnu.org/software/freefont)"))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "GNU FreeFont (http://www.gnu.org/software/freefont)");
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("Free Software Foundation."))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Free Software Foundation.");


	Y1 += Offset1+15;
	Y2 += Offset1+15;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("Liberation (https://fedorahosted.org/liberation-fonts)"))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Liberation (https://fedorahosted.org/liberation-fonts)");
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("Sponsored by Red Hat."))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Sponsored by Red Hat.");





	Y1 += Offset2+10;
	Y2 += Offset2+10;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_POWERED_BY")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_POWERED_BY"));

	int LogoX = Setup.iAspectRatioWidth/2 - 222;
	int LogoTextX = Setup.iAspectRatioWidth/2 - 72;

	// SDL
	Y1 += Offset1-20;
	Y2 += Offset1-20;
	SetRect(&SrcRest,0,0,128,64);
	SetRect(&DstRest,LogoX,Y2,LogoX+128,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/sdl.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Simple DirectMedia Layer");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://www.libsdl.org");


	// OpenGL
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SetRect(&SrcRest,0,0,128,64);
	SetRect(&DstRest,LogoX,Y2,LogoX+128,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/opengl.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Open Graphics Library");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://www.opengl.org");


	// OpenAL
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SetRect(&SrcRest,0,0,128,64);
	SetRect(&DstRest,LogoX,Y2,LogoX+128,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/openal.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Open Audio Library");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://www.openal.org");



	// FreeType
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SetRect(&SrcRest,0,0,128,64);
	SetRect(&DstRest,LogoX,Y2,LogoX+128,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/freetype.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "FreeType2");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://www.freetype.org");


	// ogg vorbis
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SetRect(&SrcRest,0,0,64,64);
	SetRect(&DstRest,LogoX+32,Y2,LogoX+32+64,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/oggvorbis.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Ogg Vorbis");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://www.vorbis.com");






	Y1 += Offset2+10;
	Y2 += Offset2+10;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize(vw_GetText("10_DEVELOPING_WITH")))/2;
	if (Y1 > 300) {ttt = (650 - Y1) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y1 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y1, 0, 0, 1.0f, 1.0f,1.0f,0.0f, ttt*MenuContentTransp, vw_GetText("10_DEVELOPING_WITH"));

	// Code::Blocks
	Y1 += Offset1-20;
	Y2 += Offset1-20;
	SetRect(&SrcRest,0,0,64,64);
	SetRect(&DstRest,LogoX+32,Y2,LogoX+32+64,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/codeblocks.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Code::Blocks IDE");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://www.codeblocks.org");

	// gcc
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SetRect(&SrcRest,0,0,64,64);
	SetRect(&DstRest,LogoX+32,Y2,LogoX+32+64,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/gnugcc.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "GNU GCC Compiler Collection");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://gcc.gnu.org");


	// svn
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SetRect(&SrcRest,0,0,64,64);
	SetRect(&DstRest,LogoX+32,Y2,LogoX+32+64,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/svn.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Subversion");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://subversion.apache.org");


	// gentoo
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SetRect(&SrcRest,0,0,64,64);
	SetRect(&DstRest,LogoX+32,Y2,LogoX+32+64,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/gentoo.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Gentoo Linux");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://www.gentoo.org");


	// gimp
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SetRect(&SrcRest,0,0,64,64);
	SetRect(&DstRest,LogoX+32,Y2,LogoX+32+64,Y2+64);
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA/CREDITS/gimp.tga"), true, ttt*MenuContentTransp);

	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "GIMP ");
	Y1 += Offset1;
	Y2 += Offset1;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(LogoTextX, Y2+5, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://www.gimp.org");



	// GIMP normalmap plugin
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("GIMP normalmap plugin"))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "GIMP normalmap plugin");
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("http://code.google.com/p/gimp-normalmap"))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://code.google.com/p/gimp-normalmap");



	// Spacescape
	Y1 += Offset1+20;
	Y2 += Offset1+20;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("Spacescape"))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Spacescape");
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("http://sourceforge.net/projects/spacescape"))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://sourceforge.net/projects/spacescape");





	// логотип и копирайт
	Y1 += Offset2+30;
	Y2 += Offset2+30;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("Copyright © 2007-2012, Viewizard"))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "Copyright © 2007-2012, Viewizard");
	Y1 += Offset1;
	Y2 += Offset1;
	SizeI = (Setup.iAspectRatioWidth-vw_FontSize("http://www.viewizard.com"))/2;
	if (Y2 > 300) {ttt = (650 - Y2) /100.0f; if (ttt > 1.0f) ttt = 1.0f;}
	else {ttt = (Y2 - 100) /100.0f; if (ttt < 0.0f) ttt = 0.0f;}
	vw_DrawFont(SizeI, Y2, 0, 0, 1.0f, 1.0f,1.0f,1.0f, ttt*MenuContentTransp, "http://www.viewizard.com");






	int	X = Setup.iAspectRatioWidth/2 - 256 - 38;
	int Y = 165+100*5;

	if (DrawButton256(X,Y, vw_GetText("1_MAIN_MENU"), MenuContentTransp, &Button10Transp, &LastButton10UpdateTime))
	{
		ComBuffer = MAIN_MENU;
	}
	X = Setup.iAspectRatioWidth/2 + 38;
	if (DrawButton256(X,Y, vw_GetText("1_DONATE"), MenuContentTransp, &Button11Transp, &LastButton11UpdateTime))
	{
		// нужно свернуть игру, запустить броузер и выйти в основное меню
		SDL_WM_IconifyWindow();

		switch (Setup.MenuLanguage)
		{
			case 1: //en
				vw_OpenBrouser("http://www.viewizard.com/astromenace/donors.php");
				break;
			case 2: //de
				vw_OpenBrouser("http://www.viewizard.com/de/astromenace/donors.php");
				break;
			case 3: //ru
				vw_OpenBrouser("http://www.viewizard.com/ru/astromenace/donors.php");
				break;
		}

		ComBuffer = MAIN_MENU;
	}

}
