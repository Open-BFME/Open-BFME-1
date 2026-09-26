class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *one, void *two);
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeErr;
};

int bfmeCallCIB(void *a, void *b, void *one, void *two);

void BfmeThingCIB::bfmeGoCIB(void *one, void *two)
{
	if (bfmeCallCIB(m_bfmeA, m_bfmeB, one, two) < 0)
		m_bfmeErr = -100;
}
