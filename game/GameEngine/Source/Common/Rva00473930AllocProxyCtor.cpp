// cl: /O2 /DNDEBUG /MD /EHs-c-

typedef unsigned int UnsignedInt;
typedef bool Bool;

namespace _STL
{
// Retail 0x0082E540 is the matched node pool refill/mutex body.
static __forceinline void *vectorSmallAllocate(unsigned int bytes);
template <bool Threads, int Instance>
class __node_alloc
{
	static void *__cdecl _M_allocate(unsigned int bytes);
	friend void *vectorSmallAllocate(unsigned int bytes);
};
static __forceinline void *vectorSmallAllocate(unsigned int bytes)
{
	return __node_alloc<true, 0>::_M_allocate(bytes);
}
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

	m_bfmePtr = _STL::vectorSmallAllocate( 0x18 );
}
