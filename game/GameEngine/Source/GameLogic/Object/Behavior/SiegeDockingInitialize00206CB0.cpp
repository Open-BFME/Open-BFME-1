// RVA 0x00206CB0: SIEGETOWER / SIEGELADDER bone initialization.
// Owner layout agrees with SiegeDockingBehavior ctor 0x002062C0 and xfer
// 0x00206FF0: Object+8, pointer-vector+0x24, enabled flag+0x30.
// The original method spelling is unproved; the address is retained.
// Coordinate array callbacks are retail Coord3D ctor/dtor at 0x83330/0x5BC40.
// MatrixRows is the witnessed 3x16-byte row ABI with non-inlined row ctor,
// shared with SpawnPointProductionExitUpdateInitializeBonePositions.cpp.
// The second coordinate array is constructed and destroyed even though unused.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
struct Coord3D;
#include "coord3d.h"
class Matrix3D;
class SpawnBoneRow { public: SpawnBoneRow(); float x,y,z,w; };
struct MatrixRows00206CB0 { SpawnBoneRow row[3]; };
struct Position00206CB0 { float x,y,z; void setNegated(float a,float b,float c) { x=-a;y=-b;z=-c; } };
struct SiegeDockEntry00206FF0 { int index00,type04; Position00206CB0 position08,direction14; int objectID20; };
class Object { public: int getMultiLogicalBonePosition(const char*,int,Coord3D*,Matrix3D*,bool,int) const; };
class SiegeDockingBehavior { public:
 Object* getObject() { return object08; }
 void initializeBones00206CB0();
 char prefix00[8]; Object* object08; char prefix0C[0x18];
 _STL::vector<SiegeDockEntry00206FF0*> entries24;
 bool initialized30;
};
void SiegeDockingBehavior::initializeBones00206CB0() {
 int index=0;
 Coord3D positions[10];
 MatrixRows00206CB0 transforms[10];
 Coord3D directions[10];
 int count=object08->getMultiLogicalBonePosition("SIEGETOWER",10,positions,(Matrix3D*)transforms,true,0);
 for(;index<count;++index) {
  SiegeDockEntry00206FF0* entry=new SiegeDockEntry00206FF0;
  entry->index00=index;
  entry->type04=0;
  entry->position08=*(Position00206CB0*)&positions[index];
  MatrixRows00206CB0* transform=&transforms[index];
  entry->direction14.setNegated(transform->row[0].x,transform->row[1].x,transform->row[2].x);
  entry->objectID20=0;
  entries24.push_back(entry);
 }
 count=getObject()->getMultiLogicalBonePosition("SIEGELADDER",10,positions,(Matrix3D*)transforms,true,0);
 for(int i=0;i<count;++i) {
  SiegeDockEntry00206FF0* entry=new SiegeDockEntry00206FF0;
  entry->index00=index;
  entry->type04=1;
  entry->position08=*(Position00206CB0*)&positions[i];
  MatrixRows00206CB0* transform=&transforms[i];
  entry->direction14.setNegated(transform->row[0].x,transform->row[1].x,transform->row[2].x);
  entry->objectID20=0;
  entries24.push_back(entry);
  ++index;
 }
 initialized30=true;
}




