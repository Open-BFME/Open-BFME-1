// stlport
// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0018A0F0, 118 bytes: the tunnel-network guard's copy of the
// guard "has attacked me and I can return fire" condition (Zero Hour's
// AITNGuard.cpp hasAttackedMeAndICanReturnFire), bool cdecl(State*, void*)
// with the void* unused. It is a file-static condition callback, so no name
// survives and the identity stays address-derived. Like the matched AIGuard
// copy at 0x0015C280 (Rva0015C280GuardPredicate.cpp), BFME reads the
// last-attacker slot once and never clears it; this copy also skips that
// copy's isAbleToAttack() test.
#include "../command_source_type.h"
#include "../../../Include/Common/Enums/Relationship.h"
#include "../../../Include/Common/Enums/AbleToAttackType.h"
enum CanAttackResult { ATTACKRESULT_NOT_POSSIBLE = 0, ATTACKRESULT_INVALID_SHOT = 1,
    ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2, ATTACKRESULT_POSSIBLE = 3 };
#define OBJECT_TU_MEMBERS \
    Relationship getRelationship(const Object *) const; \
    CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType, const Object *, CommandSourceType) const; \
    BodyModuleInterface *getBodyModule() const { return m_body; }
#include "../Object/object.h"
#undef OBJECT_TU_MEMBERS
#include "../../Common/Thing/GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;

// Partial BFME ABI views, as in Rva0015C280GuardPredicate.cpp: the vendor
// StateMachine uses the incompatible ZH layout. State+1C -> machine+10 is the
// machine's owner.
class StateMachine {
public:
    unsigned char m_rva0018a0f0_pad[0x10];
    Object *m_owner;
};
class State {
public:
    unsigned char m_rva0018a0f0_pad[0x1c];
    StateMachine *m_machine;
};
// Retail body interface slot +48, as in the matched AIGuard copy.
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

extern "C" bool __cdecl Rva0018A0F0Predicate(State *state, void *)
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
    CanAttackResult result = obj->getAbleToAttackSpecificObject(ATTACK_NEW_TARGET, target, CMD_FROM_AI);
    if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING) return true;
    return false;
}
