// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h
class CreateModuleInterface
{
public:
	virtual void createModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h
class CreateModule : public BehaviorModule,
	public CreateModuleInterface,
	public ModuleInterface
{
public:
	CreateModule( Thing *thing, const ModuleData *moduleData );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterCreate.h
class SupplyCenterCreate : public CreateModule
{
public:
	SupplyCenterCreate( Thing *thing, const ModuleData *moduleData );
};

SupplyCenterCreate::SupplyCenterCreate( Thing *thing, const ModuleData *moduleData )
	: CreateModule( thing, moduleData )
{
}
