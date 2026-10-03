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

// Retail's call at 0x005C3A6E targets the ILT entry 0x000209DC, the 5-byte
// thunk in front of the body at 0x005C33E0
// (?makeParticleSystemHandle005C33E0, .../ParticleSystemManagerCreateParticleSystem.cpp).
// That thunk symbol is the only name defined at the call target, so reference
// it under its own spelling; the hidden return pointer plus the three cdecl
// arguments keep the same call shape.
extern "C" BfmeVec3 __cdecl __identifier("?j_000209dc@@YAXXZ")(
	void *src, int id, void *extra );

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

	return __identifier("?j_000209dc@@YAXXZ")( src, ++m_id, extra );
}
