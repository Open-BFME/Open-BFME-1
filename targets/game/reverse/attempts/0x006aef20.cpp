// ?rva006AEF20@MilesAudioManager@@QAEXPAVXfer@@PAVPlayingAudioRef@@PAUXferVersion@@@Z
// partial score=0.29 date=2026-09-28
// cl: /FAsc /Fabuild/w63/x3.cod /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// RVA 006B0E00: MilesAudioManager::MilesAudioManager (1550 B; RET at +0x60D, INT3 after).
// RVA 006ACF50: MilesAudioManager::~MilesAudioManager (1256 B), reached from
//   primary vtable slot 0 through the scalar-deleting wrapper 0x006AF7B0. It
//   installs the same vtable pair, holds the "LOTRMilesAudioManagerMutex"
//   handle through the scoped lock whose out-of-line destructor is 0x006915E0,
//   drains the +0x4C request list and +0x50 request set (RequestFlags006A6B40),
//   then destroys every member in reverse order (29 unwind states, the last one
//   the lock) and ends in the inlined Rva00694E00 destructor.
//
// IDENTITY
//   * installs the MilesAudioManager vtable pair 0x0111C0C0 (+0x00) and
//     0x0111C0AC (+0x08); the destructor 0x006ACF50 (reached from slot 0 through
//     the scalar-deleting wrapper 0x006AF7B0) installs the same pair, and slot 2
//     of the +0x08 table (0x00696360) returns the literal "MilesAudioManager";
//   * creates the named mutex "LOTRMilesAudioManagerMutex" (string 0x0111BA5C)
//     at +0x95C, the handle the destructor waits on and closes;
//   * +0x0C receives a new AudioSettings, the pointer the matched
//     MilesAudioManager::openDevice (MilesAudioManager.cpp) reads at +0x0C, and
//     +0xB68 the _time64 stamp openDevice rewrites;
//   * sole caller: the niladic factory make006B5890 (via ILT).
//
// Member types: every out-of-line destructor the retail destructor calls binds
// by its instantiation's mangled name (vector<AsciiString>, vector<UnicodeString>,
// set<AsciiString>, the request containers, and address-derived payloads that
// keep the names the matched STLport bodies already carry).
//
// LAYOUT. BFME's audio manager shares almost nothing with Zero Hour's; members
// are spelled from this body alone and keep their offsets as names except where
// the body proves the role. The two bases are wrapped in the novtable
// intermediate class whose out-of-line ctor/dtor are the matched 0x00694E00 /
// 0x00694E30: retail's unwind state 0 calls that destructor, which is why the
// Snapshot base has no unwind state of its own here (unlike Eva). Every
// container is real STLport so that its constructor inlines as retail's does;
// each out-of-line helper binds by its instantiation's mangled name.
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <wchar.h>
#include "Common/UnicodeString.h"
#include <hash_map>
#include <hash_set>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <queue>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef __int64 Time64;

extern "C" __declspec(dllimport) Time64 __cdecl _time64(Time64 *time);
extern "C" __declspec(dllimport) void *__stdcall CreateMutexA(void *attributes, int initialOwner, const char *name);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *mutex);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *addend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *addend);

inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

// Only the slots this TU calls are named; the rest keep their index.
class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading( void );
	virtual void slot02();
	virtual Bool isCRC( void );
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual Xfer &xferVersion( XferVersion *version );
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual Xfer &xferReal( Real *value );
	virtual void slot28();
	virtual Xfer &xferUnsignedInt( UnsignedInt *value );
	virtual Xfer &xferInt( Int *value );
	virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual Xfer &xferBool( Bool *value );
	virtual Xfer &xferEnum( const char *name, void *data, UnsignedInt size );
};

extern void __cdecl xferTree( Xfer *xfer, void *tree );
Xfer *xferUnicodeStringVector( Xfer *xfer, _STL::vector<UnicodeString> *strings );
Xfer *xferAsciiStringVector( Xfer *xfer, _STL::vector<AsciiString> *strings );

class AsciiString;
extern const AsciiString Rva01336E50EmptyString;

