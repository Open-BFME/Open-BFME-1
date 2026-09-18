// ??0BfmeAptScreenOnlineCustomMatch@@QAE@H@Z
// partial score=0.32 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ??0BfmeAptScreenOnlineCustomMatch@@QAE@H@Z
// BfmeAptScreenOnlineCustomMatch constructor, retail 0x00545310, 1935 bytes.
// The constructor uses the recovered online custom-match callback bindings.

#include "../../reference/shims/stringinline/StringInline.h"

class BfmeAptWindowContext
{
public:
	BfmeAptWindowContext( int context ) : m_context( context ), m_z38( 0 ) {}

private:
	int m_context;
	int m_z38;
};

class BfmeAptGameWindow
{
public:
	BfmeAptGameWindow( int context )
		: m_f04( 0 ), m_f08( 0 ), m_f0c( 0 ), m_f10( 0 ), m_f14( 0 ),
		m_f18( 0 ), m_f1c( 0 ), m_f20( 0 ), m_f24( 0 ), m_f28( 0 ),
		m_f2c( 0 ), m_f30( 0 ), m_context( context ) {}
	virtual ~BfmeAptGameWindow();

private:
	int m_f04;
	int m_f08;
	int m_f0c;
	int m_f10;
	int m_f14;
	int m_f18;
	int m_f1c;
	int m_f20;
	int m_f24;
	int m_f28;
	int m_f2c;
	int m_f30;
	BfmeAptWindowContext m_context;
};

class BfmeAptScreenSecondary
{
public:
	BfmeAptScreenSecondary() {}
	virtual ~BfmeAptScreenSecondary() {}
};

class Gen00529110Owner;

class SkirmishScreenState
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	SkirmishScreenState( Gen00529110Owner *owner, int value );
	~SkirmishScreenState();

private:
	unsigned char m_data[ 0x130 ];
};

class BfmeCustomMatchMember40
{
public:
	BfmeCustomMatchMember40( Gen00529110Owner *owner, int value )
		: m_state( owner, value ) {}
	~BfmeCustomMatchMember40();

private:
	SkirmishScreenState m_state;
};

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual void unused04();
	virtual void unused08();
	virtual bool write();
	void setInt( AsciiString key, int value );
	int getInt( AsciiString key, int defaultValue ) const;

private:
	unsigned char m_data[ 0x10 ];
};

class CustomMatchPreferences : public UserPreferences
{
public:
	CustomMatchPreferences();
	virtual ~CustomMatchPreferences();
};

class GameSpyInfo
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
};

extern GameSpyInfo *TheGameSpyInfo;

class __multiple_inheritance FunctorTarget;
typedef void ( FunctorTarget::*FunctorMethod )( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	unsigned int m_unmodelled;
	FunctorMethod m_method;
};

class Rva00539A60FunctorHolder
{
public:
	Rva00539A60FunctorHolder( FunctorBinding binding );
	Rva00539A60FunctorHolder( const Rva00539A60FunctorHolder &other ) throw()
		: m_ptr( other.m_ptr )
	{
		if( m_ptr ) ++((unsigned int *)m_ptr)[1];
	}
	~Rva00539A60FunctorHolder();

	void *m_ptr;
};

class Rva00539AD0FunctorHolder
{
public:
	Rva00539AD0FunctorHolder( FunctorBinding binding );
	Rva00539AD0FunctorHolder( const Rva00539AD0FunctorHolder &other ) throw()
		: m_ptr( other.m_ptr )
	{
		if( m_ptr ) ++((unsigned int *)m_ptr)[1];
	}
	~Rva00539AD0FunctorHolder();

	void *m_ptr;
};

struct GameSpyStagingRoomFields
{
	unsigned char m_unmodelled[ 0x43C ];
	bool m_flag43C;
};
extern GameSpyStagingRoomFields *TheGameSpyGame;

class MpGameSetup
{
public:
	void GadgetInit();
};

class BfmeAptScreenOnlineCustomMatch;
extern BfmeAptScreenOnlineCustomMatch *TheBfmeOnlineCustomMatch;

extern void j_000338ed();
extern void j_0003df14();
extern void j_00025671();
extern void j_0003923e();
extern void j_0000feb6();
extern void j_0002efbe();
extern void j_0002edb6();
extern void j_0000e011();
extern void j_000469ca();
extern void j_00040d9a();
extern void j_00049cd3();
extern void j_000431f3();
extern void j_00034e23();
extern void j_000095e8();
extern void j_00044f9e();
extern void j_0001aaeb();
extern void j_0000d3d2();
extern void j_0001f9c9();

class __single_inheritance CustomMatchCallbackRegistry
{
public:
	typedef void ( CustomMatchCallbackRegistry::*Registrar )(
		const AsciiString &, Rva00539A60FunctorHolder );

	static __forceinline Registrar registrar()
	{
		union Bits { Registrar member; void ( *code )(); } bits;
		bits.code = j_000338ed;
		return bits.member;
	}
};

typedef void ( *CustomMatchInitRegistrar )(
	const AsciiString &, Rva00539AD0FunctorHolder );

