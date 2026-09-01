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

class BfmeLogUVB
{
public:
	virtual void bfmeV0UVB() = 0;
	virtual void bfmeV1UVB() = 0;
	virtual void bfmeV2UVB() = 0;
	virtual void bfmeWarnUVB(const char *msg, const char *file, int line) = 0;
};

BfmeLogUVB *bfmeGetLogUVB(void);

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
	bfmeGetLogUVB()->bfmeWarnUVB(g_bfmeMsgUVB, g_bfmeFileUVB, 0x2e);
	return 0;
}
