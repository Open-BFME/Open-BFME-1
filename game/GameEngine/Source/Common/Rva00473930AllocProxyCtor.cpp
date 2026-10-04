// cl: /O2 /DNDEBUG /MD /EHs-c-

typedef unsigned int UnsignedInt;
typedef bool Bool;

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate( UnsignedInt bytes );
};
}

class Rva00473930
{
public:
	Rva00473930( int flags );

private:
	void initialize( Bool *out, int mode );
	void *m_bfmePtr;
};

// Retail routes this initializer call through the incremental-link thunk at
// 0x0000E7CD (?j_0000e7cd@@YAXXZ), not through a body of this class's own.
extern void j_0000e7cd();

// Route holder: the call site is thiscall (this in ecx, args on the stack), so
// only the member-pointer call shape matters; the class is irrelevant to codegen.
class Route00473930 {};

Rva00473930::Rva00473930( int flags )
{
	Bool ok;

	typedef void (Route00473930::*Initialize)( Bool *, int );
	union { void (*fn)(); Initialize call; } initialize = { j_0000e7cd };
	( ( ( Route00473930 * ) this )->*initialize.call )( &ok, 0 );

	m_bfmePtr = _STL::__new_alloc::allocate( 0x18 );
}
