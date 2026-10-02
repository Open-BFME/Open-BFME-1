// Open-BFME5 conversions.

extern char g_bfmeEmptyUVA[];

void bfmeCopyUVA(char *dst, unsigned n, const char *src);

class BfmeThingUVA
{
public:
	void bfmeGoUVA(const char *a, const char *b, const char *c);
	char m_bfmePad[4];
	char *m_bfmeBuf;
};

void BfmeThingUVA::bfmeGoUVA(const char *a, const char *b, const char *c)
{
	bfmeCopyUVA(m_bfmeBuf + 0xa0, 0x41, a);
	bfmeCopyUVA(m_bfmeBuf + 0x101, 0x41, b ? b : g_bfmeEmptyUVA);
	bfmeCopyUVA(m_bfmeBuf + 0x142, 0x41, c ? c : g_bfmeEmptyUVA);
}

extern char g_bfmeFileUVB[];
extern char g_bfmeMsgUVB[];

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get(void);

struct BfmeRecUVB
{
	char m_bfmePad[4];
	int m_bfmeKind;
	char m_bfmeText[4];
};

int bfmeConvertUVB(char *out, void **v);
void bfmeCopyUVB(char *dst, unsigned n, const char *src);

int bfmeGoUVB(BfmeRecUVB *r, char *out)
{
	if (r->m_bfmeKind == 0) {
		void *v = *(void **)r->m_bfmeText;
		*(void **)&r = v;
		return bfmeConvertUVB(out, (void **)&r);
	}
	if (r->m_bfmeKind == 1) {
		*out = '$';
		bfmeCopyUVB(out + 1, 0x13, r->m_bfmeText);
		return 1;
	}
	Rva007EB810Get()->fail(g_bfmeMsgUVB, g_bfmeFileUVB, 0x2e);
	return 0;
}
