// Retail RVA 0x0051D590 (198 bytes).
//
// Retail ILT 0x00025306 reaches AudioEventRTS(const AsciiString &, int)
// at 0x000B2CC0. ILT 0x0002C5CF reaches setIsLogicalAudio at 0x000B2330.
// The existing native AsciiString header emits the direct StringBase calls
// used by retail. This TU declares the 0x70-byte event layout only.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/asciistring_downloadmanager

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef bool Bool;

extern void j_0004393c();

// TU-local view of the retail shell singleton, whose one identity is
// ?TheShell@@3PAVShell@@A at 0x012F4B58.
class Shell
{
public:
	void giveBackViaThunk()
	{
		typedef void (Shell::*MemberThunk)();
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_0004393c;
		(this->*thunk.member)();
	}
};

class GameWindowTransitionsHandler
{
public:
	void setGroup( AsciiString name, bool immediate );
};

class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &name, int owner );
	void setIsLogicalAudio( Bool logical );
	virtual void slot00();
	~AudioEventRTS();

private:
	unsigned char m_unmodelled[0x6c];
};

class ClientSubsystem
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
	virtual void addAudioEvent( AudioEventRTS *event );
};

extern Shell *TheShell;
extern GameWindowTransitionsHandler *TheTransitionHandler;
// The retail global at 0x012ED668 is EA's AudioManager *TheAudio, defined once
// in game/GameEngine/Source/Common/Audio/GameAudio.cpp.  This TU keeps its own
// address-derived view of that object and casts at the use, so the reference
// names the one linked global.
class AudioManager;
extern AudioManager *TheAudio;
static inline ClientSubsystem *localAudio() { return (ClientSubsystem *)TheAudio; }

class Rva0051D590
{
public:
	void first();

private:
	unsigned char m_unmodelled[0x25b];
	unsigned char m_shellMusicActive;
};

// ?first@Rva0051D590@@QAEXXZ
void Rva0051D590::first()
{
	m_shellMusicActive = 1;
	TheTransitionHandler->setGroup( AsciiString( "MainMenuToSubMenu" ), 0 );

	if ( TheShell != 0 )
		TheShell->giveBackViaThunk();

	AudioEventRTS event( AsciiString( "Shell2Music" ), 2 );
	event.setIsLogicalAudio( false );
	localAudio()->addAudioEvent( &event );
}
