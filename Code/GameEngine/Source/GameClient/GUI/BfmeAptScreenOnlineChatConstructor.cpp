// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineChat constructor, retail 0x00536DC0, 1423 bytes.
// The 0x01106F58 vtable, matching destructor at 0x0052D7C0, singleton, and
// AptOnlineChat callback strings identify this constructor.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}
};

struct ChatStringVector
{
	AsciiString *begin;
	AsciiString *end;
	AsciiString *capacity;
	__forceinline ChatStringVector() : begin( 0 ), end( 0 ), capacity( 0 ) {}
};

class BfmeAptGameWindow
{
public:
	__forceinline BfmeAptGameWindow( void *context )
		: m_context( context ), m_tail( 0 ) {}
	virtual ~BfmeAptGameWindow() {}

private:
	ChatStringVector m_vector0;
	ChatStringVector m_vector1;
	ChatStringVector m_vector2;
	ChatStringVector m_vector3;
	void *m_context;
	int m_tail;
};

class BfmeThingTC
{
public:
	void bfmeBaseTC();
};

extern "C" const void *_bfmeVftTC[];

class InGameChatSlot
{
public:
	__forceinline InGameChatSlot()
	{
		( (BfmeThingTC *)this )->bfmeBaseTC();
		m_bfmeVft = (void *)_bfmeVftTC;
		m_bfmeWhat = (void *)4;
	}
	~InGameChatSlot();

	void *m_bfmeVft;
	unsigned char m_bfmeGap[ 8 ];
	void *m_bfmeWhat;
};

typedef void (*ChatCallback)();

struct ChatFunctorWrapper
{
	__forceinline ChatFunctorWrapper( ChatCallback callback )
	{
		m_refCount = 0;
		m_vtable = (void *)0x010F6F90;
		m_callback = callback;
	}

	void *m_vtable;
	unsigned int m_refCount;
	ChatCallback m_callback;
};

