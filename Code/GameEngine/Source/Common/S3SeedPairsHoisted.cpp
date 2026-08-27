// cl: /DNDEBUG /MD /EHs-c-

// Open-BFME5: twelve more seeders, from two last grammar corrections.
//
// One is a real shape: some bodies hoist the target's vtable load into the
// PROLOGUE, ahead of `push edi`, because the first thing they do is ask the
// guard.  Nothing about the source changes -- the load simply moves in front
// of the register saves.
//
// The other was a reading error worth recording: a displacement of nine or
// less disassembles as a bare decimal (`lea eax,[edi + 4]`), not as `0x4`, so
// a hex-only pattern silently drops every sub-object living in the first ten
// bytes of its class.  Those are exactly the common ones.

struct BfmeSeedPair
{
	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
};

class BfmeSeedTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
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
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeTakeAt3C(void *item);		// slot 15, vtable+0x3C
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeTakeAt60(void *item);		// slot 24, vtable+0x60
	virtual void bfmeSlot25(void);
	virtual void bfmeTakeAt68(void *item);		// slot 26, vtable+0x68
	virtual BfmeSeedTarget *bfmeTakeAt6C(void *item);		// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
	virtual void bfmeTakeAt78(void *item);		// slot 30, vtable+0x78
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeTakeAt88(void *item);		// slot 34, vtable+0x88
	virtual void bfmeTakeAt8C(void *item);		// slot 35, vtable+0x8C
};

class BfmeSubAccept_00007289
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00007289
};

class BfmeSubAccept_00016B85
{
public:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00016B85
};

__declspec(noinline) void bfmeHandOver_00001A50(BfmeSeedTarget *target, void *item);		// ILT 0x00001A50
void bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *item);		// ILT 0x0000C9B4
void bfmeHandOver_0000FFE2(BfmeSeedTarget *target, void *item);		// ILT 0x0000FFE2
void bfmeHandOver_00012C65(BfmeSeedTarget *target, void *item);		// ILT 0x00012C65
void bfmeHandOver_000353C8(BfmeSeedTarget *target, void *item);		// ILT 0x000353C8
void bfmeHandOver_00044FD0(BfmeSeedTarget *target, void *item);		// ILT 0x00044FD0

// ?bfmeHandOver_00001A50@@YAXPAVBfmeSeedTarget@@PAX@Z		39 bytes
__declspec(noinline) void bfmeHandOver_00001A50(BfmeSeedTarget *target, void *item)
{
	target = target->bfmeTakeAt6C(item);
	target = target->bfmeTakeAt6C((char *)item + 4);
	target->bfmeTakeAt6C((char *)item + 8);
}

class Gen_000E6910
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x08
};

class Gen_0015E7E0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00022363

	char m_bfmePad0[0x44];
	char m_bfmeItem0;				// +0x44
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x50
};

class Gen_00161080
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x08
	char m_bfmePad2[0x7];
	char m_bfmeItem2;				// +0x10
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x14
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x18
	char m_bfmeItem5;				// +0x19
};

class Gen_002DFE90
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x08
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x0C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x10
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x14
};

class Gen_003A6540
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x8];
	char m_bfmeItem0;				// +0x08
};

class Gen_00412390
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x10
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x1C
	char m_bfmePad3[0xB];
	char m_bfmeItem3;				// +0x28
	char m_bfmePad4[0xB];
	char m_bfmeItem4;				// +0x34
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x38
	char m_bfmeItem6;				// +0x39
};

class Gen_004584D0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeItem0;				// +0x00
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x04
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x08
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x0C
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x10
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x14
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x18
	char m_bfmePad7[0x3];
	char m_bfmeItem7;				// +0x1C
	char m_bfmePad8[0x3];
	char m_bfmeItem8;				// +0x20
	char m_bfmePad9[0x3];
	char m_bfmeItem9;				// +0x24
	char m_bfmePad10[0x3];
	char m_bfmeItem10;				// +0x28
	char m_bfmePad11[0x3];
	char m_bfmeItem11;				// +0x2C
};

