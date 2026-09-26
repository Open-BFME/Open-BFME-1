// Open-BFME5 conversions.

class BfmeE1242;

class BfmeN1242
{
public:
	void bfmeReserve1242(int n);
	void bfmePut1242(int i, BfmeE1242 *e);
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x20 - 0x08];
	BfmeE1242 **m_bfme20;
	char m_bfmePad24[4];
	int m_bfme28;
};

extern BfmeE1242 **g_bfmeArr1242;
extern int g_bfmeCount1242;
extern void *g_bfmeResult1242;

extern "C" void bfmeMove1242(void *d, const void *s, unsigned int n);
extern "C" void *bfmeMake1242(int n);

void *bfmeInsert1242(BfmeN1242 *a, int k)
{
	int i;
	int n;
	BfmeE1242 *e;

	if ((a->m_bfme04 & 0x3f) == 0x16 && !((unsigned char)(~(a->m_bfme04 >> 15)) & 1)) {
		a->bfmeReserve1242(a->m_bfme28 + k);
		if (k) {
			bfmeMove1242(a->m_bfme20 + k, a->m_bfme20, a->m_bfme28 * 4);
			a->m_bfme28 += k;
			for (i = 0; i < k; ++i) {
				a->m_bfme20[i] = 0;
				e = g_bfmeArr1242[g_bfmeCount1242 - i - 1];
				if (i >= 0) {
					a->bfmeReserve1242(i + 1);
					a->bfmePut1242(i, e);
					n = a->m_bfme28;
					if (i + 1 > n)
						n = i + 1;
					a->m_bfme28 = n;
				}
			}
		}
		return bfmeMake1242(a->m_bfme28);
	}
	return g_bfmeResult1242;
}
