// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	unsigned int m_storage[2];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_storage[3];
};

class ObjectHelper : public UpdateModule
{
public:
	virtual ~ObjectHelper();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectDefectionHelper.h
class ObjectDefectionHelper : public ObjectHelper
{
public:
	static void forceDestructorEmission();
	virtual ~ObjectDefectionHelper();
};

ObjectDefectionHelper::~ObjectDefectionHelper()
{
}

// ?forceDestructorEmission@ObjectDefectionHelper@@SAXXZ absent-from-retail
void ObjectDefectionHelper::forceDestructorEmission()
{
	// Instantiation makes MSVC emit the scalar-deleting destructor used by the retail vtable.
	ObjectDefectionHelper value;
}
