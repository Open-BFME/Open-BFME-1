extern "C" unsigned char bfmeInfoDFI[];

class BfmeOtherDFI
{
public:
	void *bfmeMakeDFI(void *info, int flag);
};

class BfmeThingDFI
{
public:
	BfmeThingDFI *bfmeGoDFI(BfmeOtherDFI *other);
	void *m_bfmeVal;
};

BfmeThingDFI *BfmeThingDFI::bfmeGoDFI(BfmeOtherDFI *other)
{
	m_bfmeVal = other->bfmeMakeDFI(bfmeInfoDFI, 0);
	return this;
}
