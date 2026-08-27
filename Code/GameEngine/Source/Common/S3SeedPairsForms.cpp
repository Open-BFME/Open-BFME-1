// cl: /DNDEBUG /MD /EHs-c-

// Open-BFME5: forty more seeders of the same family, covering every remaining
// hand-over form the earlier two grammars could not read:
//
//   * a hand-over to a member of a SUB-OBJECT (`lea ecx,[edi+N]` before the
//     direct call, so the sub-object is the `this`);
//   * a __cdecl helper taking the target FIRST and the sub-object second --
//     its `add esp,8` is often merged into a later cleanup, so the pair of
//     pushes is what identifies it, not the cleanup;
//   * slot 0x24, which carries a literal 4 behind the address (a sized
//     hand-over) and is the only slot in this set with two arguments;
//   * slot 0x30, which is handed the VALUE of a pointer member rather than
//     the address of a sub-object;
//   * guards that jump to a mid-body label rather than the epilogue, which
//     makes the tail of the body a nested block instead of the whole of it.
//
// The vtable register alternates between eax and edx purely by scheduling --
// both spellings are the same source and both appear inside one body.

struct BfmeSeedPair
{
	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
};

class BfmeSeedTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual bool bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual bool bfmeSkip(void);		// slot 4, vtable+0x10
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeTakeAt24(void *item, int size);		// slot 9, vtable+0x24
	virtual void bfmeSeed(BfmeSeedPair *pair);		// slot 10, vtable+0x28
	virtual void bfmeSlot11(void);
	virtual void bfmeTakeAt30(void *held);		// slot 12, vtable+0x30
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeTakeAt4C(void *item);		// slot 19, vtable+0x4C
	virtual void bfmeTakeAt50(void *item);		// slot 20, vtable+0x50
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeTakeAt60(void *item);		// slot 24, vtable+0x60
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeTakeAt6C(void *item);		// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
	virtual void bfmeTakeAt78(void *item);		// slot 30, vtable+0x78
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeTakeAt84(void *item);		// slot 33, vtable+0x84
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);		// slot 35, vtable+0x8C
};

class BfmeSubAccept_000061B3
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000061B3
};

class BfmeSubAcceptRef
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeRelease(void);
};

class BfmeSubAccept_0001DE5D
{
public:
	__declspec(noinline) void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0001DE5D

private:
	void *m_bfmeHead;
	BfmeSubAcceptRef *m_bfmeRef;
	bool m_bfmeOwned;
	char m_bfmePad[0x7];
};

class BfmeSubAccept_00029DAC
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00029DAC
};

class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0002C41C
};

class BfmeSubAccept_00031A07
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00031A07
};

class BfmeSubAccept_000328EE
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000328EE
};

class BfmeSubAccept_0003EA86
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0003EA86
};

// ?bfmeAccept@BfmeSubAccept_0001DE5D@@QAEXPAVBfmeSeedTarget@@@Z		49 bytes
__declspec(noinline) void BfmeSubAccept_0001DE5D::bfmeAccept(BfmeSeedTarget *target)
{
	if (target->bfmeSlot1())
	{
		m_bfmeHead = 0;
		if (m_bfmeRef)
			m_bfmeRef->bfmeRelease();
		m_bfmeRef = 0;
		m_bfmeOwned = true;
	}
}

void bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *item);		// ILT 0x0000C9B4
void bfmeHandOver_0000FFE2(BfmeSeedTarget *target, void *item);		// ILT 0x0000FFE2
void bfmeHandOver_00020586(BfmeSeedTarget *target, void *item);		// ILT 0x00020586
void bfmeHandOver_0003EE32(BfmeSeedTarget *target, void *item);		// ILT 0x0003EE32

class Gen_0016B250
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x54
};

class Gen_0016B510
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	void *m_bfmeHeld0;				// +0x24
};

