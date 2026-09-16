// ?removePos@Pathfinder@@QAEXPAVObject@@@Z
// partial score=0.82 date=2026-09-08
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
	char m_padding00[0x14];
	ObjectID m_goalUnitID;
	ObjectID m_posUnitID;
};

class PathfindCell
{
public:
	void setPosUnit(ObjectID unitID, const ICoord2D &pos);

	BFMEPathfindCellInfo *m_info;
	char m_padding04[8];
	unsigned int m_packed;
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

	Bool center;
	Int radius;
	Int currentY = objectLayout->m_currentY;
	Int currentX = objectLayout->m_currentX;
	bfmeQuery(object, &radius, reinterpret_cast<Int *>(&center));
	Int numCellsAbove = radius;
	if (center) {
		++numCellsAbove;
	}
	PathfindLayerEnum layer = static_cast<PathfindLayerEnum>(object->getLayer());
	objectLayout->m_currentX = -1;
	objectLayout->m_currentY = -1;
	if (currentX < 0 || currentY < 0) {
		return;
	}

	ICoord2D cellNdx;
	for (Int i = currentX - radius; i < currentX + numCellsAbove; ++i) {
		for (Int j = currentY - radius; j < currentY + numCellsAbove; ++j) {
			cellNdx.x = i;
			cellNdx.y = j;
			PathfindCell *cell = getCell(layer, cellNdx.x, cellNdx.y);
			if (cell) {
				BFMEPathfindCellInfo *info = cell->m_info;
				ObjectID posUnitID = info ? info->m_posUnitID : 0;
				if (posUnitID == objectLayout->m_id) {
					cell->setPosUnit(0, cellNdx);
				}
			}
			if (layer != PATHFIND_LAYER_GROUND && layer < 16) {
				cell = getCell(PATHFIND_LAYER_GROUND, cellNdx.x, cellNdx.y);
				if (cell) {
					BFMEPathfindCellInfo *info = cell->m_info;
					ObjectID posUnitID = info ? info->m_posUnitID : 0;
					if (posUnitID == objectLayout->m_id) {
						cell->setPosUnit(0, cellNdx);
					}
				}
			}
		}
	}
}
