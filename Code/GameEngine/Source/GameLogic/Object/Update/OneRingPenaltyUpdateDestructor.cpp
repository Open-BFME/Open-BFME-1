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

class OneRingPenaltyUpdateInterface
{
public:
	virtual void penaltyAnchor();
};

class OneRingPenaltyUpdate : public UpdateModule, public OneRingPenaltyUpdateInterface
{
public:
	static void forceDestructorEmission();

protected:
	virtual ~OneRingPenaltyUpdate();
};

OneRingPenaltyUpdate::~OneRingPenaltyUpdate()
{
}

// ?forceDestructorEmission@OneRingPenaltyUpdate@@SAXXZ absent-from-retail
void OneRingPenaltyUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	OneRingPenaltyUpdate value;
}
