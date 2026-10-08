// cl: /O2 /Ob1
//
// Open-BFME: BridgeTowerBehavior complete destructor at retail RVA 0x001F5F70
// (39 bytes). The protected scalar-deleting wrapper (BridgeTowerBehavior
// DeletingDestructor.cpp, 0x001F6180) reaches it through ILT 0x00012F44;
// ilt_oracle confirms the protected ??1BridgeTowerBehavior@@MAE@XZ
// decoration. The body re-seats BridgeTowerBehavior's three interface
// vftables (+0x10, +0x14, +0x18), inlines the BehaviorModule teardown (two
// vtable stores) and tail-jumps to the ObjectModule destructor ILT 0x00047C53.
//
// The interface vftables are the constructor TU's COMDATs, named by their
// decorated symbols; novtable keeps this TU from emitting its own copies.

extern "C" const void *__identifier("??_7BridgeTowerBehavior@@6BBridgeTowerBehaviorIface2@@@")[];
extern "C" const void *__identifier("??_7BridgeTowerBehavior@@6BBridgeTowerBehaviorIface3@@@")[];
extern "C" const void *__identifier("??_7BridgeTowerBehavior@@6BBridgeTowerBehaviorIface4@@@")[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
	virtual ~Module();

private:
	const void *m_moduleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Module
{
public:
	virtual ~ObjectModule();

private:
	void *m_thing;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class __declspec(novtable) BridgeTowerBehavior : public BehaviorModule
{
protected:
	virtual ~BridgeTowerBehavior();
};

#define BRIDGE_TOWER_BEHAVIOR_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

BridgeTowerBehavior::~BridgeTowerBehavior()
{
	BRIDGE_TOWER_BEHAVIOR_VPTR(0x10, "??_7BridgeTowerBehavior@@6BBridgeTowerBehaviorIface2@@@");
	BRIDGE_TOWER_BEHAVIOR_VPTR(0x14, "??_7BridgeTowerBehavior@@6BBridgeTowerBehaviorIface3@@@");
	BRIDGE_TOWER_BEHAVIOR_VPTR(0x18, "??_7BridgeTowerBehavior@@6BBridgeTowerBehaviorIface4@@@");
}
