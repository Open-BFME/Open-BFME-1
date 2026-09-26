// Four pairs of a flag and its permission bit, and a fraction taken
// between one entry and the next. The peer tag test lives with its callers.

class Gen_00694960
{
public:
	unsigned char bfmeAnyPending(unsigned char mask) const;
private:
	unsigned char m_bfmeGap[0x39];				// +0x00
	unsigned char m_bfmeA;						// +0x39
	unsigned char m_bfmeB;						// +0x3a
	unsigned char m_bfmeC;						// +0x3b
	unsigned char m_bfmeD;						// +0x3c
};

// Each flag needs its own bit in the mask, and the first one that is set
// without permission answers for all of them.
unsigned char Gen_00694960::bfmeAnyPending(unsigned char mask) const
{
	return (m_bfmeA && !(mask & 1)) ||
		(m_bfmeB && !(mask & 2)) ||
		(m_bfmeC && !(mask & 4)) ||
		(m_bfmeD && !(mask & 8));
}

class BfmeEntryIE
{
public:
	unsigned int m_bfmeStamp;					// +0x00
	float m_bfmeValue;							// +0x04
};

class Gen_005EE410
{
public:
	void bfmeUpdate(void);
private:
	int m_bfmeGap[3];							// +0x00
	BfmeEntryIE m_bfmeEntries[8];				// +0x0c
	int m_bfmeGap2;								// +0x4c
	float m_bfmeBase;							// +0x50
	float m_bfmeFrac;							// +0x54
	int m_bfmeIndex;							// +0x58
};

void Gen_005EE410::bfmeUpdate(void)
{
	int index = m_bfmeIndex;

	unsigned int next = m_bfmeEntries[index + 1].m_bfmeStamp;
	if (next == 0)
	{
		m_bfmeFrac = 0.0f;
		return;
	}

	m_bfmeFrac = (m_bfmeEntries[index].m_bfmeValue - m_bfmeBase)
		/ (float)(next - m_bfmeEntries[index].m_bfmeStamp);
}

