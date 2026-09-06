// ?bfmeGoFS@BfmeOwnerFS@@QAEXXZ (identity unknown)
// partial score=0.95 date=2026-09-06
// 45/46; retail loads the global with 8b 15 into edx and takes the local address
// in eax, MSVC uses the a1 short form into eax and the address in edx.
// Pins: ?bfmeSendFS@... 0x00046150, ?g_bfmeGlobalFS@... 0x00EF1028
struct BfmeTripleFS
{
	int m_bfmeAFS;
	int m_bfmeBFS;
	int m_bfmeCFS;
};

class BfmeSinkFS
{
public:
	void bfmeSendFS(BfmeTripleFS *value);
};

class BfmeGlobalFS
{
public:
	unsigned char m_bfmeHeadFS[0x28];
	BfmeSinkFS *m_bfmeSinkFS;
};

extern BfmeGlobalFS *g_bfmeGlobalFS;

class BfmeOwnerFS
{
public:
	void bfmeGoFS(void);

	unsigned char m_bfmeHeadFS[0xc];
	int m_bfmeFirstFS;
	int m_bfmeSecondFS;
};

void BfmeOwnerFS::bfmeGoFS(void)
{
	BfmeTripleFS value;

	value.m_bfmeAFS = m_bfmeFirstFS;
	value.m_bfmeBFS = m_bfmeSecondFS;
	value.m_bfmeCFS = 0;

	g_bfmeGlobalFS->m_bfmeSinkFS->bfmeSendFS(&value);
}
