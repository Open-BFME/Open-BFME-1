// cl: /DNDEBUG /MD
// 0x003E0DD0: identity from matched iterateCellsAlongLine callback at
// 0x003E2F30 (ILT 0x00010532). BFME member form of ZH examineCellsCallback.
struct ICoord2D { int x,y; };
class Object;
class PathfindCell;
class PathfindCellInfo {
public:
 static void allocateCellInfos();
 unsigned short m_x00; char pad02[2]; unsigned short m_y04; char pad06[6];
 void *m_prevOpen; unsigned short m_totalCost,m_costSoFar;
 char pad14[16]; unsigned m_flags;
};
extern PathfindCellInfo *g_bfmePathfindFreeList;
// Retail global 0x012F1060 is a TU-local counter. Internal linkage permits
// the same non-aliasing load/store schedule as retail.
static unsigned g_rva012F1060;
PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(PathfindCellInfo **,PathfindCell *,const ICoord2D *);
class PathfindCell {
public:
 void setParentCellHierarchical(PathfindCell *);
 PathfindCellInfo *m_info; char pad04[8]; unsigned m_packed;
 bool getOpen() const { return m_info ? ((m_info->m_flags >> 3)&1) : false; }
 bool getClosed() const { return m_info ? ((m_info->m_flags >> 4)&1) : false; }
 int getLayer() const { return (m_packed >> 6)&63; }
};
class Rva003D54E0 {
public:
 Rva003D54E0();
 ICoord2D m_cell; int m_08,m_0c; char m_10,m_11;
 int m_14,m_18,m_1c; char m_20,m_21;
 int m_24,m_28; char m_2c,m_2d,m_2e; int m_30;
};
bool __cdecl rva3d5120(int);
class BfmeGridAL { public: unsigned char bfmeNearAL(int,int) const; };
class BfmeThingBRE;
class Gen_003D6400 { public: void bfmeCopyIndexed(BfmeThingBRE *); };
class Pathfinder {
public:
 bool bfmeStepD4F90(void *,PathfindCell *);
 bool bfmeStepE0930(Object *,ICoord2D *,ICoord2D *);
 int rva003db900(PathfindCell *,PathfindCell *);
 char pad00[0x24]; struct { ICoord2D lo,hi; } m_logicalExtent;
 char pad34[0x83c-0x34]; bool m_isTunneling;
 char pad83d[0xc9c-0x83d]; BfmeGridAL m_zoneManager;
};
struct ExamineCellsStruct {
 Pathfinder *thePathfinder; int m_04,m_08,m_0c;
 bool centerInCell,isHuman; int radius; Object *obj; PathfindCell *goalCell;
 int m_20; ICoord2D m_previous; int m_2c;
 int cellCallback(PathfindCell *,PathfindCell *,int,int);
};
int ExamineCellsStruct::cellCallback(PathfindCell *from,PathfindCell *to,int to_x,int to_y)
{
 if (g_rva012F1060 > 25000) return 1;
 ++g_rva012F1060;
 // Additional BFME range guard, absent from the ZH callback.
 if (m_2c > 0) {
  int dx=to_x-goalCell->m_info->m_x00;
  int dy=to_y-goalCell->m_info->m_y04;
  if ((dx*dx+dy*dy)*100 < m_2c*m_2c) return 1;
 }
 if (thePathfinder->m_isTunneling) return 1;
 if (from) {
  if (to->getOpen() || to->getClosed()) return 1;
  if (!thePathfinder->bfmeStepD4F90(&m_04,to)) return 1;
  if (rva3d5120(to->getLayer())) { Pathfinder *p=thePathfinder; if (!p->m_zoneManager.bfmeNearAL(to_x,to_y)) return 1; }
  if (from->getLayer()!=to->getLayer()) return 1;
  if ((unsigned char)(to->m_packed>>18)&1) return 1;
  if (isHuman) {
   if (to_x<thePathfinder->m_logicalExtent.lo.x) return 1;
   if (to_y<thePathfinder->m_logicalExtent.lo.y) return 1;
   if (to_x>thePathfinder->m_logicalExtent.hi.x) return 1;
   if (to_y>thePathfinder->m_logicalExtent.hi.y) return 1;
  }
  // The matched constructor initializes a 0x34-byte movement-check record.
  // Its cell prefix is passed through the established ICoord2D pointer ABI.
  Rva003D54E0 info;
  info.m_cell.x=to_x; info.m_cell.y=to_y;
  info.m_08=from->getLayer(); info.m_10=centerInCell; info.m_0c=radius;
  info.m_11=false; info.m_14=3; info.m_18=m_20;
  if (!thePathfinder->bfmeStepE0930(obj,&info.m_cell,&m_previous) || info.m_30) return 1;
  ICoord2D newCellCoord; newCellCoord.x=to_x; newCellCoord.y=to_y;
  unsigned newCostSoFar=from->m_info->m_costSoFar+(((unsigned char)(to->m_packed>>24)&1)?2.5f:5.0f);
  if ((to->m_packed&7)==2) return 1;
  if (!to->m_info) {
   if (!g_bfmePathfindFreeList) PathfindCellInfo::allocateCellInfos();
   to->m_info=bfmeAcquirePathfindCellInfo(&g_bfmePathfindFreeList,to,&newCellCoord);
  } else to->m_info->m_prevOpen=0;
  to->m_info->m_flags &= ~1u;
  int costRemaining=thePathfinder->rva003db900(to,goalCell);
  to->m_info->m_costSoFar=(unsigned short)newCostSoFar;
  to->setParentCellHierarchical(from);
  to->m_info->m_totalCost=(unsigned short)(to->m_info->m_costSoFar+costRemaining);
  ((Gen_003D6400 *)thePathfinder)->bfmeCopyIndexed((BfmeThingBRE *)to);
 }
 m_previous.y=to_y; m_previous.x=to_x;
 return 0;
}
