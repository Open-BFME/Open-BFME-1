// ?computePath@AIAttackMeleeApproachState@@MAE_NXZ
// partial score=0.975 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// ?computePath@AIAttackMeleeApproachState@@MAE_NXZ
// Retail 00176A50; identity evidence: 00176a50-meleeapproach-computepath.md.
#include "basetype.h"

inline __declspec(noinline) float __fastcall Rva000B6CA0Length(const Coord3D *position)
{
    return (float)sqrt(position->x*position->x + position->y*position->y + position->z*position->z);
}

extern void j_0003a17a();
extern void j_0000e570();
extern void j_00031a7f();
extern void j_000420aa();
extern void j_0003bcff();
extern void j_0002fe0f();
extern void j_0003251f();
extern void j_0002056d();
extern void j_00040246();
extern void j_0000e1c4();
extern void j_0002f66c();
extern void j_0003a391();
extern void j_0002ae23();
extern void j_0002fc7a();
extern void j_00048112();
extern void j_0003bff7();
extern void j_000126b6();
extern void j_0002bd82();
extern void j_0003ce25();
extern void j_000233ee();
extern void j_0003e423();

class Rva00176A50Receiver {};
template<class T> __forceinline T Rva00176A50Member(void (*raw)())
{
    union { void (*raw)(); T member; } fn;
    fn.raw = raw;
    return fn.member;
}
#define CALL(T, obj, fn) (((Rva00176A50Receiver*)(obj))->*Rva00176A50Member<T>(fn))

struct Rva00176A50AIUpdate
{
    char pad00[0x140];
    void *m_path;
    char pad144[0x31e-0x144];
    bool m_waitingForPath;
    char pad31f[7];
    bool m_isBlockedAndStuck;
};
struct Rva00176A50Object
{
    char pad00[0x38];
    Coord3D m_cachedPos;
    char pad44[0xbc-0x44];
    float valueBC;
    char padC0[0x204-0xc0];
    Rva00176A50AIUpdate *m_ai;
    const Coord3D *getPosition() const { return &m_cachedPos; }
};
struct Rva00176A50Machine
{
    char pad00[0x10];
    Rva00176A50Object *m_owner;
};
class GameLogic { public: char pad00[0x3c]; unsigned m_field3C; };
struct Rva00176A50AIData { char pad00[0x90]; float field90, field94; };
class AI
{
public:
    char pad00[0xc];
    void *m_pathfinder;
    char pad10[4];
    Rva00176A50AIData *m_data;
};
class CRCParameterCheck;
extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;
enum NameKeyType {};
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;

typedef void (__cdecl *BfmeCritterDesyncLog)(void *, const char *, ...);
typedef Rva00176A50Object* (Rva00176A50Receiver::*Rva000A1490)();
typedef void* (Rva00176A50Receiver::*Rva001BE230)(int*);
typedef bool (Rva00176A50Receiver::*Rva001CC790)(Rva00176A50Object*,int);
typedef void (Rva00176A50Receiver::*Rva0027BD90)(Coord3D*,bool);
typedef float (Rva00176A50Receiver::*Rva000B6CA0)() const;
typedef bool (Rva00176A50Receiver::*Rva000A2CF0)(int) const;
typedef bool (__cdecl *Rva00175820)(Rva00176A50Object*,Rva00176A50Object*);
typedef const Coord3D* (Rva00176A50Receiver::*Rva00132140)() const;
typedef Coord3D& (Rva00176A50Receiver::*Rva0014FFD0)(float);
typedef Coord3D& (Rva00176A50Receiver::*Rva000EC6F0)(const Coord3D&);
typedef int (Rva00176A50Receiver::*Rva001BEC20)() const;
typedef void* (Rva00176A50Receiver::*Rva001BEE60)(NameKeyType) const;
typedef void* (__cdecl *Rva001F8AB0)(Rva00176A50Object*);
typedef bool (Rva00176A50Receiver::*Rva00266340)() const;
typedef bool (Rva00176A50Receiver::*Rva001F9180)(Coord3D*);
typedef Coord3D& (Rva00176A50Receiver::*Rva0016A240)(const Coord3D&);
typedef void (Rva00176A50Receiver::*Rva000FB930)();
typedef bool (Rva00176A50Receiver::*Rva003D8BC0)(const Coord3D*,bool);
typedef Coord3D& (Rva00176A50Receiver::*Rva00148730)(const Coord3D&);
typedef bool (Rva00176A50Receiver::*Rva002705D0)(const Coord3D*,bool);

// ?isSamePosition@@YA_NPBUCoord3D@@00@Z
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

