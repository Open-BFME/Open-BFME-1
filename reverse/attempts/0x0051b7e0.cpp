// ??1BfmeGameLoadingScreen@@QAE@XZ
// partial score=0.62 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeGameLoadingScreen destructor, retail 0x0051B7E0, 546 bytes.
// Sibling of Gen_0051b720_dtor.cpp (retail 0x0051B720, right before this one):
// same vfptr-store trick, same Gen_0051b720Base chain to 0x00490470, same
// TheAudioClientUpdate->slot6c(2,1,0) call. This one additionally releases an
// owner interface pointer at +0x10 (bfmeSlot3(false); if it's still set,
// bfmeSlot1(true); then cleared), resets the embedded Gen005207C0Member
// preview-state object at +0x18 (same class as
// Code/GameEngine/Source/GameClient/GUI/Gen00525EE0MapRefresh.cpp's
// m_previewState -- its own destructor is pinned separately here), loops
// over the 8 player slots unregistering per-player color/level/fellowship
// APT names, then tears down the loading-type registration, background,
// audio, "GUI:Level" APT text and the MainMenuToSubMenu transition group
// before clearing the loading-screen slot at 0x012F49B0 and chaining to the
// shared 0x00490470 base destructor.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() {}
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}

	void format( AsciiString fmt, ... );
};

class UnicodeString
{
public:
	~UnicodeString();

private:
	void *m_data;
};

class GameTextInterface
{
public:
#define GAME_TEXT_SLOT(n) virtual void _gt_##n();
	GAME_TEXT_SLOT(0) GAME_TEXT_SLOT(1) GAME_TEXT_SLOT(2)
	GAME_TEXT_SLOT(3) GAME_TEXT_SLOT(4) GAME_TEXT_SLOT(5)
	GAME_TEXT_SLOT(6) GAME_TEXT_SLOT(7) GAME_TEXT_SLOT(8)
	GAME_TEXT_SLOT(9)
#undef GAME_TEXT_SLOT
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

class Rva0051D690Audio
{
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(04) AUDIO_SLOT(08) AUDIO_SLOT(0C)
	AUDIO_SLOT(10) AUDIO_SLOT(14) AUDIO_SLOT(18) AUDIO_SLOT(1C)
	AUDIO_SLOT(20) AUDIO_SLOT(24) AUDIO_SLOT(28) AUDIO_SLOT(2C)
	AUDIO_SLOT(30) AUDIO_SLOT(34) AUDIO_SLOT(38) AUDIO_SLOT(3C)
	AUDIO_SLOT(40) AUDIO_SLOT(44) AUDIO_SLOT(48) AUDIO_SLOT(4C)
	AUDIO_SLOT(50) AUDIO_SLOT(54) AUDIO_SLOT(58) AUDIO_SLOT(5C)
	AUDIO_SLOT(60) AUDIO_SLOT(64) AUDIO_SLOT(68)
#undef AUDIO_SLOT
	virtual void slot6c( int a, int b, int c );
};

extern Rva0051D690Audio *TheAudioClientUpdate;

class GameWindowTransitionsHandler
{
public:
	void setGroup( AsciiString group );
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

// The holder object at 0x012F19E8 is the same address as g_theWindowManager;
// this TU-local view only carries the one method used here (matches the
// take0046DD00/DE10/DEF0 family in S4DrainStringVector.cpp and
// Gen00525EE0MapRefresh.cpp).
struct S4Holder0046DBB0
{
	void take0046DD00( const AsciiString &s );
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init();
	virtual void loadIniFilesFromLegend();
	virtual void reset();
	virtual void update();
	virtual void draw();
};

class WindowManager : public SubsystemInterface
{
public:
	virtual ~WindowManager();
	virtual void bfmeSlot06();
	virtual void bfmeSlot07();
	virtual void bfmeSlot08();
	virtual void bfmeSlot09();
	virtual void bfmeSlot10();
	virtual void bfmeSlot11();
	virtual void bfmeSlot12();
	virtual void bfmeSlot13();
	virtual void bfmeSlot14( bool flag );

	void _bfme_removeNamedAptGadget( const AsciiString &name );
	void bfme_hideBackground( bool flag );
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

class Gen005207C0Member
{
public:
	void bfmeReset( void );
	~Gen005207C0Member();
};

// Address/behaviour-derived: an owner pointer released at the top of this
// destructor. Never instantiated locally, only called through, so the extra
// slots stay pure declarations.
class Rva0051B7E0Owner
{
public:
	virtual void bfmeSlot0();
	virtual void bfmeSlot1( bool flag );
	virtual void bfmeSlot2();
	virtual void bfmeSlot3( bool flag );
};

class Gen_0051b720Base
{
public:
	~Gen_0051b720Base();
};

class BfmeGameLoadingScreen : public Gen_0051b720Base
{
public:
	~BfmeGameLoadingScreen();

private:
	unsigned char m_unmodelled00[ 0x10 ];
	Rva0051B7E0Owner *m_owner;
	unsigned char m_unmodelled14[ 4 ];
	Gen005207C0Member m_previewState;
};

BfmeGameLoadingScreen::~BfmeGameLoadingScreen()
{
	*(unsigned *)this = 0x1106070u;

	m_owner->bfmeSlot3( false );
	if( m_owner )
		m_owner->bfmeSlot1( true );
	m_owner = 0;

	m_previewState.bfmeReset();

	AsciiString colorName;
	AsciiString clipName;
	for( int index = 0; index < 8; ++index )
	{
		colorName.format( AsciiString( "GameLoading:PlayerColor:%d" ), index );
		( reinterpret_cast<S4Holder0046DBB0 **>( 0x012f19e8 ) )[ 0 ]->take0046DD00( colorName );

		clipName.format( AsciiString( "UIClip/Level/%d" ), index );
		g_theWindowManager->_bfme_removeNamedAptGadget( clipName );

		clipName.format( AsciiString( "UIClip/Fellowship/%d" ), index );
		g_theWindowManager->_bfme_removeNamedAptGadget( clipName );
	}

	{
		AsciiString name( "GameLoadingType" );
		( reinterpret_cast<S4Holder0046DBB0 **>( 0x012f19e8 ) )[ 0 ]->take0046DD00( name );
	}

	g_theWindowManager->bfme_hideBackground( false );
	g_theWindowManager->bfmeSlot14( true );

	TheAudioClientUpdate->slot6c( 2, 1, 0 );

	{
		AsciiString labelKey( "GUI:Level" );
		UnicodeString text = TheGameText->fetch( "GUI:Level" );
		g_theWindowManager->bfme_setAptText( labelKey, text );
	}

	{
		AsciiString group( "MainMenuToSubMenu" );
		TheTransitionHandler->setGroup( group );
	}

	*(unsigned *)0x012f49b0 = 0;
}