struct Rva006B4D30Info { char m_pad00[0x84]; Int m_84; };
class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &eventName, int objectID );
	virtual ~AudioEventRTS();
	void rva000B2B50( Xfer *xfer );
	void setPlayingHandle( UnsignedInt handle );
	void rva000B3C60( void );
	void bfmeGenerateFilename( void );
	AsciiString getFilename( void );
	char m_pad04[4];
	Rva006B4D30Info *m_08;
	UnsignedInt m_0c;
	char m_pad10[0x18];
	Int m_28;
	char m_pad2c[0x1d];
	Bool m_49;
	char m_pad4a[0x1e];
	Int m_68;
	char m_pad6c[4];
};
// Counted base at +0x70 (Rva006A3200EntryList.cpp).
class BfmeBaseASCa
{
public:
	BfmeBaseASCa() : m_refCount( 0 ) {}
	virtual ~BfmeBaseASCa();
	long m_refCount;
};
class Rva006A1790Event : public AudioEventRTS, public BfmeBaseASCa
{
public:
	Rva006A1790Event( const AsciiString &eventName, int objectID ) : AudioEventRTS( eventName, objectID ) {}
};
class Rva006A1790EventRef
{
public:
	Rva006A1790EventRef &operator=( Rva006A1790Event *ptr );
	Rva006A1790Event *operator->( void ) const { return m_ptr; }
	Rva006A1790Event *m_ptr;
};

// PlayingAudio as MilesAudioManagerAllocatePlayingAudio.cpp models it, plus
// the fields the save code reads and writes.
class PlayingAudio
{
public:
	virtual ~PlayingAudio();
	void Add_Ref( void ) { InterlockedIncrement( &m_refCount ); }
	void Release_Ref( void )
	{
		if ( InterlockedDecrement( &m_refCount ) <= 0 )
			delete this;
	}
	long m_refCount;
	void *m_milesHandle;
	Int m_type;
	Int m_status;
	Rva006A1790EventRef m_event;
	char m_pad18[0x1c];
	Bool m_34;
	char m_pad35[4];
	Bool m_39;
	char m_pad3a[2];
	Bool m_3c;
	char m_pad3d[3];
};
class PlayingAudioRef
{
public:
	PlayingAudioRef( void ) : m_ptr( 0 ) {}
	PlayingAudioRef( const PlayingAudioRef &that ) : m_ptr( that.m_ptr )
	{
		if ( m_ptr )
			m_ptr->Add_Ref();
	}
	~PlayingAudioRef( void )
	{
		if ( m_ptr )
			m_ptr->Release_Ref();
	}
	PlayingAudioRef &operator=( const PlayingAudioRef &that );
	void clear( void )
	{
		if ( m_ptr )
		{
			m_ptr->Release_Ref();
			m_ptr = 0;
		}
	}
	PlayingAudio *operator->( void ) const { return m_ptr; }
	PlayingAudio *m_ptr;
};
struct Rva006B4D30Group { char m_pad00[0xc]; Int m_0c; };
struct Rva006B4D30GroupValue { Rva006B4D30Group *m_group; Real m_value; };
struct Rva006B4D30IdValue { Int m_id; Real m_value; };

// Scoped mutex hold; its out-of-line destructor is 0x006915E0.
class Rva006915E0
{
public:
	Rva006915E0( void *mutex ) : m_held( false )
	{
		m_mutex = mutex;
		if ( WaitForSingleObject( mutex, 0xFFFFFFFF ) != 0x102 )
			m_held = true;
	}
	~Rva006915E0( void ) { release(); }
	void release( void )
	{
		if ( m_held )
		{
			ReleaseMutex( m_mutex );
			m_held = false;
		}
	}

private:
	void *m_mutex;
	Bool m_held;
};

class Snapshot
{
public:
	virtual ~Snapshot( void ) {}
	virtual void crc( void ) = 0;
	virtual void xfer( Xfer *xfer ) = 0;
	virtual void loadPostProcess( void ) = 0;
};

class SubsystemInterface
{
public:
	SubsystemInterface( void );
	virtual ~SubsystemInterface( void );
	virtual void init( void ) = 0;

private:
	void *m_name;
};

// The novtable intermediate base whose out-of-line constructor (0x00694E00) and
// destructor (0x00694E30) are matched; retail's unwind state 0 destroys it.
class __declspec(novtable) Rva00694E00 : public SubsystemInterface, public Snapshot
{
public:
	Rva00694E00( void ) {}
	virtual ~Rva00694E00( void ) {}
};

