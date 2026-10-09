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

class Rva00473900
{
public:
	Rva00473900( int flags );

private:
	void initialize( Bool *out, int mode );
	void *m_bfmePtr;
};

extern void j_0000cdb0();

Rva00473900::Rva00473900( int flags )
{
	Bool ok;

	typedef void (Rva00473900::*Init)( Bool *, int );
	union { void (*fn)(); Init call; } init = { j_0000cdb0 };
	( this->*init.call )( &ok, 0 );

	m_bfmePtr = _STL::vectorSmallAllocate( 0x18 );
}
