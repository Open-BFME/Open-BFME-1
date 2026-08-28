// cl: /DNDEBUG /MD /EHsc
// readable body of ?privateDock@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

// AIUpdateInterface::privateDock, retail 0x00271760. Zero Hour's four
// statements, one for one: refuse an immobile object, clear the state machine,
// give it the goal object, record the command source, and set AI_DOCK.
//
// The offsets are BFME's: the object at +0x08, the state machine at +0x30 and
// the last command source at +0x48, which is a plain store rather than a call
// because setLastCommandSource is inline. The three machine methods are
// virtual, at +0x14, +0x38 and +0x20, and AI_DOCK is fourteen.

typedef bool Bool;

enum CommandSourceType {};

enum StateID
{
	AI_DOCK = 14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isMobile() const;						// ILT thunk at 0x00017607
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void stateMachineAnchor00();
	virtual void stateMachineAnchor04();
	virtual void stateMachineAnchor08();
	virtual void stateMachineAnchor0C();
	virtual void stateMachineAnchor10();
	virtual void clear();						// +0x14
	virtual void stateMachineAnchor18();
	virtual void stateMachineAnchor1C();
	virtual void setState( StateID state );		// +0x20
	virtual void stateMachineAnchor24();
	virtual void stateMachineAnchor28();
	virtual void stateMachineAnchor2C();
	virtual void stateMachineAnchor30();
	virtual void stateMachineAnchor34();
	virtual void setGoalObject( Object *obj );	// +0x38
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateDock( Object *obj, CommandSourceType cmdSource );

	Object *getObject() const
	{
		return m_object;
	}

	StateMachine *getStateMachine() const
	{
		return m_stateMachine;
	}

	void setLastCommandSource( CommandSourceType cmdSource )
	{
		m_lastCommandSource = cmdSource;
	}

private:
	unsigned char m_unmodelled_04[ 4 ];			// the vftable pointer takes +0x00
	Object *m_object;							// +0x08
	unsigned char m_unmodelled_0C[ 0x30 - 0x0C ];
	StateMachine *m_stateMachine;				// +0x30
	unsigned char m_unmodelled_34[ 0x48 - 0x34 ];
	CommandSourceType m_lastCommandSource;		// +0x48
};

// ?privateDock@AIUpdateInterface@@MAEXPAVObject@@W4CommandSourceType@@@Z
void AIUpdateInterface::privateDock( Object *obj, CommandSourceType cmdSource )
{
	if( getObject()->isMobile() == false )
		return;

	getStateMachine()->clear();
	getStateMachine()->setGoalObject( obj );
	setLastCommandSource( cmdSource );
	getStateMachine()->setState( AI_DOCK );
}
