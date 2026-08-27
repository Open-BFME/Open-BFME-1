// A slot chosen and its three numbers copied out for use.

struct BfmeSlotAQ
{
	unsigned char m_bfmeHead[4];		// 0x0
	int m_bfmeAcross;			// 0x4
	int m_bfmeUp;				// 0x8
	int m_bfmeAlong;			// 0xc
};

class BfmeThingAQ
{
public:
	unsigned char bfmeChooseAQ(int which);

private:
	unsigned char m_bfmeHead[0x120];	// 0x0000
	BfmeSlotAQ m_bfmeSlots[0x15a];		// 0x0120
	unsigned char m_bfmeGap[8];		// 0x16c0
	int m_bfmeChosen;			// 0x16c8
	int m_bfmeSpare;			// 0x16cc
	int m_bfmeFirst;			// 0x16d0
	int m_bfmeSecond;			// 0x16d4
	int m_bfmeThird;			// 0x16d8
	int m_bfmeFourth;			// 0x16dc
	int m_bfmeFifth;			// 0x16e0
};

unsigned char BfmeThingAQ::bfmeChooseAQ(int which)
{
	if (which != -1 && m_bfmeChosen != which)
	{
		m_bfmeChosen = which;

		m_bfmeFirst = 0;
		m_bfmeSecond = m_bfmeSlots[which].m_bfmeAcross;
		m_bfmeThird = 0;
		m_bfmeFourth = m_bfmeSlots[which].m_bfmeUp;
		m_bfmeFifth = m_bfmeSlots[which].m_bfmeAlong;

		return 1;
	}

	return 0;
}
