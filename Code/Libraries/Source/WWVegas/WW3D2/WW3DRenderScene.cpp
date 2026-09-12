// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// BFME scene renderer, RVA 0x008FE3C0 (879 bytes).
// The x87 color conversion below retains the proven rounding machinery
// from dx8wrapper.h; scene control flow is reconstructed C++.

#include "always.h"
#include "vector3.h"
#include "w3derr.h"
#include "d3d8.h"
#include "wwstring.h"
#include "wwdebug.h"

// Suppress the reference WW3D declaration: BFME's scene overload has the
// byte-return ABI below, while the vendored header declares the enum ABI.
#define WW3D_H

class SceneClass;
class CameraClass;
class RenderInfoClass;
class StaticSortListClass;

// BFME's scene-render overload returns a byte-wide success value.  The
// adjacent layer overloads compare AL with one, and retail's epilogue is
// `mov al,1`; keep that ABI while retaining the WW3D class ownership.
class WW3D
{
public:
	static bool Render(SceneClass *, CameraClass *, bool, bool, const Vector3 &);
	static bool Is_Snapshot_Activated(void) { return SnapshotActivated; }

	static bool IsInitted;
	static bool IsRendering;
	static bool AreStaticSortListsEnabled;
	static bool SnapshotActivated;
	static StaticSortListClass *CurrentStaticSortLists;
};

#define MESH_RENDER_SNAPSHOT_ENABLED
#define SNAPSHOT_SAY(x) if (WW3D::Is_Snapshot_Activated()) { WWDEBUG_SAY(x); }

extern unsigned number_of_DX8_calls;

// Local BFME ABI view.  This keeps the canonical DX8Wrapper class/symbols
// while avoiding a shared-header edit: BFME added clear_stencil to Clear,
// but the target's inline state and color conversion remain the reference
// implementation copied below.
class DX8Wrapper
{
public:
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil,
		const Vector3 &color, float dest_alpha = 0.0f, float z = 1.0f,
		unsigned int stencil = 0);
	static void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value);
	static void Set_Ambient(const Vector3 &color);
	static unsigned int Convert_Color(const Vector3 &color, float alpha);
	static IDirect3DDevice8 *_Get_D3D_Device8(void) { return D3DDevice; }
	static void Get_DX8_Render_State_Value_Name(StringClass &name,
		D3DRENDERSTATETYPE state, unsigned value);
	static const char *Get_DX8_Render_State_Name(D3DRENDERSTATETYPE state);

	static Vector3 Ambient_Color;
	static unsigned RenderStates[256];
	static unsigned render_state_changes;
	static IDirect3DDevice8 *D3DDevice;
};

#include "rendobj.h"
#include "wwprofile.h"
#include "wwmemlog.h"

// This BFME scene layout keeps the ambient-light virtual at +0x1c and the
// Render virtual at +0x58.  The WW3D2 reference header has Render at +0x50.
class SceneClass
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual const Vector3 &Get_Ambient_Light(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void Render(RenderInfoClass &);

	// Polygon mode is an inline BFME field at +0x14.
	int Get_Polygon_Mode(void) const
	{
		return *reinterpret_cast<const int *>(reinterpret_cast<const unsigned char *>(this) + 0x14);
	}

	enum PolygonMode { POINT, LINE, FILL };
};

// BFME's CameraClass has two additional virtual slots before On_Frame_Update.
class CameraClass
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void On_Frame_Update(void);
	void Apply(void);
};

struct Rva00923880Owner
{
	void releaseStacks(void);
};

WWINLINE void bfme_render_info_construct(RenderInfoClass *, CameraClass *);

// The target RenderInfoClass footprint is 0x1b8 bytes; its local base is at
// EBP-0x1d4 because the function keeps separate stack temporaries below the
// reserved area.  The observed leading members retain their source names.
class RenderInfoClass
{
public:
	RenderInfoClass(CameraClass *cam) { bfme_render_info_construct(this, cam); }
	~RenderInfoClass(void) { reinterpret_cast<Rva00923880Owner *>(this)->releaseStacks(); }
	// The BFME field is a pointer-sized camera slot.  Keeping it as a pointer
	// lets the local ctor adapter target the existing retail body without a
	// compiler-generated reference initialization sequence.
	CameraClass *Camera;
	float fog_scale;
	float fog_start;
	float fog_end;
	float alphaOverride;
	float materialPassAlphaOverride;
	float materialPassEmissiveOverride;
	void *light_environment;
	void *Texture_Projector;
	unsigned char m_unreconstructed_24[0x1b8 - 0x24];
};

// Existing retail ctor body at 0x00923690.  Its generated row is still
// address-derived, but the body itself is the witnessed RenderInfo
// initialization: ECX is this and the camera pointer is [ESP+4].
extern void d_00923690(void);
struct Rva00923690Call
{
	void invoke(CameraClass *);
};

// Existing matched owner of the retail 0x00923880 release body.  RenderInfo's
// BFME footprint contains the two ref-counted stacks drained by this method;
// use its proven symbol rather than inventing a second destructor pin.

