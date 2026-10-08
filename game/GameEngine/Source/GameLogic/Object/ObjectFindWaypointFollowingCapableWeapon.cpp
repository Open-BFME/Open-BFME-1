// cl: -GX
//
// Retail 0x001BE2B0 (11 bytes): Object::findWaypointFollowingCapableWeapon.
// The matched ScriptActions::doNamedFireWeaponFollowingWaypointPath
// (0x00302A80) calls it through ILT 0x00033361; the body adjusts this to
// Object::m_weaponSet (+0x264) and tail-jumps to the matched
// WeaponSet::findWaypointFollowingCapableWeapon (0x001EAEF0).

class Weapon;

class WeaponSet
{
public:
	Weapon *findWaypointFollowingCapableWeapon();
};

class Object
{
public:
	Weapon *findWaypointFollowingCapableWeapon();

private:
	char m_pad000[0x264];
	WeaponSet m_weaponSet;
};

Weapon *Object::findWaypointFollowingCapableWeapon()
{
	return m_weaponSet.findWaypointFollowingCapableWeapon();
}
