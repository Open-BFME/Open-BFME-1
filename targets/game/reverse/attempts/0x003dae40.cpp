// ?expandLinkedCells003DAE40@Pathfinder@@QAEXPAVPathfindCell@@PAVObject@@@Z
// partial score=0.971 date=2026-09-27
// stlport
#include <vector>
// cl: /DNDEBUG /MD
// Retail 0x003DAE40: linked-cell expansion; method identity remains address-derived.
// The allocator definition below independently matches 104 bytes at 0x003D7DB0.
// Its visibility recovers the original coordinate-load/store scheduling.
struct ICoord2D { int x,y; };
struct Coord3D { float x,y,z; };
class Object;
enum PathfindLayerEnum { Layer003DAE40Zero=0 };
class PathfindCell;
class PathfindCellInfo {
public:
 static void allocateCellInfos();
 ICoord2D m_pos;
 PathfindCellInfo *m_nextOpen,*m_prevOpen;
 unsigned short m_totalCost,m_costSoFar;
 unsigned int m_pathParent,m_goalUnitID,m_posUnitID,m_goalAircraftID;
 unsigned int m_flags0:3; unsigned int m_open:1; unsigned int m_closed:1; unsigned int m_rest:27;
 PathfindCell *m_cell; PathfindCellInfo *m_freeNext; PathfindCellInfo **m_freePrevLink;
};
extern PathfindCellInfo *g_bfmePathfindFreeList;
PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(PathfindCellInfo **,PathfindCell *,const ICoord2D *);
class Waypoint {
public:
 bool method001ABBB0(Object *);
 char m_pad00[4]; int m_at04;
 char m_pad08[0x18]; Waypoint *m_at20[8];
 char m_pad40[0xc]; int m_at4c;
};
class PathfindCell {
public:
 void setParentCellHierarchical(PathfindCell *);
 PathfindCellInfo *m_info;
 Waypoint *m_at04;
 unsigned int m_at08,m_packed;
 unsigned short getXIndex() const { return m_info->m_pos.x; }
 unsigned short getYIndex() const { return m_info->m_pos.y; }
 int getConnectLayer() const { return (m_packed>>12)&63; }
 bool getOpen() const { return m_info->m_open; }
 bool getClosed() const { return m_info->m_closed; }
 __forceinline bool allocateInfo(const ICoord2D &p) {
  if(!m_info) {
   if(!g_bfmePathfindFreeList) PathfindCellInfo::allocateCellInfos();
   m_info=bfmeAcquirePathfindCellInfo(&g_bfmePathfindFreeList,this,&p);
  } else m_info->m_prevOpen=0;
  return true;
 }
};
class BfmeThingBRE;
class Gen_003D6400 { public: void bfmeCopyIndexed(BfmeThingBRE *); };
class Rva003F69C0Object { public: void set(int *,int); };
struct LinkedRecord003DAE40 { int at00,at04,at08; };
class Pathfinder {
public:
 PathfindCell *getCell(PathfindLayerEnum,int,int);
 bool worldToCell(const Coord3D *,ICoord2D *);
 void expandLinkedCells003DAE40(PathfindCell *,Object *);
 char m_pad00[0x10]; PathfindCell **m_map;
 struct { ICoord2D lo,hi; } m_extent;
 char m_pad24[0x2470c-0x24];
 std::vector<LinkedRecord003DAE40> m_at2470c;
 __forceinline PathfindCell *groundCell(int x,int y) {
  if(x>=m_extent.lo.x && x<=m_extent.hi.x && y>=m_extent.lo.y && y<=m_extent.hi.y)
   return &m_map[x][y];
  return 0;
 }
};
void Pathfinder::expandLinkedCells003DAE40(PathfindCell *parent,Object *object) {
 if(parent->getConnectLayer()) {
  ICoord2D pos;
  pos.x=parent->getXIndex();
  pos.y=parent->getYIndex();
  PathfindCell *cell;
  if(parent->getConnectLayer()==1) cell=groundCell(pos.x,pos.y);
  else if(parent->getConnectLayer()>=16) cell=groundCell(pos.x,pos.y);
  else cell=getCell((PathfindLayerEnum)parent->getConnectLayer(),pos.x,pos.y);
  if(cell && (!cell->m_info || (!cell->getOpen() && !cell->getClosed()))) {
   if(!cell->allocateInfo(pos)) return;
   cell->setParentCellHierarchical(parent);
   cell->m_info->m_costSoFar=parent->m_info->m_costSoFar;
   cell->m_info->m_totalCost=parent->m_info->m_totalCost;
   ((Gen_003D6400 *)this)->bfmeCopyIndexed((BfmeThingBRE *)cell);
  }
 }
 Waypoint *waypoint=parent->m_at04;
 if(waypoint && object && waypoint->method001ABBB0(object)) {
  if(!m_at2470c.empty() && m_at2470c.back().at00==waypoint->m_at04) m_at2470c.pop_back();
  for(int i=0;i<waypoint->m_at4c;i++) {
   Waypoint *link=(i>=0 && i<8)?waypoint->m_at20[i]:0;
   if(!link) continue;
   const Coord3D *world=(Coord3D *)((char *)link+0xc);
   ICoord2D index;
   PathfindCell *cell=0;
   if(!worldToCell(world,&index)) cell=groundCell(index.x,index.y);
   if(!cell) continue;
   bool onList=false;
   if(cell->m_info) onList=cell->getOpen() || cell->getClosed();
   if(onList) continue;
   ICoord2D pos;
   worldToCell(world,&pos);
   if(!cell->allocateInfo(pos)) return;
   ((Rva003F69C0Object *)cell)->set((int *)parent,(int)waypoint);
   cell->m_info->m_costSoFar=parent->m_info->m_costSoFar;
   cell->m_info->m_totalCost=parent->m_info->m_totalCost;
   ((Gen_003D6400 *)this)->bfmeCopyIndexed((BfmeThingBRE *)cell);
  }
 }
}


extern int g_bfmePathfindInfoIssued;
__declspec(noinline) PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(PathfindCellInfo **freeListHead, PathfindCell *cell,const ICoord2D *position) {
 PathfindCellInfo *record=*freeListHead;
 if(record->m_freePrevLink) {
  *record->m_freePrevLink=record->m_freeNext;
  if(record->m_freeNext) record->m_freeNext->m_freePrevLink=record->m_freePrevLink;
  record->m_freePrevLink=0; record->m_freeNext=0;
 }
 record->m_cell=cell;
 record->m_pos=*position;
 record->m_nextOpen=0; record->m_prevOpen=0;
 record->m_totalCost=0; record->m_costSoFar=0;
 record->m_pathParent=0; record->m_goalUnitID=0; record->m_posUnitID=0; record->m_goalAircraftID=0;
 record->m_flags0=0; record->m_open=0; record->m_closed=0;
 ++g_bfmePathfindInfoIssued;
 return record;
}
