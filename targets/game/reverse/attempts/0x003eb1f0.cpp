// ?snapClosestGoalPosition@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z
// partial score=0.45 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?snapClosestGoalPosition@Pathfinder@@QAEXPAVObject@@PAUCoord3D@@@Z  retail 0x003EB1F0 1678 B
// Identity: the ten CritterDesync format strings (0x010EF008..) name Pathfinder::SnapClosestGoalPosition.
// Levers in this bank: Zero Hour body plus the BFME debug logs; checkDestination is the inlined
// 0x003E6E90 wrapper (inner 8-arg call then blocker==NULL) with the Bool passed by const reference
// so the raw dword of center is pushed; worldToCell / PathfindLayer::getCell / getRadiusAndCenter
// visible noinline (frame 0x30 exact, iRadius==0 constant-propagated into logs); memberwise
// adjustDest copy; getGoalUnit ternary on m_info. Compiled 1672 vs 1678, 923 non-reloc diffs.
// Residue: pos in EDI (retail EBX), layer in EBX (retail EBP), cell.y in EBP where retail keeps
// cell.x in EDI across the first checkDestination; blocker/iRadius/center slots differ.

typedef int Int;
typedef bool Bool;
typedef unsigned char UByte;
typedef float Real;
typedef unsigned int ObjectID;

struct Coord3D { Real x, y, z; };
struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };


extern "C" __declspec(dllimport) double __cdecl floor(double);
__forceinline Real fast_float_floor(Real f) { return (Real)floor((double)f); }
__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))
#define PATHFIND_CELL_SIZE 10

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };

#define PATHFIND_CELL_SIZE_F 10.0f

class CRCParameterCheck;
extern Bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);

extern const Real g_pathfindCellSize;
extern const Real g_pathfindDoubleCellSize;
extern const Real g_pathfindLevelLimit;
extern const Real g_pathfindCellCenterBias;

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

class Object
{
public:
	ObjectID getID(void) const { return m_id; }
	BfmeOverridable *getTemplate( void ) const { return m_template; }

	Int m_unknown00;
	BfmeOverridable *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;
	unsigned char m_pad78[0xbc - 0x78];
	Real m_boundingCircleRadius;
};

class TerrainLogic
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal = 0, Bool clip = true) const;
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

class PathfindCellInfo
{
public:
	unsigned char m_pad00[0x14];
	ObjectID m_goalUnitID;
};

class PathfindCell
{
public:
	ObjectID getGoalUnit(void) const
	{
		ObjectID id = m_info ? ((PathfindCellInfo *)m_info)->m_goalUnitID : 0;
		return id;
	}
	Int getType(void) const { return m_packed & 7; }
	Int getFlags(void) const { return (m_packed >> 3) & 7; }
private:
	void *m_info;
	unsigned char m_pad04[8];
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	inline __declspec(noinline) PathfindCell *getCell(Int cellX, Int cellY)
	{
		if (m_layerCells == 0)
			return 0;
		cellX -= m_xOrigin;
		cellY -= m_yOrigin;
		if (cellX < 0 || cellX >= m_width)
			return 0;
		if (cellY < 0 || cellY >= m_height)
			return 0;
		PathfindCell *cell = &m_layerCells[cellX][cellY];
		if (cell->getType() == 5)
			return 0;
		return cell;
	}
private:
	void *m_blockOfMapCells;
	PathfindCell **m_layerCells;
	Int m_width;
	Int m_height;
	Int m_xOrigin;
	Int m_yOrigin;
	unsigned char m_tail[0x44 - 0x18];
};

class Pathfinder
{
public:
	void snapClosestGoalPosition(Object *obj, Coord3D *pos);
	inline __declspec(noinline) Bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex)
	{
		cellIndex->x = REAL_TO_INT_FLOOR(worldPosition->x/PATHFIND_CELL_SIZE);
		cellIndex->y = REAL_TO_INT_FLOOR(worldPosition->y/PATHFIND_CELL_SIZE);
		Bool overflow = false;
		if (cellIndex->x < m_extent.lo.x) {overflow = true; cellIndex->x = m_extent.lo.x;}
		if (cellIndex->y < m_extent.lo.y) {overflow = true; cellIndex->y = m_extent.lo.y;}
		if (cellIndex->x > m_extent.hi.x) {overflow = true; cellIndex->x = m_extent.hi.x;}
		if (cellIndex->y > m_extent.hi.y) {overflow = true; cellIndex->y = m_extent.hi.y;}
		return overflow;
	}
	UByte bfmeInnerE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
		void *a6, void **a7, int a8);

	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
		{
			PathfindCell *cell = 0;
			if (layer > LAYER_GROUND && layer <= LAYER_LAST)
			{
				cell = m_layers[layer].getCell(x, y);
				if (cell)
					return cell;
			}
			return &m_map[x][y];
		}
		return 0;
	}

