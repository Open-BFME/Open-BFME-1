// Open-BFME5 conversions.

class BfmeClock983
{
public:
	virtual void bfmeV0983();
	virtual void bfmeV1983();
	virtual void bfmeV2983();
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
	virtual void bfmeNote983(int a);
};

extern BfmeClock983 *g_bfmeClock983;

class BfmeG983
{
public:
	void bfmeGo983(int a, void *b, int c);
	void bfmeBase983(int a, void *b, int c);

	char m_bfmePad[8];
	int m_bfmeVal;
};

void BfmeG983::bfmeGo983(int a, void *b, int c)
{
	if (a == 0x1b && b)
		g_bfmeClock983->bfmeNote983(m_bfmeVal);

	bfmeBase983(a, b, c);
}
