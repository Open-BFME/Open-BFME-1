// ?render@Rva00934940Renderer@@QAEXXZ
// partial score=0.479763199226773 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I. /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Oy
// Anonymous batched renderer at RVA 0x00934940, full extent 8277 bytes.
// The matched Render2DClass::Reset at 0x00934820 independently witnesses this
// physical owner; Render2DClass::Render is a distinct body at 0x00933E50.
// Keep this member address-derived. The seven batch lists hold linked vertex
// records whose index ranges are copied before the texture/stencil draw pass.
// Bank only: 8275 emitted bytes, 4304 probe-masked differing positions, score
// 0.479763199226773 after the two-byte extent penalty; normalized shape .992.
// See targets/game/reverse/identity_evidence/00934940-batched-renderer.md.
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

class Rva00934940TextureRef
{
	TextureBaseClass *Texture;

public:
	Rva00934940TextureRef() : Texture(NULL) {}
	~Rva00934940TextureRef() { if (Texture) Texture->Release_Ref(); }
	operator TextureBaseClass *&() { return Texture; }
};


struct Rva00934940Resolution : DX8Wrapper {
 using DX8Wrapper::Get_Device_Resolution_Width;
 using DX8Wrapper::Get_Device_Resolution_Height;
};
extern int g_bfmeFirstEB, g_bfmeSecondEB, g_bfmeThirdEB, g_bfmeFourthEB, g_bfmeFifthEB;
extern unsigned Rva012D7180;
struct Rva00934940RawArray {
 void *Data; int Size, m_count, GrowthStep;
 int Count() const { return m_count; }
};

