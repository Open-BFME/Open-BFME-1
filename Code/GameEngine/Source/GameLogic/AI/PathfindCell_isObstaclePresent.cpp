// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Retail 0x003D4C10, 46 bytes through the int3 run at +0x2E: the Zero Hour
// inline PathfindCell::isObstaclePresent, reached through ILT 0x0004850E by
// ObstacleCellStruct::cellCallback (six sites) and Pathfinder::internalFindPath.
// The inner `m_info && ...` is materialised as a 32-bit 0/1 while the outer
// `return false` stays 8-bit, which is why retail keeps two false exits.

typedef bool Bool;
typedef int ObjectID;
#define INVALID_ID 0

struct PathfindCellInfo
{
	char m_unmodelled00[ 0x20 ];
	ObjectID m_obstacleID;
};

class PathfindCell
{
public:
	enum CellType { CELL_CLEAR, CELL_WATER, CELL_CLIFF, CELL_RUBBLE, CELL_OBSTACLE };
	CellType getType( void ) const { return (CellType)m_type; }
	Bool isObstaclePresent( ObjectID objID );

private:
	PathfindCellInfo *m_info;
	char m_unmodelled04[ 8 ];
	unsigned int m_type : 3;
};

Bool PathfindCell::isObstaclePresent( ObjectID objID )
{
	if (objID != INVALID_ID && (getType() == PathfindCell::CELL_OBSTACLE))
	{
		return (m_info && m_info->m_obstacleID == objID);
	}

	return false;
}
