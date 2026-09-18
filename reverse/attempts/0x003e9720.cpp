// ?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@HPBDH@Z
// partial score=0.4 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003E9720: Pathfinder::updateGoal(Object *, Coord3D const *,
// PathfindLayerEnum, char const *, int).  The five-argument identity is
// anchored by the GiantBird and AIUpdate callers through ILT 0x000294E2.
// The two flag words and the object cells below are deliberately kept as
// retail-offset views; the BFME object is not the ZH Object layout.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Coord2D
{
	Int x;
	Int y;
};

typedef Coord2D ICoord2D;

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum KindOfType
{
	BFME_KIND_108 = 108
};

extern Real floor(Real);

__forceinline long bfmeFloatToIntFloor(Real value)
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define REAL_TO_INT_FLOOR(x) \
	(bfmeFloatToIntFloor(floor((Real)(x))))

extern const Real g_bfmeScaleBK;
extern const Real g_bfmeK1253;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad_008[0xC8 - 0x08];
	unsigned char m_flagsC8;
	unsigned char m_pad_C9[0xD4 - 0xC9];
	UnsignedInt m_flagsD4;
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class ContainModuleInterface : public BfmeVirtualSlots<64>
{
public:
	virtual UnsignedInt query(Int) = 0;
};

class AIUpdateInterface : public BfmeVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement() const = 0;
	Bool isAircraftThatAdjustsDestination() const;
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;

	void *m_vtable;
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	void setDestinationLayer(PathfindLayerEnum layer);
	Bool isKindOf(KindOfType kind) const;

	unsigned char m_pad_008[0x74 - 0x08];
	UnsignedInt m_id;
	unsigned char m_pad_078[0x9C - 0x78];
	ICoord2D m_rva003E9720_09C;
	ICoord2D m_rva003E9720_0A4;
	unsigned char m_pad_0AC[0x1FC - 0x0AC];
	ContainModuleInterface *m_contain;
	void *m_body_200;
	AIUpdateInterface *m_ai;
	unsigned char m_pad_208[0x344 - 0x208];
	unsigned char m_privateStatus;
};

class PathfindCellInfo
{
public:
	unsigned char m_pad_000[0x14];
	UnsignedInt m_goalUnitID;
	UnsignedInt m_posUnitID;
};

class PathfindCell
{
public:
	void setGoalAircraft(UnsignedInt unitID, const ICoord2D &pos);
	void setGoalUnit(UnsignedInt unitID, const ICoord2D &pos);
	void setPosUnit(UnsignedInt unitID, const ICoord2D &pos);

	UnsignedInt getGoalUnit() const
	{
		UnsignedInt id = m_info ? m_info->m_goalUnitID : 0;
		return id;
	}

	UnsignedInt getPosUnit() const
	{
		UnsignedInt id = m_info ? m_info->m_posUnitID : 0;
		return id;
	}

	PathfindCellInfo *m_info;
	unsigned char m_pad_004[8];
	UnsignedInt m_packed;
};

class TerrainLogic : public BfmeVirtualSlots<41>
{
public:
	virtual Bool objectInteractsWithBridgeEnd(Object *obj, Int layer) const = 0;
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void updateGoal(Object *obj, const Coord3D *newGoalPos, Int layer,
		const char *file, Int line);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	void removeGoal(Object *obj);

protected:
	void getRadiusAndCenter(const Object *obj, Int &radius, Bool &center);

