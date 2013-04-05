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


#include "Texture.h"


typedef char				PVRTchar8;
typedef signed char			PVRTint8;
typedef signed short		PVRTint16;
typedef signed int			PVRTint32;
typedef unsigned char		PVRTuint8;
typedef unsigned short		PVRTuint16;
typedef unsigned int		PVRTuint32;

typedef float				PVRTfloat32;

#if (defined(__int64) || defined(_WIN32))
typedef signed __int64     PVRTint64;
typedef unsigned __int64   PVRTuint64;
#elif defined(TInt64)
typedef TInt64             PVRTint64;
typedef TUInt64            PVRTuint64;
#else
typedef signed long long   PVRTint64;
typedef unsigned long long PVRTuint64;
#endif
union PixelType
{
	struct LowHigh
	{
		PVRTuint32 Low;
		PVRTuint32 High;
	} Part;
	PVRTuint64 PixelTypeID;
	PVRTuint8 PixelTypeChar[8];
};
enum EPVRTPixelFormat
{
	ePVRTPF_PVRTCI_2bpp_RGB,
	ePVRTPF_PVRTCI_2bpp_RGBA,
	ePVRTPF_PVRTCI_4bpp_RGB,
	ePVRTPF_PVRTCI_4bpp_RGBA,
	ePVRTPF_PVRTCII_2bpp,
	ePVRTPF_PVRTCII_4bpp,
	ePVRTPF_ETC1,
	ePVRTPF_DXT1,
	ePVRTPF_DXT2,
	ePVRTPF_DXT3,
	ePVRTPF_DXT4,
	ePVRTPF_DXT5,

	//These formats are identical to some DXT formats.
	ePVRTPF_BC1 = ePVRTPF_DXT1,
	ePVRTPF_BC2 = ePVRTPF_DXT3,
	ePVRTPF_BC3 = ePVRTPF_DXT5,

	//These are currently unsupported:
	ePVRTPF_BC4,
	ePVRTPF_BC5,
	ePVRTPF_BC6,
	ePVRTPF_BC7,

	//These are supported
	ePVRTPF_UYVY,
	ePVRTPF_YUY2,
	ePVRTPF_BW1bpp,
	ePVRTPF_SharedExponentR9G9B9E5,
	ePVRTPF_RGBG8888,
	ePVRTPF_GRGB8888,
	ePVRTPF_ETC2_RGB,
	ePVRTPF_ETC2_RGBA,
	ePVRTPF_ETC2_RGB_A1,
	ePVRTPF_EAC_R11,
	ePVRTPF_EAC_RG11,

	//Invalid value
	ePVRTPF_NumCompressedPFs
};

#pragma pack(push,4)
struct PVRTextureHeaderV3{
	PVRTuint32	u32Version;			//Version of the file header, used to identify it.
	PVRTuint32	u32Flags;			//Various format flags.
	PVRTuint64	u64PixelFormat;		//The pixel format, 8cc value storing the 4 channel identifiers and their respective sizes.
	PVRTuint32	u32ColourSpace;		//The Colour Space of the texture, currently either linear RGB or sRGB.
	PVRTuint32	u32ChannelType;		//Variable type that the channel is stored in. Supports signed/unsigned int/short/byte or float for now.
	PVRTuint32	u32Height;			//Height of the texture.
	PVRTuint32	u32Width;			//Width of the texture.
	PVRTuint32	u32Depth;			//Depth of the texture. (Z-slices)
	PVRTuint32	u32NumSurfaces;		//Number of members in a Texture Array.
	PVRTuint32	u32NumFaces;		//Number of faces in a Cube Map. Maybe be a value other than 6.
	PVRTuint32	u32MIPMapCount;		//Number of MIP Maps in the texture - NB: Includes top level.
	PVRTuint32	u32MetaDataSize;	//Size of the accompanying meta data.
};
#pragma pack(pop)
int ReadPVR(BYTE **DIB, eFILE *pFile, int *DWidth, int *DHeight, int *DChanels)
{
	PVRTextureHeaderV3* header = new PVRTextureHeaderV3();
	pFile->fread(header, sizeof(PVRTextureHeaderV3), 1);
	int len = pFile->RealLength - (sizeof(PVRTextureHeaderV3)+header->u32MetaDataSize);
	pFile->fseek(header->u32MetaDataSize,SEEK_CUR);

	*DIB = new BYTE[len];
	pFile->fread(*DIB, sizeof(BYTE), len);

	*DWidth = header->u32Width;
	*DHeight = header->u32Height;
		 
	*DChanels = header->u64PixelFormat == 1 ? 4 : 3;
	
	delete header;
}

