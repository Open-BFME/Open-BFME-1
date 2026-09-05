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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	ActiveBody( Thing *thing, const ModuleData *moduleData );
	virtual ~ActiveBody();

private:
	// The three module bases reach +0x14; StructureBody's own first member is
	// at +0xE0, so this is what sits between. Only its size is claimed.
	unsigned char m_unmodelled_14[ 0xE0 - 0x14 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureBody.h
class StructureBody : public ActiveBody
{
public:
	StructureBody( Thing *thing, const ModuleData *moduleData );
	virtual ~StructureBody();

private:
	int m_unmodelled_E0;			// +0xE0, zeroed by the constructor
};

StructureBody::StructureBody( Thing *thing, const ModuleData *moduleData )
	: ActiveBody( thing, moduleData ), m_unmodelled_E0( 0 )
{
}

StructureBody::~StructureBody()
{
}
