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

class MonsterDockUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@MonsterDockUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType MonsterDockUpdate::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("MonsterDockUpdate");
	return nk;
}

class AttributeModifierUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AttributeModifierUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType AttributeModifierUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AttributeModifierUpgrade");
	return nk;
}

class AudioLoopUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AudioLoopUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType AudioLoopUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AudioLoopUpgrade");
	return nk;
}

class BaseUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@BaseUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType BaseUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("BaseUpgrade");
	return nk;
}

class CastleUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CastleUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType CastleUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("CastleUpgrade");
	return nk;
}

class DelayedUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@DelayedUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType DelayedUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("DelayedUpgrade");
	return nk;
}

class GeometryUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@GeometryUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType GeometryUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("GeometryUpgrade");
	return nk;
}

class LevelUpUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@LevelUpUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType LevelUpUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("LevelUpUpgrade");
	return nk;
}

class ProductionSpeedBonusUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ProductionSpeedBonusUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType ProductionSpeedBonusUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ProductionSpeedBonusUpgrade");
	return nk;
}

class TooltipUpgrade
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@TooltipUpgrade@@UBE?AW4NameKeyType@@XZ
NameKeyType TooltipUpgrade::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("TooltipUpgrade");
	return nk;
}

class CastleMemberBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CastleMemberBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType CastleMemberBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
	return nk;
}

class CastleBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@CastleBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType CastleBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("CastleBehavior");
	return nk;
}

class AnimationSoundClientBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@AnimationSoundClientBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType AnimationSoundClientBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("AnimationSoundClientBehavior");
	return nk;
}

class RandomSoundSelectorClientBehavior
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@RandomSoundSelectorClientBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType RandomSoundSelectorClientBehavior::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("RandomSoundSelectorClientBehavior");
	return nk;
}

class W3DBuffDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DBuffDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DBuffDraw::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("W3DBuffDraw");
	return nk;
}

class W3DFloorDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DFloorDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DFloorDraw::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("W3DFloorDraw");
	return nk;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DPoliceCarDraw.h
class W3DPoliceCarDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DPoliceCarDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DPoliceCarDraw::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("W3DPoliceCarDraw");
	return nk;
}

class W3DScriptedModelDraw
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@W3DScriptedModelDraw@@UBE?AW4NameKeyType@@XZ
NameKeyType W3DScriptedModelDraw::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("W3DScriptedModelDraw");
	return nk;
}
