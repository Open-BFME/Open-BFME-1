// ?bfmeSetupJG@BfmeThingJG@@QAEXHHHHH_N@Z
// partial score=0.9832 date=2026-10-29
// ?bfmeSetupJG@BfmeThingJG@@QAEXHHHHH_N@Z
// Tail fields 0x3C..0x50 as an inline-reset sub-struct with a nested float-trio zero(): source store order,
// no volatile. Residue: retail setne dl, ours setne al (+0x5F/+0x62).
class BfmeSubJG
{
public:
	void bfmeStartJG(int a, int b, float c);
	unsigned char m_bfmeGapJG[8];
};
struct TrioJG { float x; float y; float z; void zero() { x = 0.0f; y = 0.0f; z = 0.0f; } };
struct TailJG
{
	int a3c; int a40; char a44; char a45; bool a46; char pad; TrioJG t;
	void reset(bool f) { a3c = 0; a40 = 0; a45 = 0; a46 = f; t.zero(); }
};
class BfmeThingJG
{
public:
	void bfmeSetupJG(int p1, int p2, int p3, int p4, int p5, bool p6);

	unsigned char m_bfmeHeadJG[4];
	int m_bfme04JG;
	int m_bfme08JG;
	int m_bfme0cJG;
	BfmeSubJG m_bfmeSubJG;
	int m_bfme18JG;
	int m_bfme1cJG;
	int m_bfme20JG;
	char m_bfme24JG;
	unsigned char m_bfmePad0JG[3];
	int m_bfme28JG;
	unsigned char m_bfmeGap1JG[0xc];
	int m_bfme38JG;
	TailJG m_tail;
};

void BfmeThingJG::bfmeSetupJG(int p1, int p2, int p3, int p4, int p5, bool p6)
{
	int n = p2;
	if (n <= 1)
		n = 1;
	m_bfme04JG = n;
	m_bfme08JG = 0;
	m_bfme18JG = 0;
	m_bfme1cJG = 0;
	m_bfme20JG = 0;
	m_bfme28JG = 1;
	m_bfmeSubJG.bfmeStartJG(p3, p4, (float)p2);
	m_bfme0cJG = p5;
	if (p6)
		m_bfme38JG = 0;
	m_tail.reset(m_bfme0cJG != 0);
	m_bfme24JG = 1;
}
