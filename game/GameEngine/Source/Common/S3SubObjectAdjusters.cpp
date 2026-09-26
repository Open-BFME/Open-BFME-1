// Four sub-object adjusters.
//
// Each rewrites one pointer argument IN PLACE -- add 0x38, store it back into
// the same stack slot -- and then tail-jumps through a virtual slot. Rewriting
// the slot rather than pushing a new frame is what makes the tail jump
// possible: the callee sees the same argument count in the same positions.
//
// In source that adjustment is not arithmetic but a member address: the
// argument points at a whole object and the virtual takes the sub-object that
// lives at +0x38 of it.

struct BfmeSub
{
	char m_bfmeBytes[4];
};

struct BfmeWhole
{
	char m_bfmeHead[0x38];
	BfmeSub m_bfmeSub;					// +0x38
};


class Gen_0025A910
{
public:
	void bfmeForward(BfmeWhole *whole);

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
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeVirtual(BfmeSub *sub);		// slot 13, vtable+0x34
};

class Gen_00263B80
{
public:
	void bfmeForward(BfmeWhole *whole);

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
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeVirtual(BfmeSub *sub);		// slot 13, vtable+0x34
};

class Gen_002DB3C0
{
public:
	void bfmeForward(void *first, BfmeWhole *whole);

	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeVirtual(void *first, BfmeSub *sub);		// slot 4, vtable+0x10
};

class Gen_002DE910
{
public:
	void bfmeForward(void *first, BfmeWhole *whole);

	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeVirtual(void *first, BfmeSub *sub);		// slot 6, vtable+0x18
};

// ?bfmeForward@Gen_0025A910@@QAEXPAUBfmeWhole@@@Z
void Gen_0025A910::bfmeForward(BfmeWhole *whole)
{
	bfmeVirtual(&whole->m_bfmeSub);
}

// ?bfmeForward@Gen_00263B80@@QAEXPAUBfmeWhole@@@Z
void Gen_00263B80::bfmeForward(BfmeWhole *whole)
{
	bfmeVirtual(&whole->m_bfmeSub);
}

// ?bfmeForward@Gen_002DB3C0@@QAEXPAXPAUBfmeWhole@@@Z
void Gen_002DB3C0::bfmeForward(void *first, BfmeWhole *whole)
{
	bfmeVirtual(first, &whole->m_bfmeSub);
}

// ?bfmeForward@Gen_002DE910@@QAEXPAXPAUBfmeWhole@@@Z
void Gen_002DE910::bfmeForward(void *first, BfmeWhole *whole)
{
	bfmeVirtual(first, &whole->m_bfmeSub);
}
