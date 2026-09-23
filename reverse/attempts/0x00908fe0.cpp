// ?End_Scene@DX8Wrapper@@SAX_N@Z
// partial score=0.83 date=2026-09-23
// cl: /ICode/Libraries/Source/WWVegas/WW3D2 /Ireference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
// readable body of ?Set_Index_Buffer@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/sortingrenderer.cpp
// readable body of ?Set_Vertex_Buffer@DX8Wrapper@@: Code/Libraries/Source/WWVegas/wwshade/shdrenderer.cpp
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/dx8wrapper.cpp                         $*
 *                                                                                             *
 *              Original Author:: Jani Penttinen                                               *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 08/05/02 1:27p                                              $*
 *                                                                                             *
 *                    $Revision:: 170                                                         $*
 *                                                                                             *
 * 06/26/02 KM Matrix name change to avoid MAX conflicts                                       *
 * 06/27/02 KM Render to shadow buffer texture support														*
 * 06/27/02 KM Shader system updates																				*
 * 08/05/02 KM Texture class redesign 
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   DX8Wrapper::_Update_Texture -- Copies a texture from system memory to video memory        *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//#define CREATE_DX8_MULTI_THREADED
//#define CREATE_DX8_FPU_PRESERVE
#define WW3D_DEVTYPE D3DDEVTYPE_HAL

#include "dx8wrapper.h"
#include "dx8webbrowser.h"
#include "dx8fvf.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8renderer.h"
#include "ww3d.h"
#include "camera.h"
#include "wwstring.h"
#include "matrix4.h"
#include "vertmaterial.h"
#include "rddesc.h"
#include "lightenvironment.h"
#include "statistics.h"
#include "registry.h"
#include "boxrobj.h"
#include "pointgr.h"
#include "render2d.h"
#include "sortingrenderer.h"
#include "shattersystem.h"
#include "light.h"
#include "assetmgr.h"
#include "textureloader.h"
#include "missingtexture.h"
#include "thread.h"
#include <stdio.h>
#include <D3dx8core.h>
#include "pot.h"
#include "wwprofile.h"
#include "ffactory.h"
#include "dx8caps.h"
#include "formconv.h"
#include "dx8texman.h"
#include "bound.h"
#include "dx8webbrowser.h"

#include "shdlib.h"

extern void bfmeEndSceneTouch00958910(void *);
// ?End_Scene@DX8Wrapper@@SAX_N@Z
// partial score=0.82 date=2026-09-10
// ?End_Scene@DX8Wrapper@@SAX_N@Z
// Best bounded reconstruction banked by lane20; source fragment only.
struct BfmeEndSceneDeviceVtable { void *slots0to2[3]; long (__stdcall *TestCooperativeLevel)(void *); void *slots4to16[13]; long (__stdcall *Present)(void *, const void *, const void *, void *, const void *); void *slots18to41[24]; long (__stdcall *EndScene)(void *); };
struct BfmeEndSceneDevice { BfmeEndSceneDeviceVtable *vtable; };
class BfmeAwakenLog { public: virtual BfmeAwakenLog *slot00(int); virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void); virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void); virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void); virtual void slot30(void); virtual void slot34(void); virtual BfmeAwakenLog *slot38(const char *); virtual void slot3c(void); virtual void slot40(void); virtual void slot44(void); virtual void slot48(void); virtual BfmeAwakenLog *slot4c(int); };
class BfmeAwakenDebug { public: virtual void slot00(void); virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void); virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void); virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void); virtual void slot30(void); virtual void slot34(void); virtual void slot38(void); virtual void slot3c(void); virtual void slot40(void); virtual void slot44(void); virtual void slot48(void); virtual void slot4c(void); virtual void slot50(void); virtual void slot54(void); virtual void slot58(void); virtual void slot5c(void); virtual void slot60(void); virtual void slot64(void); virtual void slot68(void); virtual BfmeAwakenLog *slot6c(int, int); };
extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int);
extern void __cdecl Rva009DB560Sleep(unsigned int);
extern VertexBufferClass *Rva01341120VertexBuffers[];
extern IndexBufferClass *Rva01341128IndexBuffer;

class BfmeHandleCX
{
public:
    TextureClass *p;
    ~BfmeHandleCX(void) { if (p) p->Release_Ref(); }
};

void DX8Wrapper::End_Scene(bool flip_frames)
{
    unsigned saved_scene_state = *reinterpret_cast<unsigned *>(0x013405c4);
    *reinterpret_cast<unsigned *>(0x013405c8) = saved_scene_state;
    *reinterpret_cast<unsigned *>(0x013405c4) = 0;
    reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->EndScene(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice));
    ++number_of_DX8_calls;
    bfmeEndSceneTouch00958910(0);
    if (flip_frames) {
        int result = reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->Present(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice), 0, 0, 0, 0);
        ++number_of_DX8_calls;
        if (result >= 0) { ++FrameCount; IsDeviceLost = false; } else IsDeviceLost = true;
        if (result == D3DERR_DEVICELOST) {
            result = reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->TestCooperativeLevel(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice));
            if (result == D3DERR_DEVICENOTRESET) Reset_Device(true); else Rva009DB560Sleep(200);
        } else if (result != 0) {
            _bfme_debugRecordCallsite(1);
            TheBfmeAwakenDebug->slot60();
            TheBfmeAwakenDebug->slot6c(0, 0)->slot38("DX8 error ")->slot00(result)->slot4c(1);
        }
    }
    if (Rva01341120VertexBuffers[0]) Rva01341120VertexBuffers[0]->Release_Engine_Ref();
    *reinterpret_cast<unsigned short *>(0x01341118) = 0;
    *reinterpret_cast<unsigned short *>(0x0134111a) = 0;
    if (Rva01341120VertexBuffers[0]) Rva01341120VertexBuffers[0]->Release_Ref();
    *reinterpret_cast<unsigned *>(0x0133f49c) |= 0x10000;
    IndexBufferClass *index_buffer = Rva01341128IndexBuffer;
    if (index_buffer) Rva01341128IndexBuffer->Release_Engine_Ref();
    Rva01341120VertexBuffers[0] = 0;
    *reinterpret_cast<unsigned *>(0x0134110c) = 4;
    *reinterpret_cast<unsigned short *>(0x0134111c) = 0;
    if (index_buffer) index_buffer->Release_Ref();
    *reinterpret_cast<unsigned *>(0x01341114) = 4;
    Rva01341128IndexBuffer = 0;
    *reinterpret_cast<unsigned short *>(0x0134112c) = 0;
    *reinterpret_cast<unsigned *>(0x0133f49c) |= 0x20000;
    TextureBaseClass **textures = reinterpret_cast<TextureBaseClass **>(0x01340ec8);
    for (int i = 0; i < CurrentCaps->Get_Max_Textures_Per_Pass(); ++i) {
        BfmeHandleCX texture;
        texture.p = reinterpret_cast<TextureClass *>(textures[i]);
        if (texture.p) texture.p->Release_Ref();
        texture.p = 0;
        textures[i] = 0;
        *reinterpret_cast<unsigned *>(0x0133f49c) |= 0x40 << i;
    }
    VertexMaterialClass **material = reinterpret_cast<VertexMaterialClass **>(0x01340ec4);
    if (*material) (*material)->Release_Ref();
    *reinterpret_cast<unsigned *>(0x0133f49c) |= 0x4000;
    *material = 0;
    *reinterpret_cast<unsigned *>(0x0134051c) = 0;
}
