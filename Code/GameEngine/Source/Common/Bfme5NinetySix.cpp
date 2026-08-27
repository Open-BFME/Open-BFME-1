// Two more: a stop that only fires at the top of the scale, and a ring index.

class BfmeThingLC
{
public:
	int m_bfmeGap[14];							// +0x00
	int m_bfmeC;								// +0x38
	int m_bfmeB;								// +0x3c
	int m_bfmeValue;							// +0x40
	unsigned char m_bfmeGap2[0x69 - 0x44];		// +0x44
	unsigned char m_bfmeD;						// +0x69
	unsigned char m_bfmeE;						// +0x6a
};

extern BfmeThingLC *g_bfmeThingLC;

class Gen_006E1B80
{
public:
	void bfmeStop(void);
private:
	int m_bfmeGap[7];							// +0x00
	unsigned char m_bfmeFlag;					// +0x1c
	unsigned char m_bfmeGap2[0xa8 - 0x1d];		// +0x1d
	int m_bfmeState;							// +0xa8
};

void Gen_006E1B80::bfmeStop(void)
{
	if (g_bfmeThingLC->m_bfmeValue == 0x42C80000)
	{
		m_bfmeState = 4;

		BfmeThingLC *thing = g_bfmeThingLC;
		thing->m_bfmeValue = 0;
		thing->m_bfmeB = 0;
		thing->m_bfmeC = 0;

		g_bfmeThingLC->m_bfmeD = 0;
		g_bfmeThingLC->m_bfmeE = 0;

		m_bfmeFlag = 0;
	}
}

class BfmeSlotLD
{
public:
	int m_bfmeWords[5];
};

class Gen_008A0C90
{
public:
	BfmeSlotLD *bfmeAt(int offset) const;
private:
	BfmeSlotLD *m_bfmeBegin;					// +0x0000
	BfmeSlotLD *m_bfmeEnd;						// +0x0004
	int m_bfmeGap[1194];						// +0x0008
	int m_bfmeSlots;							// +0x12b0
};

BfmeSlotLD *Gen_008A0C90::bfmeAt(int offset) const
{
	int index = ((m_bfmeEnd - m_bfmeBegin) + offset) % m_bfmeSlots;
	if (index >= 0)
		return m_bfmeBegin + index;
	return m_bfmeBegin + (index + m_bfmeSlots);
}
