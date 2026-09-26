// Four more: a restore of three saved values, a re-attach, a deadline check
// and two guarded pair copies.

class Gen_0042E800
{
public:
	void bfmeRestore(void);

private:
	char m_bfmeHead[0xC5];					// +0x000
	bool m_bfmeFlagA;					// +0x0C5
	bool m_bfmeFlagB;					// +0x0C6
	char m_bfmePad;						// +0x0C7
	int m_bfmeFirst;					// +0x0C8
	int m_bfmeSecond;					// +0x0CC
	int m_bfmeThird;					// +0x0D0
	int m_bfmeSavedFirst;					// +0x0D4
	int m_bfmeSavedSecond;					// +0x0D8
	int m_bfmeSavedThird;					// +0x0DC
};

// ?bfmeRestore@Gen_0042E800@@QAEXXZ
void Gen_0042E800::bfmeRestore(void)
{
	m_bfmeFlagA = true;
	m_bfmeFlagB = false;

	m_bfmeFirst = m_bfmeSavedFirst;
	m_bfmeSecond = m_bfmeSavedSecond;
	m_bfmeThird = m_bfmeSavedThird;
}

class BfmeOwnerEJ
{
public:
	char m_bfmeHead[0x1DC];					// +0x000
	int m_bfmeBack;						// +0x1DC
};

class Gen_00479A60
{
public:
	void bfmeAttach(BfmeOwnerEJ *owner);

private:
	int *m_bfmeTable;					// +0x00
	int m_bfmeValue;					// +0x04
	BfmeOwnerEJ *m_bfmeOwner;				// +0x08
};

// ?bfmeAttach@Gen_00479A60@@QAEXPAVBfmeOwnerEJ@@@Z
void Gen_00479A60::bfmeAttach(BfmeOwnerEJ *owner)
{
	BfmeOwnerEJ *current = m_bfmeOwner;

	if (current != 0)
	{
		current->m_bfmeBack = m_bfmeValue;

		m_bfmeOwner = 0;
	}

	if (owner != 0)
	{
		m_bfmeOwner = owner;

		m_bfmeValue = owner->m_bfmeBack;

		owner->m_bfmeBack = (int)this;
	}
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

class Gen_005B53D0
{
public:
	unsigned char bfmeExpired(void);

private:
	char m_bfmeHead[0x150];					// +0x000
	unsigned int m_bfmeStamp;				// +0x150
};

// ?bfmeExpired@Gen_005B53D0@@QAEEXZ
unsigned char Gen_005B53D0::bfmeExpired(void)
{
	if (m_bfmeStamp > (unsigned int)g_bfmeSwitchCJ->m_bfmeNow)
		m_bfmeStamp = 0;

	return m_bfmeStamp + 5 >= (unsigned int)g_bfmeSwitchCJ->m_bfmeNow;
}

class BfmePairEJ
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
};

class Gen_0043B1E0
{
public:
	void bfmeGetPairs(BfmePairEJ *first, BfmePairEJ *second) const;

private:
	char m_bfmeHead[0x544];					// +0x000
	int m_bfmeA;						// +0x544
	int m_bfmeB;						// +0x548
	int m_bfmeC;						// +0x54C
	int m_bfmeD;						// +0x550
};

// ?bfmeGetPairs@Gen_0043B1E0@@QBEXPAVBfmePairEJ@@0@Z
void Gen_0043B1E0::bfmeGetPairs(BfmePairEJ *first, BfmePairEJ *second) const
{
	if (first != 0)
	{
		first->m_bfmeFirst = m_bfmeA;
		first->m_bfmeSecond = m_bfmeB;
	}

	if (second != 0)
	{
		second->m_bfmeFirst = m_bfmeC;
		second->m_bfmeSecond = m_bfmeD;
	}
}
