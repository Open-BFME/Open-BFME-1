// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
#include "dx8wrapper.h"
#include "ww3d.h"

// stlport
// RVA 0x007158F0 +511, named RTS3DScene::Render callers and GeneralsMD
// W3DScene.cpp Flush establish identity. BFME adds shader mesh dispatch,
// explicit stencil state setup and a second translucent/particle phase.
// Retail witnesses custom pass +0x868, extra polygon pass +0x18, vector
// start/finish +0x890/+0x894, local player +0xc and player index +0x24.
// The two anonymous helpers retain their established ILT identities and
// typed member-call views (ret 4 / ret 16), as in RTS3DSceneRva00715530.cpp.
// clear(), rather than spelling erase directly, preserves native STLport
// inline copy shape. No shared ZH scene header/layout is changed.
#include <vector>
class RenderInfoClass;
class RenderObjClass;
class DX8MeshRendererClass { public: void Flush(); void Clear_Pending_Delete_Lists(); };
extern DX8MeshRendererClass *TheDX8MeshRenderer;
struct IDirect3DDevice8;
struct Rva01340534DeviceVTable {
 void *slots[0x170/4];
 long (__stdcall *SetVertexShader)(IDirect3DDevice8*,unsigned long);
};



class SortingRendererClass { public: static void Flush(); };
class Player { char pad00[0x24]; public: int m_playerIndex; };
class PlayerList { char pad00[0xc]; public: Player *m_localPlayer; };
extern PlayerList *ThePlayerList;
void DoShadows(RenderInfoClass&,bool);
void DoTrees(RenderInfoClass&);
void bfmeDispatch_006CDF70(void*,void*);
void Rva006FA040Invoke(int);
void bfmeGo991B(int);
void j_00001299();
void j_00017238();
struct Rva00714810View { void call(RenderInfoClass&); };
struct Rva00713780View { void call(RenderInfoClass&,RenderObjClass*,int,int); };
class RTS3DScene {
 char pad000[0x18];
 int m_extraPassPolyMode;
 char pad01c[0x868-0x1c];
 int m_customPassMode;
 char pad86c[0x890-0x86c];
 std::vector<RenderObjClass*> m_shaderMeshes;
protected:
 void flushTranslucentObjects(RenderInfoClass&);
 void rva00715530(RenderInfoClass&);
public:
 void Flush(RenderInfoClass&);
 void flushOccluded(RenderInfoClass &r) {
  union { void (*f)(); void (Rva00714810View::*m)(RenderInfoClass&); } fn;
  fn.f=j_00001299;
  (((Rva00714810View*)this)->*fn.m)(r);
 }
 void renderMesh(RenderInfoClass &r,RenderObjClass *o,int i) {
  union { void (*f)(); void (Rva00713780View::*m)(RenderInfoClass&,RenderObjClass*,int,int); } fn;
  fn.f=j_00017238;
  (((Rva00713780View*)this)->*fn.m)(r,o,i,1);
 }
};
void RTS3DScene::Flush(RenderInfoClass &rinfo) {
 TheDX8MeshRenderer->Flush();
 if(m_customPassMode==0) {
  if(DX8Wrapper::Has_Stencil()) flushOccluded(rinfo);
  if(!m_shaderMeshes.empty()) {
   for(std::vector<RenderObjClass*>::iterator it=m_shaderMeshes.begin();it!=m_shaderMeshes.end();++it)
    renderMesh(rinfo,*it,ThePlayerList?ThePlayerList->m_localPlayer->m_playerIndex:0);
   m_shaderMeshes.clear();
  }
  if(m_customPassMode==0 && m_extraPassPolyMode==0) DoShadows(rinfo,false);
 }
 if(DX8Wrapper::Has_Stencil()) {
  (*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(52,1);
  (*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(57,0);
  (*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(58,-1);
  (*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(59,-1);
  (*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(56,8);
  (*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(54,1);
  (*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(53,1);
  (*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(55,3);
 }
 DoTrees(rinfo);
 (*static_cast<void (*)(unsigned long, unsigned)>(&DX8Wrapper::Set_DX8_Render_State))(52,0);
 if(m_customPassMode==0 && m_extraPassPolyMode==0) DoShadows(rinfo,true);
 (*reinterpret_cast<Rva01340534DeviceVTable **>(DX8Wrapper::_Get_D3D_Device8()))->SetVertexShader(DX8Wrapper::_Get_D3D_Device8(), 0);
 WW3D::Render_And_Clear_Static_Sort_Lists(rinfo);
 if(m_customPassMode==0) {
  bfmeDispatch_006CDF70(&rinfo,(void*)1);
  bfmeDispatch_006CDF70(&rinfo,0);
  if(m_customPassMode==0) {
   if(m_extraPassPolyMode==0) flushTranslucentObjects(rinfo);
   if(m_customPassMode==0 && m_extraPassPolyMode==0) Rva006FA040Invoke((int)&rinfo);
  }
 }
 SortingRendererClass::Flush();
 if(m_customPassMode==0) {
  if(m_extraPassPolyMode==0) rva00715530(rinfo);
  if(m_customPassMode==0 && m_extraPassPolyMode==0) bfmeGo991B((int)&rinfo);
 }
 SortingRendererClass::Flush();
 TheDX8MeshRenderer->Clear_Pending_Delete_Lists();
}
