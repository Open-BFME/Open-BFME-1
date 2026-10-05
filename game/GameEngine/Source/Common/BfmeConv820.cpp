// cl: /O1
struct BfmeRefEMI
{
	unsigned short m_bfmeCount;
};

// TU-local view of the Apt allocator-hook pair table owned by Apt.cpp; the
// global itself is declared under its canonical spelling so it links.
struct BfmeStringPool3AF0
{
	void *m_bfmeF0;
	void (__cdecl *m_bfmeF1)(BfmeRefEMI *r);
};

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
struct BfmeHdrVKI;
class BfmeStrVKI { public: BfmeHdrVKI *m_bfme00; };
struct BfmeBuf1233;
struct BfmeStr1233 { BfmeBuf1233 *m_bfme00; };
class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;

BfmeStrVKI g_String012D5140 = { (BfmeHdrVKI *)&g_rva012D5298Empty };
extern BfmeStr1233 g_bfmeStr1233;

void bfmeGoEMIa()
{
	BfmeRefEMI *r = (BfmeRefEMI *)g_String012D5140.m_bfme00;
	if (--r->m_bfmeCount == 0)
		g_rva01337A30AllocPair->m_bfmeF1(r);
}

void bfmeGoEMIb()
{
	BfmeRefEMI *r = (BfmeRefEMI *)g_bfmeStr1233.m_bfme00;
	if (--r->m_bfmeCount == 0)
		g_rva01337A30AllocPair->m_bfmeF1(r);
}
