// ?Render@HeightMapRenderObjClass@@UAEXAAVRenderInfoClass@@@Z
// partial score=0.445360824742268 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Identity: ctor RVA006D1C80 installs primary vtable VA0111DC88; slot12
// through ILT RVA00042D57 routes here. Full ret4 at006D41C0 ends3395B.
// Same-TU helper RVA006D2480 is249B through ret1C at006D2576 (gen row says246).
// Additional measured getter/setter definitions are retained in render_40.cpp.
// This bank is the best complete render probe, render_37. Callee signatures
// beyond existing proved names deliberately retain address-derived identities.
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "rendobj.h"
#include "rinfo.h"
#include "matpass.h"
#include "shader.h"
#include "dx8wrapper.h"

extern Matrix4 Rva00F4108C;
extern VertexMaterialClass *Rva00F40EC4;
extern unsigned Rva00F3F49C,Rva00F40EC0,Rva00ED6E1C;
extern bool Rva00ED6DFC;
__forceinline void invalidate(){Rva00ED6DFC=true;}
__forceinline void material(VertexMaterialClass *m){
 if(m)m->Add_Ref();if(Rva00F40EC4)Rva00F40EC4->Release_Ref();Rva00F40EC4=m;Rva00F3F49C|=0x4000;
}
__forceinline void shader(const unsigned &s){if(!Rva00ED6DFC && s==Rva00F40EC0)return;Rva00F40EC0=s;Rva00F3F49C|=0x8000;StringClass description;}
__forceinline void world(const Matrix3D &m){Rva00F4108C=Matrix4(m).Transpose();Rva00F3F49C|=1;Rva00F3F49C&=~0x40000;}

