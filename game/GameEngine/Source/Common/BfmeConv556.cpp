class BfmeCacheBZA;

class BfmeThingBZA
{
public:
	BfmeCacheBZA *bfmeGetBZA();
	unsigned char m_bfmeHead[0x244];
	BfmeCacheBZA *m_bfmeCache;
};

BfmeCacheBZA *bfmeMakeBZA(BfmeThingBZA *owner);

BfmeCacheBZA *BfmeThingBZA::bfmeGetBZA()
{
	if (m_bfmeCache == 0)
		m_bfmeCache = bfmeMakeBZA(this);
	return m_bfmeCache;
}
