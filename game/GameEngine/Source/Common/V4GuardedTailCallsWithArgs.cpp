// cl: /Igame/Libraries/Source/WWVegas/WWLib

// Two fifteen-byte __thiscall members that forward their whole argument list to
// a member of a pointer held at +0x28, and do nothing when it is null:
//
//     mov ecx,[ecx+0x28] / test ecx,ecx / jz .out / jmp <REL32> / .out: ret N
//
// WHAT THE BYTES SHOW.  This is the guarded tail-jump shape, but unlike the
// niladic family in R1GuardedPointerTailCalls.cpp these two END IN `ret N`, and
// that fixes their arity exactly: 0x20 bytes of stack arguments for the first
// and 4 for the second.  Nothing re-pushes anything before the jump, so the
// callee reads the SAME argument slots this function was called with and pops
// the same count -- the two signatures are identical, argument for argument.
//
// The loaded dword becomes ecx and is jumped through, so it is a stored pointer
// and the callee is a __thiscall member of what it points at.  Two distinct
// callees, so two distinct pointee types.
//
// The argument types are NOT recoverable: the bytes never touch the arguments,
// only their total size, so eight dwords and one dword are spelled as plain
// ints purely to reproduce the counts.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

#include "ascii_string.h"

class Rva0076F980Mid;

// Declared by the same mangled names their defining TUs use, so the guarded
// calls below link.  This TU only needs each class as a pointer type; the
// layouts live with the definitions (Gen_003C6340 in S3GuardedDelegatesBulk.cpp,
// LivingWorldRegionManager in LivingWorldRegionManager_Rva003C8C60.cpp).
class LivingWorldRegionManager
{
public:
	void rva003C8C60( const AsciiString &regionName, const Rva0076F980Mid &names, unsigned int spawnNumber, unsigned int startNumber, unsigned int replaceDelay, unsigned char oneShot, unsigned char reclaimOrphans, unsigned char requireSpawner );
};

class Gen_003C6340
{
public:
	void bfmeForward( void *a0 );
};

class Rva003BCA50
{
public:
	void forward( int a, int b, int c, int d, int e, int f, int g, int h );
	char                      m_pad00[ 0x28 ];
	LivingWorldRegionManager *m_regionManager;
};
void Rva003BCA50::forward( int a, int b, int c, int d, int e, int f, int g, int h )
{
	if( m_regionManager )
		m_regionManager->rva003C8C60( *reinterpret_cast<const AsciiString *>( a ), *reinterpret_cast<const Rva0076F980Mid *>( b ), (unsigned int)c, (unsigned int)d, (unsigned int)e, (unsigned char)f, (unsigned char)g, (unsigned char)h );
}

class Rva003BCA70
{
public:
	void forward( int a );
	char          m_pad00[ 0x28 ];
	Gen_003C6340 *m_regionManager;
};
void Rva003BCA70::forward( int a )
{
	if( m_regionManager )
		m_regionManager->bfmeForward( reinterpret_cast<void *>( a ) );
}
