// cl: /DNDEBUG /MD /EHsc
// readable body of ?update@DozerAIUpdate@@UAE?AW4UpdateSleepTime@@XZ: game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp

// BFME DozerAIUpdate::update (0x002B7BB0, 158 B): the Zero Hour body without
// the mine-clearing weapon-set branch. It runs through the UpdateModuleInterface
// view at +0x10 (object at this-8); the DozerAIInterface sits at +0x340 and the
// dozer state machine at +0x35C, as DozerAIUpdateCreateMachinesBfme.cpp has it.



#include "../../../../../Include/GameLogic/Module/UpdateSleepTime.h"
#include "../../../command_source_type.h"
enum DozerTask { DOZER_TASK_INVALID = -1, DOZER_TASK_BUILD = 0, DOZER_TASK_REPAIR = 1 };
#include "../../../../../Include/Common/ObjectID.h"

class Object
{
public:
	// Object::isEffectivelyDead: bit 0 of the private status byte.
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	unsigned char m_unmodelled_000[0x344];
	unsigned char m_privateStatus;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class ActionManager
{
public:
	bool canRepairObject(const Object *obj, const Object *objectToRepair, CommandSourceType commandSource);
};

extern ActionManager *TheActionManager;

class DozerPrimaryStateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void updateStateMachine();
};

#define SLOTS8(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3(); \
	virtual void n##4(); virtual void n##5(); virtual void n##6(); virtual void n##7();
#define SLOTS64(n) SLOTS8(n##0) SLOTS8(n##1) SLOTS8(n##2) SLOTS8(n##3) \
	SLOTS8(n##4) SLOTS8(n##5) SLOTS8(n##6) SLOTS8(n##7)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	SLOTS64(objectModuleSlotA)
	SLOTS64(objectModuleSlotB)

protected:
	Object *getObject() const { return m_object; }

private:
	const void *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	virtual CommandSourceType getLastCommandSource() const;		// primary slot 128 (+0x200)
	virtual UpdateSleepTime update();

private:
	unsigned char m_unmodelled_014[0x340 - 0x14];
};

class DozerAIInterface
{
public:
	virtual void dozerSlot00(); virtual void dozerSlot01(); virtual void dozerSlot02();
	virtual void dozerSlot03(); virtual void dozerSlot04(); virtual void dozerSlot05();
	virtual void dozerSlot06();
	virtual ObjectID getTaskTarget(DozerTask task) const;		// +0x1C
	virtual void dozerSlot08();
	virtual DozerTask getCurrentTask() const;					// +0x24
	virtual void dozerSlot10(); virtual void dozerSlot11(); virtual void dozerSlot12();
	virtual void cancelTask(DozerTask task);					// +0x34
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
class DozerAIUpdate : public AIUpdateInterface, public DozerAIInterface
{
public:
	virtual UpdateSleepTime update();

private:
	void createMachines();

	unsigned char m_unmodelled_344[0x35C - 0x344];
	DozerPrimaryStateMachine *m_dozerMachine;
};

// ?update@DozerAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime DozerAIUpdate::update()
{
	createMachines();

	// extend the normal AI system
	AIUpdateInterface::update();

	// do nothing if we're dead
	if (getObject()->isEffectivelyDead())
		return UPDATE_SLEEP_NONE;

	// get and validate our current task
	DozerTask currentTask = getCurrentTask();
	if (currentTask != DOZER_TASK_INVALID)
	{
		ObjectID taskTarget = getTaskTarget(currentTask);
		Object *targetObject = TheGameLogic->findObjectByID(taskTarget);
		bool invalidTask = false;

		// validate the task and the target
		if (currentTask == DOZER_TASK_REPAIR &&
				TheActionManager->canRepairObject(getObject(), targetObject, getLastCommandSource()) == false)
			invalidTask = true;

		// cancel the task if it's now invalid
		if (invalidTask == true)
			cancelTask(currentTask);
	}

	// run our own state machine
	m_dozerMachine->updateStateMachine();

	return UPDATE_SLEEP_NONE;
}
