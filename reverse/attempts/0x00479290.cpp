// ?bfmeBase983@BfmeG983@@QAEXHPAXH@Z
// partial score=0.97 date=2026-09-17
// Open-BFME5 conversion.
// The caller at 0x004BE180 reaches this body through ILT 0x00016C2A.
// That pin names the body BfmeG983::bfmeBase983.

class BfmeClock983
{
public:
	virtual void bfmeV0983();
	virtual void bfmeV1983();
	virtual void bfmeV2983(int a, void *b, int c);

	char m_bfmePad983[0x1d8];
	BfmeClock983 *m_bfmeBack983;
};

class BfmeG983
{
public:
	void bfmeBase983(int a, void *b, int c);

	char m_bfmePad[4];
	BfmeClock983 *m_bfmeA;
	BfmeClock983 *m_bfmeB;
};

void BfmeG983::bfmeBase983(int a, void *b, int c)
{
	if (m_bfmeA != 0)
		m_bfmeA->bfmeV2983(a, b, c);
	else
		m_bfmeB->bfmeV2983(a, b, c);

	if (a == 2)
	{
		BfmeClock983 *front = m_bfmeA;
		BfmeClock983 *back = m_bfmeB;
		if (back == 0)
			return;

		back->m_bfmeBack983 = front;
		m_bfmeB = 0;
	}
}
