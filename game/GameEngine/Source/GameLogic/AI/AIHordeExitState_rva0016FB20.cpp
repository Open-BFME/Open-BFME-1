// ?update@Rva0016FB20AIHordeExitState@@UAE?AW4StateReturnType@@XZ
// Neutral ABI view of the AIHordeExitState update body at retail 0x0016FB20.
//
// Identity evidence is the complete constructor/table chain, not the string
// by itself: constructor 0x00171540 passes "AIHordeExitState" to State's
// naming base and stores vtable 0x01098048; the table has 17 entries and its
// slot 6 (+0x18) ILT 0x0003101B routes to 0x0016FB20.  The table's scalar
// deleting-dtor and complete-dtor entries resolve through the existing weak
// ILT targets 0x0002ADA1 -> 0x00180140 and 0x00026C60 -> 0x000A1AF0; this TU
// declares the state ABI only and emits no replacement table.
//
// The body uses the owner/goal AI and containment offsets established by the
// sibling AIExitState conversion.  The HordeContain slot 57 return is kept
// neutral: retail tests its bool result and chooses success versus continue,
// but this evidence does not prove a semantic name for that slot.
// The existing j_000084B8 thunk is Thing::getTemplate (body 0x00098E50); the
// typed member-pointer adapter below calls that real thunk without adding a
// pin or a guessed alias.
// cl: /DNDEBUG /MD /EHsc

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

// Existing thunk: ILT 0x0000E570 -> StateMachine::getGoalObject.
extern void j_0000e570(void);
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

private:
	unsigned char m_unreconstructed_00[ 0x10 ];
	Object *m_owner;
	unsigned char m_unreconstructed_14[ 0x1c - 0x14 ];
	void *m_currentState;
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

// AIUpdateInterface: getAiFreeToExit is the virtual at +0x170 (slot 92).
class BFMEExitAI : public BFMEVirtualSlots< 92 >
{
public:
	virtual AIFreeToExitType getAiFreeToExit( const Object *exiter ) const = 0;
};

class HordeContainInterface;

// ContainModuleInterface: getHordeContainInterface is slot 26 (+0x68).
class BFMEContainModule : public BFMEVirtualSlots< 26 >
{
public:
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

// The goal's containment view exposes its exit interface at slot 24 (+0x60).
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
	virtual ExitDoorType reserveDoorForExit( const void *objType,
		Object *specificObject ) = 0;
	virtual void exitObjectViaDoor( Object *newObj,
		ExitDoorType exitDoor ) = 0;
};

// The exact slot 57 (+0xE4) result is a bool from retail's test al.  Keep the
// declaration neutral until a named caller or implementation proves more.
class __declspec(novtable) HordeContainInterface : public BFMEVirtualSlots< 57 >
{
public:
	virtual Bool bfmeSlot57() = 0;
};

class Object
{
public:
	BFMEContainModule *getContainModule() const
	{
		return reinterpret_cast<BFMEContainModule *>(m_contain);
	}

	BFMEExitContain *getExitContain() const
	{
		return reinterpret_cast<BFMEExitContain *>(m_contain);
	}

	BFMEExitAI *getAI() const
	{
		return m_ai;
	}

private:
	unsigned char m_unreconstructed_00[ 0x1fc ];
	void *m_contain;
	unsigned char m_unreconstructed_200[ 4 ];
	BFMEExitAI *m_ai;
};

// The name and return type come from the existing real body 0x00098E50.
// This is a TU-local typed member call to the already-owned j_000084B8 thunk.
struct BfmeThingTemplateCall
{
	const void *getTemplate() const;
};

extern void j_000084b8(void);

static __forceinline const void *bfmeGetTemplate( Object *object )
{
	typedef const void *(BfmeThingTemplateCall::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000084b8;
	return (reinterpret_cast<const BfmeThingTemplateCall *>(object)->*fn.member)();
}

class __declspec(novtable) Rva0016FB20AIHordeExitState
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

private:
	unsigned char m_unreconstructed_04[ 0x18 ];
	StateMachine *m_machine;
};

StateReturnType Rva0016FB20AIHordeExitState::update()
{
	Object *obj = getMachine()->getOwner();
	Object *goal = getMachine()->getGoalObject();
	if (obj == 0 || goal == 0)
		return STATE_FAILURE;

	BFMEExitAI *goalAI = goal->getAI();
	if (goalAI && goalAI->getAiFreeToExit( obj ) == WAIT_TO_EXIT)
		return STATE_CONTINUE;

	BFMEContainModule *ownerContain = obj->getContainModule();
	if (ownerContain == 0)
		return STATE_FAILURE;
	HordeContainInterface *horde =
		ownerContain->getHordeContainInterface();
	if (horde == 0)
		return STATE_FAILURE;

	BFMEExitContain *goalContain = goal->getExitContain();
	ExitInterface *exitInterface = goalContain == 0 ? 0 :
		goalContain->getContainExitInterface();
	if (exitInterface == 0)
		return STATE_FAILURE;
	if (exitInterface->isExitBusy())
		return STATE_CONTINUE;

	ExitDoorType exitDoor = exitInterface->reserveDoorForExit(
		bfmeGetTemplate( obj ), obj );
	if (exitDoor == DOOR_NONE_AVAILABLE)
		return STATE_FAILURE;

	if (horde->bfmeSlot57())
	{
		exitInterface->exitObjectViaDoor( obj, exitDoor );
		return STATE_SUCCESS;
	}

	exitInterface->exitObjectViaDoor( obj, exitDoor );
	return STATE_CONTINUE;
}
