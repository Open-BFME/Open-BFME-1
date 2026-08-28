struct BfmeSubBRE
{
	void bfmeDoBRE(void *what);
	unsigned char m_bfmeHead[0x24];
	unsigned int m_bfmeFlags;
};

class BfmeThingBRE
{
public:
	void bfmeGoBRE(void *what);
	BfmeSubBRE *m_bfmeSub;
};

void BfmeThingBRE::bfmeGoBRE(void *what)
{
	m_bfmeSub->bfmeDoBRE(what);
	m_bfmeSub->m_bfmeFlags |= 8;
	m_bfmeSub->m_bfmeFlags &= 0xffffffef;
}
