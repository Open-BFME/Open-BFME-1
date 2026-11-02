// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00235CD0 (53 bytes) copy-constructs a tree node's value: STLport
// _Construct of a pair<const int, V> where V is 16 bytes.  It is reached
// through ILT 0x00007ED7 by the _M_insert at 0x0023B4D0 and directly by the
// allocate-then-initialise helper 0x00236750 (AllocateThenInitialise.cpp),
// which already calls it as gen00235CD0(void *, void *).  The pinned
// _Construct<pair<const int, Rva0023B5B0Value> > spelling at ILT 0x00007ED7 is
// contradicted by retail's ILT order, so the real mapped type is unknown and
// the body keeps that caller's address-derived name.
//
// Shape: the key dword is copied, then the value through its own copy
// constructor -- a 12-byte POD member copied through a second source/target
// pointer pair, then the last dword.  An implicit copy of the value (or a
// nested Vector3-style copy constructor) flattens the copy to 41 bytes.  The
// copy is the placement new STLport _Construct performs (its null test is
// the placement-new check); calling _Construct itself only tail-jumps.  The
// retail STLport configuration matches Rva0094D370TextureMap.cpp.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

struct Rva00235CD0Triple
{
	int m_words[3];
};

struct Rva00235CD0Value
{
	Rva00235CD0Value(const Rva00235CD0Value &other) : m_triple(other.m_triple), m_last(other.m_last) {}
	Rva00235CD0Triple m_triple;
	int m_last;
};

typedef _STL::pair<const int, Rva00235CD0Value> Rva00235CD0Pair;

// ?gen00235CD0@@YAXPAX0@Z
void gen00235CD0(void *destination, void *source)
{
	::new (destination) Rva00235CD0Pair(*(const Rva00235CD0Pair *)source);
}
