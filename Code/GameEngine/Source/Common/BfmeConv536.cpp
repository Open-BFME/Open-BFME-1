class BfmeThingBVA
{
public:
	void bfmeStepBVA(BfmeThingBVA *other);
	BfmeThingBVA *bfmeGoBVA(BfmeThingBVA *other);
	unsigned char m_bfmeHead[0xc];
	int m_bfmeWhat;
	bool m_bfmeFlag;
};

BfmeThingBVA *BfmeThingBVA::bfmeGoBVA(BfmeThingBVA *other)
{
	if (this != other)
	{
		bfmeStepBVA(other);
		m_bfmeFlag = true;
		m_bfmeWhat = other->m_bfmeWhat;
	}
	return this;
}
