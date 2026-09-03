// cl: /DNDEBUG /MD /O2
// Open-BFME5: sibling of BfmeRectVNE / BfmeBoxVNF. Same base vftable and
// unsigned*0.03f clamp, but +0xC holds a refcounted pointer instead of a
// second scaled axis. Retail 0x003BBB70, 95 bytes.

extern void *g_bfmeVtaVNE;
extern void *g_bfmeVtbVNG;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long *addend);

struct BfmeRefVNG
{
	void *m_referent;
};

class BfmeRectVNG
{
public:
	BfmeRectVNG *bfmeInitVNG(unsigned w, const BfmeRefVNG &ref, char f);

	void *volatile m_bfme00;
	unsigned m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
	void *m_bfme0c;
};

// ?bfmeInitVNG@BfmeRectVNG@@QAEPAV1@IABUBfmeRefVNG@@D@Z
BfmeRectVNG *BfmeRectVNG::bfmeInitVNG(unsigned w, const BfmeRefVNG &ref, char f)
{
	m_bfme00 = &g_bfmeVtaVNE;
	m_bfme08 = f;
	m_bfme04 = (int)((float)w * 0.03f);
	if (m_bfme04 < 1)
		m_bfme04 = 1;
	m_bfme00 = &g_bfmeVtbVNG;
	m_bfme0c = ref.m_referent;
	if (m_bfme0c != 0)
		InterlockedIncrement((long *)((char *)m_bfme0c + 4));
	return this;
}
