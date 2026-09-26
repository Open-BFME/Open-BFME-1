// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<T>::_M_insert_overflow, the reallocating insert,
// 13 bodies of 268 bytes.  Every one carried only a machine byte-dump row; the
// same shape is already converted at 0x00771870.
//
// The body grows the buffer to old size plus the larger of old size and the
// fill length, then runs three phases into it: everything before the insertion
// point, the inserted run itself, and -- only when the at-end flag is clear --
// everything after.  Then the old buffer goes through the vector's own
// _M_clear and the three pointers are rewritten.
//
// The element is eight bytes wide and the bytes say so three times: the pointer
// difference is shifted right by three, every copy loop strides by eight, and
// the new end-of-storage is a scale-8 lea.  What the element IS does not
// follow, only that it is not trivially copied -- all three phases call
// _Construct rather than moving the bytes inline, which is what a type with a
// non-trivial copy constructor forces.  Each element is therefore an
// eight-byte, non-trivially-copied type named for the address of the body, and
// its _Construct and _M_clear are pinned beside it.

namespace _STL
{
template <class Type>
class allocator
{
};

struct __false_type
{
};

void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

template <class Type>
void __cdecl _Construct(Type *destination, const Type &value);

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			_Construct(result, *first);
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
		_Construct(result, value);
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
		_Construct(newFinish, value);
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
				_Construct(newFinish, *cur);
				++cur;
				++newFinish;
			}
			while (cur != last);
		}
	}

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

struct Rva000A8500Element
{
	char m_body[ 8 ];
};

// retail 0x000A8500
template class vector<Rva000A8500Element, allocator<Rva000A8500Element> >;

struct Rva000B19F0Element
{
	char m_body[ 8 ];
};

// retail 0x000B19F0
template class vector<Rva000B19F0Element, allocator<Rva000B19F0Element> >;

struct Rva0019A900Element
{
	char m_body[ 8 ];
};

// retail 0x0019A900
template class vector<Rva0019A900Element, allocator<Rva0019A900Element> >;

struct Rva0025CB00Element
{
	char m_body[ 8 ];
};

// retail 0x0025CB00
template class vector<Rva0025CB00Element, allocator<Rva0025CB00Element> >;

struct Rva002949D0Element
{
	char m_body[ 8 ];
};

// retail 0x002949D0
template class vector<Rva002949D0Element, allocator<Rva002949D0Element> >;

struct Rva0029FA20Element
{
	char m_body[ 8 ];
};

// retail 0x0029FA20
template class vector<Rva0029FA20Element, allocator<Rva0029FA20Element> >;

struct Rva00347900Element
{
	char m_body[ 8 ];
};

// retail 0x00347900
template class vector<Rva00347900Element, allocator<Rva00347900Element> >;

struct Rva003751A0Element
{
	char m_body[ 8 ];
};

// retail 0x003751A0
template class vector<Rva003751A0Element, allocator<Rva003751A0Element> >;

struct Rva00381300Element
{
	char m_body[ 8 ];
};

// retail 0x00381300
template class vector<Rva00381300Element, allocator<Rva00381300Element> >;

struct Rva003B0060Element
{
	char m_body[ 8 ];
};

// retail 0x003B0060
template class vector<Rva003B0060Element, allocator<Rva003B0060Element> >;

struct Rva004358A0Element
{
	char m_body[ 8 ];
};

// retail 0x004358A0
template class vector<Rva004358A0Element, allocator<Rva004358A0Element> >;

struct Rva005751D0Element
{
	char m_body[ 8 ];
};

// retail 0x005751D0
template class vector<Rva005751D0Element, allocator<Rva005751D0Element> >;

struct Rva007719C0Element
{
	char m_body[ 8 ];
};

// retail 0x007719C0
template class vector<Rva007719C0Element, allocator<Rva007719C0Element> >;

}
