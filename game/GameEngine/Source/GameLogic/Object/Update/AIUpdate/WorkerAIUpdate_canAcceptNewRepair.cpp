// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: WorkerAIUpdate::canAcceptNewRepair, retail 0x002C99C0.
//
// The DozerAIInterface vtable pin, the call from WorkerAIUpdate::privateRepair,
// and the identical BFME/Zero Hour repair predicate establish this identity.
// This local ABI view keeps the BFME WorkerAIUpdate secondary-interface slice:
// its task array begins eight bytes later than the one-secondary-base sibling
// at 0x002B87E0.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int ObjectID;
typedef bool Bool;

enum KindOfType
{
	KINDOF_BRIDGE_TOWER = 0x18
};

class Object;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

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

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
};

class WorkerAIUpdateInterfaceSlice
{
public:
	virtual ~WorkerAIUpdateInterfaceSlice(void) = 0;
	virtual void onDelete(void) = 0;

private:
	char m_slicePad[0x33c];
};

class WorkerDozerAIInterface
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

class WorkerAIUpdate : public WorkerAIUpdateInterfaceSlice,
	public WorkerDozerAIInterface
{
public:
	virtual void onDelete(void);
	virtual Bool canAcceptNewRepair(Object *target);

private:
	unsigned char m_secondaryLayoutPad[8];
	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		unsigned int m_taskOrderFrame;
	};
	DozerTaskInfo m_task[3];
};

struct Rva002B7240Source
{
public:
	virtual void unused(void) = 0;
	virtual ObjectID getBridgeID(void) = 0;
};

Rva002B7240Source *Rva002B7240Lookup(ObjectID id);

Bool WorkerAIUpdate::canAcceptNewRepair(Object *obj)
{
	if (obj == 0)
		return false;

	if (getCurrentTask() != 1)
		return true;

	Object *currentRepair = TheGameLogic->findObjectByID(m_task[1].m_targetObjectID);
	if (currentRepair != 0)
	{
		if (currentRepair == obj)
			return false;

		if (((Thing *)currentRepair)->isKindOf(KINDOF_BRIDGE_TOWER) &&
			((Thing *)obj)->isKindOf(KINDOF_BRIDGE_TOWER))
		{
			Rva002B7240Source *currentTowerInterface =
				Rva002B7240Lookup((ObjectID)(unsigned long)currentRepair);
			Rva002B7240Source *newTowerInterface =
				Rva002B7240Lookup((ObjectID)(unsigned long)obj);

			if (currentTowerInterface == 0 || newTowerInterface == 0)
				return false;

			if (currentTowerInterface->getBridgeID() == newTowerInterface->getBridgeID())
				return false;
		}
	}

	return true;
}
