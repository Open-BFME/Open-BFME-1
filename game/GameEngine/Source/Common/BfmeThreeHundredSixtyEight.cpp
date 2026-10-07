// The tail call goes to ILT 0x00007513 -> 0x001C9B80, matched as
// BfmeThing916D::bfmeGo916D (thiscall, one stack argument).
class BfmeThing916D
{
public:
	void bfmeGo916D(void *what);
};

class BfmeInnerWC;

struct BfmeOwnerWC
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerWC *m_bfmeInner;
};

class BfmeSubWC
{
public:
	virtual void bfmeReleaseWC(int what);
};

class BfmeThingWC
{
public:
	void bfmeGoWC(int what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerWC *m_bfmeOwner;
	unsigned char m_bfmeGap[4];
	BfmeSubWC *m_bfmeSub;
};

void BfmeThingWC::bfmeGoWC(int what)
{
	BfmeSubWC *sub = m_bfmeSub;
	if (sub != 0)
		sub->bfmeReleaseWC(1);
	m_bfmeSub = 0;
	BfmeInnerWC *inner = m_bfmeOwner->m_bfmeInner;
	if (inner != 0)
		reinterpret_cast<BfmeThing916D *>(inner)->bfmeGo916D((void *)1);
}
