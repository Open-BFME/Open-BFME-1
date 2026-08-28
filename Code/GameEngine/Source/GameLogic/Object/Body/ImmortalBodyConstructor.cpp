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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModule : public BehaviorModule,
	public BodyModuleInterface,
	public ModuleInterface
{
public:
	BodyModule( Thing *thing, const ModuleData *moduleData );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h
class ImmortalBody : public BodyModule
{
public:
	ImmortalBody( Thing *thing, const ModuleData *moduleData );
};

ImmortalBody::ImmortalBody( Thing *thing, const ModuleData *moduleData )
	: BodyModule( thing, moduleData )
{
}
