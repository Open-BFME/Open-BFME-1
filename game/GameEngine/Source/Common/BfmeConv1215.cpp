// Open-BFME5 conversions.

class BfmeE1215
{
public:
	virtual void bfmeV1215A();
	virtual void bfmeV1215B();
	unsigned m_bfme04;
};

class BfmeA1215
{
public:
	int m_bfme00;
	int m_bfme04;
	BfmeE1215 **m_bfme08;
	char m_bfmePad0c[0x60 - 0x0c];
	BfmeE1215 **m_bfme60;
};

class BfmeG1215
{
public:
	int m_bfme00;
	int m_bfme04;
};

struct Rva00899560Pool;

extern Rva00899560Pool *g_rva01337810GcRoots;

// Retail 0x008D0B00 and 0x008A30C0 are the gen-asm dump bodies
// (game/gen_asm/d_008cb600.asm and game/gen_asm/d_008a0830.asm); the
// bfmeStep1215* spellings were pins for them, not definitions.  The owners are
// address-derived void() symbols, so reference those and cast at the calls.
extern void d_008d0b00();
extern void d_008a30c0();

typedef void (__cdecl *Rva008D0B00Step)(BfmeA1215 *a, const unsigned char **b);
typedef void (__fastcall *Rva008A30C0Idle)(BfmeG1215 *self);

void bfmeGo1215(BfmeA1215 *a, const unsigned char **b)
{
	const unsigned char *p;
	unsigned char c;
	BfmeE1215 *e;
	BfmeG1215 *g;

	p = *b;
	c = *p;
	*b = p + 1;
	e = a->m_bfme60[c];
	a->m_bfme08[a->m_bfme00] = e;
	++a->m_bfme00;
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1215A();
	(reinterpret_cast<Rva008D0B00Step>(d_008d0b00))(a, b);
	e = a->m_bfme08[a->m_bfme00 - 1];
	if (!((unsigned char)(e->m_bfme04 >> 30) & 1))
		e->bfmeV1215B();
	--a->m_bfme00;
	g = (BfmeG1215 *)g_rva01337810GcRoots;
	if (g->m_bfme04 && a->m_bfme00 == 0)
		(reinterpret_cast<Rva008A30C0Idle>(d_008a30c0))(g);
}
