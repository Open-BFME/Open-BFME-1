// ?update@Rva0016FC30AIExitState@@UAE?AW4StateReturnType@@XZ
// Neutral ABI view of the BFME AIExitState update body at retail 0x0016FC30.
//
// Identity evidence: the named AIExitState constructor at 0x00171610 installs
// retail vtable 0x01098120, whose slot 6 (+0x18) is ILT 0x0000C473 and lands
// at this body.  The body follows the AIExitState exit-door path: it asks the
// StateMachine for its goal, checks the goal AI's WAIT_TO_EXIT result, obtains
// the BFME containment exit interface, reserves a door, and compares the
// machine's current state with this state's id after dispatching the exit.
// The source uses an address-derived class and explicit BFME views because the
// broad State/Object headers carry different field offsets.  The 17 declared
// virtual slots put update at the proven +0x18 role; novtable emits no new
// table from this ABI view, so the retail table remains the only identity
// evidence.
// cl: /DNDEBUG /MD /EHsc

extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)

typedef int Int;
typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum AIFreeToExitType
{
	WAIT_TO_EXIT = 2
};

enum ExitDoorType
{
	DOOR_NONE_AVAILABLE = -1
};

class Object;

// Existing pin at ILT 0x0000E570 -> StateMachine::getGoalObject body.
extern void j_0000e570();
class StateMachine;
typedef Object *(__fastcall *GetGoalObject)( StateMachine * );

class StateMachine
{
public:
	Object *getOwner()
	{
		return m_owner;
	}

	Object *getGoalObject()
	{
		return ((GetGoalObject)j_0000e570)( this );
	}

	Int getCurrentStateID() const
	{
		void *currentState = m_currentState;
		return currentState ? *(Int *)((char *)currentState + 4) : 999999;
	}

private:
	unsigned char m_unreconstructed_00[ 0x10 ];
	Object *m_owner;
	unsigned char m_unreconstructed_14[ 0x1c - 0x14 ];
	void *m_currentState;
};

// Existing pin at ILT 0x000022BB -> Overridable::getFinalOverride.
class Overridable
{
public:
	Overridable *getFinalOverride();

	unsigned char m_unreconstructed_00[ 4 ];
	Overridable *m_nextOverride;
};

template <Int N>
class BFMEVirtualSlots : public BFMEVirtualSlots< N - 1 >
{
public:
	virtual void unused( char (*)[ N ] ) = 0;
};

template <>
class BFMEVirtualSlots< 0 >
{
};

// BFME's AIUpdateInterface places getAiFreeToExit at vtable +0x170.
class BFMEExitAI : public BFMEVirtualSlots< 92 >
{
public:
	virtual AIFreeToExitType getAiFreeToExit( const Object *exiter ) const = 0;
};

// BFME's ContainModuleInterface places getContainExitInterface at +0x60.
class ExitInterface;
class BFMEExitContain : public BFMEVirtualSlots< 24 >
{
public:
	virtual ExitInterface *getContainExitInterface() = 0;
};

class ExitInterface
{
public:
	virtual Bool isExitBusy() const = 0;
	virtual ExitDoorType reserveDoorForExit( void *objType, Object *specificObject ) = 0;
	virtual void exitObjectViaDoor( Object *newObj, ExitDoorType exitDoor ) = 0;
};

class Object
{
	public:
	Overridable *getTemplate() const
	{
		return m_template;
	}

	BFMEExitContain *getContain() const
	{
		return m_contain;
	}

	BFMEExitAI *getAI() const
	{
		return m_ai;
	}

	private:
	unsigned char m_unreconstructed_00[ 4 ];
	Overridable *m_template;
	unsigned char m_unreconstructed_08[ 0x1fc - 0x08 ];
	BFMEExitContain *m_contain;
	unsigned char m_unreconstructed_200[ 4 ];
	BFMEExitAI *m_ai;
};

class __declspec(novtable) Rva0016FC30AIExitState
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual StateReturnType update();
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;

	StateMachine *getMachine()
	{
		return m_machine;
	}

	Object *getMachineOwner()
	{
		return m_machine->getOwner();
	}

	Object *getMachineGoalObject()
	{
		return m_machine->getGoalObject();
	}

	Int getID() const
	{
		return *(Int *)((char *)this + 4);
	}

private:
	unsigned char m_unreconstructed_04[ 0x18 ];
	StateMachine *m_machine;
};

StateReturnType Rva0016FC30AIExitState::update()
{
	Object *obj = getMachineOwner();
	Object *goal = getMachineGoalObject();
	if (goal)
	{
		BFMEExitAI *goalAI = goal->getAI();
		if (goalAI && goalAI->getAiFreeToExit( obj ) == WAIT_TO_EXIT)
		{
			// This is the documented zero-byte MSVC shaping barrier that keeps
			// the retail early-return block ahead of the exit path.
			_WriteBarrier();
			return STATE_CONTINUE;
		}

		ExitInterface *exitInterface = goal->getContain() ?
			goal->getContain()->getContainExitInterface() : 0;
		if (exitInterface == 0)
			return STATE_FAILURE;
		if (exitInterface->isExitBusy())
			return STATE_CONTINUE;

		Overridable *thingTemplate = obj->getTemplate();
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = thingTemplate->m_nextOverride->getFinalOverride();
		ExitDoorType exitDoor = exitInterface ?
			exitInterface->reserveDoorForExit( thingTemplate, obj ) : DOOR_NONE_AVAILABLE;
		if (exitDoor == DOOR_NONE_AVAILABLE)
			return STATE_FAILURE;

		exitInterface->exitObjectViaDoor( obj, exitDoor );
		if (getMachine()->getCurrentStateID() != getID())
			return STATE_CONTINUE;
		return STATE_SUCCESS;
	}

	return STATE_FAILURE;
}
