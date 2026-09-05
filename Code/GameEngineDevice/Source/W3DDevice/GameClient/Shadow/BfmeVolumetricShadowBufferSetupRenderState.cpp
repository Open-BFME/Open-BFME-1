// cl: /DNDEBUG /MD
//
// Retail RVA 0x007C19F0, 408 bytes: render-state setup that precedes the
// matched drawAndRelease() at 0x007C1BF0 (same shadow-buffer-lock owner:
// m_vertexBuffer/m_indexBuffer sit at +0x0/+0x4 in both bodies). Sets the
// current material to the PRELIT_DIFFUSE preset, binds vertex/index
// buffers, seeds the world matrix to identity on first use, applies
// pending render-state changes, then sets the D3D8 stencil states and
// clears the vertex/pixel shader before the caller draws.
// Shares 0x1340EC4 (current material) / 0x133F49C (dirty-state mask) with
// the other members of this render-state family.

class VertexBufferClass;
class IndexBufferClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.h
class VertexMaterialClass
{
public:
	virtual void Delete_This();
	int refs;
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType preset);
	void ReleaseGlobalRef();
};

extern VertexMaterialClass *ScreenMaterial;      // 0x1340EC4 -- shared model global
extern unsigned TheBoxTextureDirtyMask;          // 0x133F49C -- shared model global

static inline int decrementRef(int *p) { return --*p; }

void VertexMaterialClass::ReleaseGlobalRef()
{
	decrementRef(&refs);
	if (refs == 0)
		Delete_This();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	static ShaderClass _PresetOpaqueShader;
};

class DX8Wrapper
{
public:
	static void Set_Shader(const ShaderClass &shader);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index);
	static void Apply_Render_State_Changes(void);
};

extern float g_worldMatrix[16];   // 0x134108C, one 4x4 identity matrix

struct Device { void **vt; };
extern Device *ScreenDevice;      // 0x1340534

typedef long (__stdcall *SetRenderStateFn)(Device *, unsigned, unsigned);
typedef long (__stdcall *SetShaderStageFn)(Device *, unsigned);

struct TacticalViewLike { unsigned char pad[8]; unsigned mask; };
extern TacticalViewLike *TheTacticalView;   // 0x1306EEC

class BfmeVolumetricShadowBufferLocks
{
	VertexBufferClass *m_vertexBuffer;
	IndexBufferClass *m_indexBuffer;

public:
	void setupRenderState();
};

void BfmeVolumetricShadowBufferLocks::setupRenderState()
{
	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	if (vmat)
		++vmat->refs;

	if (ScreenMaterial)
		ScreenMaterial->ReleaseGlobalRef();

	unsigned dirty = TheBoxTextureDirtyMask | 0x4000;
	ScreenMaterial = vmat;
	TheBoxTextureDirtyMask = dirty;
	if (vmat) {
		if (--vmat->refs == 0)
			vmat->Delete_This();
	}

	DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueShader);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffer, 0);
	DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);

	unsigned mask = TheBoxTextureDirtyMask;
	if (!(mask & 0x40000)) {
		mask |= 0x40001;
		g_worldMatrix[0] = 1.0f;
		g_worldMatrix[1] = 0.0f;
		g_worldMatrix[2] = 0.0f;
		g_worldMatrix[3] = 0.0f;
		g_worldMatrix[4] = 0.0f;
		g_worldMatrix[5] = 1.0f;
		g_worldMatrix[6] = 0.0f;
		g_worldMatrix[7] = 0.0f;
		g_worldMatrix[8] = 0.0f;
		g_worldMatrix[9] = 0.0f;
		g_worldMatrix[10] = 1.0f;
		g_worldMatrix[11] = 0.0f;
		g_worldMatrix[12] = 0.0f;
		g_worldMatrix[13] = 0.0f;
		g_worldMatrix[14] = 0.0f;
		g_worldMatrix[15] = 1.0f;
		TheBoxTextureDirtyMask = mask;
	}

	DX8Wrapper::Apply_Render_State_Changes();

	Device *dev = ScreenDevice;
	((SetRenderStateFn)dev->vt[0xE4 / 4])(dev, 0x34, 1);
	((SetRenderStateFn)dev->vt[0xE4 / 4])(dev, 0x38, 8);
	unsigned mask2 = TheTacticalView->mask;
	((SetRenderStateFn)dev->vt[0xE4 / 4])(dev, 0x3a, 0xffffffff);
	((SetRenderStateFn)dev->vt[0xE4 / 4])(dev, 0x3b, ~mask2);
	((SetShaderStageFn)dev->vt[0x170 / 4])(dev, 0);
	((SetShaderStageFn)dev->vt[0x164 / 4])(dev, 2);
}
