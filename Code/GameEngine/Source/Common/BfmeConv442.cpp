class BfmeSubBCF
{
public:
	void bfmeSendBCF(void *what);
};

class BfmeThingBCF
{
public:
	void bfmeGoBCF();
	unsigned char m_bfmeHead[0xc];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[0x824];
	BfmeSubBCF m_bfmeSub;
};

void BfmeThingBCF::bfmeGoBCF()
{
	m_bfmeSub.bfmeSendBCF(m_bfmeWhat);
}
