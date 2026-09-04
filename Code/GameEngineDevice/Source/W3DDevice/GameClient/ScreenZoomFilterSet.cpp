// cl: /DNDEBUG /MD
// ScreenZoomFilter vtable 0x011289D4 slot 5 -> 0x0040C7E3 -> 0x007D1F00.
// Slot 0 identifies matched ScreenZoomFilter::init at 0x007D2390.
class TextureBaseClass;
class VertexMaterialClass{public:virtual void Delete_This();int refs;enum PresetType{PRELIT_DIFFUSE};static VertexMaterialClass*Get_Preset(PresetType);void Release_Ref(){if(!--refs)Delete_This();}};
extern VertexMaterialClass *ScreenMaterial;extern unsigned TheBoxTextureDirtyMask;
class ShaderClass{unsigned x;};extern ShaderClass ScreenOpaqueShader;
void BaseHeightMapScorchSetShader(const ShaderClass&);
void BoxSetTexture(unsigned,TextureBaseClass*&);
class DX8Wrapper{public:static void Apply_Render_State_Changes();static void Set_DX8_Render_State(unsigned long,unsigned);};
struct ZoomSettings{
 char pad0[0x218];int mode;char pad1[0xdbd-0x21c];bool highlight;
 void apply82AA0(int);
};
extern ZoomSettings *ZoomGlobalSettings;
struct ZoomClient{char pad[0x3c];int frame;};extern ZoomClient *ZoomGameClient;
class ZoomEnvironment{public:
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
virtual void apply(int);};extern ZoomEnvironment *ZoomTerrain;
class ZoomView{public:
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
virtual void setMode(int);virtual void pad45();virtual void setFilter(int);};extern ZoomView *ZoomTacticalView;
extern int ZoomLastFrame,ZoomPulse,ZoomFadeDirection,ZoomFadeFrames,ZoomCurrentFrame;
extern bool ZoomPulseDown;extern float ZoomFadeValue;
enum FilterModes{FM_NULL_MODE};
class ScreenZoomFilter{public:virtual int set(FilterModes);unsigned shader;TextureBaseClass *texture;int savedMode;};
int ScreenZoomFilter::set(FilterModes mode){
 ZoomGlobalSettings->highlight=false;
 bool changed=false;
 if(ZoomLastFrame!=ZoomGameClient->frame){changed=true;ZoomLastFrame=ZoomGameClient->frame;}
 if(ZoomPulse&&changed){
  if(ZoomFadeDirection<0&&!ZoomPulseDown){
   ZoomPulseDown=true;ZoomPulse=30;
   ZoomGlobalSettings->apply82AA0(savedMode);
   ZoomTerrain->apply(savedMode);
  }
  if(ZoomPulseDown){
   ZoomPulse-=3;
   if(ZoomPulse<1){ZoomPulseDown=false;ZoomPulse=0;ZoomTacticalView->setMode(0);ZoomTacticalView->setFilter(0);}
  }else{
   ZoomPulse+=3;
   if(ZoomPulse>=30){ZoomPulseDown=true;ZoomTacticalView->setMode(15);ZoomTacticalView->setFilter(7);savedMode=ZoomGlobalSettings->mode;ZoomGlobalSettings->apply82AA0(4);ZoomTerrain->apply(4);}
  }
 }
 if(mode>FM_NULL_MODE){
  if(ZoomFadeDirection>0){
   if(changed)++ZoomCurrentFrame;
   int fade=ZoomCurrentFrame;
   if(fade<ZoomFadeFrames)ZoomFadeValue=(float)fade/(float)ZoomFadeFrames;
   else{ZoomFadeValue=1;ZoomCurrentFrame=0;ZoomFadeDirection=0;}
  }else if(ZoomFadeDirection<0){
   if(changed)++ZoomCurrentFrame;
   int fade=ZoomCurrentFrame;
   if(fade<ZoomFadeFrames)ZoomFadeValue=1-(float)fade/(float)ZoomFadeFrames;
   else{ZoomFadeValue=0;ZoomTacticalView->setMode(0);ZoomTacticalView->setFilter(0);ZoomCurrentFrame=0;ZoomFadeDirection=0;}
  }
  VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
  if(vmat)++vmat->refs;if(ScreenMaterial)ScreenMaterial->Release_Ref();ScreenMaterial=vmat;TheBoxTextureDirtyMask|=0x4000;if(vmat)vmat->Release_Ref();
  BaseHeightMapScorchSetShader(ScreenOpaqueShader);BoxSetTexture(0,texture);DX8Wrapper::Apply_Render_State_Changes();DX8Wrapper::Set_DX8_Render_State(23,8);DX8Wrapper::Set_DX8_Render_State(14,0);DX8Wrapper::Apply_Render_State_Changes();return true;
 }
 return false;
}

