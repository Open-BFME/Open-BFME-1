// ?d_00182f70@@YAXXZ
// partial score=0.3785004516711834 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled
// Retail 00182F70: ECX receiver, no incoming stack arguments, AL result.
// Complete 1107-byte boundary ends at 001833C2; no EH frame.
// Opaque owner retained: old structural method names contradict one another.
// Hub/remover contracts: docs/analysis/0x003e9720.md.
#include "../../Code/Libraries/Source/WWVegas/WWMath/coord.h"

struct Object00182F70;
struct AI00182F70;
struct Contain00182F70;
template<int N> struct Slots00182F70:Slots00182F70<N-1> {virtual void slot(char(*)[N])=0;};
template<> struct Slots00182F70<0> {};
struct Query00182F70:Slots00182F70<73> {virtual bool slot124(Object00182F70*)=0;};
struct Contain00182F70:Slots00182F70<26> {virtual Query00182F70* slot68()=0;};
struct Object00182F70 {
    unsigned char pad00[0x38]; Coord3D position;
    unsigned char pad44[0x50]; unsigned char byte94; unsigned char pad95[0x27]; float floatBC;
    unsigned char padC0[0x13c]; Contain00182F70* contain1FC;
    unsigned char pad200[4]; AI00182F70* ai204;
    unsigned char pad208[0xc]; Object00182F70* ptr214;
    bool rva001c9270(); void* rva001be230(int);
    const Coord3D* rva00132140(); int rva001bec20();
    bool rva000a2cf0(int); float rva0015be50(const Coord3D*);
};
struct AI00182F70 {
    unsigned char pad00[0x140]; void* path140;
    unsigned char pad144[0x64]; unsigned char data1A8[0x10]; int dword1B8;
    unsigned char pad1BC[0x162]; bool byte31E; unsigned char pad31F[7]; bool byte326;
    void rva002739f0(Object00182F70*); void rva0026fe90(float);
    void rva0027bd90(Coord3D*,bool);
};
struct Machine00182F70 {
    unsigned char pad00[0x10]; Object00182F70* owner;
    Object00182F70* rva000a1490();
};
struct Pathfinder00182F70 {
    bool rva003edf90(Object00182F70*,const Coord3D*,const Coord3D*,int);
    void rva003eac80(Object00182F70*,void*,Coord3D*);
    // Retail caller consumes only AL of the landed int predicate.
    int rva003ee850(Object00182F70*,int,int,const Coord3D*,const Coord3D*);
    void rva003e3d20(Object00182F70*);
    void rva003f5c70(Object00182F70*,void*,Coord3D*);
    void rva003e9720(Object00182F70*,const Coord3D*,int,const char*,int);
};
struct Terrain00182F70 {int rva001a7c20(Object00182F70*,const Coord3D*);};
struct CoordCalls00182F70 {
    Coord3D& rva0014ffd0(float); Coord3D& rva000ec6f0(const Coord3D&);
    Coord3D& rva000c3d40(const Coord3D&); void rva000fb930(); float rva000fe9b0() const;
};
struct AIHub00182F70 {unsigned char pad00[12]; Pathfinder00182F70* pathfinder;};
struct Clock00182F70 {unsigned char pad00[0x3c]; unsigned frame;};
extern AIHub00182F70* TheAI;
extern Clock00182F70* TheGameLogic;
extern Terrain00182F70* TheTerrainLogic;
extern unsigned char g_012F0239;
extern void* g_012ED4FC;
extern const float g_0108882C,g_01075C6C,g_0107533C,g_01076C24;
extern bool rva00175820(Object00182F70*,Object00182F70*);
extern bool rva001752a0(Coord3D*,Object00182F70*,Object00182F70*);
extern void rva00065c80(void*,const char*);

class PathCompute00182F70 {
public:
    unsigned char pad00[0x1c]; Machine00182F70* machine;
    unsigned char pad20[4]; Coord3D coord24;
    unsigned char pad30[0x1c]; bool byte4C,byte4D; unsigned char pad4E[2]; Coord3D coord50;
    unsigned frame5C; bool byte60,byte61;
    static bool __stdcall rva0016f150(Coord3D*,Object00182F70*,Object00182F70*);
    bool compute();
};

// The real static helper is visible so VC7.1 can select its private
// EDX/ECX/EAX argument convention. Source is the ZH AIStates twin.
static bool isSamePosition(const Coord3D* ourPos,const Coord3D* prevTargetPos,const Coord3D* curTargetPos) {
    Coord3D diff;
    diff.x=curTargetPos->x-prevTargetPos->x; diff.y=curTargetPos->y-prevTargetPos->y;
    Coord3D toTarget;
    toTarget.x=curTargetPos->x-ourPos->x; toTarget.y=curTargetPos->y-ourPos->y;
    float toleranceSqr=(toTarget.x*toTarget.x+toTarget.y*toTarget.y)*0.01f;
    if(diff.x*diff.x+diff.y*diff.y>toleranceSqr) return false;
    return true;
}

