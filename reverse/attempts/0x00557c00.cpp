// ??0BfmeOnlineProfileScreen@@QAE@PAX@Z
// partial score=0.55 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeOnlineProfileScreen destructor, retail 0x00553EE0, 702 bytes.
// Mirrors createAptScreenOnlineProfile (AptScreenFactories.cpp, retail
// 0x0055BBA0 / object ctor 0x00557C00, still gen_asm): the singleton lives at
// 0x012F4AB4 (TheBfmeOnlineProfileSlot). If this instance is the live
// singleton and g_theWindowManager (0x012F19E8) is set, it unregisters 8
// image gadgets (through _bfme_removeNamedAptGadget, already pinned by
// OnlineHomeDestructor.cpp) and 4 player-level-icon tooltips (through
// removeAptObject) by name, then clears the singleton. The base class
// destructor call (vfptr reset to ??_7BfmeAptGameWindow@@6B@ then
// bfmeDestroy(), pinned 0x00021FC1, reaching ??1S4Owner@@UAE@XZ) runs
// unconditionally, same shape as OnlineHomeDestructor.cpp / OnlineChatDestructor.cpp.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}
};

class BfmeAptGameWindow
{
public:
	virtual ~BfmeAptGameWindow()
	{
		bfmeDestroy();
	}
	void bfmeDestroy();

private:
	unsigned char m_unmodelled[ 0x38 ];
};

// FunctorBinding/holder plumbing shared by every registration call in the
// constructor below - same idiom as BfmeAptScreenQuitMenuConstructor.cpp.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	unsigned int m_unmodelled;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount( 0 ) {}
	virtual void invoke();

	unsigned int m_refCount;
};

// wraps the two tooltip-bind callbacks (retail wrapper vtable 0x01108604)
class Rva01108604FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva01108604FunctorWrapper( const FunctorBinding &binding ) : m_binding( binding ) {}

	FunctorBinding m_binding;
};

class Rva0050F8B0FunctorHolder
{
public:
	__forceinline Rva0050F8B0FunctorHolder( FunctorBinding binding )
	{
		m_ptr = new Rva01108604FunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	Rva01108604FunctorWrapper *m_ptr;
};

// wraps the four level-bar provider callbacks (retail wrapper vtable 0x01108610)
class Rva01108610FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva01108610FunctorWrapper( const FunctorBinding &binding ) : m_binding( binding ) {}

	FunctorBinding m_binding;
};

class Rva0050F920FunctorHolder
{
public:
	__forceinline Rva0050F920FunctorHolder( FunctorBinding binding )
	{
		m_ptr = new Rva01108610FunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	Rva01108610FunctorWrapper *m_ptr;
};

// address-derived pin: 0x004650F0 sibling WindowManager forward target,
// already claimed at ILT 0x0000F31C by pinharvest for the QuitMenu family.
class WindowManager
{
public:
	void _bfme_removeNamedAptGadget( const AsciiString &name );
	void removeAptObject( const AsciiString &name );
	void bfmeBindRva004650F0( const AsciiString &name, Rva0050F8B0FunctorHolder callback );
};

// this-call registration surface reached directly (no +0x218 secondary vtable
// on this single-inheritance screen); real body still an unclaimed dump, ILT
// already pinned at 0x0000ACFE for the QuitMenu/DisconnectScreen family.
class _bfme_AptGameWindow
{
public:
	void _bfme_showAptScreenWithArg( const AsciiString &name, void *argument,
		Rva0050F920FunctorHolder callback );
};

// already landed at 0x0046C790 (BfmeConv1024.cpp): looks an image up by name
// through TheMappedImageCollection and stores it into a gadget slot map at
// +0x6c; called here with pointers to on-stack AsciiStrings reinterpreted as
// the (int,int) signature retail compiled it with.
class BfmeA1024
{
public:
	void bfmeGo1024A( int image, int key );
};

extern WindowManager *g_theWindowManager;

class BfmeOnlineProfileScreen;
extern BfmeOnlineProfileScreen *TheBfmeOnlineProfileSlot;

extern const char *g_bfmeOnlineProfileImageA;
extern const char *g_bfmeOnlineProfileImageB;
extern const char *g_bfmeOnlineProfileImageC;
extern const char *g_bfmeOnlineProfileImageD;
extern const char *g_bfmeOnlineProfileImageLevelIconA;
extern const char *g_bfmeOnlineProfileImageLevelIconB;
extern const char *g_bfmeOnlineProfileImageLevelIconC;
extern const char *g_bfmeOnlineProfileImageLevelIconD;

class BfmeAptFunctorMarker {};

class __multiple_inheritance BfmeOnlineProfileScreen
	: public BfmeAptGameWindow, public BfmeAptFunctorMarker
{
public:
	BfmeOnlineProfileScreen( void *context );
	virtual ~BfmeOnlineProfileScreen();

private:
	// retail 0x00415B36 (ILT) - shared handler for all four tooltip binds
	void _bfme_tooltipCallback();
	// retail 0x004100EB (ILT) - shared provider for all four level-bar binds
	void _bfme_levelBarProvider();
	// retail 0x00954AA0 via ILT 0x00032849 - reads the context pointer at
	// +0x34 and refreshes cached GameSpy player stats
	// (see ?_bfme_cacheLocalPlayerStatsWithLocale@@YAXXZ, symbols.csv note)
	void _bfme_refreshCachedStats();
};

BfmeOnlineProfileScreen::~BfmeOnlineProfileScreen()
{
	if( TheBfmeOnlineProfileSlot == this )
	{
		if( g_theWindowManager )
		{
			{
				AsciiString name( g_bfmeOnlineProfileImageA );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageB );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageC );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageD );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageLevelIconA );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageLevelIconB );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageLevelIconC );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageLevelIconD );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconGondor" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconRohan" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconIsengard" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconMordor" );
				g_theWindowManager->removeAptObject( name );
			}
		}
		TheBfmeOnlineProfileSlot = 0;
	}
}

