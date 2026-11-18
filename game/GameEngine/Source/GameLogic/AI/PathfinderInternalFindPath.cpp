// cl: /DNDEBUG /MD /Igame/Libraries/Include/Lib /Igame/GameEngine/Source/GameLogic/Object
//
// Retail 0x003F0340 (2347 B): Pathfinder::internalFindPath, Zero Hour's
// A* search with BFME's CritterDesync trace strings, movement profile and
// waypoint/tunnel checks. Built from the banked reconstruction (attempt history
// 0x003f0340) and finished on 2026-10-17:
//  - worldToCell, clip, getClippedCell, the cell-info acquire and
//    getRadiusAndCenter are visible never-inlined copies, as in retail's
//    pathfinder TU (each emitted copy matches its own retail body), so VC7.1
//    knows the coordinate and cell locals do not escape;
//  - BFME's Coord3D has a user copy constructor;
//  - checkDestination is an inline owning its blocker (retail packs blocker
//    onto the cell index);
//  - the movement profile is filled by an inline init() whose arguments
//    evaluate right to left in retail's call order;
//  - the zone and obstacle reads go through the cell's getZone() and the
//    pathfinder's getIgnoreObstacleID() accessors (TU-local inline readers of
//    the fields; each changes the scratch-register rotation retail shows).
// class-gate: allow Coord3D BFME's user copy constructor, absent from the canonical header, decides the frame and copy order here
struct Coord3D
{
	Coord3D() {}
	Coord3D( const Coord3D &c ) : x(c.x), y(c.y), z(c.z) {}
	float x;
	float y;
	float z;
};
#define BFME_HAVE_COORD3D
#include "../../../Include/Common/ScalarTypes.h"

class Player;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const; int getLayer() const; Bool bfmeIsComputerControlled() const;
#include "object.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"
struct IRegion2D { ICoord2D lo, hi; };
#include "../../../Include/Common/Enums/PathfindLayerEnum.h"
class Path;
class PathfindCell;
class PathfindCellInfo;

extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *, const char *, ...);
extern "C" bool bfmeRetailCritterDesyncFlag;
extern "C" void *bfmeRetailCritterDesyncSink;
static unsigned g_rva012F1060;
extern PathfindCellInfo *g_bfmePathfindFreeList;

#define TRACE(msg) if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink) bfmeRetailCritterDesyncLog(bfmeRetailCritterDesyncSink, "CritterDesync:    Pathfinder::InternalFindPath() " msg)

extern void j_00042a37();
extern void j_0001fbbd();
extern void j_00036b33();
extern void j_0002f798();
extern void j_00049f3f();
extern void j_00036642();
extern void j_0004a980();
extern void j_00005e48();

class Player
{
public:
    unsigned char m_pad[0x2c];
    int m_playerType;
};

class AIUpdateInterface
{
public:
    int getIgnoredObstacleID();
};

class Rva003D54E0
{
public:
    int m_00, m_04, m_08, m_0c;
    char m_10, m_11;
    int m_14, m_18, m_1c;
    char m_20, m_21;
    int m_24, m_28;
    char m_2c, m_2d, m_2e;
    int m_30;

    Rva003D54E0();

};

class LocomotorSet
{
public:
    unsigned char m_pad[0x10];
    int m_validLocomotorSurfaces;
    int getValidSurfaces() const { return m_validLocomotorSurfaces; }
};

struct PathfindMovementProfile
{
    __forceinline void init(const LocomotorSet &locomotorSet, Bool crush, Int lay, Bool terrain)
    {
        acceptableSurfaces = locomotorSet.getValidSurfaces();
        crusher = crush;
        terrainOnly = terrain;
        layer = lay;
    }
    int acceptableSurfaces;
    unsigned char crusher;
    unsigned char terrainOnly;
    unsigned char padding[2];
    int layer;
};

class PathfindZoneManager
{
public:
    UnsignedShort getEffectiveZone(const PathfindMovementProfile &, UnsignedShort) const;
    UnsignedShort bfmeEffectiveTerrainZone(const PathfindMovementProfile &, UnsignedShort) const;
};