class __multiple_inheritance BfmeAptScreenOnlineCustomMatch
	: public BfmeAptGameWindow, public BfmeAptScreenSecondary
{
public:
	BfmeAptScreenOnlineCustomMatch( int a );
	virtual ~BfmeAptScreenOnlineCustomMatch();
	__forceinline Gen00529110Owner *ownerForState()
	{
		return ( Gen00529110Owner * )( ( char * )this + 0x3C );
	}

	void cancelPopUpJoin();
	void createGame();
	void joinGame();
	void acceptJoinGame();
	void chatEnter();
	void playGame();
	void cancel();
	void refresh();
	void onOpenCreateDialog();
	void cancelPopUpCreate();
	void cancelPopUpHost();
	void sortByName();
	void sortByGameType();
	void sortByNumPlayers();
	void sortByPing();
	void initGadgets();

	private:
	BfmeCustomMatchMember40 m_mid;
	CustomMatchPreferences m_prefs;
	int m_unmodelled188;
	int m_unmodelled18c;
	int m_unmodelled190;
	int m_unmodelled194;
	int m_unmodelled198;
	unsigned char m_unmodelled19c[ 4 ];
	int m_unmodelled1a0;
	int m_unmodelled1a4;
	int m_unmodelled1a8;
	int m_unmodelled1ac;
	int m_unmodelled1b0;
	bool m_unmodelled1b4;
	unsigned char m_unmodelled1b5[ 3 ];
	int m_unmodelled1b8;
	int m_unmodelled1bc;
	int m_unmodelled1c0;
	int m_unmodelled1c4;
	bool m_unmodelled1c8;
	unsigned char m_unmodelled1c9[ 3 ];
	int m_unmodelled1cc;
	int m_unmodelled1d0;
	bool m_unmodelled1d4;
	bool m_unmodelled1d5;
	bool m_unmodelled1d6;
	unsigned char m_unmodelled1d7;
	int m_unmodelled1d8;
	int m_unmodelled1dc;
	int m_unmodelled1e0;
	AsciiString m_unusedName;
	int m_primarySort;
	int m_secondarySort;
};

union CustomMatchMethodBits
{
	FunctorMethod member;
	unsigned int words[ 2 ];
};

BfmeAptScreenOnlineCustomMatch::BfmeAptScreenOnlineCustomMatch( int a )
	: BfmeAptGameWindow( a )
	, m_mid( ownerForState(), 0x10 )
	, m_prefs()
	, m_unmodelled188( 0 )
	, m_unmodelled18c( 0 )
	, m_unmodelled190( 0 )
	, m_unmodelled194( 0 )
	, m_unmodelled198( 0 )
	, m_unmodelled1a0( 0 )
	, m_unmodelled1a4( 0 )
	, m_unmodelled1a8( 0 )
	, m_unmodelled1ac( 0 )
	, m_unmodelled1b0( 0 )
	, m_unmodelled1b4( false )
	, m_unmodelled1b8( 0 )
	, m_unmodelled1bc( -1 )
	, m_unmodelled1c0( 0 )
	, m_unmodelled1c4( 0 )
	, m_unmodelled1c8( false )
	, m_unmodelled1cc( 0 )
	, m_unmodelled1d0( 0 )
	, m_unmodelled1d4( false )
	, m_unmodelled1d5( true )
	, m_unmodelled1d6( true )
	, m_unmodelled1d8( 0 )
	, m_unmodelled1dc( 0 )
	, m_unmodelled1e0( 0 )
	, m_unusedName( "APT:NULL" )
{
	m_primarySort = 8;
	m_secondarySort = 4;

	if( TheBfmeOnlineCustomMatch == 0 )
	{
		TheBfmeOnlineCustomMatch = this;
		CustomMatchCallbackRegistry *registry =
			( CustomMatchCallbackRegistry * )this;
		CustomMatchMethodBits callback;

		callback.words[0] = (unsigned int)j_00025671;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::CancelPopUpJoin" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_0003923e;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::CreateGame" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_0000feb6;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::JoinGame" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_0002efbe;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::AcceptJoinGame" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_0002edb6;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::ChatEnter" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_0000e011;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::PlayGame" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_000469ca;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::Cancel" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_00040d9a;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::Refresh" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_00049cd3;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::OnOpenCreateDialog" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_000431f3;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::CancelPopUpCreate" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_00034e23;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::CancelPopUpHost" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_000095e8;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::SortName" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_00044f9e;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::SortGameType" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_0001aaeb;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::SortNumPlayers" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_0000d3d2;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnline::CustomMatch::SortPing" );
			( registry->*CustomMatchCallbackRegistry::registrar() )( name,
				Rva00539A60FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}
		callback.words[0] = (unsigned int)j_0001f9c9;
		callback.words[ 1 ] = 0;
		{
			AsciiString name( "AptOnlineCustomMatch::InitGadgets" );
			( ( CustomMatchInitRegistrar )j_0003df14 )( name,
				Rva00539AD0FunctorHolder( FunctorBinding(
					callback.member, ( FunctorTarget * )this ) ) );
		}

		( ( MpGameSetup * )( ( char * )this + 0x40 ) )->GadgetInit();
	}

	m_primarySort = m_prefs.getInt( AsciiString( "PrimarySort" ), m_primarySort );
	m_secondarySort = m_prefs.getInt( AsciiString( "SecondarySort" ), m_secondarySort );

	if( TheGameSpyGame )
		TheGameSpyGame->m_flag43C = false;
}


