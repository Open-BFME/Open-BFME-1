// Open-BFME5 conversions.

extern "C" char g_bfmeS1177[];

struct BfmeBuf1177
{
	void bfmeInit1177(char *s, int z);
	int m_bfme00[16];
	int m_bfme40[16];
	int m_bfme80;
};

class BfmeQ1177
{
public:
	void bfmeSend1177(int a, BfmeBuf1177 *b);
};

void bfmeNotify1177(BfmeQ1177 *a1, int a2)
{
	BfmeBuf1177 buf;
	int i;

	buf.m_bfme80 = 0;

	for (i = 0; i < 16; i++) {
		buf.m_bfme40[i] = 0;
		buf.m_bfme00[i] = 0;
	}

	buf.bfmeInit1177(g_bfmeS1177, 0);
	a1->bfmeSend1177(a2, &buf);
}
