// ?d_0046ef10@@YAXXZ
// partial score=0.83 date=2026-08-30
// cl: /Og
extern int *g_bfmeLimitsDF;

// ?bfmeBandChecked@@YAHH@Z
int __cdecl bfmeBandChecked(int value)
{
	int index = 0;
	int *limit;
	register int query = value;

	if (g_bfmeLimitsDF == 0)
		goto beyond_limits;

	limit = g_bfmeLimitsDF + 1;

	do {
		int currentLimit = *limit;
		++index;
		if (query < currentLimit)
			return index;
		++limit;
	} while (index < 9);

beyond_limits:
	return ++index;
}
