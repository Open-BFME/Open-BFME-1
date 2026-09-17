// ?linePassableCallback@LinePassableStruct@@QAEHPAVPathfindCell@@0HH@Z
// cl: /DNDEBUG /MD
// Open-BFME: retail 0x003E5950. The callback answers whether the line of
// sight may pass from one pathfind cell to the next.
//
// Retail keeps two copies of the twelve-byte 'return 1' epilogue, and the
// third return-one site jumps back into the first copy. MSVC 7.1 cross-jumps
// identical tails into one. Two DIFFERENT barrier intrinsics, one per copy,
// keep both, and a third site takes the same intrinsic as the copy retail
// merges it into. Neither intrinsic emits an instruction or a relocation.

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

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
	// Address-derived names already pinned in reverse/symbols.csv at the
	// incremental-link thunks 0x00024299, 0x0004A980 and 0x0002B9E0.
	Bool bfmeStepE0930( Object *obj, ICoord2D *info, ICoord2D *query );
	Bool bfmeStepE05B0( Object *obj, ICoord2D *info );
	Bool bfmeStepD4F90( void *parms, PathfindCell *cell );
};

class LinePassableStruct
{
public:
	Int linePassableCallback( PathfindCell *from, PathfindCell *to,
		Int to_x, Int to_y );

	Pathfinder			*m_pathfinder;
	Object				*m_obj;
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
		if (!m_pathfinder->bfmeStepE0930( m_obj, &m_info.cell, &m_query.cell )) {
			_WriteBarrier();
			return 1;
		}
	} else {
		if (!m_pathfinder->bfmeStepE05B0( m_obj, &m_info.cell )) {
			_ReadWriteBarrier();
			return 1;
		}
	}

	if (m_allyFixedCount) {
		_WriteBarrier();
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

	return !m_pathfinder->bfmeStepD4F90( &m_valid, to );
}
