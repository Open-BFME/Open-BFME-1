// cl: /DNDEBUG /MD /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class Rva0051D690Shell
{
public:
	void restore();

	unsigned char m_bfmeHeadBQ[ 0x59 ];
	unsigned char m_bfmeFlagBQ;
};

extern Rva0051D690Shell *g_obj12F4B58;

struct Rva005A00B0AudioClient
{
	virtual void bfmeSlot00BQ();
	virtual void bfmeSlot01BQ();
	virtual void bfmeSlot02BQ();
	virtual void bfmeSlot03BQ();
	virtual void bfmeSlot04BQ();
	virtual void bfmeSlot05BQ();
	virtual void bfmeSlot06BQ();
	virtual void bfmeSlot07BQ();
	virtual void bfmeSlot08BQ();
	virtual void bfmeSlot09BQ();
	virtual void bfmeStopBQ( int mode );
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class GameWindowTransitionsHandler
{
public:
	void setGroup( AsciiString name );
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

class AptMainMenu
{
public:
	void BattleSchool( void *unused );

	unsigned char m_bfmeHeadBQ[ 0x264 ];
	int m_bfmeStateBQ;
};

void AptMainMenu::BattleSchool( void *unused )
{
	if( g_obj12F4B58 != 0 )
		g_obj12F4B58->m_bfmeFlagBQ = 0;

	TheAudioClientUpdate->bfmeStopBQ( 8 );

	TheTransitionHandler->setGroup( AsciiString( "MainMenuToBattleSchool" ) );

	if( g_obj12F4B58 != 0 )
		g_obj12F4B58->restore();

	m_bfmeStateBQ = 0;
}
