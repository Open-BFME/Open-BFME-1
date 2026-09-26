extern "C" unsigned char bfmeInfoDFJ[];

class BfmeOtherDFJ
{
public:
	void *bfmeMakeDFJ(void *info, int flag);
};

class BfmeThingDFJ
{
public:
	BfmeThingDFJ *bfmeGoDFJ(BfmeOtherDFJ *other);
	void *m_bfmeVal;
};

BfmeThingDFJ *BfmeThingDFJ::bfmeGoDFJ(BfmeOtherDFJ *other)
{
	m_bfmeVal = other->bfmeMakeDFJ(bfmeInfoDFJ, 0);
	return this;
}
