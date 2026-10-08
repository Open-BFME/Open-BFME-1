// Open-BFME5 conversions.

class BfmeAptScreenLanLobby;
extern BfmeAptScreenLanLobby *g_rva012F4998LanLobby;
// retail 0x012F4B58: the shell singleton, whose one identity is
// ?TheShell@@3PAVShell@@A.  The view above is this TU's own layout of it, so
// the reference carries the defining name and the view is selected by a cast.
class Shell;
extern Shell *TheShell;
extern bool LANbuttonPushed;

// Callees (tools/callees.py): ILT 0x6AAA -> 0x0057F470 Shell::pop; tail jump
// to 0x00517450 Rva00517450LanLobby::rva00517450; ILT 0x290D2 -> 0x00465B80
// Rva00465B80::apply.
class Rva00517450LanLobby
{
public:
	void rva00517450();
};

class Shell
{
public:
	void pop();
};

class Rva00465B80
{
public:
	void apply();
};

typedef Rva00517450LanLobby BfmeRun1006;
typedef Rva00465B80 BfmeHub1006;
#define bfmeRun1006() rva00517450()
#define bfmeDo1006() apply()

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

	if (!reinterpret_cast<BfmeRun1006 * &>(g_rva012F4998LanLobby)) {
		TheShell->pop();
		LANbuttonPushed = 1;
		return;
	}

	reinterpret_cast<BfmeRun1006 * &>(g_rva012F4998LanLobby)->bfmeRun1006();
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


// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the hub call through it, so the pointee stays the local BfmeHub1006 view and
// the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

class BfmeAptScreenSpellStore;
extern BfmeAptScreenSpellStore *g_purchaseScienceWindow;

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

	BfmeObj1006 *p = reinterpret_cast<BfmeObj1006 * &>(g_purchaseScienceWindow);

	if (p && !p->m_bfmeFlag) {
		p->m_bfmeFlag = 1;
		((BfmeAux1006 *)TheShell)->m_bfmeFlag = 1;
		((BfmeHub1006 *)g_rva012F19E8WindowManager)->bfmeDo1006();
	}

	m_bfmeWant = 0;
}
