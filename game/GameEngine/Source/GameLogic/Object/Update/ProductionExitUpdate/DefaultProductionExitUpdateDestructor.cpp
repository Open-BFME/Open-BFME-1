// cl: /DNDEBUG /MD /EHsc

class Module
{
public:
	virtual ~Module();
private:
	unsigned int m_moduleStorage[2];
};

class BehaviorModuleInterface { public: virtual void behaviorAnchor(); };
class BehaviorModule : public Module, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModuleInterface { public: virtual void updateAnchor(); };
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}
private:
	unsigned int m_updateModuleStorage[3];
};

class ExitInterface { public: virtual void exitObject(); };
class DefaultProductionExitUpdate : public UpdateModule, public ExitInterface
{
public:
	static void forceDestructorEmission();
protected:
	virtual ~DefaultProductionExitUpdate();
};

DefaultProductionExitUpdate::~DefaultProductionExitUpdate() {}

// ?forceDestructorEmission@DefaultProductionExitUpdate@@SAXXZ absent-from-retail
void DefaultProductionExitUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	DefaultProductionExitUpdate value;
}
