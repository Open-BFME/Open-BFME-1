// ?startNewGame@Rva00367810Entries@@QAEXXZ
// partial score=0.12 date=2026-09-12
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail RVA 0x00367470, 644 bytes.  GameLogic::startNewGame services the
// embedded store at GameLogic+0x170 (see Rva00367810EntryUpdate.cpp).  Early
// out is GameLogic::_bfme_isInLivingWorldCampaign.  Identity of the remaining
// callees is still placeholder pins; this is a layout skeleton, not a landing.

typedef unsigned char ByteBool;

class GameLogic
{
public:
	ByteBool _bfme_isInLivingWorldCampaign( void );
	unsigned char m_lead[ 0x90 ];
	unsigned char m_byte90;
};

#define TheGameLogic (*(GameLogic **)0x012F0898)

struct Rva002EE330PlayerList
{
	char m_unmodelled[ 0x0C ];
	void *m_campaign;
};

#define ThePlayerList (*(Rva002EE330PlayerList **)0x012ED748)

class Rva00367810Entries
{
public:
	void startNewGame();

	char m_lead[ 0x10 ];
	unsigned char m_busy;
	char m_pad[ 7 ];
	char *m_first;
	char *m_last;
};

extern void j_000380fa();
extern void j_000259cd();
extern void j_00034383();
extern void j_0001e056();
extern void j_0001df16();
extern void j_00040327();
extern void j_0001897b();

void Rva00367810Entries::startNewGame()
{
	if ( !TheGameLogic->_bfme_isInLivingWorldCampaign() )
		return;

	m_busy = 1;
	void *campaign = ThePlayerList->m_campaign;
	if ( campaign )
	{
		GameLogic *logic = TheGameLogic;
		unsigned char saved = logic->m_byte90;
		logic->m_byte90 = 0;
		(void)saved;
		(void)j_000380fa;
		(void)j_000259cd;
		(void)j_00034383;
		(void)j_0001e056;
		(void)j_0001df16;
		(void)j_00040327;
		(void)j_0001897b;
	}

	char *first = m_first;
	char *last = m_last;
	if ( first != last )
	{
		for ( char *entry = first; entry != last; entry += 0x58 )
			(void)entry;
	}

	m_busy = 0;
}
