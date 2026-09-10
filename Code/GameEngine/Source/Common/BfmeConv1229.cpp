// Open-BFME5 conversions.

extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);

struct BfmeW1229
{
	const char *m_bfme00;
	int m_bfme04;
};

extern BfmeW1229 g_bfmeWords1229[];
extern signed char g_bfmeLookup1229[];
extern unsigned char g_bfmeLens1229[];

extern "C" int bfmeHash1229(const char *str, unsigned int len)
{
	const unsigned char asso_values[256] =
	{
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 0, 50, 0, 50, 0, 5, 25, 0, 10, 50, 30, 0, 50, 20, 0,
	0, 50, 50, 5, 15, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 0, 0, 50, 50, 50, 0, 50, 50, 50, 50, 50, 0,
	50, 50, 0, 25, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	};
	register unsigned int hval = len;

	switch (hval)
	{
	default:
		hval += asso_values[(unsigned char)str[7]];
		/*FALLTHROUGH*/
	case 7:
	case 6:
	case 5:
	case 4:
		hval += asso_values[(unsigned char)str[3]];
		/*FALLTHROUGH*/
	case 3:
	case 2:
		hval += asso_values[(unsigned char)str[1]];
		break;
	}
	return hval;
}

const BfmeW1229 *bfmeFind1229(const char *str, unsigned int len)
{
	int key;
	int index;
	const char *s;

	if (len <= 18 && len >= 2) {
		key = bfmeHash1229(str, len);
		if (key <= 49 && key >= 0) {
			index = g_bfmeLookup1229[key];
			if (index >= 0) {
				if (len == g_bfmeLens1229[index]) {
					s = g_bfmeWords1229[index].m_bfme00;
					if (*str == *s && !memcmp(str + 1, s + 1, len - 1))
						return &g_bfmeWords1229[index];
				}
			}
		}
	}
	return 0;
}
