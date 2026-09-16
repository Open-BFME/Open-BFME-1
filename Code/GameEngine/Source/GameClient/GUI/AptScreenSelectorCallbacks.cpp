// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Three Apt screen callbacks that had no ledger row at all. Each screen
// constructor pushes a selector string and then loads the ILT thunk of the
// callback within about eighty bytes, so the string names the body. Retail
// 0x0051FD66 registers 0x0051D180 under "AptMainMenu::StopGameMovie". Retail
// 0x0056EA93 registers 0x0056A840 under "AptSaveLoad::OnClosed". Retail
// 0x005985F5 registers 0x00589900 under "AptPalantir::OnBttnObserveNextPlayer".
//
// Retail compiles all three with a tail jump, so each one ends in a jmp rather
// than a call and a ret.

class GameMessage;

// ?TheMessageStream@@3PAVMessageStream@@A, the same thirteen empty slots and
// appendMessage at slot 13 that Rva0051D1E0Shutdown.cpp already witnesses.
class MessageStream
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot0A() = 0;
	virtual void slot0B() = 0;
	virtual void slot0C() = 0;
	virtual GameMessage *appendMessage( int type ) = 0;
};

struct Rva00367E30Logic
{
	unsigned char m_unmodelled[ 0x10C ];
	int m_mode;
};

class Shell40D9
{
public:
	unsigned char m_unmodelled[ 0x50 ];
	char m_bfmeFlagEAH;
};

struct Rva00579160Manager
{
	void bfmeRunEAH();
};

class BfmeGlob938A
{
public:
	void bfmeTail938A( int f );
};

extern MessageStream *TheMessageStream;
extern Rva00367E30Logic *TheBfmeGameLogic;
extern Shell40D9 *TheShell;
extern void *g_bfmeReadyAG;
extern Rva00579160Manager *Rva00579160TheManager;
extern BfmeGlob938A *g_bfme938GlobA;

class BfmeAptScreenMainMenu
{
public:
	void _bfme_stopGameMovie( const char *name );
};

class BfmeAptScreenSaveLoad
{
public:
	void _bfme_onClosed( const char *name );
};

class BfmeAptScreenPalantir
{
public:
	void _bfme_onBttnObserveNextPlayer( const char *name );
};

void BfmeAptScreenMainMenu::_bfme_stopGameMovie( const char *name )
{
	(void)name;
	if ( TheBfmeGameLogic->m_mode != 8 )
		TheMessageStream->appendMessage( 0x1D );
}

void BfmeAptScreenSaveLoad::_bfme_onClosed( const char *name )
{
	(void)name;
	if ( TheShell )
		TheShell->m_bfmeFlagEAH = 1;
	if ( g_bfmeReadyAG )
		Rva00579160TheManager->bfmeRunEAH();
}

// The palantir body compiles to retail's nineteen bytes, but it cannot take a
// ledger row yet. The generated gap row ?j_0058990e@@YAXXZ claims five of those
// bytes as a standalone thunk at 0x0058990E, which is really this body's tail
// jump, and add_match refuses a claim that starts before a scaffold it would
// retire. Retracting that gap row unblocks the claim.
void BfmeAptScreenPalantir::_bfme_onBttnObserveNextPlayer( const char *name )
{
	(void)name;
	g_bfme938GlobA->bfmeTail938A( 1 );
}
