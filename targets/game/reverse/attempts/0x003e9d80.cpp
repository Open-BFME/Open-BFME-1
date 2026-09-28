// ?updatePos@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.88 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
// readable body of ?updatePos@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
//
// Retail 0x003E9D80: Pathfinder::updatePos (1213 bytes through ret 8).
// Identity: the ILT 0x00013647 is called by the matched Object::setLayer,
// OpenContain::exitObjectViaDoor, OpenContain::exitObjectInAHurry and
// AIUpdateInterface::loadPostProcess; the body is the Zero Hour updatePos
// (same radius/centre, cell-flip and old/new cell sweeps) forked for BFME.
// BFME returns a Bool (every exit loads al), keeps the current pathfind cell
// on the Object (+0xA4/+0xA8) instead of the AI module, and adds a dead-object
// layer repair at the top. Layouts follow the landed siblings
// PathfinderRemoveGoal003E3D20.cpp and PathfinderGetLayer.cpp.

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int ObjectID;

struct ICoord2D
{
	Int x, y;
};

struct Coord3D
{
	Real x, y, z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum KindOfType
{
};

// Out-of-line float overload (retail calls it through ILT 0x0000597A).
float __cdecl floor(float);

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(floor(x)))

extern const Real g_pathfindCellSize;
extern const Real g_pathfindDoubleCellSize;
extern const Real g_pathfindLevelLimit;
extern const Real g_pathfindCellCenterBias;

// Retail 0x003D5120 (ILT 0x0003C8DF): value == 1 || value >= 16.
bool rva3d5120(int value);

template <Int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public BFMEVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement() const = 0;    // vtable +0x1EC
	virtual Bool rva003E9D80Slot1F0() const = 0;       // vtable +0x1F0
	__forceinline Bool groundMovementNotSlot1F0_003E9D80() const { return isDoingGroundMovement() && !rva003E9D80Slot1F0(); }
};

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic : public BFMEVirtualSlots<41>
{
public:
	virtual Bool objectInteractsWithBridgeEnd(Object *obj, Int layer) const = 0; // vtable +0xA4
};

extern TerrainLogic *TheTerrainLogic;

class Thing
{
public:
	Bool isKindOf(KindOfType t) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	BfmeOverridable *getTemplate(void) const { return m_template; }
	ObjectID getID(void) const { return m_id; }
	AIUpdateInterface *getAIUpdateInterface(void) const { return m_ai; }
	const ICoord2D *getCurPathfindCell(void) const { return &m_rva003E9D80_0A4; }
	void setCurPathfindCell(const ICoord2D &cell) { m_rva003E9D80_0A4 = cell; }
	Bool isEffectivelyDead(void) const { return (m_privateStatus & 1) != 0; }
	Int getLayer(void) const;
	void setLayer(PathfindLayerEnum layer);

	void *m_vtable;
	BfmeOverridable *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;
	unsigned char m_pad78[0xa4 - 0x78];
	ICoord2D m_rva003E9D80_0A4;
	unsigned char m_padAC[0xbc - 0xac];
	Real m_boundingCircleRadius;
	unsigned char m_padC0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x344 - 0x208];
	unsigned char m_privateStatus;
};

class PathfindCellInfo
{
public:
	unsigned char m_pad00[0x14];
	ObjectID m_goalUnitID;
	ObjectID m_posUnitID;
};

class PathfindCell
{
public:
	ObjectID getGoalUnit(void) const
	{
		PathfindCellInfo *info = (PathfindCellInfo *)m_info;
		return info ? info->m_goalUnitID : 0;
	}

	ObjectID getPosUnit(void) const
	{
		PathfindCellInfo *info = (PathfindCellInfo *)m_info;
		return info ? info->m_posUnitID : 0;
	}

	// BFME-only claim test (unit 0x003E9D80): the cell takes a position unit
	// when it has no info, no position unit, or the goal unit is the caller.
	Bool rva003E9D80CanTakePos(ObjectID unitID) const
	{
		PathfindCellInfo *info = (PathfindCellInfo *)m_info;
		if (info == 0 || info->m_posUnitID == 0)
			return true;
		return info->m_goalUnitID == unitID;
	}

	Int getType(void) const { return m_packed & 0x7; }
	Int getLayer(void) const { return (m_packed >> 6) & 0x3f; }

	void setPosUnit(ObjectID unitID, const ICoord2D &cellPosition);

	void *m_info;
	unsigned char m_pad04[8];
	unsigned int m_packed;
};

class Pathfinder
{
public:
	Bool updatePos(Object *obj, const Coord3D *newPos);
	void removePos(Object *obj);
	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY);
	Bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);

	__forceinline PathfindCell *getGroundCell(Int cellX, Int cellY)
	{
		if (cellX >= m_extentLoX && cellX <= m_extentHiX &&
			cellY >= m_extentLoY && cellY <= m_extentHiY)
			return &m_map[cellX][cellY];
		return 0;
	}

