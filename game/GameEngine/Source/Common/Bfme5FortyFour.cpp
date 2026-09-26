// Five more: a tier from two limits, a reset around a state, a bounded bit
// check, an unlink, and three global flags.

class BfmeLimitsDM
{
public:
	int m_bfmeHead[6];					// +0x00
	int m_bfmeLow;						// +0x18
	int m_bfmeHigh;						// +0x1C
};

class Gen_003C6310
{
public:
	int bfmeTier(int value) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeLimitsDM *m_bfmeLimits;				// +0x04
};

// ?bfmeTier@Gen_003C6310@@QBEHH@Z
int Gen_003C6310::bfmeTier(int value) const
{
	BfmeLimitsDM *limits = m_bfmeLimits;

	if (value <= limits->m_bfmeLow)
		return 0;

	return (value > limits->m_bfmeHigh) + 1;
}

class Gen_00433780
{
public:
	void bfmeReset(void);

private:
	int m_bfmeHead[5];					// +0x00
	int m_bfmeState;					// +0x14
	int m_bfmeCurrent;					// +0x18
	int m_bfmeLast;						// +0x1C
	int m_bfmeGap[2];					// +0x20
	int m_bfmeCount;					// +0x28
};

// ?bfmeReset@Gen_00433780@@QAEXXZ
void Gen_00433780::bfmeReset(void)
{
	int state = m_bfmeState;

	if (state == 1 || state == 4)
		m_bfmeCount = 0;

	m_bfmeLast = m_bfmeCurrent;

	if (state != 3)
		m_bfmeState = 0;
}

class BfmeSlotDM
{
public:
	int m_bfmeHead[4];					// +0x00
	unsigned char m_bfmeBits;				// +0x10
	char m_bfmeTail[3];					// +0x11
};

class Gen_00465C20
{
public:
	bool bfmeCheck(unsigned int index) const;

private:
	char m_bfmeHead[0xA8];					// +0x00
	BfmeSlotDM m_bfmeSlots[12];				// +0xA8
};

// ?bfmeCheck@Gen_00465C20@@QBE_NI@Z
bool Gen_00465C20::bfmeCheck(unsigned int index) const
{
	if (index >= 12)
		return false;

	// The byte widens on the way in, so every step here stays on the full
	// register.
	unsigned int bits = m_bfmeSlots[index].m_bfmeBits;

	bits = bits >> 1;
	bits = ~bits;

	return (bits & 1) != 0;
}

class Gen_003D4B60
{
public:
	void bfmeUnlink(void);

private:
	int m_bfmeFirst;					// +0x00
	int m_bfmeHead[10];					// +0x04
	Gen_003D4B60 *m_bfmePrev;				// +0x2C
	Gen_003D4B60 *m_bfmeNext;				// +0x30
};

// ?bfmeUnlink@Gen_003D4B60@@QAEXXZ
void Gen_003D4B60::bfmeUnlink(void)
{
	Gen_003D4B60 *next = m_bfmeNext;

	if (next == 0)
		return;

	next->m_bfmeFirst = (int)m_bfmePrev;

	Gen_003D4B60 *prev = m_bfmePrev;

	if (prev != 0)
		prev->m_bfmeNext = m_bfmeNext;

	m_bfmeNext = 0;
	m_bfmePrev = 0;
}

extern bool g_bfmeFlagDMa;					// retail 0x012B7D84
extern bool g_bfmeFlagDMb;					// retail 0x012F4AFD
extern bool g_bfmeFlagDMc;					// retail 0x012F4AFE

// ?bfmeQuiet@@YAHXZ
int __cdecl bfmeQuiet(void)
{
	if (!g_bfmeFlagDMa && !g_bfmeFlagDMb && !g_bfmeFlagDMc)
		return 1;

	return 0;
}
