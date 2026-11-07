// ?computePath@AIAttackMeleeApproachState@@MAE_NXZ
// partial score=0.9981 date=2026-11-07
// ?computePath@AIAttackMeleeApproachState@@MAE_NXZ
// partial 2/1041 non-reloc bytes differ (residue: 0xAE frame-store register eax vs edx)
// cl: /DNDEBUG /MD /EHsc /Ob1 /Igame/Libraries/Source/WWVegas/WWMath
// AIAttackMeleeApproachState::computePath, retail RVA 0x00176A50 (1041 bytes);
// identity: targets/game/reverse/identity_evidence/00176a50-aiattackmeleeapproachstate-computepath.md
// /Ob1 and the WWMath include follow the matched sibling of the same class,
// AIAttackMeleeApproachState_onEnter.cpp.
// The Coord3D members the body calls (length, normalize, Scale, Add, -=, +=)
// have visible noinline bodies: VC7.1 then proves `direction` never escapes,
// shares one 12-byte slot for every direction value (retail sub esp,0x1C) and
// schedules the unit-direction copy around the x87 radius math as retail does.
// The two position54 -> m_goalPosition copies before Add are plain word copies:
// retail copies Coord3D with the implicit (exported ??4Coord3D@@QAEAAV0@ABV0@@Z)
// block copy, which keeps both lvalues this-relative; an inlined user
// operator= hides that and serialises the loads.
#include "coord3d.h"
#include <math.h>
typedef bool Bool;
typedef float Real;
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
__forceinline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &p) {
    struct Raw { unsigned x,y,z; }; *(Raw*)this=*(const Raw*)&p; return *this;
}
__forceinline Coord3D &Coord3D::operator=(const Coord3D &p) { Coord3DBase *base=this; *base=p; return *this; }
inline Coord3D::Coord3D(const Coord3D &p) { x=p.x; y=p.y; z=p.z; }
inline void Coord3D::set(float ax, float ay, float az) { x=ax; y=ay; z=az; }
inline Coord3D &Coord3D::Sub2D(const Coord3DBase &p) {x-=p.x; y-=p.y; return *this;}
inline __declspec(noinline) float Coord3D::length() const { return (float)sqrt(x*x+y*y+z*z); }
inline __declspec(noinline) void Coord3D::normalize() {
 float len=(float)sqrt(x*x+y*y+z*z);
 if(len != 0.0f) { float scale=1.0f/len; x*=scale; y*=scale; z*=scale; }
}
inline __declspec(noinline) Coord3D &Coord3D::Scale(float scale) { x*=scale; y*=scale; z*=scale; return *this; }
inline __declspec(noinline) Coord3D &Coord3D::Add(const Coord3DBase &that) { x+=that.x; y+=that.y; z+=that.z; return *this; }
inline __declspec(noinline) Coord3D &Coord3D::operator-=(const Coord3DBase &that) { x-=that.x; y-=that.y; z-=that.z; return *this; }
inline __declspec(noinline) Coord3D &Coord3D::operator+=(const Coord3DBase &that) { x+=that.x; y+=that.y; z+=that.z; return *this; }


enum NameKeyType {};
enum KindOfType { KINDOF_5C = 0x5c, KINDOF_95 = 0x95 };
enum CrushSquishTestType { TEST_CRUSH_ONLY, TEST_SQUISH_ONLY, TEST_CRUSH_OR_SQUISH };
enum WeaponSlotType;
class Weapon;
class Module { public: bool is() const; };
class DynamicPortalBehaviour { public: bool isEndPortalAboveWall(Coord3D *pos); };
class Pathfinder { public: bool bfmeGroundCellThreshold(const Coord3D *pos, bool flag); };
class AIUpdateInterface
{
public:
    void requestPath(Coord3D *destination, bool isFinalGoal);
    bool requestMeleeApproachPath(Coord3D *destination, bool adjusted);
    bool isBlockedAndStuck() const { return m_isBlockedAndStuck; }
    void *getPath() const { return m_path; }
    bool isWaitingForPath() const { return m_waitingForPath; }
    char pad00[0x140];
    void *m_path;
    char pad144[0x31e-0x144];
    bool m_waitingForPath;
    char pad31f[7];
    bool m_isBlockedAndStuck;
};
class Thing
{
public:
    bool isKindOf(KindOfType kind) const;
    const Coord3D *getUnitDirectionVector2D() const;
    const Coord3D *getPosition() const { return &m_cachedPos; }
    char pad00[0x38];
    Coord3D m_cachedPos;
};
class Object : public Thing
{
public:
    Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
    bool crushPolicy(Object *victim, CrushSquishTestType test) const;
    int bfmeScale() const;
    Module *findModule(NameKeyType key) const;
    AIUpdateInterface *getAI() const { return m_ai; }
    char pad44[0xbc-0x44];
    float valueBC;
    char padC0[0x204-0xc0];
    AIUpdateInterface *m_ai;
};
class StateMachine
{
public:
    Object *getGoalObject();
    char pad00[0x10];
    Object *m_owner;
};
class GameLogic { public: unsigned getFrame() const { return m_field3C; } char pad00[0x3c]; unsigned m_field3C; };
struct TAiData { char pad00[0x90]; float field90, field94; };
class AI
{
public:
    char pad00[0xc];
    Pathfinder *m_pathfinder;
    char pad10[4];
    TAiData *m_data;
    const TAiData *getAiData() const { return m_data; }
};
class CRCParameterCheck;
extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *check, const char *format, ...);
bool bfmeMeleeHordeTargetInvalid(Object *source, Object *victim);
DynamicPortalBehaviour *rva001F8AB0(Object *obj);
struct CoordWords { float x,y,z; };

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
    StateMachine *m_machine;
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
};

