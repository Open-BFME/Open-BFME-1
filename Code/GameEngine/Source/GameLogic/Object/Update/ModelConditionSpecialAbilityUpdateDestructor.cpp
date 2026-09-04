// cl: /DNDEBUG /MD /EHsc

class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();

private:
	unsigned int m_behaviorModuleStorage[2];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void updateAnchor();

private:
	unsigned int m_updateModuleStorage[3];
};

class ModuleInterface
{
public:
	virtual void moduleAnchor();
};

class ModelConditionSpecialAbilityUpdate : public SpecialAbilityUpdate,
	public BehaviorModuleInterface,
	public UpdateModuleInterface,
	public ModuleInterface
{
protected:
	virtual ~ModelConditionSpecialAbilityUpdate();
};

ModelConditionSpecialAbilityUpdate::~ModelConditionSpecialAbilityUpdate()
{
}
