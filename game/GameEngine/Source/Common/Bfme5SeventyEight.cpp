// One more: four pairs of globals reset together.

extern int g_bfmeDefaultFE[];					// retail 0x012BC0C8
extern int g_bfmeFlagsFE[4];					// retail 0x012F9C5C
extern int *g_bfmePointersFE[4];				// retail 0x012F9CA4

// ?bfmeResetFE@@YAXXZ
void __cdecl bfmeResetFE(void)
{
	g_bfmePointersFE[0] = g_bfmeDefaultFE;
	g_bfmeFlagsFE[0] = 1;

	g_bfmePointersFE[1] = g_bfmeDefaultFE;
	g_bfmeFlagsFE[1] = 1;

	g_bfmePointersFE[2] = g_bfmeDefaultFE;
	g_bfmeFlagsFE[2] = 1;

	g_bfmePointersFE[3] = g_bfmeDefaultFE;
	g_bfmeFlagsFE[3] = 1;
}
