// cl: /DNDEBUG /MD /EHs-c-

// Open-BFME5: forty-nine more stack-pair seeders, found by scanning every
// remaining gen_asm dump for the family signature rather than by grouping
// bytes -- the members and slot numbers differ per body, so no byte bucket
// ever collects them, but the prologue, the pair and the epilogue are
// identical in all forty-nine.
//
// The body is always the same three-part shape: seed a two-byte pair from one
// `mov al,1`, hand its address to slot ten of the target, then run a sequence
// of hand-overs -- either a member of the seeder's own class taking the target
// (a direct call through an ILT slot), or a virtual on the target carrying the
// address of one of the seeder's sub-objects.
//
// The pair lives in the four bytes the prologue's `push ecx` reserves, and its
// address is taken BEFORE the two stores, which is what puts `lea ecx,[esp+8]`
// between the `mov al,1` and the first `mov byte ptr [esp+8],al`.
//
// Sub-object offsets are read straight off each `lea eax,[edi+OFF]`; the LAST
// one in a body comes out as `add edi,OFF` instead, because that is the point
// where `this` is dead.  That is the compiler's choice, not the source's, so
// the offsets below are declared plainly and the shape falls out.

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
	virtual void bfmeSlot4(void);
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
	virtual void bfmeTakeAt68(void *item);		// slot 26, vtable+0x68
	virtual void bfmeTakeAt6C(void *item);		// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
	virtual void bfmeTakeAt78(void *item);		// slot 30, vtable+0x78
	virtual void bfmeTakeAt7C(void *item);		// slot 31, vtable+0x7C
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);		// slot 35, vtable+0x8C
};

class Gen_000EC810
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x9C];
	char m_bfmeItem0;				// +0x9C
};

class Gen_0016B0B0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x1];
	char m_bfmeItem1;				// +0x26
	char m_bfmeItem2;				// +0x27
};

class Gen_0016B320
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

class Gen_0016C040
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x2B];
	char m_bfmeItem1;				// +0x50
};

class Gen_0016C300
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmePad0[0x50];
	char m_bfmeItem0;				// +0x50
};

class Gen_0016C790
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00033BF4

	char m_bfmePad0[0x6C];
	char m_bfmeItem0;				// +0x6C
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x70
};

class Gen_0016C860
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00033BF4

	char m_bfmePad0[0x6C];
	char m_bfmeItem0;				// +0x6C
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x70
};

class Gen_0016C8C0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x25];
	char m_bfmeItem0;				// +0x25
	char m_bfmeItem1;				// +0x26
	char m_bfmeItem2;				// +0x27
};

class Gen_0016E060
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x2C
};

class Gen_0016E0C0
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
	char m_bfmeItem3;				// +0x59
};

class Gen_00189E40
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x2C];
	char m_bfmeItem0;				// +0x2C
};

class Gen_001ED5F0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_001F6900
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmeItem1;				// +0x21
};

class Gen_001F7A70
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

class Gen_001FADA0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_00200380
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

class Gen_00203DF0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x28
};

class Gen_00212790
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000160B3

	char m_bfmePad0[0x14];
	char m_bfmeItem0;				// +0x14
};

class Gen_00212B40
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00017A49

	char m_bfmePad0[0xE0];
	char m_bfmeItem0;				// +0xE0
	char m_bfmeItem1;				// +0xE1
};

class Gen_00213440
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00017A49

	char m_bfmePad0[0xE0];
	char m_bfmeItem0;				// +0xE0
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0xE4
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0xE8
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0xEC
	char m_bfmePad4[0x3];
	char m_bfmeItem4;				// +0xF0
};

class Gen_0022A170
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00016027

	char m_bfmePad0[0x100];
	char m_bfmeItem0;				// +0x100
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x104
};

class Gen_0022CD40
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000489DC

	char m_bfmePad0[0xD8];
	char m_bfmeItem0;				// +0xD8
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0xDC
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0xE0
};

