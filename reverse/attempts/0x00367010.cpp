// ?finish@Rva003677B0Entry@@QAEXPAX_N@Z
// partial score=0.23 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// The 0x00367010 body is a distinct 613-byte entry operation.  The smaller
// indexed caller below only proves the entry ABI; its body is not a donor for
// this reconstruction.  Retail uses the same 0xB4-byte army records and
// narrow StringBase/ThingFactory calls as the independently recovered
// LivingWorldPlayerArmy family, but the owner of this address remains
// address-derived because the three raw callers do not name it.
#include "PreRTS.h"
#include "Common/INI.h"
#include <vector>

void operator delete( void *, unsigned int );

extern void j_0000ebce();
extern void j_0000f2e5();
extern void j_0001a136();
extern void j_0001af23();
extern void j_0001e56f();
extern void j_00028560();
extern void j_0003b91c();
extern void j_00044788();

class ThingTemplate
{
public:
	Int getCommandPointCost() const { return m_commandPointCost; }
	bool hasPhaseFlag() const
	{
		return ((*reinterpret_cast<const UnsignedInt *>(
			reinterpret_cast<const char *>( this ) + 0xD0 ) >> 25) & 1) != 0;
	}

private:
	char m_unmodelled[ 0x4B4 ];
	Int m_commandPointCost;
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate( const AsciiString &name );
};

extern ThingFactory *TheThingFactory;

class LivingWorldArmy
{
public:
	AsciiString getName() const;

	Int getCount() const
	{
		return *reinterpret_cast<const Int *>( reinterpret_cast<const char *>( this ) + 0x34 );
	}

	unsigned char getFlag() const
	{
		return *reinterpret_cast<const unsigned char *>( reinterpret_cast<const char *>( this ) + 0x38 );
	}

	private:
	char m_body[ 0xB4 ];
};

// The local list is the retail three-word node: next, previous and an
// optional payload.  Keeping the links typed avoids aliasing the stack slot
// through an unrelated scalar type while retaining the observed 12-byte
// allocation and cleanup.
struct Rva00367010Node
{
	Rva00367010Node *m_next;
	Rva00367010Node *m_previous;
	void *m_value;
};

struct Rva00367010Work
{
	unsigned int m_state;
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

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class Rva000C7C30Holder
{
public:
	Int get( Int unused ) const;
};

class Rva003677B0Entry
{
public:
	void finish( void *value, bool enabled );

	char m_lead[ 0x20 ];
	int  m_state;
	char m_middle[ 0x0C ];
	std::vector<LivingWorldArmy> m_armies;
	char m_value;
	char m_gap3D[ 7 ];
	int  m_survivalThreshold;

