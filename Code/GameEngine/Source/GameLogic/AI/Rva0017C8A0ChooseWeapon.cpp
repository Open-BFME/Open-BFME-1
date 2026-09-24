// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /MD /EHsc
// BFME state helper at retail RVA 0x0017C8A0. The owning state class is not
// recovered, so it carries an address-derived name. The layouts below are the
// ones AIIdleState_update.cpp already uses for the same objects.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum MoodMatrixAction
{
	MM_ACTION_ATTACK = 2
};

enum WeaponChoiceCriteria
{
	PREFER_MOST_DAMAGE = 0
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class Object;
class AIUpdateInterface;

class StateMachine
{
public:
	Object *getGoalObject();

	unsigned char m_padding000[0x10];
	Object *m_owner;
};

#define OBJECT_TU_MEMBERS \
	Bool chooseBestWeaponForTarget(const Object *target, WeaponChoiceCriteria criteria, CommandSourceType cmdSource);
#include "../Object/object.h"

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<128>
{
public:
	virtual CommandSourceType getLastCommandSource() const = 0;

	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
};

class Rva0017C8A0State
{
public:
	StateReturnType chooseWeapon();

	unsigned char m_padding000[0x1C];
	StateMachine *m_machine;
};

StateReturnType Rva0017C8A0State::chooseWeapon()
{
	Object *source = m_machine->m_owner;
	Object *victim = m_machine->getGoalObject();
	AIUpdateInterface *ai = source->m_ai;

	if ((ai->getMoodMatrixActionAdjustment(MM_ACTION_ATTACK) & 1) != 0 &&
		victim != 0 &&
		!source->chooseBestWeaponForTarget(victim, PREFER_MOST_DAMAGE,
			ai->getLastCommandSource()))
	{
		return STATE_FAILURE;
	}

	return STATE_SUCCESS;
}
