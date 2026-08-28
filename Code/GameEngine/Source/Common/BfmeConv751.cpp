struct BfmeSrcDPD
{
	int m_bfmeA;
	int m_bfmeB;
};

class BfmeOtherDPD
{
public:
	void bfmeCallDPD(void *value);
	unsigned char m_bfmeHead[8];
	int m_bfmeA;
	int m_bfmeB;
};

BfmeOtherDPD *bfmeGoDPD(BfmeOtherDPD *other, void *value, BfmeSrcDPD *src)
{
	volatile int tmp = 0;
	other->bfmeCallDPD(value);
	other->m_bfmeA = src->m_bfmeA;
	other->m_bfmeB = src->m_bfmeB;
	return other;
}
