void bfmeDoBDF(void *one, void *two);

class BfmeThingBDF
{
public:
	void bfmeGoBDF();
	unsigned char m_bfmeHead[0xb4];
	void *m_bfmeWhat;
};

void BfmeThingBDF::bfmeGoBDF()
{
	bfmeDoBDF(m_bfmeWhat, m_bfmeWhat);
}
