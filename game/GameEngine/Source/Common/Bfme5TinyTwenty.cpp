// Five more: a three-way readiness test, two accumulators gated on the same
// global flag, a cursor that stores through itself and then advances, and a
// bit test that lands as a zero/one.

class Gen_000874E0
{
public:
	int bfmeReady(void) const;

private:
	int m_bfmeHead[15];					// +0x00
	unsigned char m_bfmeFlags;				// +0x3C
	int m_bfmeGap[17];					// +0x40
	int m_bfmeState;					// +0x84
};

// ?bfmeReady@Gen_000874E0@@QBEHXZ
int Gen_000874E0::bfmeReady(void) const
{
	int state = m_bfmeState;

	// The whole test answers "no" first, so the three affirmatives share the
	// one block the compiler leaves at the end.
	if (state != 0 && state != 3 && (m_bfmeFlags & 1) == 0)
		return 0;

	return 1;
}

class BfmeSwitchCJ
{
public:
	char m_bfmeHead[0x90];					// +0x00
	unsigned char m_bfmeEnabled;				// +0x90
};

extern BfmeSwitchCJ *g_bfmeSwitchCJ;				// retail 0x012F0898

class Gen_000E8AF0
{
public:
	void bfmeAddTotal(int amount);
	void bfmeAddCount(int amount);

private:
	int m_bfmeHead;						// +0x00
	int m_bfmeCount;					// +0x04
	int m_bfmeTotal;					// +0x08
};

// ?bfmeAddTotal@Gen_000E8AF0@@QAEXH@Z
void Gen_000E8AF0::bfmeAddTotal(int amount)
{
	unsigned char enabled = g_bfmeSwitchCJ->m_bfmeEnabled;

	if (enabled)
		m_bfmeTotal = m_bfmeTotal + amount;
}

// ?bfmeAddCount@Gen_000E8AF0@@QAEXH@Z
void Gen_000E8AF0::bfmeAddCount(int amount)
{
	unsigned char enabled = g_bfmeSwitchCJ->m_bfmeEnabled;

	if (enabled)
		m_bfmeCount = m_bfmeCount + amount;
}

class Gen_0018F100
{
public:
	void bfmeSetCursor(void **value);

private:
	int m_bfmeHead[3];					// +0x00
	void **m_bfmeCursor;					// +0x0C
};

// ?bfmeSetCursor@Gen_0018F100@@QAEXPAPAX@Z
void Gen_0018F100::bfmeSetCursor(void **value)
{
	void **next = value;

	*m_bfmeCursor = next;

	// The empty cursor rides in the variable, so it goes out through a
	// register instead of as an immediate store.
	if (next)
		next = next + 1;
	else
		next = 0;

	m_bfmeCursor = next;
}

class Gen_000C4C80
{
public:
	int bfmeHasBit(int bit) const;

private:
	int m_bfmeHead[105];					// +0x000
	unsigned int m_bfmeMask;				// +0x1A4
};

// ?bfmeHasBit@Gen_000C4C80@@QBEHH@Z
int Gen_000C4C80::bfmeHasBit(int bit) const
{
	return (m_bfmeMask & (1 << (bit & 31))) != 0;
}
