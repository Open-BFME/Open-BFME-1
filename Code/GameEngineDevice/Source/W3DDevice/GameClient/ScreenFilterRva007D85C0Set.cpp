// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D81C0, filter vtable 0x01128BAC slot 5.
// The matched Rva007D85C0 constructor installs this vtable; original class name unknown.
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
 enum PresetType {PRELIT_DIFFUSE};
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
extern unsigned ScreenOpaqueShader, ScreenCurrentShader;
extern bool ScreenSnapshot;
extern unsigned ScreenRenderStates[];
extern Device *ScreenDevice;
extern unsigned ScreenStateChanges,ScreenTotalChanges;
class DX8Wrapper {
public:
 static void Apply_Render_State_Changes();
 static void Get_DX8_Render_State_Value_Name(StringClass&,unsigned long,unsigned int);
 static __forceinline void Set_DX8_Render_State(unsigned long state,unsigned value) {
  if(ScreenRenderStates[state]==value)return;
  if(ScreenSnapshot){StringClass s(0,true);Get_DX8_Render_State_Value_Name(s,state,value);}
  ScreenRenderStates[state]=value;
  ScreenDevice->v->SetRenderState(ScreenDevice,state,value);
  ++ScreenTotalChanges; ++ScreenStateChanges;
 }
};
enum FilterModes {FM_NULL_MODE};
class Rva007D85C0 { protected: virtual int set(FilterModes); };
int Rva007D85C0::set(FilterModes mode) {
 if(mode>FM_NULL_MODE){
 VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 if(vmat)++vmat->refs;
 if(ScreenMaterial)ScreenMaterial->Release_Ref();
 ScreenMaterial=vmat;
 TheBoxTextureDirtyMask|=0x4000;
 if(vmat)vmat->Release_Ref();
 if(ScreenShaderDirty||ScreenOpaqueShader!=ScreenCurrentShader){ScreenCurrentShader=ScreenOpaqueShader;TheBoxTextureDirtyMask|=0x8000;StringClass s;}
 {TextureHandle tex;BoxSetTexture(0,(TextureBaseClass*&)tex.p);}
 {TextureHandle tex;BoxSetTexture(1,(TextureBaseClass*&)tex.p);}
 DX8Wrapper::Apply_Render_State_Changes();
 DX8Wrapper::Set_DX8_Render_State(23,8);
 DX8Wrapper::Set_DX8_Render_State(14,0);
 DX8Wrapper::Apply_Render_State_Changes();
 }
 return true;
}



