// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport vector<float>::resize, retail 0x00459F70.
//
// Byte for byte the body landed at 0x001DC360 outside its single relocation,
// because float is four bytes wide and trivially assignable like the other
// three.  The derivation is written up there: the fill value is passed BY
// VALUE, proven by `lea esi,[esp+0x10]` handing _M_fill_insert the address of
// its own parameter slot, which the vendored STLport header cannot express, so
// the class is spelled locally.
//
// The element type is pinned by the callee: the grow arm's rel32 resolves to
// ILT 0x00025AAE, which jumps to 0x00459D90 -- landed in this same commit as
// vector<float>::_M_fill_insert, 283 bytes exact, 0x1E0 bytes below this body
// in the same TU.  That is the whole reason this member of the family had to
// wait: the other three read their element type off a _M_fill_insert the ledger
// already named, and this one's callee was still an unnamed dump.
//
// Placement follows the nearest named neighbour and is not a TU claim; see
// FloatVectorFillInsertThunk.cpp.

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

	// ?_M_fill_insert@?$vector@MV?$allocator@M@_STL@@@_STL@@QAEXPAMIABM@Z
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

template void vector<float, allocator<float> >::resize(unsigned int, float);
}
