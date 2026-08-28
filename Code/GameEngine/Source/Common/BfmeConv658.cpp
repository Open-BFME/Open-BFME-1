extern unsigned int bfmeFlagCWC;
extern int bfmeNextCWC;
extern int bfmeIdCWC;

int bfmeGoCWC()
{
	if (!(bfmeFlagCWC & 1))
	{
		bfmeFlagCWC |= 1;
		bfmeIdCWC = bfmeNextCWC++;
		return bfmeIdCWC;
	}
	return bfmeIdCWC;
}
