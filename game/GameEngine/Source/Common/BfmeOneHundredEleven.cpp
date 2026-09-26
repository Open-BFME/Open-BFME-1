// One more: a constructor that clears its scalars and then a block of sixteen
// slots.

class Gen_00808B80
{
public:
	void bfmeReset(void);
private:
	int m_bfmeGap;								// +0x000
	int m_bfmeA;								// +0x004
	int m_bfmeB;								// +0x008
	int m_bfmeC;								// +0x00c
	int m_bfmeD;								// +0x010
	int m_bfmeE;								// +0x014
	int m_bfmeSlots[16];						// +0x018
	int m_bfmeF;								// +0x058
	int m_bfmeG;								// +0x05c
	int m_bfmeGap2;								// +0x060
	int m_bfmeH;								// +0x064
	unsigned char m_bfmeGap3[0x168 - 0x68];		// +0x068
	unsigned char m_bfmeI;						// +0x168
	unsigned char m_bfmeGap4[3];				// +0x169
	int m_bfmeJ;								// +0x16c
	int m_bfmeK;								// +0x170
	unsigned char m_bfmeL;						// +0x174
};

void Gen_00808B80::bfmeReset(void)
{
	m_bfmeB = 0;
	m_bfmeA = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;

	m_bfmeF = 0;
	m_bfmeG = 0;
	m_bfmeH = 0;

	m_bfmeI = 0;
	m_bfmeJ = 0;
	m_bfmeK = 0;

	for (int index = 0; index < 16; ++index)
		m_bfmeSlots[index] = 0;

	m_bfmeL = 0;
}
