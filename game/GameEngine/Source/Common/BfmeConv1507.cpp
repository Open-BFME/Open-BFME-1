// Open-BFME5 conversions.

extern void *g_bfmeVtaVNE;
extern void *g_bfmeVtbVNE;

// Retail 0x003BBF70 is a constructor, not an init method: it installs the
// base vftable, the base fields, then the derived vftable, and returns this.
// Its callers (Glo012F1024Item::j_00015e42 at 0x003ADED0) reach it from a
// new-expression whose EH state guards the allocation, which only a
// constructor call produces.
class BfmeRectVNE
{
public:
	BfmeRectVNE(unsigned w, unsigned h, char f);
	void *volatile m_bfme00;
	unsigned m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
	unsigned m_bfme0c;
};

// ??0BfmeRectVNE@@QAE@IID@Z
BfmeRectVNE::BfmeRectVNE(unsigned w, unsigned h, char f)
{
	m_bfme00 = &g_bfmeVtaVNE;
	m_bfme08 = f;
	m_bfme04 = (int)((float)w * 0.03f);
	if (m_bfme04 < 1)
		m_bfme04 = 1;
	m_bfme00 = &g_bfmeVtbVNE;
	m_bfme0c = (int)((float)h * 0.03f);
}
