// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// RVA 006B0E00: MilesAudioManager::MilesAudioManager (1550 B; RET at +0x60D, INT3 after).
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
// LAYOUT. BFME's audio manager shares almost nothing with Zero Hour's; members
// are spelled from this body alone and keep their offsets as names except where
// the body proves the role. The two bases are wrapped in the novtable
// intermediate class whose out-of-line ctor/dtor are the matched 0x00694E00 /
// 0x00694E30: retail's unwind state 0 calls that destructor, which is why the
// Snapshot base has no unwind state of its own here (unlike Eva). Every
// container is real STLport so that its constructor inlines as retail's does;
// each out-of-line helper binds by its instantiation's mangled name.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
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

class Snapshot
{
public:
	virtual ~Snapshot( void ) {}
	virtual void crc( void ) = 0;
	virtual void xfer( void ) = 0;
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
	virtual ~Rva00694E00( void );
};

class AudioSettings { public: AudioSettings( void ); char m_body[0x138]; };
class MiscAudio { public: MiscAudio( void ); char m_body[0xe00]; };
class Rva00694710AudioWorker { public: Rva00694710AudioWorker( void *mutex ); char m_body[0x4c]; };

// Hash map payloads and set key: the address-derived spellings the matched
// out-of-line STLport bodies already carry.
struct Gen_t_006ac680_p12cd { int a[3]; };
struct Gen_t_006ac620_p12cd { int a[3]; };
struct Gen_t_006ac6e0_p12cd { int a[3]; };
struct Gen_t_006ac7d0_p12cd { int a[3]; };
struct Gen_t_006ac830_p12cd { int a[3]; };
struct Gen_t_006ac890_p12cd { int a[3]; };
struct Gen_t_00076a90_k4 { int k; bool operator<( const Gen_t_00076a90_k4 &o ) const { return k < o.k; } };
struct Gen00026F35 { int a[3]; };
struct Rva006AADB0Element { int a[2]; };

// Array element types: out-of-line constructors and destructors passed to the
// EH vector constructor iterator.
class Rva006ABC60
{
public:
	Rva006ABC60( void );
	~Rva006ABC60( void );
	void setIndex( Int index ) { m_index00 = index; }

private:
	Int m_index00;			// the owner stores the element's array index here
	char m_body[0x1c0];
};
class Rva0069CEE0 { public: Rva0069CEE0( void ); ~Rva0069CEE0( void ); char m_body[0xc]; };
class Rva00478100 { public: Rva00478100( void ); ~Rva00478100( void ); char m_body[0xc]; };
class Rva006967A0 { public: Rva006967A0( void ); ~Rva006967A0( void ); char m_body[0x4]; };

class MilesAudioManager : public Rva00694E00
{
public:
	MilesAudioManager( void );
	virtual ~MilesAudioManager( void );
	virtual void init( void );
	virtual void crc( void );
	virtual void xfer( void );
	virtual void loadPostProcess( void );

private:
	AudioSettings *m_audioSettings;						// +0x00c
	MiscAudio *m_miscAudio;								// +0x010
	UnsignedInt m_014, m_018, m_01c, m_020;				// +0x014
	Real m_024;											// +0x024
	UnsignedInt m_028, m_02c, m_030, m_034, m_038, m_03c, m_040;
	Real m_044;											// +0x044
	UnsignedInt m_048;									// +0x048
	_STL::list<void *> m_list04c;						// +0x04c
	_STL::hash_map<int, Gen_t_006ac680_p12cd> m_hash050;	// +0x050
	_STL::set<Gen_t_00076a90_k4> m_set064;				// +0x064
	_STL::hash_map<int, Gen_t_006ac620_p12cd> m_hash070;	// +0x070
	Int m_084;											// +0x084
	_STL::vector<int> m_vector088;						// +0x088
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
	UnsignedInt m_960, m_964, m_968;					// +0x960
	_STL::hash_map<int, Gen_t_006ac6e0_p12cd> m_hash96c;	// +0x96c
	_STL::vector<int> m_vector980;						// +0x980
	_STL::vector<int> m_vector98c;						// +0x98c
	Rva00478100 m_998[3];								// +0x998
	_STL::list<void *> m_list9bc;						// +0x9bc
	_STL::list<void *> m_list9c0;
	_STL::list<void *> m_list9c4;
	_STL::list<void *> m_list9c8;
	_STL::list<void *> m_list9cc;
	_STL::list<void *> m_list9d0;
	_STL::queue<Rva006AADB0Element> m_queues[6];			// +0x9d4
	UnsignedInt m_ac4[3];								// +0xac4
	Rva006967A0 m_ad0[3];								// +0xad0
	_STL::vector<int> m_vectoradc;						// +0xadc
	_STL::vector<int> m_vectorae8;						// +0xae8
	_STL::map<int, int> m_mapaf4;						// +0xaf4
	Rva00694710AudioWorker *m_worker;					// +0xb00
	_STL::list<void *> m_listb04;						// +0xb04
	_STL::hash_map<int, Gen_t_006ac7d0_p12cd> m_hashb08;	// +0xb08
	_STL::hash_map<int, Gen_t_006ac830_p12cd> m_hashb1c;	// +0xb1c
	_STL::hash_map<int, Gen_t_006ac890_p12cd> m_hashb30;	// +0xb30
	UnsignedInt m_b44, m_b48;							// +0xb44
	Int m_b4c;											// +0xb4c
	UnsignedInt m_b50, m_b54, m_b58;					// +0xb50
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
	  m_954( 0 ), m_958( -1 ), m_mutex( 0 ), m_960( 0 ), m_964( 0 ), m_968( 0 ),
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