bool PathCompute00182F70::compute() {
    bool forceRepath=false;
    byte60=false;
    Object00182F70* source=machine->owner;
    if(!source->rva001c9270()) return false;
    AI00182F70* ai=source->ai204;
    if(ai->byte326) forceRepath=true;
    if(byte4D) return true;
    if(!forceRepath && !ai->path140 && !ai->byte31E) forceRepath=true;
    if(!forceRepath && TheGameLogic->frame-frame5C<5) return true;
    frame5C=TheGameLogic->frame;
    Object00182F70* victim=machine->rva000a1490();
    if(!victim) return false;
    if((victim->byte94&0x20) && victim->ptr214) victim=victim->ptr214;
    if(!forceRepath && isSamePosition(&source->position,&coord50,&victim->position)) return true;
    if(!source->rva001be230(0)) return false;
    coord50=victim->position;
    ai->rva002739f0(0);
    ai->rva0026fe90(100.0f);
    coord24=coord50;
    Coord3D delta=coord24;
    if(rva00175820(source,victim) && TheAI->pathfinder->rva003edf90(source,&source->position,&victim->position,0)) {
        delta=*victim->rva00132140();
        ((CoordCalls00182F70*)&delta)->rva0014ffd0(victim->floatBC*2+60.0f);
        ((CoordCalls00182F70*)&coord24)->rva000ec6f0(delta);
        TheAI->pathfinder->rva003eac80(source,ai->data1A8,&coord24);
        if(g_012F0239 && g_012ED4FC) rva00065c80(g_012ED4FC,"CritterDesync: setAdjustDestination(FALSE) 23");
        byte4C=false;
        ai->rva0027bd90(&coord24,false);
        byte4D=ai->byte31E;
        if(ai->path140) byte4D=false;
        return true;
    }
    ((CoordCalls00182F70*)&delta)->rva000c3d40(source->position);
    ((CoordCalls00182F70*)&delta)->rva000fb930();
    delta.scale(source->floatBC*0.7f);
    if(victim->rva001bec20()==1) {
        Coord3D destination=coord24;
        destination.sub(&delta);
        if(!(unsigned char)TheAI->pathfinder->rva003ee850(source,ai->dword1B8,1,&coord24,&destination)) coord24=destination;
        if(victim->rva000a2cf0(7)) rva0016f150(&coord24,source,victim);
    }
    if(!rva001752a0(&coord24,source,victim)) {byte60=true; return false;}
    TheAI->pathfinder->rva003e3d20(source);
    if(byte61) TheAI->pathfinder->rva003f5c70(source,ai->data1A8,&coord24);
    else rva0016f150(&coord24,source,0);
    delta=coord24;
    delta.sub(&source->position);
    float before=victim->rva0015be50(&source->position);
    float improvement=before-victim->rva0015be50(&coord24);
    if(improvement < ((CoordCalls00182F70*)&delta)->rva000fe9b0()*0.5f && ai->path140 && source->contain1FC) {
        Query00182F70* q=source->contain1FC->slot68();
        if(q && q->slot124(victim)) {byte60=true; return false;}
    }
    if(byte61) TheAI->pathfinder->rva003e9720(source,&coord24,TheTerrainLogic->rva001a7c20(source,&coord24),"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp",0x13eb);
    ai->rva0027bd90(&coord24,false);
    byte4D=ai->byte31E;
    if(ai->path140) byte4D=false;
    return true;
}

// Existing ILT routes; these aliases assert only the witnessed machine ABI.
#pragma comment(linker, "/alternatename:?rva001c9270@Object00182F70@@QAE_NXZ=?j_00017607@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000a1490@Machine00182F70@@QAEPAUObject00182F70@@XZ=?j_0000e570@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001be230@Object00182F70@@QAEPAXH@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002739f0@AI00182F70@@QAEXPAUObject00182F70@@@Z=?j_0000315c@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0026fe90@AI00182F70@@QAEXM@Z=?j_0000ebab@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00175820@@YA_NPAUObject00182F70@@0@Z=?j_0002056d@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003edf90@Pathfinder00182F70@@QAE_NPAUObject00182F70@@PBUCoord3D@@1H@Z=?j_0004a327@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00132140@Object00182F70@@QAEPBUCoord3D@@XZ=?j_00040246@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0014ffd0@CoordCalls00182F70@@QAEAAUCoord3D@@M@Z=?j_0000e1c4@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000ec6f0@CoordCalls00182F70@@QAEAAUCoord3D@@ABU2@@Z=?j_0002f66c@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003eac80@Pathfinder00182F70@@QAEXPAUObject00182F70@@PAXPAUCoord3D@@@Z=?j_00011252@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00065c80@@YAXPAXPBD@Z=?j_0003a17a@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0027bd90@AI00182F70@@QAEXPAUCoord3D@@_N@Z=?j_0003bcff@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000c3d40@CoordCalls00182F70@@QAEAAUCoord3D@@ABU2@@Z=?j_000179ef@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000fb930@CoordCalls00182F70@@QAEXXZ=?j_0002bd82@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001bec20@Object00182F70@@QAEHXZ=?j_0003a391@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003ee850@Pathfinder00182F70@@QAEHPAUObject00182F70@@HHPBUCoord3D@@1@Z=?j_00029d7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000a2cf0@Object00182F70@@QAE_NH@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0016f150@PathCompute00182F70@@SG_NPAUCoord3D@@PAUObject00182F70@@1@Z=?j_0002255c@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001752a0@@YA_NPAUCoord3D@@PAUObject00182F70@@1@Z=?j_0001e0d3@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003e3d20@Pathfinder00182F70@@QAEXPAUObject00182F70@@@Z=?j_00015d02@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003f5c70@Pathfinder00182F70@@QAEXPAUObject00182F70@@PAXPAUCoord3D@@@Z=?j_0004029b@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0015be50@Object00182F70@@QAEMPBUCoord3D@@@Z=?j_000158b1@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000fe9b0@CoordCalls00182F70@@QBEMXZ=?j_0002ef14@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva001a7c20@Terrain00182F70@@QAEHPAUObject00182F70@@PBUCoord3D@@@Z=?j_0001c675@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva003e9720@Pathfinder00182F70@@QAEXPAUObject00182F70@@PBUCoord3D@@HPBDH@Z=?j_000294e2@@YAXXZ")

// 0016F150 consumes three stack dwords and ret 12; incoming ECX is unused.
