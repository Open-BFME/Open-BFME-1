// Open-BFME5 conversions.

extern char g_bfmeDefault1032[];
char * __stdcall bfmeFind1032(int a);

char * __stdcall bfmeGo1032E(int a)
{
	char *y = bfmeFind1032(a);

	if (y == 0)
		return g_bfmeDefault1032;

	return y + 0x48;
}
