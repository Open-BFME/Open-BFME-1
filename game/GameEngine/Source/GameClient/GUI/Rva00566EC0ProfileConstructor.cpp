// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// RVA 00566EC0 constructs the distinct 28-byte object embedded at +390 in
// the main Skirmish screen; the legacy full-screen class name was incorrect.
// identity_evidence/00566ec0-profile-family.md records the independent proof.
// The small object
// whose primary vftable is 0x0110A314.  Its four bindings use the proven
// single-inheritance wrapper family at 0x0110A318 and the same WindowManager
// registration surface as the landed neighbours.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

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
	char m_unknown04[0x14];

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
		: m_ptr( other.m_ptr )
	{
		if( m_ptr )
			++m_ptr->m_refCount;
	}

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

class Rva00566EC0Profile
{
public:
	Rva00566EC0Profile( void );
	virtual ~Rva00566EC0Profile();

private:
	SkirmishPreferences m_prefs;
};

extern Rva00566EC0Profile *Rva012F4B3CProfile;

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

// ??0Rva00566EC0Profile@@QAE@XZ
Rva00566EC0Profile::Rva00566EC0Profile( void )
	: m_prefs()
{
	if( Rva012F4B3CProfile != 0 )
		return;

	Rva012F4B3CProfile = this;

	{
		// "Skirmish/tooltipPlayerLevelIconGondor" (also used by the destructor).
		AsciiString name( "Skirmish/tooltipPlayerLevelIconGondor" );
		FunctorBindingSingle binding(
			rawFunctorMethod( 0x0044219F ),
			(FunctorTargetSingle *)this );
		g_theWindowManager->bfmeBindRva004650F0( name,
			Rva0050F8B0FunctorHolder( binding ) );
	}
	{
		// "Skirmish/tooltipPlayerLevelIconRohan".
		AsciiString name( "Skirmish/tooltipPlayerLevelIconRohan" );
		FunctorBindingSingle binding(
			rawFunctorMethod( 0x0044219F ),
			(FunctorTargetSingle *)this );
		g_theWindowManager->bfmeBindRva004650F0( name,
			Rva0050F8B0FunctorHolder( binding ) );
	}
	{
		// "Skirmish/tooltipPlayerLevelIconIsengard".
		AsciiString name( "Skirmish/tooltipPlayerLevelIconIsengard" );
		FunctorBindingSingle binding(
			rawFunctorMethod( 0x0044219F ),
			(FunctorTargetSingle *)this );
		g_theWindowManager->bfmeBindRva004650F0( name,
			Rva0050F8B0FunctorHolder( binding ) );
	}
	{
		// "Skirmish/tooltipPlayerLevelIconMordor".
		AsciiString name( "Skirmish/tooltipPlayerLevelIconMordor" );
		FunctorBindingSingle binding(
			rawFunctorMethod( 0x0044219F ),
			(FunctorTargetSingle *)this );
		g_theWindowManager->bfmeBindRva004650F0( name,
			Rva0050F8B0FunctorHolder( binding ) );
	}
}
