// ?d_00177a90@@YAXXZ
// partial score=0.9789915966386554 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Retail RVA 0x00177A90, 952 bytes. Opaque owner: the diagnostic names the
// melee-engage state, but no original class/virtual signature is claimed.
// Layout/ABI evidence: docs/analysis/0x003e8e10.md sections 1b-1d and this
// caller's complete retail instructions. Reuses Rva0016D5F0PathTest call views.
#include "basetype.h"

extern void j_0003a17a();
extern void j_0001f253();
extern void j_00031a7f();
extern void j_0003a4e5();
extern void j_000296b8();
extern void j_0001c675();
extern void j_000294e2();
extern void j_00015d93();

class Rva00177A90Receiver {};
template<class T> __forceinline T Rva00177A90Member(void (*raw)())
{
    union { void (*raw)(); T member; } fn;
    fn.raw = raw;
    return fn.member;
}
#define CALL(T, obj, fn) (((Rva00177A90Receiver*)(obj))->*Rva00177A90Member<T>(fn))

struct Rva00177A90AIUpdate
{
    char pad00[0x140];
    void *m_path; // oracle AIUpdateInterface+140; retail +67
    char pad144[0x31e-0x144];
    bool flag31e;
    char pad31f[7];
    bool m_isBlockedAndStuck; // oracle +326; retail +33
};
struct Rva00177A90Object
{
    char pad00[0x38];
    Coord3D m_position;
    char pad44[0xbc-0x44];
    float valueBC; // 177A90+154/+15c; twice this field plus literal 60.0
    char padC0[0x204-0xc0];
    Rva00177A90AIUpdate *m_ai;
};
struct Rva00177A90Machine
{
    char pad00[0x10];
    Rva00177A90Object *m_owner;
};
class GameLogic
{
public:
    char pad00[0x3c];
    unsigned m_frame;
    char pad40[0x1a0-0x40];
    int m_desyncLogFrameCount;
};
class AI { public: char pad00[0xc]; void *m_pathfinder; };
class CRCParameterCheck;
extern GameLogic *TheBfmeGameLogic;
extern AI *TheAI;
extern CRCParameterCheck *TheCRCParameterCheck;
extern void *TheTerrainLogic;
extern bool Glo012F0239;

typedef void (__cdecl *BfmeCritterDesyncLog)(void *, const char *, ...);
typedef Rva00177A90Object* (Rva00177A90Receiver::*Rva0009A510)(int);
typedef void* (Rva00177A90Receiver::*Rva001BE230)(int*);
typedef bool (Rva00177A90Receiver::*Rva001E6930)(Rva00177A90Object*,const Coord3D*,Rva00177A90Object*,const Coord3D*,float);
typedef bool (Rva00177A90Receiver::*Rva003E8E10)(Rva00177A90Object*,void*,void*,Coord3D*,Rva00177A90Object*);
typedef int (Rva00177A90Receiver::*Rva001A7C20)(Rva00177A90Object*,const Coord3D*);
typedef void (Rva00177A90Receiver::*Rva003E9720)(Rva00177A90Object*,const Coord3D*,int,const char*,int);
typedef void (Rva00177A90Receiver::*Rva00270470)(Coord3D*);

// Authentic static helper from AIStates.cpp / ZH AIStates.cpp, not an ABI stub.
// Its TU-private register ABI must be independently byte-verified at 0016AA70.
static __declspec(noinline) Bool isSamePosition(const Coord3D *ourPos,
    const Coord3D *prevTargetPos, const Coord3D *curTargetPos)
{
    Coord3D diff;
    diff.x = curTargetPos->x - prevTargetPos->x;
    diff.y = curTargetPos->y - prevTargetPos->y;
    Coord3D toTarget;
    toTarget.x = curTargetPos->x - ourPos->x;
    toTarget.y = curTargetPos->y - ourPos->y;
    const Real TOLERANCE_FACTOR = 1.0f / (10.0f * 10.0f);
    Real toleranceSqr = (toTarget.x*toTarget.x+toTarget.y*toTarget.y) * TOLERANCE_FACTOR;
    if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
        return false;
    return true;
}


extern void j_0000e570();
extern void j_00027bc9();
extern void j_0002056d();
extern void j_00040246();
extern void j_0000e1c4();
extern void j_0002f66c();
extern void j_00011252();
extern void j_0003bcff();
extern void j_0001e0d3();
extern void j_00027ffc();
typedef Rva00177A90Object* (Rva00177A90Receiver::*Rva000A1490)();
typedef void (Rva00177A90Receiver::*Rva001C0010)(Coord3D*);
typedef const Coord3D* (Rva00177A90Receiver::*Rva00132140)();
typedef Coord3D& (Rva00177A90Receiver::*Rva0014FFD0)(float);
typedef Coord3D& (Rva00177A90Receiver::*Rva000EC6F0)(const Coord3D&);
typedef void (Rva00177A90Receiver::*Rva003EAC80)(Rva00177A90Object*,void*,Coord3D*);
typedef void (Rva00177A90Receiver::*Rva0027BD90)(Coord3D*,bool);
typedef void (Rva00177A90Receiver::*Rva003F6090)(Rva00177A90Object*,void*,Coord3D*,bool);
typedef bool (__cdecl *Rva00175820)(Rva00177A90Object*,Rva00177A90Object*);
typedef bool (__cdecl *Rva001752A0)(Coord3D*,Rva00177A90Object*,Rva00177A90Object*);

