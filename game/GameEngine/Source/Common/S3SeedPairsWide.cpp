// Three more stack-pair seeders, 0x002BBD90, 0x002BBE90 and 0x002BC110.
//
// Same opening as the shorter seeders: both bytes of the pair come from one
// mov al,1 and its address goes to virtual slot ten. What follows is four more
// virtual calls, at vtable+0x74, +0x60, +0x78 and +0x6C, handing over the
// sub-objects at this+0x3C, +0x2C, +0x28 and +0x38 in that order. The first
// three addresses are lea'd; the last is formed with add edi,0x38, because edi
// is dead once it has been pushed.

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
	virtual void bfmeTakeAt2C(void *item);			// slot 24, vtable+0x60
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeTakeAt38(void *item);			// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt3C(void *item);			// slot 29, vtable+0x74
	virtual void bfmeTakeAt28(void *item);			// slot 30, vtable+0x78
};

struct BfmeSubObject
{
	char m_bfmeBytes[4];
};


class Gen_002BBD90
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x28];
	BfmeSubObject m_bfmeAt28;				// +0x28
	BfmeSubObject m_bfmeAt2C;				// +0x2C
	char m_bfmeGap[0x38 - 0x30];
	BfmeSubObject m_bfmeAt38;				// +0x38
	BfmeSubObject m_bfmeAt3C;				// +0x3C
};

class Gen_002BBE90
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x28];
	BfmeSubObject m_bfmeAt28;				// +0x28
	BfmeSubObject m_bfmeAt2C;				// +0x2C
	char m_bfmeGap[0x38 - 0x30];
	BfmeSubObject m_bfmeAt38;				// +0x38
	BfmeSubObject m_bfmeAt3C;				// +0x3C
};

class Gen_002BC110
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeHead[0x28];
	BfmeSubObject m_bfmeAt28;				// +0x28
	BfmeSubObject m_bfmeAt2C;				// +0x2C
	char m_bfmeGap[0x38 - 0x30];
	BfmeSubObject m_bfmeAt38;				// +0x38
	BfmeSubObject m_bfmeAt3C;				// +0x3C
};

// ?bfmeSeed@Gen_002BBD90@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_002BBD90::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt3C(&m_bfmeAt3C);
	target->bfmeTakeAt2C(&m_bfmeAt2C);
	target->bfmeTakeAt28(&m_bfmeAt28);
	target->bfmeTakeAt38(&m_bfmeAt38);
}

// ?bfmeSeed@Gen_002BBE90@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_002BBE90::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt3C(&m_bfmeAt3C);
	target->bfmeTakeAt2C(&m_bfmeAt2C);
	target->bfmeTakeAt28(&m_bfmeAt28);
	target->bfmeTakeAt38(&m_bfmeAt38);
}

// ?bfmeSeed@Gen_002BC110@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_002BC110::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	target->bfmeTakeAt3C(&m_bfmeAt3C);
	target->bfmeTakeAt2C(&m_bfmeAt2C);
	target->bfmeTakeAt28(&m_bfmeAt28);
	target->bfmeTakeAt38(&m_bfmeAt38);
}