class Gen_0016B940
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x5C
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x68
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x6C
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x70
	char m_bfmeItem5;				// +0x71
	char m_bfmeItem6;				// +0x72
	char m_bfmeItem7;				// +0x73
	char m_bfmeItem8;				// +0x74
	char m_bfmeItem9;				// +0x75
};

class Gen_0016BAD0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
};

class Gen_0016BB90
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x5C
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x60
	char m_bfmeItem3;				// +0x61
	char m_bfmeItem4;				// +0x62
	char m_bfmeItem5;				// +0x63
	char m_bfmeItem6;				// +0x64
};

class Gen_0016BCF0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x54
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x60
};

class Gen_0016BFC0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x54
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x60
	char m_bfmePad3[0x7];
	char m_bfmeItem3;				// +0x68
};

class Gen_0016C730
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00033BF4

	char m_bfmePad0[0x6C];
	void *m_bfmeHeld0;				// +0x6C
};

class Gen_0016C7F0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x5C
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x60
};

class Gen_0016D180
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
};

class Gen_0016D480
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
};

class Gen_001ED0C0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_001EE830
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	BfmeSubAccept_00029DAC m_bfmeSub0;		// +0x20
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x2C
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x30
};

class Gen_001FFCA0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0003689A

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0x3];
	BfmeSubAccept_0002C41C m_bfmeSub1;		// +0x54
	char m_bfmePad2[0x6F];
	char m_bfmeItem2;				// +0xC4
	char m_bfmePad3[0xB];
	char m_bfmeItem3;				// +0xD0
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0xD4
};

class Gen_00202740
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
};

class Gen_00202D30
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x2C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x30
};

class Gen_00204710
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	BfmeSubAccept_00029DAC m_bfmeSub0;		// +0x20
};

class Gen_00207470
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_00214C60
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00031557

	char m_bfmePad0[0xE0];
	char m_bfmeItem0;				// +0xE0
};

class Gen_00214EA0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00031557

	char m_bfmePad0[0xE4];
	char m_bfmeItem0;				// +0xE4
};

class Gen_00268060
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000160B3

	char m_bfmePad0[0x14];
	char m_bfmeItem0;				// +0x14
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x18
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x1C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x20
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x24
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x28
};

class Gen_0028CE90
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
};

class Gen_00292E60
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	void *m_bfmeHeld0;				// +0x20
};

class Gen_002A07E0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	BfmeSubAccept_0001DE5D m_bfmeSub0;		// +0x20
	char m_bfmeItem1;				// +0x30
};

class Gen_002AE710
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x2C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x30
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x34
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x38
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x3C
	char m_bfmePad7[0x3];
	char m_bfmeItem7;				// +0x40
};

class Gen_002AF780
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x7];
	char m_bfmeItem2;				// +0x30
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x34
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x38
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x3C
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x40
	char m_bfmePad7[0x3];
	char m_bfmeItem7;				// +0x44
	char m_bfmePad8[0x3];
	char m_bfmeItem8;				// +0x48
};

class Gen_002B6F10
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
};

class Gen_002B6FA0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
};

class Gen_002B6FF0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x44];
	char m_bfmeItem0;				// +0x44
};

class Gen_002B7030
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	void *m_bfmeHeld1;				// +0x28
};

class Gen_002BBD40
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0000DC24

};

class Gen_002BE2A0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x34
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x38
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x3C
};

class Gen_002BE460
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
};

class Gen_005EE7B0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0xC];
	BfmeSubAccept_000061B3 m_bfmeSub0;		// +0x0C
	char m_bfmePad1[0x43];
	char m_bfmeItem1;				// +0x50
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x54
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x58
};

class Gen_005F4300
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x18];
	BfmeSubAccept_0003EA86 m_bfmeSub0;		// +0x18
};

class Gen_005F67A0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x18];
	BfmeSubAccept_000328EE m_bfmeSub0;		// +0x18
};

class Gen_005FA6D0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x1C];
	char m_bfmeItem0;				// +0x1C
};

class Gen_005FFA00
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0xC];
	BfmeSubAccept_00031A07 m_bfmeSub0;		// +0x0C
};

