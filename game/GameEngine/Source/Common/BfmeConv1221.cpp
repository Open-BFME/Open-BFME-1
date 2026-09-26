// Open-BFME5 conversions.

extern int g_bfmeLeft1221;
extern unsigned int *g_bfmeNext1221;

extern "C" unsigned int bfmeReload1221(void);

unsigned int bfmeNext1221(void)
{
	unsigned int y;

	if (--g_bfmeLeft1221 < 0)
		return bfmeReload1221();

	y = *g_bfmeNext1221++;
	y ^= y >> 11;
	y ^= (y << 7) & 0x9d2c5680;
	y ^= (y << 15) & 0xefc60000;
	return y ^ (y >> 18);
}
