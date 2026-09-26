// Ten more stack-pair seeders.
//
// Eight of them -- 0x00295430, 0x002AB430, 0x002D84E0, 0x00213EA0, 0x002B2CA0,
// 0x0016C430, 0x0016E140 and 0x002CF710 -- seed the pair, hand the target to a
// member of their own class, and finish with one virtual call carrying a
// sub-object. Two more, 0x004095A0 and 0x002BBF70, skip the member call and
// make two virtual calls instead.
//
// In every one the LAST sub-object address is formed with add edi and any
// earlier one with a lea, because the add can only be used once this is dead.

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
	virtual void bfmeSlot26(void);
	virtual void bfmeSlot27(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
	virtual void bfmeTakeAt78(void *item);		// slot 30, vtable+0x78
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);		// slot 35, vtable+0x8C
};

struct BfmeSubObject
{
	char m_bfmeBytes[4];
};


class Gen_00295430
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmeHead[0x20];
	BfmeSubObject m_bfmeItem;				// +0x20
};

class Gen_002AB430
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000044C1

	char m_bfmeHead[0x20];
	BfmeSubObject m_bfmeItem;				// +0x20
};

class Gen_002D84E0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x000183FE

	char m_bfmeHead[0x20];
	BfmeSubObject m_bfmeItem;				// +0x20
};

class Gen_00213EA0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0003BC7D

	char m_bfmeHead[0x18];
	BfmeSubObject m_bfmeItem;				// +0x18
};

class Gen_002B2CA0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00033B77

	char m_bfmeHead[0x38];
	BfmeSubObject m_bfmeItem;				// +0x38
};

class Gen_0016C430
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmeHead[0x50];
	BfmeSubObject m_bfmeItem;				// +0x50
};

class Gen_0016E140
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x00002379

	char m_bfmeHead[0x50];
	BfmeSubObject m_bfmeItem;				// +0x50
};

class Gen_002CF710
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	void bfmeAccept(BfmeSeedTarget *target);		// ILT 0x0001D043

	char m_bfmeHead[0x88];
	BfmeSubObject m_bfmeItem;				// +0x88
};

class Gen_004095A0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x0C];
	BfmeSubObject m_bfmeFirstItem;				// +0x0C
	BfmeSubObject m_bfmeSecondItem;				// +0x10
};

class Gen_002BBF70
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x28];
	BfmeSubObject m_bfmeFirstItem;				// +0x28
	BfmeSubObject m_bfmeSecondItem;				// +0x2C
};

// ?bfmeSeed@Gen_00295430@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_00295430::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem);
}

// ?bfmeSeed@Gen_002AB430@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_002AB430::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem);
}

// ?bfmeSeed@Gen_002D84E0@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_002D84E0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt8C(&m_bfmeItem);
	bfmeAccept(target);
}

// ?bfmeSeed@Gen_00213EA0@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_00213EA0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem);
}

// ?bfmeSeed@Gen_002B2CA0@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_002B2CA0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem);
}

// ?bfmeSeed@Gen_0016C430@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0016C430::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem);
}

// ?bfmeSeed@Gen_0016E140@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0016E140::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt8C(&m_bfmeItem);
}

// ?bfmeSeed@Gen_002CF710@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_002CF710::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->bfmeTakeAt78(&m_bfmeItem);
}

// ?bfmeSeed@Gen_004095A0@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_004095A0::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt74(&m_bfmeFirstItem);
	target->bfmeTakeAt74(&m_bfmeSecondItem);
}

// ?bfmeSeed@Gen_002BBF70@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_002BBF70::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt74(&m_bfmeFirstItem);
	target->bfmeTakeAt60(&m_bfmeSecondItem);
}
