// ?groundPathPassableCallback@GroundPathPassableStruct@@QAEHPAVPathfindCell@@0HH@Z
// partial score=0.94 date=2026-09-04
// cl: /DNDEBUG /MD
//
// Retail 0x003E5B80: BFME's member form of the sibling of ZH
// Pathfinder::linePassableCallback -- same shape as 0x003E5950 but with a
// skip-count guard, so it is the port of ZH's attackBlockedByObstacle-style
// "skipCount" callback fused with the line-passable query.
//
// No /EHsc: retail registers no handler for the body.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;

struct ICoord2D
{
	Int x, y;
};

class PathfindCell
{
public:
	Int getLayer() const { return (m_bits >> 6) & 0x3f; }
	Int getType() const { return m_bits & 7; }

	Int			m_head[3];		// 0x00
	UnsignedInt	m_bits;			// 0x0C
};

enum
{
	LAYER_WALL_START = 2,
	LAYER_LAST = 15,
	CELL_CLEAR = 0
};

struct TCheckMovementInfo
{
	ICoord2D	cell;			// +0x00
	Int			layer;			// +0x08
	Int			m_rest[8];		// +0x0C .. +0x2B
	Bool		m_limited;		// +0x2C  (0x34 in the owner)
};

struct Rva003E0930Struct
{
	ICoord2D	cell;			// +0x00
};

struct Rva003D4F90Struct
{
	Int			m_parms[3];
};

class Pathfinder
{
public:
	Bool checkForMovementFrom( const Object *obj, TCheckMovementInfo *info,
		Rva003E0930Struct *query );
	Bool checkForMovement( const Object *obj, TCheckMovementInfo *info );
	Bool validMovementPosition( const Rva003D4F90Struct *parms,
		const PathfindCell *cell );
};

class GroundPathPassableStruct
{
public:
	Int groundPathPassableCallback( PathfindCell *from, PathfindCell *to,
		Int to_x, Int to_y );

	Pathfinder			*m_pathfinder;		// 0x00
	const Object		*m_obj;				// 0x04
	TCheckMovementInfo	m_info;				// 0x08 (m_limited at 0x34)
	Int					m_allyFixedCount;	// 0x38
	Rva003E0930Struct	m_query;			// 0x3C
	Rva003D4F90Struct	m_valid;			// 0x44
	Int					m_hitCount;			// 0x50
};

Int GroundPathPassableStruct::groundPathPassableCallback( PathfindCell *from,
	PathfindCell *to, Int to_x, Int to_y )
{
	m_info.cell.x = to_x;
	m_info.cell.y = to_y;
	m_info.layer = to->getLayer();

	if (from) {
		if (!m_pathfinder->checkForMovementFrom( m_obj, &m_info, &m_query )) {
			return 1;	// bail out
		}
	} else {
		if (!m_pathfinder->checkForMovement( m_obj, &m_info )) {
			return 1;	// bail out
		}
	}

	if (m_allyFixedCount) {
		return 1;	// bail out
	}

	if (m_info.m_limited) {
		m_hitCount++;
		if (m_hitCount > 1) {
			return 1;	// bail out
		}
	}

	m_query.cell.x = to_x;
	m_query.cell.y = to_y;

	if (from) {
		Int layer = to->getLayer();
		if (layer >= LAYER_WALL_START && layer <= LAYER_LAST &&
				from->getLayer() == layer && to->getType() == CELL_CLEAR) {
			return 0;	// keep going
		}
	}

	return !m_pathfinder->validMovementPosition( &m_valid, to );
}
