// ILT122AB -> Gen001C9AC0::handle(int); ILT41970 -> d_002d9f90.
// Retain the clear body's independently verified ECX/no-argument/RET0 ABI.
extern "C" void __cdecl __identifier("?d_002d9f90@@YAXXZ")();
class Gen001C9AC0 { public: void handle(int); };

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
};

class BfmeBaseTEB
{
public:
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
public:
	virtual void removeUpgrade();
};

void WeaponSetUpgrade::removeUpgrade()
{
	(*(Gen001C9AC0 **)((char *)this - 8))->handle(3);
	union
	{
		void (__cdecl *symbol)();
		void (BfmeBaseTEB::*member)();
	} clear;
	clear.symbol = &__identifier("?d_002d9f90@@YAXXZ");
	(((BfmeBaseTEB *)((char *)this - 0x10))->*clear.member)();
	bfmeDoTEB(0);
}
