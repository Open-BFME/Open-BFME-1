// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// COUNT lane near-twin of ?onDelete@WorkerAIUpdate@@UAEXXZ @ 0x002C9090
// (WorkerAIUpdateOnDelete.cpp). Byte-identical except the task array starts
// at +0x344 instead of +0x34C -- eight bytes earlier, so this sibling's
// AIUpdateInterfaceSlice-equivalent private slice is 8 bytes smaller. Since
// this isn't literally WorkerAIUpdate (a different RVA can't share its
// mangled name), the owner and its interface slice are address-derived; the
// interface vtables, task struct and control flow are otherwise identical.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int ObjectID;
typedef unsigned char Bool;

class Object;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

private:
	char m_slicePad[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged(void);

	void clearActivelyBeingConstructed(void)
	{
		const unsigned int activelyBeingConstructed = 0x10;
		const volatile unsigned char *conditionByte =
			reinterpret_cast<const volatile unsigned char *>(&m_conditionState);
		if (*conditionByte & activelyBeingConstructed)
		{
			m_conditionState &= ~activelyBeingConstructed;
			notifyModelConditionChanged();
		}
	}

private:
	char m_slicePad[0x118];
	unsigned int m_conditionState;
};

class Rva002B7F80InterfaceSlice
{
public:
	virtual ~Rva002B7F80InterfaceSlice(void) = 0;
	virtual void onDelete(void) = 0;

private:
	char m_slicePad[0x33c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
class Rva002B7F80DozerAIInterface
{
public:
	virtual void onDelete(void) = 0;
	virtual float getRepairHealthPerSecond(void) const = 0;
	virtual float getBoredTime(void) const = 0;
	virtual float getBoredRange(void) const = 0;
	virtual Object *construct(void *, const void *, float, void *, Bool) = 0;
	virtual int getMostRecentCommand(void) = 0;
	virtual Bool isTaskPending(int task) = 0;
	virtual ObjectID getTaskTarget(int task) = 0;
	virtual Bool isAnyTaskPending(void) = 0;
	virtual int getCurrentTask(void) const = 0;
	virtual void setCurrentTask(int task) = 0;
	virtual Bool getIsRebuild(void) = 0;
	virtual void newTask(int task, Object *target) = 0;
	virtual void cancelTask(int task) = 0;
	virtual void internalTaskComplete(int task) = 0;
	virtual void internalCancelTask(int task) = 0;
	virtual void internalTaskCompleteOrCancelled(int task) = 0;
	virtual const void *getDockPoint(int task, int point) = 0;
	virtual void setBuildSubTask(int task) = 0;
	virtual int getBuildSubTask(void) = 0;
	virtual Bool canAcceptNewRepair(Object *target) = 0;
	virtual void createBridgeScaffolding(Object *target) = 0;
	virtual void removeBridgeScaffolding(Object *target) = 0;
	virtual void startBuildingSound(const void *sound, ObjectID constructionSiteID) = 0;
	virtual void finishBuildingSound(void) = 0;
};

class Rva002B7F80Update : public Rva002B7F80InterfaceSlice,
	public Rva002B7F80DozerAIInterface
{
public:
	virtual void onDelete(void);

private:
	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		unsigned int m_taskOrderFrame;
	};

	DozerTaskInfo m_task[3];
};

void Rva002B7F80Update::onDelete(void)
{
	int i;

	for (i = 0; i < 3; ++i)
	{
		if (isTaskPending(i))
			cancelTask(i);
	}

	for (i = 0; i < 3; ++i)
	{
		Object *goalObject = TheGameLogic->findObjectByID(m_task[i].m_targetObjectID);
		if (goalObject != 0)
			goalObject->clearActivelyBeingConstructed();
	}

	finishBuildingSound();
}
