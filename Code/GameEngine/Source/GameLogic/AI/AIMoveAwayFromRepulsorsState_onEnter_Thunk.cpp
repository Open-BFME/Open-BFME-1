// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_FAILURE = -2
};

enum ObjectID
{
	INVALID_OBJECT_ID
};

enum LocomotorSetType
{
	LOCOMOTORSET_PANIC = 4
};

enum ModelConditionFlagType
{
	MODELCONDITION_PANICKING = 12
};

class ModelConditionFlags
{
public:
	Bool test(ModelConditionFlagType condition) const
	{
		return (m_bits & (1u << condition)) != 0;
	}

	void set(ModelConditionFlagType condition)
	{
		m_bits |= 1u << condition;
	}

private:
	UnsignedInt m_bits;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

#define BFME_VTABLE_SLOT(offset) virtual void slot##offset();

class BfmeAIUpdateVTable
{
public:
	BFME_VTABLE_SLOT(000) BFME_VTABLE_SLOT(004) BFME_VTABLE_SLOT(008) BFME_VTABLE_SLOT(00C)
	BFME_VTABLE_SLOT(010) BFME_VTABLE_SLOT(014) BFME_VTABLE_SLOT(018) BFME_VTABLE_SLOT(01C)
	BFME_VTABLE_SLOT(020) BFME_VTABLE_SLOT(024) BFME_VTABLE_SLOT(028) BFME_VTABLE_SLOT(02C)
	BFME_VTABLE_SLOT(030) BFME_VTABLE_SLOT(034) BFME_VTABLE_SLOT(038) BFME_VTABLE_SLOT(03C)
	BFME_VTABLE_SLOT(040) BFME_VTABLE_SLOT(044) BFME_VTABLE_SLOT(048) BFME_VTABLE_SLOT(04C)
	BFME_VTABLE_SLOT(050) BFME_VTABLE_SLOT(054) BFME_VTABLE_SLOT(058) BFME_VTABLE_SLOT(05C)
	BFME_VTABLE_SLOT(060) BFME_VTABLE_SLOT(064) BFME_VTABLE_SLOT(068) BFME_VTABLE_SLOT(06C)
	BFME_VTABLE_SLOT(070) BFME_VTABLE_SLOT(074) BFME_VTABLE_SLOT(078) BFME_VTABLE_SLOT(07C)
	BFME_VTABLE_SLOT(080) BFME_VTABLE_SLOT(084) BFME_VTABLE_SLOT(088) BFME_VTABLE_SLOT(08C)
	BFME_VTABLE_SLOT(090) BFME_VTABLE_SLOT(094) BFME_VTABLE_SLOT(098) BFME_VTABLE_SLOT(09C)
	BFME_VTABLE_SLOT(0A0) BFME_VTABLE_SLOT(0A4) BFME_VTABLE_SLOT(0A8) BFME_VTABLE_SLOT(0AC)
	BFME_VTABLE_SLOT(0B0) BFME_VTABLE_SLOT(0B4) BFME_VTABLE_SLOT(0B8) BFME_VTABLE_SLOT(0BC)
	BFME_VTABLE_SLOT(0C0) BFME_VTABLE_SLOT(0C4) BFME_VTABLE_SLOT(0C8) BFME_VTABLE_SLOT(0CC)
	BFME_VTABLE_SLOT(0D0) BFME_VTABLE_SLOT(0D4) BFME_VTABLE_SLOT(0D8) BFME_VTABLE_SLOT(0DC)
	BFME_VTABLE_SLOT(0E0) BFME_VTABLE_SLOT(0E4) BFME_VTABLE_SLOT(0E8) BFME_VTABLE_SLOT(0EC)
	BFME_VTABLE_SLOT(0F0) BFME_VTABLE_SLOT(0F4) BFME_VTABLE_SLOT(0F8) BFME_VTABLE_SLOT(0FC)
	BFME_VTABLE_SLOT(100) BFME_VTABLE_SLOT(104) BFME_VTABLE_SLOT(108) BFME_VTABLE_SLOT(10C)
	BFME_VTABLE_SLOT(110) BFME_VTABLE_SLOT(114) BFME_VTABLE_SLOT(118) BFME_VTABLE_SLOT(11C)
	BFME_VTABLE_SLOT(120) BFME_VTABLE_SLOT(124) BFME_VTABLE_SLOT(128) BFME_VTABLE_SLOT(12C)
	BFME_VTABLE_SLOT(130) BFME_VTABLE_SLOT(134) BFME_VTABLE_SLOT(138) BFME_VTABLE_SLOT(13C)
	BFME_VTABLE_SLOT(140) BFME_VTABLE_SLOT(144) BFME_VTABLE_SLOT(148) BFME_VTABLE_SLOT(14C)
	BFME_VTABLE_SLOT(150) BFME_VTABLE_SLOT(154) BFME_VTABLE_SLOT(158) BFME_VTABLE_SLOT(15C)
	BFME_VTABLE_SLOT(160) BFME_VTABLE_SLOT(164) BFME_VTABLE_SLOT(168) BFME_VTABLE_SLOT(16C)
	BFME_VTABLE_SLOT(170) BFME_VTABLE_SLOT(174) BFME_VTABLE_SLOT(178) BFME_VTABLE_SLOT(17C)
	BFME_VTABLE_SLOT(180) BFME_VTABLE_SLOT(184) BFME_VTABLE_SLOT(188) BFME_VTABLE_SLOT(18C)
	BFME_VTABLE_SLOT(190) BFME_VTABLE_SLOT(194) BFME_VTABLE_SLOT(198) BFME_VTABLE_SLOT(19C)
	BFME_VTABLE_SLOT(1A0) BFME_VTABLE_SLOT(1A4) BFME_VTABLE_SLOT(1A8) BFME_VTABLE_SLOT(1AC)
	BFME_VTABLE_SLOT(1B0) BFME_VTABLE_SLOT(1B4) BFME_VTABLE_SLOT(1B8) BFME_VTABLE_SLOT(1BC)
	BFME_VTABLE_SLOT(1C0) BFME_VTABLE_SLOT(1C4) BFME_VTABLE_SLOT(1C8) BFME_VTABLE_SLOT(1CC)
	BFME_VTABLE_SLOT(1D0) BFME_VTABLE_SLOT(1D4) BFME_VTABLE_SLOT(1D8) BFME_VTABLE_SLOT(1DC)
	BFME_VTABLE_SLOT(1E0) BFME_VTABLE_SLOT(1E4) BFME_VTABLE_SLOT(1E8) BFME_VTABLE_SLOT(1EC)
	BFME_VTABLE_SLOT(1F0) BFME_VTABLE_SLOT(1F4) BFME_VTABLE_SLOT(1F8)
};

#undef BFME_VTABLE_SLOT

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public BfmeAIUpdateVTable
{
public:
	virtual void chooseLocomotorSet(LocomotorSetType set);
	void requestSafePath(ObjectID enemyID);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	float getVisionRange() const;

	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

	ObjectID getID() const
	{
		return m_id;
	}

	void setModelConditionState(ModelConditionFlagType condition)
	{
		if (!m_modelConditionFlags.test(condition))
		{
			m_modelConditionFlags.set(condition);
			notifyModelConditionChanged();
		}
	}

	void notifyModelConditionChanged();

private:
	unsigned char m_unreconstructed_000[0x74];
	ObjectID m_id;
	unsigned char m_unreconstructed_078[0xA0];
	ModelConditionFlags m_modelConditionFlags;
	unsigned char m_unreconstructed_11C[0xE8];
	AIUpdateInterface *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removeGoal(Object *object);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Object *findClosestRepulsor(const Object *object, float visionRange);

	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

private:
	unsigned char m_unreconstructed_00[0x0C];
	Pathfinder *m_pathfinder;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getOwner() const
	{
		return m_owner;
	}

private:
	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	virtual StateReturnType onEnter();

protected:
	unsigned char m_unreconstructed_04[0x18];
	StateMachine *m_machine;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();

	Object *getMachineOwner() const
	{
		return m_machine->getOwner();
	}

	void setAdjustsDestination(Bool adjusts)
	{
		m_adjustDestinations = adjusts;
	}

protected:
	unsigned char m_unreconstructed_20[0x04];
	Coord3D m_goalPosition;
	unsigned char m_unreconstructed_30[0x1C];
	Bool m_adjustDestinations;
	unsigned char m_unreconstructed_4D[0x03];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveAwayFromRepulsorsState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	int m_okToRepathTimes;
	Bool m_checkForPath;
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern AI *TheAI;
extern void j_0003a17a();

typedef void (__cdecl *DebugLogFunction)(void *, const char *);

StateReturnType AIMoveAwayFromRepulsorsState::onEnter()
{
	if (g_012F0239 && g_012ED4FC)
	{
		((DebugLogFunction)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(FALSE) 11");
	}

	setAdjustsDestination(false);
	Object *object = getMachineOwner();
	Object *enemy = TheAI->findClosestRepulsor(getMachineOwner(), object->getVisionRange());
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!enemy || !ai)
		return STATE_FAILURE;

	ai->chooseLocomotorSet(LOCOMOTORSET_PANIC);
	if (object)
		object->setModelConditionState(MODELCONDITION_PANICKING);

	m_okToRepathTimes = 1;
	m_checkForPath = true;
	TheAI->pathfinder()->removeGoal(object);
	ai->requestSafePath(enemy->getID());
	return AIInternalMoveToState::onEnter();
}
