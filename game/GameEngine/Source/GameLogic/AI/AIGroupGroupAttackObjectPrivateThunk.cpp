class Object;
#include "../command_source_type.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
    void groupAttackObjectPrivate(bool, Object *, int, CommandSourceType);
};

void d_00155da0();

class AIGroupGroupAttackObjectPrivateShim
{
public:
    void attack(bool forced, Object *target, int maxShots, CommandSourceType source);
};

void AIGroup::groupAttackObjectPrivate(bool forced, Object *target, int maxShots, CommandSourceType source)
{
    union {
        void (*asFunction)(void);
        void (AIGroupGroupAttackObjectPrivateShim::*asMember)(bool, Object *, int, CommandSourceType);
    } targetCall;
    targetCall.asFunction = d_00155da0;
    (((AIGroupGroupAttackObjectPrivateShim *)this)->*targetCall.asMember)(
        forced, target, maxShots, source);
}
