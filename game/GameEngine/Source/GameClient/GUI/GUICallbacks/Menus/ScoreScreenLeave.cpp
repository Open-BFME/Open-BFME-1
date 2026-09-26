// Retail RVA 0x00573000, 359 bytes.
// The callers at 0x005731C0, 0x005731D0, and 0x0057811D identify this routine
// as the shared score-screen exit path.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/asciistring_downloadmanager

#include "Common/AsciiString.h"

typedef bool Bool;

enum ObjectID
{
	OBJECT_ID_UNUSED = 0
};

extern void j_0000876f();
extern void j_0000bd7f();
extern void j_000290d2();
extern void j_0003950e();
extern void j_0003e56d();

class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &name, ObjectID owner );
	virtual void slot00();
	~AudioEventRTS();

private:
	unsigned char m_unmodelled[ 0x6c ];
};

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
	virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68();
	virtual void slot6c( int a, int b, int c );
};

class CampaignManager
{
public:
	__forceinline bool hasFollowUp()
	{
		typedef bool (CampaignManager::*MemberThunk)();
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_0003e56d;
		return (this->*thunk.member)();
	}
};

class Rva012F49B4Thing
{
public:
	__forceinline void returnToShell()
	{
		typedef void (Rva012F49B4Thing::*MemberThunk)();
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_0000876f;
		(this->*thunk.member)();
	}
};

class WindowManager
{
public:
	__forceinline void returnToShell()
	{
		typedef void (WindowManager::*MemberThunk)();
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_000290d2;
		(this->*thunk.member)();
	}

	__forceinline void hideBackgroundForLeave( Bool hide )
	{
		typedef void (WindowManager::*MemberThunk)( Bool );
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_0000bd7f;
		(this->*thunk.member)( hide );
	}
};

class Mouse
{
public:
	__forceinline void returnToShell()
	{
		typedef void (Mouse::*MemberThunk)();
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_0003950e;
		(this->*thunk.member)();
	}
};

class Shell
{
public:
	char m_unmodelled[ 0x50 ];
	Bool m_shellMapActive;
};

class BfmeAptScreenScoreScreen
{
public:
	char m_unmodelled[ 0x25c ];
	int m_gameType;
};

extern ClientSubsystem *TheAudioClientUpdate;
extern CampaignManager *TheLivingWorldLogic;
extern Rva012F49B4Thing *g_rva012F49B4;
extern WindowManager *g_theWindowManager;
extern Mouse *TheMouse;
extern Shell *TheShell;
extern BfmeAptScreenScoreScreen *g_obj12F4B50;

class LoadGameFadeHolder
{
public:
	LoadGameFadeHolder( void *binding ) throw();
	LoadGameFadeHolder( const LoadGameFadeHolder &other ) throw() : m_ptr( other.m_ptr ) {}
	~LoadGameFadeHolder() throw() {}

	void *m_ptr;
};

void postTimedOp( LoadGameFadeHolder holder, void *key );

// ?_bfme_leaveScoreScreen@@YAXXZ
void _bfme_leaveScoreScreen()
{
	if ( g_obj12F4B50 == 0 )
		return;

	TheAudioClientUpdate->slot6c( 2, 1, 0 );
	if ( g_obj12F4B50->m_gameType == 0 )
	{
		if ( TheLivingWorldLogic->hasFollowUp() )
		{
			if ( g_rva012F49B4 != 0 )
				g_rva012F49B4->returnToShell();
			g_theWindowManager->returnToShell();
			return;
		}

		TheShell->m_shellMapActive = 1;
		g_theWindowManager->returnToShell();
		TheMouse->returnToShell();
		g_theWindowManager->hideBackgroundForLeave( true );
		postTimedOp( LoadGameFadeHolder( reinterpret_cast<void *>( 0x00435d6e ) ),
			reinterpret_cast<void *>( 0x012ed588 ) );
		return;
	}

	AudioEventRTS event( AsciiString( "Shell2Music" ), (ObjectID)2 );
	((LwsAudioEventRTS *)&event)->setIsLogicalAudio( false );
	TheAudioClientUpdate->addAudioEvent( &event );
	g_theWindowManager->returnToShell();
}
