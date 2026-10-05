// Open-BFME5 conversions.

extern char g_bfmeEmptyUVA[];

// Retail 0x007E8640: the bounded FESL string copy both helpers call.
void Rva007E8640Copy(char *dst, unsigned n, const char *src);

class BfmeThingUVA
{
public:
	void bfmeGoUVA(const char *a, const char *b, const char *c);
	char m_bfmePad[4];
	char *m_bfmeBuf;
};

void BfmeThingUVA::bfmeGoUVA(const char *a, const char *b, const char *c)
{
	Rva007E8640Copy(m_bfmeBuf + 0xa0, 0x41, a);
	Rva007E8640Copy(m_bfmeBuf + 0x101, 0x41, b ? b : g_bfmeEmptyUVA);
	Rva007E8640Copy(m_bfmeBuf + 0x142, 0x41, c ? c : g_bfmeEmptyUVA);
}

// Retail .rdata at VA 0x0111C2A0: "false" including its NUL (6 bytes).
// The diagnostic callers pass its address; no EA symbol name is proven.
extern const char g_rva0111C2A0[] = "false";

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

// Retail 0x00807AB0: the U2 diagnostic module's tagged-value formatter.
// Spelled exactly as the body the ledger owns at that address
// (?Rva00807AB0@@YAHPADPBX@Z, Y2Rva00807900Module.cpp): the tagged word
// arrives by pointer.
int Rva00807AB0(char *out, const void *v);

int bfmeGoUVB(BfmeRecUVB *r, char *out)
{
	if (r->m_bfmeKind == 0) {
		void *v = *(void **)r->m_bfmeText;
		*(void **)&r = v;
		return Rva00807AB0(out, (const void *)&r);
	}
	if (r->m_bfmeKind == 1) {
		*out = '$';
		Rva007E8640Copy(out + 1, 0x13, r->m_bfmeText);
		return 1;
	}
	Rva007EB810Get()->fail(g_rva0111C2A0, "\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp", 0x2e);
	return 0;
}
