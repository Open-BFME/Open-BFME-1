// ?finish@Rva003677B0Entry@@QAEXPAX_N@Z
// partial score=0.40 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Rva003677B0Entry::finish, retail RVA 0x00367010.
// ABI proven by the landed indexed caller at 0x003677B0.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;

void operator delete( void *, unsigned int );

extern void j_0000ebce();
extern void j_0000f2e5();
extern void j_0001a136();
extern void j_0001af23();
extern void j_0001e56f();
extern void j_00028560();
extern void j_0003b91c();
extern void j_00044788();

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class ThingTemplate
{
public:
	Int getCommandPointCost() const
	{
		return *reinterpret_cast<const Int *>(
			reinterpret_cast<const char *>( this ) + 0x4B4 );
	}

	bool hasPhaseFlag() const
	{
		return ( ( *reinterpret_cast<const UnsignedInt *>(
			reinterpret_cast<const char *>( this ) + 0xD0 ) >> 25 ) & 1 ) != 0;
	}
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate( const AsciiString &name );
};

#define TheThingFactory (*(ThingFactory **)0x012EF1D8)

class LivingWorldArmy
{
public:
	AsciiString getName() const;

	Int getCount() const
	{
		return *reinterpret_cast<const Int *>(
			reinterpret_cast<const char *>( this ) + 0x34 );
	}

	unsigned char getFlag() const
	{
		return *reinterpret_cast<const unsigned char *>(
			reinterpret_cast<const char *>( this ) + 0x38 );
	}

private:
	char m_body[ 0xB4 ];
};

struct Rva00364980HeapCompare
{
	void *m_state;
};

struct Rva002EE330PlayerList
{
	char m_unmodelled[ 0x0C ];
	void *m_campaign;
};

#define Rva002EE330ThePlayers (*(Rva002EE330PlayerList **)0x012ED748)

class Rva000C7C30Holder
{
public:
	Int get( Int unused ) const;
};

struct Rva00367010Work
{
	Rva00367010Work()
	{
		typedef void ( Rva00367010Work::*WorkCall )();
		union { void ( *raw )(); WorkCall member; } workCtor;
		workCtor.raw = j_0003b91c;
		( this->*workCtor.member )();
	}

	~Rva00367010Work()
	{
		typedef void ( Rva00367010Work::*WorkCall )();
		union { void ( *raw )(); WorkCall member; } workDtor;
		workDtor.raw = j_0000f2e5;
		( this->*workDtor.member )();
	}

	unsigned int m_state;
};

class Rva003677B0Entry
{
public:
	void finish( void *value, bool enabled );
	void addArmy( LivingWorldArmy *army, Int count, void **pending );

	char m_lead[ 0x20 ];
	int m_state;
	char m_middle[ 0x0C ];
	_STL::vector<LivingWorldArmy> m_armies;
	char m_value;
	char m_gap3D[ 7 ];
	int m_survivalThreshold;
};

static Int rva003677B0ArmyCount( Rva003677B0Entry *entry )
{
	typedef Int ( Rva003677B0Entry::*CountCall )() const;
	union { void ( *raw )(); CountCall member; } call;
	call.raw = j_0000ebce;
	return ( entry->*call.member )();
}

static void rva003677B0SortArmies( LivingWorldArmy *first,
	LivingWorldArmy *last, Rva00364980HeapCompare compare )
{
	typedef void ( __cdecl *SortCall )(
		LivingWorldArmy *, LivingWorldArmy *, Rva00364980HeapCompare );
	union { void ( *raw )(); SortCall function; } call;
	call.raw = j_0001e56f;
	call.function( first, last, compare );
}

static ThingTemplate *rva003677B0FindTemplate( ThingFactory *factory,
	const AsciiString &name )
{
	typedef ThingTemplate *( ThingFactory::*FindCall )( const AsciiString & );
	union { void ( *raw )(); FindCall member; } call;
	call.raw = j_00028560;
	return ( factory->*call.member )( name );
}

void Rva003677B0Entry::addArmy( LivingWorldArmy *army, Int count,
	void **pending )
{
	typedef void ( Rva003677B0Entry::*AddCall )(
		LivingWorldArmy *, Int, void ** );
	union { void ( *raw )(); AddCall member; } call;
	call.raw = j_00044788;
	( this->*call.member )( army, count, pending );
}

void Rva003677B0Entry::finish( void *value, bool enabled )
{
	Rva00367010Work work;
	_STL::list<void *> pending;

	const Int threshold = m_survivalThreshold;
	bool useSurvivalThreshold = false;
	if ( threshold > 0 && threshold > rva003677B0ArmyCount( this ) )
		useSurvivalThreshold = true;

	Rva00364980HeapCompare compare;
	compare.m_state = 0;
	rva003677B0SortArmies( &m_armies[ 0 ], &m_armies[ 0 ] + m_armies.size(),
		compare );

	Int available;
	if ( enabled )
	{
		Rva002EE330PlayerList *players = Rva002EE330ThePlayers;
		void *campaign = players->m_campaign;
		if ( campaign )
		{
			typedef Int ( Rva000C7C30Holder::*AvailableCall )( Int ) const;
			union { void ( *raw )(); AvailableCall member; } availableCall;
			availableCall.raw = j_0001af23;
			available = ( reinterpret_cast<Rva000C7C30Holder *>(
				reinterpret_cast<char *>( campaign ) + 0x30 )->*
				availableCall.member )( 0 );
		}
		else
			available = 0;
	}
	else
		available = 1000000;

	for ( Int pass = 0; pass < 2; ++pass )
	{
		for ( UnsignedInt index = 0; index < m_armies.size(); ++index )
		{
			LivingWorldArmy *army = &m_armies[ index ];
			if ( army->getFlag() != 0 && !useSurvivalThreshold )
				continue;

			AsciiString name = army->getName();
			ThingTemplate *thingTemplate = rva003677B0FindTemplate(
				TheThingFactory, name );
			if ( thingTemplate == 0 )
				continue;
			if ( thingTemplate->hasPhaseFlag() != ( pass == 0 ) )
				continue;

			const Int commandPointCost = thingTemplate->getCommandPointCost();
			Int count = army->getCount();
			if ( commandPointCost > 0 && available > 0 )
				count = available / commandPointCost;
			if ( count > army->getCount() )
				count = army->getCount();
			if ( count <= 0 )
				continue;

			available -= commandPointCost * count;
			addArmy( army, count, reinterpret_cast<void **>( &pending ) );
		}
	}

	typedef void ( Rva00367010Work::*FinishCall )(
		void **, void *, bool );
	union { void ( *raw )(); FinishCall member; } workFinish;
	workFinish.raw = j_0001a136;
	( work.*workFinish.member )( reinterpret_cast<void **>( &pending ),
		value, enabled );

	m_state = 4;
}
