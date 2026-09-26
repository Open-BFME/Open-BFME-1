#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// BfmeAptScreenMainMenu constructor, retail 0x0051F3A0, 3409 bytes.
//
// The first-instance branch publishes the object at 0x012F49B4, registers the
// 26 fscommand callbacks of MainMenu.apt (22 plain Rva0051EDB0-held
// showAptScreen bindings, three Rva0051EE20-held showAptScreenWithArg bindings
// that all resolve to bfmeProvide 0x0051E9B0, and the
// Rva0051EE90-held RenderCredits binding through showPalantirScreen), pulls the
// map path through GetModuleFileNameW into the +0x268 TTD member, then bumps
// the TimesInGame counter and reads FlashTutorial through OptionPreferences.
//
// The +0x218 registry subobject is a real secondary base here: retail stores
// its vftable (0x011061C0) in constructor-initializer position between the
// primary store and the member initializers, and its presence is what makes
// the EH state numbering jump 0 -> 2 when the TTD member lands.

// by-value string plumbing, same shapes as AptScreenFactories.cpp
template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set( const StringBase<T> &other );
	void trim();

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

struct UnicodeStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
};

class UnicodeString
{
public:
	UnicodeString() : m_data( 0 ) {}
	UnicodeString( const unsigned short *text );
	UnicodeString( const UnicodeString &other );
	~UnicodeString();
	const unsigned short *str() const
	{
		return m_data ? (const unsigned short *)((char *)m_data + 8)
			: (const unsigned short *)0x0107388C;
	}

private:
	UnicodeStringData *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

extern "C" __declspec(dllimport) unsigned long __stdcall GetModuleFileNameW(
	void *module, unsigned short *filename, unsigned long size );

typedef int Int;
typedef unsigned char Bool;

class __multiple_inheritance FunctorTarget;
class __multiple_inheritance BfmeAptScreenMainMenu;
typedef void (BfmeAptScreenMainMenu::*FunctorMethod)( void );

// 16-byte bound-method payload: target, refcount slot, {code, delta}.
struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	unsigned int m_unmodelled;
	FunctorMethod m_method;
};