WWINLINE void bfme_render_info_construct(RenderInfoClass *self, CameraClass *cam)
{
	typedef void (Rva00923690Call::*Function)(CameraClass *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = d_00923690;
	(reinterpret_cast<Rva00923690Call *>(self)->*fn.member)(cam);
}

// BFME keeps this renderer behind a pointer.  The camera member is at +4.
class DX8MeshRendererClass
{
public:
	void Set_Camera(CameraClass *value) { camera = value; }
	void Flush(void);
	void Clear_Pending_Delete_Lists(void);
	void Invalidate(void);
private:
	bool enable_lighting;
	CameraClass *camera;
};
extern DX8MeshRendererClass *TheDX8MeshRenderer;

class SortingRendererClass
{
public:
	static void Flush(void);
};

class StaticSortListClass
{
public:
	virtual ~StaticSortListClass(void);
	virtual void Add_To_List(RenderObjClass *, unsigned int);
	virtual void Render_And_Clear(RenderInfoClass &);
};

// These three inline bodies are the reference DX8Wrapper implementations.
// They are kept here only to give this BFME-specific TU the seven-argument
// Clear declaration while preserving all canonical static data/callee names.
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

WWINLINE void DX8Wrapper::Set_Ambient(const Vector3 &color)
{
	Ambient_Color = color;
	Set_DX8_Render_State(D3DRS_AMBIENT, Convert_Color(color, 0.0f));
}

// Provenance: this is the existing upstream x87 implementation from
// Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h (the same documented
// codegen blocker retained by the matched DX8Wrapper_Clear.cpp). The scene
// path is reconstructed C++; only this compiler machinery remains in asm.
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector3 &color, float alpha)
{
	const float scale = 255.0;
	unsigned int col;

	__asm
	{
		sub esp,20
		fwait
		fstcw [esp+16]
		mov eax,[esp+16]
		mov edi,eax
		and eax,~(1024|2048)
		or eax,(1024|2048)
		sub edi,eax
		jz dx8_color_skip
		mov [esp],eax
		fldcw [esp]
dx8_color_skip:
		mov esi,dword ptr color
		fld dword ptr[scale]
		fld dword ptr[esi]
		fld dword ptr[esi+4]
		fld dword ptr[esi+8]
		fld dword ptr[alpha]
		fld st(4)
		fmul st(4),st
		fmul st(3),st
		fmul st(2),st
		fmulp st(1),st
		fistp dword ptr[esp+0]
		fistp dword ptr[esp+4]
		fistp dword ptr[esp+8]
		fistp dword ptr[esp+12]
		mov ecx,[esp]
		mov eax,[esp+4]
		mov edx,[esp+8]
		mov ebx,[esp+12]
		shl ecx,24
		shl ebx,16
		shl edx,8
		or eax,ecx
		or eax,ebx
		or eax,edx
		fstp st(0)
		cmp edi,0
		je dx8_color_restored
		fwait
		fldcw [esp+16]
dx8_color_restored:
		add esp,20
		mov col,eax
	}
	return col;
}

// Keep the flush sequence local to this TU; this avoids defining WW3D helpers
// already owned by ww3d.cpp while preserving their inlined retail order.
static void bfme_render_and_clear_static_sort_lists(RenderInfoClass &rinfo)
{
	bool old_enable = WW3D::AreStaticSortListsEnabled;
	WW3D::AreStaticSortListsEnabled = false;
	WW3D::CurrentStaticSortLists->Render_And_Clear(rinfo);
	WW3D::AreStaticSortListsEnabled = old_enable;
}

static void bfme_flush(RenderInfoClass &rinfo)
{
	TheDX8MeshRenderer->Flush();
	bfme_render_and_clear_static_sort_lists(rinfo);
	SortingRendererClass::Flush();
	TheDX8MeshRenderer->Clear_Pending_Delete_Lists();
}

// ?Render@WW3D@@SA_NPAVSceneClass@@PAVCameraClass@@_N2ABVVector3@@@Z
bool WW3D::Render(SceneClass *scene, CameraClass *cam,
	bool clear, bool clearz, const Vector3 &color)
{
	if (!IsInitted) {
		return true;
	}

	WWPROFILE("WW3D::Render");
	WWMEMLOG(MEM_GAMEDATA);
	WWASSERT(IsInitted);
	WWASSERT(IsRendering);
	WWASSERT(scene);
	WWASSERT(cam);

	cam->On_Frame_Update();
	RenderInfoClass rinfo(cam);
	cam->Apply();

	if (clear || clearz) {
		DX8Wrapper::Clear(clear, clearz, clearz, color);
	}

	switch (scene->Get_Polygon_Mode()) {
	case SceneClass::POINT:
		DX8Wrapper::Set_DX8_Render_State(D3DRS_FILLMODE, D3DFILL_POINT);
		break;
	case SceneClass::LINE:
		DX8Wrapper::Set_DX8_Render_State(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		break;
	case SceneClass::FILL:
		DX8Wrapper::Set_DX8_Render_State(D3DRS_FILLMODE, D3DFILL_SOLID);
		break;
	}

	DX8Wrapper::Set_Ambient(scene->Get_Ambient_Light());
	TheDX8MeshRenderer->Set_Camera(rinfo.Camera);
	scene->Render(rinfo);
	bfme_flush(rinfo);

	return true;
}




