// ?parseWeaponBonusSet@WeaponTemplate@@SAXPAVINI@@PAX1PBX@Z
// cl: /DNDEBUG /MD /EHs-c-

class INI;

void *__cdecl operator new(unsigned int);
inline void *__cdecl operator new(unsigned int, void *p) { return p; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponBonusSet
{
public:
	WeaponBonusSet();
	void parseWeaponBonusSet(INI *ini);

private:
	float m_bfmeBonuses[0x84];
};

WeaponBonusSet::WeaponBonusSet()
{
	for (int i = 0; i < 0x84; ++i)
		m_bfmeBonuses[i] = 1.0f;
}

class WeaponTemplate
{
public:
	static void parseWeaponBonusSet(INI *ini, void *instance, void *store,
		const void *userData);

	char m_pad[0x4a8];
	WeaponBonusSet *m_extraBonus;
};

/*static*/ void WeaponTemplate::parseWeaponBonusSet(INI *ini, void *instance,
	void * /*store*/, const void * /*userData*/)
{
	WeaponTemplate *self = (WeaponTemplate *)instance;

	if (!self->m_extraBonus)
	{
		void *mem = operator new(sizeof(WeaponBonusSet));
		self->m_extraBonus = mem ? new(mem) WeaponBonusSet() : 0;
	}

	self->m_extraBonus->parseWeaponBonusSet(ini);
}