// the holder types ARE the callee parameter types: each binds a 16-byte
// FunctorBinding by value and builds in the callee's argument slot
class Rva0051EDB0FunctorHolder
{
public:
	Rva0051EDB0FunctorHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

class Rva0051EE20FunctorHolder
{
public:
	Rva0051EE20FunctorHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

class Rva0051EE90FunctorHolder
{
public:
	Rva0051EE90FunctorHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

// primary base, retail size through the +0x218 boundary
class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( void *context );
	virtual void _bfme_noop();
	void _bfme_showAptScreen( const AsciiString &name,
		Rva0051EDB0FunctorHolder callback );
	void _bfme_showAptScreenWithArg( const AsciiString &name, void *argument,
		Rva0051EE20FunctorHolder callback );

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

// the +0x218 registry subobject: a tracked 0x40-byte secondary base; novtable
// suppresses its own vftable store so only the derived's lands
class __declspec(novtable) Rva00465200GameWindow
{
public:
	Rva00465200GameWindow() {}
	virtual ~Rva00465200GameWindow();
	void showPalantirScreen( const AsciiString &name,
		Rva0051EE90FunctorHolder callback );

private:
	char m_unmodelled[ 0x3C ];
};

class BfmeA1024
{
public:
	void bfmeGo1024A( int image, int logo );
};

struct Rva00579160Manager {};
extern Rva00579160Manager *Rva00579160TheManager;

class ClientRoot4120
{
public:
	unsigned char m_pad[ 0xC6 ];
	unsigned char m_resolutionChangePending;
};

extern ClientRoot4120 *TheGameClient;

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

// a tracked 4-byte member: empty store ctor, real dtor
class RvaPtr27c
{
public:
	RvaPtr27c() : m_v( 0 ) {}
	~RvaPtr27c();

private:
	void *m_v;
};

class BfmeAptFunctorMarker {};

struct Rva012F49B4Thing {};
extern Rva012F49B4Thing *g_rva012F49B4;

class Mouse
{
public:
	void _bfme_setEngineVisibility( bool visible );
};

extern Mouse *TheMouse;

class GlobalData
{
public:
	unsigned char m_pad0[ 0xBB4 ];
	unsigned char m_shellMapOn;
	unsigned char m_pad1[ 0x20A ];
	unsigned char m_b0DBF;
};

extern GlobalData *TheWritableGlobalData;

class BfmeThingTTD
{
public:
	BfmeThingTTD();
	~BfmeThingTTD();
	void initialize( const unsigned short *text, const unsigned short *path );

private:
	int m_bfme00;
	int m_bfme04;
	char m_bfme08;
	char m_bfme09;
	char m_bfme0a;
	char m_bfmePad;
	long m_bfmeHr;
	int m_bfme10;
};

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual bool load( AsciiString filename );
	virtual bool write();
	Int getInt( AsciiString key, Int defaultValue ) const;
	void setInt( AsciiString key, Int val );
	bool getBool( AsciiString key, bool defaultValue ) const;
	void setBool( AsciiString key, bool val );

private:
	char m_map[ 0xC ];
	AsciiString m_filename;
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
};

class __multiple_inheritance BfmeAptScreenMainMenu
	: public _bfme_AptGameWindow, public Rva00465200GameWindow,
	public BfmeAptFunctorMarker
{
public:
	BfmeAptScreenMainMenu( void *context );
	virtual ~BfmeAptScreenMainMenu();

	void _bfme_onInitialized();
	void _bfme_goodCampaign();
	void _bfme_evilCampaign();
	void _bfme_continueCampaign();
	void _bfme_loadCampaign();
	void _bfme_skirmish();
	void _bfme_options();
	void _bfme_credits();
	void _bfme_creditsExit();
	void _bfme_exitGame();
	void _bfme_tutorial();
	void _bfme_loadGame();
	void _bfme_loadReplay();
	void _bfme_levelSelect();
	void _bfme_lan();
	void _bfme_onlineButtonPressed();
	void _bfme_multiplayerButtonPressed();
	void _bfme_acceptFireWallButton();
	void _bfme_cancelFireWallButton();
	void _bfme_battleSchool();
	void _bfme_tutorialExit();
	void _bfme_stopGameMovie();
	void bfmeProvide( const char *name, void *argument, bool setting );
	void _bfme_renderCredits();

private:
	Bool m_b258;
	Bool m_b259;
	Bool m_b25a;
	Bool m_b25b;
	Bool m_b25c;
	Bool m_b25d;
	Bool m_b25e;
	Int m_z260;
	Int m_i264;
	BfmeThingTTD m_ttd;
	RvaPtr27c m_p27c;
};

// ??0BfmeAptScreenMainMenu@@QAE@PAX@Z
BfmeAptScreenMainMenu::BfmeAptScreenMainMenu( void *context )
	: _bfme_AptGameWindow( context ),
	m_b258( false ), m_b259( false ), m_b25a( false ), m_b25b( false ),
	m_b25c( false ), m_b25d( false ), m_b25e( false ),
	m_i264( TheGameClient != 0 && TheGameClient->m_resolutionChangePending != 0
		? 8 : 0 ),
	m_ttd()
{
	if( g_rva012F49B4 == 0 )
	{
		_bfme_AptGameWindow *registry = (_bfme_AptGameWindow *)( (char *)this + 0x218 );
		g_rva012F49B4 = (Rva012F49B4Thing *)this;

		{
			AsciiString logo( "LogoWithShadow" );
			AsciiString image( "Image" );
			((BfmeA1024 *)Rva00579160TheManager)->bfmeGo1024A(
				(int)&image, (int)&logo );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_onInitialized;
			AsciiString name( "AptMainMenu::OnInitialized" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_goodCampaign;
			AsciiString name( "AptMainMenu::GoodCampaign" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_evilCampaign;
			AsciiString name( "AptMainMenu::EvilCampaign" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_continueCampaign;
			AsciiString name( "AptMainMenu::ContinueCampaign" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_loadCampaign;
			AsciiString name( "AptMainMenu::LoadCampaign" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_skirmish;
			AsciiString name( "AptMainMenu::Skirmish" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_options;
			AsciiString name( "AptMainMenu::Options" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_credits;
			AsciiString name( "AptMainMenu::Credits" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_creditsExit;
			AsciiString name( "AptMainMenu::CreditsExit" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_exitGame;
			AsciiString name( "AptMainMenu::ExitGame" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_tutorial;
			AsciiString name( "AptMainMenu::Tutorial" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_loadGame;
			AsciiString name( "AptMainMenu::LoadGame" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_loadReplay;
			AsciiString name( "AptMainMenu::LoadReplay" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_levelSelect;
			AsciiString name( "AptMainMenu::LevelSelect" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_lan;
			AsciiString name( "AptMainMenu::LAN" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_onlineButtonPressed;
			AsciiString name( "AptMainMenu::OnlineButtonPressed" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_multiplayerButtonPressed;
			AsciiString name( "AptMainMenu::MultiplayerButtonPressed" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_acceptFireWallButton;
			AsciiString name( "AptMainMenu::AcceptFireWallButton" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_cancelFireWallButton;
			AsciiString name( "AptMainMenu::CancelFireWallButton" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_battleSchool;
			AsciiString name( "AptMainMenu::BattleSchool" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_tutorialExit;
			AsciiString name( "AptMainMenu::TutorialExit" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_stopGameMovie;
			AsciiString name( "AptMainMenu::StopGameMovie" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::bfmeProvide;
			AsciiString name( "MainMenuLevel" );
			registry->_bfme_showAptScreenWithArg( name, (void *)0,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::bfmeProvide;
			AsciiString name( "MainMenuContinueCampaign" );
			registry->_bfme_showAptScreenWithArg( name, (void *)1,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::bfmeProvide;
			AsciiString name( "BlinkBattleSchoolOff" );
			registry->_bfme_showAptScreenWithArg( name, (void *)3,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenMainMenu::_bfme_renderCredits;
			AsciiString name( "AptMainMenu::RenderCredits" );
			showPalantirScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		unsigned short path[ 0x104 ] = { 0 };
		GetModuleFileNameW( 0, path, 0x208 );
		m_ttd.initialize(
			TheGameText->fetch( "GUI:Command&ConquerGenerals" ).str(), path );

		TheWritableGlobalData->m_b0DBF = 0;
		TheMouse->_bfme_setEngineVisibility( false );

		OptionPreferences prefs;
		int count = prefs.getInt( AsciiString( "TimesInGame" ), 0 ) + 1;
		prefs.setInt( AsciiString( "TimesInGame" ), count );
		m_b25d = prefs.getBool( AsciiString( "FlashTutorial" ), true );
		if( count > 5 && m_b25d )
		{
			m_b25d = false;
			prefs.setBool( AsciiString( "FlashTutorial" ), false );
		}
		prefs.write();

		if( !TheWritableGlobalData->m_shellMapOn )
			m_b25a = true;
	}
}
