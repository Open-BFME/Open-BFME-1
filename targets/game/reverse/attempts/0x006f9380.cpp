// ?d_006f9380@@YAXXZ
// partial score=0.706521739 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// 006F9380 list cleanup, shroud transitions and multi-pass floor rendering.
// Owner and element member offsets are direct instruction witnesses here.
// The W3DFloorBuffer vtable names another render body, so keep this address.
// Partial: same 920-byte extent and 0.983 normalized instruction shape.
// Material release still lacks seven bytes of retail counter-address/copy work;
// loop alignment compensates the size. Scratch and saved-register residues remain.
// BufferRebuild006F8F00 is an UNPINNED address-derived callee declaration:
// ILT RVA 000472BC targets 006F8F00, thiscall, zero stack args, result unused.
// Confirm identity/ABI and pin consistency before any future landing.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#define _OPERATOR_NEW_DEFINED_ 1
#include "texture.h"
#include "rendobj.h"
#include "vertmaterial.h"
#include "shader.h"
class VertexBufferClass;
class IndexBufferClass;
// ABI-only facade: all calls here are out of line in retail.
class DX8Wrapper { public:
 static void Set_Index_Buffer(const IndexBufferClass *,unsigned short);
 static void Set_Vertex_Buffer(const VertexBufferClass *,unsigned);
 static void Set_Shader(const ShaderClass &);
 static void Apply_Render_State_Changes();
 static void Draw_Triangles(unsigned short,unsigned short,unsigned short,unsigned short);
 private: static unsigned render_state_changed;
 friend class FloorBuffer006F9380;
};
class W3DShaderManager { public:
 enum ShaderTypes { ST_ROAD_BASE=7,ST_ROAD_BASE_NOISE1=8,ST_ROAD_BASE_NOISE2=9,ST_ROAD_BASE_NOISE12=10 };
 static int setShader(ShaderTypes,int);
 static int setShroudTex(int);
 static void resetShader(ShaderTypes);
};
int Rva00716970Lookup(int);
void BoxSetTexture(unsigned,TextureBaseClass *&);
class BaseHeightMapFloorElement { public: virtual ~BaseHeightMapFloorElement(); };
class Rva006F6F40FloorElement { public: bool update(); };
class Rva006F7150 { public: int check(int); };
class BufferRebuild006F8F00 { public: void rebuild(); };
struct FloorElement006F9380 {
 char padding00[0x20];
 TextureBaseClass *texture;
 RenderObjClass *mesh;
 void *field28;
 char padding2c[0xc];
 int field38,field3c,field40,field44;
 void *field48;
 char padding4c[0x30];
 bool field7c; char padding7d[0xf];
 int field8c,field90;
 bool field94;
 void clear() {
  field7c=false;
  if (mesh) {mesh->Release_Ref();mesh=0;}
  if (texture) {texture->Release_Ref();texture=0;}
  field28=0;field48=0;
 }
 bool visible() const { return field7c && field90!=0 && (!field94 || *(volatile const int *)&field90==2); }
 void draw(bool skipTexture) {
  if (field7c) {
   if(!skipTexture) BoxSetTexture(0,texture);
   DX8Wrapper::Draw_Triangles((unsigned short)field38,(unsigned short)field44,(unsigned short)field40,(unsigned short)field3c);
  }
 }
};
static __forceinline void assignTexture006F9380(TextureBaseClass *&slot,TextureBaseClass *&value) {
 if(value) ++*(unsigned short *)((char *)value+4);
 TextureBaseClass *old=slot;
 if(old) old->Release_Ref();
 slot=value;
}
class FloorBuffer006F9380 { public:
 void draw(void *,bool,TextureBaseClass *&,TextureBaseClass *&);
 void *field00;
 VertexBufferClass *field04;
 IndexBufferClass *field08;
 VertexMaterialClass *field0c;
 void *field10;
 int field14,field18;
 TextureBaseClass *field1c;
 _STL::list<FloorElement006F9380 *> elements;
 int field24;
 bool field28,field29,field2a;
};
void FloorBuffer006F9380::draw(void *unused,bool skipTexture,TextureBaseClass *&lightmap,TextureBaseClass *&cloudmap)
{
 int player;
 if (*(char **)0x012ED748) player=*(int *)(*(char **)(*(char **)0x012ED748+0xc)+0x24);
 else player=0;
 _STL::list<FloorElement006F9380 *>::iterator it=elements.begin();
 for (;it!=elements.end();++it) {
  while(it!=elements.end()) {
   FloorElement006F9380 *e=*it;
   if(!e->field94 || e->field90==2) break;
   _STL::list<FloorElement006F9380 *>::iterator next=it; ++next;
   e->clear();
   FloorElement006F9380 *dead=*it;
   if(dead) {
    ((BaseHeightMapFloorElement *)dead)->BaseHeightMapFloorElement::~BaseHeightMapFloorElement();
    operator delete(dead);
   }
   elements.erase(it);
   field24=elements.size();
   it=next;
  }
  if(it==elements.end()) break;
  if(((Rva006F6F40FloorElement *)*it)->update()) field2a=true;
  if(*(void **)0x012ED748 && *(void **)0x012ED5BC) {
   int old=(*it)->field8c;
   int current=((Rva006F7150 *)*it)->check(player);
   if(current!=old) {
    (*it)->field8c=current;
    FloorElement006F9380 *e=*it;
    if(e->field90==0) {
     if(current==1) {e->field90=1;field2a=true;}
    } else if(e->field90==1) {
     if(current==0) {e->field90=2;field2a=true;}
    } else if(e->field90==2) {
     if(current==1) {e->field90=1;field2a=true;}
    }
   }
  } else {
   (*it)->field8c=1;
   (*it)->field90=1;
   field2a=true;
  }
 }
 if(field2a) {((BufferRebuild006F8F00 *)this)->rebuild();field2a=false;}
 field29=false;
 if(field18) {
  VertexMaterialClass *material=field0c;
  if(material) material->Add_Ref();
  VertexMaterialClass *old=*(VertexMaterialClass **)0x01340EC4;
  if(old) {
   volatile int &refs=*(int *)((char *)old+4);
   int count=refs-1;
   refs=count;
   if(count==0) old->Delete_This();
  }
  *(VertexMaterialClass **)0x01340EC4=material;
  DX8Wrapper::render_state_changed|=0x4000;
  DX8Wrapper::Set_Index_Buffer(field08,0);
  DX8Wrapper::Set_Vertex_Buffer(field04,0);
  DX8Wrapper::Set_Shader(*(ShaderClass *)0x012BAB3C);
  DX8Wrapper::Apply_Render_State_Changes();
  W3DShaderManager::ShaderTypes shader=W3DShaderManager::ST_ROAD_BASE;
  char *globalData=*(char **)0x012ED5C8;
  if(cloudmap && *(globalData+0x38)) {
   shader=W3DShaderManager::ST_ROAD_BASE_NOISE1;
   if(lightmap && *(globalData+0x44)) shader=W3DShaderManager::ST_ROAD_BASE_NOISE12;
  } else if(lightmap && *(globalData+0x44)) shader=W3DShaderManager::ST_ROAD_BASE_NOISE2;
  int passes=Rva00716970Lookup(shader);
  if(!W3DShaderManager::setShroudTex(1)) assignTexture006F9380(*(TextureBaseClass **)0x012F9D2C,field1c);
  assignTexture006F9380(*(TextureBaseClass **)0x012F9D30,cloudmap);
  assignTexture006F9380(*(TextureBaseClass **)0x012F9D34,lightmap);
  for(int pass=0;pass<passes;++pass) {
   W3DShaderManager::setShader(shader,pass);
   for(_STL::list<FloorElement006F9380 *>::iterator drawIt=elements.begin();drawIt!=elements.end();++drawIt) {
    if((*drawIt)->visible()) (*drawIt)->draw(skipTexture);
   }
  }
  W3DShaderManager::resetShader(shader);
 }
}

