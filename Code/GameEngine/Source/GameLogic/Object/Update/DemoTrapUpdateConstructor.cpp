// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// Module-constructor family shape: an out-of-line ObjectModule base call
// (pinned at 0x000170E4), then UpdateModule's constructor inlined -- its two
// vtables at 0x0c and 0x10 then its three members -- then this class's own
// three vtables.
//
// Here every member store precedes the vtable stores, so the members are plain
// and the vptr stores sink past the whole run. MSVC groups by value: the zeros
// at 0x14, 0x20 and 0x24 first, then the two -1s at 0x18 and 0x1c.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();		///< vptr at 0x00

	void *m_04;
	void *m_08;								///< ends at 0x0c
};

class BehaviorInterface
{
public:
	virtual void behaviorAnchor() = 0;		///< vptr at 0x0c
};

class UpdateInterface
{
public:
	virtual void updateAnchor() = 0;		///< vptr at 0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule,
	public BehaviorInterface, public UpdateInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData)
	{
		m_nextCallFrameAndPhase = 0;
		m_indexInLogic = -1;
		m_updateState = -1;
	}

	virtual void behaviorAnchor();
	virtual void updateAnchor();

	int m_nextCallFrameAndPhase;			///< 0x14
	int m_indexInLogic;						///< 0x18
	int m_updateState;						///< 0x1c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DemoTrapUpdate.h
class DemoTrapUpdate : public UpdateModule
{
public:
	DemoTrapUpdate(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();

	int m_value20;							///< 0x20
	bool m_flag24;							///< 0x24
};

// ??0DemoTrapUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DemoTrapUpdate::DemoTrapUpdate( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
	m_value20 = 0;
	m_flag24 = false;
}