class Gen_0024B870
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0003D37A

	char m_bfmePad0[0xE4];
	char m_bfmeItem0;				// +0xE4
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0xE8
};

class Gen_0025D0E0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000289F7

	char m_bfmePad0[0xE8];
	char m_bfmeItem0;				// +0xE8
};

class Gen_0026A980
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
};

class Gen_0026C210
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000289F7

	char m_bfmePad0[0xE8];
	char m_bfmeItem0;				// +0xE8
};

class Gen_002815B0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_0028C760
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_0028C980
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

class Gen_0028D3C0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmeItem1;				// +0x21
};

class Gen_00291DC0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x28
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x2C
	char m_bfmeItem4;				// +0x2D
	char m_bfmeItem5;				// +0x2E
	char m_bfmeItem6;				// +0x2F
	char m_bfmeItem7;				// +0x30
};

class Gen_0029FFA0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_002B62D0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x2C
};

class Gen_002BBA50
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
};

class Gen_002BF000
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem0;				// +0x24
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x28
};

class Gen_002D5740
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000183FE

	char m_bfmePad0[0x1C];
	char m_bfmeItem0;				// +0x1C
};

class Gen_002D9B90
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
};

class Gen_00422C80
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x54];
	char m_bfmeItem0;				// +0x54
};

class Gen_005F8670
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
};

class Gen_005F9380
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x28
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x2C
};

class Gen_005F9890
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
	char m_bfmePad2[0xB];
	char m_bfmeItem2;				// +0x30
};

class Gen_005FA3C0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
};

class Gen_005FA8D0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x24
};

class Gen_005FD140
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
	char m_bfmePad1[0x7];
	char m_bfmeItem1;				// +0x0C
};

class Gen_005FE8E0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x4];
	char m_bfmeItem0;				// +0x04
};

class Gen_00756C80
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0002FD88

	char m_bfmePad0[0x20];
	char m_bfmeItem0;				// +0x20
	char m_bfmePad1[0x7];
	char m_bfmeItem1;				// +0x28
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x2C
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x30
};

class Gen_00758670
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0002FD88

	char m_bfmePad0[0x10];
	char m_bfmeItem0;				// +0x10
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x14
	char m_bfmePad2[0x3];
	char m_bfmeItem2;				// +0x18
	char m_bfmePad3[0x3];
	char m_bfmeItem3;				// +0x1C
};

class Gen_00759230
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0001E853

	char m_bfmePad0[0x3F0];
	char m_bfmeItem0;				// +0x3F0
};

class Gen_0077DCF0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00011CBB

	char m_bfmePad0[0x27C];
	char m_bfmeItem0;				// +0x27C
	char m_bfmePad1[0x3];
	char m_bfmeItem1;				// +0x280
};

