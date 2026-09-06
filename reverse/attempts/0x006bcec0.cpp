// ?d_006bcec0@@YAXXZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /O2
// Retail 0x006BCEC0 is a constructor for a class with two direct bases and
// one virtual base.  The base constructor is the existing 0x001B3CF0 body.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeBaseVUQ
{
public:
	virtual void slot00() { }
	virtual void slot04() { }
	virtual void slot08() { }
	virtual void slot0C() { }
};

class Rva006BCEC0SecondBase
{
public:
	virtual void slot00() { }
	virtual void slot04() { }
	virtual void slot08() { }
	virtual void slot0C() { }
};

class Rva006BCEC0VirtualBase
{
public:
	virtual void slot00() { }
	virtual void slot04() { }
	virtual void slot08() { }
	virtual void slot0C() { }
	virtual void slot10() { }
};

class Rva001B3CF0Base
	: public BfmeBaseVUQ
	, public Rva006BCEC0SecondBase
	, virtual public Rva006BCEC0VirtualBase
{
public:
	Rva001B3CF0Base();

private:
	char m_pad0C[0x70];
	unsigned int m_baseTail;
};

#pragma comment(linker, "/alternatename:??0Rva001B3CF0Base@@QAE@XZ=?j_000405a2@@YAXXZ")

__forceinline __fastcall void rva006BCEC0ClearWords(unsigned int *words,
	unsigned int zero)
{
	words[0] = zero;
	words[1] = zero;
	words[2] = zero;
	words[3] = zero;
	words[4] = zero;
	words[5] = zero;
	words[6] = zero;
	words[7] = zero;
	words[8] = zero;
	words[9] = zero;
	words[10] = zero;
	words[11] = zero;
	words[12] = zero;
	words[13] = zero;
	words[14] = zero;
	words[15] = zero;
	words[16] = zero;
	words[17] = zero;
	words[18] = zero;
	words[19] = zero;
	words[20] = zero;
	words[21] = zero;
	words[22] = zero;
	words[23] = zero;
	words[24] = zero;
	words[25] = zero;
	words[26] = zero;
	words[27] = zero;
	words[28] = zero;
	words[29] = zero;
	words[30] = zero;
	words[31] = zero;
}

__forceinline __int64 rva006BCEC0Zero64()
{
	return 0;
}

class Rva006BCEC0State
{
public:
	__forceinline void clearWords()
	{
		unsigned int wordZero = (unsigned int)(rva006BCEC0Zero64() >> 32);
		m_words[0] = wordZero;
		m_words[1] = wordZero;
		m_words[2] = wordZero;
		m_words[3] = wordZero;
		m_words[4] = wordZero;
		m_words[5] = wordZero;
		m_words[6] = wordZero;
		m_words[7] = wordZero;
		m_words[8] = wordZero;
		m_words[9] = wordZero;
		m_words[10] = wordZero;
		m_words[11] = wordZero;
		m_words[12] = wordZero;
		m_words[13] = wordZero;
		m_words[14] = wordZero;
		m_words[15] = wordZero;
		m_words[16] = wordZero;
		m_words[17] = wordZero;
		m_words[18] = wordZero;
		m_words[19] = wordZero;
		m_words[20] = wordZero;
		m_words[21] = wordZero;
		m_words[22] = wordZero;
		m_words[23] = wordZero;
		m_words[24] = wordZero;
		m_words[25] = wordZero;
		m_words[26] = wordZero;
		m_words[27] = wordZero;
		m_words[28] = wordZero;
		m_words[29] = wordZero;
		m_words[30] = wordZero;
		m_words[31] = wordZero;
	}

	unsigned int m_words[32];
	volatile unsigned int m_100;
	volatile unsigned int m_104;
	volatile unsigned int m_108;
	volatile unsigned int m_10C;

private:
};

class Rva006BCEC0
	: public Rva001B3CF0Base
{
public:
	Rva006BCEC0();
	virtual void slot00() { }
	virtual void slot04() { }
	virtual void slot08() { }
	virtual void slot0C() { }
	virtual void second00() { }
	virtual void second04() { }
	virtual void second08() { }
	virtual void second0C() { }
	virtual void virtual00() { }
	virtual void virtual04() { }
	virtual void virtual08() { }
	virtual void virtual0C() { }
	virtual void virtual10() { }

private:
	Rva006BCEC0State m_state;
	unsigned int m_110;
	unsigned int m_114;
};

Rva006BCEC0::Rva006BCEC0()
{
	m_state.m_100 = 0;
	m_state.m_104 = 0;
	m_state.m_108 = 0;
	m_state.m_10C = 0;
	_ReadWriteBarrier();
	m_state.clearWords();
	_ReadWriteBarrier();
	m_state.m_104 = 0;
	m_state.m_10C = 0;
	m_state.m_108 = 0;
	m_state.m_100 = 0;
	m_110 = 0;
	m_114 = 0;
}
