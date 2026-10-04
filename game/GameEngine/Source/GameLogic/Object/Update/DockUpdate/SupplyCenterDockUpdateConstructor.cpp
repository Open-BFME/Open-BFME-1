// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SupplyCenterDockUpdate module ctor.
// Out-of-line base MI, then four most-derived vtbls at +0/+0xC/+0x10/+0x20.

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor() = 0;

private:
	unsigned char m_data[8];
};

class SupplyCenterDockUpdateIface1
{
public:
	virtual void supplyCenterDockUpdateIface1Anchor() = 0;
};

class SupplyCenterDockUpdateIface2
{
public:
	virtual void supplyCenterDockUpdateIface2Anchor() = 0;

private:
	unsigned char m_pad[0xC];
};

class SupplyCenterDockUpdateIface3
{
public:
	virtual void supplyCenterDockUpdateIface3Anchor() = 0;
};

// The base call leaves through ILT 0x00048EA5, whose jmp target is
// 0x006CD4B0 = the body the ledger owns as
// ??0DockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z (0x002CD4B0, matched in
// DockUpdateConstructorBfme.cpp).  Upstream, SupplyCenterDockUpdate derives
// from DockUpdate, so that is also the real spelling of this base.
class DockUpdate : public BehaviorModule,
	public SupplyCenterDockUpdateIface1,
	public SupplyCenterDockUpdateIface2,
	public SupplyCenterDockUpdateIface3
{
public:
	DockUpdate(Thing *thing, const ModuleData *moduleData);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterDockUpdate.h
class SupplyCenterDockUpdate : public DockUpdate
{
public:
	SupplyCenterDockUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0SupplyCenterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SupplyCenterDockUpdate::SupplyCenterDockUpdate(Thing *thing, const ModuleData *moduleData)
	: DockUpdate(thing, moduleData)
{
}
