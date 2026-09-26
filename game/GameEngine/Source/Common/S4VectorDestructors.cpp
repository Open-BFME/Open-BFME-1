// cl: -GX-
// stlport
//
// Five `~vector<T>` bodies -- 95 bytes at the three narrow element widths,
// 101 where the width needs a full-width immediate --, instantiated from the VENDORED STLport
// header rather than replicated.  Each destroys every live element in place and
// then hands the whole block back through STLport's node allocator:
//
//     for ( p = m_start; p != m_finish; p += sizeof(T) ) p->~T();
//     if ( m_start ) {
//         n = ( m_end_of_storage - m_start ) / sizeof(T) * sizeof(T);
//         if ( n > 128 ) free( m_start ); else pool_free( m_start, n ); }
//
// WHAT THE BYTES SHOW.  Three dwords are read off `this` at 0, 4 and 8 -- start,
// finish and end-of-storage, STLport's `_Vector_base` layout.  The element loop
// is __thiscall (`mov ecx,esi` then a call that pops nothing) and steps by the
// element size, so the element has a NON-TRIVIAL destructor; a trivial one
// leaves no loop at all.  The `test esi,esi / je` past the deallocation is
// `_M_start != 0`, not an empty-range test -- it is re-read from `[this]` AFTER
// the loop rather than reusing the register the loop already exhausted.
//
// THE ELEMENT WIDTH IS THE AXIS, and it is written into the code three times
// over: the loop stride, a magic-multiply reciprocal, and a multiply putting
// the count back into bytes.  Retail's five are 44, 136, 528, 44 and 108 bytes.
// The round trip through the reciprocal is not redundant in the source -- it is
// `deallocate(_M_start, _M_end_of_storage - _M_start)` in STLport, an element
// COUNT that the allocator turns back into bytes.
//
// THE 128 IS STLport's __node_alloc CUTOVER, not a source constant of this
// function: above `_MAX_BYTES` the block came from `malloc` and goes back with
// one argument, at or below it the block came from the pool and goes back with
// two.  Both callees are __cdecl and each arm cleans its own push.
//
// TWO ROWS SHARE AN ELEMENT WIDTH (0x00252ED0 and 0x007746E0, both 44) but call
// DIFFERENT element destructors, so they are different instantiations and get
// different stand-in element types.  Collapsing them onto one type would have
// produced a single COMDAT claimed at two addresses.
//
// EIGHT MORE BODIES, 99 to 106 bytes, ARE THE SAME SOURCE OVER A POLYMORPHIC
// ELEMENT.  Everything outside the element loop is identical -- same three
// dwords off `this`, same reciprocal, same 128-byte cutover.  Inside it, the
// __thiscall destructor call becomes `mov eax,[esi] / push 0 / mov ecx,esi /
// call dword ptr [eax]`: an indirect call through the element's OWN first
// dword, at vtable slot ZERO, with a literal 0 argument.  That is `p->~T()` on
// a class with a VIRTUAL destructor -- the compiler routes it through the
// scalar deleting destructor and passes the "do not free" flag.  The element
// therefore carries a vptr, which is why each stand-in below is four bytes of
// vptr plus padding to the stride the loop steps by.
//
// A three-dword element difference divides by a NON-POWER-OF-TWO in every case,
// and the reciprocal sequences differ in shape rather than just in constant:
// widths 20, 36 and 92 fold the multiply-back into `lea`/`shl`, while 112, 140
// and 180 need a real `imul` and 92 and higher need `add edx,ecx` to correct
// the high half.  All of that is the compiler's, not the source's -- the source
// says `_M_end_of_storage - _M_start` and nothing more.
//
// IDENTITY IS NOT RECOVERED.  Each element type is named after the vector
// destructor that uses it, sized to the width the bytes fix, and given a
// DECLARED destructor pinned to the address its REL32 resolves to.  Nothing
// here shows what the elements are or what their destructors do.

#include <vector>

#define S4_VECTOR_DTOR( NAME, DWORDS )                                         \
	struct S4Elem##NAME                                                        \
	{                                                                          \
		int m_storage[ DWORDS ];                                               \
		~S4Elem##NAME();                                                       \
	};                                                                         \
	void s4vd##NAME( _STL::vector< S4Elem##NAME > *v )                         \
	{                                                                          \
		v->~vector();                                                          \
	}

S4_VECTOR_DTOR( 00252ED0, 11 )
S4_VECTOR_DTOR( 0039EBE0, 34 )
S4_VECTOR_DTOR( 00608D40, 132 )
S4_VECTOR_DTOR( 007746E0, 11 )
S4_VECTOR_DTOR( 0077B010, 27 )

#define S4_VECTOR_DTOR_VIRTUAL( NAME, DWORDS )                                 	struct S4Poly##NAME                                                        	{                                                                          		int m_storage[ DWORDS ];                                               		virtual ~S4Poly##NAME();                                               	};                                                                         	void s4vdv##NAME( _STL::vector< S4Poly##NAME > *v )                        	{                                                                          		v->~vector();                                                          	}

S4_VECTOR_DTOR_VIRTUAL( 000BC2E0, 27 )
S4_VECTOR_DTOR_VIRTUAL( 00136170, 22 )
S4_VECTOR_DTOR_VIRTUAL( 00197190, 34 )
S4_VECTOR_DTOR_VIRTUAL( 00362990, 44 )
S4_VECTOR_DTOR_VIRTUAL( 003AFCA0, 8 )
S4_VECTOR_DTOR_VIRTUAL( 003AFD20, 4 )
S4_VECTOR_DTOR_VIRTUAL( 003AFE90, 4 )
S4_VECTOR_DTOR_VIRTUAL( 0061A2D0, 8 )
