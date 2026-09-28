// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ??0Eva@@: game/GameEngine/Source/GameClient/Eva.cpp
// Open-BFME5: Eva::Eva, spelled against the retail BFME layout.
//
// IDENTITY (the ledger row at 0x004271B0 was a naked ILT lift filed under
// ?tryUnderAttackEvent@Radar@@; that name is refuted by the body itself):
//   * it installs the Eva vtable pair -- 0x010F1FA8 at +0x00 and 0x010F1F94 at
//     +0x08 -- the exact pair the byte-matched ??1Eva@@UAE@XZ at 0x00426560
//     writes, and slot 1 of the first is the matched ?init@Eva@@UAEXXZ
//     (0x00426680) every Eva call is dispatched through;
//   * it runs the SubsystemInterface base constructor (0x009A1A30) first and
//     the inline empty Snapshot base second, restoring Snapshot's own vtable
//     0x01073744 at +0x08 in between, exactly as the destructor restores it;
//   * it stamps the +0x58/+0x5C pair with 1/true, the same values the matched
//     ?reset@Eva@@ (EvaReset.cpp) stamps, and +0x5C is the enable flag
//     ?setEvaEnabled@Eva@@ writes;
//   * it defaults the BFME-only MiscEvaData bundle at +0x60 to 1000.0f/15/35,
//     the block INI::parseMiscEvaData (Eva.cpp) parses at exactly Eva+0x60;
//   * every Radar method lives near 0x00107000-0x00108000, this body is
//     adjacent to the matched Eva bodies, and it calls the two Eva member
//     helpers (0x00427130, 0x00425E40) that EvaReset/EvaInit also call.
//
// LAYOUT.  Retail Eva is a SubsystemInterface AND a Snapshot (two vtable
// pointers, +0x00 and +0x08), then four parsed-table containers, the live
// check vector, the +0x58/+0x5C pair and MiscEvaData.  Zero Hour's Eva.h
// describes none of that, so the class is spelled locally here (AGENTS.md,
// "Placement and integrity": TU-scoped shims over shared-header edits).
//
//   +0x0C  12-byte vector header, never touched again by this body
//   +0x18  12-byte vector header over 28-byte parsed records; resized to 17
//          by the matched body at 0x00427130 (ILT 0x000226FB)
//   +0x24  STLport hash_map, 100 buckets (matched _M_initialize_buckets at
//          0x00424990 through ILT 0x0003301E)
//   +0x38  the same hash_map; the loop below fills it with the 17 message
//          names -> their index, through the matched hashtable resize
//          (0x004240F0, ILT 0x0001B9FF) and insert_unique_noresize
//          (0x00424D30, ILT 0x000382C6)
//   +0x4C  12-byte vector header over 24-byte live check records, resized to
//          17 copies of the invalid check by the matched 0x00425E40
//          (ILT 0x000247DA)
//
// The 17 is not a guess: the body loops over TheEvaMessageNames[0..16] and the
// table at 0x010F1AF0 (the DIR32 this body indexes, verified to hold exactly
// DefaultEvaEvent, BaseUnderAttack, AllyUnderAttack, BeaconDetected,
// GeneralLevelUp, UnitLevelUp, UpgradeComplete, CastleBreached,
// EnemyCampSighted, AllyDefeated, EnemyCampDestroyed, CampDestroyed,
// AllyCampDestroyed, BuildQueuePausedDueToCPLimit, CannotBuildDueToCPLimit,
// BuildingBeingStolen, BuildingStolen, then the next table's "Side") is BFME's
// 17-entry Eva message list.
//
// The mapped payload is a placeholder name: the body only ever stores the
// loop index into it, and the matched insert body never reads it, so the value
// type keeps the address-derived spelling the matched hashtable bodies already
// use for this instantiation.

#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <hash_map>

// Retail's unwind map registers a cleanup entry for each of the three vector
// members and for the live check vector, so all four are non-trivially
// destructible here.  A destructor defined empty inside the class is dropped
// by VC7.1 together with its unwind entry, and a body-less declaration also
// adds a normal-path call; an intrinsic body keeps the entry and emits no
// instruction (docs/shape_levers.md, "the EH state constants are all one
// higher in retail").  No constructor ever calls these, so the normal path is
// unchanged.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

extern const char *TheEvaMessageNames[];

// The AsciiString functors the matched hashtable bodies use.  This body never
// hashes or compares: both live inside the out-of-line insert_unique_noresize
// at 0x00424D30, which calls the pinned bucket helper at 0x0001E4E3 and the
// StringBase comparison inline.  Only the class NAMES matter here, because the
// mangled instantiation is what resolves the three hashtable callees.
namespace rts
{
template <class T> struct hash;

template <>
struct hash<AsciiString>
{
	UnsignedInt operator()(const AsciiString &value) const;
};

template <class T> struct equal_to;

template <>
struct equal_to<AsciiString>
{
	Bool operator()(const AsciiString &left, const AsciiString &right) const;
};
}

// Address-derived payload view: see the header comment.  The pointer spelling
// is the one the matched 0x004240F0 hashtable body already carries, so the
// resize call below resolves through that body's incremental-link thunk.
struct Rva004240F0Value
{
	UnsignedInt m_payload;
};

