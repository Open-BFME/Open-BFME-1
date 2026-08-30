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

extern "C" int bfmeHash1229(const char *s, unsigned int n);

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
