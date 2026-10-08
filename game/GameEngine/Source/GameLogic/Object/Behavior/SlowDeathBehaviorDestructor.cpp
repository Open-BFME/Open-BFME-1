// cl: /O2 /Ob1
//
// Open-BFME: SlowDeathBehavior complete destructor at retail RVA 0x002077A0
// (39 bytes). The protected scalar-deleting wrapper (SlowDeathBehavior
// DeletingDestructor.cpp, 0x00207DA0) reaches it through ILT 0x00032691;
// ilt_oracle confirms the protected ??1SlowDeathBehavior@@MAE@XZ
// decoration. The body re-seats SlowDeathBehavior's SlowDeathBehaviorInterface
// (+0x20) and DieModuleInterface (+0x24) vftables, inlines the UpdateModule
// teardown (three vtable stores) and tail-jumps to the ObjectModule destructor
// ILT 0x00047C53.
//
// The two interface vftables are SlowDeathBehavior.cpp's COMDATs, named by
// their decorated symbols; novtable keeps this TU from emitting its own
// copies, and the interfaces are left out of the base list so the names do
// not bind to this TU's own vftables.

extern "C" const void *__identifier("??_7SlowDeathBehavior@@6BSlowDeathBehaviorInterface@@@")[];
extern "C" const void *__identifier("??_7SlowDeathBehavior@@6BDieModuleInterface@@@")[];

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
	void *m_object;
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}
};

class __declspec(novtable) SlowDeathBehavior : public UpdateModule
{
protected:
	virtual ~SlowDeathBehavior();
};

#define SLOW_DEATH_BEHAVIOR_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

SlowDeathBehavior::~SlowDeathBehavior()
{
	SLOW_DEATH_BEHAVIOR_VPTR(0x20, "??_7SlowDeathBehavior@@6BSlowDeathBehaviorInterface@@@");
	SLOW_DEATH_BEHAVIOR_VPTR(0x24, "??_7SlowDeathBehavior@@6BDieModuleInterface@@@");
}
