// ?bfmeObjectCell@Pathfinder@@QAEXPAVObject@@@Z
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x003DEFB0 and 0x003DF0C0: the two BFME helpers that turn an object's
// world position into a pathfind cell index.
//
// ZH AIPathfind.cpp:9974 (Pathfinder::updatePos) writes the same idiom inline:
//
//   getRadiusAndCenter(obj, radius, centerInCell);
//   if (centerInCell) newCell.x = REAL_TO_INT_FLOOR(pos->x/PATHFIND_CELL_SIZE_F);
//   else              newCell.x = REAL_TO_INT_FLOOR(0.5f+pos->x/PATHFIND_CELL_SIZE_F);
//
// BFME pulled the query out of line into Pathfinder::bfmeQuery and replaced
// ZH's fast_float_floor bit hack with the CRT floor import, keeping ZH's
// fast_float2long_round (fld/fistp) for the float->long step.  It also turned
// the division by PATHFIND_CELL_SIZE into a multiply by its reciprocal.
//
// No /EHsc: retail registers no handler for either body.

#include <math.h>

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

class Object;
class Pathfinder;
class PathfindCell;

enum PathfindLayerEnum
{
	PATHFIND_LAYER_DUMMY = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x, y;
};

const Real PATHFIND_CELL_SIZE_INV = 1.0f / 10.0f;

// BFME's REAL_TO_INT_FLOOR: the CRT floor import narrowed back to Real, then
// ZH Lib/BaseType.h:182's fast_float2long_round fld/fistp pair.  The scratch
// pair is at function scope -- retail shares one Real and one long across all
// four floor sites instead of giving each inline instance its own.
#define BFME_FLOOR_TO_LONG_ASM __asm fld dword ptr [center] __asm fistp dword ptr [radius]

union BFMEQueryScratch
{
	Int i;
	Real f;
	Bool b;
};

class BFMEObjectLayerQuery
{
public:
	Int getLayer( void ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BFMEObjectLayerQuery
{
public:
	char m_pad[0x38];
	Coord3D m_pos;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void bfmeQuery( Object *obj, Int *radius, Int *center );
	PathfindCell *bfmeGetCellByIndicesTwin( PathfindLayerEnum layer,
		Int cellX, Int cellY );

	void bfmeObjectCell( Object *obj );
	void bfmeObjectCell( Object *obj, ICoord2D *cell );
};

void Pathfinder::bfmeObjectCell( Object *obj )
{
	BFMEQueryScratch radius;
	BFMEQueryScratch center;
	bfmeQuery( obj, &radius.i, &center.i );
	Bool centerInCell = *(volatile Bool *)&center.b;

	ICoord2D cell;
	if (centerInCell) {
		center.f = (Real)floor( obj->m_pos.x * PATHFIND_CELL_SIZE_INV );
		BFME_FLOOR_TO_LONG_ASM;
	} else {
		center.f = (Real)floor( 0.5f + obj->m_pos.x * PATHFIND_CELL_SIZE_INV );
		BFME_FLOOR_TO_LONG_ASM;
	}
	cell.x = radius.i;

	if (centerInCell) {
		center.f = (Real)floor( obj->m_pos.y * PATHFIND_CELL_SIZE_INV );
		BFME_FLOOR_TO_LONG_ASM;
	} else {
		center.f = (Real)floor( 0.5f + obj->m_pos.y * PATHFIND_CELL_SIZE_INV );
		BFME_FLOOR_TO_LONG_ASM;
	}
	cell.y = radius.i;

	Int cellY = *(volatile Int *)&radius.i;
	bfmeGetCellByIndicesTwin( (PathfindLayerEnum)obj->getLayer(), cell.x, cellY );
}

void Pathfinder::bfmeObjectCell( Object *obj, ICoord2D *cell )
{
	BFMEQueryScratch radius;
	BFMEQueryScratch center;
	bfmeQuery( obj, &radius.i, &center.i );
	Bool centerInCell = center.b;

	if (centerInCell) {
		center.f = (Real)floor( obj->m_pos.x * PATHFIND_CELL_SIZE_INV );
		BFME_FLOOR_TO_LONG_ASM;
	} else {
		center.f = (Real)floor( 0.5f + obj->m_pos.x * PATHFIND_CELL_SIZE_INV );
		BFME_FLOOR_TO_LONG_ASM;
	}
	cell->x = radius.i;

	if (centerInCell) {
		center.f = (Real)floor( obj->m_pos.y * PATHFIND_CELL_SIZE_INV );
		BFME_FLOOR_TO_LONG_ASM;
	} else {
		center.f = (Real)floor( 0.5f + obj->m_pos.y * PATHFIND_CELL_SIZE_INV );
		BFME_FLOOR_TO_LONG_ASM;
	}
	cell->y = radius.i;

	bfmeGetCellByIndicesTwin( (PathfindLayerEnum)obj->getLayer(), cell->x, cell->y );
}
