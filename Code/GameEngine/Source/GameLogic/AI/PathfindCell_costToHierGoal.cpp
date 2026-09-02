// cl: /DNDEBUG /MD /EHsc

// Retail 0x003F6CA0: PathfindCell::costToHierGoal. Same arithmetic as ZH
// AIPathfind.cpp without the DEBUG_CRASH null-info guard.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;

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

struct ICoord2D
{
	Int x;
	Int y;
};

class PathfindCell;

struct PathfindCellInfo
{
	ICoord2D m_pos;
};

class PathfindCell
{
public:
	UnsignedInt costToHierGoal(PathfindCell *goal);
	UnsignedShort getXIndex(void) const { return m_info->m_pos.x; }
	UnsignedShort getYIndex(void) const { return m_info->m_pos.y; }

private:
	PathfindCellInfo *m_info;
};

UnsignedInt PathfindCell::costToHierGoal(PathfindCell *goal)
{
	Int dx = m_info->m_pos.x - goal->getXIndex();
	Int dy = m_info->m_pos.y - goal->getYIndex();
	Int cost = REAL_TO_INT_FLOOR(10.0f * (Real)sqrt(dx * dx + dy * dy) + 0.5f);
	return cost;
}
