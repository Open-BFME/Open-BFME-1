// Open-BFME5 conversions.

void *bfmeAlloc950B(unsigned int n);

struct BfmeNode950B
{
	char m_bfmeFlag;
	char m_bfmePad[3];
	int m_bfme04;
	BfmeNode950B *m_bfmeNext;
	BfmeNode950B *m_bfmePrev;
};

class BfmeList950B
{
public:
	BfmeList950B();
	BfmeNode950B *m_bfmeHead;
	int m_bfme04;
	char m_bfmePad[4];
	volatile int m_bfme0c;
	volatile char m_bfme10;
};

BfmeList950B::BfmeList950B()
{
	m_bfmeHead = 0;
	m_bfmeHead = (BfmeNode950B *)bfmeAlloc950B(0x14);
	m_bfme04 = 0;
	m_bfmeHead->m_bfmeFlag = 0;
	m_bfmeHead->m_bfme04 = 0;
	m_bfmeHead->m_bfmeNext = m_bfmeHead;
	m_bfmeHead->m_bfmePrev = m_bfmeHead;
	m_bfme0c = 0;
	m_bfme10 = 1;
}
