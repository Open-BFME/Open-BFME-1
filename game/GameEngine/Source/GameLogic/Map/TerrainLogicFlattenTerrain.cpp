// cl: /O2 /EHsc /MD /Igame/GameEngine/Include/Precompiled
#include "PreRTS.h"
// TerrainLogic::flattenTerrain, retail 0x001AE610. Matched Dozer and Worker
// construct callers reach ILT 0x00049D2D; ZH flattenTerrain is the source twin.
extern "C" __declspec(dllimport) double __cdecl floor(double);
struct Coord3D {float x,y,z;};
#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct ICoord2D {int x,y;};
class Object;
extern void j_00042ccb();
extern void j_0003ed60();
extern void j_000309f4();
extern void j_0002efc3();
// Constructor 0x001A1460 copies GeometryInfo, angle and position; next at
// 0x001A12D0 walks its footprint and returns AL. Reset 0x001A0DC0 restores
// the cursor at +0xAC/+0xB0. The inherited geometry cleanup is 0x000FFCA0.
// The member-pointer views preserve the proven thiscall ABI of existing ILTs.
class FootprintIterator001A1460 {
 char bytes[0xB4];
public:
 FootprintIterator001A1460(const void *geometry,float angle,const Coord3D *position) {
  typedef void (FootprintIterator001A1460::*Call)(const void*,float,const Coord3D*);
  union {void (*raw)();Call member;} call;
  call.raw=j_00042ccb;
  (this->*call.member)(geometry,angle,position);
 }
 ~FootprintIterator001A1460() {typedef void (__fastcall *Call)(void*);((Call)j_000309f4)(this);}
 bool next(Coord2D *position) {
  typedef bool (FootprintIterator001A1460::*Call)(Coord2D*);
  union {void (*raw)();Call member;} call;
  call.raw=j_0003ed60;
  return (this->*call.member)(position);
 }
 void reset() {typedef void (__fastcall *Call)(void*);((Call)j_0002efc3)(this);}
};
class TerrainLogic {
public:
 virtual void s0();virtual void s1();virtual void s2();
 virtual void s3();virtual void s4();virtual void s5();
 virtual float getGroundHeight(float,float,void *normal=0);
 void flattenTerrain(Object *object);
};
extern TerrainLogic *TheTerrainLogic;
class TerrainVisual001AE610 {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void setRawMapHeight(const ICoord2D*,int);
};
extern TerrainVisual001AE610 *TheTerrainVisual;
// Native fast_float2long_round from ZH Lib/BaseType.h. Retail uses this
// rounding-mode-sensitive x87 conversion for the two floor results.

void TerrainLogic::flattenTerrain(Object *object) {
 const char *obj=(const char*)object;
 if(*(const bool*)(obj+0xB0))return;
 Coord3D position;
 position.x=*(const float*)(obj+0x38);
 position.y=*(const float*)(obj+0x3C);
 position.z=*(const float*)(obj+0x40);
 float angle=*(const float*)(obj+0x44);
 FootprintIterator001A1460 iterator(obj+0xAC,angle,&position);
 float totalHeight=0;
 int count=0;
 Coord2D point;
 while(iterator.next(&point)) {
  totalHeight+=getGroundHeight(point.x,point.y);
  ++count;
 }
 if(count==0)return;
 float average=totalHeight/count;
 int height=fast_float2long_round((float)floor(average*25.6f+0.5f));
 int center=fast_float2long_round((float)floor(TheTerrainLogic->getGroundHeight(position.x,position.y)*25.6f));
 if(height>center)height=center;
 iterator.reset();
 while(iterator.next(&point)) {
  ICoord2D grid;
  grid.x=(int)point.x;grid.y=(int)point.y;
  TheTerrainVisual->setRawMapHeight(&grid,height);
  grid.x=(int)(point.x-1.0f);grid.y=(int)point.y;
  TheTerrainVisual->setRawMapHeight(&grid,height);
  grid.x=(int)(point.x+1.0f);grid.y=(int)point.y;
  TheTerrainVisual->setRawMapHeight(&grid,height);
  grid.x=(int)point.x;grid.y=(int)(point.y-1.0f);
  TheTerrainVisual->setRawMapHeight(&grid,height);
  grid.x=(int)point.x;grid.y=(int)(point.y+1.0f);
  TheTerrainVisual->setRawMapHeight(&grid,height);
  grid.x=(int)(point.x-1.0f);grid.y=(int)(point.y-1.0f);
  TheTerrainVisual->setRawMapHeight(&grid,height);
  grid.x=(int)(point.x+1.0f);grid.y=(int)(point.y+1.0f);
  TheTerrainVisual->setRawMapHeight(&grid,height);
  grid.x=(int)(point.x+1.0f);grid.y=(int)(point.y-1.0f);
  TheTerrainVisual->setRawMapHeight(&grid,height);
  grid.x=(int)(point.x-1.0f);grid.y=(int)(point.y+1.0f);
  TheTerrainVisual->setRawMapHeight(&grid,height);
 }
}
