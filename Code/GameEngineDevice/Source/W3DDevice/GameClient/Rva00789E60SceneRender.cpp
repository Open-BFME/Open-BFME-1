// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug
// Open-BFME lane C1: carved anonymous body at retail 0x00789E60 (1179 bytes).
//
// Sibling of the already-landed Rva006FEB10Scene::Customized_Render
// (0x006FEB10, same file directory) and W3DRenderScene.cpp's local
// DX8Wrapper snapshot machinery: this body is a second, differently laid
// out scene-render path with a full-screen Clear() up front, its own
// three-state Z transition (ZFUNC/ZWRITEENABLE/ZENABLE), and no visibility
// gate on the render pass. No caller or vtable install proves the owning
// class name; the address is kept in the type name.
//
// The vtable-looking constant 0x013069D0 that tools/vtable_lookup.py finds
// is not a vtable: every ctor/Add_Light/Pre_Render_Update/bfmeSetPair call
// loads it directly into ecx, so it is the fixed storage address of the
// function-local `static LightEnvironmentClass` -- MSVC's guarded static
// init (0x01306C68 bit 0, then atexit) confirms it.

#define Matrix4x4 Matrix4
#include "WW3D2/rendobj.h"
#include "WW3D2/ww3d.h"
#include "WW3D2/camera.h"
#include "WW3D2/rinfo.h"
#include "WW3D2/lightenvironment.h"
#include "WW3D2/robjlist.h"
#include "wwstring.h"

// Local BFME ABI view of DX8Wrapper: the canonical dx8wrapper.h Clear() is
// six-argument Zero Hour, retail here calls the seven-argument BFME
// overload (already landed at DX8Wrapper_Clear.cpp), and this TU needs
// MESH_RENDER_SNAPSHOT_ENABLED's inlined Set_DX8_Render_State shape (same
// technique as WW3DRenderScene.cpp).
#include "d3d8.h"

extern unsigned number_of_DX8_calls;

#define MESH_RENDER_SNAPSHOT_ENABLED

class DX8Wrapper
{
public:
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil,
		const Vector3 &color, float dest_alpha = 0.0f, float z = 1.0f,
		unsigned int stencil = 0);
	static void Set_Light(unsigned index, const D3DLIGHT8 *light);
	static void Apply_Render_State_Changes();
	static void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value);
	static void Get_DX8_Render_State_Value_Name(StringClass &name,
		D3DRENDERSTATETYPE state, unsigned value);
	static const char *Get_DX8_Render_State_Name(D3DRENDERSTATETYPE state);
	static IDirect3DDevice8 *_Get_D3D_Device8(void) { return D3DDevice; }

	static unsigned RenderStates[256];
	static unsigned render_state_changes;
	static IDirect3DDevice8 *D3DDevice;
};

WWINLINE void DX8Wrapper::Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
{
	if (RenderStates[state] == value) return;

#ifdef MESH_RENDER_SNAPSHOT_ENABLED
	if (WW3D::Is_Snapshot_Activated()) {
		StringClass value_name(0, true);
		Get_DX8_Render_State_Value_Name(value_name, state, value);
		SNAPSHOT_SAY(("DX8 - SetRenderState(state: %s, value: %s)\n",
			Get_DX8_Render_State_Name(state), value_name));
	}
#endif

	RenderStates[state] = value;
	_Get_D3D_Device8()->SetRenderState(state, value);
	++number_of_DX8_calls;
	++render_state_changes;
}

class DX8MeshRendererClass
{
public:
	void Flush(void);
};
extern DX8MeshRendererClass *TheDX8MeshRenderer;

// The Reset-shaped call retail makes on the static light environment is
// already pinned under this opaque class/method pair (Bfme5EightyEight.cpp);
// its ABI is two BfmeVecHF const-pointers, not the canonical
// LightEnvironmentClass::Reset(const Vector3&,const Vector3&) references.
class BfmeVecHF
{
public:
	float x, y, z;
};

class Gen_0094AC70
{
public:
	void bfmeSetPair(const BfmeVecHF *a, const BfmeVecHF *b);
};

// BFME layout: AmbientLight is this+0x8 (a vtable/pad004-sized object
// precedes it), the shared update/render list is this+0x60, and the light
// list is this+0x90.  Only the members this body reads are declared.
class Rva00789E60Scene
{
public:
	void Customized_Render(RenderInfoClass &rinfo);

	unsigned char pad000[8];
	Vector3 AmbientLight;					// +0x08
	unsigned char pad014[0x48];			// +0x14
	RefRenderObjListClass RenderList;		// +0x60
	unsigned char pad078[0x18];			// +0x78
	RefRenderObjListClass LightList;		// +0x90
};

// ?Customized_Render@Rva00789E60Scene@@QAEXAAVRenderInfoClass@@@Z
void Rva00789E60Scene::Customized_Render(RenderInfoClass &rinfo)
{
	DX8Wrapper::Clear(false, true, true, Vector3(0, 0, 0), 0.0f, 1.0f, 0);

	RefRenderObjListIterator it(&RenderList);
	for (it.First(); !it.Is_Done(); it.Next()) {
		it.Peek_Obj()->On_Frame_Update();
	}

	DX8Wrapper::Set_Light(0, NULL);
	DX8Wrapper::Set_Light(1, NULL);
	DX8Wrapper::Set_Light(2, NULL);
	DX8Wrapper::Set_Light(3, NULL);

	if (!rinfo.light_environment) {
		static LightEnvironmentClass lenv;

		Vector3 zero(0, 0, 0);
		reinterpret_cast<Gen_0094AC70 *>(&lenv)->bfmeSetPair(
			reinterpret_cast<const BfmeVecHF *>(&zero),
			reinterpret_cast<const BfmeVecHF *>(&AmbientLight));

		for (it.First(&LightList); !it.Is_Done(); it.Next()) {
			lenv.Add_Light(*(LightClass *)it.Peek_Obj());
		}
		lenv.Pre_Render_Update(rinfo.Camera.Get_Transform());

		rinfo.light_environment = &lenv;
	}

	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Render_State((D3DRENDERSTATETYPE)0x17, 8);
	DX8Wrapper::Set_DX8_Render_State((D3DRENDERSTATETYPE)0xe, 0);
	DX8Wrapper::Set_DX8_Render_State((D3DRENDERSTATETYPE)7, 0);

	for (it.First(&RenderList); !it.Is_Done(); it.Next()) {
		it.Peek_Obj()->Render(rinfo);
	}

	TheDX8MeshRenderer->Flush();

	DX8Wrapper::Set_DX8_Render_State((D3DRENDERSTATETYPE)0xe, 1);
	DX8Wrapper::Set_DX8_Render_State((D3DRENDERSTATETYPE)0x17, 8);
}
