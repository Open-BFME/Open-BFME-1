// Open-BFME5 conversions.

class BfmeMsgVJC
{
public:
	void bfmeRunVJC();
	void bfmeSetVJC(const char *k, void *v);
	void bfmeSet3VJC(const char *k, int v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

extern void *g_bfmeVJE;

class BfmeThingVJE
{
public:
	void bfmeGoVJE(BfmeMsgVJC *m, int downloadMin, int downloadMax, int topN, int periodType, int periodsPast, void *b);
	void bfmeSubVJE(BfmeMsgVJC *m, int n, void *b);
};

void BfmeThingVJE::bfmeGoVJE(BfmeMsgVJC *m, int downloadMin, int downloadMax, int topN, int periodType, int periodsPast, void *b)
{
	void *g = g_bfmeVJE;
	m->bfmeRunVJC();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVJC("TXN", g);
	bfmeSubVJE(m, topN, b);
	if (downloadMin > -1)
		m->bfmeSet3VJC("downloadMin", downloadMin);
	if (downloadMax > -1)
		m->bfmeSet3VJC("downloadMax", downloadMax);
	if (topN > -1)
		m->bfmeSet3VJC("topN", topN);
	if (periodType > -1)
		m->bfmeSet3VJC("periodType", periodType);
	if (periodsPast > -1)
		m->bfmeSet3VJC("periodsPast", periodsPast);
}
