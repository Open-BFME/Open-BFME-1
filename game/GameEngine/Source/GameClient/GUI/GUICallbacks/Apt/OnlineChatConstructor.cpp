// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
//
// BfmeAptScreenOnlineChat constructor, retail 0x00536DC0, 1423 bytes.
// The vtable, singleton, destructor, and AptOnlineChat strings identify the
// class. The callback bodies use the retail addresses stored by this body.

#include "StringInline.h"

class BfmeAptWindowContext
{
public:
	BfmeAptWindowContext( int context ) : m_context( context ), m_z38( 0 ) {}

private:
	int m_context;
	int m_z38;
};

class Rva0050F8B0FunctorHolder;
class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( int context )
		: m_z04( 0 ), m_z08( 0 ), m_z0C( 0 ), m_z10( 0 ), m_z14( 0 ),
		m_z18( 0 ), m_z1C( 0 ), m_z20( 0 ), m_z24( 0 ), m_z28( 0 ),
		m_z2C( 0 ), m_z30( 0 ), m_context( context ) {}
	virtual ~_bfme_AptGameWindow();
	void _bfme_showAptScreen( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );

private:
	int m_z04;
	int m_z08;
	int m_z0C;
	int m_z10;
	int m_z14;
	int m_z18;
	int m_z1C;
	int m_z20;
	int m_z24;
	int m_z28;
	int m_z2C;
	int m_z30;
	BfmeAptWindowContext m_context;
};

class BfmeThingTC { public: void bfmeBaseTC(); };
// Retail table 0x011051EC is the vftable of Rva011051ECSkirmishField, the
// defining name recorded for that address in dir32_addresses.csv.
extern "C" const void *__identifier("??_7Rva011051ECSkirmishField@@6B@")[];
#define g_bfmeRva011051ECVt __identifier("??_7Rva011051ECSkirmishField@@6B@")

class InGameChatSlot
{
public:
	__forceinline InGameChatSlot()
	{
		((BfmeThingTC *)this)->bfmeBaseTC();
		m_bfmeVft = (void *)g_bfmeRva011051ECVt;
		m_bfmeWhat = (void *)4;
	}
	~InGameChatSlot();

	void *m_bfmeVft;
	unsigned char m_bfmeGap[ 8 ];
	void *m_bfmeWhat;
};

class __single_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct OnlineChatBinding
{
	OnlineChatBinding() {}
	OnlineChatBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	FunctorMethod m_method;
};

// Retail vtable of BannerAptCallbackWrapper, defined by
// WindowManagerRegisterAptCallbacks0046FD40.cpp; the global-callback functor
// wrapper below carries it, so the wrapper's own vtable is named here the way
// retail names it.  This TU does not declare that class, hence the identifier.
extern "C" const void *__identifier("??_7BannerAptCallbackWrapper@@6B@")[];

class OnlineChatGlobalFunctorWrapper
{
public:
	OnlineChatGlobalFunctorWrapper( unsigned int method )
	{
		m_refCount = 0;
		m_vft = (void *)__identifier("??_7BannerAptCallbackWrapper@@6B@");
		m_method = method;
	}

	void *m_vft;
	unsigned int m_refCount;
	unsigned int m_method;
};

class OnlineChatVirtualHead
{
public:
	OnlineChatVirtualHead() : m_refCount( 0 ) {}
	virtual void anchor();

	unsigned int m_refCount;
};

class OnlineChatVirtualFunctorWrapper : public OnlineChatVirtualHead
{
public:
	OnlineChatVirtualFunctorWrapper( const OnlineChatBinding &binding )
		: m_binding( binding ) {}

	OnlineChatBinding m_binding;
};

class OnlineChatInitVirtualHead
{
public:
	OnlineChatInitVirtualHead() : m_refCount( 0 ) {}
	virtual void anchor();

	unsigned int m_refCount;
};

class OnlineChatInitVirtualFunctorWrapper : public OnlineChatInitVirtualHead
{
public:
	OnlineChatInitVirtualFunctorWrapper( const OnlineChatBinding &binding )
		: m_binding( binding ) {}

	OnlineChatBinding m_binding;
};

class Rva0050F8B0FunctorHolder
{
public:
	__forceinline Rva0050F8B0FunctorHolder( unsigned int method )
	{
		m_ptr = new OnlineChatGlobalFunctorWrapper( method );
		if( m_ptr )
			++((unsigned int *)m_ptr)[1];
	}
	__forceinline Rva0050F8B0FunctorHolder( OnlineChatBinding binding )
	{
		m_ptr = new OnlineChatVirtualFunctorWrapper( binding );
		if( m_ptr )
			++((unsigned int *)m_ptr)[1];
	}
	Rva0050F8B0FunctorHolder( const Rva0050F8B0FunctorHolder &other )
		: m_ptr( other.m_ptr )
	{
		if( m_ptr )
			++((unsigned int *)m_ptr)[1];
	}

	void *m_ptr;
};

class Rva0050F840FunctorHolder
{
public:
	__forceinline Rva0050F840FunctorHolder( OnlineChatBinding binding )
	{
		m_ptr = new OnlineChatInitVirtualFunctorWrapper( binding );
		if( m_ptr )
			++((unsigned int *)m_ptr)[1];
	}
	Rva0050F840FunctorHolder( const Rva0050F840FunctorHolder &other )
		: m_ptr( other.m_ptr )
	{
		if( m_ptr )
			++((unsigned int *)m_ptr)[1];
	}

