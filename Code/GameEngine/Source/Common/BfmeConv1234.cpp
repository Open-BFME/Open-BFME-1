// Open-BFME5 conversions.

class BfmeN1234
{
public:
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x20 - 0x08];
	void **m_bfme20;
	char m_bfmePad24[4];
	int m_bfme28;
};

extern void *g_bfmeResult1234;

void *bfmeReverse1234(BfmeN1234 *a)
{
	int i;
	void *t;

	if ((a->m_bfme04 & 0x3f) == 0x16 && !((unsigned char)(~(a->m_bfme04 >> 15)) & 1)) {
		for (i = 0; i < a->m_bfme28 / 2; ++i) {
			t = a->m_bfme20[i];
			a->m_bfme20[i] = a->m_bfme20[a->m_bfme28 - i - 1];
			a->m_bfme20[a->m_bfme28 - i - 1] = t;
		}
		return a;
	}
	return g_bfmeResult1234;
}
