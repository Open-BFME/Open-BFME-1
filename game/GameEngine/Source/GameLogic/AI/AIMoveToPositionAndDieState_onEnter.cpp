// cl: /DNDEBUG /MD /EHsc

// AIMoveToPositionAndDieState::onEnter (0x0017EF50): slot 4 of
// AIMoveToPositionAndDieState's table 0x0109AB50 (slot 0
// ??_GAIMoveToPositionAndDieState); its update is matched in slot 6. The body
// is AIMoveAndDeleteState::onEnter's without the model-condition bits, logging
// "... 60" where that one logs "... 50".

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

typedef void (__cdecl *AIMoveToPositionAndDieCritterDesyncLog)(void *, const char *);

// Same spelling as Rva00174A20State_update.cpp: TheCRCParameterCheck's
// CritterDesync log, called through ILT 0x0003A17A.
static void aiMoveToPositionAndDie_log(const char *message)
{
	if (g_012F0239 && g_012ED4FC)
		((AIMoveToPositionAndDieCritterDesyncLog)j_0003a17a)(g_012ED4FC, message);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }

	UnsignedByte m_unreconstructed_000[0x38];
	Coord3D m_position;									///< this+0x38
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	Object *getOwner() { return m_owner; }
	void lock() { m_locked = true; }

	UnsignedByte m_unreconstructed_000[0x10];
	Object *m_owner;									///< this+0x10
	UnsignedByte m_unreconstructed_014[0x24 - 0x14];
	Coord3D m_goalPosition;								///< this+0x24
	UnsignedByte m_unreconstructed_030[0x40 - 0x30];
	Bool m_locked;										///< this+0x40
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
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
	UnsignedByte m_unreconstructed_030[0x1c];
	Bool m_adjustDestinations;							///< this+0x4C
};

class AIMoveToPositionAndDieState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

protected:
	Bool m_appendGoalPosition;							///< this+0x50
};

// ?onEnter@AIMoveToPositionAndDieState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveToPositionAndDieState::onEnter()
{
	aiMoveToPositionAndDie_log("CritterDesync: setAdjustDestination(FALSE) 60");
	setAdjustsDestination(false);
	getMachine()->lock();
	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();
	m_appendGoalPosition = true; // We may be moving off the map.

	return AIInternalMoveToState::onEnter();
}
