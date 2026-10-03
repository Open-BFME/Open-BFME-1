// ?method@Rva00235150@@QAEXPBVCoord3D@@0HH@Z
// partial score=0.3645 date=2026-10-03
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Retail 00235150..0023527B, secondary interface; opaque name preserves address.
#include "coord3d.h"
#include <list>
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &p):Coord3DBase(p) {}
inline Coord3D &Coord3D::operator=(const Coord3D &p) {
 struct Words { unsigned x,y,z; }; *(Words*)this=*(const Words*)&p; return *this;
}
class Object;
class AI;
extern AI *TheAI;
class Rva00235150Call {};
template<class T> __forceinline T rva00235150Call(void (*raw)()) {
 union { void (*raw)(); T member; } u; u.raw=raw; return u.member;
}
extern void j_000392ca(); extern void j_0004895a();
typedef void (Rva00235150Call::*Adjust)(Object*,Coord3D*,Object*,bool);
typedef void (Rva00235150Call::*Build)(const Coord3D*,const Coord3D*,int,int,const Coord3D*,const Coord3D*);
typedef char RequireFourByteAdjust[sizeof(Adjust)==4?1:-1];
typedef char RequireFourByteBuild[sizeof(Build)==4?1:-1];
struct Rva00235150Object { char prefix[0x38]; Coord3D position; char pad[0x204-0x44]; Rva00235150Call *ai; };
struct Rva00235150AI { char prefix[0xc]; Rva00235150Call *pathfinder; };
struct Rva00235150Prefix {
 char prefix[4]; Object *owner; char pad[0x2c]; std::list<Object*> members;
};
class Rva00235150 {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18();
 virtual Coord3D slot1c(Object*,int*);
 void method(const Coord3D*,const Coord3D*,int,int);
};
void Rva00235150::method(const Coord3D *a,const Coord3D *b,int cost,int layer) {
 Rva00235150Prefix *prefix=(Rva00235150Prefix*)((char*)this-0xe0);
 Object *owner=prefix->owner;
 int requestedLayer=layer;
 for(std::list<Object*>::iterator it=prefix->members.begin();it!=prefix->members.end();++it) {
  Object *member=*it;
  if(member) {
   Rva00235150Call *ai=((Rva00235150Object*)member)->ai;
   layer=0;
   Coord3D destination; destination=slot1c(member,&layer);
   Coord3D origin=((Rva00235150Object*)owner)->position;
   if(requestedLayer!=1) {
    origin.x+=b->x;origin.y+=b->y;origin.z+=b->z;
    origin.x*=0.5f;origin.y*=0.5f;origin.z*=0.5f;
   }
   (((Rva00235150AI*)TheAI)->pathfinder->*rva00235150Call<Adjust>(j_000392ca))(member,&destination,owner,false);
   (ai->*rva00235150Call<Build>(j_0004895a))(a,b,cost,requestedLayer,&origin,&destination);
  }
 }
}
