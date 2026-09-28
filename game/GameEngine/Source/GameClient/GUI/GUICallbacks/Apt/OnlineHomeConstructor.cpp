// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineHome constructor, retail 0x005484E0, 1636 bytes.
// The OnlineHome vtable at 0x01107B70, the matching destructor at 0x00545FF0,
// and the OnlineHome gadget strings identify this constructor. The factory at
// 0x0055BAA0 calls this constructor. The body registers the five OnlineHome
// callbacks and the two online counters.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void __cdecl format( AsciiString format, ... );
};

struct HomeZeroVector
{
	int *begin;
	int *end;
	int *capacity;

	__forceinline HomeZeroVector() : begin( 0 ), end( 0 ), capacity( 0 ) {}
};

class BfmeAptGameWindow
{
public:
	__forceinline BfmeAptGameWindow( int context )
		: m_vector0(), m_vector1(), m_vector2(), m_vector3()
		, m_context( context ), m_tail( 0 ) {}
	virtual ~BfmeAptGameWindow();

private:
	HomeZeroVector m_vector0;
	HomeZeroVector m_vector1;
	HomeZeroVector m_vector2;
	HomeZeroVector m_vector3;
	int m_context;
	int m_tail;
};

class __single_inheritance FunctorTarget {};
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	FunctorMethod m_method;
};

class HomeFunctorWrapperHead
{
public:
	HomeFunctorWrapperHead() : m_refCount( 0 ) {}
	virtual ~HomeFunctorWrapperHead();

	unsigned int m_refCount;
};

