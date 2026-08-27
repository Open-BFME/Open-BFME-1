// One more: a constructor whose only defaults are two table pointers, two
// counts, one flag, a scale and a third pointer.

class BfmeTableUA;
extern BfmeTableUA g_bfmeFirstUA;
extern BfmeTableUA g_bfmeSecondUA;
extern BfmeTableUA g_bfmeThirdUA;

class Gen_0027AE50
{
public:
	Gen_0027AE50(void);
private:
	int m_bfmeA;								// +0x00
	int m_bfmeB[14];							// +0x04
	BfmeTableUA *m_bfmeFirst;					// +0x3c
	BfmeTableUA *m_bfmeSecond;					// +0x40
	int m_bfmeC;								// +0x44
	unsigned short m_bfmeD;						// +0x48
	unsigned short m_bfmeGap;					// +0x4a
	int m_bfmeE;								// +0x4c
	int m_bfmeF;								// +0x50
	int m_bfmeG;								// +0x54
	int m_bfmeH;								// +0x58
	unsigned char m_bfmeI;						// +0x5c
	unsigned char m_bfmeJ;						// +0x5d
	unsigned char m_bfmeGap2[2];				// +0x5e
	int m_bfmeK[9];								// +0x60
	float m_bfmeScale;							// +0x84
	BfmeTableUA *m_bfmeThird;					// +0x88
	int m_bfmeL;								// +0x8c
	int m_bfmeM;								// +0x90
	unsigned char m_bfmeN;						// +0x94
	unsigned char m_bfmeGap3[3];				// +0x95
	int m_bfmeO;								// +0x98
	int m_bfmeP;								// +0x9c
};

Gen_0027AE50::Gen_0027AE50(void)
{
	m_bfmeA = -1;

	m_bfmeB[0] = 0;
	m_bfmeB[1] = 0;
	m_bfmeB[2] = 0;
	m_bfmeB[3] = 0;
	m_bfmeB[4] = 0;
	m_bfmeB[5] = 0;
	m_bfmeB[6] = 0;
	m_bfmeB[7] = 0;
	m_bfmeB[8] = 0;
	m_bfmeB[9] = 0;
	m_bfmeB[10] = 0;
	m_bfmeB[11] = 0;
	m_bfmeB[12] = 0;
	m_bfmeB[13] = 0;

	m_bfmeFirst = &g_bfmeFirstUA;
	m_bfmeSecond = &g_bfmeSecondUA;

	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeE = 0x16;
	m_bfmeF = 0xf;
	m_bfmeG = 0;
	m_bfmeH = 0;
	m_bfmeI = 0;
	m_bfmeJ = 1;

	m_bfmeK[0] = 0;
	m_bfmeK[1] = 0;
	m_bfmeK[2] = 0;
	m_bfmeK[3] = 0;
	m_bfmeK[4] = 0;
	m_bfmeK[5] = 0;
	m_bfmeK[6] = 0;
	m_bfmeK[7] = 0;
	m_bfmeK[8] = 0;

	m_bfmeScale = 1.0f;
	m_bfmeThird = &g_bfmeThirdUA;

	m_bfmeL = 0;
	m_bfmeM = 0;
	m_bfmeN = 0;
	m_bfmeO = 0;
	m_bfmeP = 0;
}