// BFME uses an out-of-line texture release, unlike ZH's inline RefCountClass.
class BFMETextureRelease {public: void Release_Ref();};
class BfmeHandleCX {
public:
 BFMETextureRelease *p;
 BfmeHandleCX(int zero=0):p(0){}
 BfmeHandleCX(const BfmeHandleCX &t):p(t.p){if(p)++*(unsigned short*)((char*)p+4);}
 ~BfmeHandleCX(){if(p)p->Release_Ref();}
 BfmeHandleCX &operator=(const BfmeHandleCX &t){if(t.p)++*(unsigned short*)((char*)t.p+4);if(p)p->Release_Ref();p=t.p;return *this;}
 operator TextureBaseClass*&()const{return *(TextureBaseClass**)&p;}
};
void BoxSetTexture(unsigned,TextureBaseClass*&);
void bfme5SetTextureSlot(int,TextureClass**);
__forceinline void bind(unsigned n,const BfmeHandleCX &t){BoxSetTexture(n,t);}
__forceinline void setslot(int n,const BfmeHandleCX &t){bfme5SetTextureSlot(n,(TextureClass**)&t.p);}
class Gen_006D2630 { public:BfmeHandleCX bfmeGet()const; };
class Gen_006D2660 { public:BfmeHandleCX bfmeGet()const; };
class Gen_00923710 { public:int m(); };
class W3DShaderManager {public:enum ShaderTypes {Unused};static int setShader(ShaderTypes,int);static void resetShader(ShaderTypes);};
int Rva00716970Lookup(int);
int Rva00903060Get();
class Rva006C9270 {public:void apply();};
void Rva006FA0A0Invoke(int);
class W3DTerrainBackground {
public:int field0;char pad4[0x50];float field54;char pad58[0x6c];
 void rva0072DC30(RenderInfoClass&,bool,bool);
};
class Rva006D2480 {
public:char pad0[0x30d8];W3DTerrainBackground *tiles;int count,width,height;char pad30e8[0x10];bool enabled;char pad30f9[3];int target;float threshold;
 void apply(RenderInfoClass&,bool,bool,int&,int&,int&,int&);
};
class Rva006F9380 {public:void apply(CameraClass*,bool,const BfmeHandleCX&,const BfmeHandleCX&);};
struct Rva006D3480Iterator {void *list,*node;};
class Rva00710620 {public:void apply(CameraClass*,const BfmeHandleCX&,const BfmeHandleCX&,bool,int,int,int,int,Rva006D3480Iterator*);};
class Rva006DA2D0 {public:void apply(CameraClass*,bool,const BfmeHandleCX&);};
class Rva00702920 {public:void apply(RenderInfoClass&);};
class TerrainTracksRenderObjClassSystem {public:void flush();};
class W3DWaypointBuffer {public:void drawWaypoints(RenderInfoClass&);};
class W3DBibBuffer {public:void renderBibs();};
struct Rva006D3480Map {char pad0[8];int field8,fieldc,field10;};
struct Rva006D3480Tree {char pad[0x2a7cb8];bool field_2a7cb8;};
struct Rva006D3480Prop {char pad[0x1e1cd0];bool field_1e1cd0;};
struct Rva006D3480Scene {char pad[0x110];void *field110,*field114,*field118;};
struct Rva006D3480Global {char p0[0x38];bool field38;char p39;bool field3a;char p3b[9];bool field44;char p45[0x1d3];int field218;char p21c[0xad9];bool fieldcf5;};
struct Rva006D3480State {char pad[0xc];int fieldc;};
struct Rva006D3480Client {char pad[0x16c4];int field16c4;};
struct Rva006D3480Feature {virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual bool enabled();};
extern Rva006D3480Global *Rva00EED5C8;
extern bool Rva00EF800C,Rva00F3F42C,Rva00EF08A0;
extern Rva006D3480Feature *Rva00EF1104;
extern Rva006D3480State *Rva00EF0FE0;
extern Rva006D3480Client *Rva00EED5AC;
extern BfmeHandleCX Rva00EF9D28[8];
extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;
class BaseHeightMapRenderObjClass:public RenderObjClass {
public:
 protected:
 void renderShoreLines(CameraClass*);
 void drawScorches();
public:
 void rva006C90B0();
 char gap[0x2ff4-sizeof(RenderObjClass)];Rva006D3480Map *field_2ff4;
 char gap2ff8[0x10];bool field_3008;char gap3009[0x3f];
 ShaderClass field_3048;VertexMaterialClass *field_304c;
 BfmeHandleCX field_3050,field_3054,field_3058,field_305c,field_3060,field_3064,field_3068;
 char gap306c[0x28];Rva006D3480Tree *field_3094;Rva006D3480Prop *field_3098;Rva00702920 *field_309c;
 W3DBibBuffer *field_30a0;Rva006F9380 *field_30a4;W3DWaypointBuffer *field_30a8;Rva00710620 *field_30ac;Rva006DA2D0 *field_30b0;W3DBibBuffer *field_30b4;
 Gen_006D2630 *field_30b8;Gen_006D2660 *field_30bc;void *field_30c0;char gap30c4[0xc];bool field_30d0;
};
class HeightMapRenderObjClass:public BaseHeightMapRenderObjClass {public:virtual void Render(RenderInfoClass&);};

void Rva006D2480::apply(RenderInfoClass&r,bool a,bool b,int &xmin,int &xmax,int &ymin,int &ymax){
 for(int i=0;i<width;i++)for(int j=0;j<height;j++){
  W3DTerrainBackground *tile=tiles+j*width+i;
  if(tile->field0==2)continue;
  if(enabled && target<count && threshold<tile->field54)continue;
  tile->rva0072DC30(r,a,b);
  if(i*16<xmin)xmin=i*16;
  if(j*16<ymin)ymin=j*16;
  if(i*16+16>xmax)xmax=i*16+16;
  if(j*16+16>ymax)ymax=j*16+16;
 }
}

