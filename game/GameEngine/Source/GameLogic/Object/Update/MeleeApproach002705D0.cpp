// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// Compile symbol: ?request@MeleeApproach002705D0@@QAE_NPBVCoord3D@@_N@Z
// Retail RVA 002705D0, 783 bytes. Source-family and behavior witness:
// literal "CritterDesync: requestMeleeApproachPath1" at VA 010B9758.
// Offset view is deliberately address-derived; no unverified class layout.
// Five-argument hub and two-argument terrain contract: docs/analysis/0x003e9720.md.
#include "coord3d.h"
#include <math.h>
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
// coord3d.cpp owns ??0Coord3D@@QAE@ABV0@@Z and ??4Coord3DBase@@QAEAAU0@ABU0@@Z
// as out-of-line definitions; giving them COMDAT copies here would collide.
// This TU inlines every copy instead, so nothing external is referenced.
__forceinline void Melee002705D0CopyCoord(Coord3DBase &d, const Coord3DBase &s) {
    d.x=s.x; d.y=s.y; d.z=s.z;
}
__forceinline void Melee002705D0AssignCoord(Coord3DBase &d, const Coord3DBase &s) {
    struct Raw { unsigned int x,y,z; };
    *(Raw *)&d=*(const Raw *)&s;
}

class Melee002705D0Route {};
extern void j_0001c675(); extern void j_0002f3c9();
extern void j_000294e2(); extern void j_0003a17a();
extern void j_000176c5(); extern void j_000157da();
extern void j_000065e1(); extern void j_00013eee();

struct Melee002705D0Object {
    unsigned char pad000[0x38];
    Coord3D at038;
    unsigned char pad044[0x74-0x44];
    unsigned int at074;
    const Coord3D *position() const { return &at038; }
};
class Melee002705D0Pathfinder {
public:
    __forceinline bool queue(unsigned int id) {
        typedef bool (Melee002705D0Route::*Call)(unsigned int);
        union { void (*address)(); Call member; } route={j_00013eee};
        return (((Melee002705D0Route *)this)->*route.member)(id);
    }
};
template<int N> class Melee002705D0Slots : public Melee002705D0Slots<N-1> {
public: virtual void unused(char (*)[N]) = 0;
};
template<> class Melee002705D0Slots<0> {};
class Melee002705D0Terrain : public Melee002705D0Slots<7> {
public:
    virtual float slot01c(float x,float y,int layer,void *normal,bool flag) = 0;
    __forceinline int layer(Melee002705D0Object *obj,const Coord3D *pos) {
        typedef int (Melee002705D0Route::*Call)(Melee002705D0Object *,const Coord3D *);
        union { void (*address)(); Call member; } route={j_0001c675};
        return (((Melee002705D0Route *)this)->*route.member)(obj,pos);
    }
};
struct Melee002705D0Data { unsigned char pad000[0x94]; float at094; };
struct Melee002705D0GlobalAI {
    unsigned char pad000[12]; Melee002705D0Pathfinder *at00c;
    unsigned char pad010[4]; Melee002705D0Data *at014;
    Melee002705D0Pathfinder *pathfinder() const { return at00c; }
};
struct Melee002705D0GameLogic { unsigned char pad000[0x3c]; unsigned int at03c; };
class GameLogic;
extern GameLogic *TheGameLogic;
static inline Melee002705D0GameLogic *frameView002705D0() { return (Melee002705D0GameLogic *)TheGameLogic; }
// 0x012EF214 is retail's TheAI singleton (`AI *TheAI`, mangled
// ?TheAI@@3PAVAI@@A), defined in GameLogic/AI/ai.cpp. Melee002705D0GlobalAI
// stays as this TU's offset view of it.
class AI;
extern AI *TheAI;
static inline Melee002705D0GlobalAI *aiView002705D0() { return (Melee002705D0GlobalAI *)TheAI; }
// Retail 0x012EF4CC is the terrain singleton, defined out of line as
// ?TheTerrainLogic@@3PAVTerrainLogic@@A by GameLogic/Map/terrainlogic.cpp.
// Melee002705D0Terrain stays as this TU's virtual-table view of it.
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
extern bool Glo012F0239;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;

