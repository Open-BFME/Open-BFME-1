// ??1BroadcastStealthUpdate@@UAE@XZ
// partial score=0.15 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Scratch clean-C++ reconstruction for retail 0x00289E50.
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

class BehaviorModuleInterface
{
public:
	virtual void slot();
};

class LargeGroupBonusIface2
{
public:
	virtual void slot();
};

class BehaviorModule : public ObjectModule,
	public BehaviorModuleInterface, public LargeGroupBonusIface2
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data)
		: ObjectModule(thing, data), m_value14(0), m_value18(-1), m_value1c(-1) {}
	virtual ~BehaviorModule();
	private:
	unsigned int m_value14;
	int m_value18;
	int m_value1c;
};

class SpyVisionUpgradeMux
{
public:
	virtual void slot();
private:
	bool m_upgradeExecuted;
	unsigned char m_pad[3];
};

class BroadcastStealthUpdate : public BehaviorModule,
	public SpyVisionUpgradeMux
{
public:
	virtual ~BroadcastStealthUpdate();
private:
	_STL::list<int> m_broadcastObjects;
	unsigned int m_broadcastObjectCount;
	_STL::list<int> m_pendingObjects;
};

// ??1BroadcastStealthUpdate@@UAE@XZ
BroadcastStealthUpdate::~BroadcastStealthUpdate()
{
}
