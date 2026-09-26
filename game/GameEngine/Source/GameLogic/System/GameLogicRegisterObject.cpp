// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// GameLogic::registerObject, RVA0x0038E4C0,298B. Object constructor1D29A0
// calls this at1D39D9 through ILT2923F immediately after partition registration;
// the corresponding Object.cpp constructor names registerObject explicitly.
// BFME appends objects using head+A8/tail+AC and indexes their ID in hash_map+B0.
// Update modules receive an initial frame of at least one and enter either
// a phase vector+C4 or the forever-sleeping vector+F4. These offsets agree
// with independently recovered friend_awakenUpdateModule at38D870.
// The link helper retains its existing neutral matched identity at1BEB70.

#define _STLP_USE_NEWALLOC 1
#include <vector>
#include <hash_map>

typedef unsigned int UnsignedInt;
typedef int Int;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class ModuleData;
class Object;

class Module
{
public:
	virtual ~Module();
	virtual Int getModuleNameKey() const;
	virtual void onObjectCreated();
	virtual void onDrawableBoundToObject();
	virtual void preloadAssets(Int);
	virtual void onDelete();
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess();

private:
	const ModuleData *m_moduleData;
};

class ObjectModule : public Module
{
public:
	virtual void onCapture(Object *, Object *);

private:
	Object *m_object;
};

class BodyModuleInterface;
class CollideModuleInterface;
class ContainModuleInterface;
class CreateModuleInterface;
class DamageModuleInterface;
class DestroyModuleInterface;
class DieModuleInterface;
class SpecialPowerModuleInterface;
class UpdateModuleInterface;

class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody() = 0;
	virtual CollideModuleInterface *getCollide() = 0;
	virtual ContainModuleInterface *getContain() = 0;
	virtual CreateModuleInterface *getCreate() = 0;
	virtual DamageModuleInterface *getDamage() = 0;
	virtual DestroyModuleInterface *getDestroy() = 0;
	virtual DieModuleInterface *getDie() = 0;
	virtual SpecialPowerModuleInterface *getSpecialPower() = 0;
	virtual UpdateModuleInterface *getUpdate() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
	virtual Int getUpdatePhase() const;

	UnsignedInt m_nextCallFrame;
	Int m_indexInLogic;
	Int m_phaseInLogic;

	UnsignedInt friend_getNextCallFrame() const
	{
		return m_nextCallFrame;
	}

	void friend_setNextCallFrame(UnsignedInt frame)
	{
		if (frame > UPDATE_SLEEP_FOREVER)
			frame = UPDATE_SLEEP_FOREVER;
		m_nextCallFrame = frame;
	}

	void friend_setIndexInLogic(Int index)
	{
		m_phaseInLogic = -1;
		m_indexInLogic = index;
	}

	void friend_setIndexInLogic(Int index, Int phase)
	{
		m_phaseInLogic = phase;
		m_indexInLogic = index;
	}

};

typedef UpdateModule *UpdateModulePtr;

class BfmeLinkXN
{
public:
    void bfmeInsertXN(BfmeLinkXN **head, BfmeLinkXN **tail);
};

class Object
{
public:
    int getID() const { return id; }
    char pad00[0x74];
    int id;
    char pad78[0x178];
    BehaviorModule **modules;
};

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectPtrHash;

class GameLogic
{
public:
    void registerObject(Object *obj);
    unsigned getFrame() { return frame; }

    char pad00[0x3C];
    unsigned frame;
    char pad40[0x68];
    Object *objList;
    Object *objTail;
    ObjectPtrHash lookup;
    _STL::vector<UpdateModule *> phaseUpdates[4];
    _STL::vector<UpdateModule *> sleeping;

    void addObjectToLookupTable(Object *obj)
    {
        if (obj)
            lookup[obj->getID()] = obj;
    }
};

extern GameLogic *TheBfmeGameLogic;

void GameLogic::registerObject(Object *obj)
{
    ((BfmeLinkXN *)obj)->bfmeInsertXN((BfmeLinkXN **)&objList, (BfmeLinkXN **)&objTail);
    addObjectToLookupTable(obj);
    unsigned now = TheBfmeGameLogic->getFrame();
    if (now == 0)
        now = 1;

    for (BehaviorModule **b = obj->modules; *b; ++b)
    {
        UpdateModule *u = (UpdateModule *)(*b)->getUpdate();
        if (!u)
            continue;
        if (u->friend_getNextCallFrame() == 0)
            u->friend_setNextCallFrame(now);
        if (u->friend_getNextCallFrame() == UPDATE_SLEEP_FOREVER)
        {
            u->friend_setIndexInLogic(sleeping.size(), -1);
            sleeping.push_back(u);
        }
        else
        {
            int phase = u->getUpdatePhase();
            _STL::vector<UpdateModule *> &updates = phaseUpdates[phase];
            u->friend_setIndexInLogic(updates.size(), phase);
            updates.push_back(u);
        }
    }
}
