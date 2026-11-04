// ?start@W3DShaderManagerStartRenderToTextureShim@@SAXXZ
// cl: /DNDEBUG /MD
//
// Retail 0x007171F0, 445 bytes, RET at +0x1BC followed by INT3 padding. Body of
// W3DShaderManager::startRenderToTexture: the named static entry at ILT
// 0x000154E7 (game/GameEngine/Source/Common/ExactStaticThunks.cpp) forwards
// here, so the row keeps the shim name pinned at this address. The readable
// Zero Hour body is W3DShaderManager::startRenderToTexture in
// W3DShaderManager.cpp. BFME adds the cooperative-level guard, a
// three-argument viewport blit (ILT 0x000196A0) and the FT_VIEW_DEFAULT clear.
//
// Codegen (measured): the shader is a nested-scope local, so its slot is free
// again for the blit's scale temporary. The scale is a temporary built in the
// argument list, which puts its address in ECX and the water-opacity global
// in EDX. The opacity reaches Clear through its inline getter's return
// temporary, which keeps retail's stack copy of the value.

struct IDirect3DSurface8;

struct IDirect3DDevice8
{
	virtual long __stdcall QueryInterface(const void *iid, void **object) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
	virtual long __stdcall TestCooperativeLevel() = 0;
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X, Y, Z;
};

struct Coord2D
{
	float x, y;
};

// The blit takes its UV scale through a Coord2D pointer.
struct ViewportScale : Coord2D
{
	ViewportScale(float sx, float sy) { x = sx; y = sy; }
	operator Coord2D *() { return this; }
};

class ShaderClass
{
public:
	enum DepthCompareType { PASS_ALWAYS = 7 };
	enum DepthMaskType { DEPTH_WRITE_DISABLE = 0 };
	void Set_Depth_Compare(DepthCompareType x) { ShaderBits = (ShaderBits & ~0x7) | x; }
	void Set_Depth_Mask(DepthMaskType x) { ShaderBits = (ShaderBits & ~0x8) | (x << 3); }
	static ShaderClass _PresetOpaqueSolidShader;
	unsigned long ShaderBits;
};

class RefCountClass
{
public:
	virtual void Delete_This();
	void Add_Ref() const { ++NumRefs; }
	void Release_Ref() const
	{
		if (--NumRefs == 0)
			const_cast<RefCountClass *>(this)->Delete_This();
	}
	mutable int NumRefs;
};

class VertexMaterialClass : public RefCountClass
{
public:
	enum PresetType { PRELIT_DIFFUSE };
	static VertexMaterialClass *Get_Preset(PresetType type);
};

// DX8Wrapper's current material (render_state.material in Zero Hour).
extern VertexMaterialClass *Rva01340EC4Material;

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static void Set_Render_Target(IDirect3DSurface8 *surface, bool use_default_depth_buffer);
	static void Set_DX8_Render_State(unsigned long state, unsigned int value);
	static void Set_Shader(const ShaderClass &shader);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil,
		const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
	static __forceinline void Set_Material(VertexMaterialClass *material)
	{
		if (material)
			material->Add_Ref();
		if (Rva01340EC4Material)
			Rva01340EC4Material->Release_Ref();
		Rva01340EC4Material = material;
		render_state_changed |= 0x4000;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned render_state_changed;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct GlobalDataSoftWaterView
{
	char m_unknown00[0x8c];
	bool m_showSoftWaterEdge;
};

// Global at 0x012F7FE0; only the minimum water opacity at +0x301C is used here.
class BfmeGlobal_012f7fe0;
extern BfmeGlobal_012f7fe0 *TheBfmeGlobal_012f7fe0;

struct WaterOpacityView
{
	char m_unknown0000[0x301c];
	float m_minWaterOpacity;
	float getMinWaterOpacity() const { return m_minWaterOpacity; }
};

void bfmeDrawFilterUV(int color, int flags, Coord2D *uvScale);

enum FilterTypes
{
	FT_NULL_FILTER,
	FT_VIEW_BW_FILTER,
	FT_VIEW_MOTION_BLUR_FILTER,
	FT_VIEW_CROSSFADE,
	FT_VIEW_DEFAULT
};

class W3DShaderManager
{
	friend class W3DShaderManagerStartRenderToTextureShim;

protected:
	static FilterTypes m_currentFilter;
	static bool m_renderingToTexture;
	static IDirect3DSurface8 *m_newRenderSurface;
	static IDirect3DSurface8 *m_oldDepthSurface;
};

class W3DShaderManagerStartRenderToTextureShim
{
public:
	static void start();
};

static const WaterOpacityView *waterOpacity()
{
	return reinterpret_cast<const WaterOpacityView *>(TheBfmeGlobal_012f7fe0);
}

void W3DShaderManagerStartRenderToTextureShim::start()
{
	if (W3DShaderManager::m_renderingToTexture || W3DShaderManager::m_newRenderSurface == 0 ||
		W3DShaderManager::m_oldDepthSurface == 0)
		return;
	IDirect3DDevice8 *device = DX8Wrapper::_Get_D3D_Device8();
	if (device && device->TestCooperativeLevel() != 0)
		return;

	DX8Wrapper::Set_Render_Target(W3DShaderManager::m_newRenderSurface, true);
	W3DShaderManager::m_renderingToTexture = true;
	if (reinterpret_cast<const GlobalDataSoftWaterView *>(TheWritableGlobalData)->m_showSoftWaterEdge)
	{
		if (W3DShaderManager::m_currentFilter == FT_VIEW_MOTION_BLUR_FILTER ||
			W3DShaderManager::m_currentFilter == FT_VIEW_CROSSFADE)
		{
			DX8Wrapper::Set_DX8_Render_State(168, 8);	// D3DRS_COLORWRITEENABLE, alpha only
			{
				ShaderClass shader = ShaderClass::_PresetOpaqueSolidShader;
				shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
				shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
				DX8Wrapper::Set_Shader(shader);
			}
			VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
			DX8Wrapper::Set_Material(vmat);
			if (vmat)
				vmat->Release_Ref();
			int alpha = (int)(waterOpacity()->getMinWaterOpacity() * 255.0f);
			bfmeDrawFilterUV(0x00ffffff | (alpha << 24), 0, ViewportScale(1.0f, 1.0f));
			DX8Wrapper::Set_DX8_Render_State(168, 7);	// D3DRS_COLORWRITEENABLE, red/green/blue
		}
		else
		{
			DX8Wrapper::Clear(true, false, false, Vector3(0.0f, 0.0f, 0.0f),
				waterOpacity()->getMinWaterOpacity(), 1.0f, 0);
		}
	}
	else if (W3DShaderManager::m_currentFilter == FT_VIEW_DEFAULT)
	{
		DX8Wrapper::Clear(true, false, false, Vector3(0.0f, 0.0f, 0.0f),
			waterOpacity()->getMinWaterOpacity(), 1.0f, 0);
	}
}