class Rva00177A90MeleePath
{
public:
    bool computePath();
    char pad00[0x1c];
    Rva00177A90Machine *m_machine;
    char pad20[4];
    Coord3D m_goalPosition;
    char pad30[0x4c-0x30];
    bool m_adjustDestinations; // oracle AIInternalMoveToState+4c
    bool flag4d;
    char pad4e[0x58-0x4e];
    unsigned frame58;
    Coord3D position5c;
    char pad68[8];
    unsigned frame70;
    bool flag74;
    bool flag75;
};

bool Rva00177A90MeleePath::computePath()
{
    if (Glo012F0239 && TheCRCParameterCheck)
        ((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
            "CritterDesync: ComputePath26");
    bool forceRepath = false;
    Rva00177A90AIUpdate *ai = m_machine->m_owner->m_ai;
    if (ai->m_isBlockedAndStuck)
        return false;
    if (flag4d)
    {
        if (ai->m_path || ai->flag31e)
            return true;
        flag4d = false;
    }
    if (!ai->m_path && !ai->flag31e)
        forceRepath = true;
    if (!forceRepath && TheBfmeGameLogic->m_frame - frame58 < 5)
        return true;
    frame58 = TheBfmeGameLogic->m_frame;
    if (CALL(Rva000A1490,m_machine,j_0000e570)())
    {
        Rva00177A90Object *source = m_machine->m_owner;
        if (!forceRepath && isSamePosition(&source->m_position,&position5c,
            &CALL(Rva000A1490,m_machine,j_0000e570)()->m_position))
            return true;
        void *weapon = CALL(Rva001BE230,source,j_00031a7f)(0);
        if (!weapon)
            return false;
        Rva00177A90Object *victim = CALL(Rva000A1490,m_machine,j_0000e570)();
        Coord3D position;
        position.x = victim->m_position.x;
        position.y = victim->m_position.y;
        position.z = victim->m_position.z;
        CALL(Rva001C0010,victim,j_00027bc9)(&position);
        position5c = position;
        if (((Rva00175820)j_0002056d)(source,victim))
        {
            Coord3D direction = *CALL(Rva00132140,victim,j_00040246)();
            CALL(Rva0014FFD0,&direction,j_0000e1c4)(2.0f*victim->valueBC + 60.0f);
            m_goalPosition = position;
            CALL(Rva000EC6F0,&m_goalPosition,j_0002f66c)(direction);
            CALL(Rva003EAC80,TheAI->m_pathfinder,j_00011252)(source,(char*)ai+0x1a8,&m_goalPosition);
            if (Glo012F0239 && TheCRCParameterCheck)
                ((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
                    "CritterDesync: setAdjustDestination(FALSE) 34");
            m_adjustDestinations = false;
            CALL(Rva0027BD90,ai,j_0003bcff)(&m_goalPosition,false);
            flag4d = ai->flag31e;
            if (ai->m_path)
                flag4d = false;
            return true;
        }
        if (TheBfmeGameLogic->m_desyncLogFrameCount > 0 && !forceRepath && TheCRCParameterCheck)
            ((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
                "masiwar called by AIAttackMeleeEngageState::computePath [1]");
        if (!forceRepath && CALL(Rva001E6930,weapon,j_0003a4e5)(source,&m_goalPosition,victim,&position5c,0.0f))
            return true;
        if (TheBfmeGameLogic->m_desyncLogFrameCount > 0 && TheCRCParameterCheck)
            ((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
                "AIAttackFireDuringApproachState::computePath[2] will call FindMeleeEngagmentLocation with %f,%f (m_goalPosition:%f,%f = m_prevVictimPosition:%f, %f;)",
                (double)m_goalPosition.x,(double)m_goalPosition.y,
                (double)m_goalPosition.x,(double)m_goalPosition.y,
                (double)position5c.x,(double)position5c.y);
        m_goalPosition = position5c;
        void *finder = TheAI->m_pathfinder;
        flag75 = !CALL(Rva003E8E10,finder,j_000296b8)(source,weapon,(char*)ai+0x1a8,&m_goalPosition,victim);
        if (flag75)
        {
            m_goalPosition = position5c;
            if (((Rva001752A0)j_0001e0d3)(&m_goalPosition,source,victim))
            {
                CALL(Rva003F6090,TheAI->m_pathfinder,j_00027ffc)(source,(char*)ai+0x1a8,&m_goalPosition,false);
                CALL(Rva0027BD90,ai,j_0003bcff)(&m_goalPosition,true);
                return true;
            }
            flag74 = true;
            frame70 = TheBfmeGameLogic->m_frame + 50;
            return true;
        }
        void *pathfinder = TheAI->m_pathfinder;
        CALL(Rva003E9720,pathfinder,j_000294e2)(source,&m_goalPosition,
            CALL(Rva001A7C20,TheTerrainLogic,j_0001c675)(source,&m_goalPosition),
            (const char*)0x0109769c,0x1c38);
        CALL(Rva0027BD90,ai,j_0003bcff)(&m_goalPosition,true);
        flag4d = ai->flag31e;
        return true;
    }
    return false;
}
