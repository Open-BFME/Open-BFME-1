struct BfmeSubDEB
{
	unsigned char m_bfmeHead[0xc8];
	unsigned int m_bfmeColor;
};

class BfmeThingDEB
{
public:
	BfmeSubDEB *bfmeFindDEB();
};

unsigned int bfmeGoDEB(BfmeThingDEB *a)
{
	BfmeSubDEB *s = a->bfmeFindDEB();
	if (s != 0)
		return s->m_bfmeColor;
	return 0x00FFFFFF;
}
