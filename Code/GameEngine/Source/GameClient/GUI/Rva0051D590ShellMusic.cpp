// Retail RVA 0x0051D590 (198 bytes).
//
// The retail two-argument construction route is the ObjectID ILT 0x00025306,
// not the int route at ILT 0x0001EC13.  The logical-audio setter in this call
// site is the existing LwsAudioEventRTS route at ILT 0x0002C5CF.  Both views
// describe the same 0x70-byte retail event storage; no vtable is emitted by
// this dispatch-only TU.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Ireference/shims/campaignmanagerascii /Ireference/shims/asciistring_downloadmanager

#include "Common/AsciiString.h"

typedef bool Bool;

extern void j_0004393c();

class Rva0051D690Shell
{
public:
	void giveBackViaThunk()
	{
		typedef void (Rva0051D690Shell::*MemberThunk)();
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_0004393c;
		(this->*thunk.member)();
	}
};

class TransitionHandler
{
public:
	void setGroup( AsciiString name, int immediate );
};

enum ObjectID
{
	OBJECT_ID_UNUSED = 0
};

class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &name, ObjectID owner );
	virtual void slot00();
	~AudioEventRTS();

private:
	unsigned char m_unmodelled[0x6c];
};

// Retail ILT 0x0002C5CF is the existing LivingWorld setter route.  The
// local view keeps the 0x70-byte event storage while selecting that route,
// rather than the AudioEventRTS ILT 0x00008206.
class LwsAudioEventRTS
{
public:
	void setIsLogicalAudio( Bool logical );
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

extern Rva0051D690Shell *g_obj12F4B58;
struct Rva005A00B0Transition;
extern Rva005A00B0Transition *TheTransitionHandler;
extern ClientSubsystem *TheAudioClientUpdate;

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
	reinterpret_cast<TransitionHandler *>( TheTransitionHandler )->setGroup( AsciiString( "MainMenuToSubMenu" ), 0 );

	if ( g_obj12F4B58 != 0 )
		g_obj12F4B58->giveBackViaThunk();

	AudioEventRTS event( AsciiString( "Shell2Music" ), (ObjectID)2 );
	((LwsAudioEventRTS *)&event)->setIsLogicalAudio( false );
	TheAudioClientUpdate->addAudioEvent( &event );
}
