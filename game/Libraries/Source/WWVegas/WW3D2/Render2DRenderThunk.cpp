// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I. /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Oy
// ?Render@Render2DClass@@QAEXXZ
// Open-BFME: retail 0x00933E50, 2015 bytes (RET at 0x0093462E, then INT3).
// Identity: the matched ?Render@Render2DSentenceClass@@QAEXXZ calls this body
// for each of its renderers, as Zero Hour's Render2DSentenceClass::Render does.
//
// Zero Hour render2d.cpp Render2DClass::Render rebuilt on BFME 1's flat 2D
// batch: save view/projection, full-screen viewport, PRELIT_DIFFUSE material,
// block-copy the prebuilt 44-byte vertices and the indices into dynamic DX8
// buffers, bind the texture, build the shader from the five 2D shader
// globals, draw, restore. The BFME constructor (0x009336E0) places vertices
// at +0x14, indices at +0x24 and the texture at +0x4C.
//
// [BFME 2 donor] open-bfme-2 76f0baefa6
// Code/Libraries/Source/WWVegas/WW3D2/Render2DClassRender.cpp (BFME 2
// 0x0011A040, 7476 B, which adds a seven-mode batch loop and dot3/stencil
// states BFME 1 lacks) supplied the two shapes the earlier 0.71 bank missed:
// the array's bounds-checked Get(0) element pointer as the memcpy source
// (it keeps retail's count copy before the size multiply) and a default
// ShaderClass configured by setters (depth mask, depth compare, source and
// destination blend from the globals, fog off, primary gradient 6,
// texturing on), which VC7.1 folds into retail's merged bit expression.
// stlport
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "game/Libraries/Source/WWVegas/WW3D2/vertmaterial.h"
#include "game/Libraries/Source/WWVegas/WW3D2/shader.h"
#include "wwdebug.h"
#include "game/Libraries/Source/WWVegas/WW3D2/ww3d.h"
#include "game/Libraries/Source/WWVegas/WW3D2/rinfo.h"
#include "game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h"
#include "game/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h"
#include "game/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h"
#include "game/Libraries/Source/WWVegas/WW3D2/dx8fvf.h"

// BFME's box-sized dynamic vertex buffer access (constructor 0x0091F730,
// write lock 0x0091F160/0x0091F240); DX8Wrapper::Set_Vertex_Buffer takes it
// as a DynamicVBAccessClass.
class BoxDynamicVBAccessClass
{
	const FVFInfoClass & FVFInfo;
	unsigned Type;
	unsigned FVF;
	unsigned Start;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	class BoxVertexBufferClass * VertexBuffer;

public:
	BoxDynamicVBAccessClass(unsigned type,unsigned fvf,unsigned short vertex_count,unsigned buffer);
	~BoxDynamicVBAccessClass();

	const FVFInfoClass & FVF_Info() const { return FVFInfo; }

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;

	public:
		WriteLockClass(BoxDynamicVBAccessClass *vb_access);
		~WriteLockClass();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

extern void BoxSetTexture(unsigned stage,TextureBaseClass *& texture);

// The 2D shader settings (reset by 0x009336B0 and the Render2DClass constructor).
extern int g_bfmeFirstEB, g_bfmeThirdEB, g_bfmeFourthEB, g_bfmeFifthEB;

// A temporary texture handle that releases what it holds; Render ends by
// clearing stage 0 through one.
class Render2DTextureRef
{
	TextureBaseClass *Texture;

public:
	Render2DTextureRef() : Texture(NULL) {}
	~Render2DTextureRef() { if (Texture) Texture->Release_Ref(); }
	operator TextureBaseClass *&() { return Texture; }
};

// The device resolution accessors are protected in DX8Wrapper.
struct Render2DResolution : DX8Wrapper
{
	using DX8Wrapper::Get_Device_Resolution_Width;
	using DX8Wrapper::Get_Device_Resolution_Height;
};

struct Render2DVertex
{
	char Bytes[44];		// VertexFormatXYZNDUV2-sized, prebuilt by the Add_* helpers
};

template<class T> struct Render2DArray
{
	T *Data;
	int Size;
	int ActiveCount;
	int GrowthStep;

	unsigned Length() const { return ActiveCount; }
	T *Get(unsigned i) { if (i >= (unsigned)ActiveCount) return Data; return Data + i; }
};

class Render2DClass
{
public:
	void Render();

private:
	ShaderClass Shader;
	float CoordinateScale[2];
	float CoordinateOffset[2];
	Render2DArray<Render2DVertex> Vertices;		// +0x14
	Render2DArray<unsigned short> Indices;		// +0x24
	char m_unknown34[0x18];
	TextureBaseClass *Texture;					// +0x4C
};

void Render2DClass::Render()
{
	if (!Vertices.Length())
		return;

	// save the view and projection matrices since we're nuking them
	Matrix4x4 view, proj;
	Matrix4x4 identity(true);
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
	DX8Wrapper::Get_Transform(D3DTS_PROJECTION, proj);

	//	Configure the viewport for entire screen
	int width = Render2DResolution::Get_Device_Resolution_Width();
	int height = Render2DResolution::Get_Device_Resolution_Height();
	D3DVIEWPORT8 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = width;
	vp.Height = height;
	vp.MinZ = 0;
	vp.MaxZ = 1;
	DX8Wrapper::Set_Viewport(&vp);

	VertexMaterialClass *vm = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vm);
	REF_PTR_RELEASE(vm);

	DX8Wrapper::Set_World_Identity();
	DX8Wrapper::Set_View_Identity();
	DX8Wrapper::Set_Transform(D3DTS_PROJECTION, identity);

	BoxDynamicVBAccessClass vb(BUFFER_TYPE_DYNAMIC_DX8, 5, Vertices.Length(), 0);
	DynamicIBAccessClass ib(BUFFER_TYPE_DYNAMIC_DX8, Indices.Length());
	{
		BoxDynamicVBAccessClass::WriteLockClass vlock(&vb);
		memcpy(vlock.Get_Formatted_Vertex_Array(), Vertices.Get(0), Vertices.Length() * sizeof(Render2DVertex));
		DynamicIBAccessClass::WriteLockClass ilock(&ib);
		memcpy(ilock.Get_Index_Array(), Indices.Get(0), Indices.Length() * sizeof(unsigned short));
	}

	DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&vb));
	DX8Wrapper::Set_Index_Buffer(ib, 0);
	BoxSetTexture(0, Texture);

	ShaderClass shader;
	shader.Set_Depth_Mask((ShaderClass::DepthMaskType)g_bfmeFirstEB);
	shader.Set_Depth_Compare((ShaderClass::DepthCompareType)g_bfmeThirdEB);
	shader.Set_Src_Blend_Func((ShaderClass::SrcBlendFuncType)g_bfmeFourthEB);
	shader.Set_Dst_Blend_Func((ShaderClass::DstBlendFuncType)g_bfmeFifthEB);
	shader.Set_Fog_Func(ShaderClass::FOG_DISABLE);
	shader.Set_Primary_Gradient((ShaderClass::PriGradientType)6);
	shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
	DX8Wrapper::Set_Shader(shader);

	DX8Wrapper::Draw_Triangles(0, Indices.Length() / 3, 0, Vertices.Length());

	DX8Wrapper::Set_Transform(D3DTS_VIEW, view);
	DX8Wrapper::Set_Transform(D3DTS_PROJECTION, proj);
	BoxSetTexture(0, Render2DTextureRef());
}
