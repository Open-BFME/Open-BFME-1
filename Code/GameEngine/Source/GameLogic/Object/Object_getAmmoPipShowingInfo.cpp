// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class WeaponTemplate
{
private:
	unsigned char m_pad[0x4ac];

public:
	Int m_clipSize;
};

class Weapon
{
public:
	virtual void weaponAnchor();

	UnsignedInt getRemainingAmmo(Bool countReloadingAsEmpty) const;
	Int getClipSize() const
	{
		return m_template->m_clipSize;
	}

private:
	const WeaponTemplate *m_template;
};

class WeaponSet
{
public:
	const Weapon *findAmmoPipShowingWeapon() const;
};

class Object
{
public:
	Bool getAmmoPipShowingInfo(Int &numTotal, Int &numFull) const;

private:
	unsigned char m_pad[0x264];
	WeaponSet m_weaponSet;
};

Bool Object::getAmmoPipShowingInfo(Int &numTotal, Int &numFull) const
{
	const Weapon *weapon = m_weaponSet.findAmmoPipShowingWeapon();
	if (weapon)
	{
		numTotal = weapon->getClipSize();
		numFull = weapon->getRemainingAmmo(true);
		return true;
	}
	return false;
}
