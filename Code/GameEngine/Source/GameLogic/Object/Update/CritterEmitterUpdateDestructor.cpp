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
class CritterEmitterUpdateInterface { public: virtual void anchor(); };
class CritterEmitterUpdate : public UpdateModule, public CritterEmitterUpdateInterface
{
public:
	static void forceDestructorEmission();
protected:
	virtual ~CritterEmitterUpdate();
};

CritterEmitterUpdate::~CritterEmitterUpdate() {}

// ?forceDestructorEmission@CritterEmitterUpdate@@SAXXZ absent-from-retail
void CritterEmitterUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	CritterEmitterUpdate value;
}
