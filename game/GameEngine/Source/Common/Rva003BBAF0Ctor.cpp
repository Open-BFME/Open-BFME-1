// cl: /DNDEBUG /MD /O2
// Open-BFME5: base unsigned*0.03f clamp shared by BfmeRectVNE / VNF / VNG.
// Retail 0x003BBAF0, 66 bytes. Return-this is materialised before the <1 clamp.

extern "C" void *__identifier("??_7BfmeBaseVNH@@6B@");
#define g_bfmeVtaVNE __identifier("??_7BfmeBaseVNH@@6B@")

// Retail 0x003BB860 (31 bytes): the scaling as its own file static. The
// constructors inline it, but VC7.1 still emits a copy that takes w in EAX.
static unsigned rva003BB860Scale(unsigned w)
{
	return (int)((float)w * 0.03f);
}

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
	m_bfme04 = rva003BB860Scale(w);
	BfmeBaseVN *self = this;
	if (m_bfme04 < 1)
		m_bfme04 = 1;
	return self;
}
