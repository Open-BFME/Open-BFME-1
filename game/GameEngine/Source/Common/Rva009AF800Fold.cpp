// ?rva009af800@@YAHHH@Z

int __cdecl rva009af800(int a, int b)
{
	int mask = b >> 31;
	int absB = (b ^ mask) - mask;
	int lt = (absB < a + a) ? 1 : 0;
	int t = lt * absB - a;
	int tmask = t >> 31;
	int abst = (t ^ tmask) - tmask;
	int r = -abst;
	r = r + mask;
	r = r + a;
	r = r ^ mask;
	return r;
}
