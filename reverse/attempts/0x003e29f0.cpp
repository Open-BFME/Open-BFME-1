// ?search@Circular003E29F0@@QAE_NPBUICoord2D@@HPAU2@PAUContext003E29F0@@H@Z
// partial score=0.9495459132189707 date=2026-09-21
// cl: /DNDEBUG /MD /Ireference/shims/pathfind
// RVA 003E29F0: five stack arguments; incoming ECX is unused; ret 14h.
// Analyst pack docs/analysis/0x003e8e10.md 1b/1c proves the 60-byte
// callback layout, Object+38 position and each callee ABI.
// Full body: 991/991 bytes; initial block register/scheduling residue only.
// Distance comparison deliberately permits unordered x87 results, as retail does.
#include "GameLogic/AIPathfind.h"
#include <stddef.h>
extern void j_0003a17a();
extern void j_000469bb();
extern bool Glo012F0239;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
class Call003E29F0 {};
template<class P> __forceinline P pointer003E29F0(void (*f)()) {
    union {void (*raw)(); P member;} u;
    u.raw=f; return u.member;
}
struct Object003E29F0 { char u00[0x38]; Coord3D position; };
struct Profile003E29F0 { int u00; bool u04,u05; int u08; };
struct Context003E29F0 {
    void *pathfinder;
    Profile003E29F0 *profile;
    unsigned zone;
    bool center;
    int layer;
    Coord3D position;
    bool sourceSpecial;
    void *rangeReceiver;
    Object003E29F0 *source,*target;
    int radius;
    Coord3D *destination;
    bool special;
};
typedef char CheckContext003E29F0[(sizeof(Context003E29F0)==60 && offsetof(Context003E29F0,source)==0x28)?1:-1];
typedef bool (Call003E29F0::*CheckCellCall)(int,int);
static __forceinline bool check003E29F0(Context003E29F0 *context,int x,int y) {
    return (((Call003E29F0*)context)->*pointer003E29F0<CheckCellCall>(j_000469bb))(x,y);
}
class Circular003E29F0 {
public:
    bool search(const ICoord2D *center,int maxCells,ICoord2D *out,Context003E29F0 *context,int afterHit);
};
bool Circular003E29F0::search(const ICoord2D *center,int maxCells,ICoord2D *out,Context003E29F0 *context,int afterHit)
{
    bool found=false;
    float best=0.0f;
    int remaining=10000;
    if (Glo012F0239 && TheCRCParameterCheck) {
        typedef void (__cdecl *Log)(CRCParameterCheck*,const char*,...);
        ((Log)j_0003a17a)(TheCRCParameterCheck,"\t\tIterateCircular3 called with center=%d,%d, maxCells=%d",center->x,center->y,maxCells);
    }
    int initialX=center->x;
    int initialY=center->y;
    if (check003E29F0(context,initialX,initialY)) {
        out->x=center->x;
        out->y=center->y;
        float dx=(float)(center->x*10)-context->source->position.x;
        float dy=(float)(center->y*10)-context->source->position.y;
        found=true;
        best=dx*dx+dy*dy;
        remaining=afterHit;
    }
    int x=0;
    int y=0;
    for (int side=1;maxCells>0;side+=2) {
        if (--remaining<=0) return found;
        maxCells-=4*side+2;
        for (int i=0;i<side;++i) {
            int cellX=center->x;
            ++x;
            cellX+=x;
            {
            float dx=(float)(cellX*10)-context->source->position.x;
            float dy=(float)((center->y+y)*10)-context->source->position.y;
            float distance=dx*dx+dy*dy;
            if ((!found || !(distance>=best)) && check003E29F0(context,cellX,center->y+y)) {
                out->x=center->x+x;
                out->y=center->y+y;
                found=true;
                best=distance;
                remaining=afterHit;
            }
            }
        }
        for (int j=0;j<side;++j) {
            ++y;
            {
            float dx=(float)((center->x+x)*10)-context->source->position.x;
            float dy=(float)((center->y+y)*10)-context->source->position.y;
            float distance=dx*dx+dy*dy;
            if ((!found || !(distance>=best)) && check003E29F0(context,center->x+x,center->y+y)) {
                out->x=center->x+x;
                out->y=center->y+y;
                found=true;
                best=distance;
                remaining=afterHit;
            }
            }
        }
        for (int k=0;k<=side;++k) {
            --x;
            {
            float dx=(float)((center->x+x)*10)-context->source->position.x;
            float dy=(float)((center->y+y)*10)-context->source->position.y;
            float distance=dx*dx+dy*dy;
            if ((!found || !(distance>=best)) && check003E29F0(context,center->x+x,center->y+y)) {
                out->x=center->x+x;
                out->y=center->y+y;
                found=true;
                best=distance;
                remaining=afterHit;
            }
            }
        }
        for (int n=0;n<=side;++n) {
            --y;
            {
            float dx=(float)((center->x+x)*10)-context->source->position.x;
            float dy=(float)((center->y+y)*10)-context->source->position.y;
            float distance=dx*dx+dy*dy;
            if ((!found || !(distance>=best)) && check003E29F0(context,center->x+x,center->y+y)) {
                out->x=center->x+x;
                out->y=center->y+y;
                found=true;
                best=distance;
                remaining=afterHit;
            }
            }
        }
    }
    return found;
}
