// ??0BfmeAptScreenSkirmish@@QAE@PAX@Z
// partial score=0.22 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME-only reconstruction of the Skirmish.apt screen constructor.

template <typename T> class StringBase
{
public:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

protected:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

#pragma pointers_to_members( full_generality, multiple_inheritance )
class FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_adjustment( 0 ), m_method( method ) {}

	FunctorTarget *m_target;
	int m_adjustment;
	FunctorMethod m_method;
};

class SkirmishShowHolder
{
public:
	SkirmishShowHolder( FunctorBinding binding );
private:
	void *m_ptr;
};

class SkirmishArgHolder
{
public:
	SkirmishArgHolder( FunctorBinding binding );
private:
	void *m_ptr;
};

class SkirmishRefHolder
{
public:
	SkirmishRefHolder( FunctorBinding binding );
private:
	void *m_ptr;
};

class SkirmishRegistry
{
public:
	void showAptScreen( const AsciiString &name, SkirmishShowHolder callback );
	void showAptScreenWithArg( const AsciiString &name, void *argument,
		SkirmishArgHolder callback );
};

void skirmishSetAptScreenRef( const AsciiString &name,
	SkirmishRefHolder callback );

class BfmeAptSkirmishBase
{
public:
	BfmeAptSkirmishBase( void *context );
private:
	char m_data[ 0x258 ];
};

extern const void *BfmeAptScreenSkirmishVftable[];
extern const void *BfmeAptScreenSkirmishSecondaryVftable[];
extern const void *BfmeAptScreenSkirmishTertiaryVftable[];
extern void *g_theBfmeAptScreenSkirmish;

class __declspec(novtable) BfmeAptScreenSkirmish
	: public BfmeAptSkirmishBase
{
public:
	BfmeAptScreenSkirmish( void *context );
	void onInitialized();
	void onClosed();
	void exit();
	void back();
	void startGame();
	void profile();
	void skirmishProfile();
	void personaCancel();
	void personaAccept();
	void personaRemove();
	void personaOk();
	void tooltipPlayerLevelIcon();
	void levelBar();
	void initGadgets();

private:
	char m_data[ 0x1E4 ];
};

static void registerShow( BfmeAptScreenSkirmish *screen,
	SkirmishRegistry *registry, const char *name, FunctorMethod method )
{
	AsciiString command( name );
	registry->showAptScreen( command,
		FunctorBinding( method, (FunctorTarget *)screen ) );
}

static void registerArg( BfmeAptScreenSkirmish *screen,
	SkirmishRegistry *registry, const char *name, void *argument,
	FunctorMethod method )
{
	AsciiString command( name );
	registry->showAptScreenWithArg( command, argument,
		FunctorBinding( method, (FunctorTarget *)screen ) );
}

BfmeAptScreenSkirmish::BfmeAptScreenSkirmish( void *context )
	: BfmeAptSkirmishBase( context )
{
	*(const void ***)this = BfmeAptScreenSkirmishVftable;
	*(const void ***)( (char *)this + 0x218 ) =
		BfmeAptScreenSkirmishSecondaryVftable;
	*(const void ***)( (char *)this + 0x258 ) =
		BfmeAptScreenSkirmishTertiaryVftable;

	*(int *)( (char *)this + 0x400 ) = 0;
	*(int *)( (char *)this + 0x404 ) = -1;
	*(unsigned char *)( (char *)this + 0x408 ) = 1;
	*(unsigned char *)( (char *)this + 0x409 ) = 0;
	for( int offset = 0x40C; offset <= 0x420; offset += 4 )
		*(int *)( (char *)this + offset ) = 0;
	*(int *)( (char *)this + 0x430 ) = 10;
	*(unsigned char *)( (char *)this + 0x434 ) = 1;
	*(int *)( (char *)this + 0x438 ) = 0;

	if( g_theBfmeAptScreenSkirmish )
		return;
	g_theBfmeAptScreenSkirmish = this;

	SkirmishRegistry *registry =
		(SkirmishRegistry *)( (char *)this + 0x218 );
	registerShow( this, registry, "AptSkirmish::OnInitialized",
		(FunctorMethod)&BfmeAptScreenSkirmish::onInitialized );
	registerShow( this, registry, "AptSkirmish::OnClosed",
		(FunctorMethod)&BfmeAptScreenSkirmish::onClosed );
	registerShow( this, registry, "AptSkirmish::Exit",
		(FunctorMethod)&BfmeAptScreenSkirmish::exit );
	registerShow( this, registry, "AptSkirmish::Back",
		(FunctorMethod)&BfmeAptScreenSkirmish::back );
	registerShow( this, registry, "AptSkirmish::StartGame",
		(FunctorMethod)&BfmeAptScreenSkirmish::startGame );
	registerShow( this, registry, "AptSkirmish::Profile",
		(FunctorMethod)&BfmeAptScreenSkirmish::profile );
	registerShow( this, registry, "AptSkirmish::SkirmishProfile",
		(FunctorMethod)&BfmeAptScreenSkirmish::skirmishProfile );
	registerShow( this, registry, "AptSkirmish::Skirmish::PersonaCancel",
		(FunctorMethod)&BfmeAptScreenSkirmish::personaCancel );
	registerShow( this, registry, "AptSkirmish::Skirmish::PersonaAccept",
		(FunctorMethod)&BfmeAptScreenSkirmish::personaAccept );
	registerShow( this, registry, "AptSkirmish::Skirmish::PersonaRemove",
		(FunctorMethod)&BfmeAptScreenSkirmish::personaRemove );
	registerShow( this, registry, "AptSkirmish::Skirmish::PersonaOk",
		(FunctorMethod)&BfmeAptScreenSkirmish::personaOk );

	registerArg( this, registry, "Skirmish/tooltipPlayerLevelIcon", 0,
		(FunctorMethod)&BfmeAptScreenSkirmish::tooltipPlayerLevelIcon );
	registerArg( this, registry, "LevelBarCurrent", 0,
		(FunctorMethod)&BfmeAptScreenSkirmish::levelBar );
	registerArg( this, registry, "LevelBarA", (void *)1,
		(FunctorMethod)&BfmeAptScreenSkirmish::levelBar );
	registerArg( this, registry, "LevelBarB", (void *)2,
		(FunctorMethod)&BfmeAptScreenSkirmish::levelBar );
	registerArg( this, registry, "LevelBarC", (void *)3,
		(FunctorMethod)&BfmeAptScreenSkirmish::levelBar );
	registerArg( this, registry, "LevelBarD", (void *)4,
		(FunctorMethod)&BfmeAptScreenSkirmish::levelBar );

	{
		AsciiString command( "AptSkirmish::InitGadgets" );
		skirmishSetAptScreenRef( command,
			FunctorBinding( (FunctorMethod)&BfmeAptScreenSkirmish::initGadgets,
				(FunctorTarget *)this ) );
	}
}
