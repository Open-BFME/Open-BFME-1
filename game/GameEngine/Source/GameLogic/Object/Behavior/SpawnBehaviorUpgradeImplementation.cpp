// cl: /DNDEBUG /MD /EHsc
// SpawnBehavior::upgradeImplementation at retail 0x0020A800: slot 9 of the
// UpgradeMux table 0x010A6B70, reached only through ILT 0x00009AF7 (its VA
// appears once in the image). SpawnBehavior's registered constructor 0x0020AE30
// stores that table. Slot 9 is the upgradeImplementation call in
// UpgradeMux::attemptUpgrade (0x002D9AD0).
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
//
// The body only calls slot 8 with true. attemptUpgrade makes that slot-8 call
// last, where Zero Hour's giveSelfUpgrade calls setUpgradeExecuted(true).
// Zero Hour's SpawnBehavior is not an UpgradeMux, so this override is BFME's.

typedef bool Bool;

class UpgradeMux
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
protected:
	virtual void setUpgradeExecuted(Bool executed);
};

class SpawnBehavior : public UpgradeMux
{
protected:
	virtual void upgradeImplementation();
};

void SpawnBehavior::upgradeImplementation()
{
	setUpgradeExecuted(true);
}
