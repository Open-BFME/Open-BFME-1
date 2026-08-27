// One more: a twelve-argument constructor that also keeps the triple it was
// handed and the pointer it came from.

class BfmeTripleRC
{
public:
	int m_bfmeX;								// +0x00
	int m_bfmeY;								// +0x04
	int m_bfmeZ;								// +0x08
};

class Gen_003D5670
{
public:
	Gen_003D5670(int a, int b, int c, int d, int e, int f, unsigned char g,
		unsigned char h, int i, int j, BfmeTripleRC *triple, unsigned char l);
private:
	int m_bfmeA;								// +0x00
	int m_bfmeB;								// +0x04
	int m_bfmeC;								// +0x08
	unsigned char m_bfmeD;						// +0x0c
	unsigned char m_bfmeGap[3];					// +0x0d
	int m_bfmeE;								// +0x10
	int m_bfmeX;								// +0x14
	int m_bfmeY;								// +0x18
	int m_bfmeZ;								// +0x1c
	unsigned char m_bfmeF;						// +0x20
	unsigned char m_bfmeGap2[3];				// +0x21
	int m_bfmeG;								// +0x24
	int m_bfmeH;								// +0x28
	int m_bfmeI;								// +0x2c
	int m_bfmeJ;								// +0x30
	BfmeTripleRC *m_bfmeTriple;					// +0x34
	unsigned char m_bfmeK;						// +0x38
};

Gen_003D5670::Gen_003D5670(int a, int b, int c, int d, int e, int f, unsigned char g,
	unsigned char h, int i, int j, BfmeTripleRC *triple, unsigned char l)
{
	m_bfmeA = a;
	m_bfmeB = b;
	m_bfmeC = i;
	m_bfmeD = g;
	m_bfmeE = j;

	m_bfmeX = triple->m_bfmeX;
	m_bfmeY = triple->m_bfmeY;
	m_bfmeZ = triple->m_bfmeZ;

	m_bfmeF = h;
	m_bfmeG = e;
	m_bfmeH = c;
	m_bfmeI = d;
	m_bfmeJ = f;
	m_bfmeTriple = triple;
	m_bfmeK = l;
}
