// ?rva00552C40@BfmeAptScreenOnlineLogin@@QAEX_N@Z
// partial score=0.1 date=2026-09-10
// ?rva00552C40@BfmeAptScreenOnlineLogin@@QAEX_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/campaignmanagerascii /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// The anonymous generated row at 0x00552C40 is the bool tail used by the
// OnlineLogin DeleteNickname and Login callbacks.  The matched callers at
// 0x00553520 and 0x005536F0 pass false/true through ILT 0x00049E1D, while
// AcceptLocale calls this body with the same bool at 0x005533F0.  The method
// below keeps that proven neutral RVA identity and replaces the dump body.

#include "PreRTS.h"

typedef bool Bool;

extern "C" char *strcpy( char *destination, const char *source );

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString();

	void translate( const UnicodeString &text );

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}

	bool isEmpty() const
	{
		return !m_data || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}
};

extern const char g_Rva0107301CEmptyString[];
bool GetStringFromRegistry( AsciiString path, AsciiString key, AsciiString &value );

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 ) = 0;
};

extern GameTextInterface *TheGameText;

typedef void (*GameWinMsgBoxFunc)( void );

class GameWindow;
GameWindow *MessageBoxOkCancel( UnicodeString title, UnicodeString message,
	GameWinMsgBoxFunc okFunction, GameWinMsgBoxFunc cancelFunction );
void GSMessageBoxOk( UnicodeString title, UnicodeString message,
	GameWinMsgBoxFunc okFunction = 0 );

class WindowManager
{
public:
	void add( void *window, const char *name, int type, void *value,
		int unused0, int unused1, int unused2, int unused3 );
};

extern WindowManager *g_theWindowManager;

class GameWindow
{
public:
	int winEnable( bool enabled );
};

class Rva00548D30WindowGroup
{
private:
	unsigned char m_pad[ 0x74 ];
	GameWindow *m_windows[ 4 ];

public:
	void winEnable( bool enabled );
};

// The BFME GameSpyInfo vtable has seven BFME slots between isBuddy and the
// local-account accessors.  Thus setLocalEmail/password/base-name are slots
// 30/32/33 (+0x78/+0x80/+0x84), exactly the three calls in this body.
class GameSpyInfo
{
public:
	virtual ~GameSpyInfo();
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void setLocalName( AsciiString name ) = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual AsciiString getLocalEmail() = 0;
	virtual void setLocalEmail( AsciiString email ) = 0;
	virtual AsciiString getLocalPassword() = 0;
	virtual void setLocalPassword( AsciiString password ) = 0;
	virtual void setLocalBaseName( AsciiString name ) = 0;
};

extern GameSpyInfo *TheGameSpyInfo;

struct BuddyRequest
{
	enum { BUDDYREQUEST_LOGIN = 0 };

	int buddyRequestType;
	union
	{
		struct
		{
			char nick[ 64 ];
			char email[ 128 ];
			char password[ 64 ];
			Bool hasFirewall;
		} login;
		char body[ 0x2B4 ];
	} arg;
};

typedef char BuddyRequestSizeCheck[ sizeof( BuddyRequest ) == 0x2B8 ? 1 : -1 ];

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface();
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual Bool isThreadRunning() = 0;
	virtual Bool isConnected() = 0;
	virtual Bool isConnecting() = 0;
	virtual void addRequest( const BuddyRequest &request ) = 0;
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

extern int (__cdecl *g_bfmeNowVNH)();

namespace Rva00550500
{
	void startPings();
}

struct BfmeOnlineLoginContext
{
	unsigned char m_unmodelled[ 0x250 ];
	void *m_window;
};

class BfmeAptScreenOnlineLogin
{
public:
	void rva00552C40( bool argument );
	UnicodeString bfmeGetTextAt74() const;
	UnicodeString bfmeGetTextAt78() const;
	UnicodeString bfmeGetTextAt7C() const;

private:
	unsigned char m_unmodelled00[ 0x34 ];
	BfmeOnlineLoginContext *m_context;
	unsigned char m_unmodelled38[ 0x60 ];
	unsigned int m_loginAttemptTime;
};

// The callback body is unclaimed by name, but its exact address is the
// pointer pushed by the retail DeleteNickname arm.  Keep it declaration-free
// at source level so no fake callback body is introduced.

void BfmeAptScreenOnlineLogin::rva00552C40( bool argument )
{
	if( argument )
	{
		MessageBoxOkCancel(
			TheGameText->fetch( "GUI:SureDeleteNickname" ),
			UnicodeString( (const unsigned short *)0x01088AF4 ),
			reinterpret_cast<GameWinMsgBoxFunc>( 0x00951DB0 ),
			reinterpret_cast<GameWinMsgBoxFunc>( 0x00948D00 ) );
		return;
	}

	AsciiString login, password, email;
	email.translate( bfmeGetTextAt74() );
	login.translate( bfmeGetTextAt78() );
	password.translate( bfmeGetTextAt7C() );

	if( !email.isEmpty() && !login.isEmpty() && !password.isEmpty() )
	{
		m_loginAttemptTime = g_bfmeNowVNH();

		BuddyRequest request;
		request.buddyRequestType = BuddyRequest::BUDDYREQUEST_LOGIN;
		strcpy( request.arg.login.nick, login.str() );
		strcpy( request.arg.login.email, email.str() );
		strcpy( request.arg.login.password, password.str() );
		request.arg.login.hasFirewall = false;

		AsciiString serial;
		GetStringFromRegistry( "\\ergc", g_Rva0107301CEmptyString, serial );

		TheGameSpyInfo->setLocalBaseName( login );
		TheGameSpyInfo->setLocalEmail( email );
		TheGameSpyInfo->setLocalPassword( password );
		TheGameSpyBuddyMessageQueue->addRequest( request );

		reinterpret_cast<Rva00548D30WindowGroup *>( this )->winEnable( false );
		g_theWindowManager->add( m_context->m_window, "CallChild", 1,
			(void *)"DisableButtonLogin", 0, 0, 0, 0 );
		g_theWindowManager->add( m_context->m_window, "CallChild", 1,
			(void *)"DisableButtonDeleteNickname", 0, 0, 0, 0 );
		Rva00550500::startPings();
		return;
	}

	if( email.isEmpty() && login.isEmpty() && password.isEmpty() )
		GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
			TheGameText->fetch( "GUI:GSNoLoginInfoAll" ) );
	else if( email.isEmpty() && login.isEmpty() )
		GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
			TheGameText->fetch( "GUI:GSNoLoginInfoEmailNickname" ) );
	else if( email.isEmpty() && password.isEmpty() )
		GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
			TheGameText->fetch( "GUI:GSNoLoginInfoEmailPassword" ) );
	else if( login.isEmpty() && password.isEmpty() )
		GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
			TheGameText->fetch( "GUI:GSNoLoginInfoNicknamePassword" ) );
	else if( email.isEmpty() )
		GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
			TheGameText->fetch( "GUI:GSNoLoginInfoEmail" ) );
	else if( password.isEmpty() )
		GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
			TheGameText->fetch( "GUI:GSNoLoginInfoPassword" ) );
	else if( login.isEmpty() )
		GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
			TheGameText->fetch( "GUI:GSNoLoginInfoNickname" ) );
	else
		GSMessageBoxOk( TheGameText->fetch( "GUI:GSErrorTitle" ),
			TheGameText->fetch( "GUI:GSNoLoginInfoAll" ) );
}
