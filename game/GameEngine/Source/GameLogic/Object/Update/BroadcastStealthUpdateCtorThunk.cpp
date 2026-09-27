// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: BroadcastStealthUpdate constructor.  Its module factory and
// destructor establish the class while the two STLport lists fix the tail.

#include <list>

class Thing;
class ModuleData;
class Object;

class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};
class BehaviorModuleInterface { public: virtual void slot(); };
class UpdateModuleInterface { public: virtual void slot(); };

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data)
		: ObjectModule(thing, data) {}
	virtual ~BehaviorModule();
};

// The inlined base is UpdateModule, not BehaviorModule: retail stores the three
// tables that ??0UpdateModule (0x001B2FB0) installs, and the unwind action for
// this base calls ~UpdateModule (0x001B2B10).
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data)
		: BehaviorModule(thing, data), m_value14(0), m_value18(-1), m_value1c(-1) {}
	virtual ~UpdateModule();
	void setWakeFrame(Object *, unsigned int);
private:
	unsigned int m_value14;
	int m_value18;
	int m_value1c;
};

class SpyVisionUpgradeMux
{
public:
	SpyVisionUpgradeMux();
	virtual void slot();
private:
	bool m_upgradeExecuted;
	unsigned char m_pad[3];
};

class BroadcastStealthUpdate : public UpdateModule,
	public SpyVisionUpgradeMux
{
public:
	BroadcastStealthUpdate(Thing *, const ModuleData *);
	virtual ~BroadcastStealthUpdate();
	virtual void slot();
private:
	_STL::list<int> m_broadcastObjects;
	unsigned int m_broadcastObjectCount;
	_STL::list<int> m_pendingObjects;
};

// ??0BroadcastStealthUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
BroadcastStealthUpdate::BroadcastStealthUpdate(
	Thing *thing, const ModuleData *data)
	: UpdateModule(thing, data), SpyVisionUpgradeMux()
{
	setWakeFrame(m_object, 0x3fffffff);
	m_broadcastObjectCount = m_broadcastObjects.size();
}