// ?bfmeSeed@Gen_000EC810@@QAEXPAVBfmeSeedTarget@@@Z		51 bytes
void Gen_000EC810::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt78(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_0016B0B0@@QAEXPAVBfmeSeedTarget@@@Z		76 bytes
void Gen_0016B0B0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt7C(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_0016B320@@QAEXPAVBfmeSeedTarget@@@Z		70 bytes
void Gen_0016B320::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_0016C040@@QAEXPAVBfmeSeedTarget@@@Z		67 bytes
void Gen_0016C040::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem1);
	target->bfmeTakeAt60(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_0016C300@@QAEXPAVBfmeSeedTarget@@@Z		56 bytes
void Gen_0016C300::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt60(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_0016C790@@QAEXPAVBfmeSeedTarget@@@Z		67 bytes
void Gen_0016C790::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_0016C860@@QAEXPAVBfmeSeedTarget@@@Z		67 bytes
void Gen_0016C860::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_0016C8C0@@QAEXPAVBfmeSeedTarget@@@Z		79 bytes
void Gen_0016C8C0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_0016E060@@QAEXPAVBfmeSeedTarget@@@Z		73 bytes
void Gen_0016E060::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt74(&m_bfmeItem1);
	target->bfmeTakeAt74(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_0016E0C0@@QAEXPAVBfmeSeedTarget@@@Z		98 bytes
void Gen_0016E0C0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem3);
	target->bfmeTakeAt8C(&m_bfmeItem2);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
	bfmeAccept(target);
}

// ?bfmeSeed@Gen_00189E40@@QAEXPAVBfmeSeedTarget@@@Z		51 bytes
void Gen_00189E40::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_001ED5F0@@QAEXPAVBfmeSeedTarget@@@Z		56 bytes
void Gen_001ED5F0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt68(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_001F6900@@QAEXPAVBfmeSeedTarget@@@Z		73 bytes
void Gen_001F6900::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_001F7A70@@QAEXPAVBfmeSeedTarget@@@Z		67 bytes
void Gen_001F7A70::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_001FADA0@@QAEXPAVBfmeSeedTarget@@@Z		56 bytes
void Gen_001FADA0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt6C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_00200380@@QAEXPAVBfmeSeedTarget@@@Z		67 bytes
void Gen_00200380::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt6C(&m_bfmeItem1);
	target->bfmeTakeAt78(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_00203DF0@@QAEXPAVBfmeSeedTarget@@@Z		78 bytes
void Gen_00203DF0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt6C(&m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
	target->bfmeTakeAt78(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_00212790@@QAEXPAVBfmeSeedTarget@@@Z		56 bytes
void Gen_00212790::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt6C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_00212B40@@QAEXPAVBfmeSeedTarget@@@Z		79 bytes
void Gen_00212B40::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
	bfmeAccept(target);
}

// ?bfmeSeed@Gen_00213440@@QAEXPAVBfmeSeedTarget@@@Z		121 bytes
void Gen_00213440::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt6C(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
	target->bfmeTakeAt74(&m_bfmeItem3);
	target->bfmeTakeAt74(&m_bfmeItem4);
	bfmeAccept(target);
}

// ?bfmeSeed@Gen_0022A170@@QAEXPAVBfmeSeedTarget@@@Z		73 bytes
void Gen_0022A170::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt74(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_0022CD40@@QAEXPAVBfmeSeedTarget@@@Z		90 bytes
void Gen_0022CD40::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt74(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_0024B870@@QAEXPAVBfmeSeedTarget@@@Z		76 bytes
void Gen_0024B870::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_0025D0E0@@QAEXPAVBfmeSeedTarget@@@Z		62 bytes
void Gen_0025D0E0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_0026A980@@QAEXPAVBfmeSeedTarget@@@Z		89 bytes
void Gen_0026A980::bfmeSeed(BfmeSeedTarget *target)
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
}

// ?bfmeSeed@Gen_0026C210@@QAEXPAVBfmeSeedTarget@@@Z		59 bytes
void Gen_0026C210::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt74(&m_bfmeItem0);
	bfmeAccept(target);
}

// ?bfmeSeed@Gen_002815B0@@QAEXPAVBfmeSeedTarget@@@Z		56 bytes
void Gen_002815B0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_0028C760@@QAEXPAVBfmeSeedTarget@@@Z		56 bytes
void Gen_0028C760::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt74(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_0028C980@@QAEXPAVBfmeSeedTarget@@@Z		70 bytes
void Gen_0028C980::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_0028D3C0@@QAEXPAVBfmeSeedTarget@@@Z		73 bytes
void Gen_0028D3C0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_00291DC0@@QAEXPAVBfmeSeedTarget@@@Z		148 bytes
void Gen_00291DC0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt74(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem3);
	target->bfmeTakeAt74(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem6);
	target->bfmeTakeAt8C(&m_bfmeItem4);
	target->bfmeTakeAt8C(&m_bfmeItem7);
	target->bfmeTakeAt74(&m_bfmeItem2);
	target->bfmeTakeAt8C(&m_bfmeItem5);
}

// ?bfmeSeed@Gen_0029FFA0@@QAEXPAVBfmeSeedTarget@@@Z		56 bytes
void Gen_0029FFA0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_002B62D0@@QAEXPAVBfmeSeedTarget@@@Z		73 bytes
void Gen_002B62D0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt74(&m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
	target->bfmeTakeAt8C(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_002BBA50@@QAEXPAVBfmeSeedTarget@@@Z		51 bytes
void Gen_002BBA50::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_002BF000@@QAEXPAVBfmeSeedTarget@@@Z		62 bytes
void Gen_002BF000::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_002D5740@@QAEXPAVBfmeSeedTarget@@@Z		56 bytes
void Gen_002D5740::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt68(&m_bfmeItem0);
	bfmeAccept(target);
}

// ?bfmeSeed@Gen_002D9B90@@QAEXPAVBfmeSeedTarget@@@Z		51 bytes
void Gen_002D9B90::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_00422C80@@QAEXPAVBfmeSeedTarget@@@Z		51 bytes
void Gen_00422C80::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_005F8670@@QAEXPAVBfmeSeedTarget@@@Z		62 bytes
void Gen_005F8670::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt60(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_005F9380@@QAEXPAVBfmeSeedTarget@@@Z		84 bytes
void Gen_005F9380::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt6C(&m_bfmeItem1);
	target->bfmeTakeAt6C(&m_bfmeItem2);
	target->bfmeTakeAt60(&m_bfmeItem3);
}

// ?bfmeSeed@Gen_005F9890@@QAEXPAVBfmeSeedTarget@@@Z		73 bytes
void Gen_005F9890::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt60(&m_bfmeItem1);
	target->bfmeTakeAt60(&m_bfmeItem2);
}

// ?bfmeSeed@Gen_005FA3C0@@QAEXPAVBfmeSeedTarget@@@Z		51 bytes
void Gen_005FA3C0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_005FA8D0@@QAEXPAVBfmeSeedTarget@@@Z		62 bytes
void Gen_005FA8D0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem0);
	target->bfmeTakeAt6C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_005FD140@@QAEXPAVBfmeSeedTarget@@@Z		62 bytes
void Gen_005FD140::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt6C(&m_bfmeItem0);
	target->bfmeTakeAt8C(&m_bfmeItem1);
}

// ?bfmeSeed@Gen_005FE8E0@@QAEXPAVBfmeSeedTarget@@@Z		48 bytes
void Gen_005FE8E0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt6C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_00756C80@@QAEXPAVBfmeSeedTarget@@@Z		89 bytes
void Gen_00756C80::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt6C(&m_bfmeItem2);
	target->bfmeTakeAt6C(&m_bfmeItem3);
	target->bfmeTakeAt78(&m_bfmeItem1);
	target->bfmeTakeAt6C(&m_bfmeItem0);
}

// ?bfmeSeed@Gen_00758670@@QAEXPAVBfmeSeedTarget@@@Z		89 bytes
void Gen_00758670::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt6C(&m_bfmeItem0);
	target->bfmeTakeAt6C(&m_bfmeItem1);
	target->bfmeTakeAt6C(&m_bfmeItem2);
	target->bfmeTakeAt6C(&m_bfmeItem3);
	bfmeAccept(target);
}

// ?bfmeSeed@Gen_00759230@@QAEXPAVBfmeSeedTarget@@@Z		59 bytes
void Gen_00759230::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt6C(&m_bfmeItem0);
	bfmeAccept(target);
}

// ?bfmeSeed@Gen_0077DCF0@@QAEXPAVBfmeSeedTarget@@@Z		73 bytes
void Gen_0077DCF0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt78(&m_bfmeItem0);
	target->bfmeTakeAt78(&m_bfmeItem1);
	bfmeAccept(target);
}
