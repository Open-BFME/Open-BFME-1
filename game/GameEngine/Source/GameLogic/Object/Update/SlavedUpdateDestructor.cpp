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

class SlavedUpdateInterface
{
public:
	virtual void slavedUpdateAnchor();
};

class SlavedUpdate : public UpdateModule, public SlavedUpdateInterface
{
public:
	static void forceDestructorEmission();

protected:
	virtual ~SlavedUpdate();
};

SlavedUpdate::~SlavedUpdate()
{
}

// ?forceDestructorEmission@SlavedUpdate@@SAXXZ absent-from-retail
void SlavedUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	SlavedUpdate value;
}
