// cl: /O2 /Ob1
//
// Open-BFME: StatusBitsUpgrade complete destructor at retail RVA 0x002D7D50
// (32 bytes). The protected scalar-deleting wrapper (StatusBitsUpgrade
// DeletingDestructor.cpp, 0x002D7ED0) reaches it through ILT 0x000168B0; ilt_oracle
// confirms the protected ??1StatusBitsUpgrade@@MAE@XZ decoration. The empty
// destructor inlines the UpgradeModule teardown (four vtable stores) and
// tail-jumps to the ObjectModule destructor ILT 0x00047C53.

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

// UpgradeModule and its two non-primary bases (upstream UpgradeModule.h; BFME
// adds a third base at +0x18). Their vftables 0x010A36E0 and 0x010A36CC are
// recorded in dir32_addresses.csv only under the address-derived names below,
// so the layout keeps those names until the vftable identities are pinned.
class Rva002D44E0DeepDtorL1M0
{
public:
	virtual void upgradeMuxAnchor() = 0;

private:
	bool m_upgradeExecuted;
};

class Rva002D44E0DeepDtorL1M1
{
public:
	virtual void moduleInterfaceAnchor() = 0;
};

class Rva002D44E0DeepDtorL1 : public BehaviorModule, public Rva002D44E0DeepDtorL1M0, public Rva002D44E0DeepDtorL1M1
{
public:
	virtual ~Rva002D44E0DeepDtorL1() {}
};

class __declspec(novtable) StatusBitsUpgrade : public Rva002D44E0DeepDtorL1
{
protected:
	virtual ~StatusBitsUpgrade();
};

StatusBitsUpgrade::~StatusBitsUpgrade()
{
}
