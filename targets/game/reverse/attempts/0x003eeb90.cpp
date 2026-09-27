// ?d_003eeb90@@YAXXZ
// partial score=0.14394720561 date=2026-09-26
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// BFME Pathfinder::internal_findHierarchicalPath. Not byte-matched.
// Correct contiguous extent [003EEB90,003EFE81)=4849B: RET1C at+12EE,
// followed by INT3. The old4836B ledger/Ghidra count truncates CALL+12E1.
// Identity: native findGroundPath/findPath/findClosestPath and the 7-argument
// forwarding wrapper003F0EC0 call ILT0001FA14. ZH AIPathfind.h proves protected.
// Fresh read-only Ghidra plus raw retail recover the omitted BFME waypoint
// branch, Object* argument, movement profile and512-bucket queue. The scanned
// cells and bridge/waypoint links use native neighbor layouts, not ZH layout.
// B independently decoded003ED070: thiscall Object*,int,int,const void*,
// returnsAL, RET10; optional pointer reads+10. Old bank's int movementLayer
// declaration was wrong.003D9970: thiscall9args RET24, coordinate refs, two
// cell pointers, ushort zone, ushort array, int&, movement-profile ref,int&.
// The typed existing-ILT adapters below are real calls, not linker-only aliases.
// Native buildHierachicalPath275B supplies its protected member spelling.
// Visible bfmeAcquirePathfindCellInfo reproduces104/104B; already-owned helper
// provides NO new coverage. Strict resolver inventory has zero unresolved.
// Measurements: native4887B vs4849,4151 masked positional differences;
// score698/4849=.1439472056;126 relocs. Frame104 vsEC. Normalized instruction
// shape .914 is NOT a byte score. A linker-alias-only variant was4881/.917,
// but requires six declaration repairs; this bank retains resolved adapters.
// Fresh levers: full BFME flow, bool getters vs fused TEST18, native queue
// loop, genuine acquire visibility, coordinate scopes/reuse. Eight finite
// loop/frame shape trials did not improve. No asm or volatile was added.
#include "basetype.h"
#pragma warning(disable : 4189 4101)
typedef unsigned short zoneStorageType;
enum PathfindLayerEnum
{
    LAYER_INVALID = 0,
    LAYER_GROUND = 1,
    LAYER_LAST = 15
};
extern void j_00003ff3();
extern void j_00018471();
extern void j_0003a828();
extern void j_0002f798();
extern void j_00042d3e();
class Object;
class Path;
class PathfindCell;
class PathfindCellInfo
{
  public:
    static void allocateCellInfos(void);

    ICoord2D m_pos;                    // +0x00
    PathfindCellInfo *m_nextOpen;      // +0x08
    PathfindCellInfo *m_prevOpen;      // +0x0c
    unsigned short m_totalCost;        // +0x10
    unsigned short m_costSoFar;        // +0x12
    unsigned int m_pathParent;         // +0x14
    unsigned int m_goalUnitID;         // +0x18
    unsigned int m_posUnitID;          // +0x1c
    unsigned int m_goalAircraftID;     // +0x20
    unsigned int m_flags;              // +0x24
    PathfindCell *m_cell;              // +0x28
    PathfindCellInfo *m_freeNext;      // +0x2c
    PathfindCellInfo **m_freePrevLink; // +0x30
};

extern "C" PathfindCellInfo *g_bfmePathfindFreeList;
__declspec(noinline) PathfindCellInfo *bfmeAcquirePathfindCellInfo(PathfindCellInfo **,
                                                                   PathfindCell *,
                                                                   const ICoord2D *);
