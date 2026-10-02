// The call at 0x00802C30 targets the FESL counted-array allocator owned by
// Rva00802C30FeslAlloc.cpp; this placeholder member is that body.
class Rva00802A10
{
public:
	void allocate(int count);
	unsigned char m_bfmeHead[8];
};

struct BfmeSrcBZC
{
	int m_bfmeVal;
};

class BfmeThingBZC
{
public:
	void bfmeGoBZC(BfmeSrcBZC *src, int value);
	unsigned char m_bfmeHead[0x1c];
	Rva00802A10 m_bfmeSub;
	int m_bfmeA;
	int m_bfmeB;
};

void BfmeThingBZC::bfmeGoBZC(BfmeSrcBZC *src, int value)
{
	m_bfmeSub.allocate(src->m_bfmeVal);
	m_bfmeA = 0;
	m_bfmeB = value;
}
