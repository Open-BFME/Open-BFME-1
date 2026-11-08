// cl: /O2 /Ob1 /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
//
// Rva0075CC80Owner::rva0075CC80, retail RVA 0x0075CC80, 340 bytes (plain ret
// at +0x153). Address-derived name: no caller or string names the body (see
// targets/game/reverse/identity_evidence/0075cc80-masm-codegen-blocker.md).
// A __thiscall render-kind update: early-outs on +0xDC/+0xF8, needs the
// drawable (+0x08) and render object (+0x34); the pending arm re-evaluates
// 0x0075B4A0 and applies a pending drawable update, the main arm classifies
// the camera-to-drawable distance against data+0x100/+0x104 and, for render
// kind 3, sets the LOD level through slot +0x138.
// This replaces the MASM dump: the last two register bytes (retail's EDX
// vtable temporary for the slot +0x138 call) come from the documented typed
// vtable-slot lever with a register-only __fastcall table argument; the
// level stays the stack argument.
#include "coord3d.h"

extern "C" void *memcpy(void *,const void *,unsigned int);
#pragma intrinsic(memcpy)
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
class Drawable;
int rva0075B4A0(const Drawable *, bool *);
class Rva0075CC80Owner;
// Retail's Drawable::applyPendingModelConditionFlags (row 0x0041AA90, ILT 0x0002D439) is private.
class Drawable { void applyPendingModelConditionFlags(bool value); friend class Rva0075CC80Owner; };
class BFMERopeDrawableGetPositionShim { public: const Coord3D *get() const; };
// The rope getter's row (?getPosition@BFMERopeDrawable@@QBEPBUCoord3D@@XZ, reached by retail through
// ILT 0x0004B12D) names its struct-keyed Coord3D; this unit's Coord3D is class-keyed, so the call
// names that symbol exactly.
extern "C" void __identifier("?getPosition@BFMERopeDrawable@@QBEPBUCoord3D@@XZ")(void);
struct Rva0075CC80Vector { float x,y,z; };
class View;
extern View *TheTacticalView;
class Rva0075CC80View {
public:
 virtual void rvaSlot000();
 virtual void rvaSlot004();
 virtual void rvaSlot008();
 virtual void rvaSlot00C();
 virtual void rvaSlot010();
 virtual void rvaSlot014();
 virtual void rvaSlot018();
 virtual void rvaSlot01C();
 virtual void rvaSlot020();
 virtual void rvaSlot024();
 virtual void rvaSlot028();
 virtual void rvaSlot02C();
 virtual void rvaSlot030();
 virtual void rvaSlot034();
 virtual void rvaSlot038();
 virtual void rvaSlot03C();
 virtual void rvaSlot040();
 virtual void rvaSlot044();
 virtual void rvaSlot048();
 virtual void rvaSlot04C();
 virtual void rvaSlot050();
 virtual void rvaSlot054();
 virtual void rvaSlot058();
 virtual void rvaSlot05C();
 virtual void rvaSlot060();
 virtual void rvaSlot064();
 virtual void rvaSlot068();
 virtual void rvaSlot06C();
 virtual void rvaSlot070();
 virtual void rvaSlot074();
 virtual void rvaSlot078();
 virtual void rvaSlot07C();
 virtual void rvaSlot080();
 virtual void rvaSlot084();
 virtual void rvaSlot088();
 virtual void rvaSlot08C();
 virtual void rvaSlot090();
 virtual void rvaSlot094();
 virtual void rvaSlot098();
 virtual void rvaSlot09C();
 virtual void rvaSlot0A0();
 virtual void rvaSlot0A4();
 virtual void rvaSlot0A8();
 virtual void rvaSlot0AC();
 virtual void rvaSlot0B0();
 virtual void rvaSlot0B4();
 virtual void rvaSlot0B8();
 virtual void rvaSlot0BC();
 virtual void rvaSlot0C0();
 virtual void rvaSlot0C4();
 virtual void rvaSlot0C8();
 virtual void rvaSlot0CC();
 virtual void rvaSlot0D0();
 virtual void rvaSlot0D4();
 virtual void rvaSlot0D8();
 virtual void rvaSlot0DC();
 virtual void rvaSlot0E0();
 virtual void rvaSlot0E4();
 virtual void rvaSlot0E8();
 virtual void rvaSlot0EC();
 virtual void rvaSlot0F0();
 virtual void rvaSlot0F4();
 virtual void rvaSlot0F8();
 virtual void rvaSlot0FC();
 virtual void rvaSlot100();
 virtual void rvaSlot104();
 virtual void rvaSlot108();
 virtual void rvaSlot10C();
 virtual void rvaSlot110();
 virtual void rvaSlot114();
 virtual const Rva0075CC80Vector *rvaSlot118();
};
#include "vector3.h"
#include "rendobj.h"
struct Rva0075CC80Data {
 char m_pad000[0x100];
 float m_100,m_104;
 bool m_108,m_109;
};
// Typed view of RenderObjClass vtable slot +0x138 (Set_LOD_Level): a
// register-only __fastcall table argument keeps retail's EDX table temporary
// (docs/shape_levers.md, Vtable register-temp call shape).
struct Rva0075CC80RenderVtbl {
 char m_pad000[0x138];
 void (__fastcall *setLodLevel)(RenderObjClass *self, const Rva0075CC80RenderVtbl *table, int level);
};
class Rva0075CC80Owner {
public:
 void rva0075CC80();
 void *m_000;
 const Rva0075CC80Data *m_004;
 Drawable *m_008;
 char m_pad00C[0x28];
 RenderObjClass *m_034;
 char m_pad038[0x68];
 int m_0A0,m_0A4;
 char m_pad0A8[0x34];
 void *m_0DC;
 char m_pad0E0[0x18];
 void *m_0F8;
};
void Rva0075CC80Owner::rva0075CC80()
{
 if(m_0DC && m_0F8) return;
 Drawable *drawable=m_008;
 if(!drawable || !m_034) return;
 const Rva0075CC80Data *data=m_004;
 int renderKind=m_034->Get_LOD_Count();
 if(data->m_109) {
  Drawable *kindDrawable=m_008;
  int kind=rva0075B4A0(kindDrawable,0);
  if(kind!=m_0A4) {
   m_0A4=kind;
   ((Drawable*)drawable)->applyPendingModelConditionFlags(true);
  }
  return;
 }
 if(renderKind==3 || data->m_108) {
  const Rva0075CC80Vector *camera=((Rva0075CC80View*)TheTacticalView)->rvaSlot118();
  unsigned cameraZ,cameraX,cameraY;
  memcpy(&cameraX,&camera->x,4);
  memcpy(&cameraY,&camera->y,4);
  memcpy(&cameraZ,&camera->z,4);
  Coord3D offset;
  memcpy(&offset.x,&cameraX,4);
  memcpy(&offset.y,&cameraY,4);
  memcpy(&offset.z,&cameraZ,4);
  union { void (*raw)(); const Coord3D *(BFMERopeDrawableGetPositionShim::*member)() const; } ropePosition;
  ropePosition.raw=__identifier("?getPosition@BFMERopeDrawable@@QBEPBUCoord3D@@XZ");
  const Coord3D *position=(((BFMERopeDrawableGetPositionShim*)drawable)->*ropePosition.member)();
  offset.x-=position->x;
  offset.y-=position->y;
  offset.z-=position->z;
  float distance=offset.lengthEstimate();
  int kind;
  if(distance<data->m_100) kind=0;
  else if(distance>data->m_104) kind=2;
  else kind=1;
  if(renderKind==3) {
   RenderObjClass *robj=m_034;
   const Rva0075CC80RenderVtbl *table=*(const Rva0075CC80RenderVtbl *const *)robj;
   table->setLodLevel(robj,table,kind);
   m_0A0=kind;
   m_0A4=kind;
  } else if(kind!=m_0A0) {
   m_0A4=kind;
   ((Drawable*)drawable)->applyPendingModelConditionFlags(false);
  }
 }
}