void HeightMapRenderObjClass::Render(RenderInfoClass &rinfo){
 if(field_30d0)return;
 if(Rva00EF800C)return;
 if(Is_Hidden())return;
 if(Rva00F3F42C)return;
 bool cloud=Rva00EED5C8->field38;
 Matrix3D tm(Transform);
 if(field_3094)field_3094->field_2a7cb8=true;
 if(field_3098)field_3098->field_1e1cd0=true;
 if(Rva00EF08A0){
  bind(0,0);bind(1,0);((Rva006C9270*)this)->apply();invalidate();material(0);
  if(field_309c)field_309c->apply(rinfo);
  bind(0,0);bind(1,0);((Rva006C9270*)this)->apply();invalidate();material(0);
  return;
 }
 if((rinfo.Current_Override_Flags()&4) && Rva00EF1104 && Rva00EF1104->enabled()){
  if(Rva00EF0FE0 && Rva00EF0FE0->fieldc==2 && Rva00EED5AC && Rva00EED5AC->field16c4<2)return;
  if(((Gen_00923710*)&rinfo)->m()!=1)return;
  int yMin=field_2ff4->field8,xMin=field_2ff4->fieldc,yMax=0,xMax=0;
  rinfo.Peek_Additional_Pass(0)->Install_Materials();
  ((Rva006D2480*)this)->apply(rinfo,true,false,xMin,xMax,yMin,yMax);
  rinfo.Peek_Additional_Pass(0)->UnInstall_Materials();
  return;
 }
 DX8Wrapper::Set_Light_Environment(rinfo.light_environment);
 ((Rva006C9270*)this)->apply();bind(0,0);bind(1,0);invalidate();
 world(tm);
 material(field_304c);shader(*(unsigned*)&field_3048);
 if(Rva00EED5C8->field218==4)cloud=false;
 int st=12;
 if(Rva00EED5C8->field44 && cloud)st=15;
 else if(Rva00EED5C8->field44)st=14;
 else if(cloud)st=13;
 int passes=Rva00716970Lookup(st);
 if(!Rva00EED5C8->fieldcf5 || (!field_30b8 && st==12))passes=1;
 setslot(0,field_3050);
 if(field_30b8 && !field_3008)setslot(0,field_30b8->bfmeGet());
 setslot(1,0);setslot(2,field_3058);setslot(3,field_305c);setslot(4,field_3060);
 if(field_30bc && !field_3008)setslot(4,field_30bc->bfmeGet());
 setslot(5,field_3064);setslot(6,field_3068);
 if(Rva00903060Get()==21)DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,7);
 int yMax=0,yMin=field_2ff4->field8,xMax=0,xMin=field_2ff4->fieldc;
 int pass;
 for(pass=0;pass<passes;pass++){
  bool disable=field_3008;
  if(field_3008){shader(Rva00ED6E1C);bind(0,0);}
  else W3DShaderManager::setShader((W3DShaderManager::ShaderTypes)st,pass);
  if(pass>0)disable=true;
  ((Rva006D2480*)this)->apply(rinfo,disable,field_3008,xMin,xMax,yMin,yMax);
 }
 if(pass)W3DShaderManager::resetShader((W3DShaderManager::ShaderTypes)st);
 for(int slot=0;slot<8;slot++){Rva00EF9D28[slot]=0;}
 renderShoreLines(&rinfo.Camera);
 field_30a4->apply(&rinfo.Camera,field_3008,field_305c,field_3058);
 if(Rva00EED5C8->field3a){
  bind(0,0);bind(1,0);((Rva006C9270*)this)->apply();invalidate();
  if(!ShaderClass::Is_Backface_Culling_Inverted()){
   material(field_304c);
   if(Scene){
    Rva006D3480Scene *scene=(Rva006D3480Scene*)Scene;
    Rva006D3480Iterator lights={&scene->field110,scene->field118};
    if(field_30ac)field_30ac->apply(&rinfo.Camera,cloud?field_3058:0,Rva00EED5C8->field44?field_305c:0,field_3008,
     xMin-field_2ff4->field10,xMax-field_2ff4->field10,yMin-field_2ff4->field10,yMax-field_2ff4->field10,&lights);
   }
  }
 }
 bind(0,0);bind(1,0);((Rva006C9270*)this)->apply();invalidate();
 if(!ShaderClass::Is_Backface_Culling_Inverted()){drawScorches();rva006C90B0();Rva006FA0A0Invoke((int)&rinfo);}
 bind(0,0);bind(1,0);((Rva006C9270*)this)->apply();invalidate();DX8Wrapper::Apply_Render_State_Changes();
 field_30b0->apply(&rinfo.Camera,field_3008,field_3058);
 if(TheTerrainTracksRenderObjClassSystem)TheTerrainTracksRenderObjClassSystem->flush();
 invalidate();DX8Wrapper::Apply_Render_State_Changes();
 if(field_30a8){field_30a8->drawWaypoints(rinfo);world(tm);DX8Wrapper::Apply_Render_State_Changes();}
 field_30a0->renderBibs();
 if(field_309c)field_309c->apply(rinfo);
 bind(0,0);bind(1,0);((Rva006C9270*)this)->apply();invalidate();material(0);
}
