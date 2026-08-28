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

class GiveUpgradeUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GiveUpgradeUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType GiveUpgradeUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GiveUpgradeUpdate");
	return nk;
}

class GrabPassengerSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GrabPassengerSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType GrabPassengerSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GrabPassengerSpecialPower");
	return nk;
}

class HeroModeSpecialAbilityUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HeroModeSpecialAbilityUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType HeroModeSpecialAbilityUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HeroModeSpecialAbilityUpdate");
	return nk;
}

class LevelGrantSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@LevelGrantSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType LevelGrantSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("LevelGrantSpecialPower");
	return nk;
}

class ManTheWallsSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ManTheWallsSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType ManTheWallsSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ManTheWallsSpecialPower");
	return nk;
}

class PlayerHealSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@PlayerHealSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType PlayerHealSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("PlayerHealSpecialPower");
	return nk;
}

class ProductionSpeedBonus
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ProductionSpeedBonus@@UBE?AW4NameKeyType@@XZ
NameKeyType ProductionSpeedBonus::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ProductionSpeedBonus");
	return nk;
}

class RepairSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RepairSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType RepairSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("RepairSpecialPower");
	return nk;
}

class RousingSpeechUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RousingSpeechUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType RousingSpeechUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("RousingSpeechUpdate");
	return nk;
}

class ScavengerSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ScavengerSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType ScavengerSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ScavengerSpecialPower");
	return nk;
}

class SiegeDeploySpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SiegeDeploySpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType SiegeDeploySpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
	return nk;
}

class SpecialDisguiseUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SpecialDisguiseUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType SpecialDisguiseUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
	return nk;
}

class SplitHordeSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SplitHordeSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType SplitHordeSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SplitHordeSpecialPower");
	return nk;
}

class StopSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@StopSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType StopSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("StopSpecialPower");
	return nk;
}

class TaintSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@TaintSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType TaintSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("TaintSpecialPower");
	return nk;
}

class WeaponChangeSpecialPowerModule
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@WeaponChangeSpecialPowerModule@@UBE?AW4NameKeyType@@XZ
NameKeyType WeaponChangeSpecialPowerModule::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("WeaponChangeSpecialPowerModule");
	return nk;
}

class WeaponFireSpecialAbilityUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@WeaponFireSpecialAbilityUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType WeaponFireSpecialAbilityUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("WeaponFireSpecialAbilityUpdate");
	return nk;
}

class WeaponSetSpecialAbilityUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@WeaponSetSpecialAbilityUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType WeaponSetSpecialAbilityUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("WeaponSetSpecialAbilityUpdate");
	return nk;
}

class WoundArrowUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@WoundArrowUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType WoundArrowUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("WoundArrowUpdate");
	return nk;
}

class AutoPickUpUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AutoPickUpUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType AutoPickUpUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AutoPickUpUpdate");
	return nk;
}
