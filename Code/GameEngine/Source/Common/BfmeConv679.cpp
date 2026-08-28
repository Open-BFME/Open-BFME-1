struct BfmeSubDEC
{
	unsigned char m_bfmeHead[0x134];
	unsigned int m_bfmeColor;
};

class BfmeThingDEC
{
public:
	BfmeSubDEC *bfmeFindDEC();
};

unsigned int bfmeGoDEC(BfmeThingDEC *a)
{
	BfmeSubDEC *s = a->bfmeFindDEC();
	if (s != 0)
		return s->m_bfmeColor;
	return 0x00FFFFFF;
}
