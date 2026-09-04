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
class CreateModuleInterface { public: virtual void onCreate() = 0; };
class CreateModule : public BehaviorModule, public CreateModuleInterface
{
public:
	CreateModule(Thing *, const ModuleData *);
protected:
	virtual ~CreateModule();
private:
	bool m_needToRunOnBuildComplete;
};

CreateModule::CreateModule(Thing *thing, const ModuleData *data)
	: BehaviorModule(thing, data), m_needToRunOnBuildComplete(true)
{
}

CreateModule::~CreateModule() {}
