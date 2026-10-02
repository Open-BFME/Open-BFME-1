// LocomotorSetUpgrade::removeUpgrade at retail 0x002D62C0 (21 B): slot 7 of the
// UpgradeMux table 0x010CCFA8, which LocomotorSetUpgrade's registered
// constructor 0x002D6160 stores at +0x10. The only route is ILT 0x00037F01, whose
// VA appears once in the image. Slot 7 is EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot),
// which undoes slot 9 (LocomotorSetUpgrade::upgradeImplementation, 0x002D6290): it calls the
// Object's +0x204 interface with 0 where slot 9 passes the module-data flag.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md
// Moved from BfmeConv821.cpp.

class BfmeSub204_2C0
{
public:
	void doCall(int dummy);
};

struct BfmeOwner2C0
{
	unsigned char pad[0x204];
	BfmeSub204_2C0 *m_sub204;
};

// The Object pointer sits 8 bytes ahead of the UpgradeMux sub-object.
struct BfmeParent2C0
{
	BfmeOwner2C0 *m_owner;
};

class LocomotorSetUpgrade
{
protected:
	virtual void removeUpgrade();
};

void LocomotorSetUpgrade::removeUpgrade()
{
	BfmeParent2C0 *p = (BfmeParent2C0 *)((char *)this - 8);
	if (p->m_owner->m_sub204)
		p->m_owner->m_sub204->doCall(0);
}
