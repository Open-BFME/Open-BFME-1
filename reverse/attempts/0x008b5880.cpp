// ??0BfmeOwnBH@@QAE@PAVBfmeHostBH@@@Z (identity unknown)
// partial score=0.82 date=2026-09-06
// 40/48 at exact size. The base constructor with its two arguments, the store
// set and the three-step chain through the parameter are all modelled.
// Residue is the same wall as 0x008087D0: retail loads the parameter into ecx
// BEFORE the zero constant is materialised and keeps it there across the
// stores, while MSVC emits the zeros first and loads the parameter late into
// eax. That also drags the chain registers one step out of line.
extern int g_bfmeVftBH;

class BfmeInnerBH
{
public:
	unsigned char m_bfmeHeadBH[4];
	int m_bfmeValueBH;
};

class BfmeMidBH
{
public:
	unsigned char m_bfmeHeadBH[0xc];
	BfmeInnerBH *m_bfmeInnerBH;
};

class BfmeHostBH
{
public:
	unsigned char m_bfmeHeadBH[0x50];
	BfmeMidBH *m_bfmeMidBH;
};

class BfmeBaseBH
{
public:
	BfmeBaseBH(int kind, int size);
};

class BfmeOwnBH : public BfmeBaseBH
{
public:
	BfmeOwnBH(BfmeHostBH *host);

	int *m_bfmeVfBH;
	unsigned char m_bfmeHeadBH[0x1c];
	int m_bfmeCBH;
	int m_bfmeABH;
	int m_bfmeBBH;
};

BfmeOwnBH::BfmeOwnBH(BfmeHostBH *host)
	: BfmeBaseBH(0x15, 8)
{
	m_bfmeABH = 0;
	m_bfmeVfBH = &g_bfmeVftBH;
	m_bfmeBBH = 0;
	m_bfmeCBH = host->m_bfmeMidBH->m_bfmeInnerBH->m_bfmeValueBH;
}
