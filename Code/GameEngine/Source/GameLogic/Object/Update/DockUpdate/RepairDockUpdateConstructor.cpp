// cl: /DNDEBUG /MD /EHsc
// readable body of ??0RepairDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RepairDockUpdate.cpp

// RepairDockUpdate's constructor, retail 0x002CED20. The name used to sit on
// its five-byte incremental-link thunk, lifted naked; a thunk is not the
// constructor.
//
// Four vftable pointers: the three every module carries at +0x00, +0x0C and
// +0x10, plus the dock interface at +0x20. The base at 0x002CD4B0 is shared
// with SupplyWarehouseDockUpdate; reloc_names carries that address as
// SupplyCenterDockUpdateBase, which is its identical-code twin.
//
// Retail zeroes the two dwords at +0x88 and +0x8C before the vftable stores.
// That is scheduling - one `xor eax,eax' feeds both - not construction order.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class DockUpdateInterface
{
public:
	virtual void dockUpdateInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule,
	public UpdateModuleInterface,
	public ModuleInterface
{
private:
	// The three module bases reach +0x14; the dock interface pointer is at
	// +0x20, so this is what sits between.
	unsigned char m_unmodelled_14[ 0x0C ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h
class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	DockUpdate( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_unmodelled_24[ 0x88 - 0x24 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RepairDockUpdate.h
class RepairDockUpdate : public DockUpdate
{
public:
	RepairDockUpdate( Thing *thing, const ModuleData *moduleData );

private:
	int m_unmodelled_88;			// +0x88
	int m_unmodelled_8C;			// +0x8C
};

RepairDockUpdate::RepairDockUpdate( Thing *thing, const ModuleData *moduleData )
	: DockUpdate( thing, moduleData ), m_unmodelled_88( 0 ), m_unmodelled_8C( 0 )
{
}
