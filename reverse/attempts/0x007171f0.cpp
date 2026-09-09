// ?startRenderToTexture@W3DShaderManager@@SAXXZ
// partial score=0.991 date=2026-09-09
// cl: /DNDEBUG /MD
// Readable BFME body for the static render-to-texture setup at retail 0x007171F0, 445 bytes.
// The named W3DShaderManager entry is the 5-byte incremental-link thunk in
// Code/GameEngine/Source/Common/ExactStaticThunks.cpp; its target is this
// TU-local body. The target is reached by the matched startRenderToTexture
// thunk and by the render-filter callers in W3DShaderManager.cpp.

struct IDirect3DSurface8;
struct Device;
struct DeviceVtable { void *unused[3]; long (__stdcall *TestCooperativeLevel)(Device *); };
struct Device { DeviceVtable *v; };
extern Device *ScreenDevice;

class Vector3
{
public:
	float x, y, z;
	Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};

struct Coord2D { float x, y; };
class ShaderClass { public: unsigned bits; };

class RefCountClass
{
public:
	virtual void Delete_This();
	mutable int NumRefs;
	void Add_Ref() const { ++NumRefs; }
	void Release_Ref() const
	{
		if (--NumRefs == 0)
			const_cast<RefCountClass *>(this)->Delete_This();
	}
};

class VertexMaterialClass : public RefCountClass
{
	public:
	enum PresetType { PRELIT_DIFFUSE };
	static VertexMaterialClass *Get_Preset(PresetType);
};

extern VertexMaterialClass *ScreenMaterial;
extern unsigned TheBoxTextureDirtyMask, ScreenOpaqueShader;

struct GlobalDataView
{
	char pad[0x8c];
	bool showSoftWaterEdge;
};
extern GlobalDataView *ShaderGlobalData;

// The retail global at 0x012F7FE0 is shared by terrain/render code.  This
// narrow ABI view names only the observed field; it does not assert a higher
// level ownership or water-specific type for the global.
struct BfmeGlobal012F7FE0
{
	char pad[0x301c];
	float field_301c;
	float getField301c() const { return field_301c; }
};
extern BfmeGlobal012F7FE0 *BfmeGlobal_012f7fe0;

class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *, bool);
	static void Set_DX8_Render_State(unsigned long, unsigned int);
	static void Set_Shader(const ShaderClass &);
	static void Clear(bool, bool, bool, const Vector3 &, float, float, unsigned);
	static __forceinline void Set_Material(VertexMaterialClass *p)
	{
		if (p)
			p->Add_Ref();
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		ScreenMaterial = p;
		TheBoxTextureDirtyMask |= 0x4000;
	}
};

void bfmeDrawFilterUV(int, int, Coord2D *);

class W3DShaderManagerStartRenderToTextureShim
{
public:
	static void start();
	static bool m_renderingToTexture;
	static IDirect3DSurface8 *m_newRenderSurface, *m_oldDepthSurface;
	static int m_currentFilter;
};

union Scratch
{
	Coord2D dims;
	float opacity;
	ShaderClass shader;
};

void W3DShaderManagerStartRenderToTextureShim::start()
{
	Scratch slot;
	if (m_renderingToTexture || !m_newRenderSurface || !m_oldDepthSurface)
		return;
	if (ScreenDevice && ScreenDevice->v->TestCooperativeLevel(ScreenDevice) != 0)
		return;

	DX8Wrapper::Set_Render_Target(m_newRenderSurface, true);
	m_renderingToTexture = true;
	if (ShaderGlobalData->showSoftWaterEdge)
	{
		if (m_currentFilter == 2 || m_currentFilter == 3)
		{
			DX8Wrapper::Set_DX8_Render_State(168, 8);
			slot.shader.bits = (ScreenOpaqueShader & ~8) | 7;
			DX8Wrapper::Set_Shader(slot.shader);
			VertexMaterialClass *p = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
			DX8Wrapper::Set_Material(p);
			if (p)
				p->Release_Ref();
			int alpha = (int)(BfmeGlobal_012f7fe0->getField301c() * 255.0f);
			slot.dims.x = 1;
			slot.dims.y = 1;
			bfmeDrawFilterUV(0xffffff | (alpha << 24), 0, &slot.dims);
			DX8Wrapper::Set_DX8_Render_State(168, 7);
		}
		else
		{
			slot.opacity = BfmeGlobal_012f7fe0->getField301c();
			DX8Wrapper::Clear(true, false, false, Vector3(0, 0, 0), slot.opacity, 1, 0);
		}
	}
	else if (m_currentFilter == 4)
	{
		slot.opacity = BfmeGlobal_012f7fe0->getField301c();
		DX8Wrapper::Clear(true, false, false, Vector3(0, 0, 0), slot.opacity, 1, 0);
	}
}
