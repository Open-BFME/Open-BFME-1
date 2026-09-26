// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// stlport
//
// BfmeAptScreenOnlineLogin constructor, retail 0x005538A0, 1082 bytes.
// The first-instance branch registers the eight AptOnline::Login callbacks
// plus AptOnlineLogin::InitGadgets, then latches the two gadget-state flags
// and notifies the IME manager.

#include "StringInline.h"

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

// GameSpyLoginPreferences-shaped member at +0x3C; its real body is 0x00082970,
// reached through ILT 0x00010BE0.
class BfmeOnlineLoginMember3C
{
public:
	BfmeOnlineLoginMember3C();
	~BfmeOnlineLoginMember3C();

private:
	unsigned char m_data[ 0x38 ];
};

// FunctorBinding/holder plumbing shared by the registration calls below.  All
// eight callbacks resolve to plain 4-byte addresses (retail stores only
// target+method, 8 bytes total, no adjustor word), so FunctorTarget stays
// single inheritance here -- same convention as BfmeOnlineProfileScreenConstructor.cpp.
class __single_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount( 0 ) {}
	virtual void functorWrapperAnchor();

	unsigned int m_refCount;
};

class OnlineLoginFunctorWrapper : public FunctorWrapperHead
{
public:
	OnlineLoginFunctorWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class OnlineLoginInitGadgetsFunctorWrapper : public FunctorWrapperHead
{
public:
	OnlineLoginInitGadgetsFunctorWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class Rva0050F8B0FunctorHolder
{
public:
	__forceinline Rva0050F8B0FunctorHolder( FunctorBinding binding )
	{
		m_ptr = new OnlineLoginFunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	Rva0050F8B0FunctorHolder( const Rva0050F8B0FunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	OnlineLoginFunctorWrapper *m_ptr;
};

class Rva0050F840FunctorHolder
{
public:
	__forceinline Rva0050F840FunctorHolder( FunctorBinding binding )
	{
		m_ptr = new OnlineLoginInitGadgetsFunctorWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	Rva0050F840FunctorHolder( const Rva0050F840FunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	OnlineLoginInitGadgetsFunctorWrapper *m_ptr;
};

class BfmeAptWindowContext
{
public:
	BfmeAptWindowContext( void *context );

	void *m_context;
	int m_z38;
};

BfmeAptWindowContext::BfmeAptWindowContext( void *context )
	: m_context( context ), m_z38( 0 )
{
}

class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( void *context );
	virtual ~_bfme_AptGameWindow();

	void _bfme_showAptScreen( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );

private:
	int m_z04, m_z08, m_z0C, m_z10, m_z14, m_z18;
	int m_z1C, m_z20, m_z24, m_z28, m_z2C, m_z30;
	BfmeAptWindowContext m_ctx;
};

_bfme_AptGameWindow::_bfme_AptGameWindow( void *context )
	: m_z04( 0 ), m_z08( 0 ), m_z0C( 0 ), m_z10( 0 ), m_z14( 0 ),
	m_z18( 0 ), m_z1C( 0 ), m_z20( 0 ), m_z24( 0 ), m_z28( 0 ),
	m_z2C( 0 ), m_z30( 0 ), m_ctx( context )
{
}

class GameWindow;

class BfmeImeManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void bfmeDetach();
	virtual void bfmeNotify();
};

extern BfmeImeManager *TheBfmeImeManager;
extern class BfmeAptScreenOnlineLogin *TheBfmeOnlineLogin;

void _bfme_setAptScreenRef( const AsciiString &name,
	Rva0050F840FunctorHolder callback );

class BfmeAptScreenOnlineLogin : public _bfme_AptGameWindow
{
public:
	BfmeAptScreenOnlineLogin( void *context );
	virtual ~BfmeAptScreenOnlineLogin();

	void _bfme_login( const char *name );
	void bfmeOpenTermsPage( const char *name );
	void _bfme_acceptLocale( const char *name );
	void bfmeOpenHomePage( const char *name );
	void _bfme_onInitGadget( const char *name, void *arg, GameWindow *window );
	bool _bfme_loginGadgetsState();

private:
	BfmeOnlineLoginMember3C m_state;
	void *m_control74;
	void *m_control78;
	void *m_control7C;
	void *m_control80;
	void *m_control84;
	int m_pad88;
	int m_flag8C;
	int m_z90;
	char m_loggedInOK;
	char m_needsRefresh;
	int m_z98;
	char m_z9C;
	char m_flag9D;
	char m_gadgetState9E;
	char m_pad9F;
	char m_padA0;
	char m_zA1;
	int m_zA4;
	AsciiString m_name;
	char m_zAC;
	char m_tailAD[ 3 ];
};

extern void __stdcall bfmeGoELB( int unused );
extern void __stdcall rva00548d20( int unused );
extern void j_0002e479();

union OnlineLoginMethodBits
{
	FunctorMethod m_method;
	unsigned int m_words[ 2 ];
};

BfmeAptScreenOnlineLogin::BfmeAptScreenOnlineLogin( void *context )
	: _bfme_AptGameWindow( context ), m_control74( 0 ), m_control78( 0 ),
	m_control7C( 0 ), m_control80( 0 ), m_control84( 0 ), m_flag8C( 1 ),
	m_z90( 0 ), m_loggedInOK( 0 ), m_needsRefresh( 1 ), m_z98( 0 ),
	m_z9C( 0 ), m_flag9D( 1 ), m_gadgetState9E( 0 ), m_zA1( 0 ), m_zA4( 0 ),
	m_name(), m_zAC( 0 )
{
	if( TheBfmeOnlineLogin == 0 )
	{
		TheBfmeOnlineLogin = this;

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOnlineLogin::_bfme_login;
			AsciiString name( "AptOnline::Login::Login" );
			_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_words[ 0 ] = (unsigned int)bfmeGoELB;
			AsciiString name( "AptOnline::Login::DeleteNickname" );
			_bfme_showAptScreen( name,
				FunctorBinding( bits.m_method, (FunctorTarget *)this ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_words[ 0 ] = (unsigned int)j_0002e479;
			AsciiString name( "AptOnline::Login::Register" );
			_bfme_showAptScreen( name,
				FunctorBinding( bits.m_method, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOnlineLogin::bfmeOpenTermsPage;
			AsciiString name( "AptOnline::Login::ServiceTerms" );
			_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOnlineLogin::_bfme_acceptLocale;
			AsciiString name( "AptOnline::Login::AcceptLocale" );
			_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_words[ 0 ] = (unsigned int)rva00548d20;
			AsciiString name( "AptOnline::Login::CancelLogin" );
			_bfme_showAptScreen( name,
				FunctorBinding( bits.m_method, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOnlineLogin::bfmeOpenHomePage;
			AsciiString name( "AptOnline::Login::OfficialSite" );
			_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOnlineLogin::_bfme_onInitGadget;
			AsciiString name( "AptOnlineLogin::InitGadgets" );
			_bfme_setAptScreenRef( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		m_gadgetState9E = _bfme_loginGadgetsState();
		m_zA1 = _bfme_loginGadgetsState();
		TheBfmeImeManager->bfmeNotify();
	}
}