class TerrainLogic
{
public:
    PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;


class PathfindCellInfo
{
public:
    static void allocateCellInfos();
    ICoord2D m_pos;
    PathfindCellInfo *m_nextOpen;
    PathfindCellInfo *m_prevOpen;
    UnsignedShort m_totalCost;
    UnsignedShort m_costSoFar;
    unsigned m_pathParent;
    unsigned m_goalUnitID;
    unsigned m_posUnitID;
    union { unsigned m_obstacleID; unsigned m_goalAircraftID; };
    unsigned m_flags;
    PathfindCell *m_cell;
    PathfindCellInfo *m_freeNext;
    PathfindCellInfo **m_freePrevLink;
};

PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(PathfindCellInfo **, PathfindCell *, const ICoord2D *);

class PathfindCell
{
public:
    PathfindCellInfo *m_info;
    int m_unused04;
    UnsignedShort m_zone;
    UnsignedShort getZone() const { return m_zone; }
    UnsignedShort m_unused0a;
    unsigned m_bits;

    __forceinline void allocateInfo(const ICoord2D *pos)
    {
        if (!m_info)
        {
            if (!g_bfmePathfindFreeList)
                PathfindCellInfo::allocateCellInfos();
            m_info = bfmeAcquirePathfindCellInfo(&g_bfmePathfindFreeList, this, pos);
        }
        else
            m_info->m_prevOpen = 0;
    }
    unsigned getObstacleID() const { return m_info ? m_info->m_obstacleID : 0; }
    int getType() const { return m_bits & 7; }
    int getLayer() const { return (m_bits >> 6) & 0x3f; }
    Bool isObstaclePresent(int);
    Bool startPathfind(PathfindCell *);
    void rva003F6F10();
    // ?rva003F6C30@PathfindCell@@QAEXPAPAVPathfindCellInfo@@@Z absent-from-retail
    __forceinline void rva003F6C30(PathfindCellInfo **head)
    {
        typedef void (PathfindCell::*Fn)(PathfindCellInfo **);
        union { void (*raw)(); Fn fn; } call = { j_00005e48 };
        (this->*call.fn)(head);
    }
};

class Rva003DB4F0
{
public:
    int value() const;
};

class Rva003DB4C0
{
public:
    bool field() const;
};

class Pathfinder
{
public:
    Bool worldToCell(const Coord3D *, ICoord2D *);
    PathfindCell *getCell(PathfindLayerEnum, int, int);
    __declspec(noinline) PathfindCell *getClippedCell(PathfindLayerEnum layer, const Coord3D *pos);
    void clip(Coord3D *, Coord3D *);
    __forceinline PathfindCell *getCell(PathfindLayerEnum layer, const Coord3D *pos)
    {
        ICoord2D cell;
        if (!worldToCell(pos, &cell))
            return getCell(layer, cell.x, cell.y);
        return 0;
    }
    Bool validMovementPosition(const Coord3D *, PathfindLayerEnum, unsigned, Object *);
    Bool rva003DF580(Object *obj, int cellX, int cellY, PathfindLayerEnum layer,
        int radius, Bool centerInCell, void **blocker, int flags);
    __forceinline Bool checkDestination(Object *obj, int cellX, int cellY,
        PathfindLayerEnum layer, int radius, Bool centerInCell)
    {
        void *blocker;
        return rva003DF580(obj, cellX, cellY, layer, radius, centerInCell, &blocker, 1);
    }
    unsigned rva003DB900(PathfindCell *, PathfindCell *);
    void rva003D6400(PathfindCell *);
    void rva003D5FC0();
    PathfindCell *rva003D6490();
    void rva003DAE40(PathfindCell *, Object *);
    int rva003E6EE0(PathfindCell *, PathfindCell *, const LocomotorSet &, Bool, Bool, int, const ICoord2D &, const Object *, int);
    Path *buildActualPath(const Object *, int, const Coord3D *, PathfindCell *, Bool, Bool);

protected:
    void getRadiusAndCenter(const Object *, int &, Bool &);
    virtual Path *internalFindPath(Object *, const LocomotorSet &, const Coord3D *, const Coord3D *);

private:
    unsigned char m_opaque04[0x14 - 4];
    IRegion2D m_extent;
    unsigned char m_pad24[0x838 - 0x24];
    PathfindCellInfo *m_closedList;
    Bool m_isTunneling;
    unsigned char m_pad83d[0x844 - 0x83d];
    int m_ignoreObstacleID;
    unsigned char m_pad848[0xc9c - 0x848];
    PathfindZoneManager m_zoneManager;
public:
    int getIgnoreObstacleID() const { return m_ignoreObstacleID; }
};

extern "C" __declspec(dllimport) double __cdecl floor( double );

__forceinline long fast_float2long_round( float value )
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

extern const float g_bfmeDirectionWeight1285;
// ?g_Rva010977E0@@3MB: retail readonly VA 0x010977E0 is 20.0f.
// Retail readonly VA 0x01075350 is 0.0f (existing matched data row).
extern float g_Rva01095F98;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride( void );

