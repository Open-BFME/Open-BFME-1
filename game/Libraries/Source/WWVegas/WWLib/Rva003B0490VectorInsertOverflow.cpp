// Open-BFME5: STLport vector<T>::_M_insert_overflow, the reallocating insert,
// for the 32-byte element vector reached only from the matched push_back
// family. Grow to the old size plus the larger of the old size and the fill
// length, copy everything before the insertion point, the inserted run, and,
// only when the at-end flag is clear, everything after it, then _M_clear and
// rewrite the three pointers. The element width is the stride the copy loops
// add and the magic multiply that divides the byte distance; each is
// confirmed by the matched push_back caller. What the element IS does not
// follow -- every phase is a call -- so it is a byte array named for this
// instantiation's own address.

struct Gen_t_003b10f0_p32cd
{
	char m_body[ 32 ];
};

struct P6Elem003B1940;
void __cdecl Bfme003B1940Construct(P6Elem003B1940 *, const P6Elem003B1940 &);
class Gen_003AFBB0 { public: void bfmeDestroy(); };

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

template <class Type>
__forceinline void BfmeElementConstruct(Type *destination, const Type &value)
{
    Bfme003B1940Construct(reinterpret_cast<P6Elem003B1940 *>(destination), reinterpret_cast<const P6Elem003B1940 &>(value));
}

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			BfmeElementConstruct(result, *first);
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
		BfmeElementConstruct(result, value);
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
		BfmeElementConstruct(newFinish, value);
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
			newFinish = uninitialized_copy(position, last, newFinish);
	}

	reinterpret_cast<Gen_003AFBB0 *>(this)->bfmeDestroy();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

// ?_M_insert_overflow@?$vector@UGen_t_003b10f0_p32cd@@V?$allocator@UGen_t_003b10f0_p32cd@@@_STL@@@_STL@@IAEXPAUGen_t_003b10f0_p32cd@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Gen_t_003b10f0_p32cd, allocator<Gen_t_003b10f0_p32cd> >;
}
