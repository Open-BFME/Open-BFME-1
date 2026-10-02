// cl: /DNDEBUG /MD /EHsc
// DevastateSpecialPower::doSpecialPowerAtObject at retail 0x0025A910 (16 B):
// slot 12 of the SpecialPowerModuleInterface table 0x010B4608, which the
// registered DevastateSpecialPower constructor 0x0025A7C0 stores at +0x10. It is
// reached only through ILT 0x00019191, whose VA appears once in the image.
// Object::doSpecialPowerAtObject (0x001C37F0) calls slot 12.
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md
//
// Moved from S3SubObjectAdjusters.cpp. The body rewrites its first stack
// argument in place to the target's +0x38 sub-object (its position) and
// tail-jumps to slot 13 with the same two arguments. Slot 13 keeps a
// placeholder name; see the evidence note's open question.

typedef unsigned int UnsignedInt;

class Object;

struct BfmeSub
{
	char m_bfmeBytes[4];
};

struct BfmeWhole
{
	char m_bfmeHead[0x38];
	BfmeSub m_bfmeSub;					// +0x38
};

class DevastateSpecialPower
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10();
	virtual void doSpecialPower(UnsignedInt commandOptions);
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions);
	virtual void slot13(BfmeSub *where, UnsignedInt commandOptions);
};

void DevastateSpecialPower::doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions)
{
	slot13(&((BfmeWhole *)obj)->m_bfmeSub, commandOptions);
}
