// Four virtual delegates.
//
// Each loads a pointer -- three from a member, one from a global -- then loads
// that object's vptr and tail-jumps through a fixed vtable slot. The jump
// means the callee takes exactly what the wrapper was handed, which here is
// nothing, and the two-step load (pointer, then vptr) is what separates these
// from the direct forwarders: the call is virtual, not resolved at link time.


class Gen_001B2090Target
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeForward(void);			// slot 1, vtable+0x04
};

class Gen_001B2090
{
public:
	void bfmeForward(void);

private:
	char m_bfmeHead[0x2C];
	Gen_001B2090Target *m_bfmeImpl;				// +0x2C
};

class Gen_00749760Target
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeForward(void);			// slot 3, vtable+0x0C
};

class Gen_00749760
{
public:
	void bfmeForward(void);

private:
	char m_bfmeHead[0x4];
	Gen_00749760Target *m_bfmeImpl;				// +0x4
};

class Gen_00751D50Target
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
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeForward(void);			// slot 16, vtable+0x40
};

class Gen_00751D50
{
public:
	void bfmeForward(void);

private:
	char m_bfmeHead[0x4];
	Gen_00751D50Target *m_bfmeImpl;				// +0x4
};

class Gen_00C70C90Target
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeForward(void);			// slot 2, vtable+0x08
};

extern Gen_00C70C90Target *TheBfmeTarget_00C70C90;			// 0x012C7464

class Gen_00C70C90
{
public:
	void bfmeForward(void);
};

// ?bfmeForward@Gen_001B2090@@QAEXXZ
void Gen_001B2090::bfmeForward(void)
{
	m_bfmeImpl->bfmeForward();
}

// ?bfmeForward@Gen_00749760@@QAEXXZ
void Gen_00749760::bfmeForward(void)
{
	m_bfmeImpl->bfmeForward();
}

// ?bfmeForward@Gen_00751D50@@QAEXXZ
void Gen_00751D50::bfmeForward(void)
{
	m_bfmeImpl->bfmeForward();
}

// ?bfmeForward@Gen_00C70C90@@QAEXXZ
void Gen_00C70C90::bfmeForward(void)
{
	TheBfmeTarget_00C70C90->bfmeForward();
}
