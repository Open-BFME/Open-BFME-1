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

extern void *g_bfmeVJC;

class BfmeThingVJC
{
public:
	void bfmeGoVJC(BfmeMsgVJC *m, int ratingMin, int ratingMax, int downloadMin, int downloadMax, void *a, void *b);
	void bfmeSubVJC(BfmeMsgVJC *m, void *a, void *b);
};

void BfmeThingVJC::bfmeGoVJC(BfmeMsgVJC *m, int ratingMin, int ratingMax, int downloadMin, int downloadMax, void *a, void *b)
{
	void *g = g_bfmeVJC;
	m->bfmeRunVJC();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVJC("TXN", g);
	bfmeSubVJC(m, a, b);
	if (ratingMin > -1)
		m->bfmeSet3VJC("ratingMin", ratingMin);
	if (ratingMax > -1)
		m->bfmeSet3VJC("ratingMax", ratingMax);
	if (downloadMin > -1)
		m->bfmeSet3VJC("downloadMin", downloadMin);
	if (downloadMax > -1)
		m->bfmeSet3VJC("downloadMax", downloadMax);
}

extern void *g_bfmeVJD;

class BfmeThingVJD
{
public:
	void bfmeGoVJD(BfmeMsgVJC *m, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *b);
	void bfmeSubVJD(BfmeMsgVJC *m, int n, void *b);
};

void BfmeThingVJD::bfmeGoVJD(BfmeMsgVJC *m, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *b)
{
	void *g = g_bfmeVJD;
	m->bfmeRunVJC();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVJC("TXN", g);
	bfmeSubVJD(m, topN, b);
	if (ratingMin > -1)
		m->bfmeSet3VJC("ratingMin", ratingMin);
	if (ratingMax > -1)
		m->bfmeSet3VJC("ratingMax", ratingMax);
	if (topN > 0)
		m->bfmeSet3VJC("topN", topN);
	if (periodType > -1)
		m->bfmeSet3VJC("periodType", periodType);
	if (periodsPast > -1)
		m->bfmeSet3VJC("periodsPast", periodsPast);
}
