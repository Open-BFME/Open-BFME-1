// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class Module
{
public:
	virtual ~Module();
private:
	const ModuleData *m_moduleData;
};
class ObjectModule : public Module
{
public:
	ObjectModule(Thing *, const ModuleData *);
private:
	Thing *m_object;
};
class BehaviorModuleInterface { public: virtual void anchor(); };
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data) : ObjectModule(thing, data) {}
	virtual ~BehaviorModule() {}
};
class DestroyModuleInterface { public: virtual void onDestroy() = 0; };
class DestroyModule : public BehaviorModule, public DestroyModuleInterface
{
public:
	DestroyModule(Thing *, const ModuleData *);
protected:
	virtual ~DestroyModule();
};

DestroyModule::DestroyModule(Thing *thing, const ModuleData *data)
	: BehaviorModule(thing, data)
{
}

DestroyModule::~DestroyModule() {}
