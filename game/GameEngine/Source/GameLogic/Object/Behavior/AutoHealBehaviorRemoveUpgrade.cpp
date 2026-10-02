// AutoHealBehavior::removeUpgrade at retail 0x001EE810 (15 B): slot 7 of the
// UpgradeMux table 0x010A1C20, which AutoHealBehavior's registered constructor
// 0x001EE950 stores at its UpgradeMux sub-object (+0x20). The only route is
// ILT 0x00049C60, whose VA appears once in the image. Slot 7 is
// EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot), which undoes slot 9
// (AutoHealBehavior::upgradeImplementation, 0x001EE8D0). The body
// clears the sub-object's +0xC field and calls slot 8 (setUpgradeExecuted in
// attemptUpgrade's order) with false.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
//
// Moved from S1VirtualSlotDispatch.cpp with its byte notes: offset 0 holds the
// vftable, the slot index is reproduced by placeholder virtuals, and the char
// array reproduces the proven field offset.

class AutoHealBehavior
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8( int value );

protected:
	virtual void removeUpgrade();

public:

	char m_lead[ 8 ];
	int m_value;
};

void AutoHealBehavior::removeUpgrade()
{
	m_value = 0;
	slot8( 0 );
}

