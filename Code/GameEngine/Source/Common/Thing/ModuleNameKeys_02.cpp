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

class BannerCarrierUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@BannerCarrierUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType BannerCarrierUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("BannerCarrierUpdate");
	return nk;
}

class BroadcastStealthUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@BroadcastStealthUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType BroadcastStealthUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("BroadcastStealthUpdate");
	return nk;
}

class CivilianSpawnUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CivilianSpawnUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType CivilianSpawnUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("CivilianSpawnUpdate");
	return nk;
}

class DelayedLuaEventUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DelayedLuaEventUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType DelayedLuaEventUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DelayedLuaEventUpdate");
	return nk;
}

class EmotionTrackerUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@EmotionTrackerUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType EmotionTrackerUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("EmotionTrackerUpdate");
	return nk;
}

class SpecialEnemySenseUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@SpecialEnemySenseUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType SpecialEnemySenseUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("SpecialEnemySenseUpdate");
	return nk;
}

class TemporarilyDefectUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@TemporarilyDefectUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType TemporarilyDefectUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("TemporarilyDefectUpdate");
	return nk;
}

class WallUpgradeUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@WallUpgradeUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType WallUpgradeUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("WallUpgradeUpdate");
	return nk;
}

class GarrisonUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GarrisonUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType GarrisonUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GarrisonUpgrade");
	return nk;
}

class AttributeModifierPoolUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AttributeModifierPoolUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType AttributeModifierPoolUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AttributeModifierPoolUpdate");
	return nk;
}

class W3DHordeModelDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DHordeModelDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DHordeModelDraw::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("W3DHordeModelDraw");
	return nk;
}

class W3DLightDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DLightDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DLightDraw::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("W3DLightDraw");
	return nk;
}

class W3DQuadrupedDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DQuadrupedDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DQuadrupedDraw::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("W3DQuadrupedDraw");
	return nk;
}

class W3DStreakDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DStreakDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DStreakDraw::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("W3DStreakDraw");
	return nk;
}

class GateProxyBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GateProxyBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType GateProxyBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GateProxyBehavior");
	return nk;
}

class ModelConditionSoundSelectorClientBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ModelConditionSoundSelectorClientBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType ModelConditionSoundSelectorClientBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ModelConditionSoundSelectorClientBehavior");
	return nk;
}

class AimWeaponBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AimWeaponBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType AimWeaponBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AimWeaponBehavior");
	return nk;
}

class AutoAbilityBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AutoAbilityBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType AutoAbilityBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
	return nk;
}

class BezierProjectileBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@BezierProjectileBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType BezierProjectileBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("BezierProjectileBehavior");
	return nk;
}

class BuildingBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@BuildingBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType BuildingBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("BuildingBehavior");
	return nk;
}
