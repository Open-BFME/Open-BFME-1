// cl: /DNDEBUG /MD
//
// Retail 0x003E5E40: Pathfinder::rva003E5E40, an address-named footprint test.
// Owner and argument are proven by the body: `this` is the receiver of
// Pathfinder::getRadiusAndCenter (0x003DEE30) and Pathfinder::worldToCell
// (0x003D7EC0), the argument goes to both of those and to
// Object::bfmeIsComputerControlled, and the cell scan reads Pathfinder's
// m_map/m_extent/m_layers exactly as Pathfinder::checkDestination (0x003DD7A0)
// does.  No caller, vtable slot or string names the method.
//
// The object is snapped to its cell the way Zero Hour's snapPosition does,
// then every cell under its footprint must exist, not be type 5 or 4, not be
// an aircraft goal for a computer-controlled object, and not be claimed as a
// goal by another unit that also occupies it.
//
// getRadiusAndCenter and worldToCell carry their bodies here, marked noinline
// so the calls still bind to the pinned ILT entries.  Retail's frame needs the
// compiler to see that neither lets its out-parameters escape: only then does
// MSVC keep `center` in BL across the later calls and hand the dead radius
// and cell.x slots to the loop's row offset and first row.
// With declaration-only callees the frame grows by eight bytes.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

const ObjectID INVALID_ID = 0;

#define PATHFIND_CELL_SIZE 10
#define PATHFIND_CELL_SIZE_F 10.0f

extern "C" __declspec(dllimport) double __cdecl floor( double );

// The matched bodies round with fld/fistp; a C++ conversion of the already
// floored value computes the same result, and only the bodies' side effects
// matter to this TU.
#define REAL_TO_INT_FLOOR(x) ((Int)floor((double)(x)))

extern const Real g_pathfindCellSize;
extern const Real g_pathfindDoubleCellSize;
extern const Real g_pathfindLevelLimit;
extern const Real g_pathfindCellCenterBias;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
	void set( const Coord3D *a ) { x = a->x; y = a->y; z = a->z; }
};
struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

enum PathfindLayerEnum { PATHFIND_LAYER_GROUND = 0 };

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	BfmeOverridable *getTemplate( void ) const { return m_template; }
	const Coord3D *getPosition( void ) const { return &m_position; }
	ObjectID getID( void ) const { return m_id; }
	Bool bfmeIsComputerControlled( void ) const;

	Int m_unknown00;					// +0x00
	BfmeOverridable *m_template;		// +0x04
	unsigned char u00[0x38 - 0x08];
	Coord3D m_position;					// +0x38
	unsigned char u44[0x74 - 0x44];
	ObjectID m_id;						// +0x74
	unsigned char m_pad78[0xbc - 0x78];
	Real m_boundingCircleRadius;		// +0xbc
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination( Object *object, const Coord3D *position );
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
// +0x14 is the goal unit Pathfinder::checkDestination reads; Zero Hour keeps
// m_posUnitID directly after m_goalUnitID.
class PathfindCellInfo
{
public:
	unsigned char m_prefix[0x14];	// +0x00 opaque
	ObjectID m_goalUnitID;			// +0x14
	ObjectID m_posUnitID;			// +0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Int getRawType( void ) const { return m_packed & 0x7; }
	Int getFlags( void ) const { return m_packed & 0x38; }
	unsigned char getGoalAircraftByte( void ) const
		{ return (unsigned char)(m_packed >> 21); }
	ObjectID getGoalUnit( void ) const
		{ return m_info ? m_info->m_goalUnitID : INVALID_ID; }
	ObjectID getPosUnit( void ) const
		{ return m_info ? m_info->m_posUnitID : INVALID_ID; }

private:
	PathfindCellInfo *m_info;		// +0x00
	Int m_unused1;					// +0x04
	Int m_unused2;					// +0x08
	unsigned int m_packed;			// +0x0c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	PathfindCell *getCell( Int x, Int y );

private:
	unsigned char m_body[0x44];		// stride 0x44
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool rva003E5E40( Object *obj );
	Bool worldToCell( const Coord3D *pos, ICoord2D *cell );
	PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y );

