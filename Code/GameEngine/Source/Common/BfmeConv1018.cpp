// Open-BFME5 conversions.

class BfmeSink1018
{
public:
	void bfmeReset1018(int n);
	void bfmeSet1018(int v, int f);
};

struct BfmeK1018
{
	char m_bfmePad[0x24];
	int m_bfmeB;
	char m_bfmePad2[4];
	int m_bfmeA;
	char m_bfmePad3[8];
	char m_bfmeFlag;
};

class BfmeI1018
{
public:
	void bfmeGo1018I(void);

	char m_bfmePad[4];
	BfmeK1018 *m_bfmeK;
	BfmeSink1018 *m_bfmeSink;
};

void BfmeI1018::bfmeGo1018I(void)
{
	BfmeK1018 *k = m_bfmeK;

	m_bfmeSink->bfmeReset1018(0);

	if (k->m_bfmeFlag != 0)
		m_bfmeSink->bfmeSet1018(k->m_bfmeA, 1);
	else
		m_bfmeSink->bfmeSet1018(k->m_bfmeB, 1);
}
