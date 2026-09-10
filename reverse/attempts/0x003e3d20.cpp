// ?removeGoal@Pathfinder@@QAEXPAVObject@@@Z
// partial score=0.3 date=2026-09-10
// cl: /DNDEBUG /MD

typedef int Int;
typedef bool Bool;
typedef unsigned int ObjectID;

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

class RemoveGoalTemplate
{
public:
	const RemoveGoalTemplate *getFinalOverride(void) const;

	RemoveGoalTemplate *m_vtable;
	RemoveGoalTemplate *m_nextOverride;
	unsigned char m_pad08[0xc8 - 0x08];
	unsigned char m_kindOf;
};

class Object
{
public:
	bool isKindOf(int kind) const
	{
		RemoveGoalTemplate *t = m_template;
		if (t == 0)
			return false;
		if (t->m_nextOverride)
			t = (RemoveGoalTemplate *)t->m_nextOverride->getFinalOverride();
		return (t->m_kindOf & (1u << kind)) != 0;
	}
	ObjectID getID(void) const { return m_id; }
	void *getAIUpdateInterface(void) const { return m_ai; }
	const ICoord2D *getPathfindGoalCell(void) const { return &m_goalCell; }
	void setPathfindGoalCell(const ICoord2D &cell) { m_goalCell = cell; }
	Int getDestinationLayer(void) const { return m_destinationLayer; }

	void *m_vtable;
	RemoveGoalTemplate *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;
	unsigned char m_pad78[0x9c - 0x78];
	ICoord2D m_goalCell;
	unsigned char m_padA4[0x204 - 0xa4];
	void *m_ai;
	unsigned char m_pad208[0x318 - 0x208];
	Int m_destinationLayer;
};

class RemoveGoalCellInfo
{
public:
	unsigned char m_pad00[0x14];
	ObjectID m_goalUnit;
	unsigned char m_pad18[4];
	ObjectID m_goalAircraft;
};

class PathfindCell
{
public:
	void *m_info;
	unsigned char m_pad04[8];
	unsigned int m_packed;
};

class RemoveGoalCell
{
public:
	ObjectID getGoalUnit(void) const
	{
		RemoveGoalCellInfo *info = (RemoveGoalCellInfo *)m_info;
		return info ? info->m_goalUnit : 0;
	}

	ObjectID getGoalAircraft(void) const
	{
		RemoveGoalCellInfo *info = (RemoveGoalCellInfo *)m_info;
		return info ? info->m_goalAircraft : 0;
	}

	void setGoalUnit(ObjectID unitID, const ICoord2D &pos);
	void setGoalAircraft(ObjectID unitID, const ICoord2D &pos);

	void *m_info;
	unsigned char m_pad04[8];
	unsigned int m_packed;
};

class Pathfinder
{
public:
	void removeGoal(Object *obj);
	void getRadiusAndCenter(const Object *obj, Int &radius, Bool &center);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);

	RemoveGoalCell *getGroundCell(Int x, Int y, Int cellOffset)
	{
		if (x >= m_extentLoX && x <= m_extentHiX &&
			y >= m_extentLoY && y <= m_extentHiY)
			return (RemoveGoalCell *)((unsigned char *)m_map[x] + cellOffset);
		return 0;
	}

private:
	unsigned char m_pad00[0x10];
	RemoveGoalCell **m_map;
	Int m_extentLoX;
	Int m_extentLoY;
	Int m_extentHiX;
	Int m_extentHiY;
};

void Pathfinder::removeGoal(Object *obj)
{
	if (obj->isKindOf(2)) {
		return;
	}
	ObjectID objID = obj->getID();
	void *ai = obj->getAIUpdateInterface();
	if (ai == 0)
		return;
	ICoord2D goalCell = *obj->getPathfindGoalCell();

	Bool centerInCell;
	Int radius;
	ICoord2D newCell;
	getRadiusAndCenter(obj, radius, centerInCell);
	if (radius == 0)
		radius++;
	Int numCellsAbove = radius;
	if (centerInCell)
		numCellsAbove++;
	newCell.x = newCell.y = -1;
	if (newCell.x == goalCell.x && newCell.y == goalCell.y)
		return;
	ICoord2D cellNdx;
	obj->setPathfindGoalCell(newCell);
	Int i, j;
	if (goalCell.x >= 0 && goalCell.y >= 0) {
		for (i = goalCell.x - radius; i < goalCell.x + numCellsAbove; i++) {
			Int cellOffset = (goalCell.y - radius) << 4;
			for (j = goalCell.y - radius; j < goalCell.y + numCellsAbove; j++) {
				RemoveGoalCell *cell;
				if (i >= m_extentLoX && i <= m_extentHiX &&
					j >= m_extentLoY && j <= m_extentHiY)
					cell = (RemoveGoalCell *)((unsigned char *)m_map[i] + cellOffset);
				else
					cell = 0;
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
				if (obj->getDestinationLayer() != LAYER_GROUND) {
					cell = (RemoveGoalCell *)getCell(
						(PathfindLayerEnum)obj->getDestinationLayer(), i, j);
					if (cell && cell->getGoalUnit() == objID) {
						cellNdx.x = i;
						cellNdx.y = j;
						cell->setGoalUnit(0, cellNdx);
					}
				}
				cellOffset += 0x10;
			}
		}
	}
}

#pragma comment(linker, "/alternatename:?getFinalOverride@RemoveGoalTemplate@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?setGoalUnit@RemoveGoalCell@@QAEXIABUICoord2D@@@Z=?j_000140b0@@YAXXZ")
#pragma comment(linker, "/alternatename:?setGoalAircraft@RemoveGoalCell@@QAEXIABUICoord2D@@@Z=?j_0002eb2c@@YAXXZ")
