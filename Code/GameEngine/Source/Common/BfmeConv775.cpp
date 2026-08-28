class BfmeOwnerDSP
{
public:
	void bfmeCallDSP(void *what);
};

struct BfmeThingDSP
{
	void bfmeGoDSP();
	unsigned char m_bfmeHead[4];
	void *m_bfmeP;
};

void BfmeThingDSP::bfmeGoDSP()
{
	void *p = m_bfmeP;
	m_bfmeP = 0;
	((BfmeOwnerDSP *)((char *)this - 8))->bfmeCallDSP(p);
}