struct BfmeNodeNO;
class BfmeThingBRE
{
  public:
    void bfmeGoBRE(void *);
};
class BfmeThingNO
{
  public:
    void bfmeMoveNO(BfmeNodeNO **);
};
class Gen_003F69E0
{
  public:
    void bfmeDetach();
};
class Rva003F7380State
{
  public:
    void finishReset();
};
class Rva003D49E0
{
  public:
    int get();
};
class Rva003D4A00
{
  public:
    int get();
};
class Rva003F69C0Object
{
  public:
    void set(int *, int);
};
class PathfindCell
{
  public:
    Bool startPathfind(PathfindCell *);
    UnsignedInt costToHierGoal(PathfindCell *);
    PathfindCellInfo *m_info;
    int m_04;
    zoneStorageType m_zone, m_zoneA;
    unsigned int m_packed;
    UnsignedShort getXIndex() const
    {
        return m_info->m_pos.x;
    }
    UnsignedShort getYIndex() const
    {
        return m_info->m_pos.y;
    }
    PathfindLayerEnum getLayer() const
    {
        return (PathfindLayerEnum)((m_packed >> 6) & 63);
    }
    zoneStorageType getZone() const
    {
        return m_zone;
    }
    Bool inlineClosed() const
    {
        return (m_info->m_flags >> 4) & 1;
    }
    Bool inlineOpen() const
    {
        return (m_info->m_flags >> 3) & 1;
    }
    Bool hasInfo() const
    {
        return m_info != 0;
    }
    Bool getClosed()
    {
        return (unsigned char)((Rva003D4A00 *)this)->get() != 0;
    }
    Bool getOpen()
    {
        return (unsigned char)((Rva003D49E0 *)this)->get() != 0;
    }
    __forceinline void allocateInfo(const ICoord2D &p)
    {
        if (!m_info)
        {
            if (!g_bfmePathfindFreeList)
                PathfindCellInfo::allocateCellInfos();
            m_info = bfmeAcquirePathfindCellInfo(&g_bfmePathfindFreeList, this, &p);
        }
        else
            m_info->m_prevOpen = 0;
    }
    void releaseInfo()
    {
        ((Rva003F7380State *)this)->finishReset();
    }
    void setParentCellHierarchical(PathfindCell *p, void *w = 0)
    {
        ((Rva003F69C0Object *)this)->set((int *)p, (int)w);
    }
    void setCostSoFar(unsigned int n)
    {
        m_info->m_costSoFar = (unsigned short)n;
    }
    void setTotalCost(unsigned int n)
    {
        m_info->m_totalCost = (unsigned short)n;
    }
    unsigned int getCostSoFar() const
    {
        return m_info->m_costSoFar;
    }
    void putOnClosedList(BfmeNodeNO **list)
    {
        ((BfmeThingNO *)this)->bfmeMoveNO(list);
    }
};
class Rva003DB4C0
{
  public:
    Bool field() const;
};
class Rva003DB4F0
{
  public:
    Int value() const;
};
class Object
{
  public:
    Bool bfmeIsComputerControlled() const;
    int layerValue() const
    {
        return ((const Rva003DB4F0 *)this)->value();
    }
    Bool flag4cc() const
    {
        return ((const Rva003DB4C0 *)this)->field();
    }
};
class TerrainLogic
{
  public:
    PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
class Waypoint
{
  public:
    Bool method001ABBB0(Object *);
    char m_00[12];
    Coord3D m_pos;
    char m_18[8];
    Waypoint *m_links[8];
    char m_40[12];
    int m_numLinks;
};
struct PathfindMovementProfile
{
    Int acceptableSurfaces;
    Bool crusher, terrainOnly;
    char m_pad[2];
    Int layer;
};
class PathfindZoneManager
{
  public:
    zoneStorageType getEffectiveZone(const PathfindMovementProfile &, zoneStorageType) const;
    zoneStorageType bfmeEffectiveTerrainZone(const PathfindMovementProfile &,
                                             zoneStorageType) const;
    __forceinline zoneStorageType bfmeGetBlockZone(const PathfindMovementProfile &p, Int x, Int y,
                                                   PathfindCell **m) const
    {
        typedef zoneStorageType (PathfindZoneManager::*Method)(const PathfindMovementProfile &, Int,
                                                               Int, PathfindCell **) const;
        union {
            void (*entry)();
            Method method;
        } call;
        call.entry = j_00003ff3;
        return (this->*call.method)(p, x, y, m);
    }
    Bool bfmeInteractsWithBridge(Int, Int) const;
    Bool bfmeHasWaypoints(Int, Int) const;
    Waypoint *bfmeGetWaypoint(Int, Int, UnsignedInt) const;
    char m_00[0x2362c];
    ICoord2D m_zoneBlockExtent;
    void getExtent(ICoord2D &p) const
    {
        p = m_zoneBlockExtent;
    }
};
class PathfindLayer
{
  public:
    Bool isUsed();
    char m_00[0x18];
    ICoord2D m_start, m_end;
    int m_28;
    int m_zone;
    int m_30;
    Bool m_destroyed;
    char m_35[0x44 - 0x35];
    void getStartCellIndex(ICoord2D *p)
    {
        *p = m_start;
    }
    void getEndCellIndex(ICoord2D *p)
    {
        *p = m_end;
    }
};
class Gen_003D6400
{
  public:
    void bfmeCopyIndexed(BfmeThingBRE *);
};
class Gen_003D6490
{
  public:
    Gen_003F69E0 *bfmeTakeFirstLive();
};
class PathfindCellInfoPool
{
  public:
    void reset();
};
class Rva003DDE30Waypoints
{
  public:
    __forceinline void clear()
    {
        typedef void (Rva003DDE30Waypoints::*Method)();
        union {
            void (*entry)();
            Method method;
        } call;
        call.entry = j_00018471;
        (this->*call.method)();
    }
};
bool rva3d5120(int);
class Pathfinder
{
  protected:
    Path *internal_findHierarchicalPath(Bool, Int, Object *, const Coord3D *, const Coord3D *, Bool,
                                        Bool);

