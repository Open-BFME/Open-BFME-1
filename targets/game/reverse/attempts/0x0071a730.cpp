// ?method@Rva0071A730@@QAEXXZ
// partial score=1.0 date=2026-10-03
// Retail 0x0071A730..0x0071AFC5 RET0; opaque receiver and method.
// Texture literals are inputs, not proof of a W3DShrubBuffer owner.
// D3DX wrappers and COM slots follow the raw retail instructions.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#define private public
#define protected public
#include "dx8wrapper.h"
#undef private
#undef protected
#include "d3dx8math.h"

class Gen_00920a60 { public: void m(int); };
class ShroudFilter;
class ShroudTexture { public: ShroudFilter *getFilter(); };
class BFMEWaterTrackTextureHandle { public:
 TextureClass *m_texture;
 ~BFMEWaterTrackTextureHandle() { if(m_texture) m_texture->Release_Ref(); }
};
extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *,int,int);
extern void BoxSetTexture(unsigned,TextureBaseClass *&);
extern ShaderClass Rva00ED6E18;
struct Rva0071A730Filter { char pad0[12]; int field0c,field10; };
struct Rva0071A730Texture { TextureClass *p;
 void assign(const BFMEWaterTrackTextureHandle &v) { if(v.m_texture) v.m_texture->Add_Ref(); if(p) p->Release_Ref(); p=v.m_texture; }
 ShroudFilter *filter() { return ((ShroudTexture*)this)->getFilter(); }
};
struct Rva0071A730View { 
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual void slot4()=0;
virtual void slot5()=0;
virtual void slot6()=0;
virtual void slot7()=0;
virtual void slot8()=0;
virtual void slot9()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual int field3c()=0;
virtual void slot16()=0;
virtual int field44()=0;
virtual void slot18()=0;
virtual void field4c(int*,int*)=0;
virtual void slot20()=0;
virtual void slot21()=0;
virtual void slot22()=0;
virtual void slot23()=0;
virtual void slot24()=0;
virtual void slot25()=0;
virtual void slot26()=0;
virtual void slot27()=0;
virtual void slot28()=0;
virtual void slot29()=0;
virtual void slot30()=0;
virtual void slot31()=0;
virtual void slot32()=0;
virtual void slot33()=0;
virtual void slot34()=0;
virtual void slot35()=0;
virtual void slot36()=0;
virtual void slot37()=0;
virtual void slot38()=0;
virtual void slot39()=0;
virtual void slot40()=0;
virtual void slot41()=0;
virtual void slot42()=0;
virtual void slot43()=0;
virtual void slot44()=0;
virtual void slot45()=0;
virtual void slot46()=0;
virtual void slot47()=0;
virtual void slot48()=0;
virtual void slot49()=0;
virtual void slot50()=0;
virtual void slot51()=0;
virtual void slot52()=0;
virtual void slot53()=0;
virtual void slot54()=0;
virtual void slot55()=0;
virtual void slot56()=0;
virtual void slot57()=0;
virtual void slot58()=0;
virtual void slot59()=0;
virtual void slot60()=0;
virtual void slot61()=0;
virtual void slot62()=0;
virtual void slot63()=0;
virtual void slot64()=0;
virtual void slot65()=0;
virtual void slot66()=0;
virtual void slot67()=0;
virtual void slot68()=0;
virtual void slot69()=0;
virtual void slot70()=0;
virtual void slot71()=0;
virtual void slot72()=0;
virtual void slot73()=0;
virtual void slot74()=0;
virtual void slot75()=0;
virtual void slot76()=0;
virtual void slot77()=0;
virtual void slot78()=0;
virtual void slot79()=0;
virtual void slot80()=0;
virtual void slot81()=0;
virtual void slot82()=0;
virtual void slot83()=0;
virtual void slot84()=0;
virtual void slot85()=0;
virtual void slot86()=0;
virtual void slot87()=0;
virtual void slot88()=0;
virtual void field164(const int*,float*,float)=0;
};
extern Rva0071A730View *Rva00EF1600;
// The native shim operator multiplies inline; this ABI view retains retail's D3DX helper and return-value copy.
__forceinline D3DXMATRIX multiply(const D3DXMATRIX &a,const D3DXMATRIX &b) {
 D3DXMATRIX r; D3DXMatrixMultiply(&r,&a,&b); return r;
}
typedef HRESULT (__stdcall *GetMatrix)(IDirect3DDevice8*,DWORD,D3DXMATRIX*);
typedef HRESULT (__stdcall *SetMatrix)(IDirect3DDevice8*,DWORD,const D3DXMATRIX*);
typedef HRESULT (__stdcall *SetTSS)(IDirect3DDevice8*,DWORD,DWORD,DWORD);
__forceinline void setMatrix(unsigned n,const D3DXMATRIX &m) {
 DX8Wrapper::matrix_changes++;
 IDirect3DDevice8 *d=DX8Wrapper::_Get_D3D_Device8();
 (*(SetMatrix**)d)[44](d,n,&m); number_of_DX8_calls++;
}
#define SETTSS(stage,state,value) \
 if(DX8Wrapper::TextureStageStates[stage][state]!=value) { \
  if(WW3D::Is_Snapshot_Activated()) { StringClass name(0,true,StringClass::m_NullChar); DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(name,(D3DTEXTURESTAGESTATETYPE)state,value); } \
  DX8Wrapper::TextureStageStates[stage][state]=value; \
  IDirect3DDevice8 *d=DX8Wrapper::_Get_D3D_Device8(); (*(SetTSS**)d)[67](d,stage,state,value); \
  number_of_DX8_calls++; DX8Wrapper::texture_stage_state_changes++; \
 }