class HomeFunctorWrapperBE0 : public HomeFunctorWrapperHead
{
public:
	HomeFunctorWrapperBE0( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class HomeFunctorWrapperBEC : public HomeFunctorWrapperHead
{
public:
	HomeFunctorWrapperBEC( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class HomeFunctorWrapperBF8 : public HomeFunctorWrapperHead
{
public:
	HomeFunctorWrapperBF8( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class Rva0050F8B0FunctorHolder
{
public:
	__forceinline Rva0050F8B0FunctorHolder( FunctorBinding binding )
	{
		m_ptr = new HomeFunctorWrapperBE0( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	__forceinline Rva0050F8B0FunctorHolder(
		const Rva0050F8B0FunctorHolder &other )
		: m_ptr( other.m_ptr ) {}
	~Rva0050F8B0FunctorHolder();

	HomeFunctorWrapperBE0 *m_ptr;
};

class HomeFunctorHolderBEC
{
public:
	__forceinline HomeFunctorHolderBEC( FunctorBinding binding )
	{
		m_ptr = new HomeFunctorWrapperBEC( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	__forceinline HomeFunctorHolderBEC( const HomeFunctorHolderBEC &other )
		: m_ptr( other.m_ptr ) {}
	~HomeFunctorHolderBEC();

	HomeFunctorWrapperBEC *m_ptr;
};

class HomeFunctorHolderBF8
{
public:
	__forceinline HomeFunctorHolderBF8( FunctorBinding binding )
	{
		m_ptr = new HomeFunctorWrapperBF8( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	__forceinline HomeFunctorHolderBF8( const HomeFunctorHolderBF8 &other )
		: m_ptr( other.m_ptr ) {}
	~HomeFunctorHolderBF8();

	HomeFunctorWrapperBF8 *m_ptr;
};

extern void j_000338ed();
extern void j_0000acfe();
extern void j_0003df14();

class HomeRegistry
{
public:
	typedef void (HomeRegistry::*PlainRegistrar)(
		const AsciiString &, Rva0050F8B0FunctorHolder );
	typedef void (HomeRegistry::*RefRegistrar)(
		const AsciiString &, HomeFunctorHolderBEC );
	typedef void (HomeRegistry::*ArgRegistrar)(
		const AsciiString &, void *, HomeFunctorHolderBF8 );

	static __forceinline PlainRegistrar plainRegistrar()
	{
		union Bits { PlainRegistrar member; void (*code)(); } bits;
		bits.code = j_000338ed;
		return bits.member;
	}
	static __forceinline ArgRegistrar argRegistrar()
	{
		union Bits { ArgRegistrar member; void (*code)(); } bits;
		bits.code = j_0000acfe;
		return bits.member;
	}
};

typedef void (*HomeRefRegistrar)( const AsciiString &, HomeFunctorHolderBEC );

class WindowManager
{
public:
	void bfmeBindRva004650F0( const AsciiString &, Rva0050F8B0FunctorHolder );
	void bfme_setAptText( const AsciiString &, const AsciiString & );
};

class BfmeA1024
{
public:
	void bfmeGo1024A( int image, int key );
};

class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();

	int m_type;
	char m_body[ 0x190 ];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface();
	virtual void startThread();
	virtual void endThread();
	virtual bool isThreadRunning();
	virtual bool isConnected();
	virtual bool isConnecting();
	virtual void addRequest( const PeerRequest &request );
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern WindowManager *g_theWindowManager;
extern const char *g_onlineHomeGadgetsImage;
extern const char *g_onlineHomeGadgetsImageLevelIconMain;
extern const char *g_d_012b7920;
extern const char *g_d_012b7924;
extern const char *g_d_012b7928;
extern const char *g_d_012b792c;
extern void *TheBfmeOnlineHomeSlot;

static FunctorMethod rawFunctorMethod( unsigned int address )
{
	union Bits { unsigned int raw; FunctorMethod member; } bits;
	bits.raw = address;
	return bits.member;
}

class BfmeAptScreenOnlineHome : public BfmeAptGameWindow
{
public:
	BfmeAptScreenOnlineHome( int context );
	virtual ~BfmeAptScreenOnlineHome();
	void rva00547730();

private:
	int m_field3c;
};

BfmeAptScreenOnlineHome::BfmeAptScreenOnlineHome( int context )
	: BfmeAptGameWindow( context ), m_field3c( 0 )
{
	if( TheBfmeOnlineHomeSlot == 0 )
	{
		TheBfmeOnlineHomeSlot = this;

		{
			AsciiString keyString( "ScrollShroud" );
			AsciiString imageString( g_onlineHomeGadgetsImage );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				(int)&imageString, (int)&keyString );
		}
		{
			AsciiString keyString( "ScrollShroud" );
			AsciiString imageString( g_onlineHomeGadgetsImageLevelIconMain );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				(int)&imageString, (int)&keyString );
		}
		{
			AsciiString keyString( "AptIconGondor" );
			AsciiString imageString( g_d_012b7920 );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				(int)&imageString, (int)&keyString );
		}
		{
			AsciiString keyString( "AptIconIsengard" );
			AsciiString imageString( g_d_012b7924 );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				(int)&imageString, (int)&keyString );
		}
		{
			AsciiString keyString( "AptIconRohan" );
			AsciiString imageString( g_d_012b7928 );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				(int)&imageString, (int)&keyString );
		}
		{
			AsciiString keyString( "AptIconMordor" );
			AsciiString imageString( g_d_012b792c );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				(int)&imageString, (int)&keyString );
		}

		HomeRegistry *registry = (HomeRegistry *)this;
		{
			FunctorMethod callback = rawFunctorMethod( 0x00419844 );
			AsciiString name( "AptOnline::OnlineHome::OfficialSite" );
			FunctorBinding binding( callback, (FunctorTarget *)this );
			(registry->*HomeRegistry::plainRegistrar())( name,
				Rva0050F8B0FunctorHolder( binding ) );
		}
		{
			FunctorMethod callback = rawFunctorMethod( 0x0043AF0D );
			AsciiString name( "AptOnline::OnlineHome::OnOpened" );
			FunctorBinding binding( callback, (FunctorTarget *)this );
			(registry->*HomeRegistry::plainRegistrar())( name,
				Rva0050F8B0FunctorHolder( binding ) );
		}
		{
			FunctorMethod callback = rawFunctorMethod( 0x00446A2E );
			AsciiString name( "AptOnlineHome::InitGadgets" );
			FunctorBinding binding( callback, (FunctorTarget *)this );
			((HomeRefRegistrar)j_0003df14)( name,
				HomeFunctorHolderBEC( binding ) );
		}
		{
			FunctorMethod callback = rawFunctorMethod( 0x004316E2 );
			AsciiString name( "OnlineShell/OnlineHome/tooltipPlayerLevelIcon" );
			FunctorBinding binding( callback, (FunctorTarget *)this );
			g_theWindowManager->bfmeBindRva004650F0( name,
				Rva0050F8B0FunctorHolder( binding ) );
		}
		{
			FunctorMethod callback = rawFunctorMethod( 0x004385E1 );
			AsciiString name( "ShowOnlineHomeMovies" );
			FunctorBinding binding( callback, (FunctorTarget *)this );
			(registry->*HomeRegistry::argRegistrar())( name, (void *)0,
				HomeFunctorHolderBF8( binding ) );
		}

		AsciiString games;
		games.format( AsciiString( "%d" ), 0 );
		{
			AsciiString gamesName( "APT:GamesInProgressNum" );
			AsciiString gamesCopy( games );
			g_theWindowManager->bfme_setAptText( gamesName, gamesCopy );
		}
		games.format( AsciiString( "%d" ), 1 );
		{
			AsciiString playersName( "APT:PlayersOnlineNum" );
			AsciiString playersCopy( games );
			g_theWindowManager->bfme_setAptText( playersName, playersCopy );
		}

	PeerRequest request;
	request.m_type = 0x17;
	TheGameSpyPeerMessageQueue->addRequest( request );
	rva00547730();
}
}
