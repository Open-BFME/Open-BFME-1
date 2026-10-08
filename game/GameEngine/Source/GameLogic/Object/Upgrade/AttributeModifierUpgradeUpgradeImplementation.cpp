// AttributeModifierUpgrade::upgradeImplementation at retail 0x002D2FD0: slot 9 of the UpgradeMux table
// 0x010CBBC0, reached only through ILT 0x00026413 (its VA appears once in the image).
// AttributeModifierUpgrade's registered constructor 0x002D2EB0 stores that table. Slot 9 is the
// upgradeImplementation call in UpgradeMux::attemptUpgrade (0x002D9AD0).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

class BfmeBaseTCB
{
public:
	void bfmeInitTCB();
};

class BfmeSetterTCB
{
public:
	void bfmeSetTCB(void *p, int v);
};

// Retail calls reach ILT 0x0000835F -> 0x002D9F30 and ILT 0x00037A56 ->
// 0x001C1DA0; called by those ledger row names.
class Rva002D9F30Owner
{
public:
	void setCondition();
};

class AsciiString;

class Object
{
public:
	bool applyAttributeModifier(const AsciiString &name, int frames);
};

class AttributeModifierUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void AttributeModifierUpgrade::upgradeImplementation()
{
	((Rva002D9F30Owner *)(BfmeBaseTCB *)((char *)this - 0x10))->setCondition();
	BfmeSetterTCB *s = *(BfmeSetterTCB **)((char *)this - 8);
	((Object *)s)->applyAttributeModifier(*(const AsciiString *)(*(char **)((char *)this - 0xc) + 0x70), -1);
}