class Gen_0077F790
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00011CBB

	char m_bfmePad0[0x27D];
	char m_bfmeItem0;				// +0x27D
	char m_bfmeItem1;				// +0x27E
	char m_bfmePad2[0x89];
	BfmeSubAccept_0002C41C m_bfmeSub2;		// +0x308
	char m_bfmePad3[0x6F];
	BfmeSubAccept_0002C41C m_bfmeSub3;		// +0x378
};

class Gen_00881C60
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeItem0;				// +0x00
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x04
};

// ?bfmeSeed@Gen_0016B250@@QAEXPAVBfmeSeedTarget@@@Z		81 bytes
void Gen_0016B250::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt74(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_0016B510@@QAEXPAVBfmeSeedTarget@@@Z		48 bytes
void Gen_0016B510::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt30(m_bfmeHeld0);
}

// ?bfmeSeed@Gen_0016B940@@QAEXPAVBfmeSeedTarget@@@Z		188 bytes
void Gen_0016B940::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt60(&m_bfmeItem0);
		target->bfmeTakeAt74(&m_bfmeItem2);
		target->bfmeTakeAt8C(&m_bfmeItem4);
		target->bfmeTakeAt8C(&m_bfmeItem5);
		target->bfmeTakeAt8C(&m_bfmeItem6);
		target->bfmeTakeAt8C(&m_bfmeItem7);
		target->bfmeTakeAt60(&m_bfmeItem1);
		target->bfmeTakeAt74(&m_bfmeItem3);
		target->bfmeTakeAt8C(&m_bfmeItem9);
		target->bfmeTakeAt8C(&m_bfmeItem8);
	}
}

// ?bfmeSeed@Gen_0016BAD0@@QAEXPAVBfmeSeedTarget@@@Z		59 bytes
void Gen_0016BAD0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt74(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_0016BB90@@QAEXPAVBfmeSeedTarget@@@Z		148 bytes
void Gen_0016BB90::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt60(&m_bfmeItem0);
		target->bfmeTakeAt74(&m_bfmeItem1);
		target->bfmeTakeAt8C(&m_bfmeItem2);
		target->bfmeTakeAt8C(&m_bfmeItem3);
		target->bfmeTakeAt8C(&m_bfmeItem4);
		target->bfmeTakeAt8C(&m_bfmeItem5);
		target->bfmeTakeAt8C(&m_bfmeItem6);
	}
}

// ?bfmeSeed@Gen_0016BCF0@@QAEXPAVBfmeSeedTarget@@@Z		89 bytes
void Gen_0016BCF0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt60(&m_bfmeItem1);
		target->bfmeTakeAt4C(&m_bfmeItem2);
		target->bfmeTakeAt74(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_0016BFC0@@QAEXPAVBfmeSeedTarget@@@Z		103 bytes
void Gen_0016BFC0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt60(&m_bfmeItem1);
		target->bfmeTakeAt4C(&m_bfmeItem2);
		target->bfmeTakeAt74(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem3);
	}
}

// ?bfmeSeed@Gen_0016C730@@QAEXPAVBfmeSeedTarget@@@Z		67 bytes
void Gen_0016C730::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt30(m_bfmeHeld0);
	}
}

// ?bfmeSeed@Gen_0016C7F0@@QAEXPAVBfmeSeedTarget@@@Z		89 bytes
void Gen_0016C7F0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt60(&m_bfmeItem0);
		target->bfmeTakeAt78(&m_bfmeItem1);
		target->bfmeTakeAt78(&m_bfmeItem2);
	}
}

// ?bfmeSeed@Gen_0016D180@@QAEXPAVBfmeSeedTarget@@@Z		58 bytes
void Gen_0016D180::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
}

// ?bfmeSeed@Gen_0016D480@@QAEXPAVBfmeSeedTarget@@@Z		50 bytes
void Gen_0016D480::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
}

