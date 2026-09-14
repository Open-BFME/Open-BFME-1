// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LockWeaponCreateModuleData.
// Constructor 0x0024FE00 installs dedicated vtable 0x00CB1950; its slot
// zero routes through ILT 0x000220A7 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00031DEF reaches cleanup body 0x0024FE50.

class LockWeaponCreateModuleData
{
protected:
	virtual ~LockWeaponCreateModuleData();
private:
	friend void forceLockWeaponCreateModuleDataDeletingDestructor();
};

void forceLockWeaponCreateModuleDataDeletingDestructor()
{
	LockWeaponCreateModuleData value;
}
