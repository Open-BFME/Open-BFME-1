extern unsigned int bfmeFlagCWD;
extern int g_rva012F1030;
extern int bfmeIdCWD;

int bfmeGoCWD()
{
	if (!(bfmeFlagCWD & 1))
	{
		bfmeFlagCWD |= 1;
		bfmeIdCWD = g_rva012F1030++;
		return bfmeIdCWD;
	}
	return bfmeIdCWD;
}
