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

// Retail calls reach ILT 0x0000835F -> 0x002D9F30 and ILT 0x000348EC ->
// 0x001C9A10; called by those ledger row names.
class Rva002D9F30Owner
{
public:
	void setCondition();
};

class Gen001C9A10
{
public:
	void handle(int a);
};

class WeaponSetUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void WeaponSetUpgrade::upgradeImplementation()
{
	((Rva002D9F30Owner *)(BfmeBaseTFA *)((char *)this - 0x10))->setCondition();
	((Gen001C9A10 *)*(BfmeSubTFA **)((char *)this - 8))->handle(3);
}
