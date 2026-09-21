// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Retail RVA 0x00170680, 545 bytes. Opaque owner: the diagnostic names the
// fire-during-approach state, but no original class/virtual signature is claimed.
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

class Rva00170680Receiver {};
template<class T> __forceinline T Rva00170680Member(void (*raw)())
{
    union { void (*raw)(); T member; } fn;
    fn.raw = raw;
    return fn.member;
}
#define CALL(T, obj, fn) (((Rva00170680Receiver*)(obj))->*Rva00170680Member<T>(fn))

struct Rva00170680AIUpdate
{
    char pad00[0x140];
    void *m_path; // oracle AIUpdateInterface+140; retail +67
    char pad144[0x31e-0x144];
    bool flag31e;
    char pad31f[7];
    bool m_isBlockedAndStuck; // oracle +326; retail +33
};
struct Rva00170680Object
{
    char pad00[0x38];
    Coord3D m_position;
    char pad44[0x204-0x44];
    Rva00170680AIUpdate *m_ai;
};
struct Rva00170680Machine
{
    char pad00[0x10];
    Rva00170680Object *m_owner;
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
typedef Rva00170680Object* (Rva00170680Receiver::*Rva0009A510)(int);
typedef void* (Rva00170680Receiver::*Rva001BE230)(int*);
typedef bool (Rva00170680Receiver::*Rva001E6930)(Rva00170680Object*,const Coord3D*,Rva00170680Object*,const Coord3D*,float);
typedef bool (Rva00170680Receiver::*Rva003E8E10)(Rva00170680Object*,void*,void*,Coord3D*,Rva00170680Object*);
typedef int (Rva00170680Receiver::*Rva001A7C20)(Rva00170680Object*,const Coord3D*);
typedef void (Rva00170680Receiver::*Rva003E9720)(Rva00170680Object*,const Coord3D*,int,const char*,int);
typedef void (Rva00170680Receiver::*Rva00270470)(Coord3D*);

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

class Rva00170680ApproachPath
{
public:
    bool computePath();
    char pad00[0x1c];
    Rva00170680Machine *m_machine;
    char pad20[4];
    Coord3D m_goalPosition;
    char pad30[0x4d-0x30];
    bool flag4d;
    char pad4e[2];
    unsigned frame50;
    Coord3D position54;
    char pad60[8];
    int objectID68;
};

bool Rva00170680ApproachPath::computePath()
{
    if (Glo012F0239 && TheCRCParameterCheck)
        ((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
            "CritterDesync: ComputePath15");
    bool forceRepath = false;
    Rva00170680Machine *machine = m_machine;
    Rva00170680AIUpdate *ai = machine->m_owner->m_ai;
    if (ai->m_isBlockedAndStuck)
        return false;
    if (flag4d && ai->flag31e)
        return true;
    if (!ai->m_path && !ai->flag31e)
        forceRepath = true;
    if (!forceRepath && TheBfmeGameLogic->m_frame - frame50 < 5)
        return true;
    frame50 = TheBfmeGameLogic->m_frame;
    Rva00170680Object *victim = CALL(Rva0009A510,TheBfmeGameLogic,j_0001f253)(objectID68);
    if (victim)
    {
        Rva00170680Object *source = machine->m_owner;
        if (!forceRepath && isSamePosition(&source->m_position,&position54,&victim->m_position))
            return true;
        void *weapon = CALL(Rva001BE230,source,j_00031a7f)(0);
        if (!weapon)
            return false;
        position54 = victim->m_position;
        if (TheBfmeGameLogic->m_desyncLogFrameCount > 0 && !forceRepath && TheCRCParameterCheck)
            ((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
                "masiwar called by AIAttackFireDuringApproachState::computePath [1]");
        if (!forceRepath && CALL(Rva001E6930,weapon,j_0003a4e5)(source,&m_goalPosition,victim,&position54,0.0f))
            return true;
        m_goalPosition = position54;
        if (TheBfmeGameLogic->m_desyncLogFrameCount > 0 && TheCRCParameterCheck)
            ((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
                "AIAttackFireDuringApproachState::computePath will call FindMeleeEngagmentLocation with m_goalPosition=%f,%f",
                (double)m_goalPosition.x,(double)m_goalPosition.y);
        CALL(Rva003E8E10,TheAI->m_pathfinder,j_000296b8)(source,weapon,(char*)ai+0x1a8,&m_goalPosition,victim);
        void *pathfinder = TheAI->m_pathfinder;
        CALL(Rva003E9720,pathfinder,j_000294e2)(source,&m_goalPosition,
            CALL(Rva001A7C20,TheTerrainLogic,j_0001c675)(source,&m_goalPosition),
            (const char*)0x0109769c,0x1812);
        CALL(Rva00270470,ai,j_00015d93)(&m_goalPosition);
        flag4d = ai->flag31e;
        return true;
    }
    return false;
}
