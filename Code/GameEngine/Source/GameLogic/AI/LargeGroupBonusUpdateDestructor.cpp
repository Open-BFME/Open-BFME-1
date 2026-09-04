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
class LargeGroupBonusUpdateInterface { public: virtual void anchor(); };
class LargeGroupBonusUpdate : public UpdateModule, public LargeGroupBonusUpdateInterface
{
public:
	static void forceDestructorEmission();
protected:
	virtual ~LargeGroupBonusUpdate();
};

LargeGroupBonusUpdate::~LargeGroupBonusUpdate() {}

// ?forceDestructorEmission@LargeGroupBonusUpdate@@SAXXZ absent-from-retail
void LargeGroupBonusUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	LargeGroupBonusUpdate value;
}
