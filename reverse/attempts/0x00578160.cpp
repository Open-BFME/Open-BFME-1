// ??0BfmeAptScreenScoreScreen@@QAE@PAX@Z
// partial score=0.84 date=2026-09-20
// BfmeAptScreenScoreScreen constructor, retail 0x00578160.
// The layout and callback registry follow the retail constructor and its
// matched ScoreScreen methods and destructor.

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data( 0 ) {}
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

extern "C" void *__cdecl memset( void *buffer, int value,
	unsigned int bytes );
#pragma intrinsic(memset)

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	AsciiString( const char *text );
	~AsciiString() {}
	void format( AsciiString format, ... );

private:
	void *m_data;
};

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_refCount( 0 ), m_method( method ) {}

	FunctorTarget *m_target;
	unsigned int m_refCount;
	FunctorMethod m_method;
};

class Rva00572CA0FunctorHolder
{
public:
	Rva00572CA0FunctorHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( void *context );
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[ 0x214 ];
};

#pragma comment(linker, "/alternatename:??0_bfme_AptGameWindow@@QAE@PAX@Z=?j_00039b6c@@YAXXZ")
#pragma comment(linker, "/alternatename:??0AsciiString@@QAE@PBD@Z=??0BFMERetailAsciiString@@QAE@PBD@Z")

class ScoreScreenPrimaryVtableBase
{
public:
	__forceinline ScoreScreenPrimaryVtableBase( void *owner )
	{
		*(const void * volatile *)owner = (const void *)0x0110AAB8;
	}
};

class ScoreScreenSecondaryVtableBase
{
public:
	__forceinline ScoreScreenSecondaryVtableBase( void *owner )
	{
		*(const void **)( (char *)owner + 0x218 ) =
			(const void *)0x0110AAB4;
	}
};

struct ScoreScreenFiveFields
{
	__forceinline void clear()
	{
		m_slot278 = 0;
		m_slot27c = 0;
		m_slot280 = 0;
		m_slot284 = 0;
		m_slot288 = 0;
	}

	int m_slot278;
	int m_slot27c;
	int m_slot280;
	int m_slot284;
	int m_slot288;
};

struct ScoreScreenZeroBlock
{
	int m_slots294[ 21 ];
};

struct Gen_uwm_00045e8f
{
	Gen_uwm_00045e8f()
		: m_begin( 0 ), m_finish( 0 )
	{
		m_capacity = 0;
	}
	~Gen_uwm_00045e8f();

	void *m_begin;
	void *m_finish;
	void *m_capacity;
};

extern void Gen0082E5F0( void *memory, unsigned int bytes );

struct RawVecBuffer
{
	RawVecBuffer()
		: m_start( 0 ), m_zero04( 0 ), m_zero08( 0 ), m_zero0c( 0 ),
		  m_end( 0 ) {}
	~RawVecBuffer()
	{
		if( m_start != 0 )
		{
			int shifted = (int)( m_end - m_start ) >> 2;
			unsigned int n = (unsigned int)( shifted << 2 );
			if( n > 128 )
				::operator delete( m_start );
			else
				Gen0082E5F0( m_start, n );
		}
	}

	char *m_start;
	unsigned int m_zero04;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	char *m_end;
};

struct ScoreProviderWrapper
{
	__forceinline ScoreProviderWrapper( const FunctorBinding &binding )
		: m_vftable( (const void *)0x0110A964 ), m_refCount( 0 ),
		  m_binding( binding ) {}

	const void *m_vftable;
	unsigned int m_refCount;
	FunctorBinding m_binding;
};

class ScoreProviderHolder
{
public:
	__forceinline ScoreProviderHolder( FunctorBinding binding )
	{
		m_ptr = new ScoreProviderWrapper( binding );
		if( m_ptr != 0 )
			++m_ptr->m_refCount;
	}
private:
	ScoreProviderWrapper *m_ptr;
};

