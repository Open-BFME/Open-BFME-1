// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SupplyCenterProductionExitUpdate.
// Vtable 0x00CCB9F4 slots name this class (?getClassMemoryPool@SupplyCenterProductionExitUpdate@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x000388C5 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001CA3A reaches cleanup body 0x002D2210.

class SupplyCenterProductionExitUpdate
{
protected:
	virtual ~SupplyCenterProductionExitUpdate();
private:
	friend void forceSupplyCenterProductionExitUpdateDeletingDestructor();
};

void forceSupplyCenterProductionExitUpdateDeletingDestructor()
{
	SupplyCenterProductionExitUpdate value;
}
