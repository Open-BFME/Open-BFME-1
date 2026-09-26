// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class PassiveAreaEffectBehaviorRoot
{
public:
	PassiveAreaEffectBehaviorRoot(Thing *, const ModuleData *);
	virtual ~PassiveAreaEffectBehaviorRoot();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class PassiveAreaEffectBehaviorInterface
{
public:
	virtual void slot();
};

class PassiveAreaEffectUpdateInterface
{
public:
	virtual void slot();
};

class PassiveAreaEffectUpdateModule : public PassiveAreaEffectBehaviorRoot,
	public PassiveAreaEffectBehaviorInterface,
	public PassiveAreaEffectUpdateInterface
{
public:
	PassiveAreaEffectUpdateModule(Thing *thing, const ModuleData *moduleData)
		: PassiveAreaEffectBehaviorRoot(thing, moduleData),
		  m_nextCallFrameAndPhase(0),
		  m_indexInLogic(-1),
		  m_updateState(-1)
	{
	}

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	Object *getObject() const { return m_object; }

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class PassiveAreaEffectBehavior : public PassiveAreaEffectUpdateModule
{
public:
	PassiveAreaEffectBehavior(Thing *, const ModuleData *);

private:
	unsigned int m_unknown20;
	_STL::list<int> m_affectedObjects;
};

// ??0PassiveAreaEffectBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
PassiveAreaEffectBehavior::PassiveAreaEffectBehavior(Thing *thing,
	const ModuleData *moduleData)
	: PassiveAreaEffectUpdateModule(thing, moduleData)
{
	m_unknown20 = 0;
	m_affectedObjects.clear();
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}
