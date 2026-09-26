// Open-BFME5 conversions.

class BfmeMsgVIX
{
public:
	void bfmeRunVIX();
	void bfmeSetVIX(const char *k, void *v);
	void bfmeSet2VIX(const char *k, void *a, void *b);
	void bfmeSet4VIX(const char *k, void *v);
	void rva007E8EF0(const char *k, void *v);
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

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate(int size, int flags);
	virtual void release(void *block, int flags);
};

struct Rva007EB810Diag
{
public:
	virtual void v0();
	virtual void v1();
	virtual void __cdecl assertValue(void *value, const char *message);
	virtual void fail(const char *expr, const char *file, int line);
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *one, void *two);
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeErr;
};

extern Rva007EB810Diag *Rva007EB810Get();
extern void *bfmeGo929C();
void rva007FF100Encode(unsigned int length, const char *source, void *destination);

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

void BfmeThingVIY::bfmeSubVIY(BfmeMsgVIX *m, void *c, void *d)
{
	Rva007EFFC0Allocator *allocator = (Rva007EFFC0Allocator *)bfmeGo929C();
	unsigned int length = (unsigned int)d;
	unsigned int size = ((length + 2) / 3) * 4 + 1;
	void *content = allocator->allocate(size, 2);
	if (content == 0)
	{
		Rva007EB810Diag *diag = Rva007EB810Get();
		diag->assertValue(content, "--- out of memory\n");
		Rva007EB810Get()->fail("false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\blobservice.cpp",
			0x17c);
		return;
	}
	rva007FF100Encode(length, (const char *)c, content);
	m->rva007E8EF0("content", content);
	((Rva007EFFC0Allocator *)bfmeGo929C())->release(content, 0);
	((BfmeThingCIB *)m)->bfmeGoCIB((void *)"size", d);
}
