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

class BloodthirstyUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@BloodthirstyUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType BloodthirstyUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("BloodthirstyUpdate");
	return nk;
}

class CritterEmitterUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CritterEmitterUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType CritterEmitterUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("CritterEmitterUpdate");
	return nk;
}

class DelayedWeaponSetUpgradeUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DelayedWeaponSetUpgradeUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType DelayedWeaponSetUpgradeUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DelayedWeaponSetUpgradeUpdate");
	return nk;
}

class DestroyEnvironmentUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DestroyEnvironmentUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType DestroyEnvironmentUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DestroyEnvironmentUpdate");
	return nk;
}

class DetachableRiderUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DetachableRiderUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType DetachableRiderUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DetachableRiderUpdate");
	return nk;
}

class EntEnragedUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@EntEnragedUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType EntEnragedUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("EntEnragedUpdate");
	return nk;
}

class FadeAndDieOrnamentUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@FadeAndDieOrnamentUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType FadeAndDieOrnamentUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("FadeAndDieOrnamentUpdate");
	return nk;
}

class LargeGroupAudioUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@LargeGroupAudioUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType LargeGroupAudioUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("LargeGroupAudioUpdate");
	return nk;
}

class LargeGroupBonusUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@LargeGroupBonusUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType LargeGroupBonusUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("LargeGroupBonusUpdate");
	return nk;
}

class ModelConditionSpecialAbilityUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ModelConditionSpecialAbilityUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType ModelConditionSpecialAbilityUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ModelConditionSpecialAbilityUpdate");
	return nk;
}

class OneRingPenaltyUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@OneRingPenaltyUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType OneRingPenaltyUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("OneRingPenaltyUpdate");
	return nk;
}

class PartTheHeavensUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@PartTheHeavensUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType PartTheHeavensUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("PartTheHeavensUpdate");
	return nk;
}

class RespawnUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RespawnUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType RespawnUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("RespawnUpdate");
	return nk;
}

class RubbleRiseUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RubbleRiseUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType RubbleRiseUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("RubbleRiseUpdate");
	return nk;
}

class AnimalAIUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AnimalAIUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType AnimalAIUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AnimalAIUpdate");
	return nk;
}

class FoundationAIUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@FoundationAIUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType FoundationAIUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("FoundationAIUpdate");
	return nk;
}

class GiantBirdAIUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GiantBirdAIUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType GiantBirdAIUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GiantBirdAIUpdate");
	return nk;
}

class HordeAIUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeAIUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeAIUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HordeAIUpdate");
	return nk;
}

class HordeWorkerAIUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeWorkerAIUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeWorkerAIUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HordeWorkerAIUpdate");
	return nk;
}

class SiegeAIUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SiegeAIUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType SiegeAIUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SiegeAIUpdate");
	return nk;
}
