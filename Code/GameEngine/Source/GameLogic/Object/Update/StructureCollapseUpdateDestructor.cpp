// cl: /DNDEBUG /MD /EHsc

class Module
{
public:
	virtual ~Module();

private:
	unsigned int m_moduleStorage[2];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor();
};

class BehaviorModule : public Module, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModuleInterface
{
public:
	virtual void updateAnchor();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_updateModuleStorage[3];
};

class DieModuleInterface
{
public:
	virtual void onDie();
};

class StructureCollapseUpdate : public UpdateModule, public DieModuleInterface
{
public:
	static void forceDestructorEmission();

protected:
	virtual ~StructureCollapseUpdate();
};

StructureCollapseUpdate::~StructureCollapseUpdate()
{
}

// ?forceDestructorEmission@StructureCollapseUpdate@@SAXXZ absent-from-retail
void StructureCollapseUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	StructureCollapseUpdate value;
}