class AudioSettings { public: AudioSettings( void ); ~AudioSettings( void ); char m_body[0x138]; };
class MiscAudio { public: MiscAudio( void ); ~MiscAudio( void ); char m_body[0xe00]; };
class Rva00694710AudioWorker { public: Rva00694710AudioWorker( void *mutex ); ~Rva00694710AudioWorker( void ); char m_body[0x4c]; };
class Gen0000D33C { public: ~Gen0000D33C( void ); char m_body[0x14]; };
class Rva006A9800This { public: void rva006A9800( void ); };
class Rva00695AB0Owner { public: void setRoomType( Int roomType ); };
class Rva006AD590Owner { public: void bfmeAdjustPriorityAndVolume( AudioEventRTS *event ); };
class Ref006AE2C0;
class StartAudioStream006AE2C0 { public: void start( const Ref006AE2C0 &audio, Real position ); };
class BfmeHostESG { public: ~BfmeHostESG( void ); };
struct Rva005A00B0AudioClient;
extern Rva005A00B0AudioClient *TheAudioClientUpdate;

// The +0x4C request list and +0x50 pointer-keyed request set, as in
// RequestFlags006A6B40.cpp; the request destructor is 0x006912A0.
struct AudioRequest006A6B40 { unsigned int dword00; void *event04; unsigned int hash08; };
struct RequestHash006A6B40 {
	unsigned int operator()( const AudioRequest006A6B40 *p ) const { if ( !p ) return 0; return p->hash08; }
};
class RequestTable006A6B40 : public _STL::hash_set<AudioRequest006A6B40 *, RequestHash006A6B40>
{
public:
	iterator findHandle( UnsignedInt handle );
};
typedef _STL::list<AudioRequest006A6B40 *> RequestList006A6B40;

class Rva006A6CF0String { public: ~Rva006A6CF0String( void ); void *m_data; };
struct Gen_t_0069e220_p4pod { int v; };
struct Gen_t_0069e310_p4pod { int v; };
struct Gen_t_0069e400_p4pod { int v; };
struct Rva006A4630Value { UnsignedInt m_handle; };
struct Rva006AD440Entry { ~Rva006AD440Entry( void ); char m_body[0x40]; };

// Hash map payloads and set key: the address-derived spellings the matched
// out-of-line STLport bodies already carry.
struct Gen_t_006aab80_p12cd { int a[3]; };
struct Gen_t_006aad10_p12cd { int a[3]; };
struct Gen_t_006a3b50_p12cd { int a[3]; };
struct Gen_t_006a3c20_p12cd { int a[3]; };
struct Gen_t_006a3cf0_p12cd { int a[3]; };
struct Gen00026F35 { int a[3]; };

// Array element types: out-of-line constructors and destructors passed to the
// EH vector constructor iterator.
class Rva006ABC60
{
public:
	Rva006ABC60( void );
	~Rva006ABC60( void );
	void setIndex( Int index ) { m_index00 = index; }
	void xfer( Xfer *xfer );

private:
	Int m_index00;			// the owner stores the element's array index here
	char m_body[0x1c0];
};
class Rva0069CEE0 { public: Rva0069CEE0( void ); ~Rva0069CEE0( void ); char m_body[0xc]; };
class Rva00478100 { public: Rva00478100( void ); ~Rva00478100( void ); char m_body[0xc]; };
class Rva006967A0
{
public:
	Rva006967A0( void );
	~Rva006967A0( void );
	void clear( void )
	{
		if ( m_ptr )
		{
			m_ptr->Release_Ref();
			m_ptr = 0;
		}
	}
	PlayingAudio *m_ptr;
};

