// cl: /DNDEBUG /MD /EHsc
// readable body of ??0BridgeTowerBehavior@@: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp

// Open-BFME5: BridgeTowerBehavior module ctor.
//
// Four interface bases, none novtable, so retail writes each interface vtbl
// twice: once at +0xC/+0x10/+0x14/+0x18 as the subobjects are constructed, then
// again with the most-derived set including +0.
//
// The two zeroed words at +0x1C/+0x20 land between those two groups, which is
// where base-subobject member initialisers run -- before the most-derived vtbl
// writes. They therefore belong to the last interface base, not to the body.

class Thing;
class ModuleData;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

	unsigned int m_04;
	Object *m_object;							///< retail this+0x08
};

class BridgeTowerBehaviorIface1
{
public:
	virtual void bridgeTowerIface1Anchor();
};

class BridgeTowerBehaviorIface2
{
public:
	virtual void bridgeTowerIface2Anchor();
};

class BridgeTowerBehaviorIface3
{
public:
	virtual void bridgeTowerIface3Anchor();
};

class BridgeTowerBehaviorIface4
{
public:
	BridgeTowerBehaviorIface4() : m_1c(0), m_20(0) {}
	virtual void bridgeTowerIface4Anchor();

	unsigned int m_1c;							///< retail this+0x1C
	unsigned int m_20;							///< retail this+0x20
};

class BridgeTowerBehaviorBase : public BehaviorModule
{
public:
	BridgeTowerBehaviorBase(Thing *thing, const ModuleData *moduleData);
};

class BridgeTowerBehavior : public BridgeTowerBehaviorBase,
	public BridgeTowerBehaviorIface1,
	public BridgeTowerBehaviorIface2,
	public BridgeTowerBehaviorIface3,
	public BridgeTowerBehaviorIface4
{
public:
	BridgeTowerBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0BridgeTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
BridgeTowerBehavior::BridgeTowerBehavior(Thing *thing, const ModuleData *moduleData)
	: BridgeTowerBehaviorBase(thing, moduleData)
{
}