	BfmeOverridable *getFinalOverride( void )
	{
		if (m_override == 0) return this;
		return m_override->friend_getFinalOverride();
	}

	Int m_unknown00;
	BfmeOverridable *m_override;
	unsigned char m_pad08[0xc8 - 0x08];
	Int m_flagsC8;
	unsigned char m_padCC[0xd4 - 0xcc];
	Int m_flagsD4;
	unsigned char m_padD8[0x408 - 0xd8];
	Real m_level;
};


inline __declspec(noinline) void Pathfinder::getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell )
{
	Real diameter;
	Int maxRadius = 2;
	BfmeOverridable *t1 = reinterpret_cast<BfmeOverridable *>(object->m_template);
	if ((t1 == 0 ? t1 : t1->getFinalOverride())->m_flagsC8 & 0x400) {
		maxRadius = 4;
	} else {
		BfmeOverridable *t2 = reinterpret_cast<BfmeOverridable *>(object->m_template);
		if ((t2 == 0 ? t2 : t2->getFinalOverride())->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = reinterpret_cast<const float *>(object->m_geometryInfo)[4] * 2.0f;
	if (diameter > g_bfmeDirectionWeight1285 && diameter < 20.0f) {
		diameter = 20.0f;
	}

	if ((reinterpret_cast<BfmeOverridable *>(object->m_template) == 0 ? reinterpret_cast<BfmeOverridable *>(object->m_template) :
		reinterpret_cast<BfmeOverridable *>(object->m_template)->getFinalOverride())->m_level > 0.0f) {
		diameter = (reinterpret_cast<BfmeOverridable *>(object->m_template) == 0 ? reinterpret_cast<BfmeOverridable *>(object->m_template) :
		reinterpret_cast<BfmeOverridable *>(object->m_template)->getFinalOverride())->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_Rva01095F98 );
	centerInCell = false;
	if (radius == 0) radius++;
	if (radius & 1) {
		centerInCell = true;
	}
	radius /= 2;
	if (radius > maxRadius) {
		radius = maxRadius;
		centerInCell = true;
	}
}


inline __declspec(noinline) Bool Pathfinder::worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex)
{
	cellIndex->x = REAL_TO_INT_FLOOR(worldPosition->x/10);
	cellIndex->y = REAL_TO_INT_FLOOR(worldPosition->y/10);
	Bool overflow = false;
	if (cellIndex->x < m_extent.lo.x) {overflow = true; cellIndex->x = m_extent.lo.x;}
	if (cellIndex->y < m_extent.lo.y) {overflow = true; cellIndex->y = m_extent.lo.y;}
	if (cellIndex->x > m_extent.hi.x) {overflow = true; cellIndex->x = m_extent.hi.x;}
	if (cellIndex->y > m_extent.hi.y) {overflow = true; cellIndex->y = m_extent.hi.y;}
	return overflow;
}


extern Bool ClipLine2D(ICoord2D *, ICoord2D *, ICoord2D *, ICoord2D *, IRegion2D *);
inline __declspec(noinline) void Pathfinder::clip( Coord3D *startPosition, Coord3D *endPosition )
{
	ICoord2D fromCell, toCell;
	ICoord2D clipFromCell, clipToCell;
	fromCell.x = REAL_TO_INT_FLOOR(startPosition->x/10);
	fromCell.y = REAL_TO_INT_FLOOR(startPosition->y/10);
	toCell.x = REAL_TO_INT_FLOOR(endPosition->x/10);
	toCell.y = REAL_TO_INT_FLOOR(endPosition->y/10);
	if (ClipLine2D(&fromCell, &toCell, &clipFromCell, &clipToCell,&m_extent)) {
		if (fromCell.x!=clipFromCell.x || fromCell.y != clipFromCell.y) {
			startPosition->x = clipFromCell.x*10 + 0.05f;
			startPosition->y = clipFromCell.y*10 + 0.05f;
		}
		if (toCell.x!=clipToCell.x || toCell.y != clipToCell.y) {
			endPosition->x = clipToCell.x*10 + 0.05f;
			endPosition->y = clipToCell.y*10 + 0.05f;
		}
	}
}

// ?internalFindPath@Pathfinder@@MAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@2@Z
inline __declspec(noinline) PathfindCell *Pathfinder::getClippedCell(PathfindLayerEnum layer, const Coord3D *pos)
{
	ICoord2D cell;
	worldToCell(pos, &cell);
	return getCell(layer, cell.x, cell.y);
}

Path *Pathfinder::internalFindPath(Object *obj, const LocomotorSet &locomotorSet, const Coord3D *from, const Coord3D *rawTo)
{
    if (bfmeRetailCritterDesyncSink)
        bfmeRetailCritterDesyncLog(bfmeRetailCritterDesyncSink, "CritterDesync:    Pathfinder::InternalFindPath() called");
    g_rva012F1060 = 0;
    Bool centerInCell = true;
    int radius = 0;
    getRadiusAndCenter(obj, radius, centerInCell);
    Bool isHuman = true;
    if (obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType == 1)
    {
        TRACE("1");
        isHuman = false;
    }
    if (rawTo->x == 0.0f && rawTo->y == 0.0f)
    {
        TRACE("2 return NULL");
        return 0;
    }
    if (((unsigned char *)this)[8] == 0)
    {
        TRACE("3 return NULL");
        return 0;
    }
    Coord3D adjustTo = *rawTo;
    Coord3D *to = &adjustTo;
    Coord3D clipFrom = *from;
    clip(&clipFrom, &adjustTo);
    if (!centerInCell)
    {
        TRACE("4");
        adjustTo.x += 5.0f;
        adjustTo.y += 5.0f;
    }
    m_isTunneling = false;
    PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(0, to);
    PathfindCell *goalCell;
    {
        ICoord2D cell;
        goalCell = worldToCell(to, &cell) ? 0 : getCell(destinationLayer, cell.x, cell.y);
        if (!goalCell)
        {
            TRACE("5 return NULL");
            return 0;
        }
        worldToCell(to, &cell);
        if (!checkDestination(obj, cell.x, cell.y, destinationLayer, radius, centerInCell))
        {
            TRACE("6 return NULL");
            return 0;
        }
    }
    ICoord2D startCellNdx;
    worldToCell(&clipFrom, &startCellNdx);
    PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
    PathfindCell *parentCell = getClippedCell(layer, &clipFrom);
    if (!parentCell)
    {
        TRACE("7 return NULL");
        return 0;
    }
    {
    ICoord2D pos2d;
    worldToCell(to, &pos2d);
    goalCell->allocateInfo(&pos2d);
    if (parentCell != goalCell)
    {
        TRACE("8");
        worldToCell(&clipFrom, &pos2d);
        parentCell->allocateInfo(&pos2d);
    }
    }
    if (parentCell->getType() == 4 && parentCell->getObstacleID() != (unsigned)m_ignoreObstacleID)
    {
        TRACE("9");
        m_isTunneling = true;
    }
    else
    {
        TRACE("10");
        m_isTunneling = false;
    }
    {
        typedef unsigned char (Object::*Fn)() const;
        union { void (*raw)(); Fn fn; } call = { j_00042a37 };
        if ((obj->*call.fn)())
        {
            TRACE("11");
            parentCell->startPathfind(goalCell);
            parentCell->m_info->m_totalCost = (UnsignedShort)rva003DB900(parentCell, goalCell);
            rva003D6400(parentCell);
            Path *path = buildActualPath(obj, locomotorSet.getValidSurfaces(), from, goalCell, centerInCell, false);
            goalCell->rva003F6F10();
            rva003D5FC0();
            if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
                bfmeRetailCritterDesyncLog(bfmeRetailCritterDesyncSink, "CritterDesync:    Pathfinder::InternalFindPath() 12 return %s", path ? "VALID" : "NULL");
            return path;
        }
    }
    PathfindMovementProfile profile;
    profile.init(locomotorSet, !reinterpret_cast<const Rva003DB4C0 *>(obj)->field(),
        reinterpret_cast<const Rva003DB4F0 *>(obj)->value() - 1, obj->bfmeIsComputerControlled());
    int zone1 = m_zoneManager.getEffectiveZone(profile, parentCell->getZone());
    int zone2 = m_zoneManager.getEffectiveZone(profile, goalCell->getZone());
    if (goalCell->isObstaclePresent(getIgnoreObstacleID()) || parentCell->isObstaclePresent(getIgnoreObstacleID()) || m_isTunneling)
    {
        zone2 = m_zoneManager.bfmeEffectiveTerrainZone(profile, (UnsignedShort)zone2);
        zone2 = m_zoneManager.getEffectiveZone(profile, (UnsignedShort)zone2);
        zone1 = m_zoneManager.bfmeEffectiveTerrainZone(profile, (UnsignedShort)zone1);
        zone1 = m_zoneManager.getEffectiveZone(profile, (UnsignedShort)zone1);
        TRACE("13");
    }
    if (zone1 != zone2)
    {
        typedef Bool (Pathfinder::*Fn)(Object *, int, int, void *);
        union { void (*raw)(); Fn fn; } call = { j_0002f798 };
        if (!(this->*call.fn)(obj, zone1, zone2, 0))
        {
            goalCell->rva003F6F10();
            parentCell->rva003F6F10();
            TRACE("14 return NULL");
            return 0;
        }
    }
    if (!validMovementPosition(to, destinationLayer, locomotorSet.getValidSurfaces(), obj))
    {
        m_isTunneling = false;
        goalCell->rva003F6F10();
        parentCell->rva003F6F10();
        TRACE("15 return NULL");
        return 0;
    }
    if (!validMovementPosition(from, layer, locomotorSet.getValidSurfaces(), obj))
    {
        TRACE("16");
        m_isTunneling = true;
    }
    if (!m_isTunneling)
    {
        TRACE("17");
        Rva003D54E0 info;
        info.m_08 = parentCell->getLayer();
        info.m_10 = centerInCell;
        info.m_0c = radius;
        info.m_14 = 0;
        info.m_18 = obj->m_ai ? obj->m_ai->getIgnoredObstacleID() : 0;
        worldToCell(&clipFrom, reinterpret_cast<ICoord2D *>(&info));
        info.m_11 = 1;
        typedef Bool (Pathfinder::*Fn)(Object *, Rva003D54E0 *);
        union { void (*raw)(); Fn fn; } call = { j_0004a980 };
        if (!(this->*call.fn)(obj, &info))
        {
            TRACE("18");
            m_isTunneling = true;
        }
    }
    parentCell->startPathfind(goalCell);
    parentCell->m_info->m_totalCost = (UnsignedShort)rva003DB900(parentCell, goalCell);
    rva003D6400(parentCell);
    int cellCount = 0;
    while ((parentCell = rva003D6490()) != 0)
    {
        if (parentCell == goalCell)
        {
            m_isTunneling = false;
            Path *path = buildActualPath(obj, locomotorSet.getValidSurfaces(), from, goalCell, centerInCell, false);
            parentCell->rva003F6F10();
            rva003D5FC0();
            if (bfmeRetailCritterDesyncFlag && bfmeRetailCritterDesyncSink)
                bfmeRetailCritterDesyncLog(bfmeRetailCritterDesyncSink, "CritterDesync:    Pathfinder::InternalFindPath() 19 return %s", path ? "VALID" : "NULL");
            return path;
        }
        parentCell->rva003F6C30(&m_closedList);
        if (cellCount > 15000)
        {
            TRACE("20 failed path break");
            break;
        }
        rva003DAE40(parentCell, obj);
        cellCount += rva003E6EE0(parentCell, goalCell, locomotorSet, isHuman, centerInCell, radius, startCellNdx, obj, 0);
    }
    TRACE("21");
    m_isTunneling = false;
    rva003D5FC0();
    goalCell->rva003F6F10();
    TRACE("24 return NULL");
    return 0;
}
