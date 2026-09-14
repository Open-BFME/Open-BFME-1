// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineHome constructor, retail 0x005484E0, 1636 bytes.
// The 0x01107B70 vtable and the matched destructor at 0x00545FF0 identify
// the screen. The callback strings and image globals identify each setup
// registration in the first-instance branch.

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
	void format( AsciiString format, ... );
};

struct HomeStringVector
{
	AsciiString *begin;
	AsciiString *end;
	AsciiString *capacity;
	__forceinline HomeStringVector() : begin( 0 ), end( 0 ), capacity( 0 ) {}
};

class BfmeAptGameWindow
{
public:
	__forceinline BfmeAptGameWindow( void *context )
		: m_context( context ), m_tail( 0 ) {}
	virtual ~BfmeAptGameWindow() {}

private:
	HomeStringVector m_vector0;
	HomeStringVector m_vector1;
	HomeStringVector m_vector2;
	HomeStringVector m_vector3;
	void *m_context;
	int m_tail;
};

class __single_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	FunctorMethod m_method;
};

struct HomePlainFunctorWrapperHead
{
	HomePlainFunctorWrapperHead()
	{
		m_refCount = 0;
		m_vtable = (void *)0x01107BE0;
	}

	void *m_vtable;
	unsigned int m_refCount;
};

struct HomePlainFunctorWrapper : HomePlainFunctorWrapperHead
{
	HomePlainFunctorWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

struct HomeInitFunctorWrapperHead
{
	HomeInitFunctorWrapperHead()
	{
		m_refCount = 0;
		m_vtable = (void *)0x01107BEC;
	}

	void *m_vtable;
	unsigned int m_refCount;
};

struct HomeInitFunctorWrapper : HomeInitFunctorWrapperHead
{
	HomeInitFunctorWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

struct HomeArgFunctorWrapperHead
{
	HomeArgFunctorWrapperHead()
	{
		m_refCount = 0;
		m_vtable = (void *)0x01107BF8;
	}