// ?bfmeSeed@Gen_001ED0C0@@QAEXPAVBfmeSeedTarget@@@Z		70 bytes
void Gen_001ED0C0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt8C(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_001EE830@@QAEXPAVBfmeSeedTarget@@@Z		79 bytes
void Gen_001EE830::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	m_bfmeSub0.bfmeAccept(target);
	target->bfmeTakeAt74(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_001FFCA0@@QAEXPAVBfmeSeedTarget@@@Z		110 bytes
void Gen_001FFCA0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	target->bfmeTakeAt74(&m_bfmeItem0);
	m_bfmeSub1.bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem4);
	target->bfmeTakeAt60(&m_bfmeItem2);
	target->bfmeTakeAt6C(&m_bfmeItem3);
}

// ?bfmeSeed@Gen_00202740@@QAEXPAVBfmeSeedTarget@@@Z		69 bytes
void Gen_00202740::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	target->bfmeTakeAt74(&m_bfmeItem0);
	bfmeHandOver_0000FFE2(target, &m_bfmeItem1);
}

// ?bfmeSeed@Gen_00202D30@@QAEXPAVBfmeSeedTarget@@@Z		98 bytes
void Gen_00202D30::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
		target->bfmeTakeAt74(&m_bfmeItem1);
		target->bfmeTakeAt6C(&m_bfmeItem2);
		bfmeHandOver_00020586(target, &m_bfmeItem3);
	}
}

// ?bfmeSeed@Gen_00204710@@QAEXPAVBfmeSeedTarget@@@Z		54 bytes
void Gen_00204710::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	m_bfmeSub0.bfmeAccept(target);
}

// ?bfmeSeed@Gen_00207470@@QAEXPAVBfmeSeedTarget@@@Z		58 bytes
void Gen_00207470::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
}

// ?bfmeSeed@Gen_00214C60@@QAEXPAVBfmeSeedTarget@@@Z		72 bytes
void Gen_00214C60::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_00214EA0@@QAEXPAVBfmeSeedTarget@@@Z		72 bytes
void Gen_00214EA0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		bfmeHandOver_0000C9B4(target, &m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_00268060@@QAEXPAVBfmeSeedTarget@@@Z		116 bytes
void Gen_00268060::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	target->bfmeTakeAt74(&m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
	target->bfmeTakeAt74(&m_bfmeItem2);
	target->bfmeTakeAt6C(&m_bfmeItem3);
	target->bfmeTakeAt8C(&m_bfmeItem4);
	bfmeHandOver_0000C9B4(target, &m_bfmeItem5);
}

// ?bfmeSeed@Gen_0028CE90@@QAEXPAVBfmeSeedTarget@@@Z		76 bytes
void Gen_0028CE90::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_00292E60@@QAEXPAVBfmeSeedTarget@@@Z		67 bytes
void Gen_00292E60::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt30(m_bfmeHeld0);
	}
}

// ?bfmeSeed@Gen_002A07E0@@QAEXPAVBfmeSeedTarget@@@Z		75 bytes
void Gen_002A07E0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		m_bfmeSub0.bfmeAccept(target);
		target->bfmeTakeAt8C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_002AE710@@QAEXPAVBfmeSeedTarget@@@Z		142 bytes
void Gen_002AE710::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
		target->bfmeTakeAt74(&m_bfmeItem1);
		target->bfmeTakeAt24(&m_bfmeItem2, 4);
		target->bfmeTakeAt6C(&m_bfmeItem3);
		target->bfmeTakeAt6C(&m_bfmeItem4);
		target->bfmeTakeAt6C(&m_bfmeItem5);
		target->bfmeTakeAt6C(&m_bfmeItem6);
		target->bfmeTakeAt6C(&m_bfmeItem7);
	}
}

