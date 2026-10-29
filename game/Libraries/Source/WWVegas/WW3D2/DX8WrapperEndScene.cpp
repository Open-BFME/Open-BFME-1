// ?End_Scene@DX8Wrapper@@SAX_N@Z
// Complete 616-byte retail body; identity: WW3D::End_Render caller.
// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "vertmaterial.h"
#include <stdio.h>
#include <D3dx8core.h>


extern void bfmeEndSceneTouch00958910(void *);
struct BfmeEndSceneDeviceVtable { void *slots0to2[3]; long (__stdcall *TestCooperativeLevel)(void *); void *slots4to16[13]; long (__stdcall *Present)(void *, const void *, const void *, void *, const void *); void *slots18to41[24]; long (__stdcall *EndScene)(void *); };
struct BfmeEndSceneDevice { BfmeEndSceneDeviceVtable *vtable;
    // ?EndScene@BfmeEndSceneDevice@@QAEJXZ absent-from-retail
    long EndScene() { return vtable->EndScene(this); }
    // ?Present@BfmeEndSceneDevice@@QAEJPBX0PAX0@Z absent-from-retail
    long Present(const void *a, const void *b, void *c, const void *d) { return vtable->Present(this, a, b, c, d); }
};
class BfmeAwakenLog { public: virtual BfmeAwakenLog *slot00(int); virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void); virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void); virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void); virtual void slot30(void); virtual void slot34(void); virtual BfmeAwakenLog *slot38(const char *); virtual void slot3c(void); virtual void slot40(void); virtual void slot44(void); virtual void slot48(void); virtual BfmeAwakenLog *slot4c(int); };
class BfmeAwakenDebug { public: virtual void slot00(void); virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void); virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void); virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void); virtual void slot30(void); virtual void slot34(void); virtual void slot38(void); virtual void slot3c(void); virtual void slot40(void); virtual void slot44(void); virtual void slot48(void); virtual void slot4c(void); virtual void slot50(void); virtual void slot54(void); virtual void slot58(void); virtual void slot5c(void); virtual void slot60(void); virtual void slot64(void); virtual void slot68(void); virtual BfmeAwakenLog *slot6c(int, int); };
// Retail 0x01336E5C is ?g_Rva00F36E5C@@3PAXA (data_rows.csv,
// debug/Rva00F36E5C.cpp); TheBfmeAwakenDebug was only a pin.
extern void *g_Rva00F36E5C;
#define TheBfmeAwakenDebug ( *(BfmeAwakenDebug **)&g_Rva00F36E5C )
extern void _bfme_debugRecordCallsite(int);
extern void __cdecl Rva009DB560Sleep(unsigned long);

class BfmeHandleCX0005CC00
{
public:
    TextureClass *p;
    BfmeHandleCX0005CC00(TextureClass *texture = 0) : p(texture) { if (p) p->Add_Ref(); }
    ~BfmeHandleCX0005CC00(void) { if (p) p->Release_Ref(); }
    BfmeHandleCX0005CC00 &operator=(const BfmeHandleCX0005CC00 &other) {
        if (other.p) other.p->Add_Ref();
        if (p) p->Release_Ref();
        p = other.p;
        return *this;
    }
    bool operator==(const BfmeHandleCX0005CC00 &other) const { return p == other.p; }
    operator TextureClass *() const { return p; }
};

// The retail caps view places the signed texture-stage limit at +0x278.
struct BfmeD3D9CapsMaxTextures {
    unsigned char pad[0x278];
    int MaxTexturesPerPass;
};

// Internal storage makes the device table independent of the counter clear.
static unsigned g_Va013405C4;
static unsigned g_Va013405C8;

// ?End_Scene@DX8Wrapper@@SAX_N@Z
void DX8Wrapper::End_Scene(bool flip_frames)
{
    g_Va013405C8 = g_Va013405C4;
    BfmeEndSceneDevice *dev = reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice);
    BfmeEndSceneDeviceVtable *vtable = dev->vtable;
    g_Va013405C4 = 0;
    dev->EndScene();
    ++number_of_DX8_calls;
    bfmeEndSceneTouch00958910(0);
    if (flip_frames) {
        BfmeEndSceneDevice *present_device = reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice);
        BfmeEndSceneDeviceVtable *present_vtable = present_device->vtable;
        int result = present_device->Present(0, 0, 0, 0);
        ++number_of_DX8_calls;
        if (result >= 0) { IsDeviceLost = false; ++FrameCount; } else IsDeviceLost = true;
        // If the device was lost we need to check for cooperative level and possibly reset the device
        if (result == D3DERR_DEVICELOST) {
            result = reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->TestCooperativeLevel(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice));
            if (result == D3DERR_DEVICENOTRESET) Reset_Device(true);
            else {
                // Sleep it not active
                Rva009DB560Sleep(200);
            }
        } else if (result != 0) {
            _bfme_debugRecordCallsite(1);
            TheBfmeAwakenDebug->slot60();
            TheBfmeAwakenDebug->slot6c(0, 0)->slot38("DX8 error ")->slot00(result)->slot4c(1);
        }
    }
    // Each frame, release all of the buffers and textures.
    render_state.vba_offset = 0;
    render_state.vba_count = 0;
    if (render_state.vertex_buffers[0]) render_state.vertex_buffers[0]->Release_Engine_Ref();
    if (render_state.vertex_buffers[0]) render_state.vertex_buffers[0]->Release_Ref();
    render_state_changed |= VERTEX_BUFFER_CHANGED;
    render_state.vertex_buffers[0] = 0;
    render_state.vertex_buffer_types[0] = 4;
    render_state.iba_offset = 0;
    if (render_state.index_buffer) render_state.index_buffer->Release_Engine_Ref();
    if (render_state.index_buffer) render_state.index_buffer->Release_Ref();
    unsigned ib_changed = render_state_changed;
    render_state.index_buffer_type = 4;
    render_state.index_buffer = 0;
    render_state.index_base_offset = 0;
    render_state_changed = ib_changed | INDEX_BUFFER_CHANGED;
    BfmeHandleCX0005CC00 *textures = reinterpret_cast<BfmeHandleCX0005CC00 *>(render_state.Textures);
    for (int i = 0; i < reinterpret_cast<BfmeD3D9CapsMaxTextures *>(CurrentCaps)->MaxTexturesPerPass; ++i) {
        BfmeHandleCX0005CC00 binding;
        if (!(textures[i] == binding)) {
            textures[i] = binding;
            render_state_changed |= (TEXTURE0_CHANGED << i);
        }
    }
    
    if (render_state.material) render_state.material->Release_Ref();
    unsigned mat_changed = render_state_changed | MATERIAL_CHANGED;
    render_state.material = 0;
    Light_Environment = 0;
    render_state_changed = mat_changed;
}