class MilesAudioManager : public Rva00694E00
{
public:
	MilesAudioManager( void );
	virtual ~MilesAudioManager( void );
	virtual void init( void );
	virtual void slot08( void );
	virtual void slot0C( void );
	virtual void slot10( void );
	virtual void slot14( void );
	virtual void slot18( void );
	virtual void slot1C( void );
	virtual void slot20( void );
	virtual void slot24( void );
	virtual void slot28( void );
	virtual void slot2C( void );
	virtual void slot30( void );
	virtual void slot34( void );
	virtual void slot38( void );
	virtual void slot3C( void );
	virtual void slot40( void );
	virtual void slot44( void );
	virtual void slot48( void );
	virtual void slot4C( void );
	virtual void slot50( void );
	virtual void slot54( void );
	virtual void slot58( void );
	virtual void slot5C( void );
	virtual void slot60( void );
	virtual void slot64( void );
	virtual void slot68( void );
	virtual void slot6C( void );
	virtual void slot70( void );
	virtual void slot74( void );
	virtual void slot78( void );
	virtual void slot7C( void );
	virtual void slot80( void );
	virtual void slot84( void );
	virtual void slot88( void );
	virtual void slot8C( void );
	virtual void slot90( void );
	virtual void slot94( void );
	virtual void slot98( void );
	virtual void slot9C( void );
	virtual void slotA0( void );
	virtual void slotA4( void );
	virtual void slotA8( void );
	virtual void slot0AC( AudioEventRTS *event );
	virtual void crc( void );
	virtual void xfer( Xfer *xfer );
	void rva006AEF20( Xfer *xfer, PlayingAudioRef *handle, XferVersion *version );
	PlayingAudioRef allocatePlayingAudio( void );
	void rva006B2D80( void );
	virtual void loadPostProcess( void );

private:
	AudioSettings *m_audioSettings;						// +0x00c
	MiscAudio *m_miscAudio;								// +0x010
	UnsignedInt m_014, m_018, m_01c, m_020;				// +0x014
	Real m_024;											// +0x024
	UnsignedInt m_028, m_02c, m_030, m_034, m_038, m_03c, m_040;
	Real m_044;											// +0x044
	UnsignedInt m_048;									// +0x048
	RequestList006A6B40 m_requests;						// +0x04c
	RequestTable006A6B40 m_requestTable;	// +0x050
	_STL::set<AsciiString> m_set064;				// +0x064
	_STL::hash_map<int, Gen_t_006aab80_p12cd> m_hash070;	// +0x070
	Int m_084;											// +0x084
	_STL::vector<Rva006A6CF0String> m_vector088;						// +0x088
	_STL::vector<Gen00026F35> m_vectors094[3];			// +0x094
	Rva006ABC60 m_slots[3];								// +0x0b8
	Int m_604;											// +0x604
	UnsignedInt m_608, m_60c, m_610, m_614, m_618, m_61c, m_620, m_624;
	short m_628;										// +0x628
	Bool m_62a, m_62b, m_62c, m_62d, m_62e;				// +0x62a
	Bool m_62f, m_630, m_631, m_632, m_633, m_634, m_635, m_636, m_637;
	UnsignedInt m_638;									// +0x638
	UnsignedInt m_63c[3];								// +0x63c
	UnsignedInt m_648[3];								// +0x648
	Rva0069CEE0 m_654[0x40];							// +0x654
	UnsignedInt m_954;									// +0x954
	Int m_958;											// +0x958
	void *m_mutex;										// +0x95c
	void *m_digitalHandle960;
	UnsignedInt m_964, m_968;					// +0x960
	_STL::hash_map<int, Gen_t_006aad10_p12cd> m_hash96c;	// +0x96c
	_STL::vector<UnicodeString> m_vector980;						// +0x980
	_STL::vector<AsciiString> m_vector98c;						// +0x98c
	Rva00478100 m_998[3];								// +0x998
	_STL::list<Gen_t_0069e220_p4pod> m_list9bc;						// +0x9bc
	_STL::list<Gen_t_0069e310_p4pod> m_list9c0;
	_STL::list<Gen_t_0069e400_p4pod> m_list9c4;
	_STL::list<PlayingAudioRef> m_list9c8;
	_STL::list<PlayingAudioRef> m_list9cc;
	_STL::list<PlayingAudioRef> m_list9d0;
	_STL::deque<PlayingAudioRef> m_queues[6];			// +0x9d4
	UnsignedInt m_ac4[3];								// +0xac4
	Rva006967A0 m_ad0[3];								// +0xad0
	_STL::vector<Rva006B4D30GroupValue> m_vectoradc;						// +0xadc
	_STL::vector<Rva006B4D30IdValue> m_vectorae8;						// +0xae8
	_STL::map<UnsignedInt, Rva006A4630Value> m_mapaf4;						// +0xaf4
	Rva00694710AudioWorker *m_worker;					// +0xb00
	_STL::list<PlayingAudioRef> m_listb04;						// +0xb04
	_STL::hash_map<int, Gen_t_006a3b50_p12cd> m_hashb08;	// +0xb08
	_STL::hash_map<int, Gen_t_006a3c20_p12cd> m_hashb1c;	// +0xb1c
	_STL::hash_map<int, Gen_t_006a3cf0_p12cd> m_hashb30;	// +0xb30
	Rva006AD440Entry *m_b44;
	UnsignedInt m_b48;							// +0xb44
	Int m_b4c;											// +0xb4c
	UnsignedInt m_b50;
	Int m_b54;
	Gen0000D33C *m_b58;					// +0xb50
	Int m_b5c;											// +0xb5c
	UnsignedInt m_b60;									// +0xb60
	Time64 m_b68;										// +0xb68
	Bool m_b70;											// +0xb70
};

