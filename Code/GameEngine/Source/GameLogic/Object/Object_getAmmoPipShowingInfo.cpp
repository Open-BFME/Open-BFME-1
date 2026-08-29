// cl: /DNDEBUG /MD /EHsc
// readable body of ?getAmmoPipShowingInfo@Object@@QBE_NAAH0@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
private:
	unsigned char m_pad[0x4ac];

public:
	Int m_clipSize;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponSet
{
public:
	const Weapon *findAmmoPipShowingWeapon() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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
