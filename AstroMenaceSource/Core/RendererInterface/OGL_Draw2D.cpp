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


#include "RendererInterface.h"






//------------------------------------------------------------------------------------
// Переход на 2D режима вывода
//------------------------------------------------------------------------------------
void vw_Start2DMode(float nZ1, float nZ2)
{
    // запоминаем состояние флагов
	glPushAttrib(GL_ENABLE_BIT);
    // и выключаем "ненужные"
	glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

	// берем размер вьюпорта
	int X, Y, W, H;
	vw_GetViewport(&X, &Y, &W, &H);

	// переводим его в флоат для расчетов (нужно чтобы результаты были флоат)
	float AWw = W*1.0f;
	float AHw = H*1.0f;

	glMatrixMode(GL_PROJECTION);								//select the projection matrix
	glPushMatrix();												//store the projection matrix
	glLoadIdentity();											//reset the projection matrix

	// смотрим, была ли установка на фиксированный внутренний размер
	float AW;
	float AH;
	bool ASpresent=false;
	ASpresent = vw_GetAspectWH(&AW, &AH);


	if (ASpresent)
		glOrtho(X*(AW/AWw), (X+W)*(AW/AWw), Y*(AH/AHw), (Y+H)*(AH/AHw), nZ1, nZ2);
	else
		glOrtho(0, AWw, 0, AHw, nZ1, nZ2);	//set up an ortho screen

	glMatrixMode(GL_MODELVIEW);				//select the modelview matrix
	glPushMatrix();
	glLoadIdentity();

}



//------------------------------------------------------------------------------------
// Возвращение в обычный (3D) режим вывода
//------------------------------------------------------------------------------------
void vw_End2DMode()
{
	glMatrixMode(GL_MODELVIEW);				//select the modelview matrix
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);			//select the projection matrix
	glPopMatrix();							//restore the old projection matrix

	glMatrixMode(GL_MODELVIEW);				//select the modelview matrix

    // восстанавливаем флаги
	glPopAttrib();
}






//------------------------------------------------------------------------------------
// Прорисовка в 2д
//------------------------------------------------------------------------------------
void vw_Draw(int X, int Y, RECT *SrcRest, eTexture *Tex, bool Alpha, float RotateAngle, int DrawCorner)
{
	if (Tex == 0) return;

	float AW;
	float AH;
	bool ASpresent=false;
	ASpresent = vw_GetAspectWH(&AW, &AH);

	int W, H;
	vw_GetViewport(0, 0, &W, &H);
	float AHw = H*1.0f;

	// Установка текстуры и ее свойств...
	vw_SetTexture(0, Tex);
	vw_SetTextureBlend(Alpha, RI_BLEND_SRCALPHA, RI_BLEND_INVSRCALPHA);


	// Вычисление поправки по У в зависимости от DrawCorner
	// - расположения угла начала координат
	float tmpPosY = 0;
	// изменяем только в случае RI_UL_CORNER
	if (DrawCorner == RI_UL_CORNER)
	{
		if (ASpresent) tmpPosY = (AH - Y - Y - (SrcRest->bottom - SrcRest->top));
		else tmpPosY = (AHw - Y - Y - (SrcRest->bottom - SrcRest->top));
	}


	float ImageHeight = Tex->Height*1.0f;
	float ImageWidth = Tex->Width*1.0f;

	float FrameHeight = (SrcRest->bottom*1.0f)/ImageHeight;
	float FrameWidth = (SrcRest->right*1.0f)/ImageWidth;

	float Yst = (SrcRest->top)/ImageHeight;
	float Xst = (SrcRest->left)/ImageWidth;


	// буфер для последовательности RI_TRIANGLE_STRIP
	// войдет RI_2f_XYZ | RI_2f_TEX
	float *tmp = 0;
	tmp = new float[(2+2)*4]; if (tmp == 0) return;
	int k=0;

	tmp[k++] = X;
	tmp[k++] = Y +tmpPosY + (SrcRest->bottom - SrcRest->top);
	tmp[k++] = Xst;
	tmp[k++] = 1.0f-Yst;

	tmp[k++] = X;
	tmp[k++] = Y +tmpPosY;
	tmp[k++] = Xst;
	tmp[k++] = 1.0f-FrameHeight;

	tmp[k++] = X + (SrcRest->right - SrcRest->left);
	tmp[k++] = Y +tmpPosY + (SrcRest->bottom - SrcRest->top);
	tmp[k++] = FrameWidth;
	tmp[k++] = 1.0f-Yst;

	tmp[k++] = X + (SrcRest->right - SrcRest->left);
	tmp[k++] = Y +tmpPosY;
	tmp[k++] = FrameWidth;
	tmp[k++] = 1.0f-FrameHeight;

	glPushMatrix();
	glRotatef(RotateAngle, 0, 0, 1);

	vw_SendVertices(RI_TRIANGLE_STRIP, 4, RI_2f_XY | RI_1_TEX, tmp, 4*sizeof(float));
	glPopMatrix();


	if (tmp != 0){delete [] tmp; tmp = 0;}
	vw_SetTextureBlend(false, 0, 0);
	vw_BindTexture(0, 0);
}





