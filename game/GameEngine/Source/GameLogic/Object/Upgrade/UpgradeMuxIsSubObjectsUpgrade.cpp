// cl: /DNDEBUG /MD /EHsc
// The per-class UpgradeMux isSubObjectsUpgrade overrides that return false:
// slot 4 of each class's UpgradeMux table, reached only through that class's
// own slot-4 ILT stub. Zero Hour defines each one inline as
// `virtual Bool isSubObjectsUpgrade() { return false; }`; SubObjectsUpgrade is
// the one class that returns true (SubObjectsUpgradeIsSubObjectsUpgrade.cpp).
// Retail: `32 C0 C3` each. Owner, table and stub for every body:
// targets/game/reverse/identity_evidence/upgrademux-slot4-issubobjectsupgrade.md

typedef bool Bool;

// 0x001fb250: slot 4 of FireWeaponWhenDamagedBehavior's table 0x010a3de8
class FireWeaponWhenDamagedBehavior
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool FireWeaponWhenDamagedBehavior::isSubObjectsUpgrade()
{
	return false;
}

// 0x002043d0: slot 4 of ReplenishUnitsBehavior's table 0x010a5ac0
class ReplenishUnitsBehavior
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool ReplenishUnitsBehavior::isSubObjectsUpgrade()
{
	return false;
}

// 0x0020b0e0: slot 4 of SpawnBehavior's table 0x010a6b70
class SpawnBehavior
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool SpawnBehavior::isSubObjectsUpgrade()
{
	return false;
}

// 0x00212d90: slot 4 of DetachableRiderBody's table 0x010a7fc0
class DetachableRiderBody
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool DetachableRiderBody::isSubObjectsUpgrade()
{
	return false;
}

// 0x0027ffb0: slot 4 of AttributeModifierAuraUpdate's table 0x010bad08
class AttributeModifierAuraUpdate
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool AttributeModifierAuraUpdate::isSubObjectsUpgrade()
{
	return false;
}

// 0x00289a00: slot 4 of BroadcastStealthUpdate's table 0x010bcaf0
class BroadcastStealthUpdate
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool BroadcastStealthUpdate::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d2b10: slot 4 of ArmorUpgrade's table 0x010cba40
class ArmorUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool ArmorUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d3860: slot 4 of BaseUpgrade's table 0x010cbfd8
class BaseUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool BaseUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d4200: slot 4 of CommandSetUpgrade's table 0x010cc330
class CommandSetUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool CommandSetUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d4600: slot 4 of CostModifierUpgrade's table 0x010cc498
class CostModifierUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool CostModifierUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d5030: slot 4 of ExperienceScalarUpgrade's table 0x010cc890
class ExperienceScalarUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool ExperienceScalarUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d52e0: slot 4 of GarrisonUpgrade's table 0x010cca40
class GarrisonUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool GarrisonUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d5f80: slot 4 of LevelUpUpgrade's table 0x010cce50
class LevelUpUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool LevelUpUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d61c0: slot 4 of LocomotorSetUpgrade's table 0x010ccfa8
class LocomotorSetUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool LocomotorSetUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d6400: slot 4 of MaxHealthUpgrade's table 0x010cd158
class MaxHealthUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool MaxHealthUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d6730: slot 4 of ModelConditionUpgrade's table 0x010cd378
class ModelConditionUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool ModelConditionUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d6be0: slot 4 of ObjectCreationUpgrade's table 0x010cd620
class ObjectCreationUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool ObjectCreationUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d7b00: slot 4 of RadarUpgrade's table 0x010cda50
class RadarUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool RadarUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d7e30: slot 4 of StatusBitsUpgrade's table 0x010cdc00
class StatusBitsUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool StatusBitsUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d8060: slot 4 of StealthUpgrade's table 0x010cdd58
class StealthUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool StealthUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d9440: slot 4 of TooltipUpgrade's table 0x010ce1a0
class TooltipUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool TooltipUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002d97c0: slot 4 of UnpauseSpecialPowerUpgrade's table 0x010ce350
class UnpauseSpecialPowerUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool UnpauseSpecialPowerUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002da380: slot 4 of WeaponBonusUpgrade's table 0x010ce5b8
class WeaponBonusUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool WeaponBonusUpgrade::isSubObjectsUpgrade()
{
	return false;
}

// 0x002da540: slot 4 of WeaponSetUpgrade's table 0x010ce710
class WeaponSetUpgrade
{
protected:
	virtual Bool isSubObjectsUpgrade();
};

Bool WeaponSetUpgrade::isSubObjectsUpgrade()
{
	return false;
}
