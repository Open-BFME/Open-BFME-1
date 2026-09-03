// cl: /DNDEBUG /MD /EHsc
// readable body of ?onEnter@AITunnelNetworkGuardState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
//
// AITunnelNetworkGuardState::onEnter — retail 0x0016DAC0 (201B).
//
// ZH onEnter: new AITNGuardMachine, copy getGuardLocation into +0x44, store
// getGuardMode at +0x54, initDefaultState, then setState(AI_TN_GUARD_RETURN).
// AIUpdateInterface virtuals sit at +0x1A0 / +0x1BC as encoded by retail.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum
{
	AI_TN_GUARD_RETURN = 0x138B
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

template <int N>
class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <>
class VirtualSlots<0>
{
};

class AIUpdateInterface : public VirtualSlots<104>
{
public:
	virtual const Coord3D *getGuardLocation();
	virtual void pad_1a4();
	virtual void pad_1a8();
	virtual void pad_1ac();
	virtual void pad_1b0();
	virtual void pad_1b4();
	virtual void pad_1b8();
	virtual int getGuardMode();
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }

	unsigned char m_objectFields00[0x204];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();
	virtual StateReturnType setState(int id);

	Object *getOwner() { return m_owner; }

	unsigned char m_machineFields04[0x0c];
	Object *m_owner;
};

class AITNGuardMachine
{
public:
	AITNGuardMachine(Object *owner);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual StateReturnType initDefaultState();
	virtual StateReturnType setState(int id);

	void setTargetPositionToGuard(const Coord3D *pos) { m_positionToGuard = *pos; }
	void setGuardMode(int mode) { m_guardMode = mode; }

	unsigned char m_machineFields04[0x40];
	Coord3D m_positionToGuard;
	unsigned int m_nemesisToAttack;
	int m_guardMode;
};

class AITunnelNetworkGuardState
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineOwner() { return m_machine->getOwner(); }

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	AITNGuardMachine *m_guardMachine;
};

StateReturnType AITunnelNetworkGuardState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	m_guardMachine = new AITNGuardMachine(getMachineOwner());
	m_guardMachine->setTargetPositionToGuard(ai->getGuardLocation());
	m_guardMachine->setGuardMode(ai->getGuardMode());

	if (m_guardMachine->initDefaultState() == STATE_FAILURE)
		return STATE_FAILURE;
	return m_guardMachine->setState(AI_TN_GUARD_RETURN);
}
