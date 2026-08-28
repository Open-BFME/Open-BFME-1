void *bfmeJoinBSE(void *one, void *two);

class BfmeThingBSE
{
public:
	BfmeThingBSE *bfmeGoBSE(BfmeThingBSE *other);
	unsigned char m_bfmeHead[4];
	void *m_bfmeWhat;
};

BfmeThingBSE *BfmeThingBSE::bfmeGoBSE(BfmeThingBSE *other)
{
	void *b = other->m_bfmeWhat;
	void *a = m_bfmeWhat;
	m_bfmeWhat = bfmeJoinBSE(a, b);
	return this;
}
