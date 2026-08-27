// Two more: a twelve word block carried in with a flag cleared behind it, and
// a constructor that starts two scales at one and everything else at nothing.

class BfmeBlockTA
{
public:
	int m_bfmeWords[12];
};

class Gen_005BDE40
{
public:
	void bfmeSetBlock(const BfmeBlockTA *src);
private:
	unsigned char m_bfmeGap[0xc0];				// +0x000
	int m_bfmeBlock[12];						// +0x0c0
	unsigned char m_bfmeGap2[0x1a4 - 0xf0];		// +0x0f0
	unsigned char m_bfmeDirty;					// +0x1a4
};

void Gen_005BDE40::bfmeSetBlock(const BfmeBlockTA *src)
{
	m_bfmeBlock[0] = src->m_bfmeWords[0];
	m_bfmeBlock[1] = src->m_bfmeWords[1];
	m_bfmeBlock[2] = src->m_bfmeWords[2];
	m_bfmeBlock[3] = src->m_bfmeWords[3];
	m_bfmeBlock[4] = src->m_bfmeWords[4];
	m_bfmeBlock[5] = src->m_bfmeWords[5];
	m_bfmeBlock[6] = src->m_bfmeWords[6];
	m_bfmeBlock[7] = src->m_bfmeWords[7];
	m_bfmeBlock[8] = src->m_bfmeWords[8];
	m_bfmeBlock[9] = src->m_bfmeWords[9];
	m_bfmeBlock[10] = src->m_bfmeWords[10];
	m_bfmeBlock[11] = src->m_bfmeWords[11];

	m_bfmeDirty = 0;
}

class Gen_006D8800
{
public:
	Gen_006D8800(void);
private:
	unsigned char m_bfmeGap[0x18];				// +0x000
	float m_bfmeScaleA;							// +0x018
	float m_bfmeScaleB;							// +0x01c
	int m_bfmeA;								// +0x020
	unsigned char m_bfmeGap2[0x34 - 0x24];		// +0x024
	int m_bfmeB;								// +0x034
	int m_bfmeC;								// +0x038
	unsigned char m_bfmeGap3[0x6c - 0x3c];		// +0x03c
	int m_bfmeD;								// +0x06c
	int m_bfmeE;								// +0x070
	int m_bfmeF;								// +0x074
	int m_bfmeG;								// +0x078
	int m_bfmeH;								// +0x07c
	unsigned char m_bfmeGap4[0xb0 - 0x80];		// +0x080
	int m_bfmeI;								// +0x0b0
	int m_bfmeJ;								// +0x0b4
	int m_bfmeK;								// +0x0b8
	unsigned char m_bfmeGap5[0xec - 0xbc];		// +0x0bc
	int m_bfmeL;								// +0x0ec
	int m_bfmeM;								// +0x0f0
	int m_bfmeN;								// +0x0f4
	int m_bfmeO;								// +0x0f8
	int m_bfmeP;								// +0x0fc
	int m_bfmeQ;								// +0x100
	unsigned char m_bfmeR;						// +0x104
	unsigned char m_bfmeGap6[3];				// +0x105
	int m_bfmeS;								// +0x108
	int m_bfmeT;								// +0x10c
	unsigned char m_bfmeU;						// +0x110
};

Gen_006D8800::Gen_006D8800(void)
{
	m_bfmeScaleA = 1.0f;
	m_bfmeScaleB = 1.0f;

	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	m_bfmeG = 0;
	m_bfmeH = 0;
	m_bfmeI = 0;
	m_bfmeJ = 0;
	m_bfmeK = 0;
	m_bfmeL = 0;
	m_bfmeM = 0;
	m_bfmeN = 0;
	m_bfmeO = 0;
	m_bfmeP = 0;
	m_bfmeQ = 0;
	m_bfmeR = 0;
	m_bfmeS = 0;
	m_bfmeT = 0;
	m_bfmeU = 0;
}
