// cl: /DNDEBUG /MD
// stlport
//
// Retail 0x003F2160 (2045 B, ret 0x10): BFME's Pathfinder::findGroundPath,
// under the address-derived name the matched caller AIGroup.cpp already
// declares (rva003F2160): retail's ILT table contradicts both the Zero Hour
// decoration and the object-first findGroundPath spelling of this signature.
// Identity: the body is Zero Hour's Pathfinder::findGroundPath
// (AIPathfind.cpp) step for step -- clearPassableFlags, the hierarchical
// LOCOMOTORSURFACE_GROUND pre-pass deleted or setAllPassable, the rawTo zero
// test, m_isMapReady, clip, m_isTunneling = false, the MAX_OFFSET 8 ring
// search over clearCellForDiameter, the zone compare, the groundCellsCallback
// line walk, the eight neighbours with the +-3 clipIsPassable rescue and the
// 0.6f * delta * COST_ORTHOGONAL penalty.  BFME takes the object first: the
// matched caller AIGroup::checkSpecial (0x00154F00) passes (object, from, to,
// pathDiameter) through ILT 0x00048C57.  Helpers keep the names the matched
// findSafePath (PathfinderFindSafePathBfme.cpp) and the line walk
// (PathfinderGroundCellsAlongLineRva003E2620.cpp) already use.
//
// As in retail's pathfinder TU, worldToCell, clip, getClippedCell, the cell
// info acquire and the line walk are visible, never-inlined bodies here: only
// then does VC7.1 know the cell and coordinate locals do not escape, pack the
// frame to retail's 0x64 and keep the destination ring search in registers.
// Each emitted copy matches its retail body.  BFME's Coord3D has a user copy
// constructor; the trivial copy allocates the opening registers differently.

#include <vector>

#include "../../../Include/Common/ScalarTypes.h"





// class-gate: allow Coord3D BFME's user copy constructor, absent from the canonical header, decides the opening register allocation (1078 bytes differ with the trivial copy)
struct Coord3D
{
	Coord3D() {}
	Coord3D( const Coord3D &c ) : x(c.x), y(c.y), z(c.z) {}

	Real x;
	Real y;
	Real z;
};

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

extern Bool ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2,
	IRegion2D *clipRegion);

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum { COST_ORTHOGONAL = 10 };

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

class PathfindCell;
class Object;

void __cdecl operator delete(void *) throw();

class Path
{
	friend class Pathfinder;
protected:
	virtual ~Path(void);
};

struct PathfindCellInfo
{
	static void allocateCellInfos();

	ICoord2D m_pos;
	PathfindCellInfo *m_nextOpen;
	PathfindCellInfo *m_prevOpen;
	UnsignedShort m_totalCost;
	UnsignedShort m_costSoFar;
	UnsignedInt m_pathParent;
	UnsignedInt m_goalUnitID;
	UnsignedInt m_posUnitID;
	UnsignedInt m_goalAircraftID;
	UnsignedInt m_flags;
	PathfindCell *m_cell;
	PathfindCellInfo *m_freeNext;
	PathfindCellInfo **m_freePrevLink;
};
extern void *g_rva012F1094;
extern int g_rva012F1098;

// Retail 0x003D7DB0 (PathfindCellInfoAcquire.cpp).  Visible so the caller
// knows the cell position is only read.
inline __declspec(noinline) PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
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
	++g_rva012F1098;
	return cellInfoRecord;
}

class PathfindCell
{
public:
	enum CellType { CELL_CLEAR = 0x00 };

	Bool startPathfind(PathfindCell *goalCell);
	void setParentCellHierarchical(PathfindCell *parent);
	UnsignedInt costSoFar(PathfindCell *parent);
	void rva003F6F10();
	void rva003F6C30(PathfindCellInfo **head);

	__forceinline void allocateInfo(const ICoord2D *pos)
	{
		if (m_info == 0)
		{
			if (g_rva012F1094 == 0)
				PathfindCellInfo::allocateCellInfos();
			m_info = bfmeAcquirePathfindCellInfo(reinterpret_cast<PathfindCellInfo **>(&g_rva012F1094), this, pos);
		}
		else
		{
			m_info->m_prevOpen = 0;
		}
	}
	UnsignedShort getXIndex() const { return (UnsignedShort)m_info->m_pos.x; }
	UnsignedShort getYIndex() const { return (UnsignedShort)m_info->m_pos.y; }
	CellType getType() const { return (CellType)(m_bits & 7); }
	Bool getPinched() const { return (m_bits >> 18) & 1; }
	PathfindLayerEnum getLayer() const { return (PathfindLayerEnum)((m_bits >> 6) & 0x3f); }
	UnsignedShort getZone() const { return m_zone; }

