// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: LargeGroupAudioKeyMap copy constructor, retail 0x003D3BB0,
// 133 bytes. Retail linked this TU's private copies of two STLport helpers.
// Scope their source spellings to the observed RVAs so the exact constructor
// does not add false candidates to the same helpers instantiated elsewhere.

#define _Vector_base Rva003D3540VectorBase
#define get_allocator bfmeGetAllocator003D32D0
#include <vector>
#undef get_allocator
#undef _Vector_base

class LargeGroupAudioKeyMap :
	public _STL::vector<void *, _STL::allocator<void *> >
{
public:
	LargeGroupAudioKeyMap(const LargeGroupAudioKeyMap &other);
};

void bfmeRetainMembers(LargeGroupAudioKeyMap *map);

// ??0LargeGroupAudioKeyMap@@QAE@ABV0@@Z
LargeGroupAudioKeyMap::LargeGroupAudioKeyMap(
	const LargeGroupAudioKeyMap &other) :
	_STL::vector<void *, _STL::allocator<void *> >(other)
{
	bfmeRetainMembers(this);
}
