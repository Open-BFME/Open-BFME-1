// One more: a copy constructor that carries eighteen fields.

class Gen_001C07A0
{
public:
	Gen_001C07A0(const Gen_001C07A0 &other);
	virtual void bfmeTick(void) = 0;
private:
	int m_bfmeA;								// +0x04
	unsigned short m_bfmeB;						// +0x08
	unsigned short m_bfmeGap;					// +0x0a
	int m_bfmeC;								// +0x0c
	int m_bfmeD;								// +0x10
	int m_bfmeE;								// +0x14
	int m_bfmeF;								// +0x18
	unsigned char m_bfmeG;						// +0x1c
	unsigned char m_bfmeH;						// +0x1d
	unsigned char m_bfmeGap2[2];				// +0x1e
	int m_bfmeI;								// +0x20
	int m_bfmeJ;								// +0x24
	int m_bfmeK;								// +0x28
	int m_bfmeL;								// +0x2c
	int m_bfmeM;								// +0x30
	int m_bfmeN;								// +0x34
	int m_bfmeO;								// +0x38
	int m_bfmeP;								// +0x3c
	int m_bfmeQ;								// +0x40
	int m_bfmeR;								// +0x44
};

Gen_001C07A0::Gen_001C07A0(const Gen_001C07A0 &other)
{
	m_bfmeA = other.m_bfmeA;
	m_bfmeB = other.m_bfmeB;
	m_bfmeC = other.m_bfmeC;
	m_bfmeD = other.m_bfmeD;
	m_bfmeE = other.m_bfmeE;
	m_bfmeF = other.m_bfmeF;
	m_bfmeG = other.m_bfmeG;
	m_bfmeH = other.m_bfmeH;
	m_bfmeI = other.m_bfmeI;
	m_bfmeJ = other.m_bfmeJ;
	m_bfmeK = other.m_bfmeK;
	m_bfmeL = other.m_bfmeL;
	m_bfmeM = other.m_bfmeM;
	m_bfmeN = other.m_bfmeN;
	m_bfmeO = other.m_bfmeO;
	m_bfmeP = other.m_bfmeP;
	m_bfmeQ = other.m_bfmeQ;
	m_bfmeR = other.m_bfmeR;
}
