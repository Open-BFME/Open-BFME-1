// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Retail 0x006155E0 gets or creates a LivingWorldSound in the map at +0x194.
// The constructor at 0x0061BF00 proves mapped identity and 0x34-byte size.
// Native find and operator[] preserve the iterator/temporary structure absent
// from the old opaque-method bank; this also fixes its three-register cycle.
// Index0x006150F0 is independently exact at142B and has its own ledger row.
// The overlapping naked lift was retired with parser614F50; boundary evidence
// is recorded in docs/living_world_parser_boundary.md.
// _M_find: ILT0002DB0A ->00613AE0; _M_insert: ILT00004435 ->00614BC0.
// Both take thiscall references; node key is +4 and mapped value is +8.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include "StringInline.h"
namespace rts { template<class T> struct hash { unsigned operator()(T value) const; }; }
bool operator==(const AsciiString &, const AsciiString &);
class Xfer;

struct Coord3DBase
{
	Coord3DBase() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}

	float x;
	float y;
	float z;
};

struct Region2DBase
{
	Region2DBase( const Region2DBase &that ) :
		xMin( that.xMin ),
		yMin( that.yMin ),
		xMax( that.xMax ),
		yMax( that.yMax )
	{
	}

	float xMin;
	float yMin;
	float xMax;
	float yMax;
};

extern const Region2DBase TheInvalidRegion;

struct LivingWorldSoundEvent
{
	explicit LivingWorldSoundEvent( int initial ) : value( initial ) {}

	int value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void LoadPostProcess() = 0;
	virtual const char *GetSnapshotName() = 0;
	virtual void DoXfer( Xfer &xfer ) = 0;
};

class LivingWorldSound : public Snapshot
{
public:
	LivingWorldSound( const AsciiString &name );
	virtual ~LivingWorldSound();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() { return "LivingWorldSound"; }
	virtual void DoXfer( Xfer &xfer );

private:
	AsciiString m_name;
	Coord3DBase m_position;
	LivingWorldSoundEvent m_sound;
	unsigned int m_flags;
	Region2DBase m_zoomRegion;
	int m_playState;
	bool m_shouldFade;
	bool m_isPlaying;
	bool m_hasPlayed;
};

typedef _STL::hash_map<AsciiString, LivingWorldSound *, rts::hash<AsciiString>, _STL::equal_to<AsciiString> > BfmeMapEQV;
template LivingWorldSound *&BfmeMapEQV::operator[](const AsciiString &);
// sizeof follows the independently landed 0x0061BF00 constructor layout.
typedef char LivingWorldSound_size_must_be_52[sizeof(LivingWorldSound) == 0x34 ? 1 : -1];
typedef LivingWorldSound BfmeItemEQV;

class BfmeHostEQV {
public:
 BfmeItemEQV *bfmeGetEQV_006155E0(const AsciiString &key);
 unsigned char m_bfmeHeadEQV[0x194];
 BfmeMapEQV m_bfmeMapEQV;
};
