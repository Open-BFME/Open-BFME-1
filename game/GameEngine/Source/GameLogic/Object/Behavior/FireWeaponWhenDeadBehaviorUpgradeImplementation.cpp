// cl: /DNDEBUG /MD /EHsc
// FireWeaponWhenDeadBehavior::upgradeImplementation at retail 0x001FBEB0: slot 9 of the UpgradeMux table
// 0x010A3F40, reached only through ILT 0x000455ED (its VA appears once in the image).
// FireWeaponWhenDeadBehavior's registered constructor 0x001FBC70 stores that table. Slot 9 is the
// upgradeImplementation call in UpgradeMux::attemptUpgrade (0x002D9AD0).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// Zero Hour's FireWeaponWhenDeadBehavior.h defines this override with an empty
// body ("// nothing!"); retail is a single `ret`.

class FireWeaponWhenDeadBehavior
{
protected:
	virtual void upgradeImplementation();
};

void FireWeaponWhenDeadBehavior::upgradeImplementation()
{
	// nothing!
}