// Scoped copy of the canonical state-cache operation. BFME's aligned device
// calls use slot 67; the inherited SDK shim places this method at slot 70.
// Matched DX8Wrapper::Set_DX8_Texture_Stage_State_Body at 0x006C5840 and
// ApplyDefaultState at 0x009095A0 independently establish the slot and ABI.
struct Rva00934940DX8 : DX8Wrapper {
 static WWINLINE void Set_DX8_Texture_Stage_State(unsigned stage,D3DTEXTURESTAGESTATETYPE state,unsigned value){
  if(stage>=MAX_TEXTURE_STAGES){
   typedef HRESULT(__stdcall *SetStage)(IDirect3DDevice8*,unsigned,D3DTEXTURESTAGESTATETYPE,unsigned);
   IDirect3DDevice8 *device=_Get_D3D_Device8();
   (*(SetStage**)device)[67](device,stage,state,value);
   ++number_of_DX8_calls;
   return;
  }
  if(TextureStageStates[stage][(unsigned)state]==value)return;
  if(WW3D::Is_Snapshot_Activated()){
   StringClass value_name(0,true);
   Get_DX8_Texture_Stage_State_Value_Name(value_name,state,value);
  }
  TextureStageStates[stage][(unsigned)state]=value;
  typedef HRESULT(__stdcall *SetStage)(IDirect3DDevice8*,unsigned,D3DTEXTURESTAGESTATETYPE,unsigned);
  IDirect3DDevice8 *device=_Get_D3D_Device8();
  (*(SetStage**)device)[67](device,stage,state,value);
  ++number_of_DX8_calls;
  DX8_RECORD_TEXTURE_STAGE_STATE_CHANGE();
 }
};
struct Rva00934940CapsView {
 char unknown00[0x272];
 bool rvaField272;
 char unknown273[5];
 int rvaField278;
};
static __forceinline Rva00934940CapsView *CapsView(){return reinterpret_cast<Rva00934940CapsView*>(const_cast<DX8Caps*>(DX8Wrapper::Get_Current_Caps()));}
struct Rva00934940Vertex {
 float Position[3];
 unsigned Next, FirstIndex, IndexCount;
 unsigned Color;
 float UV[4];
};
struct Rva00934940Batch {
 bool operator==(const Rva00934940Batch&)const;
 bool operator!=(const Rva00934940Batch&)const;
 TextureBaseClass *Texture;
 int Head[7];
 int Unknown20[14];
 int IndexCount[7];
};
struct Rva00934940View {
 unsigned Shader;
 float CoordinateScale[2],CoordinateOffset[2];
 Rva00934940RawArray Vertices,Indices;
 DynamicVectorClass<Rva00934940Batch> Batches;
 TextureBaseClass *Texture;
 int CurrentBatch;
 bool IsDirty;
 Rva00934940Vertex *GetVertex(unsigned n) {
  if(n>=(unsigned)Vertices.Count())return (Rva00934940Vertex*)Vertices.Data;
  return (Rva00934940Vertex*)Vertices.Data+n;
 }
 unsigned short *GetIndex(unsigned n) {
  if(n>=(unsigned)Indices.Count())return (unsigned short*)Indices.Data;
  return (unsigned short*)Indices.Data+n;
 }

};
class Rva00934940Renderer {public:void render();};
void Rva00934940Renderer::render()
{
 Rva00934940View *self=reinterpret_cast<Rva00934940View*>(this);
 if(!self->Vertices.Count())return;
 Matrix4 view,proj;
 Matrix4 identity(true);
 DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
 DX8Wrapper::Get_Transform(D3DTS_PROJECTION,proj);
 D3DVIEWPORT8 vp;
 vp.X=0;vp.Y=0;
 vp.Width=Rva00934940Resolution::Get_Device_Resolution_Width();
 vp.Height=Rva00934940Resolution::Get_Device_Resolution_Height();
 vp.MinZ=0;vp.MaxZ=1;
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
  memcpy(vertices.Get_Formatted_Vertex_Array(),self->Vertices.Data,self->Vertices.Count()*44);
  DynamicIBAccessClass::WriteLockClass indices(&ib);
  unsigned short *output=indices.Get_Index_Array();
  for(unsigned batch=0;batch<(unsigned)self->Batches.Count();++batch){
   Rva00934940Batch &b=self->Batches[batch];
   BoxSetTexture(0,b.Texture);
   for(unsigned kind=0;kind<7;++kind){
    if(b.Head[kind]>=0){
     Rva00934940Vertex *v=self->GetVertex(b.Head[kind]);
     while(v){
      memcpy(output,self->GetIndex(v->FirstIndex),v->IndexCount*2);
      output+=v->IndexCount;
      v=v->Next?self->GetVertex(v->Next):NULL;
     }
    }
   }
  }
 }
 DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass*>(&vb));
 DX8Wrapper::Set_Index_Buffer(ib,0);
 bool changed=false;
 int startIndex=0;
 for(unsigned batch=0;batch<(unsigned)self->Batches.Count();++batch){
  Rva00934940Batch &b=self->Batches[batch];
  BoxSetTexture(0,b.Texture);
  for(unsigned kind=0;kind<7;++kind){
   if(b.Head[kind]<0)continue;
   if(changed){
    changed=false;
    BoxSetTexture(1,Rva00934940TextureRef());
    if(CapsView()->rvaField278>=3){
     BoxSetTexture(2,Rva00934940TextureRef());
     Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_TEXCOORDINDEX,2);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_COLOROP,D3DTOP_DISABLE);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAOP,D3DTOP_DISABLE);
    }
    ShaderClass::Invalidate();
   }
   unsigned depth=(g_bfmeFirstEB&0xffffe703)|0x22302;
   unsigned blend=((g_bfmeFourthEB<<9)|g_bfmeFifthEB)<<5;
   unsigned compare=g_bfmeThirdEB&0xffff3f1f;
   blend|=compare;blend&=0xfffff8ff;depth<<=3;blend|=depth;
   if(!b.Texture)blend&=0xfffeffff;
   if(kind==5)blend=(blend&0xfff7ffff)|0x40000;
   else blend&=0xfff3ffff;
   blend&=0xffefffff;
   if(kind==0 || kind==4 || kind==5)blend=(blend&0xffff7f1f)|0x4000;
   else if(kind==1)blend=(blend&0xffff7f3f)|0x4020;
   DX8Wrapper::Set_Shader(ShaderClass(blend));
   if(kind==6){
    if(b.Texture){
     changed=true;
     DX8Wrapper::Apply_Render_State_Changes();
     Rva00934940DX8::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);
    }
   }else if(kind==3 || kind==4){
    changed=true;
    DX8Wrapper::Apply_Render_State_Changes();
    if(!CapsView()->rvaField272 || CapsView()->rvaField278<3){
     DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR,0x60606060);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG2,D3DTA_TFACTOR);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
    }else{
     BoxSetTexture(1,b.Texture);BoxSetTexture(2,b.Texture);
     DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR,0x8092A587);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG0,D3DTA_TFACTOR|D3DTA_ALPHAREPLICATE);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(0,D3DTSS_COLORARG2,D3DTA_TFACTOR|D3DTA_ALPHAREPLICATE);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(0,D3DTSS_COLOROP,D3DTOP_MULTIPLYADD);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(1,D3DTSS_COLORARG1,D3DTA_CURRENT);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(1,D3DTSS_COLORARG2,D3DTA_TFACTOR);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(1,D3DTSS_COLOROP,D3DTOP_DOTPRODUCT3);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_TEXCOORDINDEX,0);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_COLORARG1,D3DTA_CURRENT);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(3,D3DTSS_COLOROP,D3DTOP_DISABLE);
     Rva00934940DX8::Set_DX8_Texture_Stage_State(3,D3DTSS_ALPHAOP,D3DTOP_DISABLE);
    }
   }
   if(g_bfmeSecondEB){
    DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE,TRUE);
    DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF,Rva012D7180);
    DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK,0xffffffff);
    DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILWRITEMASK,0xffffffff);
    DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);
    DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);
    if(g_bfmeSecondEB==2){
     DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);
     DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL,D3DSTENCILOP_REPLACE);
    }else if(g_bfmeSecondEB==1){
     DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC,D3DCMP_EQUAL);
     DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFAIL,D3DSTENCILOP_KEEP);
    }
   }
   DX8Wrapper::Draw_Triangles(startIndex,b.IndexCount[kind]/3,0,self->Vertices.Count());
   startIndex+=b.IndexCount[kind];
  }
 }
 DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
 DX8Wrapper::Set_Transform(D3DTS_PROJECTION,proj);
 BoxSetTexture(0,Rva00934940TextureRef());
 if(changed){
  BoxSetTexture(1,Rva00934940TextureRef());
  if(CapsView()->rvaField278>=3){
   BoxSetTexture(2,Rva00934940TextureRef());
   Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_TEXCOORDINDEX,2);
   Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_COLOROP,D3DTOP_DISABLE);
   Rva00934940DX8::Set_DX8_Texture_Stage_State(2,D3DTSS_ALPHAOP,D3DTOP_DISABLE);
  }
  ShaderClass::Invalidate();
 }
 if(g_bfmeSecondEB)DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE,FALSE);
 reinterpret_cast<Render2DClass*>(this)->Render2DClass::Reset();
}
