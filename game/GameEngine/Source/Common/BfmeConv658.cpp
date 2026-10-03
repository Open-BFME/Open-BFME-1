extern unsigned int bfmeFlagCWC;
extern int g_rva012F1030;
extern int bfmeIdCWC;

int bfmeGoCWC()
{
	if (!(bfmeFlagCWC & 1))
	{
		bfmeFlagCWC |= 1;
		bfmeIdCWC = g_rva012F1030++;
		return bfmeIdCWC;
	}
	return bfmeIdCWC;
}
