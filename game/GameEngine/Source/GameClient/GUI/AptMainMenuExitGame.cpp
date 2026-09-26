// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
//
// BfmeAptScreenMainMenu::_bfme_exitGame, retail 0x0051E0F0, 137 bytes. The
// constructor at 0x0051F3A0 registers this address under the selector string
// "AptMainMenu::ExitGame" and AptMainMenuConstructor.cpp already declares the
// method under that name. The body signals the shell script hook, stops the
// shell music through TheAudio vslot 0x6c, pops the shell screen and tells the
// engine to quit.

#include "StringInline.h"

class ScriptEngine
{
public:
	virtual void anchor00(); virtual void anchor04(); virtual void anchor08(); virtual void anchor0C();
	virtual void anchor10(); virtual void anchor14(); virtual void anchor18(); virtual void anchor1C();
	virtual void anchor20(); virtual void anchor24(); virtual void anchor28(); virtual void anchor2C();
	virtual void anchor30(); virtual void anchor34(); virtual void anchor38(); virtual void anchor3C();
	virtual void anchor40(); virtual void anchor44(); virtual void anchor48(); virtual void anchor4C();
	virtual void anchor50(); virtual void anchor54(); virtual void anchor58(); virtual void anchor5C();
	virtual void anchor60(); virtual void anchor64(); virtual void anchor68(); virtual void anchor6C();
	virtual void anchor70(); virtual void anchor74(); virtual void anchor78(); virtual void anchor7C();
	virtual void anchor80(); virtual void anchor84(); virtual void anchor88(); virtual void anchor8C();
	virtual void anchor90(); virtual void anchor94(); virtual void anchor98(); virtual void anchor9C();
	virtual void signalUIInteract( const AsciiString &interaction );
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

class Shell
{
public:
	void pop();
};

#define BFME_VSLOT( n ) virtual void _bfme_slot##n( void ) = 0
class GameEngine
{
public:
	BFME_VSLOT( 0 ); BFME_VSLOT( 1 ); BFME_VSLOT( 2 ); BFME_VSLOT( 3 );
	BFME_VSLOT( 4 ); BFME_VSLOT( 5 ); BFME_VSLOT( 6 ); BFME_VSLOT( 7 );
	BFME_VSLOT( 8 ); BFME_VSLOT( 9 ); BFME_VSLOT( 10 ); BFME_VSLOT( 11 );
	BFME_VSLOT( 12 );
	virtual void setQuitting( bool quitting ) = 0;
};
#undef BFME_VSLOT

extern ScriptEngine *TheScriptEngine;
extern Rva0051D690Audio *TheAudioClientUpdate;
extern Shell *TheShell;
extern GameEngine *TheGameEngine;
extern const char *TheShellHookNames[];

// inputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include/GameClient/ShellHooks.h
enum { SHELL_SCRIPT_HOOK_MAIN_MENU_EXIT_SELECTED = 15 };

class BfmeAptScreenMainMenu
{
public:
	void _bfme_exitGame( const char *name );
};

void BfmeAptScreenMainMenu::_bfme_exitGame( const char *name )
{
	(void)name;
	TheScriptEngine->signalUIInteract(
		TheShellHookNames[ SHELL_SCRIPT_HOOK_MAIN_MENU_EXIT_SELECTED ] );
	TheAudioClientUpdate->slot6c( 2, 1, 0 );
	TheShell->pop();
	TheGameEngine->setQuitting( true );
}
