// cl: /DNDEBUG /MD /EHsc

class Module
{
public:
	virtual ~Module();

private:
	const void *m_moduleData;
};

class ObjectModule : public Module
{
private:
	void *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_wakeFrame;
	int m_moduleStateA;
	int m_moduleStateB;
};

class OCLUpdate : public UpdateModule
{
public:
	static void forceDestructorEmission();

protected:
	virtual ~OCLUpdate();
};

OCLUpdate::~OCLUpdate()
{
}

// ?forceDestructorEmission@OCLUpdate@@SAXXZ absent-from-retail
void OCLUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	OCLUpdate value;
}
