struct BfmeVecZA
{
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

class BfmeThingZA
{
public:
	void bfmeBaseZA();
	BfmeThingZA *bfmeInitZA(const BfmeVecZA *one, const BfmeVecZA *two);
	unsigned char m_bfmeHead[4];
	BfmeVecZA m_bfmeA;
	BfmeVecZA m_bfmeB;
};

BfmeThingZA *BfmeThingZA::bfmeInitZA(const BfmeVecZA *one, const BfmeVecZA *two)
{
	bfmeBaseZA();
	m_bfmeA = *one;
	m_bfmeB = *two;
	return this;
}
