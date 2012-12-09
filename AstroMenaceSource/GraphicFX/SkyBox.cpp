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




//-----------------------------------------------------------------------------
// local/protected variables
//-----------------------------------------------------------------------------

// SkyBox textures
eTexture *SkyBox_Texture[6]={0,0,0,0,0,0};
// SkyBox location
float SkyBox_x = 0.0f;
float SkyBox_y = 0.0f;
float SkyBox_z = 0.0f;
// SkyBox size
float SkyBox_width_2 = 100.0f;
float SkyBox_height_2 = 100.0f;
float SkyBox_length_2 = 100.0f;






//-----------------------------------------------------------------------------
// Draw all SkyBox sides
//-----------------------------------------------------------------------------
void SkyBoxDraw(void)
{
	int VFV = RI_3f_XYZ | RI_1_TEX;
	float *buff = 0;
	buff = new float[5*4]; if (buff == 0) return;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// The BACK side
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int k=0;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 1.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 1.0f;

	if (SkyBox_Texture[BACK] != 0)
	{
		vw_SetTexture(0, SkyBox_Texture[BACK]);
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
	}
	k=0;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 2.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 2.0f;

	if (SkyBox_Texture[BACK] != 0)
	{
		vw_SetTextureBlend(true, RI_BLEND_SRCALPHA, RI_BLEND_ONE);
		vw_SetTexture(0, vw_FindTextureByName("DATA/SKYBOX/tile_stars.tga"));
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		// по умолчанию всегда трилинейная фильтрация, если надо - ставим билинейную
		if (Setup.TextureFilteringMode == 1) vw_SetTextureFiltering(RI_TEXTURE_BILINEAR);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
		vw_SetTextureBlend(false, 0, 0);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// The FRONT side
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	k=0;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 1.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 1.0f;

	if (SkyBox_Texture[FRONT] != 0)
	{
		vw_SetTexture(0, SkyBox_Texture[FRONT]);
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
	}

	k=0;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 2.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 2.0f;

	if (SkyBox_Texture[FRONT] != 0)
	{
		vw_SetTextureBlend(true, RI_BLEND_SRCALPHA, RI_BLEND_ONE);
		vw_SetTexture(0, vw_FindTextureByName("DATA/SKYBOX/tile_stars.tga"));
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		// по умолчанию всегда трилинейная фильтрация, если надо - ставим билинейную
		if (Setup.TextureFilteringMode == 1) vw_SetTextureFiltering(RI_TEXTURE_BILINEAR);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
		vw_SetTextureBlend(false, 0, 0);
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// The BOTTOM side
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	k=0;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 1.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 1.0f;

	if (SkyBox_Texture[BOTTOM] != 0)
	{
		vw_SetTexture(0, SkyBox_Texture[BOTTOM]);
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
	}

	k=0;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 2.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 2.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 0.0f;

	if (SkyBox_Texture[BOTTOM] != 0)
	{
		vw_SetTextureBlend(true, RI_BLEND_SRCALPHA, RI_BLEND_ONE);
		vw_SetTexture(0, vw_FindTextureByName("DATA/SKYBOX/tile_stars.tga"));
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		// по умолчанию всегда трилинейная фильтрация, если надо - ставим билинейную
		if (Setup.TextureFilteringMode == 1) vw_SetTextureFiltering(RI_TEXTURE_BILINEAR);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
		vw_SetTextureBlend(false, 0, 0);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// The TOP side
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	k=0;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 1.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 1.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;

	if (SkyBox_Texture[TOP] != 0)
	{
		vw_SetTexture(0, SkyBox_Texture[TOP]);
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
	}

	k=0;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 2.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 2.0f;

	if (SkyBox_Texture[TOP] != 0)
	{
		vw_SetTextureBlend(true, RI_BLEND_SRCALPHA, RI_BLEND_ONE);
		vw_SetTexture(0, vw_FindTextureByName("DATA/SKYBOX/tile_stars.tga"));
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		// по умолчанию всегда трилинейная фильтрация, если надо - ставим билинейную
		if (Setup.TextureFilteringMode == 1) vw_SetTextureFiltering(RI_TEXTURE_BILINEAR);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
		vw_SetTextureBlend(false, 0, 0);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// The LEFT side
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	k=0;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 1.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 1.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 0.0f;

	if (SkyBox_Texture[LEFT] != 0)
	{
		vw_SetTexture(0, SkyBox_Texture[LEFT]);
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
	}

	k=0;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 2.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 2.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x - SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;

	if (SkyBox_Texture[LEFT] != 0)
	{
		vw_SetTextureBlend(true, RI_BLEND_SRCALPHA, RI_BLEND_ONE);
		vw_SetTexture(0, vw_FindTextureByName("DATA/SKYBOX/tile_stars.tga"));
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		// по умолчанию всегда трилинейная фильтрация, если надо - ставим билинейную
		if (Setup.TextureFilteringMode == 1) vw_SetTextureFiltering(RI_TEXTURE_BILINEAR);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
		vw_SetTextureBlend(false, 0, 0);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// The RIGHT side
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	k=0;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 1.0f;
	buff[k++] = 1.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 1.0f;

	if (SkyBox_Texture[RIGHT] != 0)
	{
		vw_SetTexture(0, SkyBox_Texture[RIGHT]);
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
	}

	k=0;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y - SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 0.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z - SkyBox_length_2;
	buff[k++] = 0.0f;
	buff[k++] = 2.0f;
	buff[k++] = SkyBox_x + SkyBox_width_2;
	buff[k++] = SkyBox_y + SkyBox_height_2;
	buff[k++] = SkyBox_z + SkyBox_length_2;
	buff[k++] = 2.0f;
	buff[k++] = 2.0f;

	if (SkyBox_Texture[RIGHT] != 0)
	{
		vw_SetTextureBlend(true, RI_BLEND_SRCALPHA, RI_BLEND_ONE);
		vw_SetTexture(0, vw_FindTextureByName("DATA/SKYBOX/tile_stars.tga"));
		vw_SetTextureAnisotropy(Setup.AnisotropyLevel);
		// по умолчанию всегда трилинейная фильтрация, если надо - ставим билинейную
		if (Setup.TextureFilteringMode == 1) vw_SetTextureFiltering(RI_TEXTURE_BILINEAR);
		vw_SendVertices(RI_TRIANGLE_STRIP, 4, VFV, buff, 5*sizeof(float));
		vw_SetTextureBlend(false, 0, 0);
	}



	vw_BindTexture(0, 0);
	if (buff != 0){delete [] buff; buff = 0;}
}





//-----------------------------------------------------------------------------
// Setup texture for each SkyBox side
//-----------------------------------------------------------------------------
void SkyBoxSetTexture(eTexture *nTexture, int Side)
{
	SkyBox_Texture[Side] = nTexture;
}



//-----------------------------------------------------------------------------
// Create SkyBox
//-----------------------------------------------------------------------------
void SkyBoxCreate(float nx, float ny, float nz,
							 float nwidth, float nheight, float nlength)
{
	SkyBox_x = nx;
	SkyBox_y = ny;
	SkyBox_z = nz;
	SkyBox_width_2 = nwidth/2.0f;
	SkyBox_height_2 = nheight/2.0f;
	SkyBox_length_2 = nlength/2.0f;
}
