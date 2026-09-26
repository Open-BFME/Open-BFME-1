// Open-BFME5 conversions.

class BfmeE1243
{
public:
	void *bfmeVal1243();
};

class BfmeA1243
{
public:
	void bfmeApply1243(void *a, void *b, void *c);
	char m_bfmePad00[0x20];
	int m_bfme20;
	char m_bfmePad24[0x30 - 0x24];
	void *m_bfme30;
	void *m_bfme34;
	void *m_bfme38;
	char m_bfmePad3c[4];
	int m_bfme40;
	char m_bfmePad44[0x60 - 0x44];
	void *m_bfme60;
};

extern BfmeE1243 **g_bfmeArr1243;
extern int g_bfmeCount1243;
extern void *g_bfmeResult1243;

extern "C" void *bfmeMake1243(int n);

void *bfmeBuild1243(BfmeA1243 *a, int n)
{
	if (n < 1)
		return g_bfmeResult1243;

	a->m_bfme38 = g_bfmeArr1243[g_bfmeCount1243 - 1]->bfmeVal1243();
	if (n > 1)
		a->m_bfme34 = g_bfmeArr1243[g_bfmeCount1243 - 2]->bfmeVal1243();
	if (n > 2)
		a->m_bfme30 = g_bfmeArr1243[g_bfmeCount1243 - 3]->bfmeVal1243();
	a->bfmeApply1243(&a->m_bfme20, &a->m_bfme40, a->m_bfme60);
	return bfmeMake1243(0);
}
