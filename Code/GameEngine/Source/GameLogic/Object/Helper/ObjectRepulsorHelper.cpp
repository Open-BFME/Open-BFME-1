// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	virtual void updateModuleAnchor();
	virtual ~UpdateModule();

private:
	unsigned int m_storage[2];
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectRepulsorHelper.h
class ObjectRepulsorHelper : public ObjectHelper,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	ObjectRepulsorHelper(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectRepulsorHelper();
};

ObjectRepulsorHelper::ObjectRepulsorHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
}

ObjectRepulsorHelper::~ObjectRepulsorHelper()
{
}
