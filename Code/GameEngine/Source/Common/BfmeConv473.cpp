struct BfmeSubBIF
{
	void **bfmeMakeBIF(void *what);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBIF
{
public:
	void bfmeGoBIF(void *what, void *out);
	unsigned char m_bfmeHead[0x6c];
	BfmeSubBIF m_bfmeSub;
};

void BfmeThingBIF::bfmeGoBIF(void *what, void *out)
{
	void **got = m_bfmeSub.bfmeMakeBIF(what);
	*got = out;
}