protected:
	void getRadiusAndCenter( const Object *obj, Int &iRadius, Bool &center );
	Bool rva003E5E40Cells( const Object *obj, Int cellX, Int cellY,
		PathfindLayerEnum layer, Int iRadius, Bool centerInCell );

private:
	unsigned char m_prefix[0x10];		// +0x000 opaque
	PathfindCell **m_map;				// +0x010
	IRegion2D m_extent;					// +0x014
	unsigned char m_mid[0x85c - 0x24];	// +0x024 opaque
	PathfindLayer m_layers[16];			// +0x85c
};

// Retail 0x003DEE30; logic of PathfindGetRadiusAndCenterE30.cpp.
__declspec(noinline) void Pathfinder::getRadiusAndCenter( const Object *obj, Int &radius, Bool &center )
{
	Real diameter;
	Int maxRadius = 2;
	BfmeOverridable *t1 = obj->getTemplate();
	if ((t1 == 0 ? t1 : t1->getFinalOverride())->m_flagsC8 & 0x400) {
		maxRadius = 4;
	} else {
		BfmeOverridable *t2 = obj->getTemplate();
		if ((t2 == 0 ? t2 : t2->getFinalOverride())->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = obj->m_boundingCircleRadius * 2.0f;
	if (diameter > g_pathfindCellSize && diameter < g_pathfindDoubleCellSize) {
		diameter = 20.0f;
	}

	if ((obj->getTemplate() == 0 ? obj->getTemplate() :
		obj->getTemplate()->getFinalOverride())->m_level > g_pathfindLevelLimit) {
		diameter = (obj->getTemplate() == 0 ? obj->getTemplate() :
		obj->getTemplate()->getFinalOverride())->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_pathfindCellCenterBias );
	center = false;
	if (radius == 0) radius++;
	if (radius & 1) {
		center = true;
	}
	radius /= 2;
	if (radius > maxRadius) {
		radius = maxRadius;
		center = true;
	}
}

// Retail 0x003D7EC0; logic of pathfind_getcell.cpp.
__declspec(noinline) Bool Pathfinder::worldToCell( const Coord3D *pos, ICoord2D *cell )
{
	cell->x = REAL_TO_INT_FLOOR(pos->x/PATHFIND_CELL_SIZE);
	cell->y = REAL_TO_INT_FLOOR(pos->y/PATHFIND_CELL_SIZE);
	Bool overflow = false;
	if (cell->x < m_extent.lo.x) {overflow = true; cell->x = m_extent.lo.x;}
	if (cell->y < m_extent.lo.y) {overflow = true; cell->y = m_extent.lo.y;}
	if (cell->x > m_extent.hi.x) {overflow = true; cell->x = m_extent.hi.x;}
	if (cell->y > m_extent.hi.y) {overflow = true; cell->y = m_extent.hi.y;}
	return overflow;
}

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

// Retail inlines this scan; it matches only as a by-value helper, whose
// parameter copies give the loop bounds retail's operand order.
// ?rva003E5E40Cells@Pathfinder@@IAE_NPBVObject@@HHW4PathfindLayerEnum@@H_N@Z absent-from-retail
__forceinline Bool Pathfinder::rva003E5E40Cells( const Object *obj, Int cellX, Int cellY,
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
				if (goalUnitID == objID || goalUnitID == INVALID_ID)
					continue;
				if (cell->getPosUnit() == goalUnitID)
					return false;
			}
		}
	}

	return true;
}

Bool Pathfinder::rva003E5E40( Object *obj )
{
	const Coord3D *pos = obj->getPosition();
	Int iRadius;
	Bool center;
	getRadiusAndCenter( obj, iRadius, center );
	Coord3D adjustDest;
	adjustDest.set( pos );
	if (!center)
	{
		adjustDest.x += PATHFIND_CELL_SIZE_F/2;
		adjustDest.y += PATHFIND_CELL_SIZE_F/2;
	}
	ICoord2D cell;
	if (worldToCell( &adjustDest, &cell ))
		return false;
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination( obj, pos );
	return rva003E5E40Cells( obj, cell.x, cell.y, layer, iRadius, center );
}
