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
class AttributeModifierAuraUpdateInterface { public: virtual void anchor(); };
class AttributeModifierAuraUpdate : public UpdateModule, public AttributeModifierAuraUpdateInterface
{
public:
	static void forceDestructorEmission();
protected:
	virtual ~AttributeModifierAuraUpdate();
};

AttributeModifierAuraUpdate::~AttributeModifierAuraUpdate() {}

// ?forceDestructorEmission@AttributeModifierAuraUpdate@@SAXXZ absent-from-retail
void AttributeModifierAuraUpdate::forceDestructorEmission()
{
	// A local instance makes MSVC emit the protected scalar-deleting destructor.
	AttributeModifierAuraUpdate value;
}
