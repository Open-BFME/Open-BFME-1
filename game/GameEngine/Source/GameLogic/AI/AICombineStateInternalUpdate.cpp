// ?internalUpdate@AICombineState@@IAE?AW4StateReturnType@@XZ
// cl: /DNDEBUG /MD /EHsc
//
// AICombineState::internalUpdate, retail 0x0016F340 (238 B, two RET exits).
// BFME 1 identity: ILT 0x00037E34 is the only route to the body (callers
// 0x0017DA83 and 0x0017DB13), and tools/ilt_oracle.py CONFIRMS the protected
// ?internalUpdate@AICombineState@@IAE?AW4StateReturnType@@XZ there (1848
// AICombine*/method/access spellings tried, this one alone). Donor:
// open-bfme-2 b5a7b8290 Code/GameEngine/Source/GameLogic/AI/
// AICombineStateInternalUpdate.cpp (232 B there); its nested-if control flow
// is kept verbatim and is what places retail's failure exit last. BFME 1
// offsets are retail's own: state machine +0x1C, goal position +0x24, machine
// owner +0x10, Object position +0x38, contain +0x1FC, AI +0x204 (command
// source at vtable +0x200), flags byte +0x344; contain vtable +0x68 yields the
// horde interface, whose +0xF4 gives the combine target and +0x70 combines.
#include <math.h>

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

template <int N> class Slots : public Slots<N - 1> { public: virtual void gap(char (*)[N]); };
template <> class Slots<0> {};

class AIUpdateInterface : public Slots<128>
{
public:
	virtual CommandSourceType getLastCommandSource();
};

class HordeContainInterface : public Slots<28>
{
public:
	virtual void combine(Object *other, void *target, bool flag);
	virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
	virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38();
	virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48();
	virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
	virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58();
	virtual void s59(); virtual void s60();
	virtual void *getCombineTarget();
};

class ContainModuleInterface : public Slots<26>
{
public:
	virtual HordeContainInterface *getHordeContainInterface();
};

class Object
{
public:
	float getDistanceSquared(const Object *other) const;
	bool cannotCombine() const { return (m_flags344 & 1) != 0; }

	char pad000[0x38];
	Coord3D m_position;
	char pad044[0x1FC - 0x44];
	ContainModuleInterface *m_contain;
	char pad200[4];
	AIUpdateInterface *m_ai;
	char pad208[0x344 - 0x208];
	unsigned char m_flags344;
};

class StateMachine
{
public:
	Object *getGoalObject();
	char pad[0x10];
	Object *m_owner;
};

class BFMEActionManager
{
public:
	bool rva000C4080(const Object *obj, const Object *target, CommandSourceType source);
};
extern BFMEActionManager *TheActionManager;

class AICombineState
{
public:
	virtual ~AICombineState();
protected:
	StateReturnType internalUpdate();
private:
	char pad04[0x1C - 4];
	StateMachine *m_machine;
	char pad20[4];
	Coord3D m_goalPosition;
};

StateReturnType AICombineState::internalUpdate()
{
	Object *owner = m_machine->m_owner;
	Object *goal = m_machine->getGoalObject();
	if (owner->cannotCombine())
		return STATE_FAILURE;
	if (goal)
	{
		if (goal->cannotCombine())
			return STATE_FAILURE;
		if (!TheActionManager->rva000C4080(owner, goal, owner->m_ai->getLastCommandSource()))
			return STATE_FAILURE;
		m_goalPosition = goal->m_position;
		float distance = owner->getDistanceSquared(goal);
		if (2500.0f > distance)
		{
			float height = (float)fabs(goal->m_position.z - owner->m_position.z);
			if (height < 10.0f)
			{
				HordeContainInterface *horde = 0;
				Object *other = goal;
				ContainModuleInterface *contain = owner->m_contain;
				if (contain)
					horde = contain->getHordeContainInterface();
				if (!horde)
				{
					ContainModuleInterface *otherContain = goal->m_contain;
					if (otherContain)
					{
						horde = otherContain->getHordeContainInterface();
						other = owner;
					}
				}
				if (horde)
				{
					void *target = horde->getCombineTarget();
					if (target)
						horde->combine(other, target, false);
				}
			}
		}
	}
	else
	{
		return STATE_FAILURE;
	}
	return STATE_CONTINUE;
}
