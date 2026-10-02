struct BfmePairBOC
{
	void *m_bfmeOne;
	void *m_bfmeTwo;
};

extern "C" void __cdecl __identifier("?j_00020509@@YAXXZ")();
typedef void (__stdcall *BfmeTailBOCThunk)(int flag);

class BfmeThingBOC
{
public:
	void bfmeGoBOC(BfmePairBOC *pair);
	unsigned char m_bfmeHead[0xc];
	void *m_bfmeA;
	void *m_bfmeB;
};

void BfmeThingBOC::bfmeGoBOC(BfmePairBOC *pair)
{
	m_bfmeA = pair->m_bfmeOne;
	m_bfmeB = pair->m_bfmeTwo;
	((BfmeTailBOCThunk)&__identifier("?j_00020509@@YAXXZ"))(1);
}
