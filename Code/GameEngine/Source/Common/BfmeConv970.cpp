// Open-BFME5 conversions.

class BfmeRange970
{
public:
	void bfmeSet970(int a, int b, int c);

	char m_bfmePad[0x1c];
	volatile int m_bfmeX;
	volatile int m_bfmeY;
	volatile int m_bfmeZ;
	volatile int m_bfmeX2;
	volatile int m_bfmeY2;
	volatile int m_bfmeZ2;
	int m_bfmeMark;
	char m_bfmeKind;
};

void BfmeRange970::bfmeSet970(int a, int b, int c)
{
	m_bfmeX = a;
	m_bfmeY = b;
	m_bfmeZ = c;
	m_bfmeX2 = m_bfmeX;
	m_bfmeY2 = m_bfmeY;
	m_bfmeZ2 = m_bfmeZ;
	m_bfmeKind = 3;
	m_bfmeMark = -2;
}
