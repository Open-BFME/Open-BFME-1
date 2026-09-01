// Open-BFME5 conversions.

struct BfmeBlockVKS
{
	BfmeBlockVKS bfmeNotVKS() const;
	int m_bfmeArr[10];
};

BfmeBlockVKS BfmeBlockVKS::bfmeNotVKS() const
{
	BfmeBlockVKS t = *this;
	for (int i = 0; i < 10; ++i)
		t.m_bfmeArr[i] = ~t.m_bfmeArr[i];
	((unsigned short *)t.m_bfmeArr)[19] = 0;
	return t;
}
