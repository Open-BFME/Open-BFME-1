// cl: /DNDEBUG /MD
// Retail 0x003D9970 (711 B, ret 0x24): Pathfinder::processHierarchicalCell, the Zero Hour twin at AIPathfind.cpp:7346.
// Its only caller 0x003EEB90 calls it four times through ILT 0x00042D3E with ECX = Pathfinder and nine stack args.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short zoneStorageType;
typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo, hi;
};

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	Int layer;
};

class PathfindCell;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
struct PathfindCellInfo
{
	static void allocateCellInfos(void);

	ICoord2D m_pos;                         // +0x00
	PathfindCellInfo *m_nextOpen;           // +0x08
	PathfindCellInfo *m_prevOpen;           // +0x0c
	unsigned short m_totalCost;             // +0x10
	unsigned short m_costSoFar;             // +0x12
	unsigned int m_pathParent;              // +0x14
	unsigned int m_goalUnitID;              // +0x18
	unsigned int m_posUnitID;               // +0x1c
	unsigned int m_goalAircraftID;          // +0x20
	unsigned int m_flags;                   // +0x24
	PathfindCell *m_cell;                   // +0x28
	PathfindCellInfo *m_freeNext;           // +0x2c
	PathfindCellInfo **m_freePrevLink;      // +0x30
};

extern void *g_rva012F1094;
extern int g_bfmePathfindInfoIssued;

// Retail 0x003D7DB0 (PathfindCellInfoAcquire.cpp), visible so the caller knows it does not retain the position.
inline __declspec(noinline) PathfindCellInfo *__cdecl bfmeAcquirePathfindCellInfo(
	PathfindCellInfo **freeListHead, PathfindCell *pathfindCell, const ICoord2D *cellPosition)
{
	PathfindCellInfo *cellInfoRecord = *freeListHead;
	if (cellInfoRecord->m_freePrevLink != 0)
	{
		*cellInfoRecord->m_freePrevLink = cellInfoRecord->m_freeNext;
		if (cellInfoRecord->m_freeNext != 0)
			cellInfoRecord->m_freeNext->m_freePrevLink = cellInfoRecord->m_freePrevLink;
		cellInfoRecord->m_freePrevLink = 0;
		cellInfoRecord->m_freeNext = 0;
	}

	cellInfoRecord->m_cell = pathfindCell;
	cellInfoRecord->m_pos = *cellPosition;
	cellInfoRecord->m_nextOpen = 0;
	cellInfoRecord->m_prevOpen = 0;
	cellInfoRecord->m_totalCost = 0;
	cellInfoRecord->m_costSoFar = 0;
	cellInfoRecord->m_pathParent = 0;
	cellInfoRecord->m_goalUnitID = 0;
	cellInfoRecord->m_posUnitID = 0;
	cellInfoRecord->m_goalAircraftID = 0;
	cellInfoRecord->m_flags &= 0xffffffe0;
	++g_bfmePathfindInfoIssued;
	return cellInfoRecord;
}

// Byte-return views of the guarded getters matched at 0x003D49E0 and 0x003D4A00 (Y1GuardedBitfieldGetters.cpp):
// every call site here tests only AL, and the bodies are visible so the caller knows they write no memory.
struct Y1GuardedBits
{
	char m_lead[0x24];
	unsigned int m_bits;
};

class Rva003D49E0
{
public:
	__declspec(noinline) Bool get()
	{
		if (m_payload)
			return (m_payload->m_bits >> 3) & 1;
		else
			return 0;
	}

	Y1GuardedBits *m_payload;
};

class Rva003D4A00
{
public:
	__declspec(noinline) Bool get()
	{
		if (m_payload)
			return (m_payload->m_bits >> 4) & 1;
		else
			return 0;
	}

	Y1GuardedBits *m_payload;
};

class Rva003F69C0Object
{
public:
	void set(int *source, int value);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	UnsignedInt costToHierGoal(PathfindCell *goal);
	void rva003F6C30(PathfindCellInfo **head);

	__forceinline void allocateInfo(const ICoord2D &pos)
	{
		if (m_info == 0)
		{
			if (g_rva012F1094 == 0)
				PathfindCellInfo::allocateCellInfos();
			m_info = bfmeAcquirePathfindCellInfo(reinterpret_cast<PathfindCellInfo **>(&g_rva012F1094), this, &pos);
		}
		else
		{
			m_info->m_prevOpen = 0;
		}
	}
	Bool getOpen() { return ((Rva003D49E0 *)this)->get(); }
	Bool getClosed() { return ((Rva003D4A00 *)this)->get(); }
	Bool getPinched() const { return ((m_bits >> 18) & 1) != 0; }
	void setParentCellHierarchical(PathfindCell *parent)
	{
		((Rva003F69C0Object *)this)->set((int *)parent, 0);
	}

