// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport vector<Coord3D>::resize, retail 0x000B7C90.
//
// Not compiled from vendor/stlport: the retail body ends `ret 0x10`, so it pops
// sixteen bytes of stack arguments -- four for the count and twelve for the
// fill value.  It takes that value BY VALUE.  Both branches confirm it: the
// erase side does `lea edx,[esp+0x14]` to hand _M_fill_insert the address of
// its own parameter slot, where a `const Coord3D&` parameter would have been
// loaded with `mov`.  Compiled against vendor/stlport/stl/_vector.h, whose
// signature is `resize(size_type, const _Tp&)`, all 93 bytes reproduce except
// exactly those: two `ret 8` and one `mov` for `lea`.  BFME's STLport differs
// from the vendored 4.5.3 here, so the class is spelled locally rather than
// patching a header every other vector in the tree compiles against.
//
// _M_fill_insert keeps its `const Coord3D&` parameter -- that is what retail
// hands it the address of -- so the divergence is resize's alone.
//
// The element type is pinned by the callee, not by the shape: 0x00014D7B is
// already in the ledger as __copy<Coord3D*, Coord3D*, int>.  Any 12-byte POD
// would mask to these same bytes otherwise.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

namespace _STL
{
struct random_access_iterator_tag {};

template <class Type>
class allocator {};

// ??$__copy@PAUCoord3D@@PAU1@H@_STL@@YAPAUCoord3D@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z
template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result,
	const random_access_iterator_tag &, Distance *);

template <class Type, class Allocator>
class vector
{
public:
	Type *begin() { return _M_start; }
	Type *end() { return _M_finish; }
	unsigned int size() const { return (unsigned int)(_M_finish - _M_start); }

	// STLport's erase(iterator, iterator), with copy() collapsed to the one
	// __copy overload it resolves to for a random-access POD range and
	// _Destroy dropped as a no-op.  Kept as its own function because retail
	// evaluates its two arguments before materialising the iterator tag.
	Type *erase(Type *first, Type *last)
	{
		random_access_iterator_tag tag;
		Type *i = __copy(last, _M_finish, first, tag, (int *)0);
		_M_finish = i;
		return first;
	}

	void resize(unsigned int newSize, Type value);

	// ?_M_fill_insert@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXPAUCoord3D@@IABU3@@Z
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

template void vector<Coord3D, allocator<Coord3D> >::resize(unsigned int, Coord3D);
}
