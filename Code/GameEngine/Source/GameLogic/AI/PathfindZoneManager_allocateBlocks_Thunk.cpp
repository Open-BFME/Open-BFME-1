// cl: /DNDEBUG /MD /EHsc
// readable body of ?allocateBlocks@PathfindZoneManager@@QAEXABUIRegion2D@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

// BFME links both allocations through its array allocator; without the
// declaration MSVC 7.1 folds these array expressions onto scalar new.
void *operator new[](unsigned int size);

class PathfindZoneBlock
{
public:
	PathfindZoneBlock();
	~PathfindZoneBlock();

private:
	char m_retailLayout[0x228];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	void allocateBlocks(const IRegion2D &globalBounds);

private:
	void freeBlocks();

	// BFME added pathfinder state ahead of the ZH fields, so this TU models the
	// retail offsets without changing the shared ZH compatibility header.
	unsigned char m_stateEnabled;
	unsigned char m_secondaryStateEnabled;
	unsigned char m_statePadding[2];
	int m_currentZone;
	char m_pathfinderStorage[0x2361c];
	PathfindZoneBlock *m_blockOfZoneBlocks;
	PathfindZoneBlock **m_zoneBlocks;
	ICoord2D m_zoneBlockExtent;
};

typedef char ZoneBlockSizeMustMatchRetail[(sizeof(PathfindZoneBlock) == 0x228) ? 1 : -1];

void PathfindZoneManager::allocateBlocks(const IRegion2D &globalBounds)
{
	freeBlocks();

	m_stateEnabled = 1;
	m_secondaryStateEnabled = 1;
	m_currentZone = -1;

	const int zoneBlockSize = 16;
	m_zoneBlockExtent.x = (globalBounds.hi.x - globalBounds.lo.x + zoneBlockSize) / zoneBlockSize;
	m_zoneBlockExtent.y = (globalBounds.hi.y - globalBounds.lo.y + zoneBlockSize) / zoneBlockSize;

	m_blockOfZoneBlocks = new PathfindZoneBlock[m_zoneBlockExtent.x * m_zoneBlockExtent.y];
	m_zoneBlocks = new PathfindZoneBlock *[m_zoneBlockExtent.x];
	for (int i = 0; i < m_zoneBlockExtent.x; ++i)
		m_zoneBlocks[i] = &m_blockOfZoneBlocks[i * m_zoneBlockExtent.y];
}
