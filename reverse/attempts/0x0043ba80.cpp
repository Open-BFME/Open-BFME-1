// ?bfmeCheckERA@BfmeHostERA@@QAE_NXZ (identity unknown)
// partial score=0.85 date=2026-09-06
// 61/67; structure and every branch match. Retail keeps TWO separate return-true
// blocks of different widths (mov al,1 early, mov eax,1 late); MSVC merges them.
// Pins needed: ?g_bfmeGlobalDataERA@@3PAUBfmeGlobalDataERA@@A,0x00EED5C8
//              ?g_bfmeModeERA@@3PAUBfmeModeERA@@A,0x00EF1028
//              ?g_bfmeLogicERA@@3PAUBfmeLogicERA@@A,0x00EF0898
struct BfmeGlobalDataERA
{
	unsigned char m_bfmeHeadERA[0xe54];
	char m_bfmeEnabledERA;
};

struct BfmeModeERA
{
	unsigned char m_bfmeHeadERA[0x2c];
	char m_bfmeActiveERA;
	char m_bfmeLockedERA;
};

struct BfmeLogicERA
{
	unsigned char m_bfmeHeadERA[0x3c];
	unsigned int m_bfmeFrameERA;
};

extern BfmeGlobalDataERA *g_bfmeGlobalDataERA;
extern BfmeModeERA *g_bfmeModeERA;
extern BfmeLogicERA *g_bfmeLogicERA;

struct BfmeHostERA
{
	bool bfmeCheckERA(void);
	unsigned char m_bfmeHeadERA[0x814];
	unsigned int m_bfmeLimitERA;
};

bool BfmeHostERA::bfmeCheckERA(void)
{
	if (!g_bfmeGlobalDataERA->m_bfmeEnabledERA)
		return true;
	BfmeModeERA *mode = g_bfmeModeERA;
	if ((mode != 0 && mode->m_bfmeActiveERA && mode->m_bfmeLockedERA)
		|| g_bfmeLogicERA->m_bfmeFrameERA >= m_bfmeLimitERA)
		return false;
	return true;
}
