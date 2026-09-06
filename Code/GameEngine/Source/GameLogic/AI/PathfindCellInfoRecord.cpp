// cl: /DNDEBUG /MD /EHsc
// readable body of ?costToHierGoal@PathfindCell@@QAEIPAV1@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// readable body of ?startPathfind@PathfindCell@@QAE_NPAV1@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
//
// The two PathfindCell bodies that work through its info record:
// startPathfind (retail 0x003F6940) takes the record off the free list and
// resets it for a search, costToHierGoal (retail 0x003F6CA0) reads the grid
// position out of it for the hierarchical heuristic. They sat in two files
// that described the same record incompatibly, and putting the two
// descriptions in one struct is what shows why.
//
// The first two words are the cell's grid position once the record is in use
// and a free-list link while it is not: startPathfind stores a
// PathfindCellInfo* into +0x00, and costToHierGoal reads that same word as the
// x index. Neither file could show that on its own -- one called +0x00 an int
// and the other the x of an ICoord2D -- so the overlap is spelled out here as
// a union rather than picked between.
//
// costToHierGoal is ZH's arithmetic without the DEBUG_CRASH null-info guard.
// startPathfind's goalCell argument is unused (there is no costToGoal call);
// the function still returns true.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" double __cdecl sqrt(double);

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

class PathfindCell;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
struct PathfindCellInfo
{
	// In use: the cell's grid position. On the free list: the back link
	// startPathfind writes before it clears the record.
	union
	{
		ICoord2D m_pos;					// +0x00
		Int m_freeListBack;				// +0x00
	};
	PathfindCellInfo *m_pathParent;				// +0x08
	PathfindCellInfo *m_prevOpen;				// +0x0C
	UnsignedShort m_totalCost;				// +0x10
	UnsignedShort m_costSoFar;				// +0x12
	char m_mid[0x10];
	UnsignedInt m_flags;					// +0x24
	PathfindCell *m_cell;					// +0x28
	PathfindCellInfo *m_prev;				// +0x2C
	PathfindCellInfo *m_next;				// +0x30
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Bool startPathfind(PathfindCell *goalCell);
	UnsignedInt costToHierGoal(PathfindCell *goal);

	UnsignedShort getXIndex(void) const { return m_info->m_pos.x; }
	UnsignedShort getYIndex(void) const { return m_info->m_pos.y; }

private:
	PathfindCellInfo *m_info;
};

// ?startPathfind@PathfindCell@@QAE_NPAV1@@Z
Bool PathfindCell::startPathfind(PathfindCell *)
{
	PathfindCellInfo *owner = m_info;
	PathfindCellInfo *next = owner->m_next;
	if (next != 0)
	{
		next->m_freeListBack = (Int)owner->m_prev;
		PathfindCellInfo *previous = owner->m_prev;
		if (previous != 0)
			previous->m_next = owner->m_next;
		owner->m_next = 0;
		owner->m_prev = 0;
	}
	m_info->m_pathParent = 0;
	m_info->m_costSoFar = 0;
	m_info->m_totalCost = 0;
	m_info->m_flags &= ~8u;
	m_info->m_flags &= ~16u;
	return true;
}

// ?costToHierGoal@PathfindCell@@QAEIPAV1@@Z
UnsignedInt PathfindCell::costToHierGoal(PathfindCell *goal)
{
	Int dx = m_info->m_pos.x - goal->getXIndex();
	Int dy = m_info->m_pos.y - goal->getYIndex();
	Int cost = REAL_TO_INT_FLOOR(10.0f * (Real)sqrt(dx * dx + dy * dy) + 0.5f);
	return cost;
}
