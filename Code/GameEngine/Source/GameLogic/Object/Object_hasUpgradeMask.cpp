// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Object::hasUpgradeMask, retail 0x001C59C0, 84 bytes. The body
// carried only a machine byte-dump row; the name is the symbols.csv pin.
//
// An upgrade bit is looked for in two places. First the delegate at +0x1FC, if
// there is one, is asked for its source -- slot 26 of its table, no arguments
// -- and that source, if it hands one back, is asked about the bit at slot 42.
// A yes there ends the function.
//
// The delegate goes into a local first. Reading the member straight into the
// test leaves the compiler holding it in eax and copying it into ecx for the
// call, and shifts which of esi and edi carries this.
//
// Otherwise the object's own bit array at +0x224 answers: word bit >> 5, mask
// one shifted by the low five bits. The and result is turned into a Bool by
// neg/sbb/neg, which is what this compiler emits for a plain != 0 on an int.

typedef unsigned int UnsignedInt;
typedef bool Bool;

class BfmeUpgradeSource
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual Bool bfmeHasUpgrade(UnsignedInt bit) = 0;	// slot 42, vtable+0xA8
};

class BfmeUpgradeDelegate
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual BfmeUpgradeSource *bfmeSource(void) = 0;	// slot 26, vtable+0x68
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool hasUpgradeMask(UnsignedInt bit) const;

private:
	char m_bfmeHeadA[0x1FC];
	BfmeUpgradeDelegate *m_bfmeDelegate;			// +0x1FC
	char m_bfmeHeadB[0x224 - 0x200];
	UnsignedInt m_bfmeUpgradeMask[4];			// +0x224
};

// ?hasUpgradeMask@Object@@QBE_NI@Z
Bool Object::hasUpgradeMask(UnsignedInt bit) const
{
	BfmeUpgradeDelegate *delegate = m_bfmeDelegate;

	if (delegate)
	{
		BfmeUpgradeSource *source = delegate->bfmeSource();

		if (source && source->bfmeHasUpgrade(bit))
			return true;
	}

	return (m_bfmeUpgradeMask[bit >> 5] & (1 << (bit & 31))) != 0;
}
