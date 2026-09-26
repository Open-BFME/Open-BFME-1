extern int *g_bfmeLimitsDF;					// retail 0x012F401C

// ?bfmeBandChecked@@YAHH@Z
int __cdecl bfmeBandChecked(int value)
{
	int *limit = g_bfmeLimitsDF;
	int index = 0;

	if (limit) {
		while (index < 9 && value >= limit[index + 1])
			++index;
	}

	return index + 1;
}
