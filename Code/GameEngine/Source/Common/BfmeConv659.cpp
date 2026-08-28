extern unsigned int bfmeFlagCWD;
extern int bfmeNextCWD;
extern int bfmeIdCWD;

int bfmeGoCWD()
{
	if (!(bfmeFlagCWD & 1))
	{
		bfmeFlagCWD |= 1;
		bfmeIdCWD = bfmeNextCWD++;
		return bfmeIdCWD;
	}
	return bfmeIdCWD;
}
