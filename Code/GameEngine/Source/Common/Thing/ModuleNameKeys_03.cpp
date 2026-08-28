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

class ClickReactionBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ClickReactionBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType ClickReactionBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ClickReactionBehavior");
	return nk;
}

class EnragedBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@EnragedBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType EnragedBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("EnragedBehavior");
	return nk;
}

class GateOpenAndCloseBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GateOpenAndCloseBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType GateOpenAndCloseBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	return nk;
}

class GettingBuiltBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GettingBuiltBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType GettingBuiltBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GettingBuiltBehavior");
	return nk;
}

class GiantBirdSlowDeathBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GiantBirdSlowDeathBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType GiantBirdSlowDeathBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GiantBirdSlowDeathBehavior");
	return nk;
}

class HitReactionBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@HitReactionBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType HitReactionBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("HitReactionBehavior");
	return nk;
}

class PassiveAreaEffectBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@PassiveAreaEffectBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType PassiveAreaEffectBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("PassiveAreaEffectBehavior");
	return nk;
}

class RampageBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RampageBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType RampageBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("RampageBehavior");
	return nk;
}

class ShareExperienceBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ShareExperienceBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType ShareExperienceBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ShareExperienceBehavior");
	return nk;
}

class SiegeDockingBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SiegeDockingBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType SiegeDockingBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
	return nk;
}

class SlaveWatcherBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SlaveWatcherBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType SlaveWatcherBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
	return nk;
}

class SpawnTownsmenBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SpawnTownsmenBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType SpawnTownsmenBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SpawnTownsmenBehavior");
	return nk;
}

class SpawnUnitBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SpawnUnitBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType SpawnUnitBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SpawnUnitBehavior");
	return nk;
}

class DelayedDeathBody
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DelayedDeathBody@@UBE?AW4NameKeyType@@XZ
NameKeyType DelayedDeathBody::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DelayedDeathBody");
	return nk;
}

class DetachableRiderBody
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DetachableRiderBody@@UBE?AW4NameKeyType@@XZ
NameKeyType DetachableRiderBody::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DetachableRiderBody");
	return nk;
}

class FreeLifeBody
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@FreeLifeBody@@UBE?AW4NameKeyType@@XZ
NameKeyType FreeLifeBody::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("FreeLifeBody");
	return nk;
}

class OathbreakerBody
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@OathbreakerBody@@UBE?AW4NameKeyType@@XZ
NameKeyType OathbreakerBody::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("OathbreakerBody");
	return nk;
}

class PorcupineFormationBodyModule
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@PorcupineFormationBodyModule@@UBE?AW4NameKeyType@@XZ
NameKeyType PorcupineFormationBodyModule::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("PorcupineFormationBodyModule");
	return nk;
}

class SymbioticStructuresBody
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SymbioticStructuresBody@@UBE?AW4NameKeyType@@XZ
NameKeyType SymbioticStructuresBody::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SymbioticStructuresBody");
	return nk;
}

class AODCrushCollide
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AODCrushCollide@@UBE?AW4NameKeyType@@XZ
NameKeyType AODCrushCollide::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AODCrushCollide");
	return nk;
}
