// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for StatusBitsUpgrade.
// Vtable 0x00CCDD14 slots name this class (?getClassMemoryPool@StatusBitsUpgrade@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x0000BC3A to this 30-byte wrapper, whose complete destructor
// route ILT 0x000168B0 reaches cleanup body 0x002D7D50.

class StatusBitsUpgrade
{
protected:
	virtual ~StatusBitsUpgrade();
private:
	friend void forceStatusBitsUpgradeDeletingDestructor();
};

void forceStatusBitsUpgradeDeletingDestructor()
{
	StatusBitsUpgrade value;
}
