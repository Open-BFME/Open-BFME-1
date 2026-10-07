// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;
typedef float Real;

class Object;

class WeaponBonus
{
public:
	Real m_fields[6];
};

// WeaponBonus's constructor, inlined here; a file-static helper so this TU
// does not emit its own ??0WeaponBonus COMDAT beside Weapon.cpp's.
static inline void initWeaponBonus(WeaponBonus &bonus)
{
	bonus.m_fields[0] = 1.0f;
	bonus.m_fields[1] = 1.0f;
	bonus.m_fields[2] = 1.0f;
	bonus.m_fields[3] = 1.0f;
	bonus.m_fields[4] = 1.0f;
	bonus.m_fields[5] = 1.0f;
}

class WeaponTemplate
{
private:
	friend class Weapon;
	Real bfmeRangeBase(const Object *source, const WeaponBonus &bonus,
		Real heightDifference) const;
};

class Weapon
{
public:
	Real getAttackRange(const Object *source, Real heightDifference) const;

protected:
	void computeBonus(const Object *source, UnsignedInt extra, WeaponBonus &bonus) const;

private:
	char m_fields[4];
	WeaponTemplate *m_template;
};

Real Weapon::getAttackRange(const Object *source, Real heightDifference) const
{
	WeaponBonus bonus;
	initWeaponBonus(bonus);
	computeBonus(source, 0, bonus);
	return m_template->bfmeRangeBase(source, bonus, heightDifference);
}
