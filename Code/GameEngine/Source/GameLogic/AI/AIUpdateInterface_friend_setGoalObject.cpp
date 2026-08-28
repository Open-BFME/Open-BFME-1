// cl: /DNDEBUG /MD /EHsc
// readable body of ?friend_setGoalObject@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

// AIUpdateInterface::friend_setGoalObject, retail 0x0026F1A0. One virtual call
// with the machine's lock taken off around it.
//
// The lock is the byte at +0x40 of the state machine at +0x30 - the same flag
// StateMachine::setGoalPosition tests before it will write anything. This is
// the "friend_" half of that pair: it clears the lock, sets the goal through
// the machine's slot at +0x38, and puts the lock back only if it was on.
//
// The machine pointer is re-read after the call rather than kept, which is what
// a member access through `this' does when a virtual call sits in between.

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_2C() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void setGoalObject( Object *obj ) = 0;	// +0x38

	unsigned char m_unmodelled_04[ 0x40 - 4 ];
	bool m_locked;							// +0x40
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void friend_setGoalObject( Object *obj );

private:
	unsigned char m_unmodelled_00[ 0x30 ];
	StateMachine *m_stateMachine;			// +0x30
};

// ?friend_setGoalObject@AIUpdateInterface@@QAEXPAVObject@@@Z
void AIUpdateInterface::friend_setGoalObject( Object *obj )
{
	bool wasLocked = m_stateMachine->m_locked;
	m_stateMachine->m_locked = false;

	m_stateMachine->setGoalObject( obj );

	if( wasLocked )
		m_stateMachine->m_locked = true;
}
