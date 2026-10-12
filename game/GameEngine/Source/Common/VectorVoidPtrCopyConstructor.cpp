// ??0?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV01@@Z
// Retail 0x0082EB30 (200 bytes): STLport's __vector__<_Tp,_Alloc> copy
// constructor for void *.  The gen-dump row ?d_0082eb30@@YAXXZ carried these
// same 200 bytes, so this is a rename to the real identity and not a new match.
//
// The element is void *, not int.  The two are byte-identical, but the three
// out-of-line callees sit on the void * instantiation's incremental-link slots:
// tools/ilt_oracle.py confirms get_allocator at 0x00009C28, the
// _Vector_base(size_t, const allocator &) constructor at 0x00026085 and
// __copy_trivial at 0x00018179, and contradicts the int spelling at all three.
//
// Retail linked this TU's private copies of the first two, so their source
// spellings are scoped to the observed RVAs: the plain void * _Vector_base
// spelling already carries a pin for the 0x001F9330 body that
// LargeGroupAudioKeyMap's TU encodes, and adding a second address to that name
// would make one name mean two different bodies.  __copy_trivial keeps its real
// spelling and is pinned beside the 0x000666E0 body the ledger already has.
//
// cl: /Od /Ob2 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _Vector_base Rva00026085VectorBase
#define get_allocator bfmeGetAllocator00009C28
#pragma inline_depth(255)
#pragma inline_recursion(on)
namespace _STL {
__declspec(noinline) void *__copy_trivial(const void *, const void *, void *) throw();
}
#include <stl/_algobase.h>
#define inline __forceinline
#include <stl/_uninitialized.h>
#undef inline
#include <vector>
#undef get_allocator
#undef _Vector_base
template _STL::vector<void *, _STL::allocator<void *> >::vector(const _STL::vector<void *, _STL::allocator<void *> > &);
