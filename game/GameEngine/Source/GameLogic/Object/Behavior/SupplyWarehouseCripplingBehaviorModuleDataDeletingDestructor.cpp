// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SupplyWarehouseCripplingBehaviorModuleData.
// Constructor 0x0020D580 installs dedicated vtable 0x00CA7048; its slot
// zero routes through ILT 0x0000D10C to this 30-byte wrapper, whose complete
// destructor route ILT 0x0003C4C0 reaches cleanup body 0x0020D920.

class SupplyWarehouseCripplingBehaviorModuleData
{
protected:
	virtual ~SupplyWarehouseCripplingBehaviorModuleData();
private:
	friend void forceSupplyWarehouseCripplingBehaviorModuleDataDeletingDestructor();
};

void forceSupplyWarehouseCripplingBehaviorModuleDataDeletingDestructor()
{
	SupplyWarehouseCripplingBehaviorModuleData value;
}
