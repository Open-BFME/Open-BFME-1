// Open-BFME5: readable STLport vector overflow body for the 56-byte
// Rva006F2C70Element vector.  The named identity is supplied by the sole
// retail call from RvaVectorPushBack.cpp; this is the reallocating insert that
// push_back reaches when the vector has no spare capacity.

struct Rva006F2C70Element
{
	char m_body[56];
};

struct Rva00426C00Element
{
	char m_body[28];
};

struct Rva006AACB0Element
{
	char m_body[120];
};

struct Rva00774090Element
{
	char m_body[56];
};

struct Rva0081D280Element
{
	char m_body[28];
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

void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

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
		newFinish = uninitialized_copy(position, _M_finish, newFinish);

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

// ?_M_insert_overflow@?$vector@URva006F2C70Element@@V?$allocator@URva006F2C70Element@@@_STL@@@_STL@@IAEXPAURva006F2C70Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva006F2C70Element, allocator<Rva006F2C70Element> >;

// ?_M_insert_overflow@?$vector@URva00426C00Element@@V?$allocator@URva00426C00Element@@@_STL@@@_STL@@IAEXPAURva00426C00Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva00426C00Element, allocator<Rva00426C00Element> >;

// ?_M_insert_overflow@?$vector@URva006AACB0Element@@V?$allocator@URva006AACB0Element@@@_STL@@@_STL@@IAEXPAURva006AACB0Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva006AACB0Element, allocator<Rva006AACB0Element> >;

// ?_M_insert_overflow@?$vector@URva00774090Element@@V?$allocator@URva00774090Element@@@_STL@@@_STL@@IAEXPAURva00774090Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva00774090Element, allocator<Rva00774090Element> >;

// ?_M_insert_overflow@?$vector@URva0081D280Element@@V?$allocator@URva0081D280Element@@@_STL@@@_STL@@IAEXPAURva0081D280Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva0081D280Element, allocator<Rva0081D280Element> >;
}





