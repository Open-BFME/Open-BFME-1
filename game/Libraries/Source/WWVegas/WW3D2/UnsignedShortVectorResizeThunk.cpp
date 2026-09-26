// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport vector<unsigned short>::resize, retail 0x009407B0.
//
// The fourth and last member of the resize family found by scanning
// game/gen_asm/ for the 16-byte opening of the body at 0x001DC360, and the only
// one that is not 88 bytes: `sar ecx,1` and `lea ecx,[esi+edx*2]` in place of
// `sar ecx,2` and `[esi+edx*4]` make the element two bytes wide, which is one
// byte shorter in each of two places.  Everything else -- the by-value fill
// value proven by `lea esi,[esp+0x10]`, the empty-by-construction erase, the
// memmove reached through the import slot -- is the derivation written up at
// 0x001DC360.
//
// The element type is `unsigned short` and not some other two-byte POD because
// of the callee, as with the two 88-byte siblings.  The grow arm's rel32
// resolves to 0x0093FC10, which is still an unnamed 294-byte dump; compiling
// _STL::vector<unsigned short> out of inputs/vendor/stlport gives a _M_fill_insert of
// exactly 294 bytes whose instruction stream is isomorphic to it -- same
// control flow, same three memmove sites at the same import slot, same
// `rep stosd` / `rep stosw` pair (which is what fixes the width at two bytes),
// same `ret 0xc`.  That body differs from retail only by a rotation of the two
// callee-saved registers holding `this` and __old_finish (ebx/esi swapped) and
// one instruction schedule around the second fill() call, so it cannot be
// landed as a byte match, but it is more than enough to name the type this
// resize was instantiated on.

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

	// ?_M_fill_insert@?$vector@GV?$allocator@G@_STL@@@_STL@@QAEXPAGIABG@Z
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

template void vector<unsigned short, allocator<unsigned short> >::resize(unsigned int, unsigned short);
}
