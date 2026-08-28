class BfmeThingCIC
{
public:
	void bfmeGoCIC(void *one, void *two);
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeErr;
};

int bfmeCallCIC(void *a, void *b, void *one, void *two);

void BfmeThingCIC::bfmeGoCIC(void *one, void *two)
{
	if (bfmeCallCIC(m_bfmeA, m_bfmeB, one, two) < 0)
		m_bfmeErr = -100;
}
