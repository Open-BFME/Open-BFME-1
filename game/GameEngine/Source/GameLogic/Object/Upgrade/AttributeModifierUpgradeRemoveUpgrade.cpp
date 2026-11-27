// ILT41970 reaches Rva002D9F90Behavior::clearConfiguredModelCondition.
// ILT1EF9C -> BfmeOwnerXI::bfmeSendXI(BfmeMsgXI*) keeps one stack slot.
class Rva002D9F90Behavior { public: void clearConfiguredModelCondition(); };
class BfmeMsgXI;
class BfmeOwnerXI { public: void bfmeSendXI(BfmeMsgXI *); };

// AttributeModifierUpgrade::removeUpgrade at retail 0x002D3000: slot 7 of the UpgradeMux table 0x010CBBC0, reached only
// through ILT 0x0001C698 (its VA appears once in the image). AttributeModifierUpgrade's registered
// constructor 0x002D2EB0 stores that table. Slot 7 is
// EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot), which undoes
// slot 9 (AttributeModifierUpgrade::upgradeImplementation).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md

class BfmeG1040
{
public:
};

class BfmeH1040
{
public:
};

class AttributeModifierUpgrade
{
public:
	virtual char bfmeAsk1040();
	virtual void bfmeVF11040();
	virtual void bfmeVF21040();
	virtual void bfmeVF31040();
	virtual void bfmeVF41040();
	virtual void bfmeVF51040();
	virtual void bfmeVF61040();
	virtual void bfmeVF71040();
	virtual void bfmeFin1040(int n);
public:
	virtual void removeUpgrade();
};

void AttributeModifierUpgrade::removeUpgrade()
{
	if (bfmeAsk1040() == 0)
		return;

	((Rva002D9F90Behavior *)((char *)this - 0x10))->clearConfiguredModelCondition();
	(*(BfmeOwnerXI **)((char *)this - 8))->bfmeSendXI((BfmeMsgXI *)(*(char **)((char *)this - 0xc) + 0x70));
	bfmeFin1040(0);
}