class MeleeApproach002705D0 {
public:
    unsigned char pad000[8];
    Melee002705D0Object *m_object;
    unsigned char pad00c[0x144-0xc];
    unsigned int at144;
    Coord3D m_requestedDestination; // +148, name_oracle and retail log agree.
    unsigned char pad154[12];
    unsigned int at160;
    unsigned char pad164[0x17c-0x164];
    unsigned int m_queueForPathFrame; // +17c, matched neighbouring AIUpdate.cpp.
    unsigned char pad180[0x1a8-0x180];
    unsigned char at1a8[0x31e-0x1a8];
    bool at31e, at31f, at320, at321, at322;
    unsigned char pad323[0x330-0x323];
    bool at330;
    __forceinline int wake() {
        typedef int (Melee002705D0Route::*Call)();
        union { void (*address)(); Call member; } route={j_000176c5};
        return (((Melee002705D0Route *)this)->*route.member)();
    }
    __forceinline void setWake(Melee002705D0Object *obj,int frames) {
        typedef void (Melee002705D0Route::*Call)(Melee002705D0Object *,int);
        union { void (*address)(); Call member; } route={j_000157da};
        (((Melee002705D0Route *)this)->*route.member)(obj,frames);
    }
    __forceinline void destroy() {
        typedef void (Melee002705D0Route::*Call)();
        union { void (*address)(); Call member; } route={j_000065e1};
        (((Melee002705D0Route *)this)->*route.member)();
    }
    bool request(const Coord3D *destination,bool flag);
};

bool MeleeApproach002705D0::request(const Coord3D *destination,bool flag) {
    Melee002705D0Object *obj=m_object;
    Coord3D oldPosition;
    Melee002705D0CopyCoord(oldPosition,*obj->position());
    Coord3D pos;
    {
        // The normalized direction dies before the adjusted-distance temporary.
        Coord3D delta;
        delta.x=oldPosition.x-destination->x;
        delta.y=oldPosition.y-destination->y;
        delta.z=0.0f;
        if (!flag && sqrt(delta.x*delta.x+delta.y*delta.y)>aiView002705D0()->at014->at094) {
            delta.normalize();
            Melee002705D0Data *data=aiView002705D0()->at014;
            delta.x*=data->at094;
            delta.y*=data->at094;
        }
        pos.x=destination->x; pos.y=destination->y; pos.z=destination->z;
        if (!flag) {
            pos.x+=delta.x;
            pos.y+=delta.y;
            int layer=((Melee002705D0Terrain *)TheTerrainLogic)->layer(obj,destination);
            float height=((Melee002705D0Terrain *)TheTerrainLogic)->slot01c(pos.x,pos.y,layer,0,true);
            if (fabs(height-((Melee002705D0Terrain *)TheTerrainLogic)->slot01c(destination->x,destination->y,layer,0,true))>10.0f)
            Melee002705D0AssignCoord(pos,*destination);
        }
    }
    Melee002705D0Object *adjustObject=m_object;
    typedef bool (Melee002705D0Route::*AdjustCall)(Melee002705D0Object *, void *, Coord3D *);
    union { void (*address)(); AdjustCall member; } adjustCall={j_0002f3c9};
    if ((((Melee002705D0Route *)aiView002705D0()->pathfinder())->*adjustCall.member)(adjustObject,at1a8,&pos)) {
        Melee002705D0Object *owner=m_object;
        Melee002705D0Pathfinder *finder=aiView002705D0()->pathfinder();
        typedef void (Melee002705D0Route::*UpdateCall)(Melee002705D0Object *,const Coord3D *,int,const char *,int);
        union { void (*address)(); UpdateCall member; } updateCall={j_000294e2};
        (((Melee002705D0Route *)finder)->*updateCall.member)(owner,&pos,((Melee002705D0Terrain *)TheTerrainLogic)->layer(owner,&pos),
            "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp",0x351);
        Coord3D distance;
        Melee002705D0AssignCoord(distance,oldPosition);
        distance.x-=pos.x;
        distance.y-=pos.y;
        if (!(sqrt(distance.x*distance.x+distance.y*distance.y)<20.0f)) {
            if (Glo012F0239 && TheCRCParameterCheck)
            ((void (__cdecl *)(void *,const char *,...))j_0003a17a)(TheCRCParameterCheck,
                "CritterDesync: requestMeleeApproachPath1 -- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
                m_requestedDestination.x,m_requestedDestination.y,m_requestedDestination.z,pos.x,pos.y,pos.z);
            Melee002705D0AssignCoord(m_requestedDestination,pos);
            at320=true;
            at31f=false;
            at144=0;
            at321=true;
            at322=false;
            if (at160>frameView002705D0()->at03c-2) {
                if (wake()>10 && !at330) setWake(m_object,10);
                m_queueForPathFrame=frameView002705D0()->at03c+10;
                destroy();
                return true;
            }
            at31e=true;
            aiView002705D0()->pathfinder()->queue(m_object->at074);
            return true;
        }
    }
    return false;
}