template<int N> class Rva00176A50Slots : public Rva00176A50Slots<N-1> {
public: virtual void unused(char (*)[N]) = 0;
};
template<> class Rva00176A50Slots<0> {};
class AIAttackMeleeApproachState : public Rva00176A50Slots<17>
{
public:
    char pad004[0x1c-4];
    Rva00176A50Machine *m_machine;
    char pad20[4];
    Coord3D m_goalPosition;
    char pad30[0x4c-0x30];
    bool m_adjustDestinations;
    bool m_waitingForPath;
    char pad4e[2];
    unsigned frame50;
    Coord3D position54;
protected:
    virtual Bool computePath();
    __forceinline void setGoalAlongDirection00176A50(const Coord3D *directionVector, Rva00176A50Object *targetObject);
};

__forceinline void AIAttackMeleeApproachState::setGoalAlongDirection00176A50(const Coord3D *directionVector, Rva00176A50Object *targetObject)
{
    Coord3D direction = *directionVector;
    CALL(Rva0014FFD0,&direction,j_0000e1c4)(2.0f*targetObject->valueBC + 60.0f);
    m_goalPosition = position54;
    CALL(Rva000EC6F0,&m_goalPosition,j_0002f66c)(direction);
}

Bool AIAttackMeleeApproachState::computePath()
{
    if (Glo012F0239 && TheCRCParameterCheck)
        ((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,"CritterDesync: ComputePath18");
    bool forceRepath = false;
    Rva00176A50AIUpdate *ai = m_machine->m_owner->m_ai;
    if (ai->m_isBlockedAndStuck)
        return false;
    if (m_waitingForPath)
        return true;
    if (!ai->m_path && !ai->m_waitingForPath)
        forceRepath = true;
    else if (TheGameLogic->m_field3C - frame50 < 5)
        return true;
    frame50 = TheGameLogic->m_field3C;
    if (CALL(Rva000A1490,m_machine,j_0000e570)())
    {
        Rva00176A50Object *source = m_machine->m_owner;
        if (!forceRepath && isSamePosition(source->getPosition(),&position54,
            CALL(Rva000A1490,m_machine,j_0000e570)()->getPosition()))
            return true;
        void *weapon = CALL(Rva001BE230,source,j_00031a7f)(0);
        if (!weapon)
            goto fail;
        Rva00176A50Object *victim = CALL(Rva000A1490,m_machine,j_0000e570)();
        position54 = *victim->getPosition();
        if (CALL(Rva001CC790,source,j_000420aa)(victim,2))
        {
            m_goalPosition = position54;
            CALL(Rva0027BD90,ai,j_0003bcff)(&m_goalPosition,false);
            return true;
        }
        const Rva00176A50AIData *data = TheAI->m_data;
        Coord3D direction;
        direction.set(source->getPosition()->x,source->getPosition()->y,0.0f);
        direction.x -= position54.x;
        direction.y -= position54.y;
        if (Rva000B6CA0Length(&direction) < data->field90 + data->field94)
            goto fail;
        if (CALL(Rva000A2CF0,victim,j_0003251f)(0x95))
            goto fail;
        if (((Rva00175820)j_0002056d)(source,victim))
        {
            setGoalAlongDirection00176A50(CALL(Rva00132140,victim,j_00040246)(),victim);
            if (Glo012F0239 && TheCRCParameterCheck)
                ((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,"CritterDesync: setAdjustDestination(FALSE) 30");
            m_adjustDestinations = false;
            CALL(Rva0027BD90,ai,j_0003bcff)(&m_goalPosition,false);
        }
        else
        {
        void *module = 0;
        void *portal = 0;
        if (CALL(Rva000A2CF0,victim,j_0003251f)(0x5c) && CALL(Rva001BEC20,source,j_0003a391)() != 1)
        {
            static const NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
            module = CALL(Rva001BEE60,victim,j_0002ae23)(key);
            portal = ((Rva001F8AB0)j_0002fc7a)(victim);
            if (module && !CALL(Rva00266340,module,j_00048112)())
                module = 0;
        }
        bool adjusted = false;
        if (module && portal && CALL(Rva001F9180,portal,j_0003bff7)(&m_goalPosition))
        {
            direction = m_goalPosition;
            CALL(Rva0016A240,&direction,j_000126b6)(position54);
            adjusted = true;
        }
        CALL(Rva000FB930,&direction,j_0002bd82)();
        CALL(Rva0014FFD0,&direction,j_0000e1c4)(victim->valueBC);
        m_goalPosition = position54;
        CALL(Rva000EC6F0,&m_goalPosition,j_0002f66c)(direction);
        if (adjusted)
        {
            for (int i=0; i<10; ++i)
            {
                if (CALL(Rva003D8BC0,TheAI->m_pathfinder,j_0003ce25)(&m_goalPosition,false))
                    break;
                CALL(Rva00148730,&m_goalPosition,j_000233ee)(direction);
            }
        }
        if (CALL(Rva002705D0,ai,j_0003e423)(&m_goalPosition,adjusted))
        {
            m_waitingForPath = ai->m_waitingForPath;
            return true;
        }
        }
        m_waitingForPath = ai->m_waitingForPath;
    }
fail:
    return false;
}
