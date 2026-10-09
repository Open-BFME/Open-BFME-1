// ?method@Rva002632F0@@QAEXPBUCoord3D@@I@Z
// partial score=0.6336 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /I. /Igame/Libraries/Source/WWVegas/WWLib

// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <new>
#include "ascii_string.h"
#pragma auto_inline(off)
#include <vector>
#pragma auto_inline(on)
#include "game/Libraries/Include/Lib/Coord3D.h"
typedef Coord3D Coord3DBase;
class ObjectCreationList;
class OCLSpecialPower { public: const ObjectCreationList *findOCL() const; };
class SpecialPowerModuleInterface { public: void doSpecialPowerAtLocation(const Coord3D*,unsigned); };
class Rva003DAD60 { public: bool adjust003DAD60(Coord3D*); };
struct Rva002632F0AI { char pad[12]; Rva003DAD60 *pathfinder; };
extern Rva002632F0AI *Rva012EF214;
struct Rva002632F0Waypoint { char pad[12]; Coord3DBase position; };
class Rva002632F0Terrain {
public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0c();
 virtual void s10();virtual void s14();virtual void s18();virtual void s1c();
 virtual void s20();virtual void s24();virtual void s28();virtual void s2c();virtual void s30();
 virtual Coord3DBase s34(const Coord3DBase*);
 virtual Coord3DBase s38(const Coord3DBase*);
 virtual void s3c();virtual void s40();virtual void s44();virtual void s48();
 virtual void s4c();virtual void s50();virtual void s54();virtual void s58();
 virtual void s5c();virtual void s60();virtual void s64();virtual void s68();
 virtual void s6c();virtual void s70();virtual void s74();virtual void s78();
 virtual Rva002632F0Waypoint *s7c(AsciiString);
};
extern Rva002632F0Terrain *Rva012EF4CC;
struct BfmeZ1095B { unsigned vptr; int field04; };
class BfmeR1095 { public: void bfmeAdd1095(BfmeZ1095B*,int); };
class Rva002632F0Object { public: char pad[0x1a4]; int field1a4; };
class Rva002632F0UpgradeCenter { public: BfmeZ1095B *rva0010B0E0(const AsciiString&); };
extern Rva002632F0UpgradeCenter *Rva012EF188;
extern void j_00020824();
static __forceinline BfmeR1095 *rva001BE3F0(Rva002632F0Object *o) {
 typedef BfmeR1095*(Rva002632F0Object::*M)(); union {void(*f)(); M m;} u;
 u.f=&j_00020824;return (o->*u.m)();
}
class BfmeSubBUC;
void bfmeGoBUC(BfmeSubBUC*,void*,void*,void*,void*);
extern void j_000443e1();
void j_000443e1(const ObjectCreationList*,Rva002632F0Object*,const Coord3DBase*,const Coord3DBase*,int,int);
class Rva002632F0 {
public: void method(const Coord3DBase *loc,unsigned options);
 Rva002632F0Object *object() const {return *(Rva002632F0Object**)((char*)this-8);}
};
extern void j_00043464();
extern void j_0000e4e4();
extern void j_000170da();
extern void j_0002F95A();
// ?GetLengthEstimate2D@@YAMPBUCoord3D@@@Z absent-from-retail
static __forceinline float GetLengthEstimate2D(const Coord3D *that) {
 typedef float (Coord3D::*Length)() const;
 union {void(*f)();Length m;} length;
 length.f=&j_00043464;
 return (that->*length.m)();
}
void Rva002632F0::method(const Coord3DBase *loc,unsigned options) {
 if(object()->field1a4 || !loc)return;
 typedef void (SpecialPowerModuleInterface::*DoSpecialPowerAtLocation)(const Coord3D*,unsigned);
 union {void(*f)();DoSpecialPowerAtLocation m;} base;
 base.f=&j_000170da;
 (((SpecialPowerModuleInterface*)this)->*base.m)(loc,options);
 const ObjectCreationList *ocl=((OCLSpecialPower*)((char*)this-16))->findOCL();
 char *data=*(char**)((char*)this-12);
 Coord3DBase creation;
 typedef bool (Rva003DAD60::*Adjust003DAD60)(Coord3D*);
 union {void(*f)();Adjust003DAD60 m;} adjust;adjust.f=&j_0000e4e4;
 switch(*(unsigned*)(data+0x220)) {
 case 0:
  creation=Rva012EF4CC->s34((const Coord3DBase*)((char*)object()+0x38));
  (Rva012EF214->pathfinder->*adjust.m)((Coord3D*)&creation);
  bfmeGoBUC((BfmeSubBUC*)ocl,object(),&creation,(void*)loc,0);break;
 case 1:
  creation=Rva012EF4CC->s34(loc);
  (Rva012EF214->pathfinder->*adjust.m)((Coord3D*)&creation);
  bfmeGoBUC((BfmeSubBUC*)ocl,object(),&creation,0,0);break;
 case 2:
  creation=Rva012EF4CC->s34(loc);
  (Rva012EF214->pathfinder->*adjust.m)((Coord3D*)&creation);
  bfmeGoBUC((BfmeSubBUC*)ocl,object(),&creation,(void*)loc,0);break;
 case 6:
  creation=Rva012EF4CC->s38(loc);creation.z+=300.0f;
  (Rva012EF214->pathfinder->*adjust.m)((Coord3D*)&creation);
  bfmeGoBUC((BfmeSubBUC*)ocl,object(),&creation,(void*)loc,0);break;
 case 3:
  creation=*loc;bfmeGoBUC((BfmeSubBUC*)ocl,object(),&creation,0,0);break;
 case 4:
  creation.x=loc->x;creation.y=loc->y;creation.z=loc->z;
  ((void (__cdecl *)(const ObjectCreationList*,Rva002632F0Object*,const Coord3DBase*,const Coord3DBase*,int,int))
   (void(*)())&j_000443e1)(ocl,object(),&creation,loc,0,0);break;
 case 5:
  creation=*loc;creation.z+=300.0f;bfmeGoBUC((BfmeSubBUC*)ocl,object(),&creation,0,0);break;
 case 7: {
  Rva002632F0Waypoint *points[4];
  points[0]=Rva012EF4CC->s7c(AsciiString("TopArmySpawnPoint"));
  points[1]=Rva012EF4CC->s7c(AsciiString("BottomArmySpawnPoint"));
  points[2]=Rva012EF4CC->s7c(AsciiString("LeftArmySpawnPoint"));
  points[3]=Rva012EF4CC->s7c(AsciiString("RightArmySpawnPoint"));
  int best=-1;float distance=99999.0f;
  for(int i=0;i<4;++i) if(points[i]) {
   Coord3DBase delta=points[i]->position;
   delta.x-=loc->x;delta.y-=loc->y;delta.z-=loc->z;
   float d=GetLengthEstimate2D(&delta);
   if(d<distance) {distance=d;best=i;}
  }
  if(best>=0) {creation=points[best]->position;creation.z+=300.0f;
   bfmeGoBUC((BfmeSubBUC*)ocl,object(),&creation,(void*)loc,0);}
  break;
 }
 }
 std::vector<AsciiString> upgrades(*(const std::vector<AsciiString>*)(data+0x224));
 for(unsigned i=0;i<upgrades.size();++i) {
  typedef BfmeZ1095B *(Rva002632F0UpgradeCenter::*Lookup0010B0E0)(const AsciiString&);
  union {void(*f)();Lookup0010B0E0 m;} lookup;
  lookup.f=&j_0002F95A;
  BfmeZ1095B *upgrade=(Rva012EF188->*lookup.m)(upgrades[i]);
  if(!upgrade)break;
  if(upgrade->field04==0)rva001BE3F0(object())->bfmeAdd1095(upgrade,2);
 }
}