struct ScoreInitWrapper
{
	__forceinline ScoreInitWrapper( const FunctorBinding &binding )
		: m_vftable( (const void *)0x0110A970 ), m_refCount( 0 ),
		  m_binding( binding ) {}

	const void *m_vftable;
	unsigned int m_refCount;
	FunctorBinding m_binding;
};

class ScoreInitHolder
{
public:
	__forceinline ScoreInitHolder( FunctorBinding binding )
	{
		m_ptr = new ScoreInitWrapper( binding );
		if( m_ptr != 0 )
			++m_ptr->m_refCount;
	}

private:
	ScoreInitWrapper *m_ptr;
};

class ScoreRegistryWindow
{
public:
	void registerScoreScreen( const AsciiString &name,
		Rva00572CA0FunctorHolder callback );
	void registerScoreScreenWithArg( const AsciiString &name, void *argument,
		ScoreProviderHolder callback );
};

#pragma comment(linker, "/alternatename:?registerScoreScreen@ScoreRegistryWindow@@QAEXABVAsciiString@@VRva00572CA0FunctorHolder@@@Z=?j_000338ed@@YAXXZ")
#pragma comment(linker, "/alternatename:?registerScoreScreenWithArg@ScoreRegistryWindow@@QAEXABVAsciiString@@PAXVScoreProviderHolder@@@Z=?j_0000acfe@@YAXXZ")

void registerScoreScreenRef( const AsciiString &name, ScoreInitHolder callback );

#pragma comment(linker, "/alternatename:?registerScoreScreenRef@@YAXABVAsciiString@@VScoreInitHolder@@@Z=?j_0003df14@@YAXXZ")

class WindowManager
{
public:
	__declspec( noinline ) void bfme_showBackground( int kind );
};

extern WindowManager *g_theWindowManager;

extern void j_00026152();
extern void j_0000a76d();
extern void j_000328b2();
extern void j_0003936a();
extern void j_00035639();
extern void j_00003c01();
extern void j_000077c0();
extern void j_0003a1e3();
extern void j_00005fba();
extern void j_0002f806();
extern void j_0001ac49();
extern void j_00023c77();
extern void j_000289b6();
extern void j_0003ec6b();
extern void j_00007c25();
extern void j_000016e0();

union ScoreScreenMethodBits
{
	FunctorMethod method;
	struct
	{
		void (*code)( void );
		int delta;
	} raw;
};

__forceinline FunctorMethod scoreScreenMethodFromThunk( void (*code)( void ) )
{
	ScoreScreenMethodBits bits;
	bits.raw.delta = 0;
	bits.raw.code = code;
	return bits.method;
}

class __declspec( novtable ) BfmeAptScreenScoreScreen
	: public _bfme_AptGameWindow, public ScoreScreenPrimaryVtableBase,
	  public ScoreScreenSecondaryVtableBase
{
public:
	BfmeAptScreenScoreScreen( void *context );
	virtual ~BfmeAptScreenScoreScreen();

private:
	char m_pad21c[ 0x258 - 0x21c ];
	int m_slot258;
	int m_gameType;
	unsigned char m_flag260;
	unsigned char m_flag261;
	char m_pad262[ 2 ];
	Gen_uwm_00045e8f m_rows;
	char m_pad270[ 8 ];
	ScoreScreenFiveFields m_opaque278;
	int m_slot28c;
	char m_pad290[ 4 ];
	ScoreScreenZeroBlock m_zero294;
	RawVecBuffer m_rawBuffer;
	int m_slot2fc;
	BFMERetailAsciiString m_s300;
	int m_slot304;
	int m_slot308;
	int m_slot30c;
	int m_slot310;
	int m_slot314;
	int m_slot318;
	int m_slot31c;
	BFMERetailAsciiString m_s320;
	int m_slot324;
	int m_slot328;
	int m_slot32c;
	BFMERetailAsciiString m_s330;
};

