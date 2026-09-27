// ?Render@Render2DClass@@QAEXXZ
// partial score=0.7116625310173698 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I. /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Oy
// Partial Render2DClass::Render at RVA 0x00933E50, extent 2015 bytes.
// Identity: matched Render2DSentenceClass::Render calls this body.
// BFME constructor independently places vertices/indices at +0x14/+0x24 and
// texture at +0x4c; the later reference Render2D header has a different layout.
// Native body is 2013 bytes versus 2015 retail. Explicit byte-count locals
// retain one additional copy-expansion MOV; shader scheduling still differs.
// Positional masked score is 1434/2015, with 579 mismatched overlapping bytes
// and two absent bytes. Normalized instruction shape is 0.983, not acceptance.
// Frame and complete control flow remain intact. Earlier 2011-byte bank is
// preserved in attempt_history. No new callee pins are required by this draft.
// stlport
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "game/Libraries/Source/WWVegas/WW3D2/render2d.h"
#include "game/Libraries/Source/WWVegas/WW3D2/vertmaterial.h"
#include "game/Libraries/Source/WWVegas/WW3D2/shader.h"
#include "wwdebug.h"
#include "game/Libraries/Source/WWVegas/WW3D2/ww3d.h"
#include "game/Libraries/Source/WWVegas/WW3D2/rinfo.h"
#include "game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h"
#include "game/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h"
#include "game/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h"
#include "game/Libraries/Source/WWVegas/WW3D2/dx8fvf.h"

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

class Rva00933E50TextureRef
{
	TextureBaseClass *Texture;

public:
	Rva00933E50TextureRef() : Texture(NULL) {}
	~Rva00933E50TextureRef() { if (Texture) Texture->Release_Ref(); }
	operator TextureBaseClass *&() { return Texture; }
};


struct Rva00933E50Resolution : DX8Wrapper {
 using DX8Wrapper::Get_Device_Resolution_Width;
 using DX8Wrapper::Get_Device_Resolution_Height;
};
extern int g_bfmeFirstEB, g_bfmeThirdEB, g_bfmeFourthEB, g_bfmeFifthEB;
struct Rva00933E50RawArray {
 void *Data; int Size, m_count, GrowthStep;
 int Count() const { return m_count; }
};
struct Rva00933E50RenderView {
 unsigned Shader; float CoordinateScale[2], CoordinateOffset[2];
 Rva00933E50RawArray Vertices, Indices;
 char m_unreconstructed_34[0x18];
 TextureBaseClass *Texture;
};
void Render2DClass::Render()
{
 Rva00933E50RenderView *self = (Rva00933E50RenderView *)this;
 if (!self->Vertices.Count()) return;
 Matrix4 view, proj;
 Matrix4 identity(true);
 DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
 DX8Wrapper::Get_Transform(D3DTS_PROJECTION, proj);
 int width=Rva00933E50Resolution::Get_Device_Resolution_Width();
 int height=Rva00933E50Resolution::Get_Device_Resolution_Height();
 D3DVIEWPORT8 vp;
 vp.X=0;vp.Y=0;vp.Width=width;vp.Height=height;vp.MinZ=0;vp.MaxZ=1;
 DX8Wrapper::Set_Viewport(&vp);
 VertexMaterialClass *vm=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 DX8Wrapper::Set_Material(vm);
 REF_PTR_RELEASE(vm);
 DX8Wrapper::Set_World_Identity();
 DX8Wrapper::Set_View_Identity();
 DX8Wrapper::Set_Transform(D3DTS_PROJECTION,identity);
 BoxDynamicVBAccessClass vb(BUFFER_TYPE_DYNAMIC_DX8,5,self->Vertices.Count(),0);
 DynamicIBAccessClass ib(BUFFER_TYPE_DYNAMIC_DX8,self->Indices.Count());
 {
  BoxDynamicVBAccessClass::WriteLockClass vertices(&vb);
  int vertexCount = self->Vertices.Count();
  unsigned vertexBytes = vertexCount * 44;
  memcpy(vertices.Get_Formatted_Vertex_Array(),self->Vertices.Data,vertexBytes);
  DynamicIBAccessClass::WriteLockClass indices(&ib);
  int indexCount = self->Indices.Count();
  unsigned indexBytes = indexCount * 2;
  memcpy(indices.Get_Index_Array(),self->Indices.Data,indexBytes);
 }
 DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&vb));
 DX8Wrapper::Set_Index_Buffer(ib,0);
 BoxSetTexture(0,self->Texture);
 unsigned depth=(g_bfmeFirstEB&0xffffe703)|0x22302;
 unsigned blend=((g_bfmeFourthEB<<9)|g_bfmeFifthEB)<<5;
 unsigned compare=g_bfmeThirdEB&0xffff3f1f;
 blend|=compare; blend&=0xfffff8ff; depth<<=3; blend|=depth; ShaderClass shader(blend);
 DX8Wrapper::Set_Shader(shader);
 DX8Wrapper::Draw_Triangles(0,(unsigned)self->Indices.Count()/3,0,self->Vertices.Count());
 DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
 DX8Wrapper::Set_Transform(D3DTS_PROJECTION,proj);
 BoxSetTexture(0,Rva00933E50TextureRef());
}
