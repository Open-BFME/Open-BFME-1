// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: STLport reallocating insert for a 4-byte vector element, retail
// 0x000BD3B0, 328 bytes. The body carried only a machine byte-dump row and no name.
//
// The element type is not recoverable: all three phases reach one out-of-line
// _STL::_Construct at 0x000BA5B0 (retail ILT 0x0002D30D, ledger row
// ?gen_000BA5B0@@YAXPAPAX0@Z -- a two-slot refcount assign, so the element is
// a 4-byte refcounted handle) and the teardown reaches _STL::__destroy_aux
// over a range of 4-byte refcounted handles at 0x000BB5D0 (retail ILT
// 0x000247E9, ledger row ?__destroy_aux@_STL@@YAXPAVRva000BB5D0Ref@@0ABU__false_type@1@@Z,
// game/Libraries/Source/WWVegas/WWLib/_STL___destroy_aux.cpp). Both take
// pointer-sized slots, which is all this 4-byte element is, so the calls are
// respelled to those ledger rows under TU-local declarations. The element keeps
// an address-derived name and is modelled by width.
//
// Four bytes is what the bytes say: the size arithmetic shifts right by two and
// the allocator's byte count is a scale-4 lea. Unlike the wider elements in this
// family the old range is destroyed by a call before the block goes back to the
// allocator, and the free itself is still inlined.

struct Rva000BD3B0Element
{
	unsigned char m_data[4];
};

// Retail ILTs 0x0002D30D and 0x000247E9 route to these ledger-owned bodies at
// 0x000BA5B0 and 0x000BB5D0 respectively. The two-slot assign helper is a
// global-scope row, the destroy range helper is _STL's.
class Rva000BB5D0Ref;

void gen_000BA5B0(void **dst, void **src);

namespace _STL
{
template <class First, class Second>
struct pair
{
	First first;
	Second second;
};

template <class Type>
class allocator
{
};

struct __false_type
{
};

// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
static void vectorSmallDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	friend void vectorSmallDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorLargeAllocate(unsigned int bytes) { return ::operator new(bytes); }
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }
static inline void vectorLargeDeallocate(void *block) { ::operator delete(block); }
static inline void vectorSmallDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

// The old range is destroyed by an out-of-line _STL::__destroy_aux before the
// block goes back to the allocator; it takes the same trailing dispatch tag
// the rest of the family passes to its phase helpers.
// Declaration moved into _STL namespace to match ledger row
// ?__destroy_aux@_STL@@YAXPAVRva000BB5D0Ref@@0ABU__false_type@1@@Z
void __cdecl __destroy_aux(Rva000BB5D0Ref *first, Rva000BB5D0Ref *last,
	const __false_type &tag);

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			gen_000BA5B0((void **)result, (void **)&*first);
			++first;
			++result;
		}
		while (first != last);
	}
	return result;
}

template <class Type>
__forceinline Type *uninitialized_fill_n(Type *result, unsigned int count, const Type &value)
{
	for (; count > 0; --count)
	{
		gen_000BA5B0((void **)result, (void **)&value);
		++result;
	}
	return result;
}

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &,
	unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Type *newStart;
	if (length)
	{
		unsigned int bytes = length * sizeof(Type);
		if (bytes > 128)
			newStart = (Type *)vectorLargeAllocate(bytes);
		else
			newStart = (Type *)vectorSmallAllocate(bytes);
	}
	else
	{
		newStart = 0;
	}

	Type *newFinish = uninitialized_copy(_M_start, position, newStart);

	if (fillLength == 1)
	{
		gen_000BA5B0((void **)newFinish, (void **)&value);
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n(newFinish, fillLength, value);
	}

	if (!atEnd)
		newFinish = uninitialized_copy(position, _M_finish, newFinish);

	__destroy_aux(reinterpret_cast<Rva000BB5D0Ref *>(_M_start),
		reinterpret_cast<Rva000BB5D0Ref *>(_M_finish),
		reinterpret_cast<const __false_type &>(atEnd));

	if (_M_start)
	{
		unsigned int bytes = (unsigned int)(_M_end_of_storage - _M_start) * sizeof(Type);
		if (bytes > 128)
			vectorLargeDeallocate(_M_start);
		else
			vectorSmallDeallocate(_M_start, bytes);
	}

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

template class vector<Rva000BD3B0Element, allocator<Rva000BD3B0Element > >;
}
