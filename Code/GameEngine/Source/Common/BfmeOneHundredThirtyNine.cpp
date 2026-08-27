// One more: a constructor that registers itself as the one instance.

class Gen_005B42F0;
extern Gen_005B42F0 *g_bfmeInstanceXE;

#pragma pack(push, 1)

class Gen_005B42F0
{
public:
	Gen_005B42F0(void);
	virtual void bfmeTick(void) = 0;
private:
	int m_bfmeA;								// +0x04
	int m_bfmeB;								// +0x08
	int m_bfmeC;								// +0x0c
	int m_bfmeD;								// +0x10
	int m_bfmeE;								// +0x14
	int m_bfmeF;								// +0x18
	int m_bfmeG;								// +0x1c
	int m_bfmeH;								// +0x20
	int m_bfmeI;								// +0x24
	int m_bfmeJ;								// +0x28
	unsigned char m_bfmeK;						// +0x2c
	int m_bfmeL;								// +0x2d
	unsigned char m_bfmeM;						// +0x31
	unsigned char m_bfmeN;						// +0x32
	unsigned char m_bfmeO;						// +0x33
	unsigned char m_bfmeP;						// +0x34
};

#pragma pack(pop)

Gen_005B42F0::Gen_005B42F0(void)
{
	m_bfmeA = 0;
	m_bfmeB = 2;

	m_bfmeK = 0;
	m_bfmeM = 0;
	m_bfmeN = 0;
	m_bfmeO = 0;
	m_bfmeP = 0;

	m_bfmeD = 0;
	m_bfmeC = 0;
	m_bfmeF = 0;
	m_bfmeE = 0;
	m_bfmeH = 0;
	m_bfmeG = 0;
	m_bfmeJ = 0;
	m_bfmeI = 0;
	m_bfmeL = 0;

	g_bfmeInstanceXE = this;
}
