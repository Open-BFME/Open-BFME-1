// ?bfmeObjectCell@Pathfinder@@QAEXPAVObject@@PAUICoord2D@@@Z
// partial score=0.98 date=2026-09-04
// ?bfmeObjectCell@Pathfinder@@QAEXPAVObject@@PAUICoord2D@@@Z present-unmatched
// ?bfmeObjectCell@Pathfinder@@QAEXPAVObject@@PAUICoord2D@@@Z
// partial score=0.98 date=2026-09-02
// cl: /DNDEBUG /MD

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

struct Coord3D
{
    Real x, y, z;
};

struct ICoord2D
{
    Int x, y;
};

const Real PATHFIND_CELL_SIZE_INV = 1.0f / 10.0f;

#define BFME_FLOOR_TO_LONG_ASM __asm fld dword ptr [center] __asm fistp dword ptr [radius]

union BFMEQueryScratch
{
    Int i;
    Real f;
    Bool b;
};

static __forceinline Int bfmeReadVolatileInt( volatile Int *value )
{
    return *value;
}

class BFMEObjectLayerQuery
{
public:
    Int getLayer( void ) const;
};

class Object : public BFMEObjectLayerQuery
{
public:
    char m_pad[0x38];
    Coord3D m_pos;
};

class Pathfinder
{
public:
    void bfmeQuery( Object *obj, Int *radius, Int *center );
    PathfindCell *bfmeGetCellByIndicesTwin( PathfindLayerEnum layer,
        Int cellX, Int cellY );
    void bfmeObjectCell( Object *obj );
    void bfmeObjectCell( Object *obj, ICoord2D *cell );
};

void Pathfinder::bfmeObjectCell( Object *obj, ICoord2D *cell )
{
    BFMEQueryScratch radius;
    BFMEQueryScratch center;
    bfmeQuery( obj, &radius.i, &center.i );
    Bool centerInCell = *(volatile Bool *)&center.b;
    if (centerInCell) {
        center.f = (Real)floor( obj->m_pos.x * PATHFIND_CELL_SIZE_INV );
        BFME_FLOOR_TO_LONG_ASM;
    } else {
        center.f = (Real)floor( 0.5f + obj->m_pos.x * PATHFIND_CELL_SIZE_INV );
        BFME_FLOOR_TO_LONG_ASM;
    }
    cell->x = bfmeReadVolatileInt( &radius.i );

    Int cellY;
    if (centerInCell) {
        center.f = (Real)floor( obj->m_pos.y * PATHFIND_CELL_SIZE_INV );
        __asm fld dword ptr [center]
        __asm fistp dword ptr [cellY]
    } else {
        center.f = (Real)floor( 0.5f + obj->m_pos.y * PATHFIND_CELL_SIZE_INV );
        __asm fld dword ptr [center]
        __asm fistp dword ptr [cellY]
    }
    bfmeGetCellByIndicesTwin( (PathfindLayerEnum)(cell->y = cellY, obj->getLayer()),
        cell->x, cellY );
}
