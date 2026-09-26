// cl: /EHsc
// stlport
//
// Six 150-byte STLport vector<T> destructors whose element type is
// POLYMORPHIC: the destroy loop dispatches through the element's own vtable.
//
//     for (p = _M_start; p != _M_finish; p += <SIZE>)
//         mov eax,[p] / push 0 / mov ecx,p / call [eax]
//     n = _M_end_of_storage - _M_start   (rounded to a whole element count)
//     n > 0x80 ? free(_M_start) : __node_alloc::deallocate(_M_start, n)
//
// WHAT THE BYTES SHOW.  `push 0 / call [eax]` through vtable SLOT 0 is MSVC's
// scalar deleting destructor with the free flag CLEAR -- destroy in place, do
// not release.  Going through the vtable at all is the tell: `p->~T()` on a
// type whose destructor is NOT virtual compiles to a direct call, so the
// element type has a VIRTUAL DESTRUCTOR and it owns slot 0.  The `sar`/`shl`
// pair around the byte count is the compiler turning a pointer difference into
// an element count and back; it only appears because the element size is a
// power of two, which is why these six group together and the odd-sized
// vectors land in their own families.
//
// The two-arm deallocate (free above 0x80 bytes, node allocator at or below)
// is STLport 4.5.3's own `_M_deallocate`, reproduced by compiling the VENDORED
// header rather than by hand: the source below is one explicit instantiation
// per element type and nothing else.
//
// THE VARYING AXIS IS ONE FIELD: sizeof(T), read off the `add esi,<SIZE>` and
// confirmed by the matching shift count.  Sizes are 8, 0x20, 0x20, 0x10, 0x10
// and 0x20.  Six rows over three sizes means the element TYPES still differ --
// two instantiations that produced identical bytes would have been folded by
// the linker into one address, and these sit at six addresses.
//
// IDENTITY IS NOT RECOVERED.  The element names are derived from the vector
// destructor's own address; `char m_pad[SIZE-4]` carries the size past the
// vptr and is not a claim about the element's fields.  What the bytes cannot
// decide: the element's real type, how many virtuals it has, and whether these
// six vectors are related.

#include <vector>

#define Q4_POLY_ELEM( T, SIZE )                                           	struct T                                                              	{                                                                     		virtual ~T();                                                     		char m_pad[ SIZE - 4 ];                                           		T();                                                              		T( const T & );                                                   		T &operator=( const T & );                                        	};                                                                    	template class _STL::vector<T >;

Q4_POLY_ELEM( Gen003A99D0, 0x8 )
Q4_POLY_ELEM( Gen003A9C30, 0x20 )
Q4_POLY_ELEM( Gen003AA010, 0x20 )
Q4_POLY_ELEM( Gen003AA300, 0x10 )
Q4_POLY_ELEM( Gen003AA3C0, 0x10 )
Q4_POLY_ELEM( Gen003B47F0, 0x20 )