  public:
    void clip(Coord3D *, Coord3D *);
    Bool worldToCell(const Coord3D *, ICoord2D *);
    PathfindCell *getCell(PathfindLayerEnum, Int, Int);
    __forceinline int rva003DB900(PathfindCell *a, PathfindCell *b)
    {
        typedef int (Pathfinder::*Method)(PathfindCell *, PathfindCell *);
        union {
            void (*entry)();
            Method method;
        } call;
        call.entry = j_0003a828;
        return (this->*call.method)(a, b);
    }
    __forceinline Bool rva003ED070(Object *o, Int a, Int b, const void *p)
    {
        typedef Bool (Pathfinder::*Method)(Object *, Int, Int, const void *);
        union {
            void (*entry)();
            Method method;
        } call;
        call.entry = j_0002f798;
        return (this->*call.method)(o, a, b, p);
    }
    __forceinline void rva003D9970(const ICoord2D &a, const ICoord2D &b, PathfindCell *c,
                                   PathfindCell *d, zoneStorageType e, zoneStorageType *f, Int &g,
                                   const PathfindMovementProfile &h, Int &i)
    {
        typedef void (Pathfinder::*Method)(const ICoord2D &, const ICoord2D &, PathfindCell *,
                                           PathfindCell *, zoneStorageType, zoneStorageType *,
                                           Int &, const PathfindMovementProfile &, Int &);
        union {
            void (*entry)();
            Method method;
        } call;
        call.entry = j_00042d3e;
        (this->*call.method)(a, b, c, d, e, f, g, h, i);
    }

  protected:
    Path *buildHierachicalPath(const Coord3D *, PathfindCell *);