class Gen_005BDC70
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x10
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x1C
	char m_bfmePad3[0xB];
	char m_bfmeItem3;				// +0x28
	char m_bfmePad4[0xB];
	char m_bfmeItem4;				// +0x34
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x38
};

class Gen_005EFA40
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0xC];
	BfmeSubAccept_00007289 m_bfmeSub0;		// +0x0C
	char m_bfmePad1[0x87];
	char m_bfmeItem1;				// +0x94
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0xA0
	char m_bfmePad3[0xB];
	char m_bfmeItem3;				// +0xAC
};

class Gen_005FC540
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x1C];
	char m_bfmeItem0;				// +0x1C
	char m_bfmeItem1;				// +0x1D
	char m_bfmePad2[0x2];
	BfmeSubAccept_00016B85 m_bfmeSub2;		// +0x20
	char m_bfmePad3[0x1B];
	char m_bfmeItem3;				// +0x3C
};

class Gen_005FF940
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x08
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x0C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x10
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x14
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x18
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x1C
};

class Gen_006007A0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x08
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x0C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x10
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x14
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x18
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x1C
	char m_bfmePad7[0x3];
	char m_bfmeItem7;				// +0x20
	char m_bfmePad8[0x3];
	char m_bfmeItem8;				// +0x24
	char m_bfmePad9[0x3];
	char m_bfmeItem9;				// +0x28
	char m_bfmePad10[0x3];
	char m_bfmeItem10;				// +0x2C
	char m_bfmePad11[0x3];
	char m_bfmeItem11;				// +0x30
	char m_bfmePad12[0x3];
	char m_bfmeItem12;				// +0x34
};

// ?bfmeSeed@Gen_000E6910@@QAEXPAVBfmeSeedTarget@@@Z		69 bytes
void Gen_000E6910::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeHandOver_0000FFE2(target, &m_bfmeItem0);
		bfmeHandOver_0000FFE2(target, &m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_0015E7E0@@QAEXPAVBfmeSeedTarget@@@Z		78 bytes
void Gen_0015E7E0::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeAccept(target);

		bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
		target->bfmeTakeAt60(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_00161080@@QAEXPAVBfmeSeedTarget@@@Z		119 bytes
void Gen_00161080::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeHandOver_000353C8(target, &m_bfmeItem0);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem1);
		target->bfmeTakeAt78(&m_bfmeItem2);
		target->bfmeTakeAt78(&m_bfmeItem3);
		target->bfmeTakeAt8C(&m_bfmeItem4);
		target->bfmeTakeAt8C(&m_bfmeItem5);
	}
}

// ?bfmeSeed@Gen_002DFE90@@QAEXPAVBfmeSeedTarget@@@Z		108 bytes
void Gen_002DFE90::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt6C(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
		bfmeHandOver_0000C9B4(target, &m_bfmeItem2);
		target->bfmeTakeAt68(&m_bfmeItem3);
		target->bfmeTakeAt24(&m_bfmeItem4, 4);
	}
}

// ?bfmeSeed@Gen_003A6540@@QAEXPAVBfmeSeedTarget@@@Z		57 bytes
void Gen_003A6540::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt78(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_00412390@@QAEXPAVBfmeSeedTarget@@@Z		128 bytes
void Gen_00412390::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		bfmeHandOver_00001A50(target, &m_bfmeItem0);
		bfmeHandOver_00001A50(target, &m_bfmeItem1);
		bfmeHandOver_00001A50(target, &m_bfmeItem2);
		bfmeHandOver_00001A50(target, &m_bfmeItem3);
		target->bfmeTakeAt74(&m_bfmeItem4);
		target->bfmeTakeAt8C(&m_bfmeItem6);
		target->bfmeTakeAt88(&m_bfmeItem5);
	}
}