// ?bfmeSeed@Gen_002AF780@@QAEXPAVBfmeSeedTarget@@@Z		153 bytes
void Gen_002AF780::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
		target->bfmeTakeAt50(&m_bfmeItem1);
		target->bfmeTakeAt24(&m_bfmeItem2, 4);
		target->bfmeTakeAt6C(&m_bfmeItem3);
		target->bfmeTakeAt6C(&m_bfmeItem4);
		target->bfmeTakeAt6C(&m_bfmeItem5);
		target->bfmeTakeAt6C(&m_bfmeItem6);
		target->bfmeTakeAt78(&m_bfmeItem7);
		target->bfmeTakeAt60(&m_bfmeItem8);
	}
}

// ?bfmeSeed@Gen_002B6F10@@QAEXPAVBfmeSeedTarget@@@Z		61 bytes
void Gen_002B6F10::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt24(&m_bfmeItem0, 4);
	target->bfmeTakeAt78(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_002B6FA0@@QAEXPAVBfmeSeedTarget@@@Z		61 bytes
void Gen_002B6FA0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt24(&m_bfmeItem0, 4);
	target->bfmeTakeAt74(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_002B6FF0@@QAEXPAVBfmeSeedTarget@@@Z		50 bytes
void Gen_002B6FF0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt24(&m_bfmeItem0, 4);
}

// ?bfmeSeed@Gen_002B7030@@QAEXPAVBfmeSeedTarget@@@Z		61 bytes
void Gen_002B7030::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt24(&m_bfmeItem0, 4);
	target->bfmeTakeAt30(m_bfmeHeld1);
}

// ?bfmeSeed@Gen_002BBD40@@QAEXPAVBfmeSeedTarget@@@Z		56 bytes
void Gen_002BBD40::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	if ( !target->bfmeSkip() )
	{
		bfmeAccept(target);

	}
}

// ?bfmeSeed@Gen_002BE2A0@@QAEXPAVBfmeSeedTarget@@@Z		97 bytes
void Gen_002BE2A0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt24(&m_bfmeItem0, 4);
	target->bfmeTakeAt60(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
	target->bfmeTakeAt74(&m_bfmeItem3);
	target->bfmeTakeAt6C(&m_bfmeItem4);
}

// ?bfmeSeed@Gen_002BE460@@QAEXPAVBfmeSeedTarget@@@Z		50 bytes
void Gen_002BE460::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt24(&m_bfmeItem0, 4);
}

// ?bfmeSeed@Gen_005EE7B0@@QAEXPAVBfmeSeedTarget@@@Z		79 bytes
void Gen_005EE7B0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	m_bfmeSub0.bfmeAccept(target);
	target->bfmeTakeAt6C(&m_bfmeItem1);
	target->bfmeTakeAt6C(&m_bfmeItem2);
	target->bfmeTakeAt78(&m_bfmeItem3);
}

// ?bfmeSeed@Gen_005F4300@@QAEXPAVBfmeSeedTarget@@@Z		46 bytes
void Gen_005F4300::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	m_bfmeSub0.bfmeAccept(target);
}

// ?bfmeSeed@Gen_005F67A0@@QAEXPAVBfmeSeedTarget@@@Z		46 bytes
void Gen_005F67A0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	m_bfmeSub0.bfmeAccept(target);
}

// ?bfmeSeed@Gen_005FA6D0@@QAEXPAVBfmeSeedTarget@@@Z		50 bytes
void Gen_005FA6D0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeHandOver_0003EE32(target, &m_bfmeItem0);
}

// ?bfmeSeed@Gen_005FFA00@@QAEXPAVBfmeSeedTarget@@@Z		46 bytes
void Gen_005FFA00::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	m_bfmeSub0.bfmeAccept(target);
}

// ?bfmeSeed@Gen_0077F790@@QAEXPAVBfmeSeedTarget@@@Z		114 bytes
void Gen_0077F790::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		m_bfmeSub2.bfmeAccept(target);
		m_bfmeSub3.bfmeAccept(target);
	}
}

// ?bfmeSeed@Gen_00881C60@@QAEXPAVBfmeSeedTarget@@@Z		61 bytes
void Gen_00881C60::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt84(&m_bfmeItem0);
	target->bfmeTakeAt24(&m_bfmeItem1, 4);
}
