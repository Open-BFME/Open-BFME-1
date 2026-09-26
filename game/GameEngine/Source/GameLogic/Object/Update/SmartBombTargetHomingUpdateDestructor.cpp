// cl: /DNDEBUG /MD /EHsc

class Module { public: virtual ~Module(); private: unsigned int m_storage[2]; };
class BehaviorModuleInterface { public: virtual void anchor(); };
class BehaviorModule : public Module, public BehaviorModuleInterface { public: virtual ~BehaviorModule() {} };
class UpdateModuleInterface { public: virtual void anchor(); };
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}
private:
	unsigned int m_storage[3];
};
class SmartBombTargetHomingUpdateInterface { public: virtual void anchor(); };
class SmartBombTargetHomingUpdate : public UpdateModule, public SmartBombTargetHomingUpdateInterface
{
public:
	static void forceDestructorEmission();
protected:
	virtual ~SmartBombTargetHomingUpdate();
};

SmartBombTargetHomingUpdate::~SmartBombTargetHomingUpdate() {}

// ?forceDestructorEmission@SmartBombTargetHomingUpdate@@SAXXZ absent-from-retail
void SmartBombTargetHomingUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	SmartBombTargetHomingUpdate value;
}