// ?bfmeSeed@Gen_004584D0@@QAEXPAVBfmeSeedTarget@@@Z		171 bytes
void Gen_004584D0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt68(&m_bfmeItem0);
	target->bfmeTakeAt68(&m_bfmeItem1);
	bfmeHandOver_00012C65(target, &m_bfmeItem2);
	target->bfmeTakeAt6C(&m_bfmeItem3);
	target->bfmeTakeAt6C(&m_bfmeItem4);
	target->bfmeTakeAt6C(&m_bfmeItem5);
	target->bfmeTakeAt78(&m_bfmeItem6);
	target->bfmeTakeAt8C(&m_bfmeItem7);
	target->bfmeTakeAt6C(&m_bfmeItem9);
	target->bfmeTakeAt6C(&m_bfmeItem8);
	target->bfmeTakeAt74(&m_bfmeItem10);
	target->bfmeTakeAt6C(&m_bfmeItem11);
}

// ?bfmeSeed@Gen_005BDC70@@QAEXPAVBfmeSeedTarget@@@Z		115 bytes
void Gen_005BDC70::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt60(&m_bfmeItem0);
		target->bfmeTakeAt60(&m_bfmeItem1);
		target->bfmeTakeAt60(&m_bfmeItem2);
		target->bfmeTakeAt60(&m_bfmeItem3);
		target->bfmeTakeAt74(&m_bfmeItem4);
		target->bfmeTakeAt8C(&m_bfmeItem5);
	}
}

// ?bfmeSeed@Gen_005EFA40@@QAEXPAVBfmeSeedTarget@@@Z		97 bytes
void Gen_005EFA40::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		m_bfmeSub0.bfmeAccept(target);
		target->bfmeTakeAt3C(&m_bfmeItem1);
		target->bfmeTakeAt3C(&m_bfmeItem2);
		target->bfmeTakeAt78(&m_bfmeItem3);
	}
}

// ?bfmeSeed@Gen_005FC540@@QAEXPAVBfmeSeedTarget@@@Z		97 bytes
void Gen_005FC540::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		m_bfmeSub2.bfmeAccept(target);
		target->bfmeTakeAt8C(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
		target->bfmeTakeAt8C(&m_bfmeItem3);
	}
}

// ?bfmeSeed@Gen_005FF940@@QAEXPAVBfmeSeedTarget@@@Z		116 bytes
void Gen_005FF940::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt6C(&m_bfmeItem0);
	target->bfmeTakeAt6C(&m_bfmeItem1);
	target->bfmeTakeAt6C(&m_bfmeItem2);
	target->bfmeTakeAt6C(&m_bfmeItem3);
	target->bfmeTakeAt6C(&m_bfmeItem4);
	target->bfmeTakeAt6C(&m_bfmeItem5);
	bfmeHandOver_00044FD0(target, &m_bfmeItem6);
}

// ?bfmeSeed@Gen_006007A0@@QAEXPAVBfmeSeedTarget@@@Z		182 bytes
void Gen_006007A0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt6C(&m_bfmeItem0);
	target->bfmeTakeAt6C(&m_bfmeItem1);
	target->bfmeTakeAt6C(&m_bfmeItem2);
	target->bfmeTakeAt6C(&m_bfmeItem3);
	target->bfmeTakeAt6C(&m_bfmeItem4);
	target->bfmeTakeAt6C(&m_bfmeItem5);
	target->bfmeTakeAt6C(&m_bfmeItem6);
	target->bfmeTakeAt6C(&m_bfmeItem7);
	target->bfmeTakeAt6C(&m_bfmeItem8);
	target->bfmeTakeAt6C(&m_bfmeItem9);
	target->bfmeTakeAt6C(&m_bfmeItem10);
	target->bfmeTakeAt6C(&m_bfmeItem11);
	bfmeHandOver_00044FD0(target, &m_bfmeItem12);
}
