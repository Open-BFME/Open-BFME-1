// The pinned empty-string literal (symbols.csv ?g_Rva0107301CEmptyString@@3QBDB,
// RVA 0x00C7301C); the census alias _bfmeTextBME was a placeholder for it.
extern const char g_Rva0107301CEmptyString[];

struct BfmeSubBME
{
	void bfmeSetBME(void *text);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBME
{
public:
	BfmeThingBME *bfmeInitBME();
	int m_bfmeZero;
	BfmeSubBME m_bfmeSub;
};

BfmeThingBME *BfmeThingBME::bfmeInitBME()
{
	m_bfmeZero = 0;
	m_bfmeSub.bfmeSetBME((void *)g_Rva0107301CEmptyString);
	return this;
}
