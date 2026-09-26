// ??0BfmeOwnBD@@QAE@PAX@Z (identity unknown)
// partial score=0.8 date=2026-09-06
// 33/41 at exact size. Constructor over an empty base with the base ctor at
// 0x007E86B0 and the head pointer g_bfmeVft994C at 0x011296B0.
// Residue: retail loads the parameter into ecx BEFORE the zero run, so ecx
// and eax are both live across it, and stores it last; MSVC emits the zeros
// first and only then loads the parameter into eax. Tried six store
// permutations and a named local for the parameter declared at the top; the
// load never moves ahead of the zeros. Contrast 0x0059DD90 and 0x0059FAE0,
// where putting a CONSTANT store before the zero run does hoist it -- a
// parameter load does not respond the same way.
extern char g_bfmeVft994C[];

class BfmeBaseBD
{
public:
	BfmeBaseBD(void);
};

class BfmeOwnBD : public BfmeBaseBD
{
public:
	BfmeOwnBD(void *owner);

	char *m_bfmeVfBD;
	int m_bfmeABD;
	int m_bfmeBBD;
	int m_bfmeCBD;
	void *m_bfmeOwnerBD;
	int m_bfmeDBD;
};

BfmeOwnBD::BfmeOwnBD(void *owner)
{
	m_bfmeBBD = 0;
	m_bfmeCBD = 0;
	m_bfmeABD = 0;
	m_bfmeDBD = 0;
	m_bfmeVfBD = g_bfmeVft994C;
	m_bfmeOwnerBD = owner;
}
