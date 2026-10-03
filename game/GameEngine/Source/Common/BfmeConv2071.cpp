// The divisor at 0x012BB1CC is the .bss int the only definition of this
// address spells g_006fb9c0 (W3DDevice/GameClient/Gen_006fb9c0_Ftol.cpp, whose
// setter at 0x006FB9C0 stores (int)float into it).  Both spellings share the
// address in dir32_addresses.csv; only that one has a definition.
extern int g_006fb9c0;

// The sub-object start retail calls through the ILT thunk 0x0002A1B2, which
// jumps to ParabolicEase::setEaseTimes (0x00094970, Common/
// ParabolicEaseSetEaseTimesBFME.cpp).  The argument types are this TU's:
// two ints and a float pushed raw, which is why the call goes through the
// thunk's own address rather than that name.
extern void j_0002a1b2();

class BfmeSubGT
{
public:
	unsigned char m_bfmeGapGT[8];
};

class BfmeSetupGT
{
public:
	void bfmeInitGT(int p1, int p2, int p3, int p4, int p5, int p6);

	unsigned char m_bfmeHeadGT[0x1ac];
	int m_bfme1acGT;
	int m_bfme1b0GT;
	int m_bfme1b4GT;
	int m_bfme1b8GT;
	int m_bfme1bcGT;
	BfmeSubGT m_bfmeSubGT;
	char m_bfme1c8GT;
	unsigned char m_bfmePad0GT[3];
	int m_bfme1ccGT;
	unsigned char m_bfmeGap1GT[8];
	int m_bfme1d8GT;
	char m_bfme1dcGT;
	unsigned char m_bfmeGap2GT[0x21e7];
	int m_bfme23c4GT;
};

void BfmeSetupGT::bfmeInitGT(int p1, int p2, int p3, int p4, int p5, int p6)
{
	m_bfme1c8GT = 1;

	int a = p3;

	if (a < 1)
		a = 0;

	m_bfme1bcGT = a / g_006fb9c0;

	if (m_bfme1bcGT < 1)
		m_bfme1bcGT = 0;

	if (p2 < 1)
		p2 = 1;

	m_bfme1acGT = p2 / g_006fb9c0;

	if (m_bfme1acGT < 1)
		m_bfme1acGT = 1;

	m_bfme1dcGT = 1;
	m_bfme1ccGT = p1;
	m_bfme1b0GT = 0;
	m_bfme1b4GT = m_bfme23c4GT;
	m_bfme1b8GT = m_bfme23c4GT;

	union { void (*raw)(); void (BfmeSubGT::*member)(int, int, float); } start;
	start.raw = ::j_0002a1b2;
	(m_bfmeSubGT.*start.member)(p4, p5, (float)p2);

	m_bfme1d8GT = p6;
}