	void addArmy( LivingWorldArmy *army, Int count, Rva00367010Node **pending );
};

static Int rva003677B0ArmyCount( Rva003677B0Entry *entry )
{
	typedef Int (Rva003677B0Entry::*CountCall)() const;
	union { void (*raw)(); CountCall member; } call;
	call.raw = j_0000ebce;
	return (entry->*call.member)();
}

static void rva003677B0SortArmies( LivingWorldArmy *first,
	LivingWorldArmy *last, Rva00364980HeapCompare compare )
{
	typedef void (__cdecl *SortCall)(
		LivingWorldArmy *, LivingWorldArmy *, Rva00364980HeapCompare);
	union { void (*raw)(); SortCall function; } call;
	call.raw = j_0001e56f;
	call.function( first, last, compare );
}

static ThingTemplate *rva003677B0FindTemplate( ThingFactory *factory,
	const AsciiString &name )
{
	typedef ThingTemplate *(ThingFactory::*FindCall)( const AsciiString & );
	union { void (*raw)(); FindCall member; } call;
	call.raw = j_00028560;
	return (factory->*call.member)( name );
}

void Rva003677B0Entry::addArmy( LivingWorldArmy *army, Int count,
	Rva00367010Node **pending )
{
	typedef void (Rva003677B0Entry::*AddCall)(
		LivingWorldArmy *, Int, Rva00367010Node **);
	union { void (*raw)(); AddCall member; } call;
	call.raw = j_00044788;
	(this->*call.member)( army, count, pending );
}

void Rva003677B0Entry::finish( void *value, bool enabled )
{
	Rva00367010Work work;
	typedef void (Rva00367010Work::*WorkCall)();
	union { void (*raw)(); WorkCall member; } workCtor;
	workCtor.raw = j_0003b91c;
	(work.*workCtor.member)();

	Rva00367010Node *pending = static_cast<Rva00367010Node *>(
		::operator new( 0x0C ));
	pending->m_next = pending;
	pending->m_previous = pending;

	const Int threshold = m_survivalThreshold;
	bool useSurvivalThreshold = false;
	if( threshold > 0 && threshold > rva003677B0ArmyCount( this ))
		useSurvivalThreshold = true;

	Rva00364980HeapCompare compare;
	compare.m_state = 0;
	rva003677B0SortArmies( &m_armies[ 0 ], &m_armies[ 0 ] + m_armies.size(),
		compare );

	Int available;
	if( enabled )
	{
		Rva002EE330PlayerList *players = Rva002EE330ThePlayers;
		void *campaign = players->m_campaign;
		if( campaign )
		{
			typedef Int (Rva000C7C30Holder::*AvailableCall)( Int ) const;
			union { void (*raw)(); AvailableCall member; } availableCall;
			availableCall.raw = j_0001af23;
			available = (reinterpret_cast<Rva000C7C30Holder *>(
				reinterpret_cast<char *>( campaign ) + 0x30 )->*
				availableCall.member)( 0 );
		}
		else
			available = 0;
	}
	else
		available = 1000000;

	for( Int pass = 0; pass < 2; ++pass )
	{
		for( UnsignedInt index = 0; index < m_armies.size(); ++index )
		{
			LivingWorldArmy *army = &m_armies[ index ];
			if( army->getFlag() != 0 && !useSurvivalThreshold )
				continue;

			AsciiString name = army->getName();
			ThingTemplate *thingTemplate = rva003677B0FindTemplate(
				TheThingFactory, name );
			if( thingTemplate == 0 )
				continue;
			if( thingTemplate->hasPhaseFlag() != (pass == 0) )
				continue;

			const Int commandPointCost = thingTemplate->getCommandPointCost();
			Int count = army->getCount();
			if( commandPointCost > 0 && available > 0 )
				count = available / commandPointCost;
			if( count > army->getCount() )
				count = army->getCount();
			if( count <= 0 )
				continue;

			available -= commandPointCost * count;
			addArmy( army, count, &pending );
		}
	}

	typedef void (Rva00367010Work::*FinishCall)(
		Rva00367010Node **, void *, bool);
	union { void (*raw)(); FinishCall member; } workFinish;
	workFinish.raw = j_0001a136;
	(work.*workFinish.member)( &pending, value, enabled );

	m_state = 4;
	Rva00367010Node *node = pending->m_next;
	if( node != pending )
	{
		do
		{
			Rva00367010Node *next = node->m_next;
			::operator delete( node, 0x0C );
			node = next;
		}
		while( node != pending );
	}
	pending->m_next = pending;
	pending->m_previous = pending;
	::operator delete( pending, 0x0C );

	union { void (*raw)(); WorkCall member; } workDtor;
	workDtor.raw = j_0000f2e5;
	(work.*workDtor.member)();
}

class Rva003677B0SmallEntry
{
public:
	char m_lead[ 0x20 ];
	int  m_state;
	char m_middle[ 0x18 ];
	char m_value;
	char m_tail[ 0x1B ];
};

class Rva003677B0EntryRange
{
public:
	unsigned int size() const { return m_last - m_first; }
	Rva003677B0SmallEntry &operator[]( int index ) { return m_first[ index ]; }

private:
	Rva003677B0SmallEntry *m_first;
	Rva003677B0SmallEntry *m_last;
};

class Rva003677B0IndexedEntries
{
public:
	void finish( int index );

private:
	char m_lead[ 0x18 ];
	Rva003677B0EntryRange m_entries;
};

void Rva003677B0IndexedEntries::finish( int index )
{
	if( index < 0 || static_cast<unsigned int>( index ) >= m_entries.size() )
		return;

	Rva003677B0SmallEntry &entry = m_entries[ index ];
	if( entry.m_state == 3 )
	{
		entry.m_state = 4;
		reinterpret_cast<Rva003677B0Entry *>( &entry )->finish(
			&entry.m_value, false );
	}
}
