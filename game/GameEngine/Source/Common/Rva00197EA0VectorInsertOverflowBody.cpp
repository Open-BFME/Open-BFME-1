// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport reallocating insert for a 12-byte vector element, retail
// 0x00197EA0, 314 bytes. The body carried only a machine byte-dump row and no name.
//
// The element type is not recoverable from this body. Its copy helper at
// 0x00192190 is the const ArmorTemplateSet specialization; its fill helper at
// 0x001921E0 is the HorzLine specialization. Both operate on the same proven
// 12-byte trivial element width, so this body keeps an address-derived view.
//
// Twelve bytes is what the bytes say: both size computations go through the
// signed divide-by-twelve magic multiply and the new end-of-storage is a pair of
// leas. Retail hands the helpers' empty dispatch tag the address of its own
// trailing bool argument rather than spending a frame slot on it.

struct Rva00197EA0Element
{
	unsigned char m_data[12];
};

class ArmorTemplateSet;
struct HorzLine;

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

namespace _STL
{
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

struct __false_type
{
};

template <class Input, class Output>
Output __cdecl __uninitialized_copy(Input first, Input last, Output result,
	const __false_type &tag);

template <class Output, class Size, class Value>
Output __cdecl __uninitialized_fill_n(Output result, Size count,
	const Value &value, const __false_type &tag);

template <class Type>
class allocator
{
};

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

	Type *newFinish = reinterpret_cast<Type *>(__uninitialized_copy<const ArmorTemplateSet *, ArmorTemplateSet *>(
		reinterpret_cast<const ArmorTemplateSet *>(_M_start),
		reinterpret_cast<const ArmorTemplateSet *>(position),
		reinterpret_cast<ArmorTemplateSet *>(newStart), reinterpret_cast<const __false_type &>(atEnd)));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = reinterpret_cast<Type *>(__uninitialized_fill_n<HorzLine *, unsigned int, HorzLine>(
			reinterpret_cast<HorzLine *>(newFinish), fillLength,
			reinterpret_cast<const HorzLine &>(value), reinterpret_cast<const __false_type &>(atEnd)));
	}

	if (!atEnd)
		newFinish = reinterpret_cast<Type *>(__uninitialized_copy<const ArmorTemplateSet *, ArmorTemplateSet *>(
			reinterpret_cast<const ArmorTemplateSet *>(position),
			reinterpret_cast<const ArmorTemplateSet *>(_M_finish),
			reinterpret_cast<ArmorTemplateSet *>(newFinish), reinterpret_cast<const __false_type &>(atEnd)));

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

template class vector<Rva00197EA0Element, allocator<Rva00197EA0Element> >;
}
