// ?method@Rva002666A0@@QAE?AVCoord3D@@PAVObject@@PAV2@PA_N@Z
// partial score=0.5917 date=2026-10-09
// Experimental coordinate view; see identity_evidence/002666a0-storage-lifetime-retry.md.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /I.
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <windows.h>
#include <math.h>
#define Coord3D Rva002666A0ReferenceCoord3D
#define Coord2D Rva002666A0ReferenceCoord2D
#include "Common/NameKeyGenerator.h"
#include "Common/BitFlags.h"
#undef Coord3D
#undef Coord2D
#include "game/Libraries/Source/WWVegas/WWMath/coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D&o) { x=o.x;y=o.y;z=o.z; }
inline Coord3D& Coord3D::operator=(const Coord3D&o) { struct Rva002666A0Words {int a,b,c;}; *(Rva002666A0Words*)this=*(const Rva002666A0Words*)&o;return *this; }
inline void Coord3D::scale(float s) {x*=s;y*=s;z*=s;}
inline void Coord3D::add(const Coord3DBase*p) {x+=p->x;y+=p->y;z+=p->z;}
inline void Coord3D::sub(const Coord3DBase*p) {x-=p->x;y-=p->y;z-=p->z;}
inline float Coord3D::lengthSqr() const {return x*x+y*y+z*z;}
class Module;
#define BFME_HAVE_COORD3D
#define BFME_HAVE_OBJECTID
#define OBJECT_TU_MEMBERS \
 friend class Rva002666A0; protected: Module *findModule(NameKeyType) const; public: \
 void setStatus(const BitFlags<86>&,bool); \
 void setStatusBit(int,bool);
#include "game/GameEngine/Source/GameLogic/Object/object.h"
class Rva002060B0Triple {
public:
 Rva002060B0Triple(const Rva002060B0Triple&o):a(o.a),b(o.b),c(o.c){}
 int a,b,c;
};
class Rva002060B0Owner { public: Rva002060B0Triple copyAt(int); };
class Rva00206100Point {
public:
 Rva00206100Point(const Rva00206100Point&o):a(o.a),b(o.b),c(o.c){}
 int a,b,c;
};
class Rva00206100Owner { public: Rva00206100Point point(int); };
class Rva002666A0Dock {
public:
 virtual void slot0();
 virtual void slot1();
 virtual int slot2(ObjectID);
};
struct Rva002666A0ModuleView { char opaque00[0x20]; Rva002666A0Dock dock; };
struct Rva002666A0Data { char opaque00[0x1da]; bool at1da; };
struct Object003E3B20;
class VectorAdjust003E3B20 { public: void adjust(Object003E3B20*,Object003E3B20*,Coord3D*); };
extern void j_0003ce25();
class Pathfinder {
public:
 // ?bfmeGroundCellThreshold@Pathfinder@@QAE_NPBVCoord3D@@_N@Z absent-from-retail
 __forceinline bool bfmeGroundCellThreshold(const Coord3D* position,bool requireClearType) {
  union { void (*raw)(); bool (Pathfinder::*typed)(const Coord3D*,bool); } call;
  call.raw=j_0003ce25;
  return (this->*call.typed)(position,requireClearType);
 }
};
struct Rva002666A0AI { char opaque00[12]; Pathfinder *pathfinder; };
class AI;
extern AI *TheAI;
class Rva002666A0 {
public:
 Coord3D method(Object*,Coord3D*,bool*);
 // ?getObject@Rva002666A0@@QBEPAVObject@@XZ absent-from-retail
 Object* getObject() const { return object08; }
 char opaque00[4]; Rva002666A0Data *data04; Object *object08;
};
Coord3D Rva002666A0::method(Object *target,Coord3D *point,bool *found)
{
 Coord3D result = target->m_cachedPos;
 static NameKeyType key=TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
 Module *module=target->findModule(key);
 if(module) {
  // Retail reuses this three-word buffer for the two hidden return values.
  BitFlags<86> storage(BitFlags<86>::kInit,63);
  getObject()->setStatus(storage,false);
  int index=((Rva002666A0ModuleView*)module)->dock.slot2(getObject()->m_id);
  if(index>=0) {
  getObject()->setStatusBit(63,true);
  {
   // Both decoded helpers take result storage before the signed index.
   union {
    Rva002060B0Triple (Rva002060B0Owner::*original)(int);
    Rva002060B0Triple *(Rva002060B0Owner::*output)(Rva002060B0Triple*,int);
   } first;
   first.original=&Rva002060B0Owner::copyAt;
   result=*(const Coord3D*)(((Rva002060B0Owner*)module)->*first.output)((Rva002060B0Triple*)&storage,index);
   union {
    Rva00206100Point (Rva00206100Owner::*original)(int);
    Rva00206100Point *(Rva00206100Owner::*output)(Rva00206100Point*,int);
   } second;
   second.original=&Rva00206100Owner::point;
   *point=*(const Coord3D*)(((Rva00206100Owner*)module)->*second.output)((Rva00206100Point*)&storage,index);
  }
  *found=true;
  } else { *found=false; return result; }
 } else if(!*found) return result;
 Coord3D delta=result;
 delta.sub(&target->m_cachedPos);
 if(delta.lengthSqr()>1.0f) {
  delta.scale(0.1f);
  if(!data04->at1da) {
   ((VectorAdjust003E3B20*)((Rva002666A0AI*)TheAI)->pathfinder)->adjust((Object003E3B20*)getObject(),(Object003E3B20*)target,&delta);
   result=target->m_cachedPos;
   result.add(&delta);
  }
  float factor=1.0f/(float)sqrt(delta.lengthSqr());
  delta.scale(factor);
  delta.scale(5.0f);
  for(int i=0;i<10;++i) {
   if(!((Rva002666A0AI*)TheAI)->pathfinder->bfmeGroundCellThreshold(&result,false)) break;
   result.add(&delta);
  }
 }
 return result;
}
