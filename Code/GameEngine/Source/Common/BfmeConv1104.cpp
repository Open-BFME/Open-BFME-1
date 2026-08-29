// Open-BFME5 conversions.

struct BfmeC1104;

struct BfmeVt1104
{
	char m_bfmePad[0x114];
	void (__stdcall *m_bfme114)(BfmeC1104 *self, int a, int b, int c);
};

struct BfmeC1104
{
	BfmeVt1104 *m_bfmeVt;
};

extern BfmeC1104 *g_bfmeC1104;
extern int g_bfmeA1104;
extern int g_bfmeB1104;

void __cdecl bfmeGo1104A(int a)
{
	g_bfmeC1104->m_bfmeVt->m_bfme114(g_bfmeC1104, a, 6, 2);
	g_bfmeB1104++;
	g_bfmeA1104++;
	g_bfmeC1104->m_bfmeVt->m_bfme114(g_bfmeC1104, a, 5, 2);
	g_bfmeB1104++;
	g_bfmeA1104++;
	g_bfmeC1104->m_bfmeVt->m_bfme114(g_bfmeC1104, a, 0xa, 0);
	g_bfmeB1104++;
	g_bfmeA1104++;
	g_bfmeC1104->m_bfmeVt->m_bfme114(g_bfmeC1104, a, 7, 1);
	g_bfmeB1104++;
	g_bfmeA1104++;
}
