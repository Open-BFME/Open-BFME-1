// cl: /DNDEBUG /MD /EHsc
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_unmodelled_00[ 0x74 ];
	ObjectID m_id;
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject( const Object *object );

	Object *getGoalObject();
};

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
public:
	void transferAttack( ObjectID fromID, ObjectID toID );

private:
	unsigned char m_unmodelled_00[ 0x30 ];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[ 0x0C ];
	ObjectID m_currentVictimID;
};

void AIUpdateInterface::transferAttack( ObjectID fromID, ObjectID toID )
{
	if( m_currentVictimID == fromID )
		m_currentVictimID = toID;

	Object *goalObject = m_stateMachine->getGoalObject();
	if( goalObject && goalObject->getID() == fromID )
	{
		StateMachine *stateMachine = m_stateMachine;
		stateMachine->setGoalObject( TheGameLogic->findObjectByID( toID ) );
	}
}
