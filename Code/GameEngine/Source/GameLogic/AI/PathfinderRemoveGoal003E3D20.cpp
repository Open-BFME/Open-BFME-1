// ?removeGoal003E3D20@Pathfinder@@QAEXPAVObject@@@Z
// The plain removeGoal spelling is occupied by an unrelated ledger claim:
// ILT 0002248F jumps to 006C39D0 (W3DRadar buildTerrainTexture), not this body.
// Preserve that unassigned claim and distinguish this proven method by RVA.
// Retail 0x003E3D20: removeGoal; identity witnessed by landed AI-state callers.
// Object+9C goal pair; Pathfinder map+10 and extent+14: analyst hub layouts.
// Radius helper visibility is required: its authentic noinline body allows
// radius storage to expire before traversal. Both emitted bodies are byte-exact.
// Helper retained from PathfindGetRadiusAndCenterE30.cpp; no extra ledger claim.
// cl: /DNDEBUG /MD /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWMath

#include "coord.h"
typedef unsigned int ObjectID;

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

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
	BfmeOverridable *getTemplate(void) const { return m_template; }
	ObjectID getID(void) const { return m_id; }
	void *getAIUpdateInterface(void) const { return m_ai; }
	const ICoord2D *getPathfindGoalCell(void) const { return &m_rva003E3D20_09C; }
	void setPathfindGoalCell(const ICoord2D &cell) { m_rva003E3D20_09C = cell; }
	Int getDestinationLayer(void) const { return m_destinationLayer; }

	void *m_vtable;
	BfmeOverridable *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;
	unsigned char m_pad78[0x9c - 0x78];
	ICoord2D m_rva003E3D20_09C;
	unsigned char m_padA4[0xbc - 0xa4];
	Real m_boundingCircleRadius;
	unsigned char m_padC0[0x204 - 0xc0];
	void *m_ai;
	unsigned char m_pad208[0x318 - 0x208];
	Int m_destinationLayer;
};

class PathfindCellInfo
{
public:
	unsigned char m_pad00[0x14];
	ObjectID m_goalUnitID;
	unsigned char m_pad18[4];
	ObjectID m_goalAircraftID;
};

class PathfindCell
{
public:
	ObjectID getGoalUnit(void) const
	{
		PathfindCellInfo *info = (PathfindCellInfo *)m_info;
		return info ? info->m_goalUnitID : 0;
	}

	ObjectID getGoalAircraft(void) const
	{
		PathfindCellInfo *info = (PathfindCellInfo *)m_info;
		return info ? info->m_goalAircraftID : 0;
	}

	void setGoalUnit(ObjectID unitID, const ICoord2D &cellPosition);
	void setGoalAircraft(ObjectID unitID, const ICoord2D &cellPosition);

	void *m_info;
	unsigned char m_pad04[8];
	unsigned int m_packed;
};

class Pathfinder
{
public:
	void removeGoal003E3D20(Object *object);
	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY);

	PathfindCell *getGroundCell(Int cellX, Int cellY)
	{
		if (cellX >= m_extentLoX && cellX <= m_extentHiX &&
			cellY >= m_extentLoY && cellY <= m_extentHiY)
			return &m_map[cellX][cellY];
		return 0;
	}

protected:
	void getRadiusAndCenter(const Object *object, Int &radius, Bool &centerInCell);
	unsigned char m_pad00[0x10];
	PathfindCell **m_map;
	Int m_extentLoX;
	Int m_extentLoY;
	Int m_extentHiX;
	Int m_extentHiY;
};

void Pathfinder::removeGoal003E3D20(Object *object)
{
	BfmeOverridable *kindTemplate = object->m_template;
	if (kindTemplate && kindTemplate->m_override)
		kindTemplate = (BfmeOverridable *)kindTemplate->getFinalOverride();
	if (kindTemplate->m_flagsC8 & 4) {
		return;
	}
	ObjectID objID = object->getID();
	void *ai = object->getAIUpdateInterface();
	if (ai == 0)
		return;
	ICoord2D goalCell = *object->getPathfindGoalCell();

	Bool centerInCell;
	Int radius;
	ICoord2D newCell;
	getRadiusAndCenter(object, radius, centerInCell);
	if (radius == 0)
		radius++;
	Int numCellsAbove = radius;
	if (centerInCell)
		numCellsAbove++;
	newCell.x = newCell.y = -1;
	if (newCell.x == goalCell.x && newCell.y == goalCell.y)
		return;
	ICoord2D cellNdx;
	object->setPathfindGoalCell(newCell);
	Int i, j;
	if (goalCell.x >= 0 && goalCell.y >= 0) {
		for (i = goalCell.x - radius; i < goalCell.x + numCellsAbove; i++) {
			for (j = goalCell.y - radius; j < goalCell.y + numCellsAbove; j++) {
				PathfindCell *cell = getGroundCell(i, j);
				if (cell) {
					if (cell->getGoalUnit() == objID) {
						cellNdx.x = i;
						cellNdx.y = j;
						cell->setGoalUnit(0, cellNdx);
					}
					if (cell->getGoalAircraft() == objID) {
						cellNdx.x = i;
						cellNdx.y = j;
						cell->setGoalAircraft(0, cellNdx);
					}
				}
				if (object->getDestinationLayer() != LAYER_GROUND &&
					object->getDestinationLayer() < 16) {
					cell = (PathfindCell *)getCell(
						(PathfindLayerEnum)object->getDestinationLayer(), i, j);
					if (cell && cell->getGoalUnit() == objID) {
						cellNdx.x = i;
						cellNdx.y = j;
						cell->setGoalUnit(0, cellNdx);
					}
				}
			}
		}
	}
}


#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))
extern "C" __declspec(dllimport) double __cdecl floor(double);
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
