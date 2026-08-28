// cl: /DNDEBUG /MD /EHsc
// readable body of ??0OCLUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/OCLUpdate.cpp

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *, const ModuleData * );

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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	UpdateModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData ),
		  m_nextCallFrameAndPhase( 0 ),
		  m_indexInLogic( -1 ),
		  m_oclIndex( -1 ),
		  m_delay( 0 ),
		  m_count( 0 )
	{
	}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_oclIndex;
	unsigned int m_delay;
	unsigned int m_count;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h
class OCLUpdate : public UpdateModule
{
public:
	OCLUpdate( Thing *, const ModuleData * );
};

OCLUpdate::OCLUpdate( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
}
