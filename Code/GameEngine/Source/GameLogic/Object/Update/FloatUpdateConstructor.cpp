// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// Module-constructor family shape: an out-of-line ObjectModule base call
// (pinned at 0x000170E4), then UpdateModule's constructor inlined -- its two
// vtables at 0x0c and 0x10 then its three members -- then this class's own
// three vtables.
//
// Here the derived member follows the vtable stores because its value comes
// from the module data, not from a constant. UpdateModule's own members still
// group by value ahead of them.

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

// The trailing member is read from the module data at +8 rather than zeroed,
// which is why the vtable stores land before it and no register residual
// arises: only one zero is live, so 0x14 is written as an immediate.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FloatUpdate.h
class FloatUpdateModuleData
{
public:
	unsigned char m_head[8];
	bool m_enabled;							///< +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FloatUpdate.h
class FloatUpdate : public UpdateModule
{
public:
	FloatUpdate(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();

	bool m_flag20;							///< 0x20
};

// ??0FloatUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
FloatUpdate::FloatUpdate( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
	m_flag20 = ((const FloatUpdateModuleData *)moduleData)->m_enabled;
}