// BfmeOnlineProfileScreen constructor, retail 0x00557C00, 1659 bytes,
// ??0BfmeOnlineProfileScreen@@QAE@PAX@Z. Registers what the destructor above
// unregisters: 8 named apt gadgets (image + key, through BfmeA1024::bfmeGo1024A
// already landed at 0x0046C790), 4 tooltip binds sharing one callback, and
// 4 level-bar providers sharing another callback keyed by an integer 0..3;
// then refreshes cached GameSpy player stats. Refuses a second instance the
// same way createAptScreenOnlineProfile (AptScreenFactories.cpp) does.
BfmeOnlineProfileScreen::BfmeOnlineProfileScreen( void *context )
{
	*(int *)( (char *)this + 0x04 ) = 0;
	*(int *)( (char *)this + 0x08 ) = 0;
	*(int *)( (char *)this + 0x0c ) = 0;
	*(int *)( (char *)this + 0x10 ) = 0;
	*(int *)( (char *)this + 0x14 ) = 0;
	*(int *)( (char *)this + 0x18 ) = 0;
	*(int *)( (char *)this + 0x1c ) = 0;
	*(int *)( (char *)this + 0x20 ) = 0;
	*(int *)( (char *)this + 0x24 ) = 0;
	*(int *)( (char *)this + 0x28 ) = 0;
	*(int *)( (char *)this + 0x2c ) = 0;
	*(int *)( (char *)this + 0x30 ) = 0;
	*(void **)( (char *)this + 0x34 ) = context;
	*(int *)( (char *)this + 0x38 ) = 0;

	if( TheBfmeOnlineProfileSlot == 0 )
	{
		TheBfmeOnlineProfileSlot = this;

		{
			AsciiString key( "AptGondorImage" );
			AsciiString image( g_bfmeOnlineProfileImageA );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A( (int)&image, (int)&key );
		}
		{
			AsciiString key( "AptRohanImage" );
			AsciiString image( g_bfmeOnlineProfileImageB );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A( (int)&image, (int)&key );
		}
		{
			AsciiString key( "AptIsengardImage" );
			AsciiString image( g_bfmeOnlineProfileImageC );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A( (int)&image, (int)&key );
		}
		{
			AsciiString key( "AptMordorImage" );
			AsciiString image( g_bfmeOnlineProfileImageD );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A( (int)&image, (int)&key );
		}
		{
			AsciiString key( "ScrollShroud" );
			AsciiString image( g_bfmeOnlineProfileImageLevelIconA );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A( (int)&image, (int)&key );
		}
		{
			AsciiString key( "ScrollShroud" );
			AsciiString image( g_bfmeOnlineProfileImageLevelIconB );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A( (int)&image, (int)&key );
		}
		{
			AsciiString key( "ScrollShroud" );
			AsciiString image( g_bfmeOnlineProfileImageLevelIconC );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A( (int)&image, (int)&key );
		}
		{
			AsciiString key( "ScrollShroud" );
			AsciiString image( g_bfmeOnlineProfileImageLevelIconD );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A( (int)&image, (int)&key );
		}

		{
			FunctorMethod callback = (FunctorMethod)&BfmeOnlineProfileScreen::_bfme_tooltipCallback;
			AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconGondor" );
			( (WindowManager *)g_theWindowManager )->bfmeBindRva004650F0( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback = (FunctorMethod)&BfmeOnlineProfileScreen::_bfme_tooltipCallback;
			AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconRohan" );
			( (WindowManager *)g_theWindowManager )->bfmeBindRva004650F0( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback = (FunctorMethod)&BfmeOnlineProfileScreen::_bfme_tooltipCallback;
			AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconIsengard" );
			( (WindowManager *)g_theWindowManager )->bfmeBindRva004650F0( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback = (FunctorMethod)&BfmeOnlineProfileScreen::_bfme_tooltipCallback;
			AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconMordor" );
			( (WindowManager *)g_theWindowManager )->bfmeBindRva004650F0( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		{
			FunctorMethod callback = (FunctorMethod)&BfmeOnlineProfileScreen::_bfme_levelBarProvider;
			AsciiString name( "LevelBarA" );
			( (_bfme_AptGameWindow *)this )->_bfme_showAptScreenWithArg( name, (void *)0,
				Rva0050F920FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}
		{
			FunctorMethod callback = (FunctorMethod)&BfmeOnlineProfileScreen::_bfme_levelBarProvider;
			AsciiString name( "LevelBarB" );
			( (_bfme_AptGameWindow *)this )->_bfme_showAptScreenWithArg( name, (void *)1,
				Rva0050F920FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}
		{
			FunctorMethod callback = (FunctorMethod)&BfmeOnlineProfileScreen::_bfme_levelBarProvider;
			AsciiString name( "LevelBarC" );
			( (_bfme_AptGameWindow *)this )->_bfme_showAptScreenWithArg( name, (void *)2,
				Rva0050F920FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}
		{
			FunctorMethod callback = (FunctorMethod)&BfmeOnlineProfileScreen::_bfme_levelBarProvider;
			AsciiString name( "LevelBarD" );
			( (_bfme_AptGameWindow *)this )->_bfme_showAptScreenWithArg( name, (void *)3,
				Rva0050F920FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		_bfme_refreshCachedStats();
	}
}
