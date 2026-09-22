// ?d_003e9720@@YAXXZ
// partial score=0.5095785440613028 date=2026-09-21
// Compile symbol: ?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@W4PathfindLayerEnum@@PBDH@Z
// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled
//
// Retail 0x003E9720: Pathfinder::updateGoal(Object *, Coord3D const *,
// PathfindLayerEnum, char const *, int).  The five-argument identity is
// anchored by the GiantBird and AIUpdate callers through ILT 0x000294E2.
// TU-local offset views are restricted to fields witnessed by this hub.
// +D4 bit 12 is the same kind ordinal 108 tested through Thing::isKindOf.
// Retail: aligned ESP, 0x34 local allocation, saved EBX/ESI/EDI, ret 0x14; no EH.
// This complete reconstruction is partial; see PROGRESS.md for measured bytes.

#include "../../Code/Libraries/Source/WWVegas/WWMath/coord.h"

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum KindOfType
{
	BFME_KIND_108 = 108
};

// Retail float wrapper at 0x00069750; not the imported double overload.
extern Real rva00069750(Real);
#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(rva00069750((Real)(x))))

// Exact IEEE-754 values read from retail VA 0x01075C70 and 0x0107533C.
static const Real kVa01075C70 = 0.1f;
static const Real kVa0107533C = 0.5f;

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
	unsigned char m_kindOfLowByte;
	unsigned char m_pad_C9[0xD4 - 0xC9];
	UnsignedInt m_kindOfWord3;
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

class Rva003E9720ContainView : public BfmeVirtualSlots<64>
{
public:
	virtual UnsignedInt rva003E9720Slot100(Int) = 0;
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

