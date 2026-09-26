// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FireWeaponUpdateModuleData.
// Constructor 0x00292CB0 installs dedicated vtable 0x00CBED68; its slot
// zero routes through ILT 0x00017873 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0001CB57 reaches cleanup body 0x00292EF0.

class FireWeaponUpdateModuleData
{
protected:
	virtual ~FireWeaponUpdateModuleData();
private:
	friend void forceFireWeaponUpdateModuleDataDeletingDestructor();
};

void forceFireWeaponUpdateModuleDataDeletingDestructor()
{
	FireWeaponUpdateModuleData value;
}
