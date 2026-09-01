// Open-BFME5 conversions.

class BfmeMsgVIX
{
public:
	void bfmeRunVIX();
	void bfmeSetVIX(const char *k, void *v);
	void bfmeSet2VIX(const char *k, void *a, void *b);
	void bfmeSet4VIX(const char *k, void *v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

extern void *g_bfmeFVIX;
extern void *g_bfmeGVIY;

void __stdcall bfmeGoVIX(BfmeMsgVIX *m, void *email, void *parentalEmail, void *countryCode, void *eaMail, void *thirdPartyMail)
{
	void *g = g_bfmeFVIX;
	m->bfmeRunVIX();
	m->m_bfme1c = 0x61636374;
	m->bfmeSetVIX("TXN", g);
	m->bfmeSetVIX("email", email);
	m->bfmeSetVIX("parentalEmail", parentalEmail);
	m->bfmeSetVIX("countryCode", countryCode);
	m->bfmeSet4VIX("eaMailFlag", eaMail);
	m->bfmeSet4VIX("thirdPartyMailFlag", thirdPartyMail);
}

class BfmeThingVIY
{
public:
	void bfmeGoVIY(BfmeMsgVIX *m, void *a, void *b, void *c, void *d, void *e);
	void bfmeSubVIY(BfmeMsgVIX *m, void *c, void *d);
};

void BfmeThingVIY::bfmeGoVIY(BfmeMsgVIX *m, void *a, void *b, void *c, void *d, void *e)
{
	void *g = g_bfmeGVIY;
	m->bfmeRunVIX();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVIX("TXN", g);
	m->bfmeSet2VIX("blobId", a, b);
	bfmeSubVIY(m, c, d);
	m->bfmeSetVIX("version", e);
}
