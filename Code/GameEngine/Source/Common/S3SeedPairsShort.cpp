// Four short stack-pair seeders: 0x000C8830, 0x0015BB80, 0x0015E860 and
// 0x0018CC20.
//
// The narrowest member of the family: fill the two-byte pair from one mov al,1,
// hand its address to virtual slot ten, then make exactly ONE further virtual
// call. Because that call is the last use of this, the sub-object address is
// formed with add edi rather than a lea -- the same tail the longer seeders end
// with.

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
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeTakeAt6C(void *item);		// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
	virtual void bfmeTakeAt78(void *item);		// slot 30, vtable+0x78
};

struct BfmeSubObject
{
	char m_bfmeBytes[4];
};


class Gen_000C8830
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x04];
	BfmeSubObject m_bfmeItem;				// +0x04
};

class Gen_0015BB80
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x50];
	BfmeSubObject m_bfmeItem;				// +0x50
};

class Gen_0015E860
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x50];
	BfmeSubObject m_bfmeItem;				// +0x50
};

class Gen_0018CC20
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x24];
	BfmeSubObject m_bfmeItem;				// +0x24
};

// ?bfmeSeed@Gen_000C8830@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_000C8830::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt74(&m_bfmeItem);
}

// ?bfmeSeed@Gen_0015BB80@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0015BB80::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt74(&m_bfmeItem);
}

// ?bfmeSeed@Gen_0015E860@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0015E860::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt74(&m_bfmeItem);
}

// ?bfmeSeed@Gen_0018CC20@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0018CC20::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt6C(&m_bfmeItem);
}
