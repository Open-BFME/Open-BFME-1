// ?End_Scene@DX8Wrapper@@SAX_N@Z
// partial score=0.6867 date=2026-09-28
// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
// partial score=0.87 date=2026-09-28
// Identity: the only caller is ?End_Render@WW3D@@SA?AW4WW3DErrorType@@_N@Z
// (one call site), and the retail frame is the D3D9 EndScene/Present pair, so
// the ZH twin's name is the retail name here.
// Shape notes (all measured with tools/probe.py, 607B ours vs 616B retail):
//  - the two unsigned-short clears precede the Cur_VB test: retail hoists the
//    test's load/cmp above them, so the clears are written first;
//  - `IsDeviceLost = false;` precedes `++FrameCount;`, which is what splits
//    retail's increment into load/inc/.../store around the byte store;
//  - render_state_changed (0x0133F49C, proven static) is written through the
//    named static, not a cast pointer: the cast form made MSVC fuse every
//    |= into one `or [mem],imm`, while retail splits all but the first;
//  - the per-iteration BfmeHandleCX is the object in retail's single unwind
//    state (tools/eh_info.py 0x00908FE0 -> cleanup tail-jumps the matched
//    ??1BfmeHandleCX@@QAE@XZ at 0x0005CC00), so its null ctor store and the
//    -1/0 state pair belong to the loop body.
// Remaining 175 diffs, in the order probe --shape reports them (do NOT retry
// these shapes blind, each was measured):
//  1 +0x0E  retail emits the first statement's `mov eax,[0x13405c4]` BETWEEN
//    `push eax` and `mov fs:[0],esp`; VC7.1 in this TU always installs the
//    frame first. Same length either way (12 bytes of permutation).
//  2 +0x20  retail hoists the D3DDevice load/vtable load/`push esi` above the
//    `xor ebx,ebx` + `mov [0x13405c4],ebx` pair; ours keeps source order.
//  3 +0x112 retail hoists the Cur_VB test's load/cmp above the two word
//    clears; VC7.1 does not hoist a compare that feeds a branch. Same for the
//    index-buffer group at +0x159 (the `mov esi,4` materialisation).
//  4 +0x193 retail keeps the hoisted flag load together with `or edx,0x20000`
//    above the three index-buffer stores; ours sinks the `or`.
//  5 +0x1df retail has a SECOND null test in the loop
//    (`mov ecx,eax; cmp ecx,ebx; je`, the REF_PTR_SET `if (dst)` guard that
//    MSVC folds away here even when it re-reads the array element).
//  6 the material release takes the in-memory `dec [ecx+4]` form in ours and
//    the register form in retail; the identical inline Release_Ref takes the
//    register form for the vertex and index buffers, so it is register
//    pressure at that point, not the spelling.
//  7 the epilogue pieces MSVC hoists (the `mov ecx,[esp+8]` frame-chain load,
//    `pop esi`) land in a different order in the material block.
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
    BfmeHandleCX(void) : p(0) {}
    ~BfmeHandleCX(void) { if (p) p->Release_Ref(); }
};

// The loop bound is a signed dword at +0x278 of the caps object the
// CurrentCaps pointer names (retail reads [CurrentCaps+0x278] at +0x1BD and
// +0x20B). The game's dx8caps.h is the D3D8 layout (+0x124), so the field is
// read through this TU-local view instead of the header accessor.
struct BfmeD3D9CapsMaxTextures {
    unsigned char pad[0x278];
    int MaxTexturesPerPass;
};

void DX8Wrapper::End_Scene(bool flip_frames)
{
    *reinterpret_cast<unsigned *>(0x013405c8) = *reinterpret_cast<unsigned *>(0x013405c4);
    *reinterpret_cast<unsigned *>(0x013405c4) = 0;
    reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->EndScene(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice));
    ++number_of_DX8_calls;
    bfmeEndSceneTouch00958910(0);
    if (flip_frames) {
        int result = reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->Present(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice), 0, 0, 0, 0);
        ++number_of_DX8_calls;
        if (result >= 0) { IsDeviceLost = false; ++FrameCount; } else IsDeviceLost = true;
        if (result == D3DERR_DEVICELOST) {
            result = reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->TestCooperativeLevel(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice));
            if (result == D3DERR_DEVICENOTRESET) Reset_Device(true); else Rva009DB560Sleep(200);
        } else if (result != 0) {
            _bfme_debugRecordCallsite(1);
            TheBfmeAwakenDebug->slot60();
            TheBfmeAwakenDebug->slot6c(0, 0)->slot38("DX8 error ")->slot00(result)->slot4c(1);
        }
    }
    *reinterpret_cast<unsigned short *>(0x01341118) = 0;
    *reinterpret_cast<unsigned short *>(0x0134111a) = 0;
    if (Rva01341120VertexBuffers[0]) Rva01341120VertexBuffers[0]->Release_Engine_Ref();
    if (Rva01341120VertexBuffers[0]) Rva01341120VertexBuffers[0]->Release_Ref();
    render_state_changed |= 0x10000;
    Rva01341120VertexBuffers[0] = 0;
    *reinterpret_cast<unsigned *>(0x0134110c) = 4;
    *reinterpret_cast<unsigned short *>(0x0134111c) = 0;
    if (Rva01341128IndexBuffer) Rva01341128IndexBuffer->Release_Engine_Ref();
    if (Rva01341128IndexBuffer) Rva01341128IndexBuffer->Release_Ref();
    unsigned ib_changed = render_state_changed | 0x20000;
    *reinterpret_cast<unsigned *>(0x01341114) = 4;
    Rva01341128IndexBuffer = 0;
    *reinterpret_cast<unsigned short *>(0x0134112c) = 0;
    render_state_changed = ib_changed;
    TextureBaseClass **textures = reinterpret_cast<TextureBaseClass **>(0x01340ec8);
    for (int i = 0; i < reinterpret_cast<BfmeD3D9CapsMaxTextures *>(CurrentCaps)->MaxTexturesPerPass; ++i) {
        BfmeHandleCX binding;
        TextureClass *slot = reinterpret_cast<TextureClass *>(textures[i]);
        if (slot != 0) {
            if (textures[i]) reinterpret_cast<TextureClass *>(textures[i])->Release_Ref();
            unsigned tex_changed = render_state_changed | (0x40u << i);
            textures[i] = 0;
            render_state_changed = tex_changed;
        }
    }
    VertexMaterialClass *mat = *reinterpret_cast<VertexMaterialClass **>(0x01340ec4);
    if (mat) mat->Release_Ref();
    unsigned mat_changed = render_state_changed | 0x4000;
    *reinterpret_cast<VertexMaterialClass **>(0x01340ec4) = 0;
    *reinterpret_cast<unsigned *>(0x0134051c) = 0;
    render_state_changed = mat_changed;
}
