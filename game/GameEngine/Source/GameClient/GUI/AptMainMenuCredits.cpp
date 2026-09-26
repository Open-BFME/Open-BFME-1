// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
//
// BfmeAptScreenMainMenu::_bfme_credits, retail 0x0051DE70, 321 bytes. The main
// menu constructor at 0x0051F3A0 pushes the selector string
// "AptMainMenu::Credits" at 0x0051F7A8 and loads this body's ILT thunk a few
// bytes later, which is what names it.
//
// The body opens the credits roll. It rebuilds TheCredits, runs the
// MainMenuToCreditsScreen window transition, starts the Credits music and
// raises the frame rate cap to 100. CreditsMenuInit_Thunk.cpp converts the old
// window version of the same sequence at 0x004C6C60.

#include "StringInline.h"

// Same six virtuals, in the same order, that CreditsMenuInit_Thunk.cpp reads
// off ??_7CreditsManager@@6B@.
class CreditsManager
{
public:
	CreditsManager();
	virtual ~CreditsManager();
	virtual void init();
	virtual void load();
	virtual void postProcessLoad();
	virtual void reset();
	virtual void update();
	virtual void draw();

private:
	char m_unmodelled[ 0x40 ];
};

class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &eventName, int extra );
	virtual void slot00();
	~AudioEventRTS();
	void setIsLogicalAudio( bool enabled );

private:
	char m_unmodelled[ 0x6C ];
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
	virtual void slot40();
	virtual unsigned int addAudioEvent( AudioEventRTS *event );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	void setGroup( AsciiString name, bool immediate );
};

// The shell singleton, spelled for the neighbouring body at 0x0057F100 the way
// S3GuardedIndirectRelease.cpp names it.
class Rva0057F100
{
public:
	void giveBack();

	unsigned char m_unmodelled[ 0x59 ];
	unsigned char m_flag59;
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
extern Rva0051D690Audio *TheAudioClientUpdate;
extern GameWindowTransitionsHandler *TheTransitionHandler;
extern Rva0057F100 *g_obj12F4B58;
extern GameEngine *TheGameEngine;

class BfmeAptScreenMainMenu
{
public:
	void _bfme_credits( const char *name );

private:
	unsigned char m_head[ 0x264 ];
	int m_state264;
};

void BfmeAptScreenMainMenu::_bfme_credits( const char *name )
{
	(void)name;
	if ( TheCredits )
		delete TheCredits;
	TheCredits = new CreditsManager;
	TheCredits->load();
	TheCredits->init();

	TheTransitionHandler->setGroup( AsciiString( "MainMenuToCreditsScreen" ), false );

	if ( g_obj12F4B58 )
		g_obj12F4B58->giveBack();

	AudioEventRTS event( AsciiString( "Credits" ), 2 );
	event.setIsLogicalAudio( true );
	TheAudioClientUpdate->addAudioEvent( &event );

	m_state264 = 4;
	g_obj12F4B58->m_flag59 = 1;
	TheGameEngine->setFramesPerSecondLimit( 100 );
}
