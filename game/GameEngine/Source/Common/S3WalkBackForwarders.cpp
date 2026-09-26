// Six more negative-displacement forwarders, all jumping to the slot at
// 0x0002644F like the three already landed.
//
// Each reads a pointer at a fixed displacement from this -- five of them
// negative, which is the enclosing object reached by walking back out of an
// embedded sub-object, and one positive -- then adds a second constant to land
// on a sub-object of what that pointer names, and tail-jumps. Both steps stay
// plain adds because both offsets are compile-time constants. The one at
// 0x00212E50 is fourteen bytes rather than eleven only because its first
// displacement needs a full dword.

class Gen_0002644FTarget
{
public:
	void bfmeForward(void);					// ILT 0x0002644F
};


struct Gen_0020A9A0Holder
{
	char m_bfmeHead[0x58];
	Gen_0002644FTarget m_bfmeSub;				// +0x58
};

class Gen_0020A9A0
{
public:
	void bfmeForward(void);
};

struct Gen_00212E50Holder
{
	char m_bfmeHead[0x5C];
	Gen_0002644FTarget m_bfmeSub;				// +0x5C
};

class Gen_00212E50
{
public:
	void bfmeForward(void);
};

struct Gen_0027FFE0Holder
{
	char m_bfmeHead[0x28];
	Gen_0002644FTarget m_bfmeSub;				// +0x28
};

class Gen_0027FFE0
{
public:
	void bfmeForward(void);
};

struct Gen_00289AA0Holder
{
	char m_bfmeHead[0x2C];
	Gen_0002644FTarget m_bfmeSub;				// +0x2C
};

class Gen_00289AA0
{
public:
	void bfmeForward(void);
};

struct Gen_002D34F0Holder
{
	char m_bfmeHead[0x14];
	Gen_0002644FTarget m_bfmeSub;				// +0x14
};

class Gen_002D34F0
{
public:
	void bfmeForward(void);
};

struct Gen_002D6D00Holder
{
	char m_bfmeHead[0x10];
	Gen_0002644FTarget m_bfmeSub;				// +0x10
};

class Gen_002D6D00
{
public:
	void bfmeForward(void);
};

// ?bfmeForward@Gen_0020A9A0@@QAEXXZ
void Gen_0020A9A0::bfmeForward(void)
{
	Gen_0020A9A0Holder *holder = *(Gen_0020A9A0Holder **)((char *)this - 0x28);

	holder->m_bfmeSub.bfmeForward();
}

// ?bfmeForward@Gen_00212E50@@QAEXXZ
void Gen_00212E50::bfmeForward(void)
{
	Gen_00212E50Holder *holder = *(Gen_00212E50Holder **)((char *)this - 0xDC);

	holder->m_bfmeSub.bfmeForward();
}

// ?bfmeForward@Gen_0027FFE0@@QAEXXZ
void Gen_0027FFE0::bfmeForward(void)
{
	Gen_0027FFE0Holder *holder = *(Gen_0027FFE0Holder **)((char *)this - 0x1C);

	holder->m_bfmeSub.bfmeForward();
}

// ?bfmeForward@Gen_00289AA0@@QAEXXZ
void Gen_00289AA0::bfmeForward(void)
{
	Gen_00289AA0Holder *holder = *(Gen_00289AA0Holder **)((char *)this - 0x1C);

	holder->m_bfmeSub.bfmeForward();
}

// ?bfmeForward@Gen_002D6D00@@QAEXXZ
void Gen_002D6D00::bfmeForward(void)
{
	Gen_002D6D00Holder *holder = *(Gen_002D6D00Holder **)((char *)this + 0xC);

	holder->m_bfmeSub.bfmeForward();
}