MilesAudioManager::MilesAudioManager( void )
	: m_audioSettings( 0 ), m_miscAudio( 0 ),
	  m_014( 0 ), m_018( 0 ), m_01c( 0 ), m_020( 0 ),
	  m_024( 1.0f ),
	  m_028( 0 ), m_02c( 0 ), m_030( 0 ), m_034( 0 ), m_038( 0 ), m_03c( 0 ), m_040( 0 ),
	  m_044( 100.0f / 3.0f ),
	  m_048( 0 ),
	  m_084( 5 ),
	  m_604( 2 ),
	  m_608( 0 ), m_60c( 0 ), m_610( 0 ), m_614( 0 ), m_618( 0 ), m_61c( 0 ), m_620( 0 ), m_624( 0 ),
	  m_628( 2 ),
	  m_62a( true ), m_62b( true ), m_62c( true ), m_62d( true ), m_62e( true ),
	  m_62f( false ), m_630( false ), m_631( false ), m_632( false ), m_633( false ),
	  m_634( false ), m_635( false ), m_636( false ), m_637( false ),
	  m_638( 0 ),
	  m_954( 0 ), m_958( -1 ), m_mutex( 0 ), m_digitalHandle960( 0 ), m_964( 0 ), m_968( 0 ),
	  m_worker( 0 ),
	  m_b44( 0 ), m_b48( 0 ), m_b4c( -1 ), m_b50( 0 ), m_b54( 0 ), m_b58( 0 ), m_b5c( 7 ), m_b60( 0 ),
	  m_b68( _time64( 0 ) ),
	  m_b70( false )
{
	m_set064.clear();
	for ( Int i = 0; i < 3; i++ )
	{
		m_ac4[i] = 0;
		Rva006ABC60 *slot = &m_slots[i];
		slot->setIndex( i );
		m_63c[i] = 0;
		m_648[i] = 0;
	}
	m_audioSettings = new AudioSettings;
	m_miscAudio = new MiscAudio;
	m_mutex = CreateMutexA( 0, 0, "LOTRMilesAudioManagerMutex" );
	m_worker = new Rva00694710AudioWorker( m_mutex );
}

MilesAudioManager::~MilesAudioManager( void )
{
	Rva006915E0 lock( m_mutex );
	((Rva006A9800This *)this)->rva006A9800();
	m_listb04.clear();
	while ( !m_requests.empty() )
	{
		AudioRequest006A6B40 *request = m_requests.back();
		m_requests.pop_back();
		delete (BfmeHostESG *)request;
	}
	RequestTable006A6B40::iterator it = m_requestTable.begin();
	while ( it != m_requestTable.end() )
	{
		AudioRequest006A6B40 *request = *it;
		m_requestTable.erase( it );
		it = m_requestTable.begin();
		delete (BfmeHostESG *)request;
	}
	if ( TheAudioClientUpdate == (Rva005A00B0AudioClient *)this )
		TheAudioClientUpdate = 0;
	m_b48 = 0;
	delete [] m_b44;
	delete m_worker;
	lock.release();
	CloseHandle( m_mutex );
	m_mutex = 0;
	if ( m_miscAudio )
	{
		delete m_miscAudio;
		m_miscAudio = 0;
	}
	if ( m_audioSettings )
	{
		delete m_audioSettings;
		m_audioSettings = 0;
	}
	if ( m_b58 )
	{
		delete m_b58;
		m_b58 = 0;
	}
}

