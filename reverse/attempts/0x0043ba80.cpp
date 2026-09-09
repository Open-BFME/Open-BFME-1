// ?bfmeCheckERA@BfmeHostERA@@QAE_NXZ
// partial score=0.87 date=2026-09-09
// 64/67; barriers at each true-return plus an inverted final compare reproduce
// retail's branch layout and both jump targets exactly (jae to the shared false
// tail). Residue is only the final true block's width: retail emits a full
// mov eax,1 (5B) there, every spelling tried still narrows it to mov al,1 (2B).
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

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)

struct BfmeHostERA
{
	bool bfmeCheckERA(void);
	unsigned char m_bfmeHeadERA[0x814];
	unsigned int m_bfmeLimitERA;
};

bool BfmeHostERA::bfmeCheckERA(void)
{
	if (!g_bfmeGlobalDataERA->m_bfmeEnabledERA)
	{
		_ReadWriteBarrier();
		return true;
	}
	BfmeModeERA *mode = g_bfmeModeERA;
	if (mode != 0 && mode->m_bfmeActiveERA && mode->m_bfmeLockedERA)
		goto fail;
	if (g_bfmeLogicERA->m_bfmeFrameERA < m_bfmeLimitERA)
	{
		_WriteBarrier();
		return true;
	}
fail:
	return false;
}
