// Six more bodies in two shapes, both filling a two-byte pair on the stack
// and handing its address to virtual slot ten of the argument.
//
// 0x0020CDE0, 0x00282EA0 and 0x0028A260 seed the pair with two DIFFERENT
// values, one and two, so each byte gets its own immediate store rather than
// sharing a single mov al,1. Afterwards they re-read the second byte and
// compare it unsigned -- jb, not jl -- so it is an unsigned char, and only
// then call a member of their own class with the argument.
//
// 0x0015BBD0, 0x00189FF0 and 0x002BBFC0 seed both bytes from one mov al,1 and
// then make two more virtual calls, at vtable+0x74 and vtable+0x60, handing
// over the sub-objects at this+0x24 and this+0x28. The last of the three is
// formed with add edi,0x28 rather than a lea, because edi is dead afterwards.

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
	virtual void bfmeTakeLater(void *item);			// slot 24, vtable+0x60
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeSlot27(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeEarly(void *item);			// slot 29, vtable+0x74
};

struct BfmeSubObject
{
	char m_bfmeBytes[4];
};


class Gen_0020CDE0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1
};

class Gen_00282EA0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1
};

class Gen_0028A260
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1
};

class Gen_0015BBD0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x24];
	BfmeSubObject m_bfmeEarly;				// +0x24
	BfmeSubObject m_bfmeLater;				// +0x28
};

class Gen_00189FF0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x24];
	BfmeSubObject m_bfmeEarly;				// +0x24
	BfmeSubObject m_bfmeLater;				// +0x28
};

class Gen_002BBFC0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x24];
	BfmeSubObject m_bfmeEarly;				// +0x24
	BfmeSubObject m_bfmeLater;				// +0x28
};

// ?bfmeSeed@Gen_0020CDE0@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0020CDE0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 2;

	target->bfmeSeed(&pair);

	if (pair.m_bfmeSecond >= 2)
		bfmeAccept(target);
}

// ?bfmeSeed@Gen_00282EA0@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_00282EA0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 2;

	target->bfmeSeed(&pair);

	if (pair.m_bfmeSecond >= 2)
		bfmeAccept(target);
}

// ?bfmeSeed@Gen_0028A260@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0028A260::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 2;

	target->bfmeSeed(&pair);

	if (pair.m_bfmeSecond >= 2)
		bfmeAccept(target);
}

// ?bfmeSeed@Gen_0015BBD0@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0015BBD0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeEarly(&m_bfmeEarly);
	target->bfmeTakeLater(&m_bfmeLater);
}

// ?bfmeSeed@Gen_00189FF0@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_00189FF0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeEarly(&m_bfmeEarly);
	target->bfmeTakeLater(&m_bfmeLater);
}

// ?bfmeSeed@Gen_002BBFC0@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_002BBFC0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeEarly(&m_bfmeEarly);
	target->bfmeTakeLater(&m_bfmeLater);
}