	PathfindCellInfo *m_info;
	Int m_unused04;
	UnsignedShort m_zone;
	UnsignedShort m_pad0a;
	UnsignedInt m_bits;
};

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	Int layer;
};

class PathfindZoneManager
{
public:
	UnsignedShort getEffectiveZone(const PathfindMovementProfile &profile,
		UnsignedShort zone) const;
};

// The zone manager at Pathfinder+0xC9C under the names its matched passability
// helpers carry (BfmeOneHundredSixtyEight.cpp).
class BfmeGridAL : public PathfindZoneManager
{
public:
	void bfmeClearAL();
	void bfmeFillAL();
	unsigned char bfmeNearAL(Int x, Int y) const;
	unsigned char bfmeFarAL(Int x, Int y) const;
};

// Template override-chain reads of the object (S2OverrideFieldAccessors.cpp,
// Q2OverrideChainFieldReads.cpp).
class Rva003DB4F0
{
public:
	Int value() const;
};

class Rva003DB4C0
{
public:
	bool field() const;
};

class Object
{
public:
	Bool bfmeIsComputerControlled() const;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

// Retail 0x003EEB90 through ILT 0x0001FA14: the hierarchical pre-pass.
class Rva003F0EC0Owner
{
public:
	Int bfmeInnerEQC(bool isHuman, unsigned int surfaces, void *obj,
		const void *from, const void *to, unsigned int crusher, bool closestOK);
};

class PathfindLayer
{
public:
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	char m_unreconstructed[0x44];
};

class BfmeThingBRE
{
public:
	void bfmeGoBRE( void *what );
};

extern "C" int __cdecl abs( int n );
#pragma intrinsic(abs)

class Pathfinder;

struct Rva003E2620GroundCellsStruct
{
	Pathfinder *pathfinder;
	Bool centerInCell;
	PathfindCell *goalCell;
	Int pathDiameter;
};

extern Int g_Va012B4B38[8];
extern Int g_Va012B4B10[8];

class Pathfinder
{
public:
	Path *rva003F2160(Object *obj, const Coord3D *from,
		const Coord3D *rawTo, Int pathDiameter);

	__declspec(noinline) void clip(Coord3D *startPosition, Coord3D *endPosition);
	__declspec(noinline) Bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);

	// The getCell body the line walk inlines (PathfinderGroundCellsAlongLineRva003E2620.cpp).
	__forceinline PathfindCell *getCellInline( PathfindLayerEnum layer, Int cellX, Int cellY )
	{
		if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
			cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell( cellX, cellY );
				if (cell)
					return cell;
			}
			return &m_map[cellX][cellY];
		}
		return 0;
	}
	__declspec(noinline) PathfindCell *getClippedCell(PathfindLayerEnum layer, const Coord3D *pos);
	Int clearCellForDiameter(unsigned int crusher, Int cellX, Int cellY,
		PathfindLayerEnum layer, Int pathDiameter, Bool attackerOnWall);
	__declspec(noinline) Int groundCellsAlongLine003E2620(const ICoord2D &startCell,
		const ICoord2D &destinationCell, PathfindLayerEnum layer,
		Rva003E2620GroundCellsStruct *searchInfo);
	void rva003D6400(PathfindCell *cell);
	PathfindCell *rva003D6490();
	void rva003DAE40(PathfindCell *cell, Object *obj);
	void rva003D5FC0();
	UnsignedInt rva003DB900(PathfindCell *cell, PathfindCell *goalCell);
	Path *rva003E6B80(const Coord3D *from, PathfindCell *goalCell,
		Bool centerInCell, Int pathDiameter);

	unsigned char m_opaque00[8];
	Bool m_isMapReady;					// +0x8
	unsigned char m_pad09[0x10 - 9];
	PathfindCell **m_map;				// +0x10
	IRegion2D m_extent;					// +0x14
	unsigned char m_pad24[0x34 - 0x24];
	PathfindCellInfo *m_bucketHeads034[(0x834 - 0x34) / 4];	// +0x34: open-list buckets
	Int m_lowestBucket834;				// +0x834
	PathfindCellInfo *m_closedList;		// +0x838
	Bool m_isTunneling;					// +0x83C
	unsigned char m_pad83d[0x85c - 0x83d];
	PathfindLayer m_layers[16];			// +0x85C
	BfmeGridAL m_zoneManager;			// +0xC9C
	unsigned char m_pad0c9d[0x2470c - 0xc9d];
	_STL::vector<Coord3D> m_bfme2470C;	// +0x2470C
};

