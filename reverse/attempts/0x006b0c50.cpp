// ?bfmeResetGC@BfmeOwnerGC@@QAEXPAX@Z (identity unknown)
// partial score=0.97 date=2026-09-06
// 59/59 exact size; only the inline-memset setup order differs - retail emits
// lea edi (dest) then ecx (count) then eax (fill), MSVC emits ecx, eax, lea edi.
// Pin: ?bfmeCountGC@BfmeSubGC@@QAEIPAX@Z,0x00041AEC
extern "C" void *__cdecl memset(void *dest, int value, unsigned int count);
#pragma intrinsic(memset)

class BfmeSubGC
{
public:
	unsigned int bfmeCountGC(void *key);

	unsigned char m_bfmeSubDataGC[4];
};

class BfmeOwnerGC
{
public:
	void bfmeResetGC(void *key);

	unsigned char m_bfmeHeadGC[0x9c];
	unsigned int m_bfmeScaleGC;
	BfmeSubGC m_bfmeSubGC;
	unsigned char m_bfmeMidGC[0xe4];
	unsigned char m_bfmeFlagsGC[48];
};

void BfmeOwnerGC::bfmeResetGC(void *key)
{
	if (m_bfmeSubGC.bfmeCountGC(key) <= 0)
		return;

	if (m_bfmeScaleGC == 0x3f800000)
		return;

	memset(m_bfmeFlagsGC, 2, 48);
}
