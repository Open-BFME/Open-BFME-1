// Open-BFME5: readable STLport vector<T>::_M_insert_overflow body for the
// 44-byte Rva00253630Element vector.  The caller in RvaVectorPushBack.cpp
// identifies this instantiation and supplies the retail boundary.

struct Rva00253630Element
{
	char m_body[44];
};

struct Rva00777E40Element
{
	char m_body[44];
};

struct Rva0077BFB0Element
{
	char m_body[108];
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

template <class Type>
void __cdecl BfmeElementConstruct(Type *destination, const Type &value);

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
__forceinline Type *uninitialized_fill_n(Type *result, unsigned int count,
	const Type &value)
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
		newFinish = uninitialized_copy(position, _M_finish, newFinish);

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

// ?_M_insert_overflow@?$vector@URva00253630Element@@V?$allocator@URva00253630Element@@@_STL@@@_STL@@IAEXPAURva00253630Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva00253630Element, allocator<Rva00253630Element> >;

// ?_M_insert_overflow@?$vector@URva00777E40Element@@V?$allocator@URva00777E40Element@@@_STL@@@_STL@@IAEXPAURva00777E40Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva00777E40Element, allocator<Rva00777E40Element> >;

// ?_M_insert_overflow@?$vector@URva0077BFB0Element@@V?$allocator@URva0077BFB0Element@@@_STL@@@_STL@@IAEXPAURva0077BFB0Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva0077BFB0Element, allocator<Rva0077BFB0Element> >;
}



