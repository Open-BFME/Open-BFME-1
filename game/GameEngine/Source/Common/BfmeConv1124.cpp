// Open-BFME5 conversions.

struct BfmeSubE1124
{
	char m_bfmePad[4];
	char m_bfme04;
};

class BfmeBaseE1124
{
public:
	BfmeBaseE1124(void) { m_bfme04 = 1; m_bfme08 = 0; }
	volatile int m_bfme04;
	volatile char m_bfme08;
	char m_bfmePad[3];
};

class BfmeE1124 : public BfmeBaseE1124
{
public:
	BfmeE1124(BfmeSubE1124 *p);
	virtual void bfmeV0E1124(void) = 0;
	BfmeSubE1124 *m_bfme0c;
};

BfmeE1124::BfmeE1124(BfmeSubE1124 *p)
{
	m_bfme0c = p;
	p->m_bfme04 = 0;
}

struct BfmeSubF1124
{
	char m_bfmePad[4];
	char m_bfme04;
};

class BfmeBaseF1124
{
public:
	BfmeBaseF1124(void) { m_bfme04 = 1; m_bfme08 = 0; }
	volatile int m_bfme04;
	volatile char m_bfme08;
	char m_bfmePad[3];
};

class BfmeF1124 : public BfmeBaseF1124
{
public:
	BfmeF1124(BfmeSubF1124 *p);
	virtual void bfmeV0F1124(void) = 0;
	BfmeSubF1124 *m_bfme0c;
};

BfmeF1124::BfmeF1124(BfmeSubF1124 *p)
{
	m_bfme0c = p;
	p->m_bfme04 = 0;
}
