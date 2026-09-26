struct BfmePartCDF
{
	void bfmeCopyOneCDF(BfmePartCDF *other);
	void bfmeCopyTwoCDF(BfmePartCDF *other);
	unsigned char m_bfmeHead[0xc];
};

struct BfmeThingCDF
{
	BfmeThingCDF *bfmeGoCDF(BfmeThingCDF *other);
	unsigned char m_bfmeHead[4];
	BfmePartCDF m_bfmeA;
	BfmePartCDF m_bfmeB;
};

BfmeThingCDF *BfmeThingCDF::bfmeGoCDF(BfmeThingCDF *other)
{
	m_bfmeA.bfmeCopyOneCDF(&other->m_bfmeA);
	m_bfmeB.bfmeCopyTwoCDF(&other->m_bfmeB);
	return this;
}
