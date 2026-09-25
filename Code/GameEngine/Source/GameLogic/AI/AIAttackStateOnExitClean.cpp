// cl: /DNDEBUG /MD /EHsc
// stlport
// readable body of ?onExit@AIAttackState@@UAEXW4StateExitType@@@Z: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// The AIAttackState vtable at 0x00C9A0C8 selects this body in slot 5 through ILT 0x00020ACC.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

template <Int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int bitIndex)
	{
		m_bits.set(bitIndex);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object;

enum WhichTurretType
{
	WHICH_TURRET_PRIMARY = 0
};

class StateMachine
{
public:
	char m_pad00[0x10];
	Object *m_owner;
};

class AttackStateMachine
{
public:
	virtual void deleteInstance(Bool destroy = true);
};

class AIUpdateInterface
{
public:
	void setCurrentVictim(const Object *victim);
	void setTurretTargetObject(WhichTurretType turret, Object *targetObject,
		Bool forceAttacking);
	void friend_setGoalObject(Object *goalObject);
};

class Rva001BF560
{
public:
	void invoke();
};

class Object
{
public:
	char m_pad00[0x114];
	unsigned char m_condition114[4];
	char m_pad118[0xec];
	AIUpdateInterface *m_ai;

	void setStatus(const ObjectStatusMaskType &mask, Bool set);
	void notifyModelConditionChanged();
};

class BfmeAIAttackState
{
public:
	char m_pad00[0x1c];
	StateMachine *m_machine;
	char m_pad20[8];
	AttackStateMachine *m_attackMachine;

	void onExit(StateExitType status);
};

// ?onExit@AIAttackState@@UAEXW4StateExitType@@@Z
// The five masks use the values encoded by the retail instructions.  BFME's
// status numbering differs from the vendored Zero Hour header, so the body
// keeps these values visible instead of assigning unsupported names.
void BfmeAIAttackState::onExit(StateExitType status)
{
	if (m_attackMachine)
	{
		m_attackMachine->deleteInstance();
		m_attackMachine = 0;
	}

	Object *obj = m_machine->m_owner;
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 13), false);
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 25), false);
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 22), false);
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 27), false);
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 28), false);

	if (obj->m_condition114[0] & 0x20)
	{
		*reinterpret_cast<UnsignedInt *>(obj->m_condition114) &= ~0x20u;
		obj->notifyModelConditionChanged();
	}
	if (obj->m_condition114[0] & 0x40)
	{
		*reinterpret_cast<UnsignedInt *>(obj->m_condition114) &= ~0x40u;
		obj->notifyModelConditionChanged();
	}

	reinterpret_cast<Rva001BF560 *>(obj)->invoke();
	AIUpdateInterface *ai = obj->m_ai;
	if (ai)
	{
		ai->setCurrentVictim(0);
		Int turret = 0;
		while (turret < 2)
		{
			ai->setTurretTargetObject((WhichTurretType)turret, 0, 0);
			++turret;
		}
		ai->friend_setGoalObject(0);
	}
}

#pragma comment(linker, "/alternatename:?onExit@AIAttackState@@UAEXW4StateExitType@@@Z=?onExit@BfmeAIAttackState@@QAEXW4StateExitType@@@Z")
