// Two more: a seven-value setter and a reset with four handles cleared to
// nothing found.

class Gen_00396830
{
public:
	void bfmeSet(int a, int b, int c, int d, int e, int f, int g);
private:
	unsigned char m_bfmeFlag;					// +0x00
	unsigned char m_bfmeGap[3];					// +0x01
	int m_bfmeA;								// +0x04
	int m_bfmeB;								// +0x08
	int m_bfmeC;								// +0x0c
	int m_bfmeD;								// +0x10
	int m_bfmeE;								// +0x14
	int m_bfmeF;								// +0x18
	int m_bfmeG;								// +0x1c
};

void Gen_00396830::bfmeSet(int a, int b, int c, int d, int e, int f, int g)
{
	m_bfmeA = a;
	m_bfmeB = b;
	m_bfmeC = c;
	m_bfmeD = d;
	m_bfmeE = e;
	m_bfmeF = f;
	m_bfmeG = g;

	m_bfmeFlag = 1;
}

class Gen_00598F70
{
public:
	void bfmeReset(int unused);
private:
	unsigned char m_bfmeGap[0x258];				// +0x000
	unsigned char m_bfmeReady;					// +0x258
	unsigned char m_bfmeGap2;					// +0x259
	unsigned char m_bfmeBusy;					// +0x25a
	unsigned char m_bfmeGap3;					// +0x25b
	int m_bfmeCount;							// +0x25c
	unsigned char m_bfmeGap4[0x2c0 - 0x260];	// +0x260
	int m_bfmeSlots[4];							// +0x2c0
	unsigned char m_bfmeFirst;					// +0x2d0
	unsigned char m_bfmeSecond;					// +0x2d1
};

void Gen_00598F70::bfmeReset(int unused)
{
	m_bfmeBusy = 0;

	m_bfmeSlots[0] = -1;
	m_bfmeSlots[1] = -1;
	m_bfmeSlots[2] = -1;
	m_bfmeSlots[3] = -1;

	m_bfmeFirst = 0;
	m_bfmeSecond = 0;
	m_bfmeCount = 0;

	m_bfmeReady = 1;
}
