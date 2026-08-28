// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();

private:
	unsigned char m_data[12];
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
};

class AIUpdateInterface : public ObjectModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface,
	public ModuleInterface,
	public AICommandInterface
{
public:
	AIUpdateInterface( Thing *, const ModuleData * );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WanderAIUpdate.h
class WanderAIUpdate : public AIUpdateInterface
{
public:
	WanderAIUpdate( Thing *, const ModuleData * );
};

WanderAIUpdate::WanderAIUpdate( Thing *thing, const ModuleData *moduleData )
	: AIUpdateInterface( thing, moduleData )
{
}
