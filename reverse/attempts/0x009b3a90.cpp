// ?bfmeQueryCpuTierFlags@@YAXPAH00@Z
// partial score=0.99 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2

// Retail RVA 0x009B3A90 is the 141-byte CPU-tier capability helper called by
// the matched codec dispatch installers at 0x009B0D60, 0x009A8550 and
// 0x009A8B50.  Those callers pass three int* out-parameters and consume the
// cumulative flags as cdecl ints.  The body calls the direct 160-byte CPUID
// probe at RVA 0x009C4B70, reads the shared selector bytes at VA 0x00DB3B2C,
// and expands the selected 0..3 tier into {A,B,C} flags.
//
// Boundary evidence: the last executable case returns at +0x8B.  The bytes
// beginning at +0x8C are the four-entry jump table and selector data through
// +0xA8; 0xCC padding follows through the next Ghidra entry at 0x009B3B40.
// The ledger size is therefore the complete Ghidra extent of 141 bytes, not
// merely the first return instruction.

extern "C" int __cdecl Rva009C4B70CpuFeatureProbe(void);

enum BfmeCpuTier
{
	BFME_CPU_TIER_0 = 0,
	BFME_CPU_TIER_1 = 1,
	BFME_CPU_TIER_2 = 2,
	BFME_CPU_TIER_3 = 3
};

extern void __cdecl bfmeQueryCpuTierFlags(int *pTierA, int *pTierB,
	int *pTierC)
{
	unsigned int subsystem = 1;
	if (Rva009C4B70CpuFeatureProbe())
		subsystem = 0xc;
	unsigned int tier = *(reinterpret_cast<const unsigned char *>(0x00DB3B2C)
		+ subsystem);
	__assume(tier <= 3);
	switch ((BfmeCpuTier)tier)
	{
	case BFME_CPU_TIER_0:
		*pTierA = 0;
	sharedZeroTail:
		*pTierB = 0;
		*pTierC = 0;
		break;
	case BFME_CPU_TIER_1:
		*pTierA = 1;
		goto sharedZeroTail;
	case BFME_CPU_TIER_2:
		*pTierA = 1;
		*pTierB = 1;
		*pTierC = 0;
		break;
	case BFME_CPU_TIER_3:
		*pTierA = 1;
		*pTierB = 1;
		*pTierC = 1;
		break;
	}
}
