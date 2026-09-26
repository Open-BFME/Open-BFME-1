// Open-BFME5 conversions.

extern void *g_bfmeVtaVNE;
extern void *g_bfmeVtbVNE;

class BfmeRectVNE
{
public:
	BfmeRectVNE *bfmeInitVNE(unsigned w, unsigned h, char f);
	void *volatile m_bfme00;
	unsigned m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
	unsigned m_bfme0c;
};

BfmeRectVNE *BfmeRectVNE::bfmeInitVNE(unsigned w, unsigned h, char f)
{
	m_bfme00 = &g_bfmeVtaVNE;
	m_bfme08 = f;
	m_bfme04 = (int)((float)w * 0.03f);
	if (m_bfme04 < 1)
		m_bfme04 = 1;
	m_bfme00 = &g_bfmeVtbVNE;
	m_bfme0c = (int)((float)h * 0.03f);
	return this;
}
