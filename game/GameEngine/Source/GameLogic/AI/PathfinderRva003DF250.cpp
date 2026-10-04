// cl: /DNDEBUG /MD
//
// Retail 0x003DF250 (648 bytes, ret 8): an address-named Pathfinder method.
// Its caller Pathfinder::findClosestPath (0x003F3460, through ILT 0x00033B7C)
// passes (obj, &goal) and tests the Bool result. No string, vtable slot or
// Zero Hour twin names the method, so the address token stays in its name.
//
// The body snaps *dest to the object's goal cell the way Zero Hour's
// Pathfinder::snapClosestGoalPosition (AIPathfind.cpp:5125) begins:
// getRadiusAndCenter, a half-cell bias on an off-centre copy, the
// TerrainLogic destination layer, worldToCell and adjustCoordToCell. It then
// scans the object's footprint with the loop of the matched
// Pathfinder::checkDestination (0x003DD7A0, PathfindCheckDestination.cpp).
// Its rejection ladder is longer: cell types 4..6, then pos-unit and
// goal-unit tests that check KindOf bits 0x7c, 0x08 and 0x6c, through
// GameLogic::findObjectByID. The KindOf ordinals are BFME's own, so they
// keep address-derived enumerator names.
//
// Retail keeps `center` in ebx across three calls (a dword load), and it packs
// the objID, row-offset and x-end temporaries onto the dead radius, center and
// cell.x slots. The compiler does both only when it can see that
// getRadiusAndCenter (0x003DEE30) and worldToCell (0x003D7EC0) keep neither
// reference. Retail's AIPathfind.cpp defines all three functions, so those two
// matched bodies are restated out of line below. The worldToCell copy follows
// the precedent of 0x003D84A0 and 0x003D8530.
//
// The layouts restate PathfindCheckDestination.cpp and
// PathfindGetRadiusAndCenterE30.cpp TU-locally. The PathfindCellInfo ids
// follow the matched PathfindCell::setGoalUnit and setPosUnit bodies: goal at
// +0x14, pos at +0x18.
//
// No /EHsc: retail registers no handler for the body.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

const ObjectID INVALID_ID = 0;

#define PATHFIND_CELL_SIZE 10
#define PATHFIND_CELL_SIZE_F 10.0f

struct Coord3D { Real x, y, z; };
struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

enum PathfindLayerEnum { PATHFIND_LAYER_GROUND = 0 };

enum KindOfType
{
	KINDOF_RVA003DF250_08 = 0x08,
	KINDOF_RVA003DF250_6C = 0x6c,
	KINDOF_RVA003DF250_7C = 0x7c
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf( KindOfType t ) const;
};

extern "C" __declspec(dllimport) double __cdecl floor( double );

__forceinline long fast_float2long_round( float value )
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

extern const float g_bfmeDirectionWeight1285;
extern const float g_Rva010977E0;
extern const float g_rva01075350;
extern float g_Rva01095F98;

// Template view read by getRadiusAndCenter (PathfindGetRadiusAndCenterE30.cpp).
class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride( void );

	BfmeOverridable *getFinalOverride( void )
	{
		if (m_override == 0) return this;
		return m_override->friend_getFinalOverride();
	}

	Int m_unknown00;
	BfmeOverridable *m_override;
	unsigned char m_pad08[0xc8 - 0x08];
	Int m_flagsC8;
	unsigned char m_padCC[0xd4 - 0xcc];
	Int m_flagsD4;
	unsigned char m_padD8[0x408 - 0xd8];
	Real m_level;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	ObjectID getID( void ) const { return m_id; }
	Bool bfmeIsComputerControlled( void ) const;
	BfmeOverridable *getTemplate( void ) const { return m_template; }

	Int m_unknown00;						// +0x00
	BfmeOverridable *m_template;			// +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;							// +0x74
	unsigned char m_pad78[0xbc - 0x78];
	Real m_boundingCircleRadius;			// +0xbc
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( Int id );
};

extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination( Object *object, const Coord3D *pos );
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	unsigned char m_prefix[0x14];	// +0x00 opaque
	ObjectID m_goalUnitID;			// +0x14
	ObjectID m_posUnitID;			// +0x18
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Int getRawType( void ) const { return m_packed & 0x7; }
	Int getFlags( void ) const { return m_packed & 0x38; }
	unsigned char getGoalAircraftByte( void ) const
		{ return (unsigned char)(m_packed >> 21); }

	PathfindCellInfo *m_info;		// +0x00
	Int m_unused1;					// +0x04
	Int m_unused2;					// +0x08
	unsigned int m_packed;			// +0x0c
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	unsigned char m_body[0x44];		// stride 0x44
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool Rva003DF250( Object *obj, Coord3D *dest );
	Bool worldToCell( const Coord3D *pos, ICoord2D *cell );
	PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY );

protected:
	void getRadiusAndCenter( const Object *obj, Int &radius, Bool &centerInCell );
	void adjustCoordToCell( Int cellX, Int cellY, Bool centerInCell,
		Coord3D &pos, PathfindLayerEnum layer );

private:
	unsigned char m_prefix[0x10];		// +0x000 opaque
	PathfindCell **m_map;				// +0x010
	IRegion2D m_extent;					// +0x014
	unsigned char m_mid[0x85c - 0x24];	// +0x024 opaque
	PathfindLayer m_layers[16];			// +0x85c
};

