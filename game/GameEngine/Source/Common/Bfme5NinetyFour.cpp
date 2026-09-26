// Two more: the second point setter, and a reset that clears thirteen members
// in one order.

class Gen_0093D250
{
public:
	bool bfmeSetPoint(float x, float y);
private:
	int m_bfmeGap[49];							// +0x00
	float m_bfmeX;								// +0xc4
	float m_bfmeY;								// +0xc8
};

bool Gen_0093D250::bfmeSetPoint(float x, float y)
{
	if (m_bfmeX == x && m_bfmeY == y)
		return false;

	m_bfmeX = x;
	m_bfmeY = y;
	return true;
}

class Gen_0073F960
{
public:
	void bfmeReset(void);
private:
	unsigned char m_bfmeGap[0x58];				// +0x0000
	int m_bfmeA;								// +0x0058
	int m_bfmeB;								// +0x005c
	unsigned char m_bfmeGap2[0x68 - 0x60];		// +0x0060
	int m_bfmeC;								// +0x0068
	unsigned char m_bfmeGap3[0x1dc - 0x6c];		// +0x006c
	unsigned char m_bfmeD;						// +0x01dc
	unsigned char m_bfmeGap4[0x204 - 0x1dd];	// +0x01dd
	unsigned char m_bfmeE;						// +0x0204
	unsigned char m_bfmeGap5[0x228 - 0x205];	// +0x0205
	unsigned char m_bfmeF;						// +0x0228
	unsigned char m_bfmeGap6[0x27c - 0x229];	// +0x0229
	unsigned char m_bfmeG;						// +0x027c
	unsigned char m_bfmeH;						// +0x027d
	unsigned char m_bfmeGap7[0x2354 - 0x27e];	// +0x027e
	int m_bfmeI;								// +0x2354
	unsigned char m_bfmeGap8[0x23b8 - 0x2358];	// +0x2358
	unsigned char m_bfmeJ;						// +0x23b8
	unsigned char m_bfmeGap9[0x243c - 0x23b9];	// +0x23b9
	int m_bfmeK;								// +0x243c
	int m_bfmeL;								// +0x2440
	int m_bfmeM;								// +0x2444
};

void Gen_0073F960::bfmeReset(void)
{
	m_bfmeI = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	m_bfmeH = 0;
	m_bfmeG = 0;
	m_bfmeJ = 0;
	m_bfmeK = 0;
	m_bfmeL = 0;
	m_bfmeM = 0;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
}
