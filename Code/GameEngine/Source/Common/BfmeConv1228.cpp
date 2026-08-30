// Open-BFME5 conversions.

extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);

struct BfmeW1228
{
	const char *m_bfme00;
	int m_bfme04;
};

extern BfmeW1228 g_bfmeWords1228[];
extern signed char g_bfmeLookup1228[];
extern unsigned char g_bfmeLens1228[];

extern "C" int bfmeHash1228(const char *s, unsigned int n);

const BfmeW1228 *bfmeFind1228(const char *str, unsigned int len)
{
	int key;
	int index;
	const char *s;

	if (len <= 14 && len >= 5) {
		key = bfmeHash1228(str, len);
		if (key <= 14 && key >= 0) {
			index = g_bfmeLookup1228[key];
			if (index >= 0) {
				if (len == g_bfmeLens1228[index]) {
					s = g_bfmeWords1228[index].m_bfme00;
					if (*str == *s && !memcmp(str + 1, s + 1, len - 1))
						return &g_bfmeWords1228[index];
				}
			}
		}
	}
	return 0;
}
