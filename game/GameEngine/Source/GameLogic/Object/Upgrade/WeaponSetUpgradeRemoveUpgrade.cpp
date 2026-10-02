// WeaponSetUpgrade::removeUpgrade at retail 0x002DA630: slot 7 of the UpgradeMux table 0x010CE710, reached only
// through ILT 0x0001FD48 (its VA appears once in the image). WeaponSetUpgrade's registered
// constructor 0x002DA4E0 stores that table. Slot 7 is
// EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot), which undoes
// slot 9 (WeaponSetUpgrade::upgradeImplementation).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md

class BfmeSubTEB
{
public:
	void bfmeSetTEB(int a);
};

class BfmeBaseTEB
{
public:
	void bfmeInitTEB();
};

class WeaponSetUpgrade
{
public:
	virtual void bfmeV0TEB() = 0;
	virtual void bfmeV1TEB() = 0;
	virtual void bfmeV2TEB() = 0;
	virtual void bfmeV3TEB() = 0;
	virtual void bfmeV4TEB() = 0;
	virtual void bfmeV5TEB() = 0;
	virtual void bfmeV6TEB() = 0;
	virtual void bfmeV7TEB() = 0;
	virtual void bfmeDoTEB(int a) = 0;
protected:
	virtual void removeUpgrade();
};

void WeaponSetUpgrade::removeUpgrade()
{
	(*(BfmeSubTEB **)((char *)this - 8))->bfmeSetTEB(3);
	((BfmeBaseTEB *)((char *)this - 0x10))->bfmeInitTEB();
	bfmeDoTEB(0);
}
