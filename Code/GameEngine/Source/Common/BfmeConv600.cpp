class BfmeOtherCGG
{
public:
	int bfmeKindCGG(void *value);
};

class BfmeThingCGG
{
public:
	void *bfmeGoCGG(BfmeOtherCGG *other, bool flag);
	unsigned char m_bfmeHead[4];
	void *m_bfmeVal;
	unsigned char m_bfmeGap[8];
	void *m_bfmePtr;
};

void *BfmeThingCGG::bfmeGoCGG(BfmeOtherCGG *other, bool flag)
{
	if (other->bfmeKindCGG(m_bfmeVal) == 2 && !flag)
		return 0;
	return m_bfmePtr;
}
