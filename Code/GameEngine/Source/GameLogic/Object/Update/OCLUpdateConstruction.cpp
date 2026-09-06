// cl: /DNDEBUG /MD /EHsc
// readable body of ??0OCLUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/OCLUpdate.cpp
// readable body of ??0OCLUpdateModuleData@@QAE@XZ: Code/GameEngine/Source/GameLogic/Object/Update/OCLUpdate.cpp
//
// Both halves of building an OCLUpdate: the module's constructor, which does
// nothing of its own and exists to run the UpdateModule base with the
// per-instance fields zeroed, and its module data's constructor, which clears
// the four INI-parsed settings. They are the pair a module is made of and each
// sat alone in its own file.
//
// The module data's field names come from retail's own INI field table joined
// to upstream's parse table on the key: retail supplies every offset, upstream
// only the word. The offsets follow from this class's declaration sequence and
// type sizes, never from the old placeholder names. Retail zeroes them in the
// order +0x0c, +0x10, +0x8, byte +0x14.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h
class OCLUpdateModuleData
{
public:
	OCLUpdateModuleData();
	virtual ~OCLUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_ocl;					// +0x08
	unsigned int m_minDelay;				// +0x0C
	unsigned int m_maxDelay;				// +0x10
	unsigned char m_isCreateAtEdge;				// +0x14
};

// ??0OCLUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
OCLUpdate::OCLUpdate( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
}

// ??0OCLUpdateModuleData@@QAE@XZ
OCLUpdateModuleData::OCLUpdateModuleData()
{
	m_minDelay = 0;
	m_maxDelay = 0;
	m_ocl = 0;
	m_isCreateAtEdge = 0;
}
