// ?bfmeGoEQD@BfmeHostEQD@@QAEXHH@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// exact size 45/45; ONE byte differs: the unwind esp-marker slot.
// retail 89 64 24 14 ([esp+0x14], param-1 home slot); MSVC 89 64 24 18 ([esp+0x18], param-2 slot).
// Pin needed: ?bfmeInnerEQD@BfmeTargetEQD@@QAEXUBfmePairEQD@@HH@Z,0x0004461B,pin
struct BfmePairEQD
{
	BfmePairEQD(const BfmePairEQD &other) throw();
	~BfmePairEQD() throw();
	int m_bfmeFirstEQD;
	int m_bfmeSecondEQD;
};

inline BfmePairEQD::BfmePairEQD(const BfmePairEQD &other) throw()
	: m_bfmeFirstEQD(other.m_bfmeFirstEQD), m_bfmeSecondEQD(other.m_bfmeSecondEQD)
{
}

inline BfmePairEQD::~BfmePairEQD() throw()
{
}

struct BfmeTargetEQD
{
	void bfmeInnerEQD(BfmePairEQD pair, int a, int b);
};

struct BfmeHostEQD
{
	void bfmeGoEQD(int a, int b);
	BfmeTargetEQD *m_bfmeTargetEQD;
	BfmePairEQD m_bfmePairEQD;
};

void BfmeHostEQD::bfmeGoEQD(int a, int b)
{
	if (m_bfmeTargetEQD != 0)
		m_bfmeTargetEQD->bfmeInnerEQD(m_bfmePairEQD, a, b);
}
