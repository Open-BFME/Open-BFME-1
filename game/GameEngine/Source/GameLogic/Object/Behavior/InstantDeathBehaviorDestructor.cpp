// cl: /O2 /Ob1
//
// Open-BFME: InstantDeathBehavior complete destructor at retail RVA 0x00200870
// (25 bytes). The protected scalar-deleting wrapper (InstantDeathBehavior
// DeletingDestructor.cpp, 0x00200C90) reaches it through ILT 0x0003401D;
// ilt_oracle confirms the protected ??1InstantDeathBehavior@@MAE@XZ
// decoration. The empty destructor inlines the DieModule teardown (three
// vtable stores) and tail-jumps to the ObjectModule destructor ILT 0x00047C53.

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void dieModuleInterfaceAnchor() = 0;
};

// DieModule (upstream DieModule.h). Its vftable 0x010A4CEC is recorded in
// dir32_addresses.csv only under the address-derived name below, so the layout
// keeps that name until the vftable identity is pinned.
class Rva00200870NestedDtor : public BehaviorModule, public DieModuleInterface
{
public:
	virtual ~Rva00200870NestedDtor() {}
};

class __declspec(novtable) InstantDeathBehavior : public Rva00200870NestedDtor
{
protected:
	virtual ~InstantDeathBehavior();
};

InstantDeathBehavior::~InstantDeathBehavior()
{
}