Bool AIAttackMeleeApproachState::computePath()
{
    if (Glo012F0239 && TheCRCParameterCheck)
        bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"CritterDesync: ComputePath18");
    bool forceRepath = false;
    AIUpdateInterface *ai = m_machine->m_owner->m_ai;
    if (ai->m_isBlockedAndStuck)
        return false;
    if (m_waitingForPath)
        return true;
    if (!ai->m_path && !ai->m_waitingForPath)
        forceRepath = true;
    else if (TheGameLogic->m_field3C - frame50 < 5)
        return true;
    frame50 = TheGameLogic->m_field3C;
    if (m_machine->getGoalObject())
    {
        Object *source = m_machine->m_owner;
        if (!forceRepath && isSamePosition(source->getPosition(),&position54,
            m_machine->getGoalObject()->getPosition()))
            return true;
        Weapon *weapon = source->getCurrentWeapon();
        if (!weapon)
            goto fail;
        Object *victim = m_machine->getGoalObject();
        position54 = *victim->getPosition();
        if (source->crushPolicy(victim,TEST_CRUSH_OR_SQUISH))
        {
            m_goalPosition = position54;
            ai->requestPath(&m_goalPosition,false);
            return true;
        }
        const TAiData *data = TheAI->m_data;
        Coord3D direction(*source->getPosition());
        direction.Sub2D(position54);
        direction.z = 0.0f;
        if (direction.length() < TheAI->m_data->field90 + data->field94)
            goto fail;
        if (victim->isKindOf(KINDOF_95))
            goto fail;
        if (bfmeMeleeHordeTargetInvalid(source,victim))
        {
            direction = *victim->getUnitDirectionVector2D();
            direction.Scale(2.0f*victim->valueBC + 60.0f);
            *(CoordWords*)&m_goalPosition = *(const CoordWords*)&position54;
            m_goalPosition.Add(direction);
            if (Glo012F0239 && TheCRCParameterCheck)
                bfmeRetailCritterDesyncLog(TheCRCParameterCheck,"CritterDesync: setAdjustDestination(FALSE) 30");
            m_adjustDestinations = false;
            ai->requestPath(&m_goalPosition,false);
        }
        else
        {
        Module *module = 0;
        DynamicPortalBehaviour *portal = 0;
        if (victim->isKindOf(KINDOF_5C) && source->bfmeScale() != 1)
        {
            static const NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
            module = victim->findModule(key);
            portal = rva001F8AB0(victim);
            if (module && !module->is())
                module = 0;
        }
        bool adjusted = false;
        if (module && portal && portal->isEndPortalAboveWall(&m_goalPosition))
        {
            direction = m_goalPosition;
            direction -= position54;
            adjusted = true;
        }
        direction.normalize();
        direction.Scale(victim->valueBC);
        *(CoordWords*)&m_goalPosition = *(const CoordWords*)&position54;
        m_goalPosition.Add(direction);
        if (adjusted)
        {
            for (int i=0; i<10; ++i)
            {
                if (TheAI->m_pathfinder->bfmeGroundCellThreshold(&m_goalPosition,false))
                    break;
                m_goalPosition += direction;
            }
        }
        if (ai->requestMeleeApproachPath(&m_goalPosition,adjusted))
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
