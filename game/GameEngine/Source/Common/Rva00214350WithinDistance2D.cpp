// cl: /DNDEBUG /MD /Igame/Libraries/Include
// Address-derived 2D distance predicate at retail RVA 0x00214350.

#include "Lib/Coord3D.h"

extern "C" double sqrt( double value );
#pragma intrinsic( sqrt )

static float square00214350( float value ) { return value * value; }
static float squareVolatile00214350( const volatile float &value ) { return value * value; }

struct Coord2D00214350
{
	Coord2D00214350( float initialX, float initialY ) : x( initialX ), y( initialY ) {}
	float length() const { return (float)sqrt( squareVolatile00214350( x ) + square00214350( y ) ); }
	float x;
	float y;
	float unused;
};

// Retail's only caller, PorcupineDamageHelper::apply (0x002144D0), loads its
// own `this` into ECX before the call (mov ecx,edi), so this is a member of
// the helper; the body never reads ECX and pops its 12 argument bytes.
class PorcupineDamageHelper
{
public:
	unsigned char withinDistance00214350( float distance, const Coord3D *a, const Coord3D *b );
};

unsigned char PorcupineDamageHelper::withinDistance00214350(
	float distance,
	const Coord3D *a,
	const Coord3D *b )
{
	Coord2D00214350 delta( b->x, b->y );
	delta.x -= a->x;
	delta.y -= a->y;
	return delta.length() <= distance;
}
