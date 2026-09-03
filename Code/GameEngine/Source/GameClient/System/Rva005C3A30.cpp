// cl: /DNDEBUG /MD /EHsc
// Struct-returning helper: null argument yields (0,0,0); otherwise increment
// the id at +0x7C and call a 4-arg cdecl filler.

struct BfmeVec3
{
	int x;
	int y;
	int z;
	BfmeVec3( int a, int b, int c ) : x( a ), y( b ), z( c ) {}
};

BfmeVec3 fillVec005C3A30( void *src, int id, void *extra );

class Rva005C3A30
{
public:
	BfmeVec3 make( void *src, void *extra );

	unsigned char m_pad[ 0x7C ];
	int m_id;
};

BfmeVec3 Rva005C3A30::make( void *src, void *extra )
{
	volatile int unused = 0;
	if ( src == 0 )
		return BfmeVec3( 0, 0, 0 );

	return fillVec005C3A30( src, ++m_id, extra );
}