// Retail 0x003D7EC0 (PathfinderRva003D84A0.cpp).  Visible so the caller
// knows the cell index does not escape.
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

// Retail 0x003D5DE0 (pathfind_getcell.cpp).  Visible so the caller knows
// neither position escapes.
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

// Retail 0x003D8050 (AIPathfind.cpp).
inline __declspec(noinline) PathfindCell *Pathfinder::getClippedCell(PathfindLayerEnum layer, const Coord3D *pos)
{
	ICoord2D cell;
	worldToCell(pos, &cell);
	return getCell(layer, cell.x, cell.y);
}

// Retail 0x003E2620 (PathfinderGroundCellsAlongLineRva003E2620.cpp), the
// line walk the search calls: visible here as in retail's TU.
inline Int Pathfinder::groundCellsAlongLine003E2620( const ICoord2D &startCell,
	const ICoord2D &destinationCell, PathfindLayerEnum layer,
	Rva003E2620GroundCellsStruct *searchInfo )
{
	Int delta_x = abs( destinationCell.x - startCell.x );
	Int delta_y = abs( destinationCell.y - startCell.y );

	Int xinc2, yinc1, xinc1, numpixels, numadd, den;
	Int yinc2, num;
	if (delta_x >= delta_y)
	{
		numpixels = delta_x + 1;
		num = 2 * delta_y - delta_x;
		numadd = delta_y << 1;
		den = 2 * (delta_y - delta_x);
		xinc2 = 1;
		yinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}
	else
	{
		numpixels = delta_y + 1;
		num = 2 * delta_x - delta_y;
		numadd = delta_x << 1;
		den = 2 * (delta_x - delta_y);
		yinc2 = 1;
		xinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}

	if (startCell.x > destinationCell.x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (startCell.y > destinationCell.y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	Int x = startCell.x;
	Int y = startCell.y;
	PathfindCell *previousCell = 0;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *currentCell = getCellInline( layer, x, y );
		if (currentCell == 0)
			return 0;

		if (previousCell)
		{
			if ((Bool)(currentCell->m_info ? ((currentCell->m_info->m_flags >> 3) & 1) : false) ||
				(Bool)(currentCell->m_info ? ((currentCell->m_info->m_flags >> 4) & 1) : false))
				return 1;

			if (searchInfo->pathfinder->clearCellForDiameter( 0, x, y, (PathfindLayerEnum)currentCell->getLayer(),
				searchInfo->pathDiameter, true ) != searchInfo->pathDiameter)
				return 1;

			ICoord2D newCellCoord;
			newCellCoord.x = x;
			newCellCoord.y = y;
			if (currentCell->m_info == 0)
			{
				if (g_rva012F1094 == 0)
					PathfindCellInfo::allocateCellInfos();
				currentCell->m_info = bfmeAcquirePathfindCellInfo( reinterpret_cast<PathfindCellInfo **>(&g_rva012F1094), currentCell, &newCellCoord );
			}
			else
			{
				currentCell->m_info->m_prevOpen = 0;
			}
			currentCell->m_info->m_flags &= ~1u;

			Int costRemaining = searchInfo->pathfinder->rva003DB900( currentCell, searchInfo->goalCell );
			currentCell->m_info->m_costSoFar = previousCell->m_info->m_costSoFar + (((currentCell->m_bits >> 24) & 1) ? 2 : 5);
			currentCell->setParentCellHierarchical( previousCell );
			currentCell->m_info->m_totalCost = currentCell->m_info->m_costSoFar + costRemaining;

			Int bucket = currentCell->m_info->m_totalCost >> 7;
			Pathfinder *pathfinder = searchInfo->pathfinder;
			((BfmeThingBRE *)currentCell)->bfmeGoBRE( &pathfinder->m_bucketHeads034[bucket] );
			if (bucket < pathfinder->m_lowestBucket834)
				pathfinder->m_lowestBucket834 = bucket;
		}
		previousCell = currentCell;

		if (num < 0)
		{
			num += numadd;
			x += xinc2;
			y += yinc2;
		}
		else
		{
			num += den;
			x += xinc1;
			y += yinc1;
		}
	}

	return 0;
}

Path *Pathfinder::rva003F2160(Object *obj, const Coord3D *from,
	const Coord3D *rawTo, Int pathDiameter)
{
	Bool centerInCell = false;
	m_zoneManager.bfmeClearAL();
	m_bfme2470C.clear();
	Bool isHuman = true;
	Path *hPat = (Path *)reinterpret_cast<Rva003F0EC0Owner *>(this)->bfmeInnerEQC(
		isHuman, 1, obj, from, rawTo, 0, 0);
	if (hPat) {
		hPat->Path::~Path();
		::operator delete(hPat);
	} else {
		m_zoneManager.bfmeFillAL();
	}

	if (rawTo->x == 0.0f && rawTo->y == 0.0f) {
		return 0;
	}

	if (m_isMapReady == false) {
		return 0;
	}

	Coord3D adjustTo = *rawTo;
	Coord3D *to = &adjustTo;
	Coord3D clipFrom = *from;
	clip(&clipFrom, &adjustTo);

	m_isTunneling = false;

	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(obj, to);
	ICoord2D cell;
	worldToCell(to, &cell);

	if (pathDiameter != clearCellForDiameter(0, cell.x, cell.y, destinationLayer, pathDiameter, true)) {
		Int offset = 1;
		ICoord2D newCell;
		const Int MAX_OFFSET = 8;
		while (offset < MAX_OFFSET) {
			newCell = cell;
			cell.x += offset;
			if (clearCellForDiameter(0, cell.x, cell.y, destinationLayer, pathDiameter, true) == pathDiameter) break;
			cell.y += offset;
			if (clearCellForDiameter(0, cell.x, cell.y, destinationLayer, pathDiameter, true) == pathDiameter) break;
			cell.x -= offset;
			if (clearCellForDiameter(0, cell.x, cell.y, destinationLayer, pathDiameter, true) == pathDiameter) break;
			cell.x -= offset;
			if (clearCellForDiameter(0, cell.x, cell.y, destinationLayer, pathDiameter, true) == pathDiameter) break;
			cell.y -= offset;
			if (clearCellForDiameter(0, cell.x, cell.y, destinationLayer, pathDiameter, true) == pathDiameter) break;
			cell.y -= offset;
			if (clearCellForDiameter(0, cell.x, cell.y, destinationLayer, pathDiameter, true) == pathDiameter) break;
			cell.x += offset;
			if (clearCellForDiameter(0, cell.x, cell.y, destinationLayer, pathDiameter, true) == pathDiameter) break;
			cell.x += offset;
			if (clearCellForDiameter(0, cell.x, cell.y, destinationLayer, pathDiameter, true) == pathDiameter) break;
			offset++;
			cell = newCell;
		}
		if (offset >= MAX_OFFSET) {
			return 0;
		}
	}

	PathfindCell *goalCell = getCell(destinationLayer, cell.x, cell.y);
	if (goalCell == 0) {
		return 0;
	}
	goalCell->allocateInfo(&cell);

	ICoord2D startCellNdx;
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, from);
	PathfindCell *parentCell = getClippedCell(layer, &clipFrom);
	if (parentCell == 0) {
		return 0;
	}
	if (parentCell != goalCell) {
		worldToCell(&clipFrom, &startCellNdx);
		parentCell->allocateInfo(&startCellNdx);
	}

	Bool computer = obj->bfmeIsComputerControlled();
	Int profileLayer = reinterpret_cast<const Rva003DB4F0 *>(obj)->value() - 1;
	PathfindMovementProfile profile;
	profile.crusher = !reinterpret_cast<const Rva003DB4C0 *>(obj)->field();
	profile.acceptableSurfaces = 1;
	profile.terrainOnly = computer;
	profile.layer = profileLayer;

	Int zone1, zone2;
	zone1 = m_zoneManager.getEffectiveZone(profile, parentCell->getZone());
	zone2 = m_zoneManager.getEffectiveZone(profile, goalCell->getZone());
	if (zone1 != zone2) {
		goalCell->rva003F6F10();
		parentCell->rva003F6F10();
		return 0;
	}


	parentCell->startPathfind(goalCell);
	parentCell->m_info->m_totalCost = rva003DB900(parentCell, goalCell);
	rva003D6400(parentCell);

	while ((parentCell = rva003D6490()) != 0)
	{
		if (parentCell == goalCell)
		{
			m_isTunneling = false;
			Path *path = rva003E6B80(from, goalCell, centerInCell, pathDiameter);
			parentCell->rva003F6F10();
			rva003D5FC0();
			return path;
		}

		parentCell->rva003F6C30(&m_closedList);
		rva003DAE40(parentCell, 0);

		ICoord2D start, end;
		start.x = parentCell->getXIndex();
		start.y = parentCell->getYIndex();
		end.x = goalCell->getXIndex();
		end.y = goalCell->getYIndex();
		Rva003E2620GroundCellsStruct info;
		info.pathfinder = this;
		info.centerInCell = centerInCell;
		info.goalCell = goalCell;
		info.pathDiameter = pathDiameter;
		groundCellsAlongLine003E2620(start, end, parentCell->getLayer(), &info);

		const Int numNeighbors = 8;
		const Int firstDiagonal = 4;
		ICoord2D newCellCoord;
		PathfindCell *newCell;
		const Int adjacent[5] = {0, 1, 2, 3, 0};
		Bool neighborFlags[8] = {false, false, false, false, false, false, false};
		UnsignedInt newCostSoFar;

		for (int i = 0; i < numNeighbors; i++)
		{
			neighborFlags[i] = false;
			newCellCoord.x = parentCell->getXIndex() + g_Va012B4B38[i];
			newCellCoord.y = parentCell->getYIndex() + g_Va012B4B10[i];

			newCell = getCell(parentCell->getLayer(), newCellCoord.x, newCellCoord.y);
			if (newCell == 0)
				continue;

			if ((newCell->getLayer() == LAYER_GROUND) && !m_zoneManager.bfmeNearAL(newCellCoord.x, newCellCoord.y)) {
				Bool passable = false;
				if (m_zoneManager.bfmeFarAL(newCellCoord.x + 3, newCellCoord.y + 3)) passable = true;
				if (m_zoneManager.bfmeFarAL(newCellCoord.x - 3, newCellCoord.y + 3)) passable = true;
				if (m_zoneManager.bfmeFarAL(newCellCoord.x + 3, newCellCoord.y - 3)) passable = true;
				if (m_zoneManager.bfmeFarAL(newCellCoord.x - 3, newCellCoord.y - 3)) passable = true;
				if (!passable) continue;
			}

			if ((Bool)(newCell->m_info ? ((newCell->m_info->m_flags >> 3) & 1) : false) ||
				(Bool)(newCell->m_info ? ((newCell->m_info->m_flags >> 4) & 1) : false))
				continue;

			if (newCell != goalCell) {
				if (i >= firstDiagonal) {
					if (!neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]]) {
						continue;
					}
				}
				if (newCell->getType() != PathfindCell::CELL_CLEAR) {
					continue;
				}
				if (newCell->getPinched()) {
					continue;
				}
				neighborFlags[i] = true;
				newCell->allocateInfo(&newCellCoord);
			}

			Int clearDiameter = clearCellForDiameter(0, newCellCoord.x, newCellCoord.y,
				newCell->getLayer(), pathDiameter, false);
			newCostSoFar = newCell->costSoFar(parentCell);
			if (clearDiameter < pathDiameter) {
				int delta = pathDiameter - clearDiameter;
				newCostSoFar += 0.6f * (delta * COST_ORTHOGONAL);
			}
			newCell->m_info->m_flags &= ~1u;

			Int costRemaining = rva003DB900(newCell, goalCell);
			newCell->m_info->m_costSoFar = newCostSoFar;
			newCell->setParentCellHierarchical(parentCell);
			newCell->m_info->m_totalCost = newCell->m_info->m_costSoFar + costRemaining;
			rva003D6400(newCell);
		}
	}

	m_isTunneling = false;
	goalCell->rva003F6F10();
	rva003D5FC0();
	return 0;
}
