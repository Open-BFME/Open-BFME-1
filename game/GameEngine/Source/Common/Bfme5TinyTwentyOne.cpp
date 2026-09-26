// Four more: a vector size over a thirty-six byte element, a deadline built
// from a global clock, and the same linear search over a ninety-six byte
// stride emitted twice -- retail keeps both copies, so we do too.

class BfmeElemCL
{
public:
	int m_bfmeData[9];					// 36 bytes
};

class Gen_000CBC60
{
public:
	int bfmeSize(void) const;

private:
	int m_bfmeHead[177];					// +0x000
	BfmeElemCL *m_bfmeStart;				// +0x2C4
	BfmeElemCL *m_bfmeFinish;				// +0x2C8
};

// ?bfmeSize@Gen_000CBC60@@QBEHXZ
int Gen_000CBC60::bfmeSize(void) const
{
	return m_bfmeFinish - m_bfmeStart;
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

class Gen_000ECA20
{
public:
	void bfmeSetDeadline(unsigned int milliseconds);

private:
	int m_bfmeHead[62];					// +0x00
	int m_bfmeDeadline;					// +0xF8
};

// ?bfmeSetDeadline@Gen_000ECA20@@QAEXI@Z
void Gen_000ECA20::bfmeSetDeadline(unsigned int milliseconds)
{
	m_bfmeDeadline = milliseconds / 1000 * 5 + g_bfmeSwitchCJ->m_bfmeNow;
}

class BfmeSlotCM
{
public:
	int m_bfmeHead[15];					// +0x00
	void *m_bfmeKey;					// +0x3C
	int m_bfmeTail[8];					// +0x40
};

class Gen_000F9510
{
public:
	BfmeSlotCM *bfmeFind(void *key);

private:
	int m_bfmeHead;						// +0x00
	BfmeSlotCM *m_bfmeStart;				// +0x04
	BfmeSlotCM *m_bfmeFinish;				// +0x08
};

// ?bfmeFind@Gen_000F9510@@QAEPAVBfmeSlotCM@@PAX@Z
BfmeSlotCM *Gen_000F9510::bfmeFind(void *key)
{
	BfmeSlotCM *slot = m_bfmeStart;
	BfmeSlotCM *finish = m_bfmeFinish;

	while (slot != finish)
	{
		if (slot->m_bfmeKey == key)
			return slot;

		++slot;
	}

	return 0;
}

class Gen_000F9540
{
public:
	BfmeSlotCM *bfmeFind(void *key);

private:
	int m_bfmeHead;						// +0x00
	BfmeSlotCM *m_bfmeStart;				// +0x04
	BfmeSlotCM *m_bfmeFinish;				// +0x08
};

// ?bfmeFind@Gen_000F9540@@QAEPAVBfmeSlotCM@@PAX@Z
BfmeSlotCM *Gen_000F9540::bfmeFind(void *key)
{
	BfmeSlotCM *slot = m_bfmeStart;
	BfmeSlotCM *finish = m_bfmeFinish;

	while (slot != finish)
	{
		if (slot->m_bfmeKey == key)
			return slot;

		++slot;
	}

	return 0;
}
