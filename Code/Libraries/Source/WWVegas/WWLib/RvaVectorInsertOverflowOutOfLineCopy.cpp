// Open-BFME5: STLport vector<T>::_M_insert_overflow for the instantiations
// whose trailing uninitialized copy stayed OUT OF LINE.  The growth path is the
// one already converted in Rva006F2C70VectorInsertOverflow.cpp -- grow to the
// old size plus the larger of the old size and the fill length, copy everything
// before the insertion point, the inserted run, and, only when the at-end flag
// is clear, everything after it, then _M_clear and the three pointers rewritten
// -- but where that file's bodies inline the last copy loop, these bodies call
// it.  The element width is the imul the copy loops stride by and the magic
// multiply that divides the byte distance; each width is confirmed by the
// matched push_back caller in RvaVectorPushBack.cpp, which is also what names
// each of these bodies.  What the element IS does not follow -- every phase is a
// call -- so each is a byte array named for the address of its push_back.

struct Rva003A35A0Element
{
	char m_body[ 184 ];
};

struct Rva0077CC10Element
{
	char m_body[ 188 ];
};

struct Rva00607770Element
{
	char m_body[ 496 ];
};

struct Rva00608FE0Element
{
	char m_body[ 528 ];
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

Rva003A35A0Element *__cdecl BfmeRva003A35A0Copy(
	Rva003A35A0Element *first, Rva003A35A0Element *last,
	Rva003A35A0Element *result, const __false_type &);

Rva0077CC10Element *__cdecl BfmeRva0077CC10Copy(
	Rva0077CC10Element *first, Rva0077CC10Element *last,
	Rva0077CC10Element *result, const __false_type &);

Rva00607770Element *__cdecl BfmeRva00607770Copy(
	Rva00607770Element *first, Rva00607770Element *last,
	Rva00607770Element *result, const __false_type &);

Rva00608FE0Element *__cdecl BfmeRva00608FE0Copy(
	Rva00608FE0Element *first, Rva00608FE0Element *last,
	Rva00608FE0Element *result, const __false_type &);

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

template <>
void vector<Rva003A35A0Element, allocator<Rva003A35A0Element> >::_M_insert_overflow(
	Rva003A35A0Element *position, const Rva003A35A0Element &value,
	const __false_type &, unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Rva003A35A0Element *newStart;
	if (length)
	{
		unsigned int bytes = length * sizeof(Rva003A35A0Element);
		if (bytes > 128)
			newStart = (Rva003A35A0Element *)vectorLargeAllocate(bytes);
		else
			newStart = (Rva003A35A0Element *)vectorSmallAllocate(bytes);
	}
	else
	{
		newStart = 0;
	}

	Rva003A35A0Element *newFinish = uninitialized_copy(
		_M_start, position, newStart);

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
		newFinish = BfmeRva003A35A0Copy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

// ?_M_insert_overflow@?$vector@URva003A35A0Element@@V?$allocator@URva003A35A0Element@@@_STL@@@_STL@@IAEXPAURva003A35A0Element@@ABU3@ABU__false_type@2@I_N@Z

template <>
void vector<Rva0077CC10Element, allocator<Rva0077CC10Element> >::_M_insert_overflow(
	Rva0077CC10Element *position, const Rva0077CC10Element &value,
	const __false_type &, unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Rva0077CC10Element *newStart;
	if (length)
	{
		unsigned int bytes = length * sizeof(Rva0077CC10Element);
		if (bytes > 128)
			newStart = (Rva0077CC10Element *)vectorLargeAllocate(bytes);
		else
			newStart = (Rva0077CC10Element *)vectorSmallAllocate(bytes);
	}
	else
	{
		newStart = 0;
	}

	Rva0077CC10Element *newFinish = uninitialized_copy(
		_M_start, position, newStart);

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
		newFinish = BfmeRva0077CC10Copy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

// ?_M_insert_overflow@?$vector@URva0077CC10Element@@V?$allocator@URva0077CC10Element@@@_STL@@@_STL@@IAEXPAURva0077CC10Element@@ABU3@ABU__false_type@2@I_N@Z

template <>
void vector<Rva00607770Element, allocator<Rva00607770Element> >::_M_insert_overflow(
	Rva00607770Element *position, const Rva00607770Element &value,
	const __false_type &, unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Rva00607770Element *newStart;
	if (length)
	{
		unsigned int bytes = length * sizeof(Rva00607770Element);
		if (bytes > 128)
			newStart = (Rva00607770Element *)vectorLargeAllocate(bytes);
		else
			newStart = (Rva00607770Element *)vectorSmallAllocate(bytes);
	}
	else
	{
		newStart = 0;
	}

	Rva00607770Element *newFinish = uninitialized_copy(
		_M_start, position, newStart);

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
		newFinish = BfmeRva00607770Copy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

// ?_M_insert_overflow@?$vector@URva00607770Element@@V?$allocator@URva00607770Element@@@_STL@@@_STL@@IAEXPAURva00607770Element@@ABU3@ABU__false_type@2@I_N@Z

template <>
void vector<Rva00608FE0Element, allocator<Rva00608FE0Element> >::_M_insert_overflow(
	Rva00608FE0Element *position, const Rva00608FE0Element &value,
	const __false_type &, unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Rva00608FE0Element *newStart;
	if (length)
	{
		unsigned int bytes = length * sizeof(Rva00608FE0Element);
		if (bytes > 128)
			newStart = (Rva00608FE0Element *)vectorLargeAllocate(bytes);
		else
			newStart = (Rva00608FE0Element *)vectorSmallAllocate(bytes);
	}
	else
	{
		newStart = 0;
	}

	Rva00608FE0Element *newFinish = uninitialized_copy(
		_M_start, position, newStart);

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
		newFinish = BfmeRva00608FE0Copy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

// ?_M_insert_overflow@?$vector@URva00608FE0Element@@V?$allocator@URva00608FE0Element@@@_STL@@@_STL@@IAEXPAURva00608FE0Element@@ABU3@ABU__false_type@2@I_N@Z
}
