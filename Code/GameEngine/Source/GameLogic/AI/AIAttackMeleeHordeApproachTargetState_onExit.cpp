// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef bool Bool;
typedef float Real;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

class Object;

template <Int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int bitIndex)
	{
		m_bits.set(bitIndex);
	}

	BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class AIUpdateInterface
{
public:
	void ignoreObstacle(Object *obstacle);
};

template <Int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

class BFMEGroundMovementAI : public BFMEVirtualSlots<123>
{
public:
	virtual Bool isDoingGroundMovement() const = 0;
};

class Object
{
public:
	void setPosition(const Coord3D *position);

	unsigned char m_unmodelled000[0x38];
	Coord3D m_position;
	unsigned char m_unmodelled044[0x90 - 0x44];
	unsigned char m_status;
	unsigned char m_unmodelled091[0x204 - 0x91];
	AIUpdateInterface *m_ai;
};

struct StateMachine
{
	unsigned char m_unmodelled000[0x10];
	Object *m_owner;
};

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);

protected:
	unsigned char m_unmodelled004[0x18];
	StateMachine *m_machine;
};

class BfmeObjectStatusCallTarget
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set);
};

class BfmeSpeedCallTarget
{
public:
	void setDesiredSpeed(Real speed);
};

extern void j_0002181e();
extern void j_00048ca7();

#define BFME_ATTACK_MELEE_HORDE_APPROACH_DISTANCE_SQUARED (*(Real *)0x01099378)

class AIAttackMeleeHordeApproachTargetState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);

private:
	unsigned char m_unmodelled020[4];
	Coord3D m_goalPosition;
	unsigned char m_unmodelled030[0x61 - 0x30];
	Bool m_isInitialApproach;
};

void AIAttackMeleeHordeApproachTargetState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);

	StateMachine *machine = m_machine;
	m_isInitialApproach = false;
	Object *owner = machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;
	if ((owner->m_status & 1) != 0)
		return;

	ObjectStatusMaskType statusMask(ObjectStatusMaskType::kInit, 74);
	typedef void (BfmeObjectStatusCallTarget::*StatusCall)(
		const ObjectStatusMaskType &, Bool);
	union { void *asVoid; StatusCall asMember; } statusCast;
	statusCast.asVoid = (void *)j_0002181e;
	(reinterpret_cast<BfmeObjectStatusCallTarget *>(owner)->*statusCast.asMember)(
		statusMask, false);

	if (ai != 0)
	{
		typedef void (BfmeSpeedCallTarget::*SpeedCall)(Real);
		union { void *asVoid; SpeedCall asMember; } speedCast;
		speedCast.asVoid = (void *)j_00048ca7;
		(reinterpret_cast<BfmeSpeedCallTarget *>(ai)->*speedCast.asMember)(999999.0f);
		ai->ignoreObstacle(0);

		if (((BFMEGroundMovementAI *)ai)->isDoingGroundMovement())
		{
			Real dx = m_goalPosition.x - owner->m_position.x;
			Real dy = m_goalPosition.y - owner->m_position.y;
			if (dx * dx + dy * dy <
				BFME_ATTACK_MELEE_HORDE_APPROACH_DISTANCE_SQUARED)
				owner->setPosition(&m_goalPosition);
		}
	}
}
