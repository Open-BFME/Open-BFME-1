// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The 0x00566EC0 constructor belongs to the small Skirmish options object
// whose primary vftable is 0x0110A314.  Its four bindings use the proven
// single-inheritance wrapper family at 0x0110A318 and the same WindowManager
// registration surface as the landed neighbours.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
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

extern void j_00047767( void );

class __declspec(novtable) SkirmishPreferences
{
public:
	SkirmishPreferences( void )
	{
		union
		{
			void (*raw)( void );
			void (SkirmishPreferences::*member)( void );
		} call;
		call.raw = j_00047767;
		(this->*call.member)();
	}

	virtual ~SkirmishPreferences();

};

class __single_inheritance FunctorTargetSingle
{
};

typedef void (FunctorTargetSingle::*FunctorMethodSingle)( void );

struct FunctorBindingSingle
{
	FunctorBindingSingle( FunctorMethodSingle method,
		FunctorTargetSingle *target )
		: m_target( target ), m_method( method ) {}

	FunctorTargetSingle *m_target;
	FunctorMethodSingle m_method;
};

class FunctorSingleWrapperHead
{
public:
	FunctorSingleWrapperHead() : m_refCount( 0 ) {}
	virtual void functorSingleWrapperAnchor();

	unsigned int m_refCount;
};

class Rva00566A60FunctorSingleWrapper : public FunctorSingleWrapperHead
{
public:
	Rva00566A60FunctorSingleWrapper(
		const FunctorBindingSingle &binding )
		: m_binding( binding ) {}

	FunctorBindingSingle m_binding;
};

class Rva0050F8B0FunctorHolder
{
public:
	__forceinline Rva0050F8B0FunctorHolder(
		FunctorBindingSingle binding )
	{
		m_ptr = new Rva00566A60FunctorSingleWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	__forceinline Rva0050F8B0FunctorHolder(
		const Rva0050F8B0FunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	~Rva0050F8B0FunctorHolder();

	FunctorSingleWrapperHead *m_ptr;
};

class WindowManager
{
public:
	void bfmeBindRva004650F0( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );
};

extern WindowManager *g_theWindowManager;
extern const void *bfmeSkirmishOptionsVft[];

class BfmeAptScreenSkirmish
{
public:
	BfmeAptScreenSkirmish( void );
	virtual ~BfmeAptScreenSkirmish();

private:
	SkirmishPreferences m_prefs;
};

static FunctorMethodSingle rawFunctorMethod( unsigned int address )
{
	union
	{
		unsigned int raw;
		FunctorMethodSingle member;
	} method;
	method.raw = address;
	return method.member;
}

// ??0BfmeAptScreenSkirmish@@QAE@XZ
BfmeAptScreenSkirmish::BfmeAptScreenSkirmish( void )
	: m_prefs()
{
	if( *(BfmeAptScreenSkirmish **)0x012F4B3C != 0 )
		return;

	*(BfmeAptScreenSkirmish **)0x012F4B3C = this;

	{
		AsciiString name( (const char *)0x0110A2E4 );
		FunctorBindingSingle binding(
			rawFunctorMethod( 0x0044219F ),
			(FunctorTargetSingle *)this );
		g_theWindowManager->bfmeBindRva004650F0( name,
			Rva0050F8B0FunctorHolder( binding ) );
	}
	{
		AsciiString name( (const char *)0x0110A2B8 );
		FunctorBindingSingle binding(
			rawFunctorMethod( 0x0044219F ),
			(FunctorTargetSingle *)this );
		g_theWindowManager->bfmeBindRva004650F0( name,
			Rva0050F8B0FunctorHolder( binding ) );
	}
	{
		AsciiString name( (const char *)0x0110A288 );
		FunctorBindingSingle binding(
			rawFunctorMethod( 0x0044219F ),
			(FunctorTargetSingle *)this );
		g_theWindowManager->bfmeBindRva004650F0( name,
			Rva0050F8B0FunctorHolder( binding ) );
	}
	{
		AsciiString name( (const char *)0x0110A258 );
		FunctorBindingSingle binding(
			rawFunctorMethod( 0x0044219F ),
			(FunctorTargetSingle *)this );
		g_theWindowManager->bfmeBindRva004650F0( name,
			Rva0050F8B0FunctorHolder( binding ) );
	}
}
