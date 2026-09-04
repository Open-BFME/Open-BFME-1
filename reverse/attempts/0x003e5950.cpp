// ?linePassableCallback@LinePassableStruct@@QAEHPAVPathfindCell@@0HH@Z
// partial score=0.94 date=2026-09-04
// ?linePassableCallback@LinePassableStruct@@QAEHPAVPathfindCell@@0HH@Z
// cl: /DNDEBUG /MD

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x, y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Int getLayer() const { return (m_bits >> 6) & 0x3f; }
	Int getType() const { return m_bits & 7; }

	Int			m_head[3];
	UnsignedInt	m_bits;
};

enum
{
	LAYER_WALL_START = 2,
	LAYER_LAST = 15,
	CELL_CLEAR = 0
};

struct TCheckMovementInfo
{
	ICoord2D	cell;
	Int			layer;
	Int			m_rest[8];
	Bool		m_limited;
};

struct Rva003E0930Struct
{
	ICoord2D	cell;
};

struct Rva003D4F90Struct
{
	Int			m_parms[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool checkForMovementFrom( const Object *obj, TCheckMovementInfo *info,
		Rva003E0930Struct *query );
	Bool checkForMovement( const Object *obj, TCheckMovementInfo *info );
	Bool validMovementPosition( const Rva003D4F90Struct *parms,
		const PathfindCell *cell );
};

class LinePassableStruct
{
public:
	Int linePassableCallback( PathfindCell *from, PathfindCell *to,
		Int to_x, Int to_y );

	Pathfinder			*m_pathfinder;
	const Object		*m_obj;
	TCheckMovementInfo	m_info;
	Int					m_allyFixedCount;
	Rva003D4F90Struct	m_valid;
	Rva003E0930Struct	m_query;
};

Int LinePassableStruct::linePassableCallback( PathfindCell *from, PathfindCell *to,
	Int to_x, Int to_y )
{
	m_info.cell.x = to_x;
	m_info.cell.y = to_y;
	m_info.layer = to->getLayer();

	if (from) {
		if (!m_pathfinder->checkForMovementFrom( m_obj, &m_info, &m_query )) {
			return 1;
		}
	} else {
		if (m_pathfinder->checkForMovement( m_obj, &m_info )) {
			goto movement_checked;
		}
		return 1;
	}

movement_checked:
	if (m_allyFixedCount) {
		return 1;
	}

	m_query.cell.x = to_x;
	m_query.cell.y = to_y;

	if (from) {
		Int layer = to->getLayer();
		if (layer >= LAYER_WALL_START && layer <= LAYER_LAST &&
				from->getLayer() == layer && to->getType() == CELL_CLEAR) {
			return 0;
		}
	}

	return !m_pathfinder->validMovementPosition( &m_valid, to );
}
