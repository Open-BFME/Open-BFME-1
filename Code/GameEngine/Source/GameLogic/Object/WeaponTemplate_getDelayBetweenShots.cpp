// BFME retail WeaponTemplate::getDelayBetweenShots, 0x001E1610.
// Sibling of WeaponTemplate::getClipReloadTime at 0x001E1680: min/max at
// +0x4B8/+0x4BC, GameLogicRandomValue with Weapon.cpp:845, then RATE_OF_FIRE
// divide. Unlike clip reload this path has no modulo-3 snap.

typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

int GetGameLogicRandomValue(int low, int high, char *file, int line);

class WeaponBonus
{
public:
	enum Field
	{
		DAMAGE,
		RADIUS,
		RANGE,
		RATE_OF_FIRE,
		PRE_ATTACK,
		FIELD_COUNT
	};

	float getField(Field field) const { return m_field[field]; }

private:
	float m_field[6];
};

class WeaponTemplate
{
public:
	int getDelayBetweenShots(const WeaponBonus &bonus) const;

private:
	unsigned char m_prefix[0x4b8];
	int m_minDelayBetweenShots;
	int m_maxDelayBetweenShots;
};

// ?getDelayBetweenShots@WeaponTemplate@@QBEHABVWeaponBonus@@@Z
int WeaponTemplate::getDelayBetweenShots(const WeaponBonus &bonus) const
{
	int delayToUse;
	if (m_minDelayBetweenShots == m_maxDelayBetweenShots)
		delayToUse = m_minDelayBetweenShots;
	else
		delayToUse = GetGameLogicRandomValue(
			m_minDelayBetweenShots,
			m_maxDelayBetweenShots,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Weapon.cpp",
			845);

	return REAL_TO_INT_FLOOR((Real)delayToUse / bonus.getField(WeaponBonus::RATE_OF_FIRE));
}
