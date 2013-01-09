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


#ifndef Base_H
#define Base_H

#include "../config.h"



#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#define _CRT_SECURE_NO_DEPRECATE // выключаем задалбывание с безопасными функциями
	#include <windows.h>
	#include <shellapi.h>
#endif

#if defined(__APPLE__) && defined(__MACH__)
	#define __glext_h_  // Don't let gl.h include glext.h
	#include <OpenGL/gl.h>	// Header File For The OpenGL Library
	#include <OpenGL/glu.h>	// Header File For The GLu Library
	#undef __glext_h_
#else
	#define __glext_h_  // Don't let gl.h include glext.h
#ifdef USE_GLES
	#include <GLES/gl.h>
#else
	#include <GL/gl.h>	// Header File For The OpenGL Library
#endif
	#include <GL/glu.h>	// Header File For The GLu Library
	#undef __glext_h_
#endif

#include <stdlib.h> // rand, ...
#include <math.h> // math for core Math


#include "RendererInterface/GLext.h"
#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"
#include "SDL/SDL_syswm.h"
#include "SDL/SDL_endian.h" // для VFS, чтобы правильно считывать таблицу файлов + хранение данных игры

#ifdef USE_GLES
#undef SDL_GL_GetProcAddress
void* SDL_GL_GetProcAddress(const char* name);
#endif



// если не используем переменные, и их нельзя убрать (используем прототип функции, к примеру)
#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif



#if defined(__unix) || (defined(__APPLE__) && defined(__MACH__))

// декларируем типы данных, которых может не быть
#ifndef BYTE
	#define BYTE Uint8
#endif
#ifndef WORD
	#define WORD Uint16
#endif
#ifndef DWORD
	#define DWORD Uint32
#endif
#ifndef BOOL
	#define BOOL bool
#endif

	struct RECT
	{
		int left;
		int top;
		int right;
		int bottom;
	};
	inline void SetRect(RECT *rect, int left, int top, int right, int bottom)
	{
		rect->right = right;
		rect->top = top;
		rect->left = left;
		rect->bottom =bottom;
	}


	#include <valarray> // memcpy
	#include <stdarg.h> // va_start

	#include <sys/stat.h> // mkdir
	#include <sys/types.h> // mkdir


#ifndef MAX_PATH
	#define MAX_PATH 1024
#endif // MAX_PATH


#endif // unix





#endif // Base_H
