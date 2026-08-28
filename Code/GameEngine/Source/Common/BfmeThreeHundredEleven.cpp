struct BfmeRefRD
{
	unsigned char m_bfmeHead[4];
	int m_bfmeCount;
};

class BfmeThingRD
{
public:
	void bfmeBaseRD(BfmeThingRD *from);
	BfmeThingRD *bfmeCopyRD(BfmeThingRD *from);
	unsigned char m_bfmeHead[4];
	BfmeRefRD *m_bfmeRef;
	int m_bfmeMore;
};

BfmeThingRD *BfmeThingRD::bfmeCopyRD(BfmeThingRD *from)
{
	bfmeBaseRD(from);
	BfmeRefRD *ref = from->m_bfmeRef;
	m_bfmeRef = ref;
	if (ref != 0)
		++ref->m_bfmeCount;
	m_bfmeMore = from->m_bfmeMore;
	return this;
}
