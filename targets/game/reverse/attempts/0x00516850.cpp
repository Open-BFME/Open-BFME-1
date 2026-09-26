// ?d_00516850@@YAXXZ
// partial score=0.43 date=2026-09-21
// ?bfmeGo1078A@BfmeQ1078@@QAE_NHPAPAVGameInfo@@@Z [retail body 0x00516850]
// Address-derived: same BfmeQ layout family as BfmeConv1072.cpp/BfmeConv1073.cpp
// (fields m_bfme250 @0x250 and m_bfme3d4 @0x3d4 match those siblings exactly).
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class GameWindow;
void *GadgetListBoxGetItemData(GameWindow *window, int row, int column);

class Rva00685200Node;

class Rva00685200
{
	char pad[0x0C];
	Rva00685200Node *m_0C;

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

class BfmeX1078;

class BfmeR1078
{
public:
	void bfmeRun1078(BfmeX1078 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1078 *g_bfmeR1078;
extern char g_bfmeFmtB1073[];
extern char g_bfmeFmt1078[];

class BfmeQ1078
{
public:
	bool bfmeGo1078A(int row, GameInfo **outItem);

private:
	char m_bfmePad[0x250];
	BfmeX1078 *m_bfme250;
	char m_bfmePad1[0x160];
	GameWindow *m_bfme3b4;
	char m_bfmePad2[0x1C];
	int m_bfme3d4;
};

bool BfmeQ1078::bfmeGo1078A(int row, GameInfo **outItem)
{
	bool result = false;
	GameInfo *item = (GameInfo *)GadgetListBoxGetItemData(m_bfme3b4, row, 0);
	*outItem = item;

	if (!((Rva00685200 *)TheLAN)->has((Rva00685200Node *)item)) {
		*outItem = 0;
		if (m_bfme3d4 & 2) {
			g_bfmeR1078->bfmeRun1078(m_bfme250, g_bfmeFmtB1073, 0, 0, 0, 0, 0, 0);
			m_bfme3d4 &= ~2;
		}
		return result;
	}

	if (item) {
		int numPlayers = item->getNumPlayers();
		int nonClosed = ((Rva0061EE90GameInfo *)item)->countNonClosed();
		if (numPlayers < nonClosed) {
			if (!(m_bfme3d4 & 2)) {
				g_bfmeR1078->bfmeRun1078(m_bfme250, g_bfmeFmt1078, 0, 0, 0, 0, 0, 0);
				m_bfme3d4 |= 2;
			}
			return true;
		}
	}

	if (m_bfme3d4 & 2) {
		g_bfmeR1078->bfmeRun1078(m_bfme250, g_bfmeFmtB1073, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 &= ~2;
	}
	return result;
}
