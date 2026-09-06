// ?bfmeGetFN@@YAPAVBfmeStaticFN@@XZ (identity unknown)
// partial score=0.85 date=2026-09-06
// 108/104 with the per-file /EHs-c- directive; 142 without it (MSVC wraps the
// guarded construction in an SEH frame that retail does not have).
// Head of a 17-body family at 0x005DEF70 0x005DF120 0x005DF480 0x005DF510
// 0x005E0820 0x005E08B0 0x005E0A70 0x005E0CB0 0x005E0E60 0x005E1010 0x005E11C0
// 0x005E14F0 0x005E1690 0x005E1830 0x005E19B0 0x005E1B50 and 0x005DF2D0.
// cl: /EHs-c-
extern "C" void *bfmeVtFN[];

class BfmeStaticFN;

extern void **g_bfmeSrcAFN;
extern void ***g_bfmeSrcBFN;
extern BfmeStaticFN *g_bfmeHeadFN;

class BfmeStaticFN
{
public:
	BfmeStaticFN(void)
	{
		m_bfmeBFN = **g_bfmeSrcBFN;
		m_bfmeAFN = *g_bfmeSrcAFN;
		m_bfmeNextFN = g_bfmeHeadFN;
		g_bfmeHeadFN = this;
		m_bfmeVtFN = bfmeVtFN;
	}
	~BfmeStaticFN(void);

	void *m_bfmeVtFN;
	void *m_bfmeAFN;
	void *m_bfmeBFN;
	BfmeStaticFN *m_bfmeNextFN;
};

BfmeStaticFN *bfmeGetFN(void)
{
	static BfmeStaticFN s_bfmeInstanceFN;
	return &s_bfmeInstanceFN;
}
