// ?d_000d64a0@@YAXXZ
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport

// Open-BFME: hash_map<int, Gen_t_XXX_p12cd>::hashtable::erase(const_iterator),
// the const-iterator overload of the STLport hashtable erase-one path over the
// synthetic "hash_int_p12cd" payload grid (Code/gen_small/tgrid_127.cpp,
// tgrid_128.cpp, tgrid_130.cpp). Those files explicit-instantiate the whole
// hash_map<> class, which only reaches the NON-const iterator overload through
// hash_map::erase(iterator); the const overload below is a distinct retail
// body (identity confirmed in reverse/reloc_names.csv) that needs its own
// explicit instantiation. Struct layout mirrors the tgrid grid exactly (12
// bytes of payload, non-trivial ctor/dtor) so the mangled names line up.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;
typedef bool Bool;

// 0x000D64A0
struct Gen_t_000d81e0_p12cd { int a[3]; Gen_t_000d81e0_p12cd(); Gen_t_000d81e0_p12cd(const Gen_t_000d81e0_p12cd&); ~Gen_t_000d81e0_p12cd(); Gen_t_000d81e0_p12cd& operator=(const Gen_t_000d81e0_p12cd&); };
bool operator==(const Gen_t_000d81e0_p12cd&, const Gen_t_000d81e0_p12cd&);
bool operator<(const Gen_t_000d81e0_p12cd&, const Gen_t_000d81e0_p12cd&);

typedef _STL::pair<const int, Gen_t_000d81e0_p12cd> Pair_000d81e0;
typedef _STL::hashtable<Pair_000d81e0, int, _STL::hash<int>,
	_STL::_Select1st<Pair_000d81e0>, _STL::equal_to<int>,
	_STL::allocator<Pair_000d81e0> > Table_000d81e0;

// A second call site to _M_bkt_num_key in this TU (mirroring how the tgrid
// family's insert/erase/find/equal_range all share one non-inlined helper)
// keeps it out of line so erase(const_iterator&) below CALLs it, matching
// retail, instead of folding the trivial int-hash divide inline.
template class _STL::hashtable<Pair_000d81e0, int, _STL::hash<int>,
	_STL::_Select1st<Pair_000d81e0>, _STL::equal_to<int>,
	_STL::allocator<Pair_000d81e0> >;
