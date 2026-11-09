// cl: /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS

// STLport vector<T>::resize, retail 0x003D4210, for the LargeGroupAudioKeyMap
// word vector (callers: bfmeMerge 0x003D4580, bfmeAddKey 0x003D46A0).
//
// Same body as vector<int> at 0x001DC360 -- byte for byte, outside the one
// relocation -- because both element types are four-byte and trivially
// assignable.  The comment there carries the derivation; in short, the fill
// value is passed BY VALUE (the grow arm hands _M_fill_insert `lea esi,
// [esp+0x10]`, the address of its own parameter slot), which the vendored
// STLport header cannot express, so the class is spelled locally.
//
// The element is not void*: the grow arm's rel32 resolves to ILT 0x0002570C ->
// 0x003D3D50, while vector<void*>::_M_fill_insert is 0x00067740 (called by the
// hashtable bucket code) and retail has no identical-COMDAT folding.  It is
// vector<unsigned int> (see Rva003D3D50VectorFillInsert.cpp).


typedef unsigned int size_t_;

// Retail reaches memmove through its MSVCR71 import slot (`ff 15`, IAT
// 0x0135945C); /MD's <string.h> declares it dllimport, so the call binds to
// __imp__memmove.
#include <string.h>

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

	// ?_M_fill_insert@?$vector@IV?$allocator@I@_STL@@@_STL@@QAEXPAIIABI@Z
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

template void vector<unsigned int, allocator<unsigned int> >::resize(unsigned int, unsigned int);
}
