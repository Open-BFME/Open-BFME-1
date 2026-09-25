// cl: /DNDEBUG /MD /EHsc

// AIMoveAndDeleteState::onEnter (0x0017A430): slot 4 of AIMoveAndDeleteState's
// table 0x0109AAD8 (slot 0 ??_GAIMoveAndDeleteState); its update is matched in
// slot 6. Zero Hour's body, with BFME's CritterDesync log in front of
// setAdjustsDestination and two model-condition bits set on the owner before
// the base onEnter.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef bool Bool;

enum StateReturnType { STATE_CONTINUE = 0 };

struct Coord3D
{
	Real x, y, z;
};

extern UnsignedByte g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a();

typedef void (__cdecl *AIMoveAndDeleteCritterDesyncLog)(void *, const char *);

// Same spelling as Rva00174A20State_update.cpp: TheCRCParameterCheck's
// CritterDesync log, called through ILT 0x0003A17A.
static void aiMoveAndDelete_log(const char *message)
{
	if (g_012F0239 && g_012ED4FC)
		((AIMoveAndDeleteCritterDesyncLog)j_0003a17a)(g_012ED4FC, message);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged();

	const Coord3D *getPosition() const { return &m_position; }

	void bfmeSetModelConditionState( Int bit )
	{
		if (!m_modelConditionFlags.test( bit ))
		{
			m_modelConditionFlags.set( bit );
			notifyModelConditionChanged();
		}
	}

	struct ModelConditionFlags
	{
		// Returns the masked word, not a bool: retail keeps the mask in a register
		// for the test and the set that follows.
		UnsignedInt test( Int i ) const { return m_bits[i >> 5] & (1u << (i & 31)); }
		void set( Int i ) { m_bits[i >> 5] |= (1u << (i & 31)); }
		UnsignedInt m_bits[10];
	};

	UnsignedByte m_pad000[0x38];
	Coord3D m_position;									///< this+0x38
	UnsignedByte m_pad044[0x110 - 0x44];
	ModelConditionFlags m_modelConditionFlags;			///< this+0x110, 320 bits
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	Object *getOwner() { return m_owner; }
	void lock() { m_locked = true; }

	UnsignedByte m_pad000[0x10];
	Object *m_owner;									///< this+0x10
	UnsignedByte m_pad014[0x24 - 0x14];
	Coord3D m_goalPosition;								///< this+0x24
	UnsignedByte m_pad030[0x40 - 0x30];
	Bool m_locked;										///< this+0x40
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

	StateMachine *getMachine() { return m_machine; }
	Object *getMachineOwner() { return m_machine->getOwner(); }
	void setAdjustsDestination( Bool adjustsDestination ) { m_adjustDestinations = adjustsDestination; }

protected:
	UnsignedByte m_pad004[0x18];
	StateMachine *m_machine;							///< this+0x1C
	UnsignedByte m_pad020[4];
	Coord3D m_goalPosition;								///< this+0x24
	UnsignedByte m_pad030[0x1c];
	Bool m_adjustDestinations;							///< this+0x4C
};

class AIMoveAndDeleteState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

protected:
	Bool m_appendGoalPosition;							///< this+0x50
};

// ?onEnter@AIMoveAndDeleteState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveAndDeleteState::onEnter()
{
	aiMoveAndDelete_log("CritterDesync: setAdjustDestination(FALSE) 50");
	setAdjustsDestination(false);
	getMachine()->lock();
	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();
	m_appendGoalPosition = true; // We may be moving off the map.

	Object *obj = getMachineOwner();
	if (obj)
	{
		obj->bfmeSetModelConditionState( 60 );		// word 1, 0x10000000
		obj->bfmeSetModelConditionState( 241 );		// word 7, 0x00020000
	}

	return AIInternalMoveToState::onEnter();
}
