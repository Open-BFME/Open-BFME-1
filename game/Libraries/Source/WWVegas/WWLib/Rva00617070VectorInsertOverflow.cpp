// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// STLport vector<Gen_t_00617d60_p16cd>::_M_insert_overflow at retail
// 0x00617070. The matched push_back at 0x00617D60 and the retail type name
// identify this 16-byte specialization. Its copy constructor and _M_clear
// calls use the adjacent incremental-link thunks at 0x0004A296 and
// 0x0001FD2F.

struct Gen_t_00617d60_p16cd
{
	char m_body[16];
};

// Incremental-link thunks: the retail element construct (0x0004A296) and
// vector::_M_clear (0x0001FD2F) are reached through their ILT stubs.
extern void j_0004a296();
extern void j_0001fd2f();

// Address-only class shape for the _M_clear ILT thunk; no members.
class ClearTarget00617070
{
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorLargeAllocate(unsigned int bytes) { return ::operator new(bytes); }
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }

// Retail element construction is reached through the ILT thunk at 0x0004A296,
// which stands in for the placement-new construct this vector specializes.
template <class Type>
static __forceinline void elementConstruct00617070(Type *destination,
	const Type &value)
{
	typedef void (__cdecl *Ctor)(Type *, const Type &);
	((Ctor)(void *)j_0004a296)(destination, value);
}

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			elementConstruct00617070(result, *first);
			++first;
			++result;
		}
		while (first != last);
	}
	return result;
}

template <class Type>
__forceinline Type *uninitialized_fill_n(Type *result, unsigned int count,
	const Type &value)
{
	for (; count > 0; --count)
	{
		elementConstruct00617070(result, value);
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
	void _M_clear();

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
		elementConstruct00617070(newFinish, value);
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n(newFinish, fillLength, value);
	}

	if (!atEnd)
	{
		Type *last = _M_finish;
		if (position != last)
		{
			Type *cur = position;
			do
			{
				elementConstruct00617070(newFinish, *cur);
				++cur;
				++newFinish;
			}
			while (cur != last);
		}
	}

	typedef void (ClearTarget00617070::*ClearThunk)();
	union { void (*fn)(); ClearThunk call; } clear = { j_0001fd2f };
	(((ClearTarget00617070 *)this)->*clear.call)();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}
}

template class _STL::vector<Gen_t_00617d60_p16cd,
	_STL::allocator<Gen_t_00617d60_p16cd> >;
