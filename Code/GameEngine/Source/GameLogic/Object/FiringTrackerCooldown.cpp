// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

#include <string.h>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

enum
{
	BFME_CONTINUOUS_FIRE_MEAN = 2,
	BFME_CONTINUOUS_FIRE_FAST = 3,
	BFME_MODEL_CONTINUOUS_FIRE_MEAN = 109,
	BFME_MODEL_CONTINUOUS_FIRE_FAST = 110,
	BFME_MODEL_CONTINUOUS_FIRE_SLOW = 108
};

class ModelConditionFlags
{
public:
	ModelConditionFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

	void set(Int bit)
	{
		m_bits[(UnsignedInt)bit >> 5] |= 1 << ((UnsignedInt)bit & 31);
	}

	void setContinuousFireMask()
	{
		m_bits[3] |= 0x7000;
	}

private:
	UnsignedInt m_bits[10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool testWeaponBonusCondition(Int condition) const
	{
		return ((m_weaponBonusCondition >> condition) & 1) != 0;
	}

	void clearWeaponBonusCondition(Int condition)
	{
		m_weaponBonusCondition &= ~(1 << condition);
	}

	void clearAndSetModelConditionFlags(const ModelConditionFlags &clr,
		const ModelConditionFlags &set);

private:
	unsigned char m_pad[0x2A0];
	UnsignedInt m_weaponBonusCondition;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	virtual void updateModule();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/FiringTracker.h
class FiringTracker : public UpdateModule
{
public:
	virtual void update();

private:
	void coolDown(Bool forceReset);
};

void FiringTracker::coolDown(Bool forceReset)
{
	char *self = reinterpret_cast<char *>(this);
	ModelConditionFlags clr, set;

	if (!forceReset
		&& ((*reinterpret_cast<Object **>(self + 8))->testWeaponBonusCondition(BFME_CONTINUOUS_FIRE_FAST)
			|| (*reinterpret_cast<Object **>(self + 8))->testWeaponBonusCondition(BFME_CONTINUOUS_FIRE_MEAN)))
	{
		set.set(BFME_MODEL_CONTINUOUS_FIRE_SLOW);
		(*reinterpret_cast<Object **>(self + 8))->clearWeaponBonusCondition(BFME_CONTINUOUS_FIRE_FAST);
		(*reinterpret_cast<Object **>(self + 8))->clearWeaponBonusCondition(BFME_CONTINUOUS_FIRE_MEAN);
		clr.set(BFME_MODEL_CONTINUOUS_FIRE_FAST);
		clr.set(BFME_MODEL_CONTINUOUS_FIRE_MEAN);
	}
	else
	{
		(*reinterpret_cast<Object **>(self + 8))->clearWeaponBonusCondition(BFME_CONTINUOUS_FIRE_FAST);
		(*reinterpret_cast<Object **>(self + 8))->clearWeaponBonusCondition(BFME_CONTINUOUS_FIRE_MEAN);
		*reinterpret_cast<UnsignedInt *>(self + 0x3C) = 0;
		clr.setContinuousFireMask();
		*reinterpret_cast<UnsignedInt *>(self + 0x48) = 0;
		*reinterpret_cast<UnsignedInt *>(self + 0x4C) = 0;
		*reinterpret_cast<UnsignedInt *>(self + 0x50) = 0;
	}

	(*reinterpret_cast<Object **>(self + 8))->clearAndSetModelConditionFlags(clr, set);
	*reinterpret_cast<UnsignedInt *>(self + 0x20) = 0;
	*reinterpret_cast<UnsignedInt *>(self + 0x24) = 0;
}
