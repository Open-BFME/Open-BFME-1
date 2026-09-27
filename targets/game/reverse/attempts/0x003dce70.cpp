// ?d_003dce70@@YAXXZ
// partial score=0.939 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 003DCE70: ZH Pathfinder::doDebugIcons structural twin at AIPathfind.cpp:5690.
// BFME adds waypoint mode, layer/connection colors and unit-position offsets.
// Served 1776-byte dump is truncated: terminal RET is RVA 003DD5AF.
// Complete code is 1856 bytes; six DWORD switch targets follow at 003DD5B0.
// BANK: probe symbol ?doDebugIcons@Pathfinder@@QAEXXZ with --size 1880.
// Instruction-shape agreement 0.939; masked positional byte score 0.673036.
// Remaining: normalization x87 schedule / split block and loop-tail allocation.
// GameLogic::findObjectByID below independently probes EXACT over 82 bytes.
// Pending callee pin if this caller becomes exact: PathfindLayer::debug003FBBB0
// needs route 00013C0F -> 003FBBB0 (ret-only retail body, receiver is layer+85C).
// No symbols pin or function ledger change is made by this bank.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <math.h>
struct Coord3D {
 float x,y,z;
 float length() const { return (float)sqrt(x*x+y*y+z*z); }
 void normalize() { float len=length(); if (len!=0) { x/=len; y/=len; z/=len; } }
 void sub(const Coord3D *p) { x-=p->x; y-=p->y; z-=p->z; }
 void add(const Coord3D *p) { x+=p->x; y+=p->y; z+=p->z; }
};
struct Rva006E6E50Triple { float first,second,third; };
void rva006E6E50(const Coord3D *,float,int,Rva006E6E50Triple);
struct ICoord2D { int x,y; };
struct IRegion2D { ICoord2D lo,hi; };
enum PathfindLayerEnum { LAYER_GROUND=1 };
class GlobalData { public: char pad_0000[0xa88]; int m_debugAI; };
extern GlobalData *TheWritableGlobalData;
// Layout independently witnessed by GameLogicFindObjectByID.cpp and object loads in this body.
class Object { public: char pad_0000[0x38]; Coord3D position_0038; };
typedef _STL::hash_map<int,Object *,_STL::hash<int>,_STL::equal_to<int> > ObjectPtrHash;
class GameLogic {
public:
 char pad_0000[0xb0]; ObjectPtrHash m_objHash;
 __declspec(noinline) Object *findObjectByID(int id) {
  if (!id) return 0;
  ObjectPtrHash::iterator it=m_objHash.find(id);
  if (it==m_objHash.end()) return 0;
  return (*it).second;
 }
 __forceinline Object *findObjectByIDInline(int id) {
  if (!id) return 0;
  ObjectPtrHash::iterator it=m_objHash.find(id);
  if (it==m_objHash.end()) return 0;
  return (*it).second;
 }
};
extern GameLogic *TheGameLogic;
struct DebugWaypoint003DCE70 {
 char pad_0000[0xc]; Coord3D position_000c; int field_0018;
 DebugWaypoint003DCE70 *next_001c; char pad_0020[0x24]; int field_0044;
 bool field_0048; char pad_0049[0x17]; int field_0060;
};
class TerrainLogic {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual float getGroundHeight(float,float,Coord3D *);
 virtual void slot7(); virtual void slot8(); virtual void slot9();
 virtual void slot10(); virtual void slot11(); virtual void slot12();
 virtual void slot13(); virtual void slot14(); virtual void slot15();
 virtual void slot16(); virtual void slot17(); virtual void slot18();
 virtual void slot19(); virtual void slot20(); virtual void slot21();
 virtual void slot22(); virtual void slot23(); virtual void slot24();
 virtual void slot25(); virtual void slot26(); virtual void slot27();
 virtual void slot28(); virtual void slot29();
 virtual DebugWaypoint003DCE70 *waypoints003DCE70();
};
extern TerrainLogic *TheTerrainLogic;
class PathfindCellInfo { public: char pad_0000[0x14]; int m_goalUnit; int unit_0018; };
class PathfindCell {
public:
 PathfindCellInfo *m_info; int field_0004,field_0008; unsigned m_packed;
 int type() const { return m_packed&7; }
 int flags() const { return (m_packed>>3)&7; }
 int layer() const { return (m_packed>>6)&63; }
 int connect() const { return (m_packed>>12)&63; }
 bool bit18() const { return ((unsigned char)(m_packed>>18)&1)!=0; }
 bool bit19() const { return ((unsigned char)(m_packed>>19)&1)!=0; }
 bool bit20() const { return ((unsigned char)(m_packed>>20)&1)!=0; }
 bool bit21() const { return ((unsigned char)(m_packed>>21)&1)!=0; }
 int bits22() const { return (m_packed>>22)&3; }
 bool bit24() const { return ((unsigned char)(m_packed>>24)&1)!=0; }
 int goal() const { return m_info ? m_info->m_goalUnit : 0; }
 int unit() const { return m_info ? m_info->unit_0018 : 0; }
};
class PathfindLayer { public: void debug003FBBB0(); char pad_0000[0x44]; };
class Pathfinder {
public:
 void doDebugIcons();
 float getLayerHeight(PathfindLayerEnum,const Coord3D *,Coord3D *);
 char pad_0000[0x10]; PathfindCell **m_map; IRegion2D m_extent;
 char pad_0024[0x85c-0x24]; PathfindLayer m_layers[16];
 PathfindCell *ground(int x,int y) {
  if (x>=m_extent.lo.x && x<=m_extent.hi.x && y>=m_extent.lo.y && y<=m_extent.hi.y)
   return &m_map[x][y];
  return 0;
 }
};
class AI { public: char pad_0000[0xc]; Pathfinder *m_pathfinder; };
extern AI *TheAI;
void Pathfinder::doDebugIcons() {
 if (TheWritableGlobalData->m_debugAI!=3 && TheWritableGlobalData->m_debugAI!=2 &&
     TheWritableGlobalData->m_debugAI!=7 && TheWritableGlobalData->m_debugAI!=5) return;
 Rva006E6E50Triple color;
 color.first=color.second=color.third=0;
 rva006E6E50(0,0,0,color);
 if (TheWritableGlobalData->m_debugAI==7) {
  for (DebugWaypoint003DCE70 *w=TheTerrainLogic->waypoints003DCE70();w;w=w->next_001c) {
   color.first=color.second=color.third=0;
   if (w->field_0048 && (w->field_0060==1 || w->field_0060==2 || w->field_0060==3 || w->field_0060==4)) color.second=1;
   else if (w->field_0044) color.third=1;
   else color.first=1;
   rva006E6E50(&w->position_000c,5,15,color);
  }
  return;
 }
 Coord3D topLeftCorner;
 bool showCells=TheWritableGlobalData->m_debugAI==3 || TheWritableGlobalData->m_debugAI==5;
 for (int layer=0;layer<16;layer++) m_layers[layer].debug003FBBB0();
 for (int i=0;i<m_extent.hi.x;i++) {
  for (int j=0;j<m_extent.hi.y;j++) {
   topLeftCorner.x=(float)i*10.0f;
   topLeftCorner.y=(float)j*10.0f;
   color.first=color.second=color.third=0;
   bool empty=true;
   const PathfindCell *cell=TheAI->m_pathfinder->ground(i,j);
   if (cell) {
    switch(cell->type()) {
    case 1: color.third=1; empty=false; break;
    case 6: color.third=color.first=1; empty=false; break;
    case 5: color.second=1; empty=false; break;
    case 3: color.first=1; color.second=0.5f; empty=false; break;
    case 4: color.first=color.second=1; empty=false; break;
    case 2: color.first=1; empty=false; break;
    default:
     if (cell->bit18()) { color.third=color.second=0.7f; empty=false; }
     if (cell->layer()==16) { color.third=0.5f; empty=false; }
     else if (cell->layer()!=1 || cell->connect()==16) { color.first=color.third=0.7f; empty=false; }
     break;
    }
   }
   if (empty && cell->bit21()) { color.first=0.3f; empty=false; }
   Coord3D loc;
   loc.x=topLeftCorner.x+5.0f; loc.y=topLeftCorner.y+5.0f; loc.z=0;
   if (cell->layer()!=1) loc.z=getLayerHeight((PathfindLayerEnum)cell->layer(),&loc,0);
   else loc.z=TheTerrainLogic->getGroundHeight(loc.x,loc.y,0);
   if (showCells) {
    empty=true; color.first=color.second=color.third=0;
    if (cell->flags()!=0) {
     empty=false;
     Object *obj=0;
     if (cell->flags()==1) { color.first=1; obj=TheGameLogic->findObjectByIDInline(cell->goal()); }
     else if (cell->flags()==3) { color.second=color.third=color.first=1; obj=TheGameLogic->findObjectByID(cell->goal()); }
     else if (cell->flags()==2) { color.second=1; obj=TheGameLogic->findObjectByID(cell->unit()); }
     else { color.second=color.first=1; }
     if (obj) {
      Coord3D delta; delta.x=obj->position_0038.x; delta.y=obj->position_0038.y; delta.z=obj->position_0038.z;
      delta.x=(float)floor((delta.x+5.0f)*0.1f)*10.0f;
      delta.y=(float)floor((delta.y+5.0f)*0.1f)*10.0f;
      delta.sub(&loc);
      delta.normalize();
      delta.x*=1.5f; delta.y*=1.5f;
      loc.add(&delta);
      loc.z=obj->position_0038.z;
     }
    }
    if (cell->bit19()) { empty=false; color.first=0; color.second=color.third=1; }
    if (empty && cell->bit20()) { empty=false; color.first=color.second=color.third=0; }
   }
   if (!empty) {
    rva006E6E50(&loc,8,14,color);
    if (cell->connect()) { color.first=1; color.second=1; color.third=1; rva006E6E50(&loc,3,14,color); }
   }
   if (cell->bit20()) { color.first=0; color.second=0; color.third=0; rva006E6E50(&loc,3,14,color); }
   int count=cell->bits22();
   if (count>0) { color.first=count*0.5f; color.second=0; color.third=0; rva006E6E50(&loc,1.5f,14,color); }
   if (cell->bit24()) { color.first=0; color.second=0.5f; color.third=0; rva006E6E50(&loc,10,14,color); }
  }
 }
}
