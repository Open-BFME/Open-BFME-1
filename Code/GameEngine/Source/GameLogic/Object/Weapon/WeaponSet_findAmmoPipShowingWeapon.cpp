// cl: /DNDEBUG /MD /EHsc

class WeaponTemplate
{
public:
	char m_fields[0x4fb];
	bool m_showsAmmoPips;
};

class Weapon
{
public:
	bool isShowsAmmoPips() const
	{
		return m_template->m_showsAmmoPips;
	}

private:
	void *m_vtable;
	WeaponTemplate *m_template;
};

class WeaponSet
{
public:
	const Weapon *findAmmoPipShowingWeapon() const;

private:
	int m_fields[2];
	Weapon *m_weapons[4];
};

const Weapon *WeaponSet::findAmmoPipShowingWeapon() const
{
	for (int slotIndex = 0; slotIndex < 4; ++slotIndex)
	{
		Weapon *weapon = m_weapons[slotIndex];
		if (weapon != 0 && weapon->isShowsAmmoPips())
			return weapon;
	}

	return 0;
}
