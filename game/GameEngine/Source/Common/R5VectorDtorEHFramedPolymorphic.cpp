// cl: /EHsc
// stlport
//
// Open-BFME5: fourteen more STLport vector<T> destructors over a POLYMORPHIC
// element -- the shape Q4VectorDtorPolymorphic.cpp already lands six of, at
// the element sizes that are NOT powers of two.
//
// The destroy loop dispatches through the element's own vtable:
//
//     mov eax,[p] / push 0 / mov ecx,p / call [eax]
//
// which is MSVC's scalar deleting destructor with the free flag CLEAR --
// destroy in place, do not release.  Going through the vtable at all is the
// tell: `p->~T()` on a type whose destructor is not virtual compiles to a
// direct call, so the element type has a VIRTUAL DESTRUCTOR owning slot 0.
//
// What separates these six from Q4's is only the element size.  A power of
// two lets the compiler turn the pointer difference into an element count
// with a `sar`/`shl` pair; 92, 140, 180, 88, 220 and 112 do not, so each of
// these carries a magic multiply or a plain shift instead.  Same source, and
// the divide block
// is derived rather than written.
//
// IDENTITY IS NOT RECOVERED.  Element names come from the vector destructor's
// own address, and `char m_pad[SIZE-4]` carries the size past the vptr; it is
// not a claim about the element's fields.

#include <vector>

#define R5_POLY_ELEM( T, SIZE )                                               \
	struct T                                                                  \
	{                                                                         \
		virtual ~T();                                                         \
		char m_pad[ SIZE - 4 ];                                               \
		T();                                                                  \
		T( const T & );                                                       \
		T &operator=( const T & );                                            \
	};                                                                        \
	template class _STL::vector<T >;

R5_POLY_ELEM( Gen00141A00, 0x5C )		// 168B at 0x00141A00
R5_POLY_ELEM( Gen00196F30, 0x8C )		// 174B at 0x00196F30
R5_POLY_ELEM( Gen003627D0, 0xB4 )		// 174B at 0x003627D0
R5_POLY_ELEM( Gen00363750, 0x58 )		// 166B at 0x00363750
R5_POLY_ELEM( Gen003A9860, 0xDC )		// 172B at 0x003A9860
R5_POLY_ELEM( Gen0049B890, 0x70 )		// 168B at 0x0049B890
R5_POLY_ELEM( Gen003A9A90, 0x28 )		// 167B at 0x003A9A90
R5_POLY_ELEM( Gen003A9B60, 0x30 )		// 167B at 0x003A9B60
R5_POLY_ELEM( Gen003A9CF0, 0xC )		// 166B at 0x003A9CF0
R5_POLY_ELEM( Gen003A9DC0, 0x24 )		// 167B at 0x003A9DC0
R5_POLY_ELEM( Gen003A9E90, 0x14 )		// 167B at 0x003A9E90
R5_POLY_ELEM( Gen003AA0D0, 0x18 )		// 167B at 0x003AA0D0
R5_POLY_ELEM( Gen003AA1A0, 0x14 )		// 167B at 0x003AA1A0
R5_POLY_ELEM( Gen0061A200, 0x24 )		// 167B at 0x0061A200