class Rva0071A730 { public:
 void method();
 char field00[0x38]; float field38; int field3c,field40; Rva0071A730Texture field44,field48; bool field4c;
};
void Rva0071A730::method() {
 float v=field38*field38*0.15000000596046448+field38*0.1f;
 if(!field4c) { field38+=0.011f; if(v>24.0f) v=24.0f; }
 float a,b;
 if(field3c==0) { a=v; b=0; } else { a=24; b=v; }
 ShaderClass::Invalidate();
 VertexMaterialClass *mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 DX8Wrapper::Set_Material(mat); if(mat) mat->Release_Ref();
 if(!field44.p) {
  field44.assign(BFMEGetWaterTrackTexture("darkcloud.tga",0,0));
  ((Rva0071A730Filter*)field44.filter())->field0c=1;
  ((Rva0071A730Filter*)field44.filter())->field10=1;
  ((Gen_00920a60*)field44.filter())->m(0);
 }
 if(!field48.p) {
  field48.assign(BFMEGetWaterTrackTexture("exmask_ci.tga",0,0));
  ((Rva0071A730Filter*)field48.filter())->field0c=1;
  ((Rva0071A730Filter*)field48.filter())->field10=1;
  ((Gen_00920a60*)field48.filter())->m(0);
 }
 BoxSetTexture(0,*(TextureBaseClass**)&field44.p); BoxSetTexture(1,*(TextureBaseClass**)&field48.p);
 ShaderClass shader=Rva00ED6E18; *(unsigned*)&shader=(*(unsigned*)&shader&0xfe9fffff)|0x800000;
 // Expand the header setter to retain its inlined StringClass lifetime.
 if(ShaderClass::ShaderDirty || *(unsigned*)&shader!=*(unsigned*)&DX8Wrapper::render_state.shader) {
  DX8Wrapper::render_state.shader=shader; DX8Wrapper::render_state_changed|=0x8000; StringClass str(0,false,StringClass::m_NullChar);
 }
 DX8Wrapper::Apply_Render_State_Changes();
 D3DXMATRIX current, inverse, scale, translate, center;
 IDirect3DDevice8 *d=DX8Wrapper::_Get_D3D_Device8(); (*(GetMatrix**)d)[45](d,2,&current); number_of_DX8_calls++;
 SETTSS(0,11,0x20000); SETTSS(0,24,2); SETTSS(1,11,0x20000); SETTSS(1,24,2);
 float det;
 D3DXMatrixInverse(&inverse,&det,&current);
 float world[3];
 if(Rva00EF1600) {
 int originx,originy,screen[2];
  Rva00EF1600->field4c(&originx,&originy);
  screen[0]=(int)(Rva00EF1600->field3c()*0.5f);
  screen[1]=(int)(Rva00EF1600->field44()*0.5f);
  Rva00EF1600->field164(screen,world,0.0f);
 }
 D3DXMatrixTranslation(&translate,-world[0],-world[1],0.0f);
 D3DXMatrixTranslation(&center,0.5f,0.5f,0.0f);
 if(a!=0) { float s=1.0f/(a*128.0f); D3DXMatrixScaling(&scale,s,s,1); current=multiply(multiply(multiply(inverse,translate),scale),center); }
 else { D3DXMatrixScaling(&scale,0,0,1); current=multiply(multiply(inverse,translate),scale); }
 setMatrix(16,current);
 if(b!=0) { float s=1.0f/(b*128.0f); D3DXMatrixScaling(&scale,s,s,1); current=multiply(multiply(multiply(inverse,translate),scale),center); }
 else { D3DXMatrixScaling(&scale,0,0,1); current=multiply(multiply(inverse,translate),scale); }
 setMatrix(17,current); field4c=true;
}

// Evidence: ret at RVA0071AFC5 followed by INT3; ILT00001AE6 targets body.
// EH FuncInfo VA0123C6A8 has six independent cleanup states, all prior=-1:
// states0/1 cleanup VA0104CAD0/CADB -> ILT00430652 (texture handle);
// states2..5 VA0104CAE6/CAF1/CAFC/CB07 -> ILT0041A41F (StringClass).
// Scoped strict build: 1/1 body2198B, 2 complete literals, 13 float constants,
// 81 DIR32 references verified. Full shared-header gate remains for the lead.
// Queue patch: /home/deck/bfme_astra2/header_queue/n1-0071A730-string-order.patch
// Original constructors stay untouched; only explicit volatile-terminator
// overload callers acquire char-first scheduling. D3DX helper returns by value
// preserve retail matrix copies; the native shim operator* instead expands math.
// Scope of origin/screen locals is material: outer-scope locals yield2209B and
// a 4-byte larger frame. Native string ctors yield2200B, not2198B.
