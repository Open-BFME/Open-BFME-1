// cl: /DNDEBUG /MD /EHs-c-

// Open-BFME5: eleven hand-over bodies with MORE THAN ONE version block.
//
// Read by a parser that treats the body as a sequence of CALL-TERMINATED
// GROUPS -- find the next call, then check that the instructions in front of
// it are exactly the set that call needs -- instead of enumerating
// schedulings.  MSVC orders those instructions freely, and in these bodies it
// interleaves two independent version blocks, which is what defeated the
// fixed grammars.
//
// Two facts the shape settles: a second block is homed into the DEAD INCOMING
// ARGUMENT slot rather than new frame space, and when the constant 1 is needed
// four times MSVC parks it in bl for the whole body -- which is why these
// bodies save ebx where the earlier ones do not.
//
// Two siblings of this shape do NOT match and are left as dumps: both put the
// version block itself inside the boolean guard, and the block's scheduling
// inside a branch is not the one this source produces.

struct BfmeVersionBlock
{
	unsigned char m_bfmeKind;
	unsigned char m_bfmeVersion;
};

class BfmeSeedTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual bool bfmeAskAt10(void);		// slot 4, vtable+0x10
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeSeed(BfmeVersionBlock *version);		// slot 10, vtable+0x28
	virtual void bfmeSlot11(void);
	virtual void bfmeTakeAt30(void *held);		// slot 12, vtable+0x30
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
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
	virtual void bfmeTakeAt6C(void *item);		// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
	virtual void bfmeTakeAt78(void *item);		// slot 30, vtable+0x78
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);		// slot 35, vtable+0x8C
};

void bfmeHandOver_00004B79(BfmeSeedTarget *target, void *item);		// ILT 0x00004B79
void bfmeHandOver_0003EE32(BfmeSeedTarget *target, void *item);		// ILT 0x0003EE32

class Gen_0016B710
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
};

class Gen_0016B7C0
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

class Gen_0016B890
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x54
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x58
};

class Gen_0024E710
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00007658

	char m_bfmePad0[0x9BC];
	char m_bfmeItem0;				// +0x9BC
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x9C0
};

class Gen_002BBAE0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	void *m_bfmeHeld2;				// +0x2C
	char m_bfmeItem3;				// +0x30
};

class Gen_002D9BD0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000160B3

	char m_bfmePad0[0x14];
	char m_bfmeItem0;				// +0x14
};

class Gen_005FC640
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0xC];
	char m_bfmeItem0;				// +0x0C
	char m_bfmePad1[0x7];
	char m_bfmeItem1;				// +0x14
	char m_bfmePad2[0x7];
	char m_bfmeItem2;				// +0x1C
};

class Gen_005FD190
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0xC];
	char m_bfmeItem0;				// +0x0C
	char m_bfmePad1[0x7];
	char m_bfmeItem1;				// +0x14
	char m_bfmePad2[0x7];
	char m_bfmeItem2;				// +0x1C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x20
};

class Gen_005FDAC0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x2C
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x30
};

class Gen_005FDBC0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x10];
	char m_bfmeItem0;				// +0x10
};

class Gen_005FE940
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x10];
	char m_bfmeItem0;				// +0x10
};

// ?bfmeSeed@Gen_0016B710@@QAEXPAVBfmeSeedTarget@@@Z		73 bytes
void Gen_0016B710::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version0;

	version0.m_bfmeKind = 1;
	version0.m_bfmeVersion = 1;

	target->bfmeSeed(&version0);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	BfmeVersionBlock version1;

	version1.m_bfmeKind = 1;
	version1.m_bfmeVersion = 1;

	target->bfmeSeed(&version1);
}

// ?bfmeSeed@Gen_0016B7C0@@QAEXPAVBfmeSeedTarget@@@Z		92 bytes
void Gen_0016B7C0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version0;

	version0.m_bfmeKind = 1;
	version0.m_bfmeVersion = 1;

	target->bfmeSeed(&version0);
	BfmeVersionBlock version1;

	version1.m_bfmeKind = 1;
	version1.m_bfmeVersion = 1;

	target->bfmeSeed(&version1);
	bfmeAccept(target);

	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_0016B890@@QAEXPAVBfmeSeedTarget@@@Z		106 bytes
void Gen_0016B890::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version0;

	version0.m_bfmeKind = 1;
	version0.m_bfmeVersion = 1;

	target->bfmeSeed(&version0);
	target->bfmeTakeAt8C(&m_bfmeItem2);
	BfmeVersionBlock version1;

	version1.m_bfmeKind = 1;
	version1.m_bfmeVersion = 1;

	target->bfmeSeed(&version1);
	bfmeAccept(target);

	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_0024E710@@QAEXPAVBfmeSeedTarget@@@Z		89 bytes
