// BFME's WeaponStore update hook is intentionally empty. GameLogic phase 5
// calls it through WeaponStore vtable 0x010A13C8 slot +0x14.

class WeaponStore
{
public:
	virtual void update();
};

void WeaponStore::update()
{
}