void MilesAudioManager::xfer( Xfer *xfer )
{
	if ( xfer->isCRC() )
		return;
	Rva006915E0 lock( m_mutex );
	if ( xfer->isLoading() )
	{
		m_637 = true;
		m_638 = 0;
	}
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 4;
	xfer->xferVersion( &version );
	Int previous = m_604;
	xfer->xferEnum( "AudioViewType", &m_604, 4 );
	if ( previous != m_604 )
		m_631 = true;
	xfer->xferEnum( "AudioViewTypeBits", &m_61c, 4 );
	xfer->xferBool( &m_633 );
	Int i;
	for ( i = 0; i < 3; ++i )
	{
		if ( i == 2 && version.m_currentVersion >= 3 && !m_b70 )
			continue;
		xfer->xferEnum( "MusicSystem", &m_ac4[i], 4 );
		m_slots[i].xfer( xfer );
		xferTree( xfer, &m_998[i] );
		if ( version.m_currentVersion >= 4 )
			xfer->xferEnum( "AudioAffect", &m_63c[i], 4 );
	}
	if ( xfer->isLoading() )
	{
		m_vectorae8.clear();
		Int count;
		xfer->xferInt( &count );
		while ( count )
		{
			Rva006B4D30IdValue entry;
			xfer->xferInt( &entry.m_id );
			xfer->xferReal( &entry.m_value );
			m_vectorae8.push_back( entry );
			--count;
		}
		m_636 = true;
	}
	else
	{
		Int count = m_vectoradc.size();
		xfer->xferInt( &count );
		for ( _STL::vector<Rva006B4D30GroupValue>::iterator it = m_vectoradc.begin(); it != m_vectoradc.end(); ++it )
		{
			Int id = it->m_group->m_0c;
			xfer->xferInt( &id );
			Real value = it->m_value;
			xfer->xferReal( &value );
		}
	}
	xfer->xferInt( &m_b54 );
	if ( xfer->isLoading() )
		((Rva00695AB0Owner *)this)->setRoomType( m_b54 );
	if ( version.m_currentVersion >= 2 )
		xfer->xferUnsignedInt( &m_048 );
	else
		m_048 = 0xFFFFFFFF;
	m_044 = 0;
	if ( xfer->isLoading() )
	{
		Int count;
		xfer->xferInt( &count );
		for ( i = 0; i < count; ++i )
		{
			PlayingAudioRef handle;
			rva006AEF20( xfer, &handle, &version );
			rva006B2D80();
		}
		for ( i = 0; i < 3; ++i )
		{
			if ( i == 2 && version.m_currentVersion >= 3 && !m_b70 )
				continue;
			for ( Int j = 0; j < 2; ++j )
			{
				_STL::deque<PlayingAudioRef> &queue = m_queues[i * 2 + j];
				Int size = queue.size();
				Int entries;
				xfer->xferInt( &entries );
				for ( Int k = 0; k < entries; ++k )
				{
					PlayingAudioRef handle;
					rva006AEF20( xfer, &handle, &version );
					if ( handle.m_ptr && queue.size() == size )
						queue.push_back( handle );
					size = queue.size();
				}
			}
		}
		for ( i = 0; i < 3; ++i )
		{
			if ( i == 2 && version.m_currentVersion >= 3 && !m_b70 )
				continue;
			m_ad0[i].clear();
		}
		m_vector980.clear();
		m_vector98c.clear();
	}
	else
	{
		_STL::list<PlayingAudioRef> saved;
		for ( _STL::list<PlayingAudioRef>::iterator it = m_list9d0.begin(); it != m_list9d0.end(); ++it )
		{
			PlayingAudio *playing = it->m_ptr;
			if ( playing && playing->m_event.m_ptr
				&& ( playing->m_event->m_08->m_84 == 0 || playing->m_event->m_08->m_84 == 1 )
				&& ( playing->m_event->m_28 != 2 || m_b70 )
				&& !playing->m_34 && !playing->m_event->m_49 )
				saved.push_back( *it );
		}
		Int count = saved.size();
		xfer->xferInt( &count );
		for ( _STL::list<PlayingAudioRef>::iterator it2 = saved.begin(); it2 != saved.end(); ++it2 )
			rva006AEF20( xfer, &*it2, &version );
		for ( i = 0; i < 3; ++i )
		{
			if ( i == 2 && version.m_currentVersion >= 3 && !m_b70 )
				continue;
			for ( Int j = 0; j < 2; ++j )
			{
				_STL::deque<PlayingAudioRef> &queue = m_queues[i * 2 + j];
				Int size = queue.size();
				xfer->xferInt( &size );
				for ( _STL::deque<PlayingAudioRef>::iterator it3 = queue.begin(); it3 != queue.end(); ++it3 )
				{
					PlayingAudioRef handle = *it3;
					rva006AEF20( xfer, &handle, &version );
				}
			}
		}
	}
	xferUnicodeStringVector( xfer, &m_vector980 );
	xferAsciiStringVector( xfer, &m_vector98c );
}

