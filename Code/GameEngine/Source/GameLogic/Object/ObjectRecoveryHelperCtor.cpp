// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	virtual void updateModuleAnchor();
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
	unsigned int m_04;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectHelper.h
class ObjectHelper : public UpdateModule
{
public:
	ObjectHelper(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectHelper();
};

class __declspec(novtable) BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class __declspec(novtable) UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class ObjectRecoveryHelper : public ObjectHelper,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	ObjectRecoveryHelper(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectRecoveryHelper();
};

ObjectRecoveryHelper::ObjectRecoveryHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}

ObjectRecoveryHelper::~ObjectRecoveryHelper()
{
}