void Gen_0024E710::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeAskAt10() )
	{
		BfmeVersionBlock version0;

		version0.m_bfmeKind = 1;
		version0.m_bfmeVersion = 2;

		target->bfmeSeed(&version0);
		if ( version0.m_bfmeVersion >= 2 )
		{
			target->bfmeTakeAt74(&m_bfmeItem0);
			target->bfmeTakeAt68(&m_bfmeItem1);
		}
		bfmeAccept(target);

	}
}

// ?bfmeSeed@Gen_002BBAE0@@QAEXPAVBfmeSeedTarget@@@Z		119 bytes
void Gen_002BBAE0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version0;

	version0.m_bfmeKind = 1;
	version0.m_bfmeVersion = 1;

	target->bfmeSeed(&version0);
	BfmeVersionBlock version1;

	version1.m_bfmeKind = 1;
	version1.m_bfmeVersion = 1;

	target->bfmeSeed(&version1);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	if ( !target->bfmeAskAt10() )
	{
		target->bfmeTakeAt78(&m_bfmeItem3);
		target->bfmeTakeAt30(m_bfmeHeld2);
		bfmeHandOver_00004B79(target, &m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_002D9BD0@@QAEXPAVBfmeSeedTarget@@@Z		81 bytes
void Gen_002D9BD0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version0;

	version0.m_bfmeKind = 1;
	version0.m_bfmeVersion = 1;

	target->bfmeSeed(&version0);
	bfmeAccept(target);

	BfmeVersionBlock version1;

	version1.m_bfmeKind = 1;
	version1.m_bfmeVersion = 1;

	target->bfmeSeed(&version1);
	target->bfmeTakeAt8C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_005FC640@@QAEXPAVBfmeSeedTarget@@@Z		116 bytes
void Gen_005FC640::bfmeSeed(BfmeSeedTarget *target)
{
	if ( !target->bfmeAskAt10() )
	{
		BfmeVersionBlock version0;

		version0.m_bfmeKind = 1;
		version0.m_bfmeVersion = 2;

		target->bfmeSeed(&version0);
		BfmeVersionBlock version1;

		version1.m_bfmeKind = 1;
		version1.m_bfmeVersion = 1;

		target->bfmeSeed(&version1);
		target->bfmeTakeAt74(&m_bfmeItem1);
		target->bfmeTakeAt8C(&m_bfmeItem0);
		if ( version0.m_bfmeVersion >= 2 )
		{
			target->bfmeTakeAt8C(&m_bfmeItem2);
		}
	}
}

// ?bfmeSeed@Gen_005FD190@@QAEXPAVBfmeSeedTarget@@@Z		119 bytes
void Gen_005FD190::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version0;

	version0.m_bfmeKind = 1;
	version0.m_bfmeVersion = 2;

	target->bfmeSeed(&version0);
	BfmeVersionBlock version1;

	version1.m_bfmeKind = 1;
	version1.m_bfmeVersion = 1;

	target->bfmeSeed(&version1);
	target->bfmeTakeAt6C(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	if ( version0.m_bfmeVersion >= 2 )
	{
		target->bfmeTakeAt8C(&m_bfmeItem3);
	}
}

// ?bfmeSeed@Gen_005FDAC0@@QAEXPAVBfmeSeedTarget@@@Z		94 bytes
void Gen_005FDAC0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version0;

	version0.m_bfmeKind = 1;
	version0.m_bfmeVersion = 1;

	target->bfmeSeed(&version0);
	BfmeVersionBlock version1;

	version1.m_bfmeKind = 1;
	version1.m_bfmeVersion = 1;

	target->bfmeSeed(&version1);
	target->bfmeTakeAt6C(&m_bfmeItem1);
	target->bfmeTakeAt60(&m_bfmeItem0);
	bfmeHandOver_0003EE32(target, &m_bfmeItem2);
}

// ?bfmeSeed@Gen_005FDBC0@@QAEXPAVBfmeSeedTarget@@@Z		70 bytes
void Gen_005FDBC0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version0;

	version0.m_bfmeKind = 1;
	version0.m_bfmeVersion = 1;

	target->bfmeSeed(&version0);
	BfmeVersionBlock version1;

	version1.m_bfmeKind = 1;
	version1.m_bfmeVersion = 1;

	target->bfmeSeed(&version1);
	target->bfmeTakeAt6C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_005FE940@@QAEXPAVBfmeSeedTarget@@@Z		70 bytes
void Gen_005FE940::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeVersionBlock version0;

	version0.m_bfmeKind = 1;
	version0.m_bfmeVersion = 1;

	target->bfmeSeed(&version0);
	BfmeVersionBlock version1;

	version1.m_bfmeKind = 1;
	version1.m_bfmeVersion = 1;

	target->bfmeSeed(&version1);
	target->bfmeTakeAt6C(&m_bfmeItem0);
}
