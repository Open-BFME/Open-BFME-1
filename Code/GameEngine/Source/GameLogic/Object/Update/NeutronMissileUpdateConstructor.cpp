// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

// Four vptrs land at 0x00, 0x0c, 0x10 and 0x20, which is the UpdateModule
// chain (object module, behavior interface, update interface) plus one further
// interface at 0x20. The base constructor is declared only, so the call
// resolves to the existing pin for
// ??0SupplyCenterDockUpdateBase@@QAE@PAVThing@@PBVModuleData@@@Z at 0x00048EA5.

class ObjectModuleBase
{
public:
	virtual void objectModuleAnchor();

	const void *m_moduleData;				///< 0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public ObjectModuleBase
{
public:
	void *m_object;							///< 0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	unsigned int m_nextCallFrameAndPhase;	///< 0x14
	int m_indexInLogic;						///< 0x18
	unsigned int m_updateState;				///< 0x1c -- UpdateModule ends at 0x20
};

class DockInterface
{
public:
	virtual void dockAnchor() = 0;
};

class SupplyCenterDockUpdateBase : public UpdateModule, public DockInterface
{
public:
	SupplyCenterDockUpdateBase(Thing *, const ModuleData *);

	unsigned char m_gap24[0x88 - 0x24];
};

class MonsterDockUpdate : public SupplyCenterDockUpdateBase
{
public:
	MonsterDockUpdate(Thing *, const ModuleData *);

	// One override per polymorphic sub-object, so this class gets its own
	// vtable for each and the constructor stores all four.
	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();
	virtual void dockAnchor();

	bool m_flag88;							///< 0x88
	bool m_flag89;							///< 0x89
	int m_value8c;							///< 0x8c
};

// ??0MonsterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
MonsterDockUpdate::MonsterDockUpdate( Thing *thing, const ModuleData *moduleData )
	: SupplyCenterDockUpdateBase( thing, moduleData )
{
	m_flag89 = false;
	m_value8c = 0;
	m_flag88 = true;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutronMissileUpdate.h
class NeutronMissileUpdate : public SupplyCenterDockUpdateBase
{
public:
	NeutronMissileUpdate(Thing *, const ModuleData *);

	// One override per polymorphic sub-object, so this class gets its own
	// vtable for each and the constructor stores all four.
	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();
	virtual void dockAnchor();

	bool m_flag88;							///< 0x88
	bool m_flag89;							///< 0x89
	int m_value8c;							///< 0x8c
};

// ??0NeutronMissileUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
NeutronMissileUpdate::NeutronMissileUpdate( Thing *thing, const ModuleData *moduleData )
	: SupplyCenterDockUpdateBase( thing, moduleData )
{
	m_flag89 = false;
	m_value8c = 0;
	m_flag88 = true;
}
