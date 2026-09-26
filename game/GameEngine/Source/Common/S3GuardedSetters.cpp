// Fourteen guarded one-liners in two shapes.
//
// Eight are guarded setters: read a pointer -- from a member, or from a global
// -- and write one field through it only when it is not null. The width of the
// move gives the field's type away: cl is a byte, ecx a dword.
//
// Six are guarded virtual queries on the object at +0x1C. When it exists the
// call is a tail jump through a fixed vtable slot; when it does not, the body
// falls through to a constant. Note the register on that path: ecx still holds
// this, because the mov ecx,eax that redirects it sits AFTER the branch, which
// is what lets 0x000A0060 answer with its own member rather than a literal.

typedef bool Bool;


struct Gen_002EFC30Impl
{
	char m_bfmeHead[0x18F4];
	Bool m_bfmeField;						// +0x18F4
};

extern Gen_002EFC30Impl *TheBfmeImpl_002EFC30;			// 0x012EF4CC

void __stdcall bfmeSet_002EFC30(Bool value);

struct Gen_00750550Impl
{
	char m_bfmeHead[0x4];
	Bool m_bfmeField;						// +0x4
};

class Gen_00750550
{
public:
	void bfmeSet(Bool value);

private:
	char m_bfmeHead[0x44];
	Gen_00750550Impl *m_bfmeImpl;					// +0x44
};

struct Gen_00750570Impl
{
	char m_bfmeHead[0x5];
	Bool m_bfmeField;						// +0x5
};

class Gen_00750570
{
public:
	void bfmeSet(Bool value);

private:
	char m_bfmeHead[0x44];
	Gen_00750570Impl *m_bfmeImpl;					// +0x44
};

struct Gen_007511D0Impl
{
	char m_bfmeHead[0x4];
	Bool m_bfmeField;						// +0x4
};

class Gen_007511D0
{
public:
	void bfmeSet(Bool value);

private:
	char m_bfmeHead[0x10];
	Gen_007511D0Impl *m_bfmeImpl;					// +0x10
};

struct Gen_007511F0Impl
{
	char m_bfmeHead[0x5];
	Bool m_bfmeField;						// +0x5
};

class Gen_007511F0
{
public:
	void bfmeSet(Bool value);

private:
	char m_bfmeHead[0x10];
	Gen_007511F0Impl *m_bfmeImpl;					// +0x10
};

struct Gen_0075AF20Impl
{
	char m_bfmeHead[0x20];
	int m_bfmeField;						// +0x20
};

class Gen_0075AF20
{
public:
	void bfmeSet(int value);

private:
	char m_bfmeHead[0x4];
	Gen_0075AF20Impl *m_bfmeImpl;					// +0x4
};

struct Gen_0075BFB0Impl
{
	char m_bfmeHead[0x20];
	int m_bfmeField;						// +0x20
};

class Gen_0075BFB0
{
public:
	void bfmeSet(int value);

private:
	char m_bfmeHead[0x1C0];
	Gen_0075BFB0Impl *m_bfmeImpl;					// +0x1C0
};

struct Gen_0092D450Impl
{
	char m_bfmeHead[0x1C];
	Bool m_bfmeField;						// +0x1C
};

class Gen_0092D450
{
public:
	void bfmeSet(Bool value);

private:
	char m_bfmeHead[0xC8];
	Gen_0092D450Impl *m_bfmeImpl;					// +0xC8
};

class Gen_000A0060Impl
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
	virtual Bool bfmeQuery(void);			// slot 15, vtable+0x3C
};

class Gen_000A0060
{
public:
	Bool bfmeQuery(void);

private:
	char m_bfmeHead[0x1C];
	Gen_000A0060Impl *m_bfmeImpl;					// +0x1C
	char m_bfmeGap[0x42 - 0x20];
	Bool m_bfmeFlag;					// +0x42
};

class Gen_0016A1B0Impl
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
	virtual Bool bfmeQuery(void);			// slot 13, vtable+0x34
};

class Gen_0016A1B0
{
public:
	Bool bfmeQuery(void);

private:
	char m_bfmeHead[0x1C];
	Gen_0016A1B0Impl *m_bfmeImpl;					// +0x1C
};

class Gen_0026E680Impl
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
	virtual Bool bfmeQuery(void);			// slot 8, vtable+0x20
};