typedef _STL::pair<const AsciiString, Rva004240F0Value *> EvaNameIndexPair;
typedef _STL::hash_map<AsciiString, Rva004240F0Value *,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > EvaNameIndexMap;

// The live per-message check record, 24 bytes: two frame stamps this body
// invalidates and the "already played" flag at +0x14.  The default constructor
// is the invalid record, which is why the resize below can pass a temporary.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheck
{
	EvaCheck( void )
	{
		m_a = -1.0f;
		m_b = -1.0f;
		m_flag = 0;
	}
	EvaCheck( const EvaCheck &that );
	~EvaCheck( void );

	Real m_a;					// +0x00
	Real m_b;					// +0x04
	void *m_c;					// +0x08
	UnsignedInt m_d;			// +0x0c
	UnsignedInt m_e;			// +0x10
	char m_flag;				// +0x14
};

// +0x4C: the live check vector.  The two-argument resize is the matched
// 0x00425E40 body reached through ILT 0x000247DA; its fill value is 24 bytes
// BY VALUE, which is what the retail call site's 28-byte argument area and the
// callee's `ret 0x1c` both prove.
class EvaCheckVector
{
public:
	EvaCheckVector( void ) : m_begin( 0 ), m_end( 0 ), m_capacity( 0 ) {}
	~EvaCheckVector( void ) { _ReadWriteBarrier(); }

	void resize( Int count, EvaCheck value );

private:
	char *m_begin;
	char *m_end;
	char *m_capacity;
};

// +0x18: the vector of parsed check-info records (28-byte stride, proven by the
// matched resize body at 0x00427130, which this body calls with 17 through ILT
// 0x000226FB).
class Rva00427130Vector
{
public:
	Rva00427130Vector( void ) : m_begin( 0 ), m_end( 0 ), m_capacity( 0 ) {}
	~Rva00427130Vector( void ) { _ReadWriteBarrier(); }

	void resize( UnsignedInt count );

private:
	char *m_begin;
	char *m_end;
	char *m_capacity;
};

// +0x0C: the second 12-byte vector header, empty for the life of this body.
class EvaCheckInfoPtrVector
{
public:
	EvaCheckInfoPtrVector( void ) : m_begin( 0 ), m_end( 0 ), m_capacity( 0 ) {}
	~EvaCheckInfoPtrVector( void ) { _ReadWriteBarrier(); }

private:
	char *m_begin;
	char *m_end;
	char *m_capacity;
};

// The +0x08 base.  Its destructor is inline and empty in retail, and its
// constructor is too: the body only installs the vtable pointer.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot( void ) {}
	virtual void crc( void ) = 0;
	virtual void xfer( void ) = 0;
	virtual void loadPostProcess( void ) = 0;
};

// The primary base: vtable pointer at +0x00 and the subsystem name at +0x04.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface( void );
	virtual ~SubsystemInterface( void );
	virtual void init( void ) = 0;

private:
	void *m_name;				// +0x04
};

// BFME-only: the global settings bundle INI::parseMiscEvaData parses at
// Eva+0x60 (Eva.cpp).  The three defaults below are the compiled ones; the
// field names are not recovered, so they stay address-derived.
struct MiscEvaDataFields
{
	MiscEvaDataFields( void )
		: m_at60( 1000.0f )
		, m_at64( 15 )
		, m_at68( 35 )
	{
	}

	Real m_at60;					// +0x60
	Int  m_at64;					// +0x64
	Int  m_at68;					// +0x68
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
class Eva : public SubsystemInterface, public Snapshot
{
public:
	Eva( void );

	virtual ~Eva( void );

private:
	EvaCheckInfoPtrVector m_checkInfos;			// +0x0c
	Rva00427130Vector     m_defaultCheckInfos;		// +0x18
	EvaNameIndexMap       m_nameToMessage;			// +0x24
	EvaNameIndexMap       m_defaultNameToMessage;	// +0x38
	EvaCheckVector       m_checks;				// +0x4c
	Int                  m_resetCount;			// +0x58
	Bool                 m_enabled;				// +0x5c
	MiscEvaDataFields    m_miscEvaData;			// +0x60
};

Eva::Eva( void )
	: m_checkInfos()
	, m_defaultCheckInfos()
	, m_nameToMessage()
	, m_defaultNameToMessage()
	, m_checks()
	, m_resetCount( 1 )
	, m_enabled( true )
	, m_miscEvaData()
{
	// One invalid check per message, the same fill Eva::reset performs.
	m_checks.resize( 17, EvaCheck() );
	m_defaultCheckInfos.resize( 17 );

	// Seed the pristine copy of the name index, so a reset can restore it
	// wholesale: message name -> its index in TheEvaMessageNames.
	//
	// `entry` is a NAMED local, not a temporary inside the insert() call: that
	// is what ends the AsciiString temporary's scope right after the pair is
	// built, which is where retail calls releaseBuffer (0x00887940) -- before
	// the resize and the insert.  Handed straight to insert() as a temporary,
	// VC7.1 stretches the string temporary to the end of the loop body and the
	// second releaseBuffer lands one call too late.
	for( UnsignedInt i = 0; i < 17; ++i )
	{
		EvaNameIndexPair entry( AsciiString( TheEvaMessageNames[ i ] ),
			(Rva004240F0Value *)i );
		m_defaultNameToMessage.insert( entry );
	}
}