class ChatFunctorHolder
{
public:
	__forceinline ChatFunctorHolder( ChatCallback callback )
	{
		m_ptr = new ChatFunctorWrapper( callback );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	ChatFunctorHolder( const ChatFunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	ChatFunctorWrapper *m_ptr;
};

class __single_inheritance ChatFunctorTarget;
typedef void (ChatFunctorTarget::*ChatFunctorMethod)( void );

struct ChatFunctorBinding
{
	ChatFunctorBinding( ChatFunctorMethod method, ChatFunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	ChatFunctorTarget *m_target;
	ChatFunctorMethod m_method;
};

struct ChatFunctorWrapperHead
{
	__forceinline ChatFunctorWrapperHead()
	{
		m_refCount = 0;
		m_vtable = (void *)0x01106F90;
	}

	void *m_vtable;
	unsigned int m_refCount;
};

struct ChatBoundFunctorWrapper : ChatFunctorWrapperHead
{
	__forceinline ChatBoundFunctorWrapper( const ChatFunctorBinding &binding )
		: m_binding( binding ) {}

	ChatFunctorBinding m_binding;
};

class ChatBoundFunctorHolder
{
public:
	__forceinline ChatBoundFunctorHolder( ChatFunctorBinding binding )
	{
		m_ptr = new ChatBoundFunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	ChatBoundFunctorHolder( const ChatBoundFunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	ChatBoundFunctorWrapper *m_ptr;
};

struct ChatInitFunctorWrapperHead
{
	__forceinline ChatInitFunctorWrapperHead()
	{
		m_refCount = 0;
		m_vtable = (void *)0x01106F9C;
	}

	void *m_vtable;
	unsigned int m_refCount;
};

struct ChatInitFunctorWrapper : ChatInitFunctorWrapperHead
{
	__forceinline ChatInitFunctorWrapper( const ChatFunctorBinding &binding )
		: m_binding( binding ) {}

	ChatFunctorBinding m_binding;
};

class ChatInitFunctorHolder
{
public:
	__forceinline ChatInitFunctorHolder( ChatFunctorBinding binding )
	{
		m_ptr = new ChatInitFunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	ChatInitFunctorHolder( const ChatInitFunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	ChatInitFunctorWrapper *m_ptr;
};

extern void j_000338ed();
extern void j_0003df14();
extern void j_0002567b();
extern void j_00013d31();
extern void j_0003ff76();
extern void j_0001b3dd();
extern void j_00018886();
extern void j_000286be();
extern void j_0003a44a();
extern void j_0004a5ca();
extern void j_00029249();
extern void j_00029d61();
extern void j_00047258();

class __single_inheritance ChatCallbackRegistry
{
public:
	typedef void (ChatCallbackRegistry::*StaticRegistrar)(
		const AsciiString &, ChatFunctorHolder );
	typedef void (ChatCallbackRegistry::*BoundRegistrar)(
		const AsciiString &, ChatBoundFunctorHolder );

	static __forceinline StaticRegistrar staticRegistrar()
	{
		union Bits { StaticRegistrar member; void (*code)(); } bits;
		bits.code = j_000338ed;
		return bits.member;
	}

	static __forceinline BoundRegistrar boundRegistrar()
	{
		union Bits { BoundRegistrar member; void (*code)(); } bits;
		bits.code = j_000338ed;
		return bits.member;
	}
};

typedef void (*ChatInitRegistrar)( const AsciiString &, ChatInitFunctorHolder );

extern void *TheBfmeOnlineChat;

class BfmeAptScreenOnlineChat : public BfmeAptGameWindow
{
public:
	BfmeAptScreenOnlineChat( void *context );
	virtual ~BfmeAptScreenOnlineChat();
	virtual void aptSlot0() {}
	virtual void aptSlot1() {}

private:
	char m_field3c;
	int m_field40;
	int m_field44;
	int m_field48;
	int m_field4c;
	int m_field50;
	int m_field54;
	InGameChatSlot m_slot0;
	InGameChatSlot m_slot1;
	InGameChatSlot m_slot2;
	InGameChatSlot m_slot3;
	char m_field98;
	int m_field9c;
	int m_fielda0;
	int m_fielda4;
	int m_fielda8;
	int m_fieldac;
	int m_fieldb0;
	int m_fieldb4;
	AsciiString m_name;
};

union ChatMethodBits
{
	ChatCallback callback;
	ChatFunctorMethod member;
	unsigned int words[ 2 ];
};

BfmeAptScreenOnlineChat::BfmeAptScreenOnlineChat( void *context )
	: BfmeAptGameWindow( context ), m_field3c( 0 ), m_field40( 0 ),
	m_field44( 0 ), m_field48( 0 ), m_field4c( 0 ), m_field50( 0 ),
	m_field54( 0 ), m_slot0(), m_slot1(), m_slot2(), m_slot3(),
	m_field98( 0 ), m_field9c( 0 ), m_fielda0( 0 ), m_fielda4( 0 ),
	m_fielda8( 4 ), m_fieldac( 0 ), m_fieldb0( 0 ), m_fieldb4( 0 ),
	m_name( "APT:NULL" )
{
	if( TheBfmeOnlineChat == 0 )
	{
		TheBfmeOnlineChat = this;
		ChatCallbackRegistry *registry = (ChatCallbackRegistry *)this;
		ChatMethodBits callback;

		callback.words[ 0 ] = (unsigned int)j_0002567b;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnlineChat::QuickMatch" );
			( registry->*ChatCallbackRegistry::staticRegistrar() )( name,
				ChatFunctorHolder( callback.callback ) );
		}
		callback.words[ 0 ] = (unsigned int)j_00013d31;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnlineChat::OnBttnCancel" );
			( registry->*ChatCallbackRegistry::boundRegistrar() )( name,
				ChatBoundFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
		callback.words[ 0 ] = (unsigned int)j_0003ff76;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnlineChat::OnBttnAccept" );
			( registry->*ChatCallbackRegistry::boundRegistrar() )( name,
				ChatBoundFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
		callback.words[ 0 ] = (unsigned int)j_0001b3dd;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnlineChat::OnBttnEnterText" );
			( registry->*ChatCallbackRegistry::boundRegistrar() )( name,
				ChatBoundFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
		callback.words[ 0 ] = (unsigned int)j_00018886;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnlineChat::OnBttnAddFriend" );
			( registry->*ChatCallbackRegistry::boundRegistrar() )( name,
				ChatBoundFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
		callback.words[ 0 ] = (unsigned int)j_000286be;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnlineChat::OnBttnAddIgnore" );
			( registry->*ChatCallbackRegistry::boundRegistrar() )( name,
				ChatBoundFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
		callback.words[ 0 ] = (unsigned int)j_0003a44a;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnlineChat::OnBttnFriendList" );
			( registry->*ChatCallbackRegistry::boundRegistrar() )( name,
				ChatBoundFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
		callback.words[ 0 ] = (unsigned int)j_0004a5ca;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnlineChat::OnBttnIgnoreList" );
			( registry->*ChatCallbackRegistry::boundRegistrar() )( name,
				ChatBoundFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
		callback.words[ 0 ] = (unsigned int)j_00029249;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnlineChat::OnBttnPlayerList" );
			( registry->*ChatCallbackRegistry::boundRegistrar() )( name,
				ChatBoundFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
		callback.words[ 0 ] = (unsigned int)j_00029d61;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::Chat::OnBttnRemoveIgnore" );
			( registry->*ChatCallbackRegistry::boundRegistrar() )( name,
				ChatBoundFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
		callback.words[ 0 ] = (unsigned int)j_00047258;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnlineChat::InitGadgets" );
			( (ChatInitRegistrar)j_0003df14 )( name,
				ChatInitFunctorHolder( ChatFunctorBinding(
					callback.member,
					(ChatFunctorTarget *)this ) ) );
		}
	}
}
