// Open-BFME5 conversions.

class BfmeClock983
{
public:
	virtual void bfmeV0983();
	virtual void bfmeV1983();
	virtual int bfmeV2983(int a, void *b, int c);
	virtual void bfmeV3983();
	virtual void bfmeV4983();
	virtual void bfmeV5983();
	virtual void bfmeV6983();
	virtual void bfmeV7983();
	virtual void bfmeV8983();
	virtual void bfmeV9983();
	virtual void bfmeV10983();
	virtual void bfmeV11983();
	virtual void bfmeV12983();
	virtual void bfmeV13983();
	virtual void bfmeV14983();
	virtual void bfmeV15983();
	virtual void bfmeV16983();
	virtual void bfmeV17983();
	virtual void bfmeV18983();
	virtual void bfmeV19983();
	virtual void bfmeV20983();
	virtual void bfmeV21983();
	virtual void bfmeV22983();
	virtual void bfmeV23983();
	virtual void bfmeV24983();
	virtual void bfmeV25983();
	virtual void bfmeV26983();
	virtual void bfmeV27983();
	virtual void bfmeV28983();
	virtual void bfmeV29983();
	virtual void bfmeV30983();
	virtual void bfmeV31983();
	virtual void bfmeV32983();
	virtual void bfmeV33983();
	virtual void bfmeV34983();
	virtual void bfmeV35983();
	virtual void bfmeV36983();
	virtual void bfmeV37983();
	virtual void bfmeV38983();
	virtual void bfmeV39983();
	virtual void bfmeV40983();
	virtual void bfmeV41983();
	virtual void bfmeV42983();
	virtual void bfmeV43983();
	virtual void bfmeNote983(BfmeClock983 *a);

	char m_bfmePad983[0x1d8];
	BfmeClock983 *m_bfmeBack983;
};

extern BfmeClock983 *g_bfmeClock983;

class BfmeG983
{
public:
	void bfmeGo983(int a, void *b, int c);
	__declspec(noinline) int bfmeBase983(int a, void *b, int c);

	char m_bfmePad[4];
	BfmeClock983 *m_bfmeA;
	BfmeClock983 *m_bfmeB;
};

void BfmeG983::bfmeGo983(int a, void *b, int c)
{
	if (a == 0x1b && b)
		g_bfmeClock983->bfmeNote983(m_bfmeB);

	bfmeBase983(a, b, c);
}

int BfmeG983::bfmeBase983(int a, void *b, int c)
{
	int result;
	if (m_bfmeA != 0)
		result = m_bfmeA->bfmeV2983(a, b, c);
	else
		result = m_bfmeB->bfmeV2983(a, b, c);

	if (a == 2)
	{
		BfmeClock983 *front = m_bfmeA;
		BfmeClock983 *back = m_bfmeB;
		if (back == 0)
			return result;

		back->m_bfmeBack983 = front;
		m_bfmeB = 0;
	}
	return result;
}
