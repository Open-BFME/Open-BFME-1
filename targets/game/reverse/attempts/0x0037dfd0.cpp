// ?rva0037dfd0@@YGXPAURva0037DFD0Container@@PAVObject@@@Z
// partial score=0.3458 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
#include "ascii_string.h"
#include "coord3d.h"
#include "matrix3d.h"
class Object;
class FXList {public:bool bfmeIsBlocked();void doFXPos(const Coord3DBase*,const Matrix3D*,float,const Coord3DBase*)const;void doFXObj(const Object*,const Object*)const;};
#pragma comment(linker,"/alternatename:?doFXPos@FXList@@QBEXPBUCoord3DBase@@PBVMatrix3D@@M0@Z=?j_0001bb21@@YAXXZ")
class ObjectCreationList {public:void createInternal(const Object*,const Object*,unsigned)const;};
class Rva0037DFD0Drawable {public:bool bone(const char*,Matrix3D&);};
#pragma comment(linker,"/alternatename:?bone@Rva0037DFD0Drawable@@QAE_NPBDAAVMatrix3D@@@Z=?j_0003ec11@@YAXXZ")
class Rva0037DFD0Object {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual Rva0037DFD0Drawable *drawable();
};
struct FXEntry {FXList *fx;AsciiString name;};
struct Rva0037DFD0Container {char pad[0x34];FXEntry *begin,*end;int gap;ObjectCreationList *ocl;};
void __stdcall rva0037dfd0(Rva0037DFD0Container *container,Object *primary){
 for(unsigned i=0;i<(unsigned)(container->end-container->begin);++i){
  FXEntry *entry=container->begin+i;
  Rva0037DFD0Object *view=(Rva0037DFD0Object*)primary;
  if(!entry->name.isEmpty() && view->drawable()){
   Matrix3D transform(true);
   view->drawable()->bone(entry->name.str(),transform);
   Coord3DBase pos;
   pos.x=transform[0][3];pos.y=transform[1][3];pos.z=transform[2][3];
   FXList *fx=entry->fx;
   if(fx && !fx->bfmeIsBlocked())fx->doFXPos(&pos,&transform,0.0f,0);
  }else{
   FXList *fx=entry->fx;
   if(fx && !fx->bfmeIsBlocked())fx->doFXObj(primary,0);
  }
 }
 if(container->ocl)container->ocl->createInternal(primary,0,0);
}
