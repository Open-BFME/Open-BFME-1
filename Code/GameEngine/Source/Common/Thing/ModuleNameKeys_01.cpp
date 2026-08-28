// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: module getModuleNameKey bodies, converted out of machine byte
// dumps.
//
// Each is the same four lines -- a function-local static initialised once from
// TheNameKeyGenerator->nameToKey("<module>") -- so the code cannot say which
// module it belongs to, and the guard byte, the static and the string pointer
// are all relocation sites the byte gate masks. The string itself is not
// masked: verify_string_refs reads the literal out of the source and compares
// it to the bytes the retail push points at, so the name each body carries is
// what assigns it, and a wrong name fails the gate rather than landing quietly.

enum NameKeyType { };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ClearanceTestingSlowDeathBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ClearanceTestingSlowDeathBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType ClearanceTestingSlowDeathBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ClearanceTestingSlowDeathBehavior");
	return nk;
}

class DualWeaponBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DualWeaponBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType DualWeaponBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DualWeaponBehavior");
	return nk;
}

class DynamicPortalBehaviour
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DynamicPortalBehaviour@@UBE?AW4NameKeyType@@XZ
NameKeyType DynamicPortalBehaviour::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DynamicPortalBehaviour");
	return nk;
}

class OathbreakersFadeAwayBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@OathbreakersFadeAwayBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType OathbreakersFadeAwayBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("OathbreakersFadeAwayBehavior");
	return nk;
}

class ReplenishUnitsBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ReplenishUnitsBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType ReplenishUnitsBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ReplenishUnitsBehavior");
	return nk;
}

class RunOffMapBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RunOffMapBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType RunOffMapBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("RunOffMapBehavior");
	return nk;
}

class WargBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@WargBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType WargBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("WargBehavior");
	return nk;
}

class RespawnBody
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RespawnBody@@UBE?AW4NameKeyType@@XZ
NameKeyType RespawnBody::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("RespawnBody");
	return nk;
}

class CivilianSpawnCollide
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CivilianSpawnCollide@@UBE?AW4NameKeyType@@XZ
NameKeyType CivilianSpawnCollide::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("CivilianSpawnCollide");
	return nk;
}

class ExperienceLevelCreate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ExperienceLevelCreate@@UBE?AW4NameKeyType@@XZ
NameKeyType ExperienceLevelCreate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ExperienceLevelCreate");
	return nk;
}

class CombineHordeSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CombineHordeSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType CombineHordeSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("CombineHordeSpecialPower");
	return nk;
}

class DeflectSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DeflectSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType DeflectSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DeflectSpecialPower");
	return nk;
}

class DevastateSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DevastateSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType DevastateSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DevastateSpecialPower");
	return nk;
}

class ElvenWoodSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ElvenWoodSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType ElvenWoodSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ElvenWoodSpecialPower");
	return nk;
}

class GloriousChargeUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GloriousChargeUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType GloriousChargeUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GloriousChargeUpdate");
	return nk;
}

class PlayerUpgradeSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@PlayerUpgradeSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType PlayerUpgradeSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("PlayerUpgradeSpecialPower");
	return nk;
}

class SiegeDeployHordeSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SiegeDeployHordeSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType SiegeDeployHordeSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SiegeDeployHordeSpecialPower");
	return nk;
}

class ToggleHiddenSpecialAbilityUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ToggleHiddenSpecialAbilityUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType ToggleHiddenSpecialAbilityUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ToggleHiddenSpecialAbilityUpdate");
	return nk;
}

class ToggleMountedSpecialAbilityUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ToggleMountedSpecialAbilityUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType ToggleMountedSpecialAbilityUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ToggleMountedSpecialAbilityUpdate");
	return nk;
}

class AttributeModifierAuraUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AttributeModifierAuraUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType AttributeModifierAuraUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AttributeModifierAuraUpdate");
	return nk;
}
