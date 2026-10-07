// stlport
// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0015C280, 129 bytes. The guard constructor condition table
// proves bool cdecl(State*, void*); keep its existing address-derived identity.
// Unlike Zero Hour, BFME calls the last-attacker slot once and never clears it.
// Evidence: identity_evidence/0015c280-native-guard-predicate.md.
#include "../command_source_type.h"
enum Relationship { ENEMIES = 0 };
enum AbleToAttackType { ATTACK_NEW_TARGET = 0 };
enum CanAttackResult { ATTACKRESULT_NOT_POSSIBLE = 0, ATTACKRESULT_INVALID_SHOT = 1,
    ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2, ATTACKRESULT_POSSIBLE = 3 };
#define OBJECT_TU_MEMBERS \
    Relationship getRelationship(const Object *) const; \
    bool isAbleToAttack() const; \
    CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType, const Object *, CommandSourceType) const; \
    BodyModuleInterface *getBodyModule() const { return m_body; }
#include "../Object/object.h"
#undef OBJECT_TU_MEMBERS
#include "../../Common/Thing/GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;

// Partial BFME ABI views: vendor StateMachine uses the incompatible ZH layout.
// State+1C -> machine+10 is independently consumed by the guard constructor
// callback table and the matched AIExitState::onExit. No shared header changes.
class StateMachine {
public:
    unsigned char m_rva0015c280_pad[0x10];
    Object *m_owner;
};
class State {
public:
    unsigned char m_rva0015c280_pad[0x1c];
    StateMachine *m_machine;
};
// Retail body interface slot +48, as in matched guard-retaliate return update.
class BodyModuleInterface {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual ObjectID getClearableLastAttacker() const;
};

extern "C" bool __cdecl Rva0015C280Predicate(State *state, void *)
{
    Object *obj = state->m_machine->m_owner;
    BodyModuleInterface *body = obj ? obj->getBodyModule() : 0;
    if (!(obj && body)) return false;
    ObjectID attacker = body->getClearableLastAttacker();
    if (attacker == 0) return false;
    Object *target = TheGameLogic->findObjectByID(attacker);
    if (!target) return false;
    if (obj->getRelationship(target) != ENEMIES) return false;
    if (((target->m_privateStatus & 1) != 0)) return false;
    if (!obj->isAbleToAttack()) return false;
    CanAttackResult result = obj->getAbleToAttackSpecificObject(ATTACK_NEW_TARGET, target, CMD_FROM_AI);
    if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING) return true;
    return false;
}
