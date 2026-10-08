// cl: /O2 /Ob1
//
// Open-BFME: WallUpgradeUpdate complete destructor at retail RVA 0x002B2100
// (39 bytes). The protected scalar-deleting wrapper (WallUpgradeUpdate
// DeletingDestructor.cpp, 0x002B2410) reaches it through ILT 0x0002575C;
// ilt_oracle confirms the protected ??1WallUpgradeUpdate@@MAE@XZ
// decoration. The body re-seats WallUpgradeUpdate's two upgrade-mixin
// vftables (+0x20, +0x24), inlines the UpdateModule teardown (three vtable
// stores) and tail-jumps to the ObjectModule destructor ILT 0x00047C53.
//
// The two mixin vftables are the constructor TU's COMDATs, named by their
// decorated symbols; novtable keeps this TU from emitting its own copies.

extern "C" const void *__identifier("??_7WallUpgradeUpdate@@6BWUU_Iface3@@@")[];
extern "C" const void *__identifier("??_7WallUpgradeUpdate@@6BWUU_Iface4@@@")[];

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

class __declspec(novtable) WallUpgradeUpdate : public UpdateModule
{
protected:
	virtual ~WallUpgradeUpdate();
};

#define WALL_UPGRADE_UPDATE_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

WallUpgradeUpdate::~WallUpgradeUpdate()
{
	WALL_UPGRADE_UPDATE_VPTR(0x20, "??_7WallUpgradeUpdate@@6BWUU_Iface3@@@");
	WALL_UPGRADE_UPDATE_VPTR(0x24, "??_7WallUpgradeUpdate@@6BWUU_Iface4@@@");
}