BfmeAptScreenScoreScreen::BfmeAptScreenScoreScreen( void *context )
	: _bfme_AptGameWindow( context ), ScoreScreenPrimaryVtableBase( this ),
	  ScoreScreenSecondaryVtableBase( this ),
	  m_slot258( 0 ), m_gameType( 5 ), m_flag260( 0 ), m_flag261( 0 ),
	  m_rows(), m_slot28c( 0 ), m_rawBuffer(), m_slot2fc( 0 ), m_s300(),
	  m_slot304( 0 ), m_slot310( 0 ), m_slot314( 0 ), m_slot318( 0 ),
	  m_s320(), m_slot324( 0 ), m_slot328( 0 ), m_slot32c( 0 ),
	  m_s330( "APT:NULL" )
{
	if( *(void **)0x012F4B50 == 0 )
	{
		*(void **)0x012F4B50 = this;
		m_opaque278.clear();
		memset( m_zero294.m_slots294, 0, sizeof( m_zero294.m_slots294 ) );
		m_slot308 = 0;
		m_slot30c = 0;

		ScoreRegistryWindow *registry =
			(ScoreRegistryWindow *)( (char *)this + 0x218 );

		{
			BFMERetailAsciiString name( "AptScoreScreen::OnInitialized" );
			registry->registerScoreScreen(
				reinterpret_cast<const AsciiString &>( name ),
				Rva00572CA0FunctorHolder( FunctorBinding(
					scoreScreenMethodFromThunk( j_00026152 ),
					(FunctorTarget *)this ) ) );
		}
		{
			BFMERetailAsciiString name( "AptScoreScreen::Exit" );
			registry->registerScoreScreen(
				reinterpret_cast<const AsciiString &>( name ),
				Rva00572CA0FunctorHolder( FunctorBinding(
					scoreScreenMethodFromThunk( j_0000a76d ),
					(FunctorTarget *)this ) ) );
		}
		{
			BFMERetailAsciiString name( "AptScoreScreen::Save" );
			registry->registerScoreScreen(
				reinterpret_cast<const AsciiString &>( name ),
				Rva00572CA0FunctorHolder( FunctorBinding(
					scoreScreenMethodFromThunk( j_000328b2 ),
					(FunctorTarget *)this ) ) );
		}
		{
			BFMERetailAsciiString name( "AptScoreScreen::Continue" );
			registry->registerScoreScreen(
				reinterpret_cast<const AsciiString &>( name ),
				Rva00572CA0FunctorHolder( FunctorBinding(
					scoreScreenMethodFromThunk( j_0003936a ),
					(FunctorTarget *)this ) ) );
		}
		{
			BFMERetailAsciiString name( "AptScoreScreen::RestartGame" );
			registry->registerScoreScreen(
				reinterpret_cast<const AsciiString &>( name ),
				Rva00572CA0FunctorHolder( FunctorBinding(
					scoreScreenMethodFromThunk( j_00035639 ),
					(FunctorTarget *)this ) ) );
		}
		{
			BFMERetailAsciiString name( "AptScoreScreen::RenameAccept" );
			registry->registerScoreScreen(
				reinterpret_cast<const AsciiString &>( name ),
				Rva00572CA0FunctorHolder( FunctorBinding(
					scoreScreenMethodFromThunk( j_00003c01 ),
					(FunctorTarget *)this ) ) );
		}
		{
			BFMERetailAsciiString name( "AptScoreScreen::RenameCancel" );
			registry->registerScoreScreen(
				reinterpret_cast<const AsciiString &>( name ),
				Rva00572CA0FunctorHolder( FunctorBinding(
					scoreScreenMethodFromThunk( j_000077c0 ),
					(FunctorTarget *)this ) ) );
		}

		FunctorMethod provider = scoreScreenMethodFromThunk( j_0003a1e3 );
		for( int index = 0; index < 11; ++index )
		{
			BFMERetailAsciiString name(
				((const char * const *)0x012B7F9C)[ index ] );
			ScoreProviderHolder callback( FunctorBinding( provider,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg(
				reinterpret_cast<const AsciiString &>( name ),
				(void *)index, callback );
		}

		AsciiString playerName;
		FunctorMethod playerColor = scoreScreenMethodFromThunk( j_00005fba );
		FunctorMethod playerFaction = scoreScreenMethodFromThunk( j_0002f806 );
		for( int index = 0; index < 8; ++index )
		{
			playerName.format( (AsciiString)"ScoreScreen:PlayerColor:%d", index );
			ScoreProviderHolder callback( FunctorBinding( playerColor,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg( playerName, (void *)index,
				callback );
			playerName.format( (AsciiString)"ScoreScreen:PlayerFaction:%d", index );
			ScoreProviderHolder factionCallback( FunctorBinding( playerFaction,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg( playerName, (void *)index,
				factionCallback );
			if( index != 0 )
			{
				playerName.format( (AsciiString)"Separator%d", index );
				ScoreProviderHolder separatorCallback( FunctorBinding(
					scoreScreenMethodFromThunk( j_0001ac49 ),
					(FunctorTarget *)this ) );
				registry->registerScoreScreenWithArg( playerName, (void *)index,
					separatorCallback );
			}
		}

		provider = scoreScreenMethodFromThunk( j_00023c77 );
		{
			BFMERetailAsciiString name( "ScoreBattleStat" );
			ScoreProviderHolder callback( FunctorBinding( provider,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg(
				reinterpret_cast<const AsciiString &>( name ), (void *)0,
				callback );
		}
		{
			BFMERetailAsciiString name( "ScoreBonusObjectives" );
			ScoreProviderHolder callback( FunctorBinding( provider,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg(
				reinterpret_cast<const AsciiString &>( name ), (void *)1,
				callback );
		}
		{
			BFMERetailAsciiString name( "ScoreHeroVeterancy" );
			ScoreProviderHolder callback( FunctorBinding( provider,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg(
				reinterpret_cast<const AsciiString &>( name ), (void *)2,
				callback );
		}
		{
			BFMERetailAsciiString name( "ScoreUnitVeterancy" );
			ScoreProviderHolder callback( FunctorBinding( provider,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg(
				reinterpret_cast<const AsciiString &>( name ), (void *)3,
				callback );
		}
		{
			BFMERetailAsciiString name( "ScoreTerritoryBonus" );
			ScoreProviderHolder callback( FunctorBinding( provider,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg(
				reinterpret_cast<const AsciiString &>( name ), (void *)4,
				callback );
		}

		provider = scoreScreenMethodFromThunk( j_000289b6 );
		for( int group = 0; group < 7; ++group )
		{
			for( int stat = 0; stat < 3; ++stat )
			{
				playerName.format( (AsciiString)"battleStat%c%d",
					'A' + group, stat + 1 );
				ScoreProviderHolder callback( FunctorBinding( provider,
					(FunctorTarget *)this ) );
				registry->registerScoreScreenWithArg( playerName,
				(void *)( group * 3 + stat ), callback );
			}
		}

		provider = scoreScreenMethodFromThunk( j_0003ec6b );
		for( int index = 0; index < 8; ++index )
		{
			playerName.format( (AsciiString)"objectiveChecked%d", index + 1 );
			ScoreProviderHolder callback( FunctorBinding( provider,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg( playerName, (void *)index,
				callback );
		}

		provider = scoreScreenMethodFromThunk( j_00007c25 );
		for( int index = 0; index < 12; ++index )
		{
			playerName.format( (AsciiString)"heroVetUpgrade%d", index + 1 );
			ScoreProviderHolder callback( FunctorBinding( provider,
				(FunctorTarget *)this ) );
			registry->registerScoreScreenWithArg( playerName, (void *)index,
				callback );
		}

		{
			BFMERetailAsciiString name( "AptScoreScreen::InitGadgets" );
			ScoreInitHolder callback( FunctorBinding(
				scoreScreenMethodFromThunk( j_000016e0 ),
				(FunctorTarget *)this ) );
			registerScoreScreenRef( reinterpret_cast<const AsciiString &>( name ),
				callback );
		}
		g_theWindowManager->bfme_showBackground( 1 );
	}
}
