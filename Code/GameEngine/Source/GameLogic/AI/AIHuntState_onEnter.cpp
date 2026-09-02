// cl: /DNDEBUG /MD /EHsc
//
// AIHuntState::onEnter — retail 0x0016DCE0 (59B).
//
// Constructor-owned vtable 0x00C98330 slot 4. Slot 6 of the same table is the
// already-matched AIHuntState::update. Retail creates the hunt sub-machine
// through StateMachine vslot +0x24, then the ZH sleep-spike delay
// GetGameLogicRandomValue(0, ENEMY_SCAN_RATE) with ENEMY_SCAN_RATE == 15.

typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

	char m_pad[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class HuntSubMachine
{
public:
	virtual void pad0();
	virtual void pad1();
	virtual void pad2();
	virtual void pad3();
	virtual void pad4();
	virtual void pad5();
	virtual void pad6();
	virtual StateReturnType initDefaultState();
};

class StateMachine
{
public:
	virtual void pad0();
	virtual void pad1();
	virtual void pad2();
	virtual void pad3();
	virtual void pad4();
	virtual void pad5();
	virtual void pad6();
	virtual void pad7();
	virtual void pad8();
	virtual HuntSubMachine *createHuntMachine();
};

class AIHuntState
{
public:
	virtual StateReturnType onEnter();

private:
	char m_pad[0x18];
	StateMachine *m_machine;
	int m_unused20;
	HuntSubMachine *m_huntMachine;
	UnsignedInt m_nextEnemyScanTime;
};

StateReturnType AIHuntState::onEnter()
{
	m_huntMachine = m_machine->createHuntMachine();
	UnsignedInt sleepTime = GetGameLogicRandomValue(
		0,
		15,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp",
		0x3574);
	m_nextEnemyScanTime = TheGameLogic->getFrame() + sleepTime;
	return m_huntMachine->initDefaultState();
}
