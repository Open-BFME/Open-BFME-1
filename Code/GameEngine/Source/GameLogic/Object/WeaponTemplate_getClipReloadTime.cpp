// readable body of ?getClipReloadTime@WeaponTemplate@@QBEHABVWeaponBonus@@@Z: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp
// BFME retail WeaponTemplate::getClipReloadTime, 0x001E1680.
// The matched reloadWithBonus caller and the authentic Weapon.cpp source fix
// both the identity and the RATE_OF_FIRE field used here.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	int getClipReloadTime(const WeaponBonus &bonus) const;

private:
	unsigned char m_prefix[0x4b0];
	int m_minClipReloadTime;
	int m_maxClipReloadTime;
};

// ?getClipReloadTime@WeaponTemplate@@QBEHABVWeaponBonus@@@Z
int WeaponTemplate::getClipReloadTime(const WeaponBonus &bonus) const
{
	int reloadTime;
	if (m_minClipReloadTime == m_maxClipReloadTime)
		reloadTime = m_minClipReloadTime;
	else
		reloadTime = GetGameLogicRandomValue(
			m_minClipReloadTime,
			m_maxClipReloadTime,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Weapon.cpp",
			863);

	reloadTime -= reloadTime % 3;
	return REAL_TO_INT_FLOOR((Real)reloadTime / bonus.getField(WeaponBonus::RATE_OF_FIRE));
}
