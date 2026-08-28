void *bfmeMakeBNG(void *one, void *two);

class BfmeThingBNG
{
public:
	void bfmeGoBNG(void *what);
	unsigned char m_bfmeHead[0xb4];
	void *m_bfmeGot;
};

void BfmeThingBNG::bfmeGoBNG(void *what)
{
	m_bfmeGot = bfmeMakeBNG(what, what);
}
