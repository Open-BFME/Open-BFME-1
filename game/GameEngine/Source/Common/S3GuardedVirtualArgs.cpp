// Four guarded virtual delegates that take arguments.
//
// Each reads a pointer member, and when it is not null redirects this to it,
// loads its vptr and tail-jumps through a fixed slot. The ret immediate on the
// null path divided by four gives the argument count -- one for three of them,
// two for 0x0075B730 -- and the jump only survives because the callee takes
// exactly those arguments in the same positions.


class Gen_000C9510Target
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
	virtual void bfmeVirtual(void *a0);		// slot 14, vtable+0x38
};

class Gen_000C9510
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x220];
	Gen_000C9510Target *m_bfmeImpl;				// +0x220
};

class Gen_00382CC0Target
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeVirtual(void *a0);		// slot 1, vtable+0x04
};

class Gen_00382CC0
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x118];
	Gen_00382CC0Target *m_bfmeImpl;				// +0x118
};

class Gen_0075B730Target
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeVirtual(void *a0, void *a1);		// slot 3, vtable+0x0C
};

class Gen_0075B730
{
public:
	void bfmeForward(void *a0, void *a1);

private:
	char m_bfmeHead[0x14];
	Gen_0075B730Target *m_bfmeImpl;				// +0x14
};

class Gen_008F7B50Target
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeVirtual(void *a0);		// slot 2, vtable+0x08
};

class Gen_008F7B50
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x8];
	Gen_008F7B50Target *m_bfmeImpl;				// +0x8
};

// ?bfmeForward@Gen_000C9510@@QAEXPAX@Z
void Gen_000C9510::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeVirtual(a0);
}

// ?bfmeForward@Gen_00382CC0@@QAEXPAX@Z
void Gen_00382CC0::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeVirtual(a0);
}

// ?bfmeForward@Gen_0075B730@@QAEXPAX0@Z
void Gen_0075B730::bfmeForward(void *a0, void *a1)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeVirtual(a0, a1);
}

// ?bfmeForward@Gen_008F7B50@@QAEXPAX@Z
void Gen_008F7B50::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeVirtual(a0);
}
