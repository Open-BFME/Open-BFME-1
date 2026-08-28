struct BfmeSubDEA
{
	unsigned char m_bfmeHead[0x5c];
	unsigned int m_bfmeColor;
};

class BfmeThingDEA
{
public:
	BfmeSubDEA *bfmeFindDEA();
};

unsigned int bfmeGoDEA(BfmeThingDEA *a)
{
	BfmeSubDEA *s = a->bfmeFindDEA();
	if (s != 0)
		return s->m_bfmeColor;
	return 0x00FFFFFF;
}
