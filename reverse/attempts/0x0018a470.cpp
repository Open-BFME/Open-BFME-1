// ?onEnter@AITNGuardInnerState@@UAE?AW4StateReturnType@@XZ
// partial score=0.974619 date=2026-09-23
typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_SUCCESS = -1,
	STATE_CONTINUE = 0
};

class Object
{
};

class AttackExitConditionsInterface;

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void setGoalObject( const Object *object );
};

class AITNGuardMachineView
{
public:
	unsigned char m_fields[0x50];
	int m_nemesisToAttack;
};

class GameLogic
{
public:
	Object *findObjectByID( int id );
	unsigned char m_fields[0x3c];
	UnsignedInt m_frame;
};

class AIData
{
public:
	unsigned char m_fields[0x3c];
	UnsignedInt m_guardChaseUnitFrames;
};

class AI
{
public:
	unsigned char m_fields[0x14];
	AIData *m_aiData;
};

extern GameLogic *TheBfmeGameLogic;
extern AI *TheAI;

class AIAttackState
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit( int status );
	virtual StateReturnType update();

	AIAttackState( StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking, AttackExitConditionsInterface *conditions );
	StateMachine *getMachine() const { return *(StateMachine **)((const unsigned char *)this + 0x1c); }

	unsigned char m_fields[0x18];
	StateMachine *m_machine;
	unsigned char m_tail[0x34];
};

struct Rva0018A470ExitConditions
{
	unsigned char m_unknown00[4];
	UnsignedInt m_attackGiveUpFrame;
	unsigned char m_unknown08[4];
};

class AITNGuardInnerState
{
public:
	virtual StateReturnType onEnter();

	unsigned char m_stateFields[0x18];
	AITNGuardMachineView *m_machine;
	unsigned char m_at20[4];
	Rva0018A470ExitConditions m_exitConditions;
	AIAttackState *m_attackState;
};

extern GameLogic *TheBfmeGameLogic;
extern AI *TheAI;

StateReturnType AITNGuardInnerState::onEnter()
{
	GameLogic *logic = TheBfmeGameLogic;
	int key = m_machine->m_nemesisToAttack;
	Object *nemesis = logic->findObjectByID( key );

	if (nemesis == 0)
		return STATE_SUCCESS;

	AIData *aiData = TheAI->m_aiData;
	int frame = logic->m_frame;
	int delay = aiData->m_guardChaseUnitFrames;
	m_exitConditions.m_attackGiveUpFrame = delay + frame;

	m_attackState = new AIAttackState( (StateMachine *)m_machine, false, true, false, (AttackExitConditionsInterface *)&m_exitConditions );
	m_attackState->getMachine()->setGoalObject( nemesis );

	return m_attackState->onEnter() != STATE_CONTINUE ? STATE_SUCCESS : STATE_CONTINUE;
}
