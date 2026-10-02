struct BfmeSubCBC
{
	unsigned char m_bfmeHead[0x18];
	int m_bfmeVal;
	unsigned int m_bfmeFlags;
};

class BfmeThingCBC
{
public:
	void bfmeStepCBC(int value);
	unsigned char m_bfmeHead[0x50];
	BfmeSubCBC *m_bfmeSub;
};

// 0x013379BC is the fallback value database pointer, defined as AptValue *
// by Bfme5AppendFallback8CAFF0.cpp (?g_bfmeFallbackDB@@3PAVAptValue@@A);
// this body returns the stored pointer in eax.
class AptValue;
extern AptValue *g_bfmeFallbackDB;

int bfmeGoCBC(BfmeThingCBC *what)
{
	what->bfmeStepCBC(what->m_bfmeSub->m_bfmeVal + 1);
	what->m_bfmeSub->m_bfmeFlags &= 0xFDFFFFFFu;
	return reinterpret_cast<int>(g_bfmeFallbackDB);
}
