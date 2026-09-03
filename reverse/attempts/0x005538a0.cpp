// ??0BfmeAptScreenOnlineLogin@@QAE@PAX@Z
// partial score=0.42 date=2026-09-03
// ??0BfmeAptScreenOnlineLogin@@QAE@PAX@Z
// partial score=0.42 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
// stlport
//
// BfmeAptScreenOnlineLogin constructor, retail 0x005538A0, 1082 bytes.
// Named by AptOnline::Login::* string xrefs and vtable 0x01107F58 (the same
// table the matched destructor installs). Factory sibling s4mk0055BA20
// allocates the 0xB0-byte object.

#include "StringInline.h"

class BfmeOnlineLoginMember3C
{
public:
	BfmeOnlineLoginMember3C();

private:
	unsigned char m_data[ 0x38 ];
};

__declspec( noinline ) void constructOnlineLoginMember3C( BfmeOnlineLoginMember3C *member )
{
	member->BfmeOnlineLoginMember3C::BfmeOnlineLoginMember3C();
}

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
	OnlineLoginFunctorWrapper( void *target, void *method )
		: m_target( target ), m_method( method ) {}

	void *m_target;
	void *m_method;
};

class OnlineLoginInitGadgetsFunctorWrapper : public FunctorWrapperHead
{
public:
	OnlineLoginInitGadgetsFunctorWrapper( void *target, void *method )
		: m_target( target ), m_method( method ) {}

	void *m_target;
	void *m_method;
};

class Rva0050F8B0FunctorHolder
{
public:
	__forceinline Rva0050F8B0FunctorHolder( void *target, void *method )
	{
		m_ptr = new OnlineLoginFunctorWrapper( target, method );
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
	__forceinline Rva0050F840FunctorHolder( void *target, void *method )
	{
		m_ptr = new OnlineLoginInitGadgetsFunctorWrapper( target, method );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}
	Rva0050F840FunctorHolder( const Rva0050F840FunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	OnlineLoginInitGadgetsFunctorWrapper *m_ptr;
};

class _bfme_AptGameWindow
{
public:
	void _bfme_showAptScreen( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );
};

void _bfme_setAptScreenRef( const AsciiString &name,
	Rva0050F840FunctorHolder callback );

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
extern const void *BfmeAptScreenOnlineLoginVftable[];

class __declspec(novtable) BfmeAptScreenOnlineLogin
{
public:
	BfmeAptScreenOnlineLogin( void *context );

	void _bfme_login();
	void _bfme_deleteNickname();
	void _bfme_register();
	void _bfme_serviceTerms();
	void _bfme_acceptLocale();
	void _bfme_cancelLogin();
	void _bfme_officialSite();
	void _bfme_initGadgets();
	bool _bfme_loginGadgetsState();

private:
	const void *m_vftable;
	int m_z04, m_z08, m_z0C, m_z10, m_z14, m_z18;
	int m_z1C, m_z20, m_z24, m_z28, m_z2C, m_z30;
	void *m_context;
	int m_z38;
	unsigned char m_state[ 0x38 ];
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
	void *m_name;
	char m_zAC;
};

union OnlineLoginMethodBits
{
	void (BfmeAptScreenOnlineLogin::*m_method)();
	void *m_ptr;
};

BfmeAptScreenOnlineLogin::BfmeAptScreenOnlineLogin( void *context )
{
	void *frame0;
	void *frame1;
	void *ctx = context;
	(void)frame0;
	(void)frame1;
	m_z04 = 0;
	m_z08 = 0;
	m_z0C = 0;
	m_z10 = 0;
	m_z14 = 0;
	m_z18 = 0;
	m_z1C = 0;
	m_z20 = 0;
	m_z24 = 0;
	m_z28 = 0;
	m_z2C = 0;
	m_z30 = 0;
	m_context = ctx;
	m_z38 = 0;
	*(const void ***)this = BfmeAptScreenOnlineLoginVftable;
	constructOnlineLoginMember3C( (BfmeOnlineLoginMember3C *)m_state );

	int one = 1;
	m_control74 = 0;
	m_control78 = 0;
	m_control7C = 0;
	m_control80 = 0;
	m_control84 = 0;
	m_flag8C = one;
	m_z90 = 0;
	m_loggedInOK = 0;
	m_needsRefresh = (char)one;
	m_z98 = 0;
	m_z9C = 0;
	m_flag9D = (char)one;
	m_gadgetState9E = 0;
	m_zA1 = 0;
	m_zA4 = 0;
	m_name = 0;
	m_zAC = 0;

	if( TheBfmeOnlineLogin == 0 )
	{
		TheBfmeOnlineLogin = this;
		_bfme_AptGameWindow *registry = (_bfme_AptGameWindow *)this;

		{
			OnlineLoginMethodBits bits;
			bits.m_method = &BfmeAptScreenOnlineLogin::_bfme_login;
			AsciiString name( "AptOnline::Login::Login" );
			registry->_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( this, bits.m_ptr ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_method = &BfmeAptScreenOnlineLogin::_bfme_deleteNickname;
			AsciiString name( "AptOnline::Login::DeleteNickname" );
			registry->_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( this, bits.m_ptr ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_method = &BfmeAptScreenOnlineLogin::_bfme_register;
			AsciiString name( "AptOnline::Login::Register" );
			registry->_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( this, bits.m_ptr ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_method = &BfmeAptScreenOnlineLogin::_bfme_serviceTerms;
			AsciiString name( "AptOnline::Login::ServiceTerms" );
			registry->_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( this, bits.m_ptr ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_method = &BfmeAptScreenOnlineLogin::_bfme_acceptLocale;
			AsciiString name( "AptOnline::Login::AcceptLocale" );
			registry->_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( this, bits.m_ptr ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_method = &BfmeAptScreenOnlineLogin::_bfme_cancelLogin;
			AsciiString name( "AptOnline::Login::CancelLogin" );
			registry->_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( this, bits.m_ptr ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_method = &BfmeAptScreenOnlineLogin::_bfme_officialSite;
			AsciiString name( "AptOnline::Login::OfficialSite" );
			registry->_bfme_showAptScreen( name,
				Rva0050F8B0FunctorHolder( this, bits.m_ptr ) );
		}
		{
			OnlineLoginMethodBits bits;
			bits.m_method = &BfmeAptScreenOnlineLogin::_bfme_initGadgets;
			AsciiString name( "AptOnlineLogin::InitGadgets" );
			_bfme_setAptScreenRef( name,
				Rva0050F840FunctorHolder( this, bits.m_ptr ) );
		}

		m_gadgetState9E = _bfme_loginGadgetsState();
		m_zA1 = _bfme_loginGadgetsState();
		TheBfmeImeManager->bfmeNotify();
	}
}