class Gen_0026E680
{
public:
	Bool bfmeQuery(void);

private:
	char m_bfmeHead[0x1C];
	Gen_0026E680Impl *m_bfmeImpl;					// +0x1C
};

class Gen_0026E6A0Impl
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
	virtual Bool bfmeQuery(void);			// slot 10, vtable+0x28
};

class Gen_0026E6A0
{
public:
	Bool bfmeQuery(void);

private:
	char m_bfmeHead[0x1C];
	Gen_0026E6A0Impl *m_bfmeImpl;					// +0x1C
};

class Gen_0026E6C0Impl
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
	virtual Bool bfmeQuery(void);			// slot 11, vtable+0x2C
};

class Gen_0026E6C0
{
public:
	Bool bfmeQuery(void);

private:
	char m_bfmeHead[0x1C];
	Gen_0026E6C0Impl *m_bfmeImpl;					// +0x1C
};

class Gen_0026E6E0Impl
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
	virtual Bool bfmeQuery(void);			// slot 12, vtable+0x30
};

class Gen_0026E6E0
{
public:
	Bool bfmeQuery(void);

private:
	char m_bfmeHead[0x1C];
	Gen_0026E6E0Impl *m_bfmeImpl;					// +0x1C
};

// ?bfmeSet_002EFC30@@YGX_N@Z
void __stdcall bfmeSet_002EFC30(Bool value)
{
	if (TheBfmeImpl_002EFC30)
		TheBfmeImpl_002EFC30->m_bfmeField = value;
}

// ?bfmeSet@Gen_00750550@@QAEX_N@Z
void Gen_00750550::bfmeSet(Bool value)
{
	if (m_bfmeImpl)
		m_bfmeImpl->m_bfmeField = value;
}

// ?bfmeSet@Gen_00750570@@QAEX_N@Z
void Gen_00750570::bfmeSet(Bool value)
{
	if (m_bfmeImpl)
		m_bfmeImpl->m_bfmeField = value;
}

// ?bfmeSet@Gen_007511D0@@QAEX_N@Z
void Gen_007511D0::bfmeSet(Bool value)
{
	if (m_bfmeImpl)
		m_bfmeImpl->m_bfmeField = value;
}

// ?bfmeSet@Gen_007511F0@@QAEX_N@Z
void Gen_007511F0::bfmeSet(Bool value)
{
	if (m_bfmeImpl)
		m_bfmeImpl->m_bfmeField = value;
}

// ?bfmeSet@Gen_0075AF20@@QAEXH@Z
void Gen_0075AF20::bfmeSet(int value)
{
	if (m_bfmeImpl)
		m_bfmeImpl->m_bfmeField = value;
}

// ?bfmeSet@Gen_0075BFB0@@QAEXH@Z
void Gen_0075BFB0::bfmeSet(int value)
{
	if (m_bfmeImpl)
		m_bfmeImpl->m_bfmeField = value;
}

// ?bfmeSet@Gen_0092D450@@QAEX_N@Z
void Gen_0092D450::bfmeSet(Bool value)
{
	if (m_bfmeImpl)
		m_bfmeImpl->m_bfmeField = value;
}

// ?bfmeQuery@Gen_000A0060@@QAE_NXZ
Bool Gen_000A0060::bfmeQuery(void)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeQuery();

	return m_bfmeFlag;
}

// ?bfmeQuery@Gen_0016A1B0@@QAE_NXZ
Bool Gen_0016A1B0::bfmeQuery(void)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeQuery();

	return true;
}

// ?bfmeQuery@Gen_0026E680@@QAE_NXZ
Bool Gen_0026E680::bfmeQuery(void)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeQuery();

	return true;
}

// ?bfmeQuery@Gen_0026E6A0@@QAE_NXZ
Bool Gen_0026E6A0::bfmeQuery(void)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeQuery();

	return true;
}

// ?bfmeQuery@Gen_0026E6C0@@QAE_NXZ
Bool Gen_0026E6C0::bfmeQuery(void)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeQuery();

	return true;
}

// ?bfmeQuery@Gen_0026E6E0@@QAE_NXZ
Bool Gen_0026E6E0::bfmeQuery(void)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeQuery();

	return true;
}
