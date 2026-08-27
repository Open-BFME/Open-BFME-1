// cl: /DNDEBUG /MD /O2 /EHsc

typedef unsigned int UnsignedInt;
typedef float Real;

extern Real g_bfmeDefaultBU;

class WeaponBonus
{
public:
	void appendBonuses(WeaponBonus &bonus) const
	{
		for (int i = 0; i < 6; ++i)
			bonus.m_field[i] += m_field[i] - g_bfmeDefaultBU;
	}

	Real m_field[6];
};

class WeaponBonusSet
{
public:
	void bfmeApplyBonuses(UnsignedInt mask, WeaponBonus &bonus) const;

private:
	WeaponBonus m_bfmeBonuses[0x16];
};

// ?bfmeApplyBonuses@WeaponBonusSet@@QBEXIAAVWeaponBonus@@@Z
void WeaponBonusSet::bfmeApplyBonuses(UnsignedInt mask, WeaponBonus &bonus) const
{
	if (mask != 0)
	{
		int one = 1;

		for (int i = 0; i < 0x16; ++i)
		{
			if (mask & (one << i))
			{
				m_bfmeBonuses[i].appendBonuses(bonus);
			}
		}
	}
}
