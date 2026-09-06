// ??0BfmeOwnBF@@QAE@XZ (identity unknown)
// partial score=0.88 date=2026-09-06
// 50/57 at exact size. Fourth member of the 0x0001B522 constructor family
// (0x0059DD90, 0x0059FAE0 and 0x0059D960 all landed with the rule "head
// pointer and the non-zero constant first, zero run after").
// This one inverts it: retail stores the head pointer FIRST, then two zeros,
// and only then materialises `mov ecx,0x1e` -- i.e. the constant appears
// LATER than MSVC wants it. Tried the 0x1e store at all six positions among
// the five zero stores; MSVC always hoists both constants above the whole run
// and defers the head-pointer immediate to the end. Everything from the first
// 0x1e store onward is byte-exact.
extern int g_s5Head005A06A0;

class BfmeBaseBF
{
public:
	BfmeBaseBF(void);
};

class BfmeOwnBF : public BfmeBaseBF
{
public:
	BfmeOwnBF(void);

	int *m_bfmeVfBF;
	int m_bfmeABF;
	unsigned char m_bfmePadBF;
	char m_bfmeFlagBF;
	unsigned char m_bfmePad2BF[2];
	int m_bfmeCBF;
	int m_bfmeDBF;
	int m_bfmeEBF;
	unsigned char m_bfmeMidBF[0x10];
	int m_bfmeFBF;
	int m_bfmeGBF;
	int m_bfmeHBF;
	int m_bfmeIBF;
};

BfmeOwnBF::BfmeOwnBF(void)
{
	m_bfmeVfBF = &g_s5Head005A06A0;
	m_bfmeGBF = 0;
	m_bfmeHBF = 0;
	m_bfmeEBF = 0x1e;
	m_bfmeDBF = 0;
	m_bfmeCBF = 0;
	m_bfmeIBF = 0;
	m_bfmeABF = 0x1e;
	m_bfmeFBF = -1;
	m_bfmeFlagBF = 1;
}
