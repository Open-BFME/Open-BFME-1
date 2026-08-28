struct BfmeGotBPA
{
	unsigned char m_bfmeHead[0x14];
	void *m_bfmeWhat;
};

class BfmeThingBPA
{
public:
	BfmeGotBPA *bfmeFindBPA(void *what);
	void *bfmeGoBPA(void *what);
	BfmeGotBPA *m_bfmeEnd;
};

void *BfmeThingBPA::bfmeGoBPA(void *what)
{
	BfmeGotBPA *got = bfmeFindBPA(what);
	if (got == m_bfmeEnd)
		return 0;
	return got->m_bfmeWhat;
}