	void *m_vtable;
	unsigned int m_refCount;
};

struct HomeArgFunctorWrapper : HomeArgFunctorWrapperHead
{
	HomeArgFunctorWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class HomePlainFunctorHolder
{
public:
	__forceinline HomePlainFunctorHolder( FunctorBinding binding )
	{
		m_ptr = new HomePlainFunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	HomePlainFunctorWrapper *m_ptr;
};

class HomeArgFunctorHolder
{
public:
	__forceinline HomeArgFunctorHolder( FunctorBinding binding )
	{
		m_ptr = new HomeArgFunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	HomeArgFunctorWrapper *m_ptr;
};

class Rva0050F8B0FunctorHolder
{
public:
	__forceinline Rva0050F8B0FunctorHolder( FunctorBinding binding )
	{
		m_ptr = new HomePlainFunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	__forceinline Rva0050F8B0FunctorHolder( const Rva0050F8B0FunctorHolder &other )
	{
		m_ptr = other.m_ptr;
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	HomePlainFunctorWrapper *m_ptr;
};

class HomeInitFunctorHolder
{
	public:
	__forceinline HomeInitFunctorHolder( FunctorBinding binding )
	{
		m_ptr = new HomeInitFunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	__forceinline HomeInitFunctorHolder( const HomeInitFunctorHolder &other )
	{
		m_ptr = other.m_ptr;
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	public:
	HomeInitFunctorWrapper *m_ptr;
};

extern void j_000338ed();
extern void j_0000acfe();
extern void j_0003df14();
extern void j_00019844();
extern void j_0003af0d();
extern void j_00046a2e();
extern void j_000316e2();
extern void j_000385e1();

class __single_inheritance HomeCallbackRegistry
{
public:
	typedef void (HomeCallbackRegistry::*PlainRegistrar)(
		const AsciiString &, HomePlainFunctorHolder );
	typedef void (HomeCallbackRegistry::*ArgRegistrar)(
		const AsciiString &, void *, HomeArgFunctorHolder );

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

typedef void (*HomeGadgetRegistrar)( const AsciiString &, HomePlainFunctorHolder );
typedef void (*HomeInitRegistrar)( const AsciiString &, HomeInitFunctorHolder );

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

	int peerRequestType;
	char m_body[ 0x190 ];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual bool isThreadRunning() = 0;
	virtual bool isConnected() = 0;
	virtual bool isConnecting() = 0;
	virtual void addRequest( const PeerRequest &request ) = 0;
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const AsciiString &text );
	void bfmeBindRva004650F0( const AsciiString &name, Rva0050F8B0FunctorHolder callback );
};

extern WindowManager *g_theWindowManager;
extern void j_00030cfb();
extern void *TheBfmeOnlineHomeSlot;
extern const char *g_onlineHomeGadgetsImage;
extern const char *g_onlineHomeGadgetsImageLevelIconMain;
extern const char *g_onlineHomeImageGondor;
extern const char *g_onlineHomeImageIsengard;
extern const char *g_onlineHomeImageRohan;
extern const char *g_onlineHomeImageMordor;
extern char g_aptPalantirNumberFormat[];
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern void j_0003f2c9();

class __single_inheritance HomeTextRegistry
{
public:
	typedef void (HomeTextRegistry::*SetText)( const AsciiString &, const AsciiString & );

	static __forceinline SetText setText()
	{
		union Bits { SetText member; void (*code)(); } bits;
		bits.code = j_00030cfb;
		return bits.member;
	}
};

class BfmeAptScreenOnlineHome : public BfmeAptGameWindow
{
public:
	BfmeAptScreenOnlineHome( void *context );
	virtual ~BfmeAptScreenOnlineHome();

private:
	void *m_messageOfTheDay;
};

union HomeMethodBits
{
	FunctorMethod m_method;
	unsigned int m_words[ 2 ];
};

BfmeAptScreenOnlineHome::BfmeAptScreenOnlineHome( void *context )
	: BfmeAptGameWindow( context )
{
	*(unsigned int *)this = 0x01107B70;
	m_messageOfTheDay = 0;

	if( TheBfmeOnlineHomeSlot == 0 )
	{
		TheBfmeOnlineHomeSlot = this;

		{
			AsciiString key( "ScrollShroud" );
			AsciiString image( g_onlineHomeGadgetsImage );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				( int )&image, ( int )&key );
		}
		{
			AsciiString key( "ScrollShroud" );
			AsciiString image( g_onlineHomeGadgetsImageLevelIconMain );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				( int )&image, ( int )&key );
		}
		{
			AsciiString key( "AptIconGondor" );
			AsciiString image( g_onlineHomeImageGondor );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				( int )&image, ( int )&key );
		}
		{
			AsciiString key( "AptIconIsengard" );
			AsciiString image( g_onlineHomeImageIsengard );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				( int )&image, ( int )&key );
		}
		{
			AsciiString key( "AptIconRohan" );
			AsciiString image( g_onlineHomeImageRohan );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				( int )&image, ( int )&key );
		}
		{
			AsciiString key( "AptIconMordor" );
			AsciiString image( g_onlineHomeImageMordor );
			( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A(
				( int )&image, ( int )&key );
		}

		HomeCallbackRegistry *registry = (HomeCallbackRegistry *)this;
		{
			HomeMethodBits methodBits;
			methodBits.m_words[ 0 ] = ( unsigned int )j_00019844;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "AptOnline::OnlineHome::OfficialSite" );
			( registry->*HomeCallbackRegistry::plainRegistrar() )( name,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}
		{
			HomeMethodBits methodBits;
			methodBits.m_words[ 0 ] = ( unsigned int )j_0003af0d;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "AptOnline::OnlineHome::OnOpened" );
			( registry->*HomeCallbackRegistry::plainRegistrar() )( name,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}
		{
			HomeMethodBits methodBits;
			methodBits.m_words[ 0 ] = ( unsigned int )j_00046a2e;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "AptOnlineHome::InitGadgets" );
			( (HomeInitRegistrar)j_0003df14 )( name,
				HomeInitFunctorHolder( FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) ) );
		}
		{
			HomeMethodBits methodBits;
			methodBits.m_words[ 0 ] = ( unsigned int )j_000316e2;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "OnlineShell/OnlineHome/tooltipPlayerLevelIcon" );
			g_theWindowManager->bfmeBindRva004650F0( name,
				Rva0050F8B0FunctorHolder( FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) ) );
		}
		{
			HomeMethodBits methodBits;
			methodBits.m_words[ 0 ] = ( unsigned int )j_000385e1;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "ShowOnlineHomeMovies" );
			( registry->*HomeCallbackRegistry::argRegistrar() )( name, ( void * )0,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}

		AsciiString value;
		value.format( AsciiString( g_aptPalantirNumberFormat ), 0 );
	{
		AsciiString name( "APT:GamesInProgressNum" );
		AsciiString copy( value );
		( (HomeTextRegistry *)g_theWindowManager->*HomeTextRegistry::setText() )( name, copy );
	}
	{
		value.format( AsciiString( g_aptPalantirNumberFormat ), 1 );
		AsciiString name( "APT:PlayersOnlineNum" );
		AsciiString copy( value );
		( (HomeTextRegistry *)g_theWindowManager->*HomeTextRegistry::setText() )( name, copy );
	}

		PeerRequest request;
		request.peerRequestType = 0x17;
		TheGameSpyPeerMessageQueue->addRequest( request );
		( ( void (__fastcall *)( BfmeAptScreenOnlineHome * ) )j_0003f2c9 )( this );
	}
}
