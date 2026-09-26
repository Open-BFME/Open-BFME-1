// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<T>::_M_insert_overflow, the reallocating insert,
// 16 bodies of 287 bytes.  Every one carried only a machine byte-dump row; the
// same size is already converted at 0x002EB770 over a 20-byte element.
//
// Structurally these are the 268-byte bodies of RvaVectorInsertOverflow8.cpp:
// grow to the old size plus the larger of the old size and the fill length,
// then everything before the insertion point, the inserted run, and -- only
// when the at-end flag is clear -- everything after, then _M_clear and the
// three pointers rewritten.  Nineteen extra bytes buy one thing: an element
// width that is not a power of two.  Where an eight-byte element divides with a
// `sar 3`, these divide by a signed magic multiply, and each body's magic
// constant plus its shift is what names the width.
//
// Three widths appear: 20 bytes for 10 of them, 24 bytes for 3 of them, 36 bytes for 3 of them.  Each is confirmed twice over by the stride the copy
// loops add and by the lea that recomputes the end of storage.  As in the
// eight-byte family, what the element IS does not follow -- only that it is not
// trivially copied, since all three phases call _Construct rather than moving
// bytes inline.  Each element is named for the address of its body.

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
		newFinish = uninitialized_copy(position, _M_finish, newFinish);

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

struct Rva00143CE0Element
{
	char m_body[ 20 ];
};

// retail 0x00143CE0
template class vector<Rva00143CE0Element, allocator<Rva00143CE0Element> >;

struct Rva0035AFC0Element
{
	char m_body[ 20 ];
};

// retail 0x0035AFC0
template class vector<Rva0035AFC0Element, allocator<Rva0035AFC0Element> >;

struct Rva0035B130Element
{
	char m_body[ 20 ];
};

// retail 0x0035B130
template class vector<Rva0035B130Element, allocator<Rva0035B130Element> >;

struct Rva003A5500Element
{
	char m_body[ 20 ];
};

// retail 0x003A5500
template class vector<Rva003A5500Element, allocator<Rva003A5500Element> >;

struct Rva003B0760Element
{
	char m_body[ 20 ];
};

// retail 0x003B0760
template class vector<Rva003B0760Element, allocator<Rva003B0760Element> >;

struct Rva003B0A30Element
{
	char m_body[ 20 ];
};

// retail 0x003B0A30
template class vector<Rva003B0A30Element, allocator<Rva003B0A30Element> >;

struct Rva003BB340Element
{
	char m_body[ 20 ];
};

// retail 0x003BB340
template class vector<Rva003BB340Element, allocator<Rva003BB340Element> >;

struct Rva007742A0Element
{
	char m_body[ 20 ];
};

// retail 0x007742A0
template class vector<Rva007742A0Element, allocator<Rva007742A0Element> >;

struct Rva00774410Element
{
	char m_body[ 20 ];
};

// retail 0x00774410
template class vector<Rva00774410Element, allocator<Rva00774410Element> >;

struct Rva0077AEA0Element
{
	char m_body[ 20 ];
};

// retail 0x0077AEA0
template class vector<Rva0077AEA0Element, allocator<Rva0077AEA0Element> >;

struct Rva001DFFF0Element
{
	char m_body[ 24 ];
};

// retail 0x001DFFF0
template class vector<Rva001DFFF0Element, allocator<Rva001DFFF0Element> >;

struct Rva003B23D0Element
{
	char m_body[ 24 ];
};

// retail 0x003B23D0
template class vector<Rva003B23D0Element, allocator<Rva003B23D0Element> >;

struct Rva00771B10Element
{
	char m_body[ 24 ];
};

// retail 0x00771B10
template class vector<Rva00771B10Element, allocator<Rva00771B10Element> >;

struct Rva00146940Element
{
	char m_body[ 36 ];
};

// retail 0x00146940
template class vector<Rva00146940Element, allocator<Rva00146940Element> >;

struct Rva003B20C0Element
{
	char m_body[ 36 ];
};

// retail 0x003B20C0
template class vector<Rva003B20C0Element, allocator<Rva003B20C0Element> >;

struct Rva0061AE10Element
{
	char m_body[ 36 ];
};

// retail 0x0061AE10
template class vector<Rva0061AE10Element, allocator<Rva0061AE10Element> >;

}
