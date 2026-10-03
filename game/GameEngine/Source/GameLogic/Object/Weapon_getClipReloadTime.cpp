// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

class Object;

class WeaponBonus
{
public:
	float m_fields[6];
};

class WeaponTemplate
{
public:
	int getClipReloadTime(const WeaponBonus &bonus) const;
};

class Weapon
{
public:
	int getClipReloadTime(const Object *source) const;

protected:
	void computeBonus(const Object *source, UnsignedInt extra, WeaponBonus &bonus) const;

private:
	char m_fields[4];
	WeaponTemplate *m_template;
};

int Weapon::getClipReloadTime(const Object *source) const
{
	WeaponBonus bonus;
	bonus.m_fields[0] = 1.0f;
	bonus.m_fields[1] = 1.0f;
	bonus.m_fields[2] = 1.0f;
	bonus.m_fields[3] = 1.0f;
	bonus.m_fields[4] = 1.0f;
	bonus.m_fields[5] = 1.0f;
	computeBonus(source, 0, bonus);
	return m_template->getClipReloadTime(bonus);
}
