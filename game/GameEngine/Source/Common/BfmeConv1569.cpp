// Open-BFME5 conversions.

extern "C" unsigned int __cdecl strlen(const char *text);

struct BfmeKeyVSC
{
	char m_bfmePad00[2];
	unsigned short m_bfme02;
	int m_bfme04;
	char m_bfme08[1];
};

extern "C" BfmeKeyVSC *g_bfmeRouteKeys1282[0xb2];

// Retail 0x009F6FA0 is the MSVCR71 _strcmpi import thunk (IAT slot
// 0x0135933C); game/gen_small/imports_000.cpp lands it as the no-argument
// jump stub ?ji_009f6fa0@@YAXXZ, and this call site supplies the two
// arguments.  Same convention as game/Libraries/Source/EA/Apt/
// Rva008B4260StringCompare.cpp.
extern void ji_009f6fa0();
typedef int (__cdecl *Rva009F6FA0Compare)(const char *left, const char *right);

BfmeKeyVSC **bfmeFindVSC(const char *name)
{
	int length = strlen(name);
	int i;

	for (i = 0; i < 0xb2; ++i)
	{
		if (g_bfmeRouteKeys1282[i]->m_bfme02 == length
			&& ((Rva009F6FA0Compare)ji_009f6fa0)(g_bfmeRouteKeys1282[i]->m_bfme08, name) == 0)
			return &g_bfmeRouteKeys1282[i];
	}

	return 0;
}
