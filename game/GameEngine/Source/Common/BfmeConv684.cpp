extern "C" unsigned char bfmeInfoDFC[];

class BfmeOtherDFC
{
public:
	void *bfmeMakeDFC(void *info, int flag);
};

class BfmeThingDFC
{
public:
	BfmeThingDFC *bfmeGoDFC(BfmeOtherDFC *other);
	void *m_bfmeVal;
};

BfmeThingDFC *BfmeThingDFC::bfmeGoDFC(BfmeOtherDFC *other)
{
	m_bfmeVal = other->bfmeMakeDFC(bfmeInfoDFC, 0);
	return this;
}
