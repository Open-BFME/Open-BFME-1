// ?query@Footprint003E5E40@@QAE_NPAUObject003E5E40@@@Z
// partial score=0.96 date=2026-09-23
// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/pathfind
// Continued from reverse/attempts/0x003e5e40.cpp using analyst pack 1b/1c.
// Full 460-byte body and 0x2C local frame. Remaining: 20 EBX/EDI operand bytes.
// Stack overlap is witnessed in retail: radius at SP+14 becomes the row-byte
// offset; coordinate.x at SP+24 becomes the first row. Bounds keeps the original
// 8-byte conversion output followed by the column limit and 12-byte position.
// These are local scratch lifetimes, not a claim about a game-object layout.
#define Coord3D PathfindCoord003E5E40
#define private public
#include "GameLogic/AIPathfind.h"
#undef private
#undef Coord3D
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
extern void j_000461ff();
extern void j_000171e8();
extern void j_0001c675();
extern void j_000105cd();
extern void j_00010ea1();
extern void *TheTerrainLogic;
class Call003E5E40 {};
template<class P> __forceinline P pointer003E5E40(void (*f)()) {
    union { void (*raw)(); P member; } u;
    u.raw=f; return u.member;
}
#define CALL(T,obj,fn) (((Call003E5E40*)(obj))->*pointer003E5E40<T>(fn))
struct Object003E5E40 {
    char u00[0x38]; Coord3D position;
    char u44[0x74-0x44]; unsigned m_id;
};
struct Info003E5E40 {
    char u00[0x14]; unsigned goalUnitID,posUnitID;
};
typedef void (Call003E5E40::*RadiusCall)(Object003E5E40*,int*,bool*);
typedef bool (Call003E5E40::*WorldCall)(const Coord3D*,ICoord2D*);
typedef int (Call003E5E40::*LayerCall)(Object003E5E40*,const Coord3D*);
typedef PathfindCell* (Call003E5E40::*CellCall)(int,int);
typedef bool (Call003E5E40::*ComputerCall)();
class Footprint003E5E40 : public Pathfinder {
public:
    bool query(Object003E5E40 *object);
    __forceinline PathfindCell *cellAt(int layer,int x,int y,const int &rowBytes) {
        if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
            y >= m_extent.lo.y && y <= m_extent.hi.y) {
            if (layer > 1 && layer <= 15) {
                PathfindCell *cell=CALL(CellCall,&m_layers[layer],j_000105cd)(x,y);
                if (cell) return cell;
            }
            return (PathfindCell*)((char*)m_map[x]+rowBytes);
        }
        return 0;
    }
};
bool Footprint003E5E40::query(Object003E5E40 *object)
{
    bool center;
    union { int radius; int rowBytes; } work;
    const Coord3D *objectPosition=&object->position;
    {
        bool centerOutput;
        CALL(RadiusCall,this,j_000461ff)(object,&work.radius,&centerOutput);
        center=centerOutput;
    }
    struct Bounds { ICoord2D coordinate; int endX; Coord3D position; } bounds;
    bounds.position.x=objectPosition->x; bounds.position.y=objectPosition->y; bounds.position.z=objectPosition->z;
    if (!center) {
        bounds.position.x+=5.0f;
        bounds.position.y+=5.0f;
    }
    if (CALL(WorldCall,this,j_000171e8)(&bounds.position,&bounds.coordinate)) return false;
    int layer=CALL(LayerCall,TheTerrainLogic,j_0001c675)(object,objectPosition);
    int above=work.radius;
    if (center) ++above;
    unsigned id=object->m_id;
    int x=bounds.coordinate.x-work.radius;
    bounds.endX=above+bounds.coordinate.x;
    if (x>=bounds.endX) return true;
    bounds.coordinate.x=bounds.coordinate.y-work.radius;
    int endY=bounds.coordinate.y+above;
    for (;x<bounds.endX;++x) {
        int y=bounds.coordinate.x;
        if (y<endY) {
          work.rowBytes=y*16;
          do {
            PathfindCell *cell=cellAt(layer,x,y,work.rowBytes);
            if (!cell) return false;
            if (cell->getType()==5) return false;
            if (((unsigned char)(cell->m_packed>>21)&1) && CALL(ComputerCall,object,j_00010ea1)()) return false;
            if (cell->getType()==4) return false;
            if (cell->m_packed&0x38) {
                Info003E5E40 *info=(Info003E5E40*)cell->m_info;
                unsigned goal=info ? info->goalUnitID : 0;
                if (goal==id || goal==0) goto nextCell;
                unsigned occupied=info ? info->posUnitID : 0;
                if (occupied==goal) return false;
            }
nextCell:
            ++y; work.rowBytes+=16;
          } while (y<endY);
        }
    }
    return true;
}
