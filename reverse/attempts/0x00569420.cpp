// ?d_00569420@@YAXXZ
// partial score=0.96 date=2026-09-08
struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadEAI[0xa9e];
	char m_bfmeFlagEAI;
};

struct BfmeGateEAI
{
	char bfmeCheckEAI();
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadEAI[0x10c];
	int m_bfmeModeEAI;
};

class BfmeWinEAI
{
public:
	virtual void bfmeSlot0EAI(int a);
	virtual void bfmeSlot1EAI();
	virtual void bfmeSlot2EAI();
	virtual void bfmeSlot3EAI();
	virtual void bfmeSlot4EAI(int a);
	virtual void bfmeSlot5EAI();
};

class Shell40D9
{
public:
	BfmeWinEAI *bfmeTopEAI();
};

extern Rva006C9270GlobalData *TheWritableGlobalData;
extern BfmeGateEAI *g_bfmeGateEAI;
extern Rva00367E30Logic *TheBfmeGameLogic;
extern Shell40D9 *TheShell;

void __cdecl bfmeApplyEAI(int a, int b, int c);

class BfmeAptScreenQuitMenu
{
public:
	void _bfme_saveMenu(const char *unused);
};

void BfmeAptScreenQuitMenu::_bfme_saveMenu(const char *unused)
{
	char flag = (TheWritableGlobalData->m_bfmeFlagEAI == 0);

	if (g_bfmeGateEAI->bfmeCheckEAI())
		flag = (flag == 0);

	if (flag)
	{
		int mode = TheBfmeGameLogic->m_bfmeModeEAI;

		int n;

		if (mode == 1 || mode == 5)
			n = 4;
		else
			n = (mode == 2) + 1;

		bfmeApplyEAI(3, n, 1);
	}
	else
	{
		BfmeWinEAI *win = TheShell->bfmeTopEAI();

		win->bfmeSlot0EAI(0);
		win->bfmeSlot4EAI(0);
		win->bfmeSlot5EAI();
	}
}
