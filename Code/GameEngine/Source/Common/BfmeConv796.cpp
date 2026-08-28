struct BfmeRefDYE
{
	unsigned char m_bfmeHead[4];
	long m_bfmeRef;
};

extern "C" __declspec(dllimport) long __stdcall bfmeIncDYE(long *p);

struct BfmeThingDYE
{
	BfmeThingDYE *bfmeGoDYE(BfmeThingDYE *o);
	void bfmeBaseDYE(BfmeThingDYE *o);
	unsigned char m_bfmeHead[4];
	BfmeRefDYE *m_bfmeP;
};

BfmeThingDYE *BfmeThingDYE::bfmeGoDYE(BfmeThingDYE *o)
{
	bfmeBaseDYE(o);
	BfmeRefDYE *p = o->m_bfmeP;
	m_bfmeP = p;
	if (p)
		bfmeIncDYE(&p->m_bfmeRef);
	return this;
}

extern "C" __declspec(dllimport) int __cdecl bfmeCmpDYF(const char *a, const char *b);
extern "C" unsigned char bfmeStrDYF[];

class BfmeGlobDYF
{
public:
	void bfmeSetDYF(bool on);
};

extern BfmeGlobDYF *g_bfmeObjDYF;

void bfmeGoDYF(const char *s)
{
	g_bfmeObjDYF->bfmeSetDYF(bfmeCmpDYF(s, (const char *)bfmeStrDYF) == 0);
}

extern "C" __declspec(dllimport) int __cdecl bfmeScanDYG(const char *s, const char *fmt, void *out);
extern "C" unsigned char bfmeFmtDYG[];

int bfmeGoDYG(void *s)
{
	if (!s)
		return -1;
	if (bfmeScanDYG((const char *)s, (const char *)bfmeFmtDYG, &s) == 1)
		return (int)s;
	return -1;
}
