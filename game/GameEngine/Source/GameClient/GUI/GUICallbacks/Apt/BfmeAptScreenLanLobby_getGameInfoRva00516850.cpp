// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?getGameInfoRva00516850@BfmeAptScreenLanLobby@@QAE_NHPAPAX@Z 0x00516850 239 B
// Name: the matched caller BfmeAptScreenLanLobby::rva00518610
// (BfmeAptScreenLanLobby_rva00518610.cpp) declares and calls it for both
// list-box messages; RET 8 and the INT3 after +0xEE close the extent.
//
// Looks up the game under list row `index`, clears it when TheLAN no longer
// knows it, and toggles the join button through the scripted-UI forwarder:
// enabled (bit 2 of +0x3D4 set) while the game has fewer players than open
// slots, disabled otherwise. Source shape that reproduces retail:
// - one `return ok` at the end with `ok = true` as the last statement of the
//   enable arm keeps `ok` in BL for the disable paths while the enable path
//   returns a literal 1 and reuses EBX for the constant 2;
// - the game test wraps the player-count compare, so the compare's else arm
//   gets its own disable copy (the +0x3D4 byte load hoisted above the jge)
//   while the missing-game path shares the first copy.

class GameWindow;
void *GadgetListBoxGetItemData(GameWindow *window, int row, int column);

struct Rva00685200Node;

class Rva00685200
{
public:
	bool has(Rva00685200Node *p);
};

class LANAPI;
extern LANAPI *TheLAN;

class GameInfo
{
public:
	int getNumPlayers(void) const;
};

class Rva0061EE90GameInfo
{
public:
	int countNonClosed(void) const;
};

class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int a, int b, int c, int d, int e, int f, int g, int h);
};

class BfmeR1078;
extern BfmeR1078 *g_bfmeR1078;
extern char g_bfmeFmtB1073[];
extern char g_bfmeFmt1078[];

class BfmeAptScreenLanLobby
{
public:
	bool getGameInfoRva00516850(int index, void **game);

private:
	char m_pad000[0x250];
	unsigned int m_field250;
	char m_pad254[0x160];
	GameWindow *m_field3B4;
	char m_pad3B8[0x1C];
	unsigned int m_field3D4;
};

bool BfmeAptScreenLanLobby::getGameInfoRva00516850(int index, void **game)
{
	bool ok = false;
	*game = GadgetListBoxGetItemData(m_field3B4, index, 0);
	if (!((Rva00685200 *)TheLAN)->has((Rva00685200Node *)*game))
		*game = 0;
	if (*game)
	{
		int players = ((GameInfo *)*game)->getNumPlayers();
		if (players < ((Rva0061EE90GameInfo *)*game)->countNonClosed())
		{
			if (!(m_field3D4 & 2))
			{
				((BfmeLevelAN *)g_bfmeR1078)->bfmeBuildAN(m_field250, (int)g_bfmeFmt1078, 0, 0, 0, 0, 0, 0);
				m_field3D4 |= 2;
			}
			ok = true;
		}
		else if (m_field3D4 & 2)
		{
			((BfmeLevelAN *)g_bfmeR1078)->bfmeBuildAN(m_field250, (int)g_bfmeFmtB1073, 0, 0, 0, 0, 0, 0);
			m_field3D4 &= ~2;
		}
	}
	else if (m_field3D4 & 2)
	{
		((BfmeLevelAN *)g_bfmeR1078)->bfmeBuildAN(m_field250, (int)g_bfmeFmtB1073, 0, 0, 0, 0, 0, 0);
		m_field3D4 &= ~2;
	}
	return ok;
}