	__forceinline PathfindCell *getGroundCell(Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
			return (PathfindCell *)((unsigned char *)m_map[x] +
				y * sizeof(PathfindCell));
		return 0;
	}

private:
	unsigned char m_pad_000[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?floor@@YAMM@Z=?j_0000597a@@YAXXZ")
#pragma comment(linker, "/alternatename:?isAircraftThatAdjustsDestination@AIUpdateInterface@@QBE_NXZ=?j_00024c99@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRadiusAndCenter@Pathfinder@@IAEXPBVObject@@AAHAA_N@Z=?j_000461ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?removeGoal@Pathfinder@@QAEXPAVObject@@@Z=?j_00015d02@@YAXXZ")
#pragma comment(linker, "/alternatename:?setDestinationLayer@Object@@QAEXW4PathfindLayerEnum@@@Z=?j_00039d4c@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCell@Pathfinder@@QAEPAVPathfindCell@@W4PathfindLayerEnum@@HH@Z=?j_00020671@@YAXXZ")
#pragma comment(linker, "/alternatename:?setGoalAircraft@PathfindCell@@QAEXIABUCoord2D@@@Z=?j_0002eb2c@@YAXXZ")
#pragma comment(linker, "/alternatename:?setGoalUnit@PathfindCell@@QAEXIABUCoord2D@@@Z=?j_000140b0@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosUnit@PathfindCell@@QAEXIABUCoord2D@@@Z=?j_0000a4ac@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")

void Pathfinder::updateGoal(Object *obj, const Coord3D *newGoalPos,
	Int layer, const char *file, Int line)
{
	register Pathfinder *self = this;
	if (obj->m_privateStatus & 1)
		return;

	ThingTemplate *tmpl = (ThingTemplate *)obj->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if ((tmpl->m_flagsD4 & 0x1000) != 0)
	{
		ContainModuleInterface *contain = obj->m_contain;
		if (contain != 0 && contain->query(0) < 2)
			return;
	}

	tmpl = (ThingTemplate *)obj->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if ((tmpl->m_flagsC8 & 4) != 0)
		return;

	AIUpdateInterface *ai = obj->m_ai;
	if (ai == 0)
		return;

	if (!ai->isDoingGroundMovement())
	{
		if (!ai->isAircraftThatAdjustsDestination())
			return;

		ICoord2D goalCell = obj->m_rva003E9720_09C;
		Bool centerInCell;
		Int radius;
		ICoord2D newCell;
		self->getRadiusAndCenter(obj, radius, centerInCell);
		Int numCellsAbove = radius;
		if (centerInCell)
			numCellsAbove++;

		if (centerInCell)
		{
			newCell.x = REAL_TO_INT_FLOOR(newGoalPos->x * g_bfmeScaleBK);
			newCell.y = REAL_TO_INT_FLOOR(newGoalPos->y * g_bfmeScaleBK);
		}
		else
		{
			newCell.x = REAL_TO_INT_FLOOR(
				g_bfmeK1253 + newGoalPos->x * g_bfmeScaleBK);
			newCell.y = REAL_TO_INT_FLOOR(
				g_bfmeK1253 + newGoalPos->y * g_bfmeScaleBK);
		}

		if (newCell.x == goalCell.x && newCell.y == goalCell.y)
			return;

		obj->m_rva003E9720_09C = newCell;
		ICoord2D cellNdx;
		for (Int x = newCell.x - radius;
			x < newCell.x + numCellsAbove; ++x)
		{
			for (Int y = newCell.y - radius;
				y < newCell.y + numCellsAbove; ++y)
			{
				PathfindCell *cell = self->getGroundCell(x, y);
				if (cell != 0)
				{
					cellNdx.x = x;
					cellNdx.y = y;
					cell->setGoalAircraft(obj->m_id, cellNdx);
				}
			}
		}
		return;
	}

	Bool doGround = false;
	Bool doLayer = false;
	if (layer != LAYER_GROUND && layer < 16)
	{
		doLayer = true;
		if (TheTerrainLogic->objectInteractsWithBridgeEnd(obj, layer))
			doGround = true;
	}

	UnsignedInt id = obj->m_id;
	Bool centerInCell;
	Int radius;
	ICoord2D newCell;
	self->getRadiusAndCenter(obj, radius, centerInCell);
	Int numCellsAbove = radius;
	if (centerInCell)
		numCellsAbove++;

	if (centerInCell)
	{
		newCell.x = REAL_TO_INT_FLOOR(newGoalPos->x * g_bfmeScaleBK);
		newCell.y = REAL_TO_INT_FLOOR(newGoalPos->y * g_bfmeScaleBK);
	}
	else
	{
		newCell.x = REAL_TO_INT_FLOOR(
			g_bfmeK1253 + newGoalPos->x * g_bfmeScaleBK);
		newCell.y = REAL_TO_INT_FLOOR(
			g_bfmeK1253 + newGoalPos->y * g_bfmeScaleBK);
	}

	self->removeGoal(obj);
	obj->setDestinationLayer((PathfindLayerEnum)layer);
	Bool warn = newCell.x == obj->m_rva003E9720_0A4.x &&
		newCell.y == obj->m_rva003E9720_0A4.y;
	obj->m_rva003E9720_09C = newCell;
	if (obj->isKindOf(BFME_KIND_108))
		warn = false;

	ICoord2D cellNdx;
	for (Int x = newCell.x - radius;
		x < newCell.x + numCellsAbove; ++x)
	{
		for (Int y = newCell.y - radius;
			y < newCell.y + numCellsAbove; ++y)
		{
			PathfindCell *cell;
			if (doLayer)
			{
				cell = self->getCell((PathfindLayerEnum)layer, x, y);
				if (cell != 0)
				{
					UnsignedInt goal = cell->getGoalUnit();
					UnsignedInt pos = cell->getPosUnit();
					if (goal == pos && goal == 0)
					{
						cellNdx.x = x;
						cellNdx.y = y;
						cell->setGoalUnit(id, cellNdx);
						if (warn && cell->getPosUnit() != id)
							cell->setPosUnit(id, cellNdx);
					}
				}
			}
			if (doGround)
			{
				cell = self->getGroundCell(x, y);
				if (cell != 0)
				{
					UnsignedInt goal = cell->getGoalUnit();
					UnsignedInt pos = cell->getPosUnit();
					if (goal == pos && goal == 0)
					{
						cellNdx.x = x;
						cellNdx.y = y;
						cell->setGoalUnit(id, cellNdx);
						if (warn && cell->getPosUnit() != id)
							cell->setPosUnit(id, cellNdx);
					}
				}
			}
		}
	}
}