protected:
	void getRadiusAndCenter(const Object *object, Int &radius, Bool &centerInCell);

	unsigned char m_pad00[0x08];
	Bool m_isMapReady;
	unsigned char m_pad09[0x10 - 0x09];
	PathfindCell **m_map;
	Int m_extentLoX;
	Int m_extentLoY;
	Int m_extentHiX;
	Int m_extentHiY;
};

Bool Pathfinder::updatePos(Object *obj, const Coord3D *newPos)
{
	if (obj->isEffectivelyDead())
	{
		PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
		ICoord2D cell;
		if (worldToCell(newPos, &cell))
			return false;
		PathfindCell *pathCell = getCell(layer, cell.x, cell.y);
		if (pathCell == 0)
			return false;
		Int cellLayer = pathCell->getLayer();
		if (cellLayer == LAYER_GROUND || cellLayer != layer)
			obj->setLayer(LAYER_GROUND);
		return false;
	}

	BfmeOverridable *kindTemplate = obj->getTemplate();
	if (kindTemplate && kindTemplate->m_override)
		kindTemplate = kindTemplate->getFinalOverride();
	if (kindTemplate->m_flagsC8 & 4)
		return false;
	if (!m_isMapReady)
		return false;

	ObjectID objID = obj->getID();
	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (ai == 0)
		return false;

	ICoord2D curCell = *obj->getCurPathfindCell();
	if (!ai->groundMovementNotSlot1F0_003E9D80())
	{
		if (curCell.x >= 0 && curCell.y >= 0)
			removePos(obj);
		return false;
	}

	Bool centerInCell;
	Int radius;
	ICoord2D newCell;
	getRadiusAndCenter(obj, radius, centerInCell);
	Int numCellsAbove = radius;
	if (centerInCell)
		numCellsAbove++;
	if (centerInCell)
	{
		newCell.x = REAL_TO_INT_FLOOR(newPos->x * 0.1f);
		newCell.y = REAL_TO_INT_FLOOR(newPos->y * 0.1f);
	}
	else
	{
		newCell.x = REAL_TO_INT_FLOOR(newPos->x * 0.1f + 0.5f);
		newCell.y = REAL_TO_INT_FLOOR(newPos->y * 0.1f + 0.5f);
	}
	if (newCell.x == curCell.x && newCell.y == curCell.y)
		return false;

	PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
	Bool doGround = false;
	Bool doLayer = false;
	if (rva3d5120(layer))
	{
		PathfindCell *cell = getCell(layer, newCell.x, newCell.y);
		if (cell == 0)
			return false;
		Int cellLayer = cell->getLayer();
		if (layer != cellLayer && cell->getType() == 0)
			obj->setLayer((PathfindLayerEnum)cellLayer);
		doGround = true;
	}
	else
	{
		doLayer = true;
		if (TheTerrainLogic->objectInteractsWithBridgeEnd(obj, layer))
			doGround = true;
	}

	obj->setCurPathfindCell(newCell);
	if (obj->isKindOf((KindOfType)0x6c))
		return false;

	Int i, j;
	ICoord2D cellNdx;
	if (curCell.x >= 0 && curCell.y >= 0)
	{
		for (i = curCell.x - radius; i < curCell.x + numCellsAbove; i++)
		{
			for (j = curCell.y - radius; j < curCell.y + numCellsAbove; j++)
			{
				cellNdx.x = i;
				cellNdx.y = j;
				PathfindCell *cell = getCell(layer, i, j);
				if (cell && cell->getPosUnit() == objID)
					cell->setPosUnit(0, cellNdx);
				if (layer != LAYER_GROUND && layer < 16)
				{
					cell = getGroundCell(i, j);
					if (cell && cell->getPosUnit() == objID)
						cell->setPosUnit(0, cellNdx);
				}
			}
		}
	}
	for (i = newCell.x - radius; i < newCell.x + numCellsAbove; i++)
	{
		for (j = newCell.y - radius; j < newCell.y + numCellsAbove; j++)
		{
			PathfindCell *cell;
			cellNdx.x = i;
			cellNdx.y = j;
			if (doLayer)
			{
				cell = getCell(layer, i, j);
				if (cell && cell->rva003E9D80CanTakePos(obj->getID()))
					cell->setPosUnit(objID, cellNdx);
			}
			if (doGround)
			{
				cell = getGroundCell(i, j);
				if (cell && cell->rva003E9D80CanTakePos(obj->getID()))
					cell->setPosUnit(objID, cellNdx);
			}
		}
	}
	return true;
}

// Helper retained from PathfindGetRadiusAndCenterE30.cpp (the claimed body);
// its visible noinline definition lets VC7.1 see that the radius and centre
// outputs do not escape, as in PathfinderRemoveGoal003E3D20.cpp.
extern "C" __declspec(dllimport) double __cdecl floor(double);
#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))
__declspec(noinline) void Pathfinder::getRadiusAndCenter(
	const Object *object, Int &radius, Bool &centerInCell )
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
