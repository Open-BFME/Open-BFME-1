// Four more tiny ones: a flag set only in one mode, a table lookup behind a
// null guard, a choice between two objects and a digit parsed out of a
// string. The last two answer through the pointer first, which is what keeps
// the explicit zero and the fall-through on the reading path.

class Gen_0051D2E0
{
public:
	void bfmeSetPaired(int value);

private:
	char m_bfmeHead[0x25E];					// +0x000
	unsigned char m_bfmePaired;				// +0x25E
	char m_bfmeGap[5];					// +0x25F
	int m_bfmeKind;						// +0x264
};

// ?bfmeSetPaired@Gen_0051D2E0@@QAEXH@Z
void Gen_0051D2E0::bfmeSetPaired(int value)
{
	if (m_bfmeKind == 8)
		m_bfmePaired = (value == 2);
}

class BfmeTableCC
{
public:
	char m_bfmeHead[0x12060];				// +0x00000
	int m_bfmeSlots[64];					// +0x12060
};

class Gen_00681DB0
{
public:
	int bfmeSlot(int index) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeTableCC *m_bfmeTable;				// +0x08
};

// ?bfmeSlot@Gen_00681DB0@@QBEHH@Z
int Gen_00681DB0::bfmeSlot(int index) const
{
	BfmeTableCC *table = m_bfmeTable;

	if (table)
		return table->m_bfmeSlots[index];

	return 0;
}

class BfmeHolderCC
{
public:
	char m_bfmeHead[0x0C];					// +0x00
	int m_bfmeValue;					// +0x0C
};

class Gen_006D7C80
{
public:
	int bfmeValue(unsigned char which) const;

private:
	int m_bfmeHead[12];					// +0x00
	BfmeHolderCC *m_bfmeSecond;				// +0x30
	BfmeHolderCC *m_bfmeFirst;				// +0x34
};

// ?bfmeValue@Gen_006D7C80@@QBEHE@Z
int Gen_006D7C80::bfmeValue(unsigned char which) const
{
	if (which)
		return m_bfmeFirst->m_bfmeValue;

	return m_bfmeSecond->m_bfmeValue;
}

class BfmeTextCC
{
public:
	char m_bfmeHead[0x0C];					// +0x00
	char *m_bfmeText;					// +0x0C
};

class Gen_008A12A0
{
public:
	int bfmeDigit(void) const;

private:
	int m_bfmeHead[13];					// +0x00
	BfmeTextCC *m_bfmeHolder;				// +0x34
};

// ?bfmeDigit@Gen_008A12A0@@QBEHXZ
int Gen_008A12A0::bfmeDigit(void) const
{
	char *text = m_bfmeHolder->m_bfmeText;

	if (text[8] == ':')
		return text[9] - '0';

	return 6;
}
