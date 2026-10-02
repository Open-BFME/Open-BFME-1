// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x007D31C0, 760 bytes. Same shape family as the landed twin
// Rva007DB820::set (0x007DAE30, also 760 B, ScreenFilterRva007DB820Set.cpp):
// fade ladder (fade direction/frames/current-frame/value globals), then
// the shared Get_Preset/ScreenMaterial swap, ScreenShaderDirty check,
// BoxSetTexture, and two inlined Set_DX8_Render_State calls. Original
// filter class name unknown; landed neighbours 0x007D1E60/0x007D1E80.
// Retail keeps ShaderClass::_PresetOpaqueShader (0x012D6E08) beside the screen
// filter's own shader cache word; shader.h declares the real identity.
#include "shader.h"
class StringClass {
 char *m_Buffer;
 static char *m_EmptyString; static char m_NullChar;
 void Get_String(int,bool); void Free_String();
public:
 StringClass(int n=0,bool temp=false):m_Buffer(m_EmptyString) { Get_String(n,temp); m_Buffer[0]=m_NullChar; }
 ~StringClass(){Free_String();}
};
class VertexMaterialClass {
public:
 virtual void Delete_This(); int refs;
 enum PresetType { PRELIT_DIFFUSE };
 static VertexMaterialClass *Get_Preset(PresetType);
 void Release_Ref(){if (!--refs) Delete_This();}
};
class TextureClass { public: void Release_Ref(); };
class TextureBaseClass;
class TextureHandle { public: TextureClass *p; TextureHandle():p(0){} ~TextureHandle(){if(p)p->Release_Ref();} };
void BoxSetTexture(unsigned int,TextureBaseClass*&);
struct Device;
struct DeviceVtable {char pad[0xe4]; int (__stdcall *SetRenderState)(Device*,unsigned long,unsigned);};
struct Device{DeviceVtable *v;};
extern VertexMaterialClass *ScreenMaterial;
extern unsigned TheBoxTextureDirtyMask;
extern bool ScreenShaderDirty;
extern unsigned ScreenCurrentShader;
extern bool ScreenSnapshot;
extern unsigned ScreenRenderStates[];
extern Device *ScreenDevice;
extern unsigned ScreenStateChanges,number_of_DX8_calls;
class DX8Wrapper {
public:
 static void Apply_Render_State_Changes();
 static void Get_DX8_Render_State_Value_Name(StringClass&,unsigned long,unsigned int);
 static __forceinline void Set_DX8_Render_State(unsigned long state,unsigned value) {
  if(ScreenRenderStates[state]==value)return;
  if(ScreenSnapshot){StringClass s(0,true);Get_DX8_Render_State_Value_Name(s,state,value);}
  ScreenRenderStates[state]=value;
  ScreenDevice->v->SetRenderState(ScreenDevice,state,value);
  ++number_of_DX8_calls; ++ScreenStateChanges;
 }
};
class FadeView{public:
virtual void pad0();
virtual void pad1();
virtual void pad2();
virtual void pad3();
virtual void pad4();
virtual void pad5();
virtual void pad6();
virtual void pad7();
virtual void pad8();
virtual void pad9();
virtual void pad10();
virtual void pad11();
virtual void pad12();
virtual void pad13();
virtual void pad14();
virtual void pad15();
virtual void pad16();
virtual void pad17();
virtual void pad18();
virtual void pad19();
virtual void pad20();
virtual void pad21();
virtual void pad22();
virtual void pad23();
virtual void pad24();
virtual void pad25();
virtual void pad26();
virtual void pad27();
virtual void pad28();
virtual void pad29();
virtual void pad30();
virtual void pad31();
virtual void pad32();
virtual void pad33();
virtual void pad34();
virtual void pad35();
virtual void pad36();
virtual void pad37();
virtual void pad38();
virtual void pad39();
virtual void pad40();
virtual void pad41();
virtual void pad42();
virtual void pad43();
virtual void setMode(int);virtual void pad45();virtual void setFilter(int);};
// Retail 0x012F1600 is the one and only tactical-view singleton, declared
// once in GameClient/View.cpp as `View *TheTacticalView`. This TU only needs
// the fade-mode vtable slice, so cast the canonical global back to it.
class View;
extern View *TheTacticalView;
static inline FadeView *fadeTacticalView() { return (FadeView *)TheTacticalView; }
extern int Rva007D31C0FadeDirection,Rva007D31C0FadeFrames,Rva007D31C0FadeCurrentFrame;extern float Rva007D31C0FadeValue;
enum FilterModes {FM_NULL_MODE};
class Rva007D31C0 { protected: virtual int set(FilterModes); };
int Rva007D31C0::set(FilterModes mode) {
 if(mode>FM_NULL_MODE){
 if(Rva007D31C0FadeDirection>0){
  int fade=++Rva007D31C0FadeCurrentFrame;
  if(fade<Rva007D31C0FadeFrames)Rva007D31C0FadeValue=(float)fade/(float)Rva007D31C0FadeFrames;
  else{Rva007D31C0FadeValue=1;Rva007D31C0FadeCurrentFrame=0;Rva007D31C0FadeDirection=0;}
 }else if(Rva007D31C0FadeDirection<0){
  int fade=++Rva007D31C0FadeCurrentFrame;
  if(fade<Rva007D31C0FadeFrames)Rva007D31C0FadeValue=1-(float)fade/(float)Rva007D31C0FadeFrames;
  else{Rva007D31C0FadeValue=0;fadeTacticalView()->setMode(0);fadeTacticalView()->setFilter(0);Rva007D31C0FadeCurrentFrame=0;Rva007D31C0FadeDirection=0;}
 }

 VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 if(vmat)++vmat->refs;
 if(ScreenMaterial)ScreenMaterial->Release_Ref();
 ScreenMaterial=vmat;
 TheBoxTextureDirtyMask|=0x4000;
 if(vmat)vmat->Release_Ref();
 if(ScreenShaderDirty||ShaderClass::_PresetOpaqueShader.Get_Bits()!=ScreenCurrentShader){ScreenCurrentShader=ShaderClass::_PresetOpaqueShader.Get_Bits();TheBoxTextureDirtyMask|=0x8000;StringClass s;}
 {TextureHandle tex;BoxSetTexture(0,(TextureBaseClass*&)tex.p);}
 DX8Wrapper::Apply_Render_State_Changes();
 DX8Wrapper::Set_DX8_Render_State(23,8);
 DX8Wrapper::Set_DX8_Render_State(14,0);
 DX8Wrapper::Apply_Render_State_Changes();
 return true;
 }
 return false;
}
