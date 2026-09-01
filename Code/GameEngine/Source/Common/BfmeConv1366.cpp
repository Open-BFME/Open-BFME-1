// Open-BFME5 conversions.

extern "C" long __ftol2(double v);

struct BfmePtVHP
{
	float m_bfmeX;
	float m_bfmeY;
};

class BfmeDrawVHP
{
public:
	virtual void bfmeSlot00VHP();
	virtual void bfmeSlot04VHP();
	virtual void bfmeSlot08VHP();
	virtual void bfmeSlot0CVHP();
	virtual void bfmeSlot10VHP();
	virtual void bfmeSlot14VHP();
	virtual void bfmeSlot18VHP();
	virtual void bfmeSlot1CVHP();
	virtual void bfmeSlot20VHP();
	virtual void bfmeSlot24VHP(int x0, int y0, int x1, int y1);
};

extern BfmeDrawVHP *g_bfmeDrawVHP;

void __cdecl bfmeLineVHP(const BfmePtVHP *a, const BfmePtVHP *b)
{
	g_bfmeDrawVHP->bfmeSlot24VHP((int)(a->m_bfmeX + 0.5f), (int)(a->m_bfmeY + 0.5f),
		(int)(b->m_bfmeX + 0.5f), (int)(b->m_bfmeY + 0.5f));
}
