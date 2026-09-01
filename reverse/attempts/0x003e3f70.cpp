// ?removePos@Pathfinder@@QAEXPAVObject@@@Z
// partial score=0.72 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc /Oy-
// BFME Pathfinder::removePos uses the BFME Object and PathfindCell layouts.
// Keep those views local: the larger AIPathfind.cpp TU still uses the ZH
// headers for its unrelated bodies.

typedef int Int;
typedef int ObjectID;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 1
};

class Object
{
public:
	Int getLayer() const;
};

class BfmeLocomotorTemplate
{
public:
	BfmeLocomotorTemplate *getFinalOverride();
};

struct BFMEThingTemplateLayout
{
	void *m_vtable;
	void *m_nextOverride;
	char m_padding08[0xc0];
	unsigned char m_kindOf;
};

struct BFMEObjectLayout
{
	char m_padding00[4];
	BFMEThingTemplateLayout *m_template;
	char m_padding08[0x6c];
	ObjectID m_id;
	char m_padding78[0x2c];
	Int m_currentX;
	Int m_currentY;
	char m_paddingac[0x158];
	void *m_ai;
};

struct BFMEPathfinderLayout
{
	char m_padding00[8];
	unsigned char m_flags;
};

struct BFMEPathfindCellInfo
{
	char m_padding00[0x1c];
	ObjectID m_goalUnitID;
	ObjectID m_posUnitID;
};

class PathfindCell
{
public:
	void releaseInfo();

	BFMEPathfindCellInfo *m_info;
	char m_padding04[2];
	unsigned char m_flags;
};

class Pathfinder
{
public:
	void bfmeQuery(Object *object, Int *radius, Int *center);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	void removePos(Object *object);
};

void Pathfinder::removePos(Object *object)
{
	BFMEObjectLayout *objectLayout = reinterpret_cast<BFMEObjectLayout *>(object);
	BFMEThingTemplateLayout *thingTemplate = objectLayout->m_template;
	if (thingTemplate && thingTemplate->m_nextOverride) {
		BfmeLocomotorTemplate *finalOverride =
			reinterpret_cast<BfmeLocomotorTemplate *>(thingTemplate->m_nextOverride)->getFinalOverride();
		thingTemplate = reinterpret_cast<BFMEThingTemplateLayout *>(finalOverride);
	}
	if ((thingTemplate->m_kindOf & 4) != 0) {
		return;
	}
	BFMEPathfinderLayout *pathfinderLayout = reinterpret_cast<BFMEPathfinderLayout *>(this);
	if (pathfinderLayout->m_flags == 0) {
		return;
	}
	if (objectLayout->m_ai == 0) {
		return;
	}

	__int64 currentCellStorage = *reinterpret_cast<__int64 *>(&objectLayout->m_currentX);
	ICoord2D *currentCell = reinterpret_cast<ICoord2D *>(&currentCellStorage);
	Int radius;
	Bool center;
	volatile double alignmentProbe = 0.0;
	bfmeQuery(object, &radius, reinterpret_cast<Int *>(&center));
	Int numCellsAbove = radius;
	if (center) {
		++numCellsAbove;
	}
	PathfindLayerEnum layer = static_cast<PathfindLayerEnum>(object->getLayer());
	ICoord2D newCell;
	newCell.x = newCell.y = -1;
	objectLayout->m_currentX = newCell.x;
	objectLayout->m_currentY = newCell.y;
	if (currentCell->x < 0 || currentCell->y < 0) {
		return;
	}

	ICoord2D cellNdx;
	for (Int i = currentCell->x - radius; i < currentCell->x + numCellsAbove; ++i) {
		for (Int j = currentCell->y - radius; j < currentCell->y + numCellsAbove; ++j) {
			cellNdx.x = i;
			cellNdx.y = j;
			PathfindCell *cell = getCell(layer, cellNdx.x, cellNdx.y);
			if (cell) {
				BFMEPathfindCellInfo *info = cell->m_info;
				if (info && info->m_posUnitID == objectLayout->m_id) {
					info->m_posUnitID = -1;
					if (info->m_goalUnitID == -1) {
						cell->m_flags &= 0x0f;
						cell->releaseInfo();
					} else {
						cell->m_flags = (cell->m_flags & 0x0f) | 0x10;
					}
				}
			}
			if (layer != PATHFIND_LAYER_GROUND) {
				cell = getCell(PATHFIND_LAYER_GROUND, cellNdx.x, cellNdx.y);
				if (cell) {
					BFMEPathfindCellInfo *info = cell->m_info;
					if (info && info->m_posUnitID == objectLayout->m_id) {
						info->m_posUnitID = -1;
						if (info->m_goalUnitID == -1) {
							cell->m_flags &= 0x0f;
							cell->releaseInfo();
						} else {
							cell->m_flags = (cell->m_flags & 0x0f) | 0x10;
						}
					}
				}
			}
		}
	}
}
