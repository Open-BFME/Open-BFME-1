extern unsigned int bfmeFlagCWB;
// VA 0x012F1030: dword counter shared by RVAs 0x003BCF00, 0x0043BCF0
// and 0x004C1240. Retail .data holds four zero bytes; EA's name is unproven.
int g_rva012F1030 = 0;
extern int bfmeIdCWB;

int bfmeGoCWB()
{
	if (!(bfmeFlagCWB & 1))
	{
		bfmeFlagCWB |= 1;
		bfmeIdCWB = g_rva012F1030++;
		return bfmeIdCWB;
	}
	return bfmeIdCWB;
}
