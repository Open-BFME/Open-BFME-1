// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FireWeaponUpdateModuleData.
// Constructor 0x00292CB0 installs dedicated vtable 0x00CBED68; its slot
// zero routes through ILT 0x00017873 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0001CB57 reaches cleanup body 0x00292EF0.

class FireWeaponUpdateModuleData
{
public:
	virtual ~FireWeaponUpdateModuleData();
private:
	friend void forceFireWeaponUpdateModuleDataDeletingDestructor(const FireWeaponUpdateModuleData &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceFireWeaponUpdateModuleDataDeletingDestructor(const FireWeaponUpdateModuleData &that)
{
	FireWeaponUpdateModuleData value(that);
}
