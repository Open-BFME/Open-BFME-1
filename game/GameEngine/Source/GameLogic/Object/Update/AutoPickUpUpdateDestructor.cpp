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
class AutoPickUpUpdateInterface { public: virtual void anchor(); };
class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateInterface
{
public:
	static void forceDestructorEmission();
protected:
	virtual ~AutoPickUpUpdate();
};

AutoPickUpUpdate::~AutoPickUpUpdate() {}

// ?forceDestructorEmission@AutoPickUpUpdate@@SAXXZ absent-from-retail
void AutoPickUpUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	AutoPickUpUpdate value;
}
