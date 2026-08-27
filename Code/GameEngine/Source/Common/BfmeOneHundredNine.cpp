// One more: a field-by-field assignment that hands the object back.

class Gen_001A5A60
{
public:
	Gen_001A5A60 &bfmeAssign(const Gen_001A5A60 &other);
private:
	int m_bfmeA;								// +0x00
	int m_bfmeB;								// +0x04
	int m_bfmeC;								// +0x08
	int m_bfmeD;								// +0x0c
	int m_bfmeE;								// +0x10
	int m_bfmeF;								// +0x14
	unsigned char m_bfmeG;						// +0x18
	unsigned char m_bfmeGap[3];					// +0x19
	int m_bfmeH;								// +0x1c
	int m_bfmeI;								// +0x20
	int m_bfmeJ;								// +0x24
	int m_bfmeK;								// +0x28
	unsigned char m_bfmeL;						// +0x2c
	unsigned char m_bfmeM;						// +0x2d
	unsigned short m_bfmeN;						// +0x2e
};

Gen_001A5A60 &Gen_001A5A60::bfmeAssign(const Gen_001A5A60 &other)
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

	return *this;
}
