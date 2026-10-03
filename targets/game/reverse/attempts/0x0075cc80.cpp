// ?rva0075CC80@Rva0075CC80Owner@@QAEXXZ
// partial score=0.9941 date=2026-10-02
// cl: /O2 /Ob1 /DNDEBUG /MD
#include "../../../../game/Libraries/Source/WWVegas/WWMath/coord3d.h"

extern "C" void *memcpy(void *,const void *,unsigned int);
#pragma intrinsic(memcpy)
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
class Drawable;
int rva0075B4A0(const Drawable *, bool *);
class DrawableApplyPendingThunk { public: void apply(bool value); };
class BFMERopeDrawable { public: const Coord3D *getPosition() const; };
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
class Rva0075CC80Render {
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
 virtual void rvaSlot118();
 virtual void rvaSlot11C();
 virtual void rvaSlot120();
 virtual void rvaSlot124();
 virtual void rvaSlot128();
 virtual void rvaSlot12C();
 virtual void rvaSlot130();
 virtual void rvaSlot134();
 virtual void rvaSlot138(int value);
 virtual void rvaSlot13C();
 virtual int rvaSlot140();
};
struct Rva0075CC80Data {
 char m_pad000[0x100];
 float m_100,m_104;
 bool m_108,m_109;
};
class Rva0075CC80Owner {
public:
 void rva0075CC80();
 void *m_000;
 const Rva0075CC80Data *m_004;
 Drawable *m_008;
 char m_pad00C[0x28];
 Rva0075CC80Render *m_034;
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
 int renderKind=m_034->rvaSlot140();
 if(data->m_109) {
  Drawable *kindDrawable=m_008;
  int kind=rva0075B4A0(kindDrawable,0);
  if(kind!=m_0A4) {
   m_0A4=kind;
   ((DrawableApplyPendingThunk*)drawable)->apply(true);
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
  const Coord3D *position=((BFMERopeDrawable*)drawable)->getPosition();
  offset.x-=position->x;
  offset.y-=position->y;
  offset.z-=position->z;
  float distance=offset.lengthEstimate();
  int kind;
  if(distance<data->m_100) kind=0;
  else if(distance>data->m_104) kind=2;
  else kind=1;
  if(renderKind==3) {
   m_034->rvaSlot138(kind);
   m_0A0=kind;
   m_0A4=kind;
  } else if(kind!=m_0A0) {
   m_0A4=kind;
   ((DrawableApplyPendingThunk*)drawable)->apply(false);
  }
 }
}
