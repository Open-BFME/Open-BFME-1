// cl: /DNDEBUG /MD
//
// Retail 0x003DD7A0: Pathfinder::checkDestination, the Zero Hour twin at
// AIPathfind.cpp:4924 -- "checks to see if obj can occupy the pathfind cell at
// x,y".  The preamble is ZH lines 4927-4928 verbatim (numCellsAbove = iRadius,
// bumped by one when the object is centred in its cell), and the scan is ZH's
// nested i/j loop over cellX-iRadius .. cellX+numCellsAbove.
//
// BFME simplified the body ZH grew: ZH guards the id caching with
// `if (obj && obj->getAIUpdateInterface())` and carries an ignoreId plus a
// findObjectByID/getRelationship/canCrushOrSquish cascade; retail reads
// obj->getID() unconditionally and rejects on the far simpler ladder below.
// The aircraft-goal test consults the object rather than ZH's per-cell goal id.
//
// Pathfinder::getCell(layer,x,y) is inlined here -- bounds test, then the
// 2..15 layer window through the out-of-line PathfindLayer::getCell, then the
// ground m_map fallback -- while PathfindLayer::getCell stays a real call.
// Both are already matched in pathfind_getcell.cpp; the layouts below are that
// file's shim, restated TU-locally so this body needs no shared-header edit.
//
// No /EHsc: retail registers no handler for the body.

typedef int Int;
typedef bool Bool;
typedef unsigned int ObjectID;

const ObjectID INVALID_ID = 0;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

enum PathfindLayerEnum { PATHFIND_LAYER_GROUND = 0 };

class Object
{
public:
	// Inlined by retail straight to [obj+0x74]; the computer-controlled test
	// is the out-of-line body at 0x001BE410.
	ObjectID getID( void ) const { return m_id; }
	Bool bfmeIsComputerControlled( void ) const;

private:
	unsigned char m_prefix[0x74];	// +0x00 opaque
	ObjectID m_id;					// +0x74
};

class PathfindCell
{
public:
	// Packed dword at +0x0c: type:3@0, flags:3@3, layer:6@6, connect:6@12,
	// aircraft-goal:1@21.  Ordinals are retail's, not ZH's, so the type tests
	// are raw literals (see pathfind_getcell.cpp's note on getRawType).
	Int getRawType( void ) const { return m_packed & 0x7; }
	Int getFlags( void ) const { return m_packed & 0x38; }
	// The aircraft-goal bit is bit 21.  It has to be read through a byte
	// narrowing: MSVC 7.1 folds both `(m_packed >> 21) & 1` and the equivalent
	// one-bit bitfield into a single `test eax, 0x200000`, where retail keeps
	// the shifted-then-tested pair `shr eax, 0x15` / `test al, 1`.  Truncating
	// the shifted value to a byte first is what reproduces that pair.
	unsigned char getGoalAircraftByte( void ) const
		{ return (unsigned char)(m_packed >> 21); }
	ObjectID getGoalUnit( void ) const;

	void *m_info;					// +0x00
	Int m_unused1;					// +0x04
	Int m_unused2;					// +0x08
	unsigned int m_packed;			// +0x0c
};

class PathfindCellInfo
{
public:
	unsigned char m_prefix[0x14];	// +0x00 opaque
	ObjectID m_goalUnit;			// +0x14
};

inline ObjectID PathfindCell::getGoalUnit( void ) const
{
	PathfindCellInfo *info = (PathfindCellInfo *)m_info;
	if (info != 0)
		return info->m_goalUnit;
	return INVALID_ID;
}

class PathfindLayer
{
public:
	PathfindCell *getCell( Int x, Int y );

private:
	unsigned char m_body[0x44];		// stride 0x44
};

class Pathfinder
{
public:
	Bool checkDestination( const Object *obj, Int cellX, Int cellY,
		PathfindLayerEnum layer, Int iRadius, Bool centerInCell );
	PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y );

private:
	unsigned char m_prefix[0x10];		// +0x000 opaque
	PathfindCell **m_map;				// +0x010
	IRegion2D m_extent;					// +0x014
	unsigned char m_mid[0x85c - 0x24];	// +0x024 opaque
	PathfindLayer m_layers[16];			// +0x85c
};

inline PathfindCell *Pathfinder::getCell( PathfindLayerEnum layer, Int x, Int y )
{
	if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
		y >= m_extent.lo.y && y <= m_extent.hi.y)
	{
		if (layer > 1 && layer <= 15)
		{
			PathfindCell *cell = m_layers[layer].getCell( x, y );
			if (cell)
				return cell;
		}
		return &m_map[x][y];
	}
	return 0;
}

Bool Pathfinder::checkDestination( const Object *obj, Int cellX, Int cellY,
	PathfindLayerEnum layer, Int iRadius, Bool centerInCell )
{
	Int numCellsAbove = iRadius;
	if (centerInCell) numCellsAbove++;

	ObjectID objID = obj->getID();

	Int i, j;
	for (i = cellX - iRadius; i < cellX + numCellsAbove; i++)
	{
		for (j = cellY - iRadius; j < cellY + numCellsAbove; j++)
		{
			PathfindCell *cell = getCell( layer, i, j );
			if (cell == 0)
				return false;

			if (cell->getRawType() == 5)
				return false;

			if (cell->getGoalAircraftByte() & 1)
			{
				if (obj->bfmeIsComputerControlled())
					return false;
			}

			if (cell->getRawType() == 4)
				return false;

			if (cell->getFlags())
			{
				ObjectID goalUnitID = cell->getGoalUnit();
				if (goalUnitID != objID && goalUnitID != INVALID_ID)
					return false;
			}
		}
	}

	return true;
}
