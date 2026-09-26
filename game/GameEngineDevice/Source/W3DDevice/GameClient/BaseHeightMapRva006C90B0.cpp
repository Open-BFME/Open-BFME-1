// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Retail 0x006C90B0, complete boundary [0x006C90B0,0x006C921F).
// The BaseHeightMap constructor at 0x006CFAE0 installs the primary vtable and
// constructs the W3DTreeBuffer stored at +0x3094.  Its 0x006C5690 getter
// returns the owning one-pointer texture handle through hidden result storage.
// The public spelling of this no-argument helper is not recovered, so the
// method name remains address-derived.

#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "rendobj.h"
#include "shader.h"
#include "dx8wrapper.h"

struct Rva006C9270GlobalData
{
	unsigned char m_unmodeled00[0x65];
	unsigned char m_renderFeatureEnabled;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

// BFME's TextureBaseClass release is the matched out-of-line 0x009EB7A0
// method.  The ZH header exposes a different inline refcount implementation,
// so retain the same ABI hider already used by W3DShaderManager's owning
// texture handles.
class BFMETextureRelease
{
public:
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	~BfmeHandleCX(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	operator TextureBaseClass *&(void)
	{
		return *(TextureBaseClass **)&m_texture;
	}

private:
	BFMETextureRelease *m_texture;
};

// This is the already matched by-value getter ABI at 0x006C5690.  The object
// occupying BaseHeightMapRenderObjClass+0x3094 is the W3DTreeBuffer; this
// neutral view keeps the existing getter identity until its public spelling is
// independently recovered.
class Gen_006C5690
{
public:
	BfmeHandleCX bfmeGet(void) const;
};

extern void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);
extern void BaseHeightMapScorchSetZBias(int bias);

class BaseHeightMapRenderObjClass : public RenderObjClass
{
public:
	void rva006C90B0(void);

private:
	unsigned char m_unmodeledBaseHeightMap[0x2fd8 - sizeof(RenderObjClass)];
	// This is a second, independently observed render-buffer family.  The
	// protected scorch buffers occupy +0xD0/+0xD4/+0xD8 instead.
	VertexBufferClass *m_buffer2FD8;          // +0x2FD8
	IndexBufferClass *m_buffer2FDC;           // +0x2FDC
	TextureBaseClass *m_resource2FE0;         // +0x2FE0
	int m_count2FE4;                          // +0x2FE4
	int m_count2FE8;                          // +0x2FE8
	unsigned char m_unmodeled2FEC[0x3094 - 0x2fec];
	Gen_006C5690 *m_treeBuffer;              // +0x3094
};

void BaseHeightMapRenderObjClass::rva006C90B0(void)
{
	if (!TheWritableGlobalData->m_renderFeatureEnabled ||
		!m_resource2FE0 ||
		!m_count2FE4 ||
		!m_count2FE8 ||
		Is_Hidden())
	{
		return;
	}

	DX8Wrapper::Set_Shader(ShaderClass::_PresetAlphaShader);
	DX8Wrapper::Set_Index_Buffer(m_buffer2FDC, 0);
	DX8Wrapper::Set_Vertex_Buffer(m_buffer2FD8, 0);
	BoxSetTexture(0, (TextureBaseClass *&)m_treeBuffer->bfmeGet());

	BaseHeightMapScorchSetZBias(1);
	DX8Wrapper::Draw_Triangles(
		0,
		(unsigned short)(m_count2FE8 / 3),
		0,
		(unsigned short)m_count2FE4);
	BaseHeightMapScorchSetZBias(0);
}
