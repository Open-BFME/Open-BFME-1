struct BfmeSubCBD
{
	unsigned char m_bfmeHead[0x18];
	int m_bfmeVal;
	unsigned int m_bfmeFlags;
};

class BfmeThingCBD
{
public:
	void bfmeStepCBD(int value);
	unsigned char m_bfmeHead[0x50];
	BfmeSubCBD *m_bfmeSub;
};

// 0x013379BC: the Apt undefined-value sentinel, defined as AptValue* in
// Bfme5AppendFallback8CAFF0.cpp.  Retail returns the raw pointer word here, so
// the reinterpret_cast compiles to the same 32-bit load.
class AptValue;
extern AptValue *g_bfmeFallbackDB;

int bfmeGoCBD(BfmeThingCBD *what)
{
	what->bfmeStepCBD(what->m_bfmeSub->m_bfmeVal - 1);
	what->m_bfmeSub->m_bfmeFlags &= 0xFDFFFFFFu;
	return reinterpret_cast<int>(g_bfmeFallbackDB);
}
