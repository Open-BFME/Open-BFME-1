// cl: /DNDEBUG /MD /EHsc
// readable body of ?isCurrentlyFerryingSupplies@SupplyTruckAIUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp
// readable body of ?privateDock@SupplyTruckAIUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp
// readable body of ?update@SupplyTruckAIUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp
// Open-BFME5: SupplyTruckAIUpdate::update and ::privateDock, retail 0x002C5740
// and 0x002C5820. Both Zero Hour bodies unchanged.
//
// Offsets the two bodies fix, all relative to the object base:
//
//   +0x334  m_supplyTruckStateMachine, which also sizes AIUpdateInterface --
//           it is this class's first member, so the base is exactly 0x334 wide
//   +0x348  m_preferredDock
//   +0x74   Object::m_id, from `mov eax,[ebx+0x74]` for dock->getID()
//
// The state machine's updateStateMachine is vtable slot 4 (`call [eax+0x10]`).
//
// Two things the bytes confirm about the Zero Hour spellings rather than change:
// CMD_FROM_PLAYER is 0, so `cmdSource == CMD_FROM_PLAYER` is a bare
// `test edi,edi`; and IS_STATE_SLEEP/GET_STATE_SLEEP_FRAMES really are
// `((Int)(ret) > 0)` and `((UnsignedInt)(ret))`, which is why the ternary is a
// `test/jg` keeping the value in place with 1 as the other arm.

class Object;

typedef unsigned int ObjectID;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0							///< retail: test edi,edi
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID	= 0,
	UPDATE_SLEEP_NONE		= 1,
	UPDATE_SLEEP_FOREVER	= 0x3fffffff
};

#define UPDATE_SLEEP(numFrames)				((UpdateSleepTime)(numFrames))

typedef int StateReturnType;

enum { MACHINE_DONE_STATE_ID = 999998, INVALID_STATE_ID = 999999 };

#define IS_STATE_SLEEP(ret)					((int)(ret) > 0)
#define GET_STATE_SLEEP_FRAMES(ret)			((unsigned int)(ret))

class ObjectWithID
{
public:
	ObjectID getID( void ) const { return m_id; }

private:
	unsigned char m_unreconstructed_00[0x74];
	ObjectID m_id;								///< retail this+0x74
};

// BFME's supply-truck states. The five Zero Hour names keep their Zero Hour
// values -- the jump table at 0x006C57A4 has six entries and returns false for
// 0, 1 and 3, which is exactly ZH's ST_IDLE / ST_BUSY / ST_REGROUPING -- so the
// state BFME added is appended at the end, and it ferries.
enum SupplyTruckStateTypes
{
	ST_IDLE = 0,
	ST_BUSY = 1,
	ST_WANTING = 2,
	ST_REGROUPING = 3,
	ST_DOCKING = 4,
	ST_BFME_SIXTH = 5			///< BFME-only; unnamed, and on the ferrying side
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	unsigned int getID( void ) const { return m_id; }

private:
	unsigned char m_unreconstructed_00[4];
	unsigned int m_id;							///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	// Only slot 4 is named; the four before it exist to place it.
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual StateReturnType updateStateMachine() = 0;	///< slot 4, retail call [eax+0x10]

	// The null arm matters: retail tests m_currentState and branches straight to
	// the switch's default, because INVALID_STATE_ID is outside the case range
	// and MSVC folds the constant through.
	unsigned int getCurrentStateID( void ) const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }

private:
	unsigned char m_unreconstructed_04[0x1c - 4];
	State *m_currentState;						///< retail this+0x1c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual UpdateSleepTime update( void );					///< ILT 0x00028772

protected:
	virtual void privateDock( Object *dock, CommandSourceType cmdSource );	///< ILT 0x0004872F

	// vptr plus this brings the base to 0x330, which is where the second base
	// starts.
	unsigned char m_unreconstructed_04[0x330 - 4];
};

// The second base, at object+0x330. isCurrentlyFerryingSupplies is entered with
// it -- `mov eax,[ecx+0x4]` reaches m_supplyTruckStateMachine, which update()
// reaches as [this+0x334] from the object base -- so AIUpdateInterface is
// exactly 0x330 bytes here.
//
// That is in tension with AIUpdateInterface::setQueueForPathTime at 0x0026ECA0,
// which byte-verifies reading m_isInUpdate at object+0x330. Both readings are
// byte-verified and they cannot both describe AIUpdateInterface, so which class
// owns 0x330 is open. Nothing in these three bodies settles it, and neither
// reading changes any offset any of them uses.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h
class SupplyTruckAIInterface
{
public:
	virtual bool isAvailableForSupplying( void ) const = 0;
	virtual bool isCurrentlyFerryingSupplies( void ) const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h
class SupplyTruckAIUpdate : public AIUpdateInterface, public SupplyTruckAIInterface
{
public:
	virtual UpdateSleepTime update( void );
	virtual bool isCurrentlyFerryingSupplies( void ) const;

protected:
	virtual void privateDock( Object *dock, CommandSourceType cmdSource );

private:
	StateMachine *m_supplyTruckStateMachine;	///< retail this+0x334
	unsigned char m_unreconstructed_338[0x348 - 0x338];
	ObjectID m_preferredDock;					///< retail this+0x348
};

// ?update@SupplyTruckAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime SupplyTruckAIUpdate::update( void )
{

	StateReturnType stRet = m_supplyTruckStateMachine->updateStateMachine();

	UpdateSleepTime mine = IS_STATE_SLEEP(stRet) ? UPDATE_SLEEP(GET_STATE_SLEEP_FRAMES(stRet)) : UPDATE_SLEEP_NONE;

	// extend
	UpdateSleepTime ret = AIUpdateInterface::update();
	return (mine < ret) ? mine : ret;
}

// ?privateDock@SupplyTruckAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z
void SupplyTruckAIUpdate::privateDock( Object *dock, CommandSourceType cmdSource )
{
	AIUpdateInterface::privateDock( dock, cmdSource );

	// If this is a command from a player, I will remember this as my favorite dock to override
	// ResourceManager searches.
	if ((cmdSource == CMD_FROM_PLAYER) && dock)
	{
		// Please note, there is not a separate Warehouse and Center memory by Design.  Because
		// we lack a UI way to click Warehouse and drag to center to set up a specific path, the
		// practical realization has been made that you do not want separate memory.
		m_preferredDock = ((const ObjectWithID *)dock)->getID();
	}
}

// ?isCurrentlyFerryingSupplies@SupplyTruckAIUpdate@@UBE_NXZ
bool SupplyTruckAIUpdate::isCurrentlyFerryingSupplies() const
{
	if (m_supplyTruckStateMachine)
	{
		switch (m_supplyTruckStateMachine->getCurrentStateID())
		{
			case ST_IDLE:
			case ST_BUSY:
			case ST_REGROUPING:
				return false;
			case ST_WANTING:
			case ST_DOCKING:
			case ST_BFME_SIXTH:
				return true;
		}
	}
	return false;
}
