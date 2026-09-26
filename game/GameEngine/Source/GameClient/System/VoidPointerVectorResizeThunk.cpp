// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport vector<void *>::resize, retail 0x003D4210.
//
// Same body as vector<int> at 0x001DC360 -- byte for byte, outside the one
// relocation -- because both element types are four-byte and trivially
// assignable.  The comment there carries the derivation; in short, the fill
// value is passed BY VALUE (the grow arm hands _M_fill_insert `lea esi,
// [esp+0x10]`, the address of its own parameter slot), which the vendored
// STLport header cannot express, so the class is spelled locally.
//
// The element type is pinned by the callee, not by the shape: the grow arm's
// rel32 resolves to the ILT thunk 0x0002570C, which jumps to 0x003D3D50, and
// the ledger already holds that as
// ?_M_fill_insert@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXPAPAXIABQAX@Z
// in ParticleSys.cpp -- the same TU this body sits in, 0x4C0 bytes below it.
// Any four-byte POD would mask to these same bytes otherwise.

typedef unsigned int size_t_;

// Retail reaches memmove through the import slot (`ff 15`); the pin
// `_bfme_memmove_ptr` is already in targets/game/reverse/symbols.csv at that slot.
extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);
#define memmove (*bfme_memmove_ptr)

namespace _STL
{

template <class Type>
class allocator {};

// STLport's __copy_trivial.  The empty case is decided on the POINTERS, not on
// the byte count: retail guards with `cmp eax,eax` before it has computed a
// length at all, and only forms the count inside the arm that calls memmove.
template <class Type>
inline Type *__copy_trivial(Type *first, Type *last, Type *result)
{
	if (first == last)
		return result;
	size_t_ n = (size_t_)((const char *)last - (const char *)first);
	return (Type *)((char *)memmove(result, first, n) + n);
}

template <class Type, class Allocator>
class vector
{
public:
	Type *begin() { return _M_start; }
	Type *end() { return _M_finish; }
	unsigned int size() const { return (unsigned int)(_M_finish - _M_start); }

	// erase(iterator, iterator) with _Destroy dropped as a no-op for a POD.
	// Kept as its own function so __copy_trivial's guard is inlined from the
	// callee side, which is what leaves the dead compare behind: erase passes
	// end() as both arguments, so the range is empty by construction and the
	// length always zero, but neither was known when the guard was written.
	Type *erase(Type *first, Type *last)
	{
		Type *i = __copy_trivial(last, _M_finish, first);
		_M_finish = i;
		return first;
	}

	void resize(unsigned int newSize, Type value);

	// ?_M_fill_insert@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXPAPAXIABQAX@Z
	void _M_fill_insert(Type *pos, unsigned int n, const Type &value);

private:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::resize(unsigned int newSize, Type value)
{
	if (newSize < size())
		erase(begin() + newSize, end());
	else
		_M_fill_insert(end(), newSize - size(), value);
}

template void vector<void *, allocator<void *> >::resize(unsigned int, void *);
}
