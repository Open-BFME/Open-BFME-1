// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/nat /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

template <typename T> struct WOLLobbyStringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	WOLLobbyStringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
	int compareNoCase( const AsciiString &other ) const;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	const unsigned short *str( void ) const;
	int compareNoCase( const UnicodeString &other ) const;
};

bool operator==( const AsciiString &left, const AsciiString &right );
#define ASCIISTRING_H
#define UNICODESTRING_H
#include "PreRTS.h"
#include "Common/CustomMatchPreferences.h"
#include "GameNetwork/GameSpy/PeerThread.h"

class GameWindow;
class WindowLayout;

// The retail body calls GameSpyInfo::unregisterTextWindow through vtable +0xe8.
// This local view preserves that slot while avoiding a shared-header change: the
// BFME callback's global is the GameSpy (rather than interface) typed symbol.
class GameSpyInfo
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot2A(); virtual void slot2B();
	virtual void slot2C(); virtual void slot2D(); virtual void slot2E(); virtual void slot2F();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39();
	virtual void unregisterTextWindow(GameWindow *window);
};

// These are the BFME lobby TU's static objects. Their addresses are established
// by the named WOLLobby callers and the retail relocation map; keeping the views
// local avoids changing the existing WOLLobbyMenu.cpp storage or its siblings.
#define g_WOLLobbyListboxChat (*(GameWindow **)0x012F4628)
#define g_WOLLobbyListboxPlayers (*(GameWindow **)0x012F4624)
#define g_WOLLobbyIsShuttingDown (*(Bool *)0x012F45C0)
#define g_WOLLobbyDontShowMainMenu (*(Bool *)0x012F45D4)

class Shell
{
public:
	void shutdownComplete(WindowLayout *layout, Bool impendingPush);
	void push(AsciiString screen, Bool shelldown = FALSE);
	void reverseAnimatewindow();
};

class GameWindowTransitionsHandler
{
public:
	void reverse(AsciiString groupName);
};

extern GameSpyInfo *TheGameSpyInfo;
extern Shell *TheShell;
extern GameWindowTransitionsHandler *TheTransitionHandler;

extern void j_00044a3a(void); // ILT 0x00044A3A -> the tracked 0x0062C5D0 return-zero body
typedef GameWindow *(*GetGameInfoListBoxCall)(void);
void ReleaseWindowInfo(void);
void RaiseGSMessageBox(void);

class BfmeVirtualHideLayout
{
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
	virtual void slot8() = 0;
	virtual void slotC() = 0;
	virtual void hide(Bool immediate) = 0;
};

// This is a TU-local view of the already-proven WOLLobbyMenu::shutdownComplete
// body at 0x004F98B0. Its complexity deliberately preserves the private ESI
// call convention used by the verified sibling source; it introduces no row or
// identity claim of its own.
static Bool s_shutdownCompleteIsShuttingDown;
static char *s_shutdownCompleteNextScreen;

static void shutdownCompleteWOLLobbyMenu(WindowLayout *layout)
{
	s_shutdownCompleteIsShuttingDown = FALSE;
	((BfmeVirtualHideLayout *)layout)->hide(TRUE);
	TheShell->shutdownComplete(layout, (s_shutdownCompleteNextScreen != NULL));
	if (s_shutdownCompleteNextScreen != NULL)
	{
		TheShell->push(s_shutdownCompleteNextScreen);
	}
	s_shutdownCompleteNextScreen = NULL;
}

// ?WOLLobbyMenuShutdown@@YAXPAVWindowLayout@@PAX@Z
// Retail boundary: 0x004FAF70..0x004FB09B (299 bytes). The callback is named
// independently by the FunctionLexicon registration and by its exact caller.
void WOLLobbyMenuShutdown(WindowLayout *layout, void *userData)
{
	CustomMatchPreferences pref;
	if (((GetGameInfoListBoxCall)j_00044a3a)())
	{
		pref.setUsesLongGameList(FALSE);
	}
	else
	{
		pref.setUsesLongGameList(TRUE);
	}
	pref.write();

	ReleaseWindowInfo();

	TheGameSpyInfo->unregisterTextWindow(g_WOLLobbyListboxChat);

	PeerRequest req;
	// BFME inserts one request kind before STOPGAMELIST; retail stores 8 here.
	// The reference header exposes peerRequestType as its anonymous enum, so the
	// TU-local ABI view writes the proven BFME ordinal without changing that type.
	*(int *)&req.peerRequestType = 8;
	TheGameSpyPeerMessageQueue->addRequest(req);

	if (*(Bool *)userData)
	{
		g_WOLLobbyListboxChat = NULL;
		g_WOLLobbyListboxPlayers = NULL;
		g_WOLLobbyIsShuttingDown = TRUE;
		shutdownCompleteWOLLobbyMenu(layout);
		return;
	}

	g_WOLLobbyListboxChat = NULL;
	g_WOLLobbyListboxPlayers = NULL;
	g_WOLLobbyIsShuttingDown = TRUE;

	TheShell->reverseAnimatewindow();
	g_WOLLobbyDontShowMainMenu = FALSE;
	RaiseGSMessageBox();
	TheTransitionHandler->reverse("WOLCustomLobbyFade");
}
