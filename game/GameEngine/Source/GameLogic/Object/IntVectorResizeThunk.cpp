// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport vector<int>::resize, retail 0x001DC360.
//
// Not compiled from inputs/vendor/stlport, for the reason the whole *ResizeThunk.cpp
// family exists: BFME's STLport declares resize's fill value BY VALUE where the
// vendored 4.5.3 header declares `resize(size_type, const _Tp&)`.  The grow arm
// hands _M_fill_insert `lea esi,[esp+0x10]` -- the ADDRESS of its own parameter
// slot -- where a reference parameter already holds the pointer and needs a
// plain `mov`.  `ret 8` cannot tell the two apart (four bytes of count plus four
// of either an int or a pointer), so the `lea` is the whole evidence, and it is
// the same evidence that settled vector<Coord3D> at 0x000B7C90 and
// vector<ObjectID> at 0x002CD1B0.  The class is spelled locally rather than
// patching a header every other vector in the tree compiles against.
//
// What is new here versus those two: int is trivially assignable, so erase's
// copy() resolves to __copy_trivial and the memmove lands INLINE instead of as
// an out-of-line __copy call.  That is why the shrink arm carries two dead
// computations retail never folded away -- `cmp eax,eax` for a range that is
// empty by construction (erase's __last is end()) and `mov esi,eax / sub esi,eax`
// for a length that is therefore always zero.  Both survive because they are
// __copy_trivial's own guard and count, written before inlining knew the caller
// passed end() twice.  Spelling erase as a plain memmove with the guard removed
// comes out short; the guard has to be in the callee.
//
// _M_fill_insert keeps its `const int&` parameter -- that is what retail hands
// the address of -- so the divergence is resize's alone.

typedef unsigned int size_t_;

// Retail reaches memmove through the import slot (`ff 15`), not through a
// direct call to a thunk, so it is spelled as a pointer here for the same
// reason VectorIntegerInsertOverflowThunk.cpp spells it that way -- the pin
// `_bfme_memmove_ptr` is already in targets/game/reverse/symbols.csv at that slot.
extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);
#define memmove (*bfme_memmove_ptr)

namespace _STL
{

template <class Type>
class allocator {};

// STLport's __copy_trivial.  The empty case is decided on the POINTERS, not on
// the byte count: retail guards with `cmp eax,eax` before it has computed a
// length at all, and only forms the count (`mov esi,eax / sub esi,eax`) inside
// the arm that calls memmove.
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

	// STLport's erase(iterator, iterator) with _Destroy dropped as a no-op for
	// a POD.  Kept as its own function so __copy_trivial's guard is inlined
	// from the callee side, which is what leaves the dead compare behind.
	Type *erase(Type *first, Type *last)
	{
		Type *i = __copy_trivial(last, _M_finish, first);
		_M_finish = i;
		return first;
	}

	void resize(unsigned int newSize, Type value);

	// ?_M_fill_insert@?$vector@HV?$allocator@H@_STL@@@_STL@@QAEXPAHIABH@Z
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

template void vector<int, allocator<int> >::resize(unsigned int, int);
}