  public:
    void putOnOpenList(PathfindCell *p)
    {
        ((Gen_003D6400 *)this)->bfmeCopyIndexed((BfmeThingBRE *)p);
    }
    PathfindCell *popOpenList()
    {
        return (PathfindCell *)((Gen_003D6490 *)this)->bfmeTakeFirstLive();
    }
    __forceinline PathfindCell *firstOpenCell()
    {
        while (m_openBucket < 512)
        {
            if (m_openBuckets[m_openBucket])
            {
                PathfindCell *p = m_openBuckets[m_openBucket]->m_cell;
                ((Gen_003F69E0 *)p)->bfmeDetach();
                return p;
            }
            ++m_openBucket;
        }
        return 0;
    }
    void cleanOpenAndClosedLists()
    {
        ((PathfindCellInfoPool *)this)->reset();
    }
    __forceinline PathfindCell *getGroundCell(Int x, Int y)
    {
        if (x < m_extent.lo.x || x > m_extent.hi.x || y < m_extent.lo.y || y > m_extent.hi.y)
            return 0;
        return &m_map[x][y];
    }
    char m_00[8];
    Bool m_isMapReady;
    char m_09[7];
    PathfindCell **m_map;
    IRegion2D m_extent, m_logicalExtent;
    PathfindCellInfo *m_openBuckets[512];
    Int m_openBucket;
    BfmeNodeNO *m_closedList;
    Bool m_isTunneling;
    char m_83d[0x85c - 0x83d];
    PathfindLayer m_layers[16];
    PathfindZoneManager m_zoneManager;
    char m_tail[0x2470c - (0xc9c + 0x23634)];
    Rva003DDE30Waypoints m_waypoints;
};

Path *Pathfinder::internal_findHierarchicalPath(Bool isHuman, Int surfaces, Object *obj,
                                                const Coord3D *from, const Coord3D *rawTo,
                                                Bool crusher, Bool closestOK)
{
    if (rawTo->x == 0.0f && rawTo->y == 0.0f)
        return 0;
    if (!m_isMapReady)
        return 0;
    Coord3D adjustTo = *rawTo;
    Coord3D clipFrom = *from;
    clip(&clipFrom, &adjustTo);
    m_isTunneling = false;
    PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(0, &adjustTo);
    PathfindCell *goalCell;
    {
        ICoord2D cell;
        worldToCell(&adjustTo, &cell);
        goalCell = getCell(destinationLayer, cell.x, cell.y);
        if (!goalCell)
            return 0;
        goalCell->allocateInfo(cell);
    }
    PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, from);
    PathfindCell *parentCell;
    {
        ICoord2D fromNdx;
        worldToCell(&clipFrom, &fromNdx);
        parentCell = getCell(layer, fromNdx.x, fromNdx.y);
    }
    if (!parentCell)
        return 0;
    if (parentCell == goalCell)
    {
        goalCell->releaseInfo();
        return 0;
    }
    {
        ICoord2D startCellNdx;
        worldToCell(&clipFrom, &startCellNdx);
        parentCell->allocateInfo(startCellNdx);
    }
    PathfindMovementProfile profile;
    Bool computer = obj->bfmeIsComputerControlled();
    Int profileLayer = obj->layerValue() - 1;
    Bool flag = obj->flag4cc();
    profile.crusher = !flag;
    profile.layer = profileLayer;
    profile.acceptableSurfaces = surfaces;
    profile.terrainOnly = computer;
    Int zone1 = m_zoneManager.getEffectiveZone(profile, parentCell->getZone());
    zoneStorageType zone2 = m_zoneManager.getEffectiveZone(profile, goalCell->getZone());
    if (zone1 == 0)
        goto invalid_zones;
    if ((goalCell->m_packed & 7) == 4)
    {
        zone2 = m_zoneManager.bfmeEffectiveTerrainZone(profile, zone2);
        zone2 = m_zoneManager.getEffectiveZone(profile, zone2);
    }
    if (!rva003ED070(obj, zone1, zone2, 0))
        goto invalid_zones;
    {
        parentCell->startPathfind(goalCell);
        parentCell->setTotalCost(rva003DB900(parentCell, goalCell));
        Int cellCount = 0;
        zoneStorageType goalBlockZone;
        ICoord2D goalBlockNdx;
        if (rva3d5120(goalCell->getLayer()))
        {
            goalBlockZone = m_zoneManager.bfmeGetBlockZone(profile, goalCell->getXIndex(),
                                                           goalCell->getYIndex(), m_map);
            goalBlockNdx.x = goalCell->getXIndex() / 16;
            goalBlockNdx.y = goalCell->getYIndex() / 16;
        }
        else
        {
            goalBlockZone = goalCell->getZone();
            goalBlockNdx.x = -1;
            goalBlockNdx.y = -1;
        }
        putOnOpenList(parentCell);
        if (!rva3d5120(parentCell->getLayer()))
        {
            ICoord2D ndx, toNdx;
            PathfindLayerEnum layer = parentCell->getLayer();
            m_layers[layer].getStartCellIndex(&ndx);
            m_layers[layer].getEndCellIndex(&toNdx);
            PathfindCell *cell = getGroundCell(toNdx.x, toNdx.y);
            PathfindCell *startCell = getGroundCell(ndx.x, ndx.y);
            if (cell && startCell)
            {
                popOpenList();
                parentCell->putOnClosedList(&m_closedList);
                startCell->allocateInfo(ndx);
                startCell->setParentCellHierarchical(parentCell);
                ++cellCount;
                Int curCost = startCell->costToHierGoal(parentCell);
                Int remCost = startCell->costToHierGoal(goalCell);
                startCell->setCostSoFar(curCost);
                startCell->setTotalCost(remCost);
                startCell->setParentCellHierarchical(parentCell);
                putOnOpenList(startCell);
                ++cellCount;
                cell->allocateInfo(toNdx);
                curCost = cell->costToHierGoal(parentCell);
                remCost = cell->costToHierGoal(goalCell);
                cell->setCostSoFar(curCost);
                cell->setTotalCost(remCost);
                cell->setParentCellHierarchical(parentCell);
                putOnOpenList(cell);
            }
        }
        PathfindCell *closestCell = 0;
        Real closestDistSqr = 1.0e12f;
        while ((parentCell = firstOpenCell()) != 0)
        {
            parentCell->putOnClosedList(&m_closedList);
            zoneStorageType parentZone;
            unsigned int parentLayer = parentCell->getLayer();
            if (parentLayer == 1 || parentLayer > 15)
                parentZone = m_zoneManager.bfmeGetBlockZone(profile, parentCell->getXIndex(),
                                                            parentCell->getYIndex(), m_map);
            else
                parentZone = parentCell->getZone();
            Int blockX = parentCell->getXIndex() / 16;
            Int blockY = parentCell->getYIndex() / 16;
            Bool reachedGoal = false;
            if (parentZone == goalBlockZone &&
                (goalBlockNdx.x == -1 || (blockX == goalBlockNdx.x && blockY == goalBlockNdx.y)))
                reachedGoal = true;
            ICoord2D zoneBlockExtent;
            m_zoneManager.getExtent(zoneBlockExtent);
            if (reachedGoal)
                goto found_goal;
            if (m_zoneManager.bfmeInteractsWithBridge(parentCell->getXIndex(),
                                                      parentCell->getYIndex()))
            {
                for (Int i = 0; i <= 15; ++i)
                {
                    if (!m_layers[i].isUsed() || m_layers[i].m_destroyed)
                        continue;
                    ICoord2D ndx, toNdx;
                    m_layers[i].getStartCellIndex(&ndx);
                    m_layers[i].getEndCellIndex(&toNdx);
                    if (ndx.x / 16 != blockX || ndx.y / 16 != blockY)
                    {
                        m_layers[i].getStartCellIndex(&toNdx);
                        m_layers[i].getEndCellIndex(&ndx);
                    }
                    if (ndx.x < 0 || ndx.y < 0 || toNdx.x < 0 || toNdx.y < 0)
                        continue;
                    if (ndx.x / 16 != blockX || ndx.y / 16 != blockY)
                        continue;
                    Int bridgeZone = m_zoneManager.bfmeGetBlockZone(profile, ndx.x, ndx.y, m_map);
                    if (bridgeZone != parentZone)
                    {
                        if (ndx.x / 16 == toNdx.x / 16 && ndx.y / 16 == toNdx.y / 16)
                        {
                            ICoord2D swap = ndx;
                            ndx = toNdx;
                            toNdx = swap;
                            bridgeZone =
                                m_zoneManager.bfmeGetBlockZone(profile, ndx.x, ndx.y, m_map);
                        }
                        if (bridgeZone != parentZone)
                            continue;
                    }
                    if (m_layers[i].m_zone == goalBlockZone)
                        goto found_goal;
                    PathfindCell *cell = getGroundCell(toNdx.x, toNdx.y);
                    if (!cell || cell->getClosed() || cell->getOpen())
                        continue;
                    PathfindCell *startCell = getGroundCell(ndx.x, ndx.y);
                    if (!startCell || startCell == cell)
                        continue;
                    if (startCell != parentCell)
                    {
                        startCell->allocateInfo(ndx);
                        startCell->setParentCellHierarchical(parentCell);
                        if (!startCell->getClosed() && !startCell->getOpen())
                            startCell->putOnClosedList(&m_closedList);
                    }
                    cell->allocateInfo(toNdx);
                    cell->setParentCellHierarchical(startCell);
                    ++cellCount;
                    Int curCost = cell->costToHierGoal(startCell);
                    Int remCost = cell->costToHierGoal(goalCell);
                    cell->setCostSoFar(startCell->getCostSoFar() + curCost);
                    cell->setTotalCost(cell->getCostSoFar() + remCost);
                    cell->setParentCellHierarchical(startCell);
                    putOnOpenList(cell);
                }
            }
            if (m_zoneManager.bfmeHasWaypoints(parentCell->getXIndex(), parentCell->getYIndex()))
            {
                Bool reachedWaypointGoal = false;
                for (Int i = 0; i < 13; ++i)
                {
                    Waypoint *waypoint = m_zoneManager.bfmeGetWaypoint(parentCell->getXIndex(),
                                                                       parentCell->getYIndex(), i);
                    if (!waypoint || !waypoint->method001ABBB0(obj))
                        continue;
                    ICoord2D ndx;
                    worldToCell(&waypoint->m_pos, &ndx);
                    for (Int j = 0; j < waypoint->m_numLinks; ++j)
                    {
                        if (j < 0 || j >= 8 || !waypoint->m_links[j])
                            continue;
                        ICoord2D toNdx;
                        worldToCell(&waypoint->m_links[j]->m_pos, &toNdx);
                        if (ndx.x / 16 != blockX || ndx.y / 16 != blockY)
                        {
                            m_layers[i].getStartCellIndex(&toNdx);
                            m_layers[i].getEndCellIndex(&ndx);
                        }
                        if (ndx.x < 0 || ndx.y < 0 || toNdx.x < 0 || toNdx.y < 0)
                            continue;
                        if (ndx.x / 16 != blockX || ndx.y / 16 != blockY)
                            continue;
                        zoneStorageType bridgeZone =
                            m_zoneManager.bfmeGetBlockZone(profile, ndx.x, ndx.y, m_map);
                        if (bridgeZone != parentZone)
                            continue;
                        if (m_layers[i].m_zone == goalBlockZone)
                        {
                            reachedWaypointGoal = true;
                            break;
                        }
                        PathfindCell *cell = getGroundCell(toNdx.x, toNdx.y);
                        if (!cell || cell->getClosed() || cell->getOpen())
                            continue;
                        PathfindCell *startCell = getGroundCell(ndx.x, ndx.y);
                        if (!startCell)
                            continue;
                        if (startCell != parentCell)
                        {
                            startCell->allocateInfo(ndx);
                            startCell->setParentCellHierarchical(parentCell);
                            if (!startCell->getClosed() && !startCell->getOpen())
                                startCell->putOnClosedList(&m_closedList);
                        }
                        cell->allocateInfo(toNdx);
                        cell->setParentCellHierarchical(startCell, waypoint);
                        ++cellCount;
                        Int curCost = cell->costToHierGoal(startCell);
                        Int remCost = cell->costToHierGoal(goalCell);
                        cell->setCostSoFar(startCell->getCostSoFar() + curCost);
                        cell->setTotalCost(cell->getCostSoFar() + remCost);
                        cell->setParentCellHierarchical(startCell, waypoint);
                        putOnOpenList(cell);
                    }
                }
                if (reachedWaypointGoal)
                    goto found_goal;
            }
            Real dx = abs((Int)goalCell->getXIndex() - (Int)parentCell->getXIndex());
            Real dy = abs((Int)goalCell->getYIndex() - (Int)parentCell->getYIndex());
            Real distSqr = dx * dx + dy * dy;
            if (distSqr < closestDistSqr)
            {
                closestCell = parentCell;
                closestDistSqr = distSqr;
            }
            zoneStorageType examinedZones[16];
            Int numExZones = 0;
            if (blockX > 0)
            {
                for (Int i = 1; i <= 16; ++i)
                {
                    ICoord2D scanCell;
                    scanCell.x = blockX * 16;
                    scanCell.y = blockY * 16 + 8;
                    Int offset = i >> 1;
                    if (i & 1)
                        offset = -offset;
                    scanCell.y += offset;
                    ICoord2D delta;
                    delta.x = -1;
                    delta.y = 0;
                    PathfindCell *cell = getGroundCell(scanCell.x, scanCell.y);
                    if (!cell)
                        continue;
                    if (cell->hasInfo() && (cell->inlineClosed() || cell->inlineOpen()))
                        continue;
                    if (isHuman &&
                        (scanCell.x < m_logicalExtent.lo.x || scanCell.x > m_logicalExtent.hi.x ||
                         scanCell.y < m_logicalExtent.lo.y || scanCell.y > m_logicalExtent.hi.y))
                        continue;
                    rva003D9970(scanCell, delta, parentCell, goalCell, parentZone, examinedZones,
                                numExZones, profile, cellCount);
                }
            }
            if (blockX < zoneBlockExtent.x - 1)
            {
                numExZones = 0;
                for (Int i = 1; i <= 16; ++i)
                {
                    ICoord2D scanCell;
                    scanCell.x = blockX * 16 + 15;
                    scanCell.y = blockY * 16 + 8;
                    Int offset = i >> 1;
                    if (i & 1)
                        offset = -offset;
                    scanCell.y += offset;
                    ICoord2D delta;
                    delta.x = 1;
                    delta.y = 0;
                    PathfindCell *cell = getGroundCell(scanCell.x, scanCell.y);
                    if (!cell)
                        continue;
                    if (cell->hasInfo() && (cell->inlineClosed() || cell->inlineOpen()))
                        continue;
                    if (isHuman &&
                        (scanCell.x < m_logicalExtent.lo.x || scanCell.x > m_logicalExtent.hi.x ||
                         scanCell.y < m_logicalExtent.lo.y || scanCell.y > m_logicalExtent.hi.y))
                        continue;
                    rva003D9970(scanCell, delta, parentCell, goalCell, parentZone, examinedZones,
                                numExZones, profile, cellCount);
                }
            }
            if (blockY > 0)
            {
                numExZones = 0;
                for (Int i = 1; i <= 16; ++i)
                {
                    ICoord2D scanCell;
                    scanCell.y = blockY * 16;
                    scanCell.x = blockX * 16 + 8;
                    Int offset = i >> 1;
                    if (i & 1)
                        offset = -offset;
                    scanCell.x += offset;
                    ICoord2D delta;
                    delta.x = 0;
                    delta.y = -1;
                    PathfindCell *cell = getGroundCell(scanCell.x, scanCell.y);
                    if (!cell)
                        continue;
                    if (cell->hasInfo() && (cell->inlineClosed() || cell->inlineOpen()))
                        continue;
                    if (isHuman &&
                        (scanCell.x < m_logicalExtent.lo.x || scanCell.x > m_logicalExtent.hi.x ||
                         scanCell.y < m_logicalExtent.lo.y || scanCell.y > m_logicalExtent.hi.y))
                        continue;
                    rva003D9970(scanCell, delta, parentCell, goalCell, parentZone, examinedZones,
                                numExZones, profile, cellCount);
                }
            }
            if (blockY < zoneBlockExtent.y - 1)
            {
                numExZones = 0;
                for (Int i = 1; i <= 16; ++i)
                {
                    ICoord2D scanCell;
                    scanCell.y = blockY * 16 + 15;
                    scanCell.x = blockX * 16 + 8;
                    Int offset = i >> 1;
                    if (i & 1)
                        offset = -offset;
                    scanCell.x += offset;
                    ICoord2D delta;
                    delta.x = 0;
                    delta.y = 1;
                    PathfindCell *cell = getGroundCell(scanCell.x, scanCell.y);
                    if (!cell)
                        continue;
                    if (cell->hasInfo() && (cell->inlineClosed() || cell->inlineOpen()))
                        continue;
                    if (isHuman &&
                        (scanCell.x < m_logicalExtent.lo.x || scanCell.x > m_logicalExtent.hi.x ||
                         scanCell.y < m_logicalExtent.lo.y || scanCell.y > m_logicalExtent.hi.y))
                        continue;
                    rva003D9970(scanCell, delta, parentCell, goalCell, parentZone, examinedZones,
                                numExZones, profile, cellCount);
                }
            }
        }
        if (closestOK && closestCell)
        {
            m_isTunneling = false;
            Path *path = buildHierachicalPath(from, closestCell);
            if (goalCell->hasInfo() && !goalCell->getClosed() && !goalCell->getOpen())
                goalCell->releaseInfo();
            cleanOpenAndClosedLists();
            return path;
        }
        m_waypoints.clear();
        m_isTunneling = false;
        goalCell->releaseInfo();
        cleanOpenAndClosedLists();
        return 0;
    found_goal:
        if (parentCell != goalCell)
            goalCell->setParentCellHierarchical(parentCell);
        m_isTunneling = false;
        Path *path = buildHierachicalPath(from, goalCell);
        if (goalCell->hasInfo() && !(goalCell->m_info->m_flags >> 4 & 1) && !goalCell->getOpen())
            goalCell->releaseInfo();
        if (parentCell->hasInfo() && !(parentCell->m_info->m_flags >> 4 & 1) &&
            !parentCell->getOpen())
            parentCell->releaseInfo();
        cleanOpenAndClosedLists();
        return path;
    }
invalid_zones:
    goalCell->releaseInfo();
    parentCell->releaseInfo();
    return 0;
}

