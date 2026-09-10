// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2
// CPU-tier flags at 0x009B3A90, reached by matched codec installers
// 0x009B0D60, 0x009A8550 and 0x009A8B50 with three int* output slots.
// The 140-byte executable ends at +0x8B. Its compiler-generated four-entry
// jump table and thirteen-byte selector extend the complete body to 169 bytes.
// Ghidras old 141-byte extent cuts into the first jump-table entry.
// Spell out the original selector cases so MSVC regenerates both tables.

extern "C" int __cdecl Rva009C4B70CpuFeatureProbe(void);

extern void __cdecl bfmeQueryCpuTierFlags(int *pTierA, int *pTierB,
	int *pTierC)
{
	unsigned int subsystem = 1;
	if (Rva009C4B70CpuFeatureProbe())
		subsystem = 0xc;
	switch (subsystem)
	{
	case 0: case 2: case 4: case 5: case 8: case 9: case 10:
		*pTierA = 0;
		*pTierB = 0;
		*pTierC = 0;
		break;
	case 1: case 3: case 6: case 7:
		*pTierA = 1;
		*pTierB = 0;
		*pTierC = 0;
		break;
	case 11:
		*pTierA = 1;
		*pTierB = 1;
		*pTierC = 0;
		break;
	case 12:
		*pTierA = 1;
		*pTierB = 1;
		*pTierC = 1;
		break;
	}
}