inline PathfindCell *Pathfinder::getCell( PathfindLayerEnum layer, Int cellX, Int cellY )
{
	if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
		cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
	{
		if (layer > 1 && layer <= 15)
		{
			PathfindCell *cell = m_layers[layer].getCell( cellX, cellY );
			if (cell)
				return cell;
		}
		return &m_map[cellX][cellY];
	}
	return 0;
}

// Retail 0x003DEE30, matched in PathfindGetRadiusAndCenterE30.cpp; defined
// out of line here as well, as in retail's AIPathfind.cpp, so the compiler
// sees that it keeps neither reference.
inline __declspec(noinline) void Pathfinder::getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell )
{
	Real diameter;
	Int maxRadius = 2;
	BfmeOverridable *t1 = object->getTemplate();
	if ((t1 == 0 ? t1 : t1->getFinalOverride())->m_flagsC8 & 0x400) {
		maxRadius = 4;
	} else {
		BfmeOverridable *t2 = object->getTemplate();
		if ((t2 == 0 ? t2 : t2->getFinalOverride())->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = object->m_boundingCircleRadius * 2.0f;
	if (diameter > g_bfmeDirectionWeight1285 && diameter < g_Rva010977E0) {
		diameter = 20.0f;
	}

	if ((object->getTemplate() == 0 ? object->getTemplate() :
		object->getTemplate()->getFinalOverride())->m_level > g_rva01075350) {
		diameter = (object->getTemplate() == 0 ? object->getTemplate() :
		object->getTemplate()->getFinalOverride())->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_Rva01095F98 );
	centerInCell = false;
	if (radius == 0) radius++;
	if (radius & 1) {
		centerInCell = true;
	}
	radius /= 2;
	if (radius > maxRadius) {
		radius = maxRadius;
		centerInCell = true;
	}
}

// Retail 0x003D7EC0, matched in pathfind_getcell.cpp; visible here for the
// same reason.
// One ANY-COMDAT copy per TU: every emission of worldToCell (retail 0x003D7EC0)
// is this same inline, never-inlined body, so link.exe may keep any of them.
inline __declspec(noinline) Bool Pathfinder::worldToCell( const Coord3D *worldPosition, ICoord2D *cellIndex )
{
	cellIndex->x = REAL_TO_INT_FLOOR(worldPosition->x/PATHFIND_CELL_SIZE);
	cellIndex->y = REAL_TO_INT_FLOOR(worldPosition->y/PATHFIND_CELL_SIZE);
	Bool overflow = false;
	if (cellIndex->x < m_extent.lo.x) {overflow = true; cellIndex->x = m_extent.lo.x;}
	if (cellIndex->y < m_extent.lo.y) {overflow = true; cellIndex->y = m_extent.lo.y;}
	if (cellIndex->x > m_extent.hi.x) {overflow = true; cellIndex->x = m_extent.hi.x;}
	if (cellIndex->y > m_extent.hi.y) {overflow = true; cellIndex->y = m_extent.hi.y;}
	return overflow;
}

Bool Pathfinder::Rva003DF250( Object *obj, Coord3D *dest )
{
	Int iRadius;
	Bool center;
	getRadiusAndCenter( obj, iRadius, center );
	Coord3D adjustDest;
	adjustDest.x = dest->x;
	adjustDest.y = dest->y;
	adjustDest.z = dest->z;
	if (!center) {
		adjustDest.x += PATHFIND_CELL_SIZE_F/2;
		adjustDest.y += PATHFIND_CELL_SIZE_F/2;
	}
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination( obj, dest );
	ICoord2D cell;
	worldToCell( &adjustDest, &cell );
	Int cellX = cell.x;
	Int cellY = cell.y;
	adjustCoordToCell( cellX, cellY, center, *dest, layer );

	Int numCellsAbove = iRadius;
	if (center) numCellsAbove++;

	ObjectID objID = obj->getID();

	Int i, j;
	for (i = cellX - iRadius; i < cellX + numCellsAbove; i++)
	{
		for (j = cellY - iRadius; j < cellY + numCellsAbove; j++)
		{
			PathfindCell *theCell = getCell( layer, i, j );
			if (theCell == 0)
				return false;

			if (theCell->getRawType() == 5)
				return false;

			if (theCell->getGoalAircraftByte() & 1)
			{
				if (obj->bfmeIsComputerControlled())
					return false;
			}

			Int type = theCell->getRawType();
			if (type == 4 || type == 5 || type == 6)
				return false;

			if (theCell->getFlags())
			{
				PathfindCellInfo *info = theCell->m_info;
				ObjectID posUnitID = info ? info->m_posUnitID : INVALID_ID;
				if (posUnitID != objID && posUnitID != INVALID_ID)
				{
					if (!obj->isKindOf( KINDOF_RVA003DF250_7C ))
						return false;
					Object *unit = TheGameLogic->findObjectByID( posUnitID );
					if (unit && !unit->isKindOf( KINDOF_RVA003DF250_08 ))
						return false;
				}

				ObjectID goalUnitID = info ? info->m_goalUnitID : INVALID_ID;
				if (goalUnitID != objID && goalUnitID != INVALID_ID)
				{
					Object *unit = TheGameLogic->findObjectByID( goalUnitID );
					if (unit)
					{
						if (unit->isKindOf( KINDOF_RVA003DF250_6C ) &&
							!obj->isKindOf( KINDOF_RVA003DF250_6C ))
							continue;
						if (!unit->isKindOf( KINDOF_RVA003DF250_08 ))
							return false;
						if (!obj->isKindOf( KINDOF_RVA003DF250_7C ))
							return false;
					}
				}
			}
		}
	}

	return true;
}
