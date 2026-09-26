// cl: /DNDEBUG /MD
// Fourteen 65-byte __thiscall block releases, one shape, all fourteen
// byte-identical except for their two position-dependent REL32 displacements.
// Retail:
//
//     if (m_start)
//         __node_alloc<true,0>::deallocate(m_start, (m_cap - m_start) * 20);
//
// with deallocate inlined: `n > 128 ? operator delete(p) : _M_deallocate(p,n)`.
//
// WHAT THE BYTES SHOW.  Three pointers at 0, 4 and 8; only 0 and 8 are read,
// and the difference between them is divided by 20 (imul 0x66666667 / sar 3
// plus the shr-31/add sign fixup, so a SIGNED ptrdiff_t) and multiplied back by
// 20 (`lea eax,[eax+eax*4]` then `shl eax,2`).  Dividing and re-multiplying by
// the same constant is what a POINTER SUBTRACTION scaled back to bytes looks
// like -- the element type is 20 bytes wide and the capacity is a pointer, not
// a stored count.  The unread pointer at offset 4 is the middle of the usual
// begin/end/capacity triple.
//
// The two callees are already-named ledger rows and need no pin: the `n > 128`
// arm is `??3@YAXPAX@Z` (one pushed dword) and the other is
// `_STL::__node_alloc<1,0>::_M_deallocate` (two pushed dwords).  128 is
// STLport's _MAX_BYTES, and the split is its allocator's own `deallocate`
// inlined into the caller, which is why this file spells it that way rather
// than as two bare function pointers.
//
// ONE AXIS, AND IT IS EMPTY: every member has element size 20 and the same two
// callees, so the fourteen bodies differ only in where they sit.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#include <new>

namespace _STL
{

template <bool __threads, int __inst>
class __node_alloc
{
	static void _M_deallocate( void *p, unsigned int n );

public:
	static void deallocate( void *p, unsigned int n )
	{
		if ( n > 128 )
			::operator delete( p );
		else
			_M_deallocate( p, n );
	}
};

}

struct BigBlockElem
{
	char m_bytes[ 20 ];
};

#define BFME_BLOCK_RELEASE( NAME )                                        \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void clear();                                                     \
		BigBlockElem *m_start;                                            \
		BigBlockElem *m_finish;                                           \
		BigBlockElem *m_cap;                                              \
	};                                                                    \
	void NAME::clear()                                                    \
	{                                                                     \
		if ( m_start )                                                    \
			_STL::__node_alloc< true, 0 >::deallocate(                    \
				m_start,                                                  \
				( m_cap - m_start ) * sizeof( BigBlockElem ) );           \
	}

BFME_BLOCK_RELEASE( Rva0013B050 )
BFME_BLOCK_RELEASE( Rva0013B0B0 )
BFME_BLOCK_RELEASE( Rva0013F700 )
BFME_BLOCK_RELEASE( Rva002E4E40 )
BFME_BLOCK_RELEASE( Rva00354530 )
BFME_BLOCK_RELEASE( Rva003545C0 )
BFME_BLOCK_RELEASE( Rva003A45A0 )
BFME_BLOCK_RELEASE( Rva003A7B90 )
BFME_BLOCK_RELEASE( Rva003A7E40 )
BFME_BLOCK_RELEASE( Rva003B8AA0 )
BFME_BLOCK_RELEASE( Rva00638F30 )
BFME_BLOCK_RELEASE( Rva00760EF0 )
BFME_BLOCK_RELEASE( Rva00638530 )
BFME_BLOCK_RELEASE( Rva00638F90 )
