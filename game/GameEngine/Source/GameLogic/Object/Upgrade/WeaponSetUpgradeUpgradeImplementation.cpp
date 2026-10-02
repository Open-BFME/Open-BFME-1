// WeaponSetUpgrade::upgradeImplementation at retail 0x002DA610: slot 9 of the UpgradeMux table
// 0x010CE710, reached only through ILT 0x000397A2 (its VA appears once in the image).
// WeaponSetUpgrade's registered constructor 0x002DA4E0 stores that table. Slot 9 is the
// upgradeImplementation call in UpgradeMux::attemptUpgrade (0x002D9AD0).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

class BfmeSubTFA
{
public:
	void bfmeSetTFA(int a);
};

class BfmeBaseTFA
{
public:
	void bfmeInitTFA();
};

class WeaponSetUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void WeaponSetUpgrade::upgradeImplementation()
{
	((BfmeBaseTFA *)((char *)this - 0x10))->bfmeInitTFA();
	(*(BfmeSubTFA **)((char *)this - 8))->bfmeSetTFA(3);
}
