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

class HordeMemberCollide
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeMemberCollide@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeMemberCollide::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HordeMemberCollide");
	return nk;
}

class ContestableContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ContestableContain@@UBE?AW4NameKeyType@@XZ
NameKeyType ContestableContain::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ContestableContain");
	return nk;
}

class SiegeEngineContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SiegeEngineContain@@UBE?AW4NameKeyType@@XZ
NameKeyType SiegeEngineContain::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SiegeEngineContain");
	return nk;
}

class HordeContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeContain@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeContain::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HordeContain");
	return nk;
}

class HordeGarrisonContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeGarrisonContain@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeGarrisonContain::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HordeGarrisonContain");
	return nk;
}

class HordeSiegeEngineContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeSiegeEngineContain@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeSiegeEngineContain::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HordeSiegeEngineContain");
	return nk;
}

class HordeTransportContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HordeTransportContain@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeTransportContain::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HordeTransportContain");
	return nk;
}

class HorseHordeContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HorseHordeContain@@UBE?AW4NameKeyType@@XZ
NameKeyType HorseHordeContain::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HorseHordeContain");
	return nk;
}

class SlaughterHordeContain
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SlaughterHordeContain@@UBE?AW4NameKeyType@@XZ
NameKeyType SlaughterHordeContain::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SlaughterHordeContain");
	return nk;
}

class EvacuateDamage
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@EvacuateDamage@@UBE?AW4NameKeyType@@XZ
NameKeyType EvacuateDamage::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("EvacuateDamage");
	return nk;
}

class ReflectDamage
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ReflectDamage@@UBE?AW4NameKeyType@@XZ
NameKeyType ReflectDamage::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ReflectDamage");
	return nk;
}

class HeroDie
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HeroDie@@UBE?AW4NameKeyType@@XZ
NameKeyType HeroDie::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HeroDie");
	return nk;
}

class RefundDie
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RefundDie@@UBE?AW4NameKeyType@@XZ
NameKeyType RefundDie::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("RefundDie");
	return nk;
}

class ObjectGuardingHelper
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ObjectGuardingHelper@@UBE?AW4NameKeyType@@XZ
NameKeyType ObjectGuardingHelper::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ObjectGuardingHelper");
	return nk;
}

class ArrowStormUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ArrowStormUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType ArrowStormUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ArrowStormUpdate");
	return nk;
}

class CloudBreakSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CloudBreakSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType CloudBreakSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("CloudBreakSpecialPower");
	return nk;
}

class DarknessSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DarknessSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType DarknessSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DarknessSpecialPower");
	return nk;
}

class DominateEnemySpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DominateEnemySpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType DominateEnemySpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DominateEnemySpecialPower");
	return nk;
}

class FellBeastSwoopPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@FellBeastSwoopPower@@UBE?AW4NameKeyType@@XZ
NameKeyType FellBeastSwoopPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("FellBeastSwoopPower");
	return nk;
}

class FreezingRainSpecialPower
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@FreezingRainSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType FreezingRainSpecialPower::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("FreezingRainSpecialPower");
	return nk;
}
