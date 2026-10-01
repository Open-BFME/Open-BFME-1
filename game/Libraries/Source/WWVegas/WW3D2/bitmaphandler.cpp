// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "bitmaphandler.h"
#include "wwdebug.h"
#include "colorspace.h"

void Bitmap_Assert(bool condition)
{
	WWASSERT(condition);
}

// ?Create_Mipmap_B8G8R8A8@BitmapHandlerClass@@SAXPAEI0III@Z present-unmatched
void BitmapHandlerClass::Create_Mipmap_B8G8R8A8(
	unsigned char* dest_surface, 
	unsigned dest_surface_pitch,
	unsigned char* src_surface,
	unsigned src_surface_pitch,
	unsigned width,
	unsigned height)
{
	unsigned src_pitch=src_surface_pitch/4;
	for (unsigned y=0;y<height;y+=2) {
		unsigned* dest=(unsigned*)dest_surface;
		dest_surface+=dest_surface_pitch;
		unsigned* src=(unsigned*)src_surface;
		src_surface+=src_surface_pitch;
		for (unsigned x=0;x<width;x+=2) {
			unsigned bgra3=src[src_pitch];
			unsigned bgra1=*src++;
			unsigned bgra4=src[src_pitch];
			unsigned bgra2=*src++;
			*dest++=Combine_A8R8G8B8(bgra1,bgra2,bgra3,bgra4);
		}
	}
}

// These header bodies are retail-verified in this TU. Keep their emitted
// copies without compiling the unverified Zero Hour image-copy routines.
#pragma inline_depth(0)
// ?Rva00929100EmitBitmapColors@@YAIIPAVVector3@@PBV1@ABVVector4@@@Z present-unmatched
unsigned Rva00929100EmitBitmapColors(unsigned packed, Vector3 *result,
    const Vector3 *input, const Vector4 &rgba)
{
    RGB_To_HSV(*result, *input);
    HSV_To_RGB(*result, *input);
    Vector4 decoded = DX8Wrapper::Convert_Color(packed);
    Vector4 copied(rgba);
    return DX8Wrapper::Convert_Color(decoded) +
        DX8Wrapper::Convert_Color(*input, copied[3]);
}
#pragma inline_depth()
