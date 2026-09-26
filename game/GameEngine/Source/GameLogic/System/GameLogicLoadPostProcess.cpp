// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

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

class Object
{
public:
	Object *getNextObject() const
	{
		return m_nextObject;
	}

	BehaviorModule **getBehaviorModules() const
	{
		return m_behaviorModules;
	}

private:
	char m_pad00[0x88];
	Object *m_nextObject;
	char m_pad8c[0x164];
	BehaviorModule **m_behaviorModules;
};

class GameLogic
{

protected:
	virtual void loadPostProcess();

	public:
	UnsignedInt getFrame()
	{
		return m_frame;
	}

	Object *getFirstObject()
	{
		return m_objList;
	}

private:
	char m_pad04[0x38];
	UnsignedInt m_frame;
	char m_pad40[0x60];
	Object *m_objList;
	char m_padA4[0x18];
	_STL::vector<UpdateModulePtr> m_sleepyUpdates[4];
	_STL::vector<UpdateModulePtr> m_normalUpdates;
};

extern GameLogic *TheBfmeGameLogic;

void GameLogic::loadPostProcess()
{
	for (Int phase = 0; phase < 4; ++phase)
	{
		for (_STL::vector<UpdateModulePtr>::iterator it = m_sleepyUpdates[phase].begin();
			it != m_sleepyUpdates[phase].end(); ++it)
		{
			(*it)->friend_setIndexInLogic(-1);
		}
		m_sleepyUpdates[phase].clear();
	}

	for (_STL::vector<UpdateModulePtr>::iterator it = m_normalUpdates.begin();
		it != m_normalUpdates.end(); ++it)
	{
		(*it)->friend_setIndexInLogic(-1);
	}
	m_normalUpdates.clear();

	UnsignedInt now = TheBfmeGameLogic->getFrame();
	if (now == 0)
		now = 1;

	for (Object *obj = getFirstObject(); obj; obj = obj->getNextObject())
	{
		for (BehaviorModule **module = obj->getBehaviorModules(); *module; ++module)
		{
			UpdateModule *update = (UpdateModule *)(*module)->getUpdate();
			if (!update)
				continue;

			if (update->friend_getNextCallFrame() == 0)
				update->friend_setNextCallFrame(now);

			if (update->friend_getNextCallFrame() == UPDATE_SLEEP_FOREVER)
			{
				update->friend_setIndexInLogic(m_normalUpdates.size(), -1);
				m_normalUpdates.push_back(update);
			}
			else
			{
				Int updatePhase = update->getUpdatePhase();
				_STL::vector<UpdateModulePtr> &sleepyUpdates = m_sleepyUpdates[updatePhase];
				update->friend_setIndexInLogic(sleepyUpdates.size(), updatePhase);
				sleepyUpdates.push_back(update);
			}
		}
	}
}
