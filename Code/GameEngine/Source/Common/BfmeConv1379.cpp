// Open-BFME5 conversions.

class BfmeMsgVIW
{
public:
	void bfmeRunVIW();
	void bfmeSetVIW(const char *k, void *v);
	void bfmeSet2VIW(const char *k, void *a, void *b);
	void bfmeSet3VIW(const char *k, int v);
	void bfmeSet4VIW(const char *k, void *v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

extern void *g_bfmeAVIW;
extern void *g_bfmeBVIW;
extern void *g_bfmeCVIW;
extern void *g_bfmeDVIW;
extern void *g_bfmeEVIW;

void __stdcall bfmeGoAVIW(BfmeMsgVIW *m, void *a, void *b)
{
	void *g = g_bfmeAVIW;
	m->bfmeRunVIW();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVIW("TXN", g);
	m->bfmeSet2VIW("blobId", a, b);
}

void __stdcall bfmeGoBVIW(BfmeMsgVIW *m, void *a, void *b)
{
	void *g = g_bfmeBVIW;
	m->bfmeRunVIW();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVIW("TXN", g);
	m->bfmeSet2VIW("blobId", a, b);
}

void __stdcall bfmeGoCVIW(BfmeMsgVIW *m, void *a, void *b)
{
	void *g = g_bfmeCVIW;
	m->bfmeRunVIW();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVIW("TXN", g);
	m->bfmeSet2VIW("blobId", a, b);
}

void __stdcall bfmeGoDVIW(BfmeMsgVIW *m, void *a, void *b, int r)
{
	void *g = g_bfmeDVIW;
	m->bfmeRunVIW();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVIW("TXN", g);
	m->bfmeSet2VIW("blobId", a, b);
	m->bfmeSet3VIW("rating", r);
}

void __stdcall bfmeGoEVIW(BfmeMsgVIW *m, void *a, void *b)
{
	void *g = g_bfmeEVIW;
	m->bfmeRunVIW();
	m->m_bfme1c = 0x61636374;
	m->bfmeSetVIW("TXN", g);
	m->bfmeSet4VIW("eaMailFlag", a);
	m->bfmeSet4VIW("thirdPartyMailFlag", b);
}