	unsigned char m_pad_008[0x74 - 0x08];
	UnsignedInt m_id;
	unsigned char m_pad_078[0x9C - 0x78];
	ICoord2D m_rva003E9720_09C;
	ICoord2D m_rva003E9720_0A4;
	unsigned char m_pad_0AC[0x1FC - 0x0AC];
	Rva003E9720ContainView *m_contain;
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
	void updateGoal(Object *obj, const Coord3D *newGoalPos, PathfindLayerEnum layer,
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
#pragma comment(linker, "/alternatename:?rva00069750@@YAMM@Z=?j_0000597a@@YAXXZ")
#pragma comment(linker, "/alternatename:?isAircraftThatAdjustsDestination@AIUpdateInterface@@QBE_NXZ=?j_00024c99@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRadiusAndCenter@Pathfinder@@IAEXPBVObject@@AAHAA_N@Z=?j_000461ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?removeGoal@Pathfinder@@QAEXPAVObject@@@Z=?j_00015d02@@YAXXZ")
#pragma comment(linker, "/alternatename:?setDestinationLayer@Object@@QAEXW4PathfindLayerEnum@@@Z=?j_00039d4c@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCell@Pathfinder@@QAEPAVPathfindCell@@W4PathfindLayerEnum@@HH@Z=?j_00020671@@YAXXZ")
#pragma comment(linker, "/alternatename:?setGoalAircraft@PathfindCell@@QAEXIABUICoord2D@@@Z=?j_0002eb2c@@YAXXZ")
#pragma comment(linker, "/alternatename:?setGoalUnit@PathfindCell@@QAEXIABUICoord2D@@@Z=?j_000140b0@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosUnit@PathfindCell@@QAEXIABUICoord2D@@@Z=?j_0000a4ac@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")

void Pathfinder::updateGoal(Object *obj, const Coord3D *newGoalPos,
	PathfindLayerEnum layer, const char *file, Int line)
{
	Bool centerOrSamePosition;
	Bool doGround;
	Bool doLayer;
	Int radius;
	// Retail uses separate aircraft and ground setter pairs.
	ICoord2D groundCellNdx;
	Pathfinder *self = this;
	if (obj->m_privateStatus & 1)
		return;

	ThingTemplate *tmpl = (ThingTemplate *)obj->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if ((tmpl->m_kindOfWord3 & 0x1000) != 0)
	{
		Rva003E9720ContainView *contain = obj->m_contain;
		if (contain != 0 && contain->rva003E9720Slot100(0) < 2)
			return;
	}

	tmpl = (ThingTemplate *)obj->m_template;
	if (tmpl != 0 && tmpl->m_nextOverride != 0)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if ((tmpl->m_kindOfLowByte & 4) != 0)
		return;

	AIUpdateInterface *ai = obj->m_ai;
	if (ai == 0)
		return;

	if (!ai->isDoingGroundMovement())
	{
		if (!ai->isAircraftThatAdjustsDestination())
			return;

		ICoord2D goalCell = obj->m_rva003E9720_09C;
		ICoord2D newCell;
		self->getRadiusAndCenter(obj, radius, doLayer);
		Int numCellsAbove = radius;
		if (doLayer)
			numCellsAbove++;

		if (doLayer)
		{
			newCell.x = REAL_TO_INT_FLOOR(newGoalPos->x * kVa01075C70);
			newCell.y = REAL_TO_INT_FLOOR(newGoalPos->y * kVa01075C70);
		}
		else
		{
			newCell.x = REAL_TO_INT_FLOOR(
				kVa0107533C + newGoalPos->x * kVa01075C70);
			newCell.y = REAL_TO_INT_FLOOR(
				kVa0107533C + newGoalPos->y * kVa01075C70);
		}

		if (newCell.x == goalCell.x && newCell.y == goalCell.y)
			return;

		obj->m_rva003E9720_09C = newCell;
		ICoord2D cellNdx;
		// Retail freezes both rectangle bounds before entering the scan.
		const Int scanRadius = radius;
		for (Int x = newCell.x - scanRadius; x < newCell.x + numCellsAbove; ++x)
		{
			for (Int y = newCell.y - scanRadius; y < newCell.y + numCellsAbove; ++y)
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

	else
	{
		doGround = false;
		doLayer = false;
		if (layer == LAYER_GROUND || layer >= 16)
		{
			doGround = true;
		}
		else
		{
			doLayer = true;
			if (TheTerrainLogic->objectInteractsWithBridgeEnd(obj, layer))
				doGround = true;
		}

		UnsignedInt id = obj->m_id;
		ICoord2D newCell;
		self->getRadiusAndCenter(obj, radius, centerOrSamePosition);
		Int numCellsAbove = radius;
		if (centerOrSamePosition)
			numCellsAbove++;

		if (centerOrSamePosition)
		{
			newCell.x = REAL_TO_INT_FLOOR(newGoalPos->x * kVa01075C70);
			newCell.y = REAL_TO_INT_FLOOR(newGoalPos->y * kVa01075C70);
		}
		else
		{
			newCell.x = REAL_TO_INT_FLOOR(
				kVa0107533C + newGoalPos->x * kVa01075C70);
			newCell.y = REAL_TO_INT_FLOOR(
				kVa0107533C + newGoalPos->y * kVa01075C70);
		}

		self->removeGoal(obj);
		obj->setDestinationLayer((PathfindLayerEnum)layer);
		ICoord2D posCell = obj->m_rva003E9720_0A4;
		centerOrSamePosition = newCell.x == posCell.x && newCell.y == posCell.y;
		obj->m_rva003E9720_09C = newCell;
		if (obj->isKindOf(BFME_KIND_108))
			centerOrSamePosition = false;

		const Int scanRadius = radius;
		for (Int x = newCell.x - scanRadius; x < newCell.x + numCellsAbove; ++x)
		{
			for (Int y = newCell.y - scanRadius; y < newCell.y + numCellsAbove; ++y)
			{
				PathfindCell *cell;
				if (doLayer)
				{
					cell = self->getCell((PathfindLayerEnum)layer, x, y);
					if (cell != 0)
					{
						UnsignedInt goal = cell->getGoalUnit();
						UnsignedInt pos = cell->getPosUnit();
						if (goal != pos || goal == 0)
						{
							groundCellNdx.x = x;
							groundCellNdx.y = y;
							cell->setGoalUnit(id, groundCellNdx);
							if (centerOrSamePosition && cell->getPosUnit() != id)
								cell->setPosUnit(id, groundCellNdx);
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
						if (goal != pos || goal == 0)
						{
							groundCellNdx.x = x;
							groundCellNdx.y = y;
							cell->setGoalUnit(id, groundCellNdx);
							if (centerOrSamePosition && cell->getPosUnit() != id)
								cell->setPosUnit(id, groundCellNdx);
						}
					}
				}
			}
		}
	}
}
