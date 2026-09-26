class BfmeItemCU
{
public:
	BfmeItemCU(void *src);

	unsigned char m_bfmePadCU[0xc];
};

class BfmeNodeCU
{
public:
	BfmeNodeCU *bfmeCopyCU(const BfmeNodeCU &src);

	BfmeItemCU *m_bfmeItemCU;
	int m_bfmeBCU;
	int m_bfmeCCU;
};

BfmeNodeCU *BfmeNodeCU::bfmeCopyCU(const BfmeNodeCU &src)
{
	BfmeItemCU *p;

	if (src.m_bfmeItemCU != 0)
		p = new BfmeItemCU(src.m_bfmeItemCU);
	else
		p = 0;

	m_bfmeItemCU = p;
	m_bfmeBCU = src.m_bfmeBCU;
	m_bfmeCCU = src.m_bfmeCCU;

	return this;
}
