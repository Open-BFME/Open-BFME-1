class Object;
enum CommandSourceType
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
    void groupAttackObjectPrivate(bool, Object *, int, CommandSourceType);
};

class AIGroupGroupAttackObjectPrivateShim
{
public:
    void attack(bool forced, Object *target, int maxShots, CommandSourceType source);
};

void AIGroup::groupAttackObjectPrivate(bool forced, Object *target, int maxShots, CommandSourceType source)
{
    ((AIGroupGroupAttackObjectPrivateShim *)this)->attack(forced, target, maxShots, source);
}
