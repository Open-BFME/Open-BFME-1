// cl: /DNDEBUG /MD
//
// Retail 0x003E0370: the one-cell movement/occupancy check used by the BFME
// Pathfinder walk.  The four arguments are the object being moved, the cell,
// the movement payload, and the last object id seen by the caller.

typedef int Int;
typedef int ObjectID;

enum KindOfType { KINDOF_FIRST = 0 };
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
enum CrushSquishTestType { TEST_CRUSH_ONLY = 0, TEST_SQUISH_ONLY = 1, TEST_CRUSH_OR_SQUISH = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOf( KindOfType kind ) const;

protected:
	char m_thingPad[0x74];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	bool bfmeIsComputerControlled( void ) const;
	Relationship getRelationship( const Object *that ) const;
	bool canCrushOrSquish( Object *other, CrushSquishTestType type ) const;

	ObjectID m_id;					// 0x74
	char m_pad78[0x204 - 0x78];
	void *m_ai;					// 0x204
};

// The BFME object lookup is the renamed 1011 helper used by the neighbouring
// landed Pathfinder bodies.  Its retail return type is BfmeX1011; the cell
// helper consumes the same pointer as an Object.
class BfmeX1011;
class BfmeLook1011
{
public:
	BfmeX1011 *bfmeFind1011( Int id );
};

extern BfmeLook1011 *g_bfmeLook1011;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	char m_pad00[0x18];
	ObjectID m_posUnit;				// 0x18
};

class PathfindCell
{
public:
	PathfindCellInfo *m_info;			// 0x00
	Int m_field04;
	Int m_field08;

	union
	{
		unsigned int m_word;			// 0x0C
		struct
		{
			unsigned int m_type : 3;
			unsigned int m_flags : 3;
			unsigned int m_zone : 6;
		};
	};
};

// Really TCheckMovementInfo in the ZH source; BFME's body has the same field
// offsets as the already reconstructed E05B0/E0930 movement helpers.
struct ICoord2D
{
	Int x;							// 0x00
	Int y;							// 0x04
	Int layer;						// 0x08
	Int radius;						// 0x0C
	bool centerInCell;				// 0x10
	bool considerTransient;				// 0x11
	char pad12[2];
	Int checkMask;					// 0x14
	ObjectID ignoreID;				// 0x18
	char blob1C[0x28 - 0x1c];		// 0x1C
	Int allyFixed;					// 0x28
	bool enemyFixed;					// 0x2C
	bool allyMoving;					// 0x2D
	bool allyGoal;					// 0x2E
	char pad2F[1];
	Int blockCount;					// 0x30
};

class Pathfinder
{
public:
	bool bfmeStepD4F90( void *state, PathfindCell *cell );
	bool bfmeStepE0370( Object *obj, PathfindCell *cell, ICoord2D *info, ObjectID *lastID );
};

bool Pathfinder::bfmeStepE0370( Object *obj, PathfindCell *cell, ICoord2D *info, ObjectID *lastID )
{
	if (cell->m_type == 5)
		info->blockCount++;

	if (((unsigned char)(cell->m_word >> 21) & 1) && obj->bfmeIsComputerControlled())
		info->blockCount++;

	if (info->checkMask & 8)
	{
		Int zone = cell->m_zone;
		Int layer = info->layer;
		if (info->layer != zone &&
			((info->layer == 1 && zone != 16) ||
			 (layer >= 17 && layer <= 64 && zone != 16)))
			info->blockCount++;
	}

	if (info->checkMask & 4)
	{
		if (!bfmeStepD4F90( &info->blob1C, cell ))
			info->blockCount++;
	}

	Int flags = cell->m_flags;
	if (flags == 0)
		return true;

	if (flags == 1 || flags == 4)
		info->allyGoal = true;

	ObjectID posUnit = cell->m_info ? cell->m_info->m_posUnit : 0;
	if (posUnit == obj->m_id)
		return true;
	if (posUnit == info->ignoreID)
		return true;
	if (posUnit == *lastID)
		return true;

	*lastID = posUnit;
	Object *unit = (Object *)g_bfmeLook1011->bfmeFind1011( posUnit );
	if (unit == 0)
		return true;

	bool check = false;
	bool isAlly;
	if (flags == 2 || flags == 4)
	{
		isAlly = (obj->getRelationship( unit ) == ALLIES);
		if (isAlly)
			info->allyMoving = true;
		if (info->considerTransient)
			check = true;
	}
	if (flags == 3)
	{
		check = true;
		isAlly = (obj->getRelationship( unit ) == ALLIES);
	}
	if (!check)
		return true;

	if (isAlly && obj->isKindOf( (KindOfType)0x73 ) && unit->isKindOf( (KindOfType)0x73 ))
		return true;
	if (obj->isKindOf( (KindOfType)0x7c ) && unit->isKindOf( (KindOfType)0x08 ))
		return true;

	if (isAlly)
	{
		if (unit->m_ai == 0)
			return false;
		if (info->checkMask & 2)
			return false;
		info->allyFixed = 1;
	}
	else
	{
		if (!obj->canCrushOrSquish( unit, TEST_CRUSH_OR_SQUISH ))
		{
			if (info->checkMask & 1)
				return false;
			info->enemyFixed = true;
		}
	}

	return true;
}
