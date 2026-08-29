// Open-BFME5 conversions.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

extern "C" int (__cdecl *g_bfmeFn1182)(int c);
extern "C" int g_bfmeTab1182[0x100];
extern "C" char g_bfmeDone1182;

void bfmeInit1182(void)
{
	int i;
	int (__cdecl *fn)(int c);

	if (g_bfmeDone1182)
		return;

	memset(g_bfmeTab1182, 0, 0x100);
	fn = g_bfmeFn1182;
	g_bfmeDone1182 = 1;

	for (i = 0; i < 0x100; i++)
		if (fn(i))
			g_bfmeTab1182[i] = 2;

	g_bfmeTab1182[10] = 1;
	g_bfmeTab1182[13] = 1;
	g_bfmeTab1182[59] = 3;
}
