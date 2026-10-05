// Open-BFME5 conversions.

class BfmeRun1006
{
public:
	void bfmeRun1006();
};

class BfmeStop1006
{
public:
	void bfmeStop1006();
};

extern BfmeRun1006 *g_bfmeRun1006;
// retail 0x012F4B58: the shell singleton, whose one identity is
// ?TheShell@@3PAVShell@@A.  The view above is this TU's own layout of it, so
// the reference carries the defining name and the view is selected by a cast.
class Shell;
extern Shell *TheShell;
extern bool LANbuttonPushed;

class BfmeA1006
{
public:
	void bfmeGo1006A();

	char m_bfmePad[0x3d];
	char m_bfmeDone;
	char m_bfmePad2[2];
	int m_bfmeVal;
};

void BfmeA1006::bfmeGo1006A()
{
	if (m_bfmeDone)
		return;
	if (!m_bfmeVal)
		return;

	if (!g_bfmeRun1006) {
		((BfmeStop1006 *)TheShell)->bfmeStop1006();
		LANbuttonPushed = 1;
		return;
	}

	g_bfmeRun1006->bfmeRun1006();
}

struct BfmeObj1006
{
	char m_bfmePad[0x254];
	char m_bfmeFlag;
};

struct BfmeAux1006
{
	char m_bfmePad[0x50];
	char m_bfmeFlag;
};

class BfmeHub1006
{
public:
	void bfmeDo1006();
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the hub call through it, so the pointee stays the local BfmeHub1006 view and
// the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

extern BfmeObj1006 *g_bfmeObj1006;

class BfmeB1006
{
public:
	void bfmeGo1006B(int unused);

	char m_bfmePad[0x25a];
	char m_bfmeWant;
};

void BfmeB1006::bfmeGo1006B(int unused)
{
	if (!m_bfmeWant)
		return;

	BfmeObj1006 *p = g_bfmeObj1006;

	if (p && !p->m_bfmeFlag) {
		p->m_bfmeFlag = 1;
		((BfmeAux1006 *)TheShell)->m_bfmeFlag = 1;
		((BfmeHub1006 *)g_rva012F19E8WindowManager)->bfmeDo1006();
	}

	m_bfmeWant = 0;
}
