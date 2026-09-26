// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: FireWeaponWhenDamagedBehaviorModuleData scalar-deleting
// destructor at retail RVA 0x0012ACA0 (30 bytes).  The matching constructor
// at 0x0012A100 installs vtable 0x0108F078, whose slot zero is ILT 0x0001C3EB
// and reaches this wrapper.  Its complete destructor is called through ILT
// 0x00049A1C; that route reaches the 67-byte body at 0x0012ACD0, which tears
// down the module-data base at +0x08 and restores vtable 0x01073744.

class FireWeaponWhenDamagedBehaviorModuleData
{
public:
	virtual ~FireWeaponWhenDamagedBehaviorModuleData();
};

void forceFireWeaponWhenDamagedBehaviorModuleDataDeletingDestructor()
{
	FireWeaponWhenDamagedBehaviorModuleData value;
}
