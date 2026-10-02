// LocomotorSetUpgrade::upgradeImplementation at retail 0x002D6290: slot 9 of the UpgradeMux table
// 0x010CCFA8, reached only through ILT 0x0000744B (its VA appears once in the image).
// LocomotorSetUpgrade's registered constructor 0x002D6160 stores that table. Slot 9 is the
// upgradeImplementation call in UpgradeMux::attemptUpgrade (0x002D9AD0).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

class BfmeZ1034
{
public:
	void bfmeSet1034(char on);
};

struct BfmeW1034
{
	char m_bfmePad[0x204];
	BfmeZ1034 *m_bfmeZ;
};

struct BfmeV1034
{
	char m_bfmePad[0x70];
	char m_bfmeFlag;
};

class LocomotorSetUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void LocomotorSetUpgrade::upgradeImplementation()
{
	BfmeZ1034 *z = (*(BfmeW1034 **)((char *)this - 8))->m_bfmeZ;

	if (z != 0)
		z->bfmeSet1034((char)((*(BfmeV1034 **)((char *)this - 0xc))->m_bfmeFlag == 0));
}
