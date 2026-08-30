// Open-BFME5 conversions.

class BfmeE1232
{
public:
	virtual void bfmeV1232A();
	virtual void bfmeV1232B();
	unsigned m_bfme04;
};

class BfmeA1232
{
public:
	void bfmePop1232(int n);
	int m_bfme00;
	int m_bfme04;
	BfmeE1232 **m_bfme08;
};

void BfmeA1232::bfmePop1232(int n)
{
	BfmeE1232 *e;
	int i;

	for (i = 1; i <= n; ++i) {
		e = m_bfme08[m_bfme00 - i];
		if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
			e->bfmeV1232B();
	}
	m_bfme00 -= n;
}
