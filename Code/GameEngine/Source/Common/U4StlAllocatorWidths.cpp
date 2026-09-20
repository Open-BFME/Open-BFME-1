// cl: -GX-
// stlport
//
// Two ADJACENT PAIRS of STLport allocator entry points from the
// 0x005E97B0..0x0060D680 slice: `allocator<T>::allocate(n, hint)` and
// `allocator<T>::deallocate(p, n)` at element widths 0x70 and 0x210.
//
//     allocate:   mov eax,[esp+4] / test eax,eax / je RET0
//                 imul eax,eax,<WIDTH> / cmp eax,0x80 / push eax
//                 jbe SMALL / call <malloc>  / add esp,4 / ret 8
//         SMALL:  call <pool_alloc> / add esp,4 / ret 8
//         RET0:   xor eax,eax / ret 8
//
//     deallocate: mov ecx,[esp+4] / test ecx,ecx / je RET
//                 mov eax,[esp+8] / imul eax,eax,<WIDTH> / cmp eax,0x80
//                 jbe SMALL / push ecx / call <free> / add esp,4 / ret 8
//         SMALL:  push eax / push ecx / call <pool_free> / add esp,8 / ret 8
//
// WHAT THE BYTES SHOW.  Both are `ret 8` with ecx never read, which is the
// __thiscall an EMPTY const member function of a class template gets; the two
// stack dwords are the two declared parameters and the second one of
// `allocate` is never touched, which is exactly STLport 4.5.3's
//
//     _Tp* allocate(size_type __n, const void* = 0) const
//     { return __n != 0 ? ... __sgi_alloc::allocate(__n * sizeof(value_type)) : 0; }
//     void deallocate(pointer __p, size_type __n) const
//     { if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type)); }
//
// in vendor/stlport/stl/_alloc.h.  The 0x80 cutover and the two-armed callee
// split are NOT source constants of these functions -- they are __sgi_alloc's
// own body inlined into both: at or below `_MAX_BYTES` the block comes from and
// goes back to the node pool with a SIZE argument, above it from and to malloc
// with one argument.  Nothing is written here to produce that; it comes out of
// the vendored header, which is why the header is used rather than replicated.
//
// THE ONLY AXIS IS sizeof(value_type), and it is the sole immediate in each
// body.  0x70 fits an imm8 (`6b c0 70`) and 0x210 does not (`69 c0 10 02 00
// 00`), which is the whole of the 46-vs-49 and 47-vs-50 length difference.
//
// WHY THESE ARE NOT FOLDED ONTO AN EXISTING vector<> TU.  Both pairs sit
// ADJACENT in the image -- 0x00604FE0/0x00605040 and 0x00607F50/0x00607F90 --
// and a translation unit that only DESTROYS a vector emits `deallocate` and
// never `allocate`, so an adjacent pair can only come from a TU that
// instantiates the container whole.  Code/GameEngine/Source/Common/
// S4VectorDestructors.cpp and R3VectorOwnerDestructors.cpp each carry a
// destructor over a 0x210-wide element and their `deallocate` bodies are
// byte-identical to 0x00607F90, but neither emits an `allocate` for it; folding
// the pair onto either would claim an ICF twin for an owner the bytes do not
// pick out.  A whole instantiation, as here, produces both members and puts
// them in this order.
//
// IDENTITY IS NOT RECOVERED.  `char m_body[WIDTH]` carries a size and nothing
// else, and the element names are derived from the addresses of the rows they
// serve.

#include <vector>

#define U4_ALLOC_WIDTH( NAME, SZ )                                            \
	struct NAME                                                               \
	{                                                                         \
		char m_body[ SZ ];                                                    \
		NAME();                                                               \
		NAME( const NAME & );                                                 \
		~NAME();                                                              \
		NAME &operator=( const NAME & );                                      \
	};                                                                        \
	template class _STL::vector<NAME >;

U4_ALLOC_WIDTH( U4Elem00605040, 0x70 )
U4_ALLOC_WIDTH( U4Elem00607F50, 0x210 )
U4_ALLOC_WIDTH( Rva0036C980Elem, 4 )
