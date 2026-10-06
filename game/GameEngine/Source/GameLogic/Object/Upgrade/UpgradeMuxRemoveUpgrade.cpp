// cl: /DNDEBUG /MD /EHsc
// UpgradeMux slot 7 bodies that are trivial: slot 8 with false (the inverse
// of attemptUpgrade's final setUpgradeExecuted(true)) or empty. Slot 7 is
// EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot); each override sits on its proven owner.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Owner, table and ILT stub for every body:
// targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md

typedef bool Bool;

class UpgradeMux
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07();
protected:
	virtual void setUpgradeExecuted(Bool executed);
};

// 0x001FB260: slot 7 of FireWeaponWhenDamagedBehavior's table 0x010A3DE8 (ILT 0x0003F049)
class FireWeaponWhenDamagedBehavior : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void FireWeaponWhenDamagedBehavior::removeUpgrade()
{
	setUpgradeExecuted(false);
}

// 0x001FBB80: slot 7 of FireWeaponWhenDeadBehavior's table 0x010A3F40 (ILT 0x0000A7A4)
class FireWeaponWhenDeadBehavior : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void FireWeaponWhenDeadBehavior::removeUpgrade()
{
	setUpgradeExecuted(false);
}

// 0x002043E0: slot 7 of ReplenishUnitsBehavior's table 0x010A5AC0 (ILT 0x0000F245)
class ReplenishUnitsBehavior : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void ReplenishUnitsBehavior::removeUpgrade()
{
	setUpgradeExecuted(false);
}

// 0x0020A810: slot 7 of SpawnBehavior's table 0x010A6B70 (ILT 0x0000CD8D)
class SpawnBehavior : public UpgradeMux
{
protected:
	virtual void removeUpgrade();
};

void SpawnBehavior::removeUpgrade()
{
	setUpgradeExecuted(false);
}

// 0x00212D20: slot 7 of DetachableRiderBody's table 0x010A7FC0 (ILT 0x0001C71A)
class DetachableRiderBody : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void DetachableRiderBody::removeUpgrade()
{
}

// 0x0027FFA0: slot 7 of AttributeModifierAuraUpdate's table 0x010BAD08 (ILT 0x00033703)
class AttributeModifierAuraUpdate : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void AttributeModifierAuraUpdate::removeUpgrade()
{
	setUpgradeExecuted(false);
}

// 0x002899F0: slot 7 of BroadcastStealthUpdate's table 0x010BCAF0 (ILT 0x00020AC7)
class BroadcastStealthUpdate : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void BroadcastStealthUpdate::removeUpgrade()
{
	setUpgradeExecuted(false);
}

// 0x002D3DD0: slot 7 of CastleUpgrade's table 0x010CC1B0 (ILT 0x0003AECC)
class CastleUpgrade : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void CastleUpgrade::removeUpgrade()
{
}

// 0x002D4CF0: slot 7 of DelayedUpgrade's table 0x010CC700 (ILT 0x00025BA3)
class DelayedUpgrade : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void DelayedUpgrade::removeUpgrade()
{
}

// 0x002D5F70: slot 7 of LevelUpUpgrade's table 0x010CCE50 (ILT 0x000319FD)
class LevelUpUpgrade : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void LevelUpUpgrade::removeUpgrade()
{
}

// 0x002D7A50: slot 7 of RadarUpgrade's table 0x010CDA50 (ILT 0x0003B200)
class RadarUpgrade : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void RadarUpgrade::removeUpgrade()
{
	setUpgradeExecuted(false);
}

// 0x002D8220: slot 7 of SubObjectsUpgrade's table 0x010CDEB0 (ILT 0x00047EBF)
class SubObjectsUpgrade : public UpgradeMux
{
protected:
	virtual void removeUpgrade();
};

void SubObjectsUpgrade::removeUpgrade()
{
}

// 0x002DA300: slot 7 of WeaponBonusUpgrade's table 0x010CE5B8 (ILT 0x00011E73)
class WeaponBonusUpgrade : public UpgradeMux
{
public:
	virtual void removeUpgrade();
};

void WeaponBonusUpgrade::removeUpgrade()
{
}
