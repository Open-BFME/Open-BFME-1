// Five more: a bounded slot store, two flag tests, a two-word store and a
// countdown.

class Gen_00523380
{
public:
	void bfmeSetSlot(unsigned short index, unsigned char value);

private:
	char m_bfmeHead[0x12C];					// +0x000
	unsigned char m_bfmeSlots[8];				// +0x12C
};

// ?bfmeSetSlot@Gen_00523380@@QAEXGE@Z
void Gen_00523380::bfmeSetSlot(unsigned short index, unsigned char value)
{
	if (index < 8)
		m_bfmeSlots[index] = value;
}

class BfmeGameCW
{
public:
	char m_bfmeHead[0x288];					// +0x000
	bool m_bfmeOver;					// +0x288
};

extern BfmeGameCW *g_bfmeGameCW;				// retail 0x012F706C

class Gen_00609320
{
public:
	int bfmeDisabled(void) const;

private:
	char m_bfmeHead[0x60];					// +0x00
	bool m_bfmeQuiet;					// +0x60
};

// ?bfmeDisabled@Gen_00609320@@QBEHXZ
int Gen_00609320::bfmeDisabled(void) const
{
	if (!m_bfmeQuiet && !g_bfmeGameCW->m_bfmeOver)
		return 0;

	return 1;
}

class BfmePairCW
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
};

class BfmeOwnerCW
{
public:
	char m_bfmeHead[0x12050];				// +0x00000
	BfmePairCW m_bfmePair;					// +0x12050
	int m_bfmeGap;						// +0x12058
	int m_bfmeDeadline;					// +0x1205C
};

class Gen_00681980
{
public:
	void bfmeSetPair(const BfmePairCW *value);

private:
	int m_bfmeHead[2];					// +0x00
	BfmeOwnerCW *m_bfmeOwner;				// +0x08
};

// ?bfmeSetPair@Gen_00681980@@QAEXPBVBfmePairCW@@@Z
void Gen_00681980::bfmeSetPair(const BfmePairCW *value)
{
	BfmeOwnerCW *owner = m_bfmeOwner;

	if (owner)
		owner->m_bfmePair = *value;
}

class BfmeClockCJ
{
public:
	int m_bfmeHead[15];					// +0x00
	int m_bfmeNow;						// +0x3C
	char m_bfmeGap[0x50];					// +0x40
	unsigned char m_bfmeEnabled;				// +0x90
};

extern BfmeClockCJ *g_bfmeSwitchCJ;				// retail 0x012F0898

class Gen_00681D30
{
public:
	int bfmeRemaining(void) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeOwnerCW *m_bfmeOwner;				// +0x08
};

// ?bfmeRemaining@Gen_00681D30@@QBEHXZ
int Gen_00681D30::bfmeRemaining(void) const
{
	BfmeOwnerCW *owner = m_bfmeOwner;

	if (owner)
		return owner->m_bfmeDeadline - g_bfmeSwitchCJ->m_bfmeNow + 1;

	return 0;
}

class BfmeEntryCW
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
};

class Gen_006990B0
{
public:
	int bfmeReady(void) const;

private:
	unsigned int bfmeSize(void) const
	{
		return m_bfmeFinish - m_bfmeStart;
	}

	int m_bfmeHead[2];					// +0x00
	BfmeEntryCW *m_bfmeStart;				// +0x08
	BfmeEntryCW *m_bfmeFinish;				// +0x0C
	int m_bfmeGap;						// +0x10
	int m_bfmeMode;						// +0x14
};

// ?bfmeReady@Gen_006990B0@@QBEHXZ
int Gen_006990B0::bfmeReady(void) const
{
	int ready = 1;

	// Written as "== 0" the shift folds into a mask test; the negated "> 0"
	// keeps it.
	if (m_bfmeMode == 1 && !(bfmeSize() > 0))
		ready = 0;

	return ready;
}