extern "C" __declspec(dllimport) void *__stdcall AIL_open_stream( void *driver, const char *filename, int stream );
extern "C" __declspec(dllimport) void __stdcall AIL_stream_ms_position( void *stream, Int *total, Int *current );
extern "C" __declspec(dllimport) Int __stdcall AIL_stream_loop_count( void *stream );

void MilesAudioManager::rva006AEF20( Xfer *xfer, PlayingAudioRef *audio, XferVersion *version )
{
	if ( xfer->isLoading() )
	{
		*audio = allocatePlayingAudio();
		(*audio)->m_event = new Rva006A1790Event( Rva01336E50EmptyString, 0 );
	}
	(*audio)->m_event->rva000B2B50( xfer );
	xfer->xferBool( &(*audio)->m_39 );
	if ( xfer->isLoading() )
	{
		slot0AC( (*audio)->m_event.m_ptr );
		((Rva006AD590Owner *)this)->bfmeAdjustPriorityAndVolume( (*audio)->m_event.m_ptr );
		Real position;
		Int loops;
		UnsignedInt handle;
		xfer->xferReal( &position );
		xfer->xferInt( &loops );
		xfer->xferUnsignedInt( &handle );
		PlayingAudio *playing = audio->m_ptr;
		if ( !playing->m_event->m_08 )
		{
			audio->clear();
			return;
		}
		if ( playing->m_event->m_08->m_84 == 0 && playing->m_event->m_68 != -1 && loops > 0 )
			playing->m_event->m_68 = loops;
		(*audio)->m_3c = true;
		UnsignedInt id = m_084++;
		Rva006A4630Value value;
		value.m_handle = id;
		_STL::pair<_STL::map<UnsignedInt, Rva006A4630Value>::iterator, bool> result =
			m_mapaf4.insert( _STL::pair<const UnsignedInt, Rva006A4630Value>( handle, value ) );
		if ( !result.second )
		{
			id = result.first->second.m_handle;
			for ( RequestList006A6B40::iterator it = m_requests.begin(); it != m_requests.end(); )
			{
				AudioRequest006A6B40 *request = *it;
				if ( request->event04 && ((AudioEventRTS *)request->event04)->m_0c == id )
				{
					it = m_requests.erase( it );
					delete (BfmeHostESG *)request;
				}
				else
					++it;
			}
			RequestTable006A6B40::iterator found = m_requestTable.findHandle( id );
			if ( found != m_requestTable.end() )
			{
				AudioRequest006A6B40 *request = *found;
				m_requestTable.erase( found );
				delete (BfmeHostESG *)request;
			}
		}
		(*audio)->m_event->setPlayingHandle( id );
		(*audio)->m_event->rva000B3C60();
		(*audio)->m_event->bfmeGenerateFilename();
		AsciiString filename = (*audio)->m_event->getFilename();
		(*audio)->m_milesHandle = AIL_open_stream( m_digitalHandle960, filename.str(), 0 );
		(*audio)->m_type = 3;
		((StartAudioStream006AE2C0 *)this)->start( *(const Ref006AE2C0 *)audio, position );
	}
	else
	{
		Int length;
		Int current;
		AIL_stream_ms_position( (*audio)->m_milesHandle, &length, &current );
		Real position;
		if ( length <= 0 )
			position = 0.0f;
		else
			position = (Real)current / length;
		xfer->xferReal( &position );
		Int loops = AIL_stream_loop_count( (*audio)->m_milesHandle );
		xfer->xferInt( &loops );
		UnsignedInt handle = (*audio)->m_event->m_0c;
		xfer->xferUnsignedInt( &handle );
	}
}
