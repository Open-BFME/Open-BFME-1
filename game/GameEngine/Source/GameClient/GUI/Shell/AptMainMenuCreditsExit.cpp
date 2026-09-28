// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
//
// BfmeAptScreenMainMenu::_bfme_creditsExit, retail 0x0051E010, 178 bytes. The
// main menu constructor at 0x0051F3A0 pushes the selector string
// "AptMainMenu::CreditsExit" at 0x0051F811 and loads this body's ILT thunk a
// few bytes later, which is what names it. The body resets and deletes
// TheCredits, restores the shell music the credits roll stopped, reverses the
// MainMenuToCreditsScreen transition and puts the frame rate cap back.

#include "StringInline.h"

// Same six virtuals, in the same order, that CreditsMenuInit_Thunk.cpp reads
// off ??_7CreditsManager@@6B@.
class CreditsManager
{
public:
	virtual ~CreditsManager();
	virtual void init();
	virtual void load();
	virtual void postProcessLoad();
	virtual void reset();
	virtual void update();
	virtual void draw();
};

// Same shell singleton and same two methods Rva0051D690MainMenuHelper.cpp uses.
class Rva0051D690Shell
{
public:
	bool check();
	void restore();

	unsigned char m_unmodelled[ 0x59 ];
	unsigned char m_flag59;
};

class Rva0051D690Audio
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68();
	virtual void slot6c( int a, int b, int c );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	void reverse( AsciiString name );
};

struct Rva006C9270GlobalData
{
	unsigned char m_head[ 0x24 ];
	int m_framesPerSecondLimit;
};

#define BFME_VSLOT( n ) virtual void _bfme_slot##n( void ) = 0
class GameEngine
{
public:
	BFME_VSLOT( 0 ); BFME_VSLOT( 1 ); BFME_VSLOT( 2 ); BFME_VSLOT( 3 );
	BFME_VSLOT( 4 ); BFME_VSLOT( 5 ); BFME_VSLOT( 6 ); BFME_VSLOT( 7 );
	BFME_VSLOT( 8 ); BFME_VSLOT( 9 ); BFME_VSLOT( 10 );
	virtual void setFramesPerSecondLimit( int fps ) = 0;
};
#undef BFME_VSLOT

extern CreditsManager *TheCredits;
extern Rva0051D690Shell *g_obj12F4B58;
extern Rva0051D690Audio *TheAudioClientUpdate;
extern GameWindowTransitionsHandler *TheTransitionHandler;
extern Rva006C9270GlobalData *TheWritableGlobalData;
extern GameEngine *TheGameEngine;

class BfmeAptScreenMainMenu
{
public:
	void _bfme_creditsExit( const char *name );

private:
	unsigned char m_head[ 0x264 ];
	int m_state264;
	unsigned char m_gap268[ 0x14 ];
	AsciiString m_name27C;
};

void BfmeAptScreenMainMenu::_bfme_creditsExit( const char *name )
{
	(void)name;
	if ( TheCredits )
	{
		TheCredits->reset();
		delete TheCredits;
		TheCredits = 0;
	}
	if ( !g_obj12F4B58 || !g_obj12F4B58->check() )
	{
		TheAudioClientUpdate->slot6c( 2, 1, 0 );
		g_obj12F4B58->restore();
	}
	TheTransitionHandler->reverse( AsciiString( "MainMenuToCreditsScreen" ) );
	m_state264 = 0;
	m_name27C.~AsciiString();
	g_obj12F4B58->m_flag59 = 0;
	TheGameEngine->setFramesPerSecondLimit( TheWritableGlobalData->m_framesPerSecondLimit );
}
