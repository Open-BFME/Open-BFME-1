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
class DelayedUpgradeUpdateInterface { public: virtual void setDelay(); };
class DelayedWeaponSetUpgradeUpdate : public UpdateModule, public DelayedUpgradeUpdateInterface
{
public:
	static void forceDestructorEmission();
protected:
	virtual ~DelayedWeaponSetUpgradeUpdate();
};

DelayedWeaponSetUpgradeUpdate::~DelayedWeaponSetUpgradeUpdate() {}

// ?forceDestructorEmission@DelayedWeaponSetUpgradeUpdate@@SAXXZ absent-from-retail
void DelayedWeaponSetUpgradeUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	DelayedWeaponSetUpgradeUpdate value;
}
