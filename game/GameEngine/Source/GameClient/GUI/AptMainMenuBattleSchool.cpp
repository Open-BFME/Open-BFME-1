// cl: /DNDEBUG /MD /Iinputs/reference/shims/stringinline

#include "StringInline.h"

class Rva0051D690Shell
{
public:
	void restore();

	unsigned char m_bfmeHeadBQ[ 0x59 ];
	unsigned char m_bfmeFlagBQ;
};

// The retail shell singleton at 0x012F4B58 has the one identity
// ?TheShell@@3PAVShell@@A, so the reference carries its defining class name;
// this TU's own view of the object stays above and is selected by a cast.
class Shell;

extern Shell *TheShell;

static inline Rva0051D690Shell *localShell()
{
	return (Rva0051D690Shell *)TheShell;
}

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

// Retail's AudioManager singleton (0x012ED668); the TU-local view below only
// names the slot this body calls.
class AudioManager;

extern AudioManager *TheAudio;

static inline Rva005A00B0AudioClient *localAudioClient()
{
	return (Rva005A00B0AudioClient *)TheAudio;
}

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
	if( TheShell != 0 )
		localShell()->m_bfmeFlagBQ = 0;

	localAudioClient()->bfmeStopBQ( 8 );

	TheTransitionHandler->setGroup( AsciiString( "MainMenuToBattleSchool" ) );

	if( TheShell != 0 )
		localShell()->restore();

	m_bfmeStateBQ = 0;
}
