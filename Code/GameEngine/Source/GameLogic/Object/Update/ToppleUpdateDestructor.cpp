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

class CollideModuleInterface { public: virtual void onCollide(); };
class ToppleUpdate : public UpdateModule, public CollideModuleInterface
{
public:
	static void forceDestructorEmission();
protected:
	virtual ~ToppleUpdate();
};

ToppleUpdate::~ToppleUpdate() {}

// ?forceDestructorEmission@ToppleUpdate@@SAXXZ absent-from-retail
void ToppleUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	ToppleUpdate value;
}