protected:
	inline __declspec(noinline) void getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell )
	{
		Real diameter;
		Int maxRadius = 2;
		BfmeOverridable *t1 = object->getTemplate();
		if ((t1 == 0 ? t1 : t1->getFinalOverride())->m_flagsC8 & 0x400) {
			maxRadius = 4;
		} else {
			BfmeOverridable *t2 = object->getTemplate();
			if ((t2 == 0 ? t2 : t2->getFinalOverride())->m_flagsD4 & 0x1000) {
				maxRadius = 4;
			}
		}

		diameter = object->m_boundingCircleRadius * 2.0f;
		if (diameter > g_pathfindCellSize && diameter < g_pathfindDoubleCellSize) {
			diameter = 20.0f;
		}

		if ((object->getTemplate() == 0 ? object->getTemplate() :
			object->getTemplate()->getFinalOverride())->m_level > g_pathfindLevelLimit) {
			diameter = (object->getTemplate() == 0 ? object->getTemplate() :
			object->getTemplate()->getFinalOverride())->m_level;
		}

		radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_pathfindCellCenterBias );
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
	void adjustCoordToCell(Int cellX, Int cellY, Bool centerInCell,
		Coord3D &position, PathfindLayerEnum layer);

	Bool checkDestination(const Object *obj, Int cellX, Int cellY,
		PathfindLayerEnum layer, Int iRadius, const Bool &centerInCell)
	{
		void *blocker;
		if (!bfmeInnerE6E90((void *)obj, (void *)cellX, (void *)cellY,
			(void *)layer, (void *)iRadius, *(void **)&centerInCell, &blocker, 0))
			return false;
		Bool empty = (blocker == 0);
		return empty;
	}

	void adjustCoordToCellInline(Int cellX, Int cellY, Bool centerInCell,
		Coord3D &position, PathfindLayerEnum layer)
	{
		if (centerInCell) {
			position.x = ((Real)cellX + 0.5f) * PATHFIND_CELL_SIZE_F;
			position.y = ((Real)cellY + 0.5f) * PATHFIND_CELL_SIZE_F;
		} else {
			position.x = ((Real)cellX+0.05) * PATHFIND_CELL_SIZE_F;
			position.y = ((Real)cellY+0.05) * PATHFIND_CELL_SIZE_F;
		}
		position.z = TheTerrainLogic->getLayerHeight(position.x, position.y, layer);
	}

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_mid[0x85c - 0x24];
	PathfindLayer m_layers[16];
};

#define CRITTER_LOG Glo012F0239 && TheCRCParameterCheck

void Pathfinder::snapClosestGoalPosition(Object *obj, Coord3D *pos)
{
	if (CRITTER_LOG)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() called with pos=%g,%g,%g", pos->x, pos->y, pos->z);
	Int iRadius;
	Bool center;
	getRadiusAndCenter(obj, iRadius, center);
	if (CRITTER_LOG)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() iRadius=%d, center=%s", iRadius, center ? "TRUE" : "FALSE");
	ICoord2D cell;
	Coord3D adjustDest;
	adjustDest.x = pos->x;
	adjustDest.y = pos->y;
	adjustDest.z = pos->z;
	if (!center) {
		if (CRITTER_LOG)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() !center, adjustDest...");
		adjustDest.x += PATHFIND_CELL_SIZE_F/2;
		adjustDest.y += PATHFIND_CELL_SIZE_F/2;
	}
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, pos);
	worldToCell(&adjustDest, &cell);
	adjustCoordToCell(cell.x, cell.y, center, *pos, LAYER_GROUND);
	if (CRITTER_LOG)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination about to get called with cell=%d,%d, layer=%d, iRadius=%d, center=%s, pos=%g%g%g", cell.x, cell.y, layer, iRadius, center ? "TRUE" : "FALSE", pos->x, pos->y, pos->z);
	if (checkDestination(obj, cell.x, cell.y, layer, iRadius, center)) {
		if (CRITTER_LOG)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination succeeds, returning...");
		return;
	}
	if (CRITTER_LOG)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination fails, continuing...");

	// Try adjusting by 1.
	Int i, j;
	for (i = cell.x - 1; i < cell.x + 2; i++) {
		for (j = cell.y - 1; j < cell.y + 2; j++) {
			if (checkDestination(obj, i, j, layer, iRadius, center)) {
				adjustCoordToCell(i, j, center, *pos, layer);
				if (CRITTER_LOG)
					bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination2 succeeds with cell=%d,%d, layer=%d, iRadius=%d, center=%s, pos=%g%g%g", cell.x, cell.y, layer, iRadius, center ? "TRUE" : "FALSE", pos->x, pos->y, pos->z);
				return;
			}
		}
	}
	if (iRadius == 0) {
		// Try to find an unoccupied cell.
		for (i = cell.x - 1; i < cell.x + 2; i++) {
			for (j = cell.y - 1; j < cell.y + 2; j++) {
				PathfindCell *newCell = getCell(layer, i, j);
				if (newCell) {
					if (newCell->getGoalUnit() == 0 || newCell->getGoalUnit() == obj->getID()) {
						adjustCoordToCellInline(i, j, center, *pos, layer);
						if (CRITTER_LOG)
							bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination3 succeeds with cell=%d,%d, layer=%d, iRadius=%d, center=%s, pos=%g%g%g", cell.x, cell.y, layer, iRadius, center ? "TRUE" : "FALSE", pos->x, pos->y, pos->z);
						return;
					}
				}
			}
		}
		// Try to find an unoccupied cell.
		for (i = cell.x - 1; i < cell.x + 2; i++) {
			for (j = cell.y - 1; j < cell.y + 2; j++) {
				PathfindCell *newCell = getCell(layer, i, j);
				if (newCell) {
					if (newCell->getFlags() != 3) {
						adjustCoordToCellInline(i, j, center, *pos, layer);
						if (CRITTER_LOG)
							bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() CheckDestination4 succeeds with cell=%d,%d, layer=%d, iRadius=%d, center=%s, pos=%g%g%g", cell.x, cell.y, layer, iRadius, center ? "TRUE" : "FALSE", pos->x, pos->y, pos->z);
						return;
					}
				}
			}
		}
	}
	if (CRITTER_LOG)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: Pathfinder::SnapClosestGoalPosition() iRadius=%d>0 do nothing case, pos=%g%g%g", iRadius, pos->x, pos->y, pos->z);
}