	void *m_ptr;
};

extern void j_000338ed();
extern void j_0003df14();
extern void j_0002567b();
// The AptOnline selector callbacks this constructor registers are retail ILT
// thunks: retail stored the thunk address itself in each binding, so the address
// the binding carries is the thunk.  Each union below reinterprets that thunk
// address as the __single_inheritance FunctorMethod the binding field holds; the
// member function each callback reached is never named or defined in this TU.
extern void j_00013d31();
extern void j_0003ff76();
extern void j_0001b3dd();
extern void j_00018886();
extern void j_000286be();
extern void j_0003a44a();
extern void j_0004a5ca();
extern void j_00029d61();
extern void j_00029249();
extern void j_00047258();

void _bfme_setAptScreenRef( const AsciiString &name,
	Rva0050F840FunctorHolder callback );

class BfmeAptScreenOnlineChat : public _bfme_AptGameWindow
{
public:
	BfmeAptScreenOnlineChat( int context );
	virtual ~BfmeAptScreenOnlineChat();

private:
	char m_flag3C;
	unsigned char m_pad3D[ 3 ];
	int m_z40;
	int m_z44;
	int m_z48;
	int m_z4C;
	int m_z50;
	int m_z54;
	InGameChatSlot m_slot0;
	InGameChatSlot m_slot1;
	InGameChatSlot m_slot2;
	InGameChatSlot m_slot3;
	char m_flag98;
	unsigned char m_pad99[ 3 ];
	int m_z9C;
	int m_zA0;
	int m_zA4;
	int m_zA8;
	int m_zAC;
	int m_zB0;
	int m_zB4;
	AsciiString m_unusedName;
};

extern BfmeAptScreenOnlineChat *TheBfmeOnlineChat;

BfmeAptScreenOnlineChat::BfmeAptScreenOnlineChat( int context )
	: _bfme_AptGameWindow( context ), m_flag3C( 0 ), m_z40( 0 ), m_z44( 0 ),
	m_z48( 0 ), m_z4C( 0 ), m_z50( 0 ), m_z54( 0 ), m_slot0(), m_slot1(),
	m_slot2(), m_slot3(), m_flag98( 0 ), m_z9C( 0 ), m_zA0( 0 ), m_zA4( 0 ),
	m_zA8( 4 ), m_zAC( 0 ), m_zB0( 0 ), m_zB4( 0 ),
	m_unusedName( "APT:NULL" )
{
	if( TheBfmeOnlineChat == 0 )
	{
		TheBfmeOnlineChat = this;

		{
			AsciiString name( "AptOnline::OnlineChat::QuickMatch" );
			_bfme_showAptScreen( name, Rva0050F8B0FunctorHolder( (unsigned int)j_0002567b ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_00013d31 };
			AsciiString name( "AptOnline::OnlineChat::OnBttnCancel" );
			_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( OnlineChatBinding(
					u.call, (FunctorTarget *)this ) ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_0003ff76 };
			FunctorMethod callback = u.call;
			AsciiString name( "AptOnline::OnlineChat::OnBttnAccept" );
			_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( OnlineChatBinding(
					callback, (FunctorTarget *)this ) ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_0001b3dd };
			FunctorMethod callback = u.call;
			AsciiString name( "AptOnline::OnlineChat::OnBttnEnterText" );
			_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( OnlineChatBinding(
					callback, (FunctorTarget *)this ) ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_00018886 };
			FunctorMethod callback = u.call;
			AsciiString name( "AptOnline::OnlineChat::OnBttnAddFriend" );
			_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( OnlineChatBinding(
					callback, (FunctorTarget *)this ) ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_000286be };
			FunctorMethod callback = u.call;
			AsciiString name( "AptOnline::OnlineChat::OnBttnAddIgnore" );
			_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( OnlineChatBinding(
					callback, (FunctorTarget *)this ) ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_0003a44a };
			FunctorMethod callback = u.call;
			AsciiString name( "AptOnline::OnlineChat::OnBttnFriendList" );
			_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( OnlineChatBinding(
					callback, (FunctorTarget *)this ) ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_0004a5ca };
			FunctorMethod callback = u.call;
			AsciiString name( "AptOnline::OnlineChat::OnBttnIgnoreList" );
			_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( OnlineChatBinding(
					callback, (FunctorTarget *)this ) ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_00029d61 };
			FunctorMethod callback = u.call;
			AsciiString name( "AptOnline::OnlineChat::OnBttnPlayerList" );
			_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( OnlineChatBinding(
					callback, (FunctorTarget *)this ) ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_00029249 };
			FunctorMethod callback = u.call;
			AsciiString name( "AptOnline::Chat::OnBttnRemoveIgnore" );
			_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( OnlineChatBinding(
					callback, (FunctorTarget *)this ) ) );
		}
		{
			union { void (*fn)(); FunctorMethod call; } u = { j_00047258 };
			FunctorMethod callback = u.call;
			AsciiString name( "AptOnlineChat::InitGadgets" );
			_bfme_setAptScreenRef( name,
				Rva0050F840FunctorHolder( OnlineChatBinding(
					callback, (FunctorTarget *)this ) ) );
		}
	}
}
