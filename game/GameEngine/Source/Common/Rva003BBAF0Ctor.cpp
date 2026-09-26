// cl: /DNDEBUG /MD /O2
// Open-BFME5: base unsigned*0.03f clamp shared by BfmeRectVNE / VNF / VNG.
// Retail 0x003BBAF0, 66 bytes. Return-this is materialised before the <1 clamp.

extern void *g_bfmeVtaVNE;

class BfmeBaseVN
{
public:
	BfmeBaseVN *bfmeInitVN(unsigned w, char f);

	void *volatile m_bfme00;
	unsigned m_bfme04;
	char m_bfme08;
};

// ?bfmeInitVN@BfmeBaseVN@@QAEPAV1@ID@Z
BfmeBaseVN *BfmeBaseVN::bfmeInitVN(unsigned w, char f)
{
	m_bfme00 = &g_bfmeVtaVNE;
	m_bfme08 = f;
	m_bfme04 = (int)((float)w * 0.03f);
	BfmeBaseVN *self = this;
	if (m_bfme04 < 1)
		m_bfme04 = 1;
	return self;
}
