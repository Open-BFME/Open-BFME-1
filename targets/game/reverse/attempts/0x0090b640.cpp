// ?Shutdown@DX8Wrapper@@SAXXZ
// partial score=0.97 date=2026-09-27
// cl: /Iinputs/reference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// Open-BFME8: DX8Wrapper::Shutdown, retail 0x0090B640, 408 bytes (the body ends
// on the ret at +0x197, so 0x198 not the 0x408 the lift claimed; the following
// Set_Any_Render_Device body starts at 0x0090B7E0).
//
// The Zero Hour body at inputs/reference/.../dx8wrapper.cpp:325 with three BFME
// differences, each read straight out of the retail bytes:
//  - retail calls the device-release helper at 0x00907B00 where Zero Hour spells
//    it Release_Device(); the ledger pins that body as ?d_00907b00@@YAXXZ (see
//    Rva00907B00ReleaseDevice.cpp), so it is called under that name here.
//  - retail tears the heap-allocated mesh renderer down at the tail
//    (TheDX8MeshRenderer = 0x0134B0E8 is a DX8MeshRendererClass* in BFME, the
//    same form DX8Wrapper_Do_Onetime_Device_Dependent_Inits.cpp allocates) and
//    does NOT reach Zero Hour's DX8Caps::Shutdown().
//  - retail drops the cap count from DX8Caps+0x278, not +0x124.

#include "dx8wrapper.h"
#include "rddesc.h"
#include "wwstring.h"
#include "vector.h"

// Retail 0x00907B00, the device-release helper Shutdown calls under D3DDevice.
// See Rva00907B00ReleaseDevice.cpp for the recovered body.
void d_00907b00(void);

// BFME allocates the mesh renderer on the heap (see
// DX8Wrapper_Do_Onetime_Device_Dependent_Inits.cpp) and its destructor is the
// one compiled in DX8MeshRendererDestructorNothrow.cpp, so the class is renamed
// by macro exactly as that TU does.
#define DX8MeshRendererClass Rva00949D00Renderer
class Rva00949D00Renderer
{
public:
	~Rva00949D00Renderer();
};
extern Rva00949D00Renderer *TheDX8MeshRenderer;

extern HINSTANCE D3D8Lib;

// The three render-device tables, laid out by retail at VA 0x01341134,
// 0x013411D4 and 0x013405EC with no recovered name of their own. The three
// Clear sequences below carry the element sizes 4, 4 and 0x5b8 and the element
// destructors of StringClass, StringClass and RenderDeviceDescClass, which is
// the Zero Hour declaration order (name / short name / description), so the
// names here stay address-keyed.
DynamicVectorClass<StringClass> Rva01341134DeviceNameTable;
DynamicVectorClass<StringClass> Rva013411D4DeviceShortNameTable;
DynamicVectorClass<RenderDeviceDescClass> Rva013405ECDeviceDescriptionTable;

// BFME's DX8Caps is 0x2ac bytes and the recovered header layout stops at 0x154,
// so the trailing fields live in the header's unrecovered tail. The int at
// +0x278 is MaxTexturesPerPass: dx8caps.cpp's BFME overlay reads it there
// between the isFogAllowed byte and the 0x27c/0x280/0x284 shader-version words
// that Check_Maximum_Texture_Support is matched against.
struct BfmeDX8CapsMaxTexturesView
{
	char unused[0x278];
	int max_textures;
};

// ?Shutdown@DX8Wrapper@@SAXXZ
void DX8Wrapper::Shutdown(void)
{
	if (D3DDevice) {

		Set_Render_Target ((IDirect3DSurface8 *)NULL);
		d_00907b00();
	}

	if (D3DInterface) {
		D3DInterface->Release();
		D3DInterface=NULL;

	}

	if (CurrentCaps)
	{
		int max=((BfmeDX8CapsMaxTexturesView *)CurrentCaps)->max_textures;
		for (int i = 0; i < max; i++)
		{
			if (Textures[i])
			{
				Textures[i]->Release();
				Textures[i] = NULL;
			}
		}
	}

	if (D3DInterface) {
		UINT newRefCount=D3DInterface->Release();
		D3DInterface=NULL;
	}

	if (D3D8Lib) {
		FreeLibrary(D3D8Lib);
		D3D8Lib = NULL;
	}

	Rva01341134DeviceNameTable.Clear();		 // note - Delete_All() resizes the vector, causing a reallocation.  Clear is better. jba.
	Rva013411D4DeviceShortNameTable.Clear();
	Rva013405ECDeviceDescriptionTable.Clear();

	if (TheDX8MeshRenderer) {
		delete TheDX8MeshRenderer;
	}
	TheDX8MeshRenderer = NULL;
	IsInitted = false;		// 010803 srj
}
