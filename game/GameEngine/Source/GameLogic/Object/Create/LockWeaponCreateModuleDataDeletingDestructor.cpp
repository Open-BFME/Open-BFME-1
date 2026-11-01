// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LockWeaponCreateModuleData.
// Constructor 0x0024FE00 installs dedicated vtable 0x00CB1950; its slot
// zero routes through ILT 0x000220A7 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00031DEF reaches cleanup body 0x0024FE50.

class LockWeaponCreateModuleData
{
public:
	virtual ~LockWeaponCreateModuleData();
private:
	friend void forceLockWeaponCreateModuleDataDeletingDestructor();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceLockWeaponCreateModuleDataDeletingDestructor(const LockWeaponCreateModuleData &that)
{
	LockWeaponCreateModuleData value(that);
}
