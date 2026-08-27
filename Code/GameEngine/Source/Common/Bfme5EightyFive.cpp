// Two more: a box that starts as a single point, and an init that keeps the
// top of its own word.

class BfmePointGT
{
public:
	int m_bfmeX;
	int m_bfmeY;
};

class Gen_0043B150
{
public:
	void bfmeSetBox(const BfmePointGT *p);
private:
	int m_bfmeGap[336];							// +0x000
	unsigned char m_bfmeSet;					// +0x540
	unsigned char m_bfmeGap2[3];				// +0x541
	BfmePointGT m_bfmeMin;						// +0x544
	BfmePointGT m_bfmeMax;						// +0x54c
};

void Gen_0043B150::bfmeSetBox(const BfmePointGT *p)
{
	if (p != 0)
	{
		m_bfmeMin = *p;
		m_bfmeMax = *p;
		m_bfmeSet = 1;
	}
	else
	{
		m_bfmeSet = 0;
	}
}

class BfmePairGU
{
public:
	int m_bfmeX;
	int m_bfmeY;
};

extern int g_bfmeLiveGU;

class Gen_003D4B00
{
public:
	void bfmeInit(int owner, const BfmePairGU *p);
private:
	int m_bfmeX;								// +0x00
	int m_bfmeY;								// +0x04
	int m_bfmeC;								// +0x08
	int m_bfmeD;								// +0x0c
	unsigned short m_bfmeE;						// +0x10
	unsigned short m_bfmeF;						// +0x12
	int m_bfmeG;								// +0x14
	int m_bfmeH;								// +0x18
	int m_bfmeI;								// +0x1c
	int m_bfmeJ;								// +0x20
	int m_bfmeBits;								// +0x24
	int m_bfmeOwner;							// +0x28
};

void Gen_003D4B00::bfmeInit(int owner, const BfmePairGU *p)
{
	m_bfmeOwner = owner;
	m_bfmeX = p->m_bfmeX;
	m_bfmeY = p->m_bfmeY;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	m_bfmeG = 0;
	m_bfmeH = 0;
	m_bfmeI = 0;
	m_bfmeJ = 0;
	m_bfmeBits = m_bfmeBits & 0xFFFFFFE0;
	++g_bfmeLiveGU;
}
