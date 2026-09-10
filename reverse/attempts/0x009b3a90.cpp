// ?bfmeQueryCpuTierFlags@@YAXPAH00@Z
// partial score=0.98 date=2026-09-10
// Reads the shared per-subsystem CPU tier byte (subsystem 1 for the plain
// codec path, subsystem 0xc once bfmeDetectCpuFeature confirms the wider
// probe) and expands its 0..3 tier value into three cumulative capability
// flags for the caller's SIMD dispatch-table installer.

extern int __cdecl bfmeDetectCpuFeature(void);

enum BfmeCpuTier
{
	BFME_CPU_TIER_0 = 0,
	BFME_CPU_TIER_1 = 1,
	BFME_CPU_TIER_2 = 2,
	BFME_CPU_TIER_3 = 3
};

static const unsigned char g_bfmeCpuTierBySubsystem[16] =
{
	0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3
};

void __cdecl bfmeQueryCpuTierFlags(register int *pTierA, int *pTierB, int *pTierC)
{
	unsigned int subsystem = 1;
	if (bfmeDetectCpuFeature())
		subsystem = 0xc;
	unsigned int tier = g_bfmeCpuTierBySubsystem[subsystem];
	__assume(tier <= 3);
	switch ((BfmeCpuTier)tier)
	{
	case 0:
		*pTierA = 0;
	sharedZeroTail:
		*pTierB = 0;
		*pTierC = 0;
		break;
	case 1:
		*pTierA = 1;
		goto sharedZeroTail;
	case 2:
		*pTierA = 1;
		*pTierB = 1;
		*pTierC = 0;
		break;
	case 3:
		*pTierA = 1;
		*pTierB = 1;
		*pTierC = 1;
		break;
	}
}
