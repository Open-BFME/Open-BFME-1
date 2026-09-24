// Four more tiny ones: a deferred write flushed and cleared, a flag cleared
// twice around a singleton, a bit read through a pointer and another pair
// handed back.
//
// The bit has to answer through the pointer first: with the null tested first
// MSVC returns the null itself as the zero and the explicit xor disappears.

class Gen_0035EE50
{
public:
	void bfmeFlush(void);

private:
	int m_bfmeHead[8];					// +0x00
	unsigned char *m_bfmeSlot;				// +0x20
	unsigned char m_bfmeValue;				// +0x24
};

// ?bfmeFlush@Gen_0035EE50@@QAEXXZ
void Gen_0035EE50::bfmeFlush(void)
{
	unsigned char *slot = m_bfmeSlot;

	if (slot != 0)
	{
		*slot = m_bfmeValue;

		m_bfmeSlot = 0;
		m_bfmeValue = 0;
	}
}

class BfmeHolderBS
{
public:
	char m_bfmeHead[0x18F4];				// +0x0000
	unsigned char m_bfmeFlag;				// +0x18F4
};

extern BfmeHolderBS *g_bfmeHolderBS;				// retail 0x012EF4CC

class Gen_002ED870
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[2];					// +0x00
	unsigned char m_bfmeFlag;				// +0x08
};

// ?bfmeClear@Gen_002ED870@@QAEXXZ
void Gen_002ED870::bfmeClear(void)
{
	m_bfmeFlag = 0;

	BfmeHolderBS *holder = g_bfmeHolderBS;

	if (holder != 0)
		holder->m_bfmeFlag = 0;

	m_bfmeFlag = 0;
}

class BfmeThingBS
{
public:
	char m_bfmeHead[0x24];					// +0x00
	unsigned int m_bfmeBits;				// +0x24
};

class Gen_003D4C70
{
public:
	int bfmeBit(void) const;

private:
	BfmeThingBS *m_bfmeThing;				// +0x00
};

// ?bfmeBit@Gen_003D4C70@@QBEHXZ
int Gen_003D4C70::bfmeBit(void) const
{
	BfmeThingBS *thing = m_bfmeThing;

	if (thing)
		return (thing->m_bfmeBits >> 1) & 1;

	return 0;
}

class Gen_003C6F60
{
public:
	void bfmeGetPair(int *out) const;

private:
	int m_bfmeHead[27];					// +0x00
	int m_bfmeFirst;					// +0x6C
	int m_bfmeSecond;					// +0x70
};

