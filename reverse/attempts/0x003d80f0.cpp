// ?newMap@Pathfinder@@QAEXXZ
// partial score=0.74 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/terrainlogic /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
typedef int Int;
typedef float Real;
typedef bool Bool;

__forceinline long fast_float2long_round(float value)
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

struct Coord3D
{
	Real x, y, z;
};

struct Region3D
{
	Coord3D lo, hi;
};

struct ICoord2D
{
	Int x, y;
};

struct IRegion2D
{
	ICoord2D lo, hi;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_WALL = 15,
	LAYER_LAST = 15
};

class Waypoint;
class Object;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void getMaximumPathfindExtent(Region3D *extent);
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual Waypoint *getFirstWaypoint();
	PathfindLayerEnum getLayerForDestination(Object *object, const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

class Object
{
public:
	Object *getNextObject(void) const { return m_next; }
	unsigned char m_unreconstructed_00[0x88];
	Object *m_next;
};

class GameLogic
{
public:
	Object *getFirstObject(void);
};

extern GameLogic *TheGameLogic;
extern "C" Real g_bfmeScaleBK;
extern "C" __declspec(dllimport) double __cdecl BfmeFloorER(double value);

struct BfmeWaypointView
{
	unsigned char m_unreconstructed_00[0x0c];
	Coord3D m_location;
	unsigned char m_unreconstructed_18[4];
	BfmeWaypointView *m_next;
	unsigned char m_unreconstructed_20[0x28];
	Bool m_byte48;
	unsigned char m_unreconstructed_49[0x17];
	Int m_dword60;
};

class PathfindCell
{
public:
	PathfindCell();
	~PathfindCell();
	unsigned char m_unreconstructed_00[0x10];
};

typedef PathfindCell *PathfindCellP;

class PathfindLayer
{
public:
	Bool isUsed(void);
	void bfmeAllocateCells(const IRegion2D *extent);
	PathfindCell *getCell(Int x, Int y);
	unsigned char m_unreconstructed_00[0x44];
};

class PathfindZoneManager
{
public:
	void allocateBlocks(const IRegion2D &extent);
};

class BfmeOwnerETD;
class BfmeCellETD
{
public:
	void bfmeSetOwnerETD(BfmeOwnerETD *owner);
};

class Pathfinder
{
public:
	void newMap(void);
	Bool worldToCell(const Coord3D *position, ICoord2D *cell);
	void classifyMap(void);
	void updateAt003FA5B0(Object *object, int add, int flags);

	void *m_vtable;
	unsigned char m_unreconstructed_04[4];
	Bool m_isMapReady;
	unsigned char m_unreconstructed_09[3];
	PathfindCell *m_blockOfMapCells;
	PathfindCellP *m_map;
	IRegion2D m_extent;
	unsigned char m_unreconstructed_24[0x838];
	PathfindLayer m_layers[16];
	PathfindZoneManager m_zoneManager;
};

void Pathfinder::newMap(void)
{
	Region3D terrainExtent;
	TheTerrainLogic->getMaximumPathfindExtent(&terrainExtent);
	IRegion2D bounds;
	bounds.lo.x = fast_float2long_round((Real)BfmeFloorER((double)(*(volatile Real *)&terrainExtent.lo.x * g_bfmeScaleBK)));
	bounds.hi.x = fast_float2long_round((Real)BfmeFloorER((double)(*(volatile Real *)&terrainExtent.hi.x * g_bfmeScaleBK)));
	bounds.lo.y = fast_float2long_round((Real)BfmeFloorER((double)(*(volatile Real *)&terrainExtent.lo.y * g_bfmeScaleBK)));
	bounds.hi.y = fast_float2long_round((Real)BfmeFloorER((double)(*(volatile Real *)&terrainExtent.hi.y * g_bfmeScaleBK)));
	bounds.hi.x--;
	bounds.hi.y--;
	Bool dataAllocated = false;
	if (m_extent.hi.x == bounds.hi.x && m_extent.hi.y == bounds.hi.y) {
		if (m_blockOfMapCells != 0 && m_map != 0) {
			dataAllocated = true;
		}
	}
	if (!dataAllocated) {
		m_extent = bounds;
		m_zoneManager.allocateBlocks(m_extent);
		m_blockOfMapCells = new PathfindCell[(bounds.hi.x + 1) * (bounds.hi.y + 1)];
		m_map = new PathfindCellP[bounds.hi.x + 1];
		Int i;
		for (i = 0; i <= bounds.hi.x; ++i) {
			m_map[i] = &m_blockOfMapCells[i * (bounds.hi.y + 1)];
		}
		for (i = 0; i < 15; ++i) {
			if (m_layers[i].isUsed()) {
				m_layers[i].bfmeAllocateCells(&m_extent);
			}
		}
		BfmeWaypointView *waypoint = (BfmeWaypointView *)TheTerrainLogic->getFirstWaypoint();
		for (; waypoint != 0; waypoint = waypoint->m_next) {
			if (!waypoint->m_byte48)
				continue;
			Int kind = waypoint->m_dword60;
			if (kind != 1 && kind != 2 && kind != 3 && kind != 4)
				continue;
			PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, &waypoint->m_location);
			ICoord2D cellPosition;
			if (worldToCell(&waypoint->m_location, &cellPosition))
				continue;
			if (cellPosition.x < m_extent.lo.x)
				continue;
			if (cellPosition.x > m_extent.hi.x)
				continue;
			if (cellPosition.y < m_extent.lo.y)
				continue;
			if (cellPosition.y > m_extent.hi.y)
				continue;
			PathfindCell *cell;
			if (layer > LAYER_GROUND && layer < LAYER_LAST) {
				cell = m_layers[layer].getCell(cellPosition.x, cellPosition.y);
			} else {
				cell = &m_map[cellPosition.x][cellPosition.y];
			}
			if (cell != 0) {
				((BfmeCellETD *)cell)->bfmeSetOwnerETD((BfmeOwnerETD *)waypoint);
			}
		}
	}
	classifyMap();
	for (Object *object = TheGameLogic->getFirstObject(); object != 0; object = object->getNextObject()) {
		updateAt003FA5B0(object, 1, 0);
	}
	m_isMapReady = true;
}
