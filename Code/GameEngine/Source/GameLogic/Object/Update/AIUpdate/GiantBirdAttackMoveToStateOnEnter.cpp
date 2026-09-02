// cl: /DNDEBUG /MD

typedef int Int;

enum StateReturnType
{
	STATE_FAILURE = 0,
	STATE_SUCCESS = 1
};

class StateMachine;

class AIUpdateInterface
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual void unused010() = 0;
	virtual void unused014() = 0;
	virtual void unused018() = 0;
	virtual void unused01c() = 0;
	virtual void unused020() = 0;
	virtual void unused024() = 0;
	virtual void unused028() = 0;
	virtual void unused02c() = 0;
	virtual void unused030() = 0;
	virtual void unused034() = 0;
	virtual void unused038() = 0;
	virtual void unused03c() = 0;
	virtual void unused040() = 0;
	virtual void unused044() = 0;
	virtual void unused048() = 0;
	virtual void unused04c() = 0;
	virtual void unused050() = 0;
	virtual void unused054() = 0;
	virtual void unused058() = 0;
	virtual void unused05c() = 0;
	virtual void unused060() = 0;
	virtual void unused064() = 0;
	virtual void unused068() = 0;
	virtual void unused06c() = 0;
	virtual void unused070() = 0;
	virtual void unused074() = 0;
	virtual void unused078() = 0;
	virtual void unused07c() = 0;
	virtual void unused080() = 0;
	virtual void unused084() = 0;
	virtual void unused088() = 0;
	virtual void unused08c() = 0;
	virtual void unused090() = 0;
	virtual void unused094() = 0;
	virtual void unused098() = 0;
	virtual void unused09c() = 0;
	virtual void unused0a0() = 0;
	virtual void unused0a4() = 0;
	virtual void unused0a8() = 0;
	virtual void unused0ac() = 0;
	virtual void unused0b0() = 0;
	virtual void unused0b4() = 0;
	virtual void unused0b8() = 0;
	virtual void unused0bc() = 0;
	virtual void unused0c0() = 0;
	virtual void unused0c4() = 0;
	virtual void unused0c8() = 0;
	virtual void unused0cc() = 0;
	virtual void unused0d0() = 0;
	virtual void unused0d4() = 0;
	virtual void unused0d8() = 0;
	virtual void unused0dc() = 0;
	virtual void unused0e0() = 0;
	virtual void unused0e4() = 0;
	virtual void unused0e8() = 0;
	virtual void unused0ec() = 0;
	virtual void unused0f0() = 0;
	virtual void unused0f4() = 0;
	virtual void unused0f8() = 0;
	virtual void unused0fc() = 0;
	virtual void unused100() = 0;
	virtual void unused104() = 0;
	virtual void unused108() = 0;
	virtual void unused10c() = 0;
	virtual void unused110() = 0;
	virtual void unused114() = 0;
	virtual void unused118() = 0;
	virtual void unused11c() = 0;
	virtual void unused120() = 0;
	virtual void unused124() = 0;
	virtual void unused128() = 0;
	virtual void unused12c() = 0;
	virtual void unused130() = 0;
	virtual void unused134() = 0;
	virtual void unused138() = 0;
	virtual void unused13c() = 0;
	virtual void unused140() = 0;
	virtual void unused144() = 0;
	virtual void unused148() = 0;
	virtual void unused14c() = 0;
	virtual void unused150() = 0;
	virtual void unused154() = 0;
	virtual void unused158() = 0;
	virtual void unused15c() = 0;
	virtual void unused160() = 0;
	virtual void unused164() = 0;
	virtual void unused168() = 0;
	virtual void unused16c() = 0;
	virtual void unused170() = 0;
	virtual void unused174() = 0;
	virtual void unused178() = 0;
	virtual void unused17c() = 0;
	virtual void unused180() = 0;
	virtual void unused184() = 0;
	virtual void unused188() = 0;
	virtual void unused18c() = 0;
	virtual void unused190() = 0;
	virtual void unused194() = 0;
	virtual void unused198() = 0;
	virtual void unused19c() = 0;
	virtual void unused1a0() = 0;
	virtual void unused1a4() = 0;
	virtual void unused1a8() = 0;
	virtual void unused1ac() = 0;
	virtual void unused1b0() = 0;
	virtual void unused1b4() = 0;
	virtual void unused1b8() = 0;
	virtual void unused1bc() = 0;
	virtual void unused1c0() = 0;
	virtual void unused1c4() = 0;
	virtual void unused1c8() = 0;
	virtual void unused1cc() = 0;
	virtual void unused1d0() = 0;
	virtual void unused1d4() = 0;
	virtual void unused1d8() = 0;
	virtual void unused1dc() = 0;
	virtual void unused1e0() = 0;
	virtual void unused1e4() = 0;
	virtual void unused1e8() = 0;
	virtual void unused1ec() = 0;
	virtual void unused1f0() = 0;
	virtual void unused1f4() = 0;
	virtual void unused1f8() = 0;
	virtual void unused1fc() = 0;
	virtual Int makeAttackMoveGoal() = 0;
};

class Object
{
public:
	unsigned char m_unreconstructed00[0x204];
	AIUpdateInterface *m_aiUpdate;
};

class StateMachine
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void start() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void reset(Int id) = 0;

	unsigned char m_unreconstructed04[0x0c];
	Object *m_owner;
};

class GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();

	Int m_id;
	Int m_successStateID;
	Int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
};

class GiantBirdAttackMoveToState : public GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();

private:
	Int m_unreconstructed20;
	Int m_unreconstructed24;
	Int m_goalHandle;
	StateMachine *m_attackMachine;
	Int m_retryCount;
};

StateReturnType GiantBirdAttackMoveToState::onEnter()
{
	AIUpdateInterface *ai = m_machine->m_owner->m_aiUpdate;
	m_attackMachine->start();
	m_attackMachine->reset(0);
	m_goalHandle = ai->makeAttackMoveGoal();
	m_retryCount = 5;
	return GiantBirdNormalFlightState::onEnter();
}
