// cl: /DNDEBUG /MD
// Address-derived 2D distance predicate at retail RVA 0x00214350.

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

unsigned char __stdcall withinDistance00214350(
	float distance,
	const Coord2D00214350 *a,
	const Coord2D00214350 *b )
{
	Coord2D00214350 delta( b->x, b->y );
	delta.x -= a->x;
	delta.y -= a->y;
	return delta.length() <= distance;
}
