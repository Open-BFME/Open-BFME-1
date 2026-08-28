// cl: /DNDEBUG /MD /EHsc
// readable body of ??0SupplyWarehouseDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate.cpp

// SupplyWarehouseDockUpdate's constructor, retail 0x002CF800. The name used to sit on
// its five-byte incremental-link thunk, lifted naked; a thunk is not the
// constructor.
//
// Four vftable pointers: the three every module carries at +0x00, +0x0C and
// +0x10, plus the dock interface at +0x20. The base at 0x002CD4B0 is shared
// with SupplyWarehouseDockUpdate; reloc_names carries that address as
// SupplyCenterDockUpdateBase, which is its identical-code twin.
//
// The single member at +0x88 is not a constant: it is copied out of the module
// data, which the base left at this+0x04. Retail loads that pointer before the
// vftable stores and dereferences it after - scheduling around the four
// independent stores, not two separate statements.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	const ModuleData *m_moduleData;		// +0x04
	unsigned char m_unmodelled_08[4];
};

// Only the one field this constructor reads.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseDockUpdate.h
struct SupplyWarehouseDockUpdateModuleData
{
	unsigned char m_unmodelled_00[0x10];
	int m_startingBoxes;				// +0x10
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseDockUpdate.h
class SupplyWarehouseDockUpdate : public DockUpdate
{
public:
	SupplyWarehouseDockUpdate( Thing *thing, const ModuleData *moduleData );

private:
	int m_boxesRemaining;			// +0x88
};

SupplyWarehouseDockUpdate::SupplyWarehouseDockUpdate( Thing *thing, const ModuleData *moduleData )
	: DockUpdate( thing, moduleData ),
	  m_boxesRemaining( ((const SupplyWarehouseDockUpdateModuleData *)getModuleData())->m_startingBoxes )
{
}
