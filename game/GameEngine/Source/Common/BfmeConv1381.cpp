// cl: /GS
// Open-BFME5 conversions.

extern "C" int __cdecl sprintf(char *buf, const char *fmt, ...);

class BfmeMsgVJA
{
public:
	void bfmeRunVJA();
	void bfmeSetVJA(const char *k, void *v);
	void bfmeSet3VJA(const char *k, int v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

extern void *g_bfmeVJA;

void __stdcall bfmeGoVJA(BfmeMsgVJA *m, void *name, void **kw, int n, int max)
{
	char buf[0x20];
	void *g = g_bfmeVJA;
	m->bfmeRunVJA();
	m->m_bfme1c = 0x61636374;
	m->bfmeSetVJA("TXN", g);
	m->bfmeSetVJA("name", name);
	m->bfmeSet3VJA("maxSuggestions", max);
	for (int i = 0; i < n; ++i)
	{
		sprintf(buf, "keywords.%d", i);
		m->bfmeSetVJA(buf, kw[i]);
	}
	m->bfmeSet3VJA("keywords.[]", n);
}

extern void *g_bfmeVJB;

void __stdcall bfmeGoVJB(BfmeMsgVJA *m, void *name, void **kw, int n, int max)
{
	char buf[0x20];
	void *g = g_bfmeVJB;
	m->bfmeRunVJA();
	m->m_bfme1c = 0x61636374;
	m->bfmeSetVJA("TXN", g);
	m->bfmeSetVJA("name", name);
	m->bfmeSet3VJA("maxSuggestions", max);
	for (int i = 0; i < n; ++i)
	{
		sprintf(buf, "keywords.%d", i);
		m->bfmeSetVJA(buf, kw[i]);
	}
	m->bfmeSet3VJA("keywords.[]", n);
}
