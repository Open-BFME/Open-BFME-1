// cl: /DNDEBUG /MD /EHs-c- /Igame/GameEngine/Source/Common/System
//
// BFME retail's primary FireWeaponWhenDamagedBehavior vtable is at VA
// 0x010A3F04.  Its name slot reaches the literal
// "FireWeaponWhenDamagedBehavior", and its xfer slot reaches RVA 0x001FB270.
// The BFME body deliberately orders the base transfers before its light-CRC
// early-out and version transfer; that differs from the later ZH source.

#include "xfer.h"
#include "snapshot.h"

typedef bool Bool;

class DamageInfo;
enum BodyDamageType
{
	BODY_PRISTINE
};

class Weapon : public Snapshot
{
};

class UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_bfmeStorage[0x1C];
};

class UpgradeMux
{
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	Bool m_upgradeExecuted;
	unsigned char m_bfmePad[3];
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(DamageInfo *damageInfo) = 0;
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo,
		BodyDamageType oldState, BodyDamageType newState) = 0;
};

class FireWeaponWhenDamagedBehavior : public UpdateModule,
	public UpgradeMux,
	public DamageModuleInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Weapon *m_reactionWeaponPristine;
	Weapon *m_reactionWeaponDamaged;
	Weapon *m_reactionWeaponReallyDamaged;
	Weapon *m_reactionWeaponRubble;
	Weapon *m_continuousWeaponPristine;
	Weapon *m_continuousWeaponDamaged;
	Weapon *m_continuousWeaponReallyDamaged;
	Weapon *m_continuousWeaponRubble;
};

// ?xfer@FireWeaponWhenDamagedBehavior@@MAEXPAVXfer@@@Z
void FireWeaponWhenDamagedBehavior::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	UpgradeMux::upgradeMuxXfer(xfer);
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 1;
	*xfer == version;

	Bool weaponPresent = m_reactionWeaponPristine != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_reactionWeaponPristine;

	weaponPresent = m_reactionWeaponDamaged != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_reactionWeaponDamaged;

	weaponPresent = m_reactionWeaponReallyDamaged != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_reactionWeaponReallyDamaged;

	weaponPresent = m_reactionWeaponRubble != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_reactionWeaponRubble;

	weaponPresent = m_continuousWeaponPristine != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_continuousWeaponPristine;

	weaponPresent = m_continuousWeaponDamaged != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_continuousWeaponDamaged;

	weaponPresent = m_continuousWeaponReallyDamaged != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_continuousWeaponReallyDamaged;

	weaponPresent = m_continuousWeaponRubble != 0;
	*xfer == weaponPresent;
	if (weaponPresent)
		*xfer == *m_continuousWeaponRubble;
}
