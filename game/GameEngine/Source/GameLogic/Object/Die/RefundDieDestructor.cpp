// cl: /O2 /Ob1
//
// Open-BFME: RefundDie complete destructor at retail RVA 0x00255A40
// (25 bytes). The protected scalar-deleting wrapper (RefundDie
// DeletingDestructor.cpp, 0x00255B70) reaches it through ILT 0x00001B4F;
// ilt_oracle confirms the protected ??1RefundDie@@MAE@XZ
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
class Rva00255A40NestedDtor : public BehaviorModule, public DieModuleInterface
{
public:
	virtual ~Rva00255A40NestedDtor() {}
};

class __declspec(novtable) RefundDie : public Rva00255A40NestedDtor
{
protected:
	virtual ~RefundDie();
};

RefundDie::~RefundDie()
{
}