extern int g_bfmePathfindInfoIssued;
__declspec(noinline) PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
    PathfindCellInfo **freeListHead, PathfindCell *pathfindCell, const ICoord2D *cellPosition)
{
    PathfindCellInfo *cellInfoRecord = *freeListHead;
    if (cellInfoRecord->m_freePrevLink != 0)
    {
        *cellInfoRecord->m_freePrevLink = cellInfoRecord->m_freeNext;
        if (cellInfoRecord->m_freeNext != 0)
            cellInfoRecord->m_freeNext->m_freePrevLink = cellInfoRecord->m_freePrevLink;
        cellInfoRecord->m_freePrevLink = 0;
        cellInfoRecord->m_freeNext = 0;
    }

    cellInfoRecord->m_cell = pathfindCell;
    cellInfoRecord->m_pos = *cellPosition;
    cellInfoRecord->m_nextOpen = 0;
    cellInfoRecord->m_prevOpen = 0;
    cellInfoRecord->m_totalCost = 0;
    cellInfoRecord->m_costSoFar = 0;
    cellInfoRecord->m_pathParent = 0;
    cellInfoRecord->m_goalUnitID = 0;
    cellInfoRecord->m_posUnitID = 0;
    cellInfoRecord->m_goalAircraftID = 0;
    cellInfoRecord->m_flags &= 0xffffffe0;
    ++g_bfmePathfindInfoIssued;
    return cellInfoRecord;
}
