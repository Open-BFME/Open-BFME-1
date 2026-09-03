// cl: /DNDEBUG /MD
//
// Retail 0x003DEBB0: the per-cell obstacle test of a BFME pathfind walk,
// member-ified onto its payload struct the way the rest of this region is --
// __thiscall taking (from, to, to_x, to_y) with `ret 0x10`, returning 0 to
// keep walking and 1 to stop.  `from` is unused.
//
// The cascade is Zero Hour's checkDestination obstacle ladder (AIPathfind.cpp
// 4947-4990) lifted out into its own callback: a cell that is not an obstacle
// is passable, and an obstacle cell is passable if the obstacle belongs to the
// mover, to its partner, to either of their contained-by chains, or to the
// remembered cell -- ZH's `cell->isObstaclePresent(ignoreId)` continue-cases.
// What survives that ladder is looked up with GameLogic::findObjectByID and
// tested with two Thing::isKindOf ordinals, exactly ZH's
// findObjectByID/getRelationship tail rewritten against KindOf flags.
//
// The head is BFME-only bookkeeping: a wide layer window (0x11..0x40, well
// past the 2..15 wall range) sets a flag, bumps a counter and resets a run
// length, and a non-zero skip count consumes one cell and returns.
//
// Every callee here is already matched: isObstaclePresent 0x003D4C10,
// the guarded bitfield getter 0x003D4C50, bfme5WalkFirstValue 0x003D51A0,
// GameLogic::findObjectByID 0x0009A510, Thing::isKindOf 0x000A2CF0 and
// Object::getLayer.
//
// Codegen note: the two obstacle-owner ids have to be read as the raw m_id
// field, not through getID().  The accessor spelling compiles to the same
// semantics but makes MSVC 7.1 pick eax and edi for the load-and-push pairs
// where retail picks edx and ecx -- four bytes, and the only delta left.
//
// No /EHsc: retail registers no handler for the body.

typedef int Int;
typedef bool Bool;
typedef int ObjectID;

enum KindOfType { KINDOF_FIRST = 0 };

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	unsigned char m_prefix[0x20];	// +0x00 opaque
	ObjectID m_obstacleID;			// +0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Int getLayer( void ) const { return (m_packed >> 6) & 0x3f; }
	Int getRawType( void ) const { return m_packed & 0x7; }

	// ZH PathfindCell::getObstacleID: the side table is optional.
	ObjectID getObstacleID( void ) const
	{
		if (m_info)
			return m_info->m_obstacleID;
		return 0;
	}

	Bool isObstaclePresent( ObjectID objID );

	PathfindCellInfo *m_info;		// +0x00
	Int m_unused1;					// +0x04
	Int m_unused2;					// +0x08
	unsigned int m_packed;			// +0x0c
};

// The guarded bitfield getter already matched at 0x003D4C50; retail calls it
// with the cell in ecx.
class Rva003D4C50
{
public:
	Bool get( void );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf( KindOfType kind ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	ObjectID getID( void ) const { return m_id; }
	Int getLayer( void ) const;

	unsigned char m_prefix[0x74];		// +0x000 opaque
	ObjectID m_id;						// +0x074
	unsigned char m_mid[0x214 - 0x78];	// +0x078 opaque
	Object *m_containedBy;				// +0x214
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( Int id );
};

extern GameLogic *TheGameLogic;

// The walk-owner accessor already matched at 0x003D51A0; retail calls it
// cdecl with a single object argument.
class Bfme5WalkOwner;
Int bfme5WalkFirstValue( Bfme5WalkOwner *owner );

class ObstacleCellStruct
{
public:
	Int cellCallback( PathfindCell *from, PathfindCell *to, Int to_x, Int to_y );

	Object *m_obj;					// 0x00
	Object *m_other;				// 0x04
	PathfindCell *m_cell;			// 0x08
	Int m_skip;						// 0x0c
	Bool m_hitLayer;				// 0x10
	Int m_layerCount;				// 0x14
	Int m_runLength;				// 0x18
};

Int ObstacleCellStruct::cellCallback( PathfindCell *from, PathfindCell *to,
	Int to_x, Int to_y )
{
	Int layer = to->getLayer();
	if (layer >= 0x11 && layer <= 0x40)
	{
		m_hitLayer = true;
		m_layerCount++;
		m_runLength = 0;
	}
	else
	{
		m_runLength++;
	}

	if (m_skip > 0)
	{
		m_skip--;
		return 0;
	}

	if (to->getRawType() != 4)
		return 0;

	ObjectID objID = m_obj->getID();
	if (objID != 0)
	{
		PathfindCellInfo *info = to->m_info;
		if (info != 0 && info->m_obstacleID == objID)
			return 0;
	}

	Object *other = m_other;
	if (other != 0)
	{
		if (to->isObstaclePresent( other->m_id ))
			return 0;
		if (to->isObstaclePresent( bfme5WalkFirstValue( (Bfme5WalkOwner *)other ) ))
			return 0;
	}

	Object *obj = m_obj;
	Object *held = obj->m_containedBy;
	if (held != 0)
	{
		if (to->isObstaclePresent( held->m_id ))
			return 0;
		held = held->m_containedBy;
		if (held != 0)
		{
			if (to->isObstaclePresent( held->m_id ))
				return 0;
		}
	}

	if (to->isObstaclePresent( bfme5WalkFirstValue( (Bfme5WalkOwner *)obj ) ))
		return 0;

	if (((Rva003D4C50 *)to)->get())
		return 0;

	if (m_cell != 0)
	{
		if (to->isObstaclePresent( m_cell->getObstacleID() ))
			return 0;
	}

	Object *unit = TheGameLogic->findObjectByID( to->getObstacleID() );
	if (unit != 0)
	{
		if (unit->isKindOf( (KindOfType)0x3b ))
		{
			if (m_obj->getLayer() != 1)
				return 0;
			if (m_other != 0)
			{
				if (m_other->getLayer() != 1)
					return 0;
			}
		}

		if (unit->isKindOf( (KindOfType)0x87 ))
			return 0;
	}

	return 1;
}
