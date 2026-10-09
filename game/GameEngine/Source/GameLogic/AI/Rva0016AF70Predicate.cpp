// ?rva0016AF70@@YA_NPAVRva0016AF70State@@PAX@Z
// cl: /DNDEBUG /MD /EHsc
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum AbleToAttackType { ATTACK_TYPE_0 = 0 };
enum CanAttackResult { RESULT_2 = 2, RESULT_3 = 3 };
#include "../command_source_type.h"
class Weapon;
template<int N> class Rva0016AF70Slots : public Rva0016AF70Slots<N - 1> {
public:
    virtual void unused(char (*)[N]) = 0;
};
template<> class Rva0016AF70Slots<0> {};
class Rva0016AF70AIView : public Rva0016AF70Slots<128> {
public:
    virtual CommandSourceType getLastCommandSource() const = 0;
};
#define OBJECT_TU_MEMBERS \
    Weapon *getCurrentWeapon(WeaponSlotType *); \
    bool isAbleToAttack() const; \
    CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType, const Object *, CommandSourceType) const;
#include "../Object/object.h"
class StateMachine {
public:
    Object *getGoalObject();
    char m_pad00[0x10];
    Object *m_owner;
};
class Rva0016AF70State {
public:
    char m_pad00[0x1c];
    StateMachine *m_machine;
};
struct Rva0016AF70TemplateView {
    char m_pad00[0x533];
    bool m_533;
    bool rva0016AF70Flag() const { return m_533; }
};
struct Rva0016AF70WeaponView {
    char m_pad00[4];
    Rva0016AF70TemplateView *m_info;
    const Rva0016AF70TemplateView *getTemplate() const { return m_info; }
};
// Ported from Open BFME 2 Code/GameEngine/Source/GameLogic/AI/Rva00343F8ADispatch.cpp.
bool rva0016AF70(Rva0016AF70State *state, void *data)
{
    StateMachine *machine = state->m_machine;
    Object *owner = machine->m_owner;
    Object *goal = machine->getGoalObject();
    if (!goal || (goal->m_privateStatus & 1)) {
        Weapon *weapon = owner->getCurrentWeapon(0);
        if (weapon && ((Rva0016AF70WeaponView *)weapon)->getTemplate()->rva0016AF70Flag())
            return false;
    }
    if (owner && goal) {
        CanAttackResult result;
        if (!owner->isAbleToAttack() ||
            ((result = owner->getAbleToAttackSpecificObject(
                (AbleToAttackType)(unsigned)data, goal,
                ((const Rva0016AF70AIView *)owner->m_ai)->getLastCommandSource())) != RESULT_3 && result != RESULT_2))
            return true;
    }
    return false;
}
