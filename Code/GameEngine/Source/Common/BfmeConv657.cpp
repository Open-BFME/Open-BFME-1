extern unsigned int bfmeFlagCWB;
extern int bfmeNextCWB;
extern int bfmeIdCWB;

int bfmeGoCWB()
{
	if (!(bfmeFlagCWB & 1))
	{
		bfmeFlagCWB |= 1;
		bfmeIdCWB = bfmeNextCWB++;
		return bfmeIdCWB;
	}
	return bfmeIdCWB;
}
