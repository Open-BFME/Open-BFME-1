// cl: /DNDEBUG /MD /EHs-c-

// Open-BFME5: twenty-four more stack-pair seeders -- the two shapes the first
// sweep's grammar could not read.
//
// Shape one puts the ILT member call BEFORE the pair instead of after, and
// therefore needs no `push ecx`: the pair lands in the outgoing argument space
// that call already reserved, at [esp+0xc] rather than [esp+8].
//
// Shape two wraps everything after the member call in a guard -- slot four of
// the target answers a byte and a `jne` straight to the epilogue skips the
// rest.  Inside the guard MSVC schedules the pair differently: the target's
// vtable is loaded FIRST and the pair's address taken AFTER the two stores,
// where the unguarded form takes the address before them.  That is scheduling,
// not source -- the guarded and unguarded bodies here are written identically
// apart from the `if`.

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
	virtual void bfmeSlot9(void);
	virtual void bfmeSeed(BfmeSeedPair *pair);		// slot 10, vtable+0x28
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
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
	virtual void bfmeSlot26(void);
	virtual void bfmeTakeAt6C(void *item);		// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
	virtual void bfmeTakeAt78(void *item);		// slot 30, vtable+0x78
	virtual void bfmeSlot31(void);
	virtual void bfmeTakeAt80(void *item);		// slot 32, vtable+0x80
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);		// slot 35, vtable+0x8C
};

class Gen_0014F150
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00022363

	char m_bfmePad0[0x44];
	char m_bfmeItem0;				// +0x44
};

class Gen_00168910
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0004B53D

	char m_bfmePad0[0x78];
	char m_bfmeItem0;				// +0x78
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x7C
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x80
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x84
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x88
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x8C
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x90
	char m_bfmePad7[0x3];
	char m_bfmeItem7;				// +0x94
};

class Gen_00189FA0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0001C3FA

	char m_bfmePad0[0x54];
	char m_bfmeItem0;				// +0x54
};

class Gen_002077D0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x28];
	char m_bfmeItem0;				// +0x28
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x2C
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x30
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x34
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x38
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x3C
	char m_bfmePad6[0x3];
	char m_bfmeItem6;				// +0x40
	char m_bfmePad7[0x7];
	char m_bfmeItem7;				// +0x48
	char m_bfmePad8[0x3];
	char m_bfmeItem8;				// +0x4C
};

class Gen_0020D890
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
};

class Gen_0022F410
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000489DC

	char m_bfmePad0[0xD4];
	char m_bfmeItem0;				// +0xD4
	char m_bfmeItem1;				// +0xD5
};

class Gen_0024F500
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000160B3

	char m_bfmePad0[0x14];
	char m_bfmeItem0;				// +0x14
};

class Gen_00256360
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00003AEE

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x28
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x2C
};

class Gen_0025A590
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00033B77

	char m_bfmePad0[0x3C];
	char m_bfmeItem0;				// +0x3C
	char m_bfmeItem1;				// +0x3D
};

class Gen_0025DA40
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000289F7

	char m_bfmePad0[0xE8];
	char m_bfmeItem0;				// +0xE8
	char m_bfmeItem1;				// +0xE9
	char m_bfmePad2[0x2];
	char m_bfmeItem2;				// +0xEC
};

class Gen_0026E160
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000289F7

	char m_bfmePad0[0xE8];
	char m_bfmeItem0;				// +0xE8
};

class Gen_00280CF0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
	char m_bfmeItem2;				// +0x25
};

class Gen_0028B8A0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmeItem1;				// +0x25
};

class Gen_0028EAD0
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
	char m_bfmePad8[0x3];
	char m_bfmeItem8;				// +0x44
	char m_bfmePad9[0x3];
	char m_bfmeItem9;				// +0x48
	char m_bfmePad10[0x3];
	char m_bfmeItem10;				// +0x4C
};

class Gen_002956A0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmeItem1;				// +0x21
	char m_bfmePad2[0x2];
	char m_bfmeItem2;				// +0x24
	char m_bfmePad3[0xB];
	char m_bfmeItem3;				// +0x30
};

class Gen_00297F70
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

