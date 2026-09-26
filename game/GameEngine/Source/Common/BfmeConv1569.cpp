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

int bfmeCompareVSC(const char *left, const char *right);

BfmeKeyVSC **bfmeFindVSC(const char *name)
{
	int length = strlen(name);
	int i;

	for (i = 0; i < 0xb2; ++i)
	{
		if (g_bfmeRouteKeys1282[i]->m_bfme02 == length
			&& bfmeCompareVSC(g_bfmeRouteKeys1282[i]->m_bfme08, name) == 0)
			return &g_bfmeRouteKeys1282[i];
	}

	return 0;
}
