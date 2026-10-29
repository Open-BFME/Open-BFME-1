// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: retail 0x003A4FD0 (220 bytes, ret 4). A living-world state
// update: unless its 0x003A4E30 check (BfmeHostCB::bfmePopCB on the same
// object) consumes the call, and when both flags at +0x1D/+0x1E are set, it
// looks up the region under the point (x, y, 0) through the campaign's region
// manager (0x012F1028 +0x28), and when 0x003CAE00 accepts that region it
// hands the region (+4), this object's name (0x003A4390) and the argument to
// the manager's 0x003C9CB0, then tells the campaign (0x003BE020). The flag at
// +0x1C is cleared on every path. Class and method names are address-derived.
//
// Shape note measured against retail: y is read into a local before the
// manager is loaded (retail's fld/fstp of y precedes the integer copy of x).
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class LivingWorldRegion;

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8160( Coord3D *point );
	bool rva003CAE00( LivingWorldRegion *region );
	void rva003C9CB0( void *a, void *b, void *c, void *d );
};

class Glo012F1028Type
{
public:
	void rva003BE020( LivingWorldRegion *region );

	char m_unmodelled00[ 0x28 ];
	LivingWorldRegionManager *m_regionManager;
};
// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )

class BfmeHostCB
{
public:
	char bfmePopCB();
};

// 0x003A4390: return by value the string member at +4; matched as
// ?getName@Rva003A4390Owner@@QAE?AVAsciiString@@XZ (Rva003A4390NameGetter.cpp).
class Rva003A4390Owner
{
public:
	AsciiString getName();
};

class Rva003A4FD0State
{
public:
	void update( void *arg );

private:
	char m_unmodelled00[ 0x0C ];
	float m_x;
	float m_y;
	char m_unmodelled14[ 8 ];
	unsigned char m_rva1C;
	unsigned char m_rva1D;
	unsigned char m_rva1E;
};

void Rva003A4FD0State::update( void *arg )
{
	if( ( (BfmeHostCB *)this )->bfmePopCB() )
		return;
	if( m_rva1D && m_rva1E )
	{
		float y = m_y;
		LivingWorldRegionManager *manager = Glo012F1028->m_regionManager;
		Coord3D point;
		point.y = y;
		point.x = m_x;
		point.z = 0;
		LivingWorldRegion *region = manager->rva003C8160( &point );
		if( region && manager->rva003CAE00( region ) )
		{
			AsciiString name = ( (Rva003A4390Owner *)this )->getName();
			manager->rva003C9CB0( (char *)region + 4, &name, 0, arg );
			Glo012F1028->rva003BE020( region );
		}
	}
	m_rva1C = 0;
}

// Retail 0x003BE020 (239 bytes, ret 4): the campaign half of the update above.
// It asks the region manager (0x003C9470, through ILT 0x00033EBA) for the
// region's map point, reads the living-world camera position (vslot +0x44 of
// 0x012F7048), and times a camera move to the point (x, y, 0) from the
// distance: 0.005 per unit, clamped to [1, 5], times 30 and rounded. The move
// is vslot +0x60 (point, the float vslot +0x3C returns, rounded time). Names
// stay address-derived.
class Rva003C9470Key;
struct Rva003C9470Output
{
	float m_x;
	float m_y;
};
class Rva003C9470Owner
{
public:
	bool fallback( Rva003C9470Key *key, Rva003C9470Output *output );
};

#define V(n) virtual void slot##n();
class Rva003BE020Camera
{
public:
	V(00) V(04) V(08) V(0C) V(10) V(14) V(18) V(1C)
	V(20) V(24) V(28) V(2C) V(30) V(34) V(38)
	virtual float slot3C();						// +0x3C
	V(40)
	virtual void getPosition( Coord3D *pos );
	V(48) V(4C) V(50) V(54) V(58) V(5C)
	virtual void slot60( Coord3D *pos, float value, int frames );
};
#undef V

class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;

template <class T> inline const T &min003BE020( const T &a, const T &b ) { return a < b ? a : b; }

extern "C" double __cdecl sqrt( double );
#pragma intrinsic( sqrt )

void Glo012F1028Type::rva003BE020( LivingWorldRegion *region )
{
	Rva003C9470Output target;
	( (Rva003C9470Owner *)m_regionManager )->fallback( (Rva003C9470Key *)( (char *)region + 4 ), &target );
	Coord3D pos;
	( (Rva003BE020Camera *)g_rva012F7048LivingWorld )->getPosition( &pos );
	Coord3D dest;
	dest.x = target.m_x;
	dest.y = target.m_y;
	dest.z = 0;
	pos.x -= dest.x;
	pos.y -= dest.y;
	pos.z -= dest.z;
	float maxSeconds = 5.0f;
	{
		float seconds = (float)sqrt( pos.x * pos.x + pos.y * pos.y + pos.z * pos.z ) * 0.005f;
		float clamped = min003BE020( seconds, maxSeconds );
		if( clamped < 1.0f )
			clamped = 1.0f;
		( (Rva003BE020Camera *)g_rva012F7048LivingWorld )->slot60( &dest,
			( (Rva003BE020Camera *)g_rva012F7048LivingWorld )->slot3C(), (int)( clamped * 30.0f ) );
	}
}