class Gen_00298AE0
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

class Gen_00299B60
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_002A0320
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
	char m_bfmeItem2;				// +0x25
};

class Gen_002A0B40
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
};

class Gen_002CDC70
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0001D043

	char m_bfmePad0[0x88];
	char m_bfmeItem0;				// +0x88
	char m_bfmeItem1;				// +0x89
	char m_bfmePad2[0x2];
	char m_bfmeItem2;				// +0x8C
};

class Gen_002CFFD0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x30
};

class Gen_002D2580
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0xB];
	char m_bfmeItem1;				// +0x30
};

class Gen_00604760
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0003D2A8

	char m_bfmePad0[0xC];
	char m_bfmeItem0;				// +0x0C
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x10
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x14
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x18
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0x1C
	char m_bfmePad5[0x3];
	char m_bfmeItem5;				// +0x20
	char m_bfmePad6[0x1];
	char m_bfmeItem6;				// +0x22
	char m_bfmePad7[0x1];
	char m_bfmeItem7;				// +0x24
	char m_bfmePad8[0x3];
	char m_bfmeItem8;				// +0x28
};

// ?bfmeSeed@Gen_0014F150@@QAEXPAVBfmeSeedTarget@@@Z		52 bytes
void Gen_0014F150::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt78(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_00168910@@QAEXPAVBfmeSeedTarget@@@Z		162 bytes
void Gen_00168910::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt78(&m_bfmeItem0);
		target->bfmeTakeAt78(&m_bfmeItem1);
		target->bfmeTakeAt6C(&m_bfmeItem2);
		target->bfmeTakeAt6C(&m_bfmeItem3);
		target->bfmeTakeAt6C(&m_bfmeItem4);
		target->bfmeTakeAt6C(&m_bfmeItem5);
		target->bfmeTakeAt6C(&m_bfmeItem6);
		target->bfmeTakeAt6C(&m_bfmeItem7);
	}
}

// ?bfmeSeed@Gen_00189FA0@@QAEXPAVBfmeSeedTarget@@@Z		63 bytes
void Gen_00189FA0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_002077D0@@QAEXPAVBfmeSeedTarget@@@Z		157 bytes
void Gen_002077D0::bfmeSeed(BfmeSeedTarget *target)
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
		target->bfmeTakeAt74(&m_bfmeItem2);
		target->bfmeTakeAt74(&m_bfmeItem3);
		target->bfmeTakeAt6C(&m_bfmeItem4);
		target->bfmeTakeAt74(&m_bfmeItem5);
		target->bfmeTakeAt8C(&m_bfmeItem7);
		target->bfmeTakeAt74(&m_bfmeItem8);
		target->bfmeTakeAt8C(&m_bfmeItem6);
	}
}

// ?bfmeSeed@Gen_0020D890@@QAEXPAVBfmeSeedTarget@@@Z		74 bytes
void Gen_0020D890::bfmeSeed(BfmeSeedTarget *target)
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
	}
}

// ?bfmeSeed@Gen_0022F410@@QAEXPAVBfmeSeedTarget@@@Z		86 bytes
void Gen_0022F410::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt8C(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_0024F500@@QAEXPAVBfmeSeedTarget@@@Z		66 bytes
void Gen_0024F500::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt8C(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_00256360@@QAEXPAVBfmeSeedTarget@@@Z		99 bytes
void Gen_00256360::bfmeSeed(BfmeSeedTarget *target)
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
		target->bfmeTakeAt8C(&m_bfmeItem3);
	}
}

// ?bfmeSeed@Gen_0025A590@@QAEXPAVBfmeSeedTarget@@@Z		80 bytes
void Gen_0025A590::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt8C(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_0025DA40@@QAEXPAVBfmeSeedTarget@@@Z		100 bytes
void Gen_0025DA40::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt8C(&m_bfmeItem0);
		target->bfmeTakeAt6C(&m_bfmeItem2);
		target->bfmeTakeAt8C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_0026E160@@QAEXPAVBfmeSeedTarget@@@Z		69 bytes
void Gen_0026E160::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt8C(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_00280CF0@@QAEXPAVBfmeSeedTarget@@@Z		91 bytes
void Gen_00280CF0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
		target->bfmeTakeAt8C(&m_bfmeItem2);
	}
}

