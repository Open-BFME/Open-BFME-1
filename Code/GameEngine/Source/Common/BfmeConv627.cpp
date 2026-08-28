class BfmeSubCNG
{
public:
	void bfmeOneCNG(void *what);
};

class BfmeACNG
{
public:
	void bfmeTwoCNG();
};

class BfmeBCNG
{
public:
	void bfmeThreeCNG();
};

class BfmeThingCNG
{
public:
	void bfmeGoCNG(void *what);
	unsigned char m_bfmeHead[0x80];
	BfmeBCNG *m_bfmeB;
	unsigned char m_bfmeGap[0x28];
	BfmeSubCNG m_bfmeSub;
	unsigned char m_bfmeGap2[0x30b];
	BfmeACNG *m_bfmeA;
};

void BfmeThingCNG::bfmeGoCNG(void *what)
{
	m_bfmeSub.bfmeOneCNG(what);
	BfmeACNG *a = m_bfmeA;
	if (a != 0)
		a->bfmeTwoCNG();
	BfmeBCNG *b = m_bfmeB;
	if (b != 0)
		b->bfmeThreeCNG();
}
