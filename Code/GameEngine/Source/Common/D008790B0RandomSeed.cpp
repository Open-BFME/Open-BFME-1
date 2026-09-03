extern int g_bfmeSeed790B0;
extern int g_bfmeCarry790B0;

int d_008790b0(int reset)
{
	int carry;
	int seed;
	if (reset) {
		seed = 13;
		carry = 117;
	} else {
		carry = g_bfmeCarry790B0;
		seed = g_bfmeSeed790B0;
	}
	int next = (seed * 0x3E322 + carry * 0x8149A) % 0xF408B;
	g_bfmeCarry790B0 = seed;
	g_bfmeSeed790B0 = next;
	return next;
}