	PathfindCellInfo *m_info;
	Int m_zone;
	Int m_unused08;
	UnsignedInt m_bits;
};

class PathfindZoneManager
{
public:
	zoneStorageType bfmeGetBlockZone(const PathfindMovementProfile &profile,
		Int cellX, Int cellY, PathfindCell **map) const;
	zoneStorageType getEffectiveZone(const PathfindMovementProfile &profile,
		zoneStorageType zone) const;
};

class Pathfinder
{
public:
	void rva003D6400(PathfindCell *cell);

protected:
	void processHierarchicalCell(const ICoord2D &scanCell, const ICoord2D &delta,
		PathfindCell *parentCell, PathfindCell *goalCell, zoneStorageType parentZone,
		zoneStorageType *examinedZones, Int &numExZones,
		const PathfindMovementProfile &profile, Int &cellCount);

	// ?getGroundCell@Pathfinder@@IAEPAVPathfindCell@@HH@Z absent-from-retail
	__forceinline PathfindCell *getGroundCell(Int x, Int y)
	{
		if (x < m_extent.lo.x || x > m_extent.hi.x ||
			y < m_extent.lo.y || y > m_extent.hi.y)
			return 0;
		return &m_map[x][y];
	}

	unsigned char m_opaque00[0x10];
	PathfindCell **m_map;					// +0x010
	IRegion2D m_extent;						// +0x014
	unsigned char m_pad024[0x838 - 0x24];
	PathfindCellInfo *m_closedList;			// +0x838
	unsigned char m_pad83c[0xc9c - 0x83c];
	PathfindZoneManager m_zoneManager;		// +0xC9C
};

void Pathfinder::processHierarchicalCell(const ICoord2D &scanCell, const ICoord2D &delta,
	PathfindCell *parentCell, PathfindCell *goalCell, zoneStorageType parentZone,
	zoneStorageType *examinedZones, Int &numExZones,
	const PathfindMovementProfile &profile, Int &cellCount)
{
	if (scanCell.x < m_extent.lo.x || scanCell.x > m_extent.hi.x ||
		scanCell.y < m_extent.lo.y || scanCell.y > m_extent.hi.y)
		return;

	if (parentZone == m_zoneManager.bfmeGetBlockZone(profile, scanCell.x, scanCell.y, m_map))
	{
		PathfindCell *newCell = getGroundCell(scanCell.x, scanCell.y);
		if (newCell->getOpen() || newCell->getClosed())
			return;

		ICoord2D adjacentCell = scanCell;
		adjacentCell.x += delta.x;
		adjacentCell.y += delta.y;
		if (adjacentCell.x < m_extent.lo.x || adjacentCell.x > m_extent.hi.x ||
			adjacentCell.y < m_extent.lo.y || adjacentCell.y > m_extent.hi.y)
			return;

		PathfindCell *adjNewCell = getGroundCell(adjacentCell.x, adjacentCell.y);
		if (adjNewCell->getOpen() || adjNewCell->getClosed())
			return;

		zoneStorageType parentGlobalZone = m_zoneManager.getEffectiveZone(profile, parentZone);
		zoneStorageType newZone = m_zoneManager.bfmeGetBlockZone(profile,
			adjacentCell.x, adjacentCell.y, m_map);
		zoneStorageType newGlobalZone = m_zoneManager.getEffectiveZone(profile, newZone);
		if (newGlobalZone != parentGlobalZone)
			return;

		Int j;
		Bool found = false;
		for (j = 0; j < numExZones; j++)
		{
			if (examinedZones[j] == newZone)
			{
				found = true;
				break;
			}
		}

		newCell->allocateInfo(scanCell);
		if (!newCell->getClosed() && !newCell->getOpen())
			newCell->rva003F6C30(&m_closedList);

		adjNewCell->allocateInfo(adjacentCell);
		cellCount++;
		Int curCost = adjNewCell->costToHierGoal(parentCell);
		Int remCost = adjNewCell->costToHierGoal(goalCell);
		if (adjNewCell->getPinched() || newCell->getPinched())
		{
			curCost += 20;
		}
		else
		{
			examinedZones[numExZones] = newZone;
			numExZones++;
		}

		if (found)
		{
			adjNewCell->rva003F6C30(&m_closedList);
			return;
		}

		adjNewCell->m_info->m_costSoFar = parentCell->m_info->m_costSoFar + curCost;
		adjNewCell->m_info->m_totalCost = adjNewCell->m_info->m_costSoFar + remCost;
		adjNewCell->setParentCellHierarchical(parentCell);
		rva003D6400(adjNewCell);
	}
}

