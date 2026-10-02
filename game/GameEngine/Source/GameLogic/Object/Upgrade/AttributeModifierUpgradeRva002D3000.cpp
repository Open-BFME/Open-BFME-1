// AttributeModifierUpgrade::rva002D3000 at retail 0x002D3000: slot 7 of the UpgradeMux table 0x010CBBC0, reached only
// through ILT 0x0001C698 (its VA appears once in the image). AttributeModifierUpgrade's registered
// constructor 0x002D2EB0 stores that table. Slot 7 is a BFME-only virtual that undoes
// slot 9 (AttributeModifierUpgrade::upgradeImplementation); its name is unproven, so the method
// keeps its address.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md

class BfmeG1040
{
public:
	void bfmeStep1040(void);
};

class BfmeH1040
{
public:
	void bfmeAdd1040(void *p);
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
protected:
	virtual void rva002D3000();
};

void AttributeModifierUpgrade::rva002D3000()
{
	if (bfmeAsk1040() == 0)
		return;

	((BfmeG1040 *)((char *)this - 0x10))->bfmeStep1040();
	(*(BfmeH1040 **)((char *)this - 8))->bfmeAdd1040(*(char **)((char *)this - 0xc) + 0x70);
	bfmeFin1040(0);
}