//------------------------------------------------------------------------------------
// Прорисовка в 2д с прозрачностью
//------------------------------------------------------------------------------------
void vw_DrawTransparent(RECT *DstRest, RECT *SrcRest, eTexture *Tex, bool Alpha, float Transp, float RotateAngle, int DrawCorner, float R, float G, float B)
{

	if (Tex == 0) return;
	if (Transp <= 0.0f) return;
	if (Transp > 1.0f) Transp = 1.0f;

	float AW;
	float AH;
	bool ASpresent=false;
	ASpresent = vw_GetAspectWH(&AW, &AH);

	int W, H;
	vw_GetViewport(0, 0, &W, &H);
	float AHw = H*1.0f;

	int X = DstRest->left;
	int Y = DstRest->top;

	// Установка текстуры и ее свойств...
	vw_SetTexture(0, Tex);
	vw_SetTextureBlend(Alpha, RI_BLEND_SRCALPHA, RI_BLEND_INVSRCALPHA);

	// Вычисление поправки по У в зависимости от DrawCorner
	// - расположения угла начала координат
	float tmpPosY = 0;
	// изменяем только в случае RI_UL_CORNER
	if (DrawCorner == RI_UL_CORNER)
	{
		if (ASpresent) tmpPosY = (AH - Y - Y - (DstRest->bottom - DstRest->top));
		else tmpPosY = (AHw - Y - Y - (DstRest->bottom - DstRest->top));
	}



	float ImageHeight = Tex->Height*1.0f;
	float ImageWidth = Tex->Width*1.0f;

	float FrameHeight = (SrcRest->bottom*1.0f )/ImageHeight;
	float FrameWidth = (SrcRest->right*1.0f )/ImageWidth;

	float Yst = (SrcRest->top*1.0f)/ImageHeight;
	float Xst = (SrcRest->left*1.0f)/ImageWidth;


	vw_SetColor(R, G, B, Transp);

	// буфер для последовательности RI_TRIANGLE_STRIP
	// войдет RI_2f_XYZ | RI_2f_TEX
	float *tmp = 0;
	tmp = new float[(2+2)*4]; if (tmp == 0) return;
	int k=0;

	tmp[k++] = X;
	tmp[k++] = Y +tmpPosY + (DstRest->bottom - DstRest->top);
	tmp[k++] = Xst;
	tmp[k++] = 1.0f-Yst;

	tmp[k++] = X;
	tmp[k++] = Y +tmpPosY;
	tmp[k++] = Xst;
	tmp[k++] = 1.0f-FrameHeight;

	tmp[k++] = X + (DstRest->right - DstRest->left);
	tmp[k++] = Y +tmpPosY + (DstRest->bottom - DstRest->top);
	tmp[k++] = FrameWidth;
	tmp[k++] = 1.0f-Yst;

	tmp[k++] = X + (DstRest->right - DstRest->left);
	tmp[k++] = Y +tmpPosY;
	tmp[k++] = FrameWidth;
	tmp[k++] = 1.0f-FrameHeight;


	glPushMatrix();
	glRotatef(RotateAngle, 0, 0, 1);

	vw_SendVertices(RI_TRIANGLE_STRIP, 4, RI_2f_XY | RI_1_TEX, tmp, 4*sizeof(float));

	glPopMatrix();



	if (tmp != 0){delete [] tmp; tmp = 0;}

	vw_SetTextureBlend(false, 0, 0);
	vw_SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	vw_BindTexture(0, 0);

}
