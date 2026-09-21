// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/pathfind
// RVA 003E3B20. Layout/ABI witnesses: docs/analysis/0x003e8e10.md 1b/1c.
// Three stack arguments; mutates the third. The semantic method name is unknown.
// The pathfind shim has a trivial Coord3D stand-in. Keep its unused coordinate
// declarations separate and include the native nontrivial 12-byte class below.
#define Coord3D PathfindCoord003E3B20
#define private public
#include "GameLogic/AIPathfind.h"
#undef private
#undef Coord3D
#include "coord3d.h"
// Authentic inline bodies from WWMath/coord3d.cpp, not substitute callees.
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &c) {x=c.x;y=c.y;z=c.z;}
inline void Coord3D::scale(float s) {x*=s;y*=s;z*=s;}
inline void Coord3D::add(const Coord3DBase *c) {x+=c->x;y+=c->y;z+=c->z;}

// Independently witnessed ILTs: layer 1BEC20; contact 272800; position
// 1C0010; world-to-cell 3D7EC0; layer cell 3FBB20; override 087A80.
extern void j_0003a391();
extern void j_00015ae6();
extern void j_00027bc9();
extern void j_000171e8();
extern void j_00009a89();
extern void j_000022bb();
class Call003E3B20 {};
template<class P> __forceinline P callPointer003E3B20(void (*f)())
{
    union { void (*raw)(); P member; } u;
    u.raw=f; return u.member;
}
#define CALL(T,obj,fn) (((Call003E3B20*)(obj))->*callPointer003E3B20<T>(fn))
struct Template003E3B20 {
    unsigned u00; Template003E3B20 *nextOverride;
    char u08[0xCC-8]; unsigned uCC;
};
struct Object003E3B20 {
    unsigned u00; Template003E3B20 *m_template;
    char u08[0x38-8]; Coord3D position;
    char u44[0x204-0x44]; void *u204;
};
typedef int (Call003E3B20::*LayerCall)();
typedef bool (Call003E3B20::*ContactCall)(Object003E3B20*,Coord3D*,const Coord3D*,bool);
typedef void (Call003E3B20::*PositionCall)(Coord3D*);
typedef bool (Call003E3B20::*WorldCall)(const Coord3D*,ICoord2D*);
typedef PathfindCell* (Call003E3B20::*CellCall)(int,int);
typedef Template003E3B20* (Call003E3B20::*OverrideCall)();

class VectorAdjust003E3B20 : public Pathfinder {
public:
    void adjust(Object003E3B20 *source,Object003E3B20 *target,Coord3D *vector);
    __forceinline PathfindCell *cellAt(int layer,const ICoord2D &c) {
        // Retail +B8 loads x once and +CE loads y after both x bounds.
        // This access prevents VC7.1 from hoisting y into that guard.
        int x=*(volatile const int*)&c.x;
        if (x < m_extent.lo.x || x > m_extent.hi.x) return 0;
        int y=c.y;
        if (y < m_extent.lo.y || y > m_extent.hi.y) return 0;
        if (layer > 1 && layer <= 15) {
            PathfindCell *cell=CALL(CellCall,&m_layers[layer],j_00009a89)(x,y);
            if (cell) return cell;
        }
        return &m_map[x][y];
    }
};
void VectorAdjust003E3B20::adjust(Object003E3B20 *source,Object003E3B20 *target,Coord3D *vector)
{
    int layer=CALL(LayerCall,target,j_0003a391)();
    if (source->u204 && CALL(ContactCall,source->u204,j_00015ae6)(target,vector,&source->position,false))
        return;
    Coord3D origin;
    CALL(PositionCall,target,j_00027bc9)(&origin);
    int count;
    for (count=0;count<20;++count) {
        Coord3D position=*vector;
        position.scale((float)count);
        position.add(&origin);
        ICoord2D coordinate;
        if (CALL(WorldCall,this,j_000171e8)(&position,&coordinate)) return;
        PathfindCell *cell=cellAt(layer,coordinate);
        if (!cell) return;
        Template003E3B20 *t=target->m_template;
        if (t && t->nextOverride) t=CALL(OverrideCall,t->nextOverride,j_000022bb)();
        if (t->uCC & 0x08000000) {
            int cellLayer=cell->getLayer();
            if (cellLayer>=17 && cellLayer<=64) continue;
        } else {
            if (cell->getType()==4) continue;
        }
        float factor=(float)count;
        vector->x*=factor; vector->y*=factor; vector->z*=factor;
        return;
    }
}
