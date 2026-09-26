// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: FireWeaponUpdate scalar-deleting destructor at retail RVA
// 0x00292DD0 (30 bytes). The exact constructor at 0x00292CF0, complete
// destructor at 0x00292B50, factories, update method, and vtable 0x00CBED34
// establish the class. The destructor ILT is 0x00030111.

class FireWeaponUpdate
{
public:
	virtual ~FireWeaponUpdate();
};

void forceFireWeaponUpdateDeletingDestructor()
{
	FireWeaponUpdate value;
}