// ?bfmeSeed@Gen_0028B8A0@@QAEXPAVBfmeSeedTarget@@@Z		80 bytes
void Gen_0028B8A0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt8C(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_0028EAD0@@QAEXPAVBfmeSeedTarget@@@Z		180 bytes
void Gen_0028EAD0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt78(&m_bfmeItem0);
		target->bfmeTakeAt78(&m_bfmeItem1);
		target->bfmeTakeAt74(&m_bfmeItem2);
		target->bfmeTakeAt74(&m_bfmeItem3);
		target->bfmeTakeAt74(&m_bfmeItem4);
		target->bfmeTakeAt74(&m_bfmeItem5);
		target->bfmeTakeAt74(&m_bfmeItem6);
		target->bfmeTakeAt8C(&m_bfmeItem7);
		target->bfmeTakeAt6C(&m_bfmeItem8);
		target->bfmeTakeAt6C(&m_bfmeItem9);
		target->bfmeTakeAt6C(&m_bfmeItem10);
	}
}

// ?bfmeSeed@Gen_002956A0@@QAEXPAVBfmeSeedTarget@@@Z		102 bytes
void Gen_002956A0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt8C(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
		target->bfmeTakeAt60(&m_bfmeItem2);
		target->bfmeTakeAt74(&m_bfmeItem3);
	}
}

// ?bfmeSeed@Gen_00297F70@@QAEXPAVBfmeSeedTarget@@@Z		74 bytes
void Gen_00297F70::bfmeSeed(BfmeSeedTarget *target)
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
	}
}

// ?bfmeSeed@Gen_00298AE0@@QAEXPAVBfmeSeedTarget@@@Z		74 bytes
void Gen_00298AE0::bfmeSeed(BfmeSeedTarget *target)
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
	}
}

// ?bfmeSeed@Gen_00299B60@@QAEXPAVBfmeSeedTarget@@@Z		63 bytes
void Gen_00299B60::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
	}
}

// ?bfmeSeed@Gen_002A0320@@QAEXPAVBfmeSeedTarget@@@Z		91 bytes
void Gen_002A0320::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
		target->bfmeTakeAt8C(&m_bfmeItem2);
	}
}

// ?bfmeSeed@Gen_002A0B40@@QAEXPAVBfmeSeedTarget@@@Z		107 bytes
void Gen_002A0B40::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt74(&m_bfmeItem0);
		target->bfmeTakeAt6C(&m_bfmeItem1);
		target->bfmeTakeAt6C(&m_bfmeItem2);
		target->bfmeTakeAt6C(&m_bfmeItem3);
		target->bfmeTakeAt6C(&m_bfmeItem4);
	}
}

// ?bfmeSeed@Gen_002CDC70@@QAEXPAVBfmeSeedTarget@@@Z		100 bytes
void Gen_002CDC70::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		target->bfmeTakeAt8C(&m_bfmeItem0);
		target->bfmeTakeAt78(&m_bfmeItem2);
		target->bfmeTakeAt8C(&m_bfmeItem1);
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
	}
}

// ?bfmeSeed@Gen_002CFFD0@@QAEXPAVBfmeSeedTarget@@@Z		77 bytes
void Gen_002CFFD0::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt60(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_002D2580@@QAEXPAVBfmeSeedTarget@@@Z		77 bytes
void Gen_002D2580::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
	{
		BfmeSeedPair pair;

		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 1;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt60(&m_bfmeItem0);
		target->bfmeTakeAt8C(&m_bfmeItem1);
	}
}

// ?bfmeSeed@Gen_00604760@@QAEXPAVBfmeSeedTarget@@@Z		157 bytes
void Gen_00604760::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	if ( !target->bfmeSkip() )
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
		target->bfmeTakeAt80(&m_bfmeItem5);
		target->bfmeTakeAt8C(&m_bfmeItem6);
		target->bfmeTakeAt6C(&m_bfmeItem7);
		target->bfmeTakeAt6C(&m_bfmeItem8);
	}
}
