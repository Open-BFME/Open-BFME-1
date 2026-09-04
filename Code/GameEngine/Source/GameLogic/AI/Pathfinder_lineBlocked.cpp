// cl: /DNDEBUG /MD
//
// Retail 0x003EE850: construct the 3-arg pathfind payload at 0x003DB640,
// convert both world endpoints to cells, iterate, and return whether the
// walk reported a hit.

typedef int Int;
typedef int Bool;
typedef unsigned int size_t;

inline void *operator new(size_t, void *p)
{
	return p;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class Pathfinder;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);
	BfmeOverridable *getFinalOverride(void)
	{
		if (m_override == 0) return this;
		return m_override->friend_getFinalOverride();
	}
	Int m_unreconstructed_00;
	BfmeOverridable *m_override;
	unsigned char m_unreconstructed_08[0x444 - 0x08];
	Int m_level;
	unsigned char m_unreconstructed_448[0x4cc - 0x448];
	unsigned char m_flag4CC;
};

class Object
{
public:
	BfmeOverridable *getTemplate(void) { return m_template; }
	bool bfmeIsComputerControlled(void) const;
	Int m_unreconstructed_00;
	BfmeOverridable *m_template;
};

struct BfmeMoveQuery
{
	Int m_zone;
	unsigned char m_isPlayerOwned;
	unsigned char m_isComputerControlled;
	unsigned char m_padding06[2];
	Int m_level;

	void setLevel(Int level) volatile { m_level = level; }
};

class Rva003DB640Info
{
public:
	Rva003DB640Info(Pathfinder *pathfinder, Object *obj, Int value);

	Pathfinder * volatile m_pathfinder;
	Object *m_obj;
	ICoord2D m_cell;
	Int m_layer;
	Int m_radius;
	unsigned char m_centerInCell;
	unsigned char m_considerTransient;
	unsigned char m_padding1a[2];
	Int m_acceptableSurfaces;								// retail this+0x1c
	Int m_ignoredObstacleID;								// retail this+0x20
	BfmeMoveQuery m_working;								// retail this+0x24
	Int m_allyFixedCount;
	unsigned char m_enemyFixed;
	unsigned char m_allyMoving;
	unsigned char m_allyGoal;
	unsigned char m_padding37;
	Int m_unreconstructed_38;
	volatile BfmeMoveQuery m_query;
	Int m_unreconstructed_48;
	Int m_unreconstructed_4c;
};

Rva003DB640Info::Rva003DB640Info(Pathfinder *pathfinder, Object *obj, Int value)
{
	m_pathfinder = pathfinder;
	m_obj = obj;
	m_cell.x = 0;
	m_cell.y = 0;
	m_layer = 0;
	m_radius = 0;
	m_centerInCell = 0;
	m_considerTransient = 0;
	m_acceptableSurfaces = 0;
	m_ignoredObstacleID = 0;
	m_working.m_zone = 0;
	m_working.m_isPlayerOwned = 0;
	m_working.m_isComputerControlled = 0;
	m_working.m_level = -1;
	m_allyFixedCount = 0;
	m_allyMoving = 0;
	m_allyGoal = 0;
	m_enemyFixed = 0;
	m_unreconstructed_38 = 0;

	BfmeOverridable *t1 = obj->getTemplate();
	Int level = (t1 == 0 ? t1 : t1->getFinalOverride())->m_level;

	BfmeOverridable *t2 = obj->getTemplate();
	unsigned char owned = (t2 == 0 ? t2 : t2->getFinalOverride())->m_flag4CC;

	unsigned char computer = obj->bfmeIsComputerControlled();

	m_query.m_zone = value;
	m_query.m_isComputerControlled = computer;
	m_query.m_isPlayerOwned = (owned == 0);
	m_query.setLevel(level - 1);
	m_unreconstructed_48 = 0;
	m_unreconstructed_4c = 0;
	m_working = *(const BfmeMoveQuery *)&m_query;
	m_considerTransient = 0;
	m_ignoredObstacleID = 0;
	m_radius = 0;
	m_acceptableSurfaces = 0xc;
	m_centerInCell = 1;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003DB640Info *info);
	Bool lineBlocked(Object *obj, Int value, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end);
};

// ?lineBlocked@Pathfinder@@QAEHPAVObject@@HW4PathfindLayerEnum@@PBUCoord3D@@2@Z
Bool Pathfinder::lineBlocked(Object *obj, Int value, PathfindLayerEnum layer,
	const Coord3D *startWorld, const Coord3D *endWorld)
{
	ICoord2D end;
	ICoord2D start;
	unsigned char storage[0x50];
	Rva003DB640Info *payload = new (storage) Rva003DB640Info(this, obj, value);
	worldToCell(startWorld, &start);
	worldToCell(endWorld, &end);
	return iterateCellsAlongLine(start, end, layer, payload) != 0;
}
