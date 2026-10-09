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

class Gen_009CBC90
{
public:
	int bfmeAt(int index) const;
};

void BfmeThingBCF::bfmeGoBCF()
{
	((Gen_009CBC90 *)&m_bfmeSub)->bfmeAt((int)m_bfmeWhat);
}
