// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /MD
#include "dx8wrapper.h"

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

static inline int decrementRef(int *p) { return --*p; }

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.h


extern VertexMaterialClass *ScreenMaterial;      // 0x1340EC4 -- shared model global
extern unsigned TheBoxTextureDirtyMask;          // 0x133F49C -- shared model global

class ShaderClass;

// Not _PresetOpaqueShader: retail passes the shadow buffer's own shader at 0x012BBF14
// (bits 0x00101823; Opaque's are 0x0011581B), as the draw path does.
extern ShaderClass Rva012BBF14Shader;



extern float g_worldMatrix[16];   // 0x134108C, one 4x4 identity matrix

struct Device { void **vt; };

typedef long (__stdcall *SetRenderStateFn)(Device *, unsigned, unsigned);
typedef long (__stdcall *SetShaderStageFn)(Device *, unsigned);

// Retail's shadow-manager global at 0x01306EEC is `W3DShadowManager
// *TheW3DShadowManager`, the same name the W3D shadow TUs already use.  The
// class here is a stand-in, and retail mangles `class`/`struct` into the data
// symbol (PAV vs PAU), so it must be a class spelled as retail spells it.
class W3DShadowManager { public: unsigned char pad[8]; unsigned mask; };
extern W3DShadowManager *TheW3DShadowManager;   // 0x1306EEC

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
		vmat->Add_Ref();

	if (ScreenMaterial)
		ScreenMaterial->Release_Ref();

	unsigned dirty = TheBoxTextureDirtyMask | 0x4000;
	ScreenMaterial = vmat;
	TheBoxTextureDirtyMask = dirty;
	if (vmat) {
		vmat->Release_Ref();
	}

	(*static_cast<void (*)(const ShaderClass &)>(&DX8Wrapper::Set_Shader))(Rva012BBF14Shader);
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

	Device *dev = reinterpret_cast<Device *>(DX8Wrapper::_Get_D3D_Device8());
	((SetRenderStateFn)dev->vt[0xE4 / 4])(dev, 0x34, 1);
	((SetRenderStateFn)dev->vt[0xE4 / 4])(dev, 0x38, 8);
	unsigned mask2 = TheW3DShadowManager->mask;
	((SetRenderStateFn)dev->vt[0xE4 / 4])(dev, 0x3a, 0xffffffff);
	((SetRenderStateFn)dev->vt[0xE4 / 4])(dev, 0x3b, ~mask2);
	((SetShaderStageFn)dev->vt[0x170 / 4])(dev, 0);
	((SetShaderStageFn)dev->vt[0x164 / 4])(dev, 2);
}
