// Open-BFME5: STLport vector<T>::_M_insert_overflow, the reallocating insert,
// for two more instantiations whose trailing uninitialized copy is INLINE -- the
// same body already converted in Rva006F2C70VectorInsertOverflow.cpp, where four
// _Construct call sites appear instead of three plus an out-of-line copy.  Grow
// to the old size plus the larger of the old size and the fill length, copy
// everything before the insertion point, the inserted run, and, only when the
// at-end flag is clear, everything after it, then _M_clear and the three
// pointers rewritten.  The element width is the stride the copy loops add and
// the magic multiply that divides the byte distance; each is confirmed by the
// matched push_back caller in RvaVectorPushBack.cpp, which is also what names
// the body.  What the element IS does not follow -- every phase is a call -- so
// each is a byte array named for the address of its push_back.

struct Rva000FB210Element
{
	char m_body[ 96 ];
};

struct Rva00366890Element
{
	char m_body[ 88 ];
};

struct Gen_t_003b10a0_p48cd
{
	char m_body[ 48 ];
};

struct Gen_t_003b1050_p40cd
{
	char m_body[ 40 ];
};

struct Gen_t_001fa830_p12cd
{
	char m_body[ 12 ];
};

struct Gen_t_002e19c0_p12cd
{
	char m_body[ 12 ];
};

struct Gen_t_002e20c0_p12cd
{
	char m_body[ 12 ];
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

// ?_M_insert_overflow@?$vector@URva000FB210Element@@V?$allocator@URva000FB210Element@@@_STL@@@_STL@@IAEXPAURva000FB210Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva000FB210Element, allocator<Rva000FB210Element> >;

// ?_M_insert_overflow@?$vector@URva00366890Element@@V?$allocator@URva00366890Element@@@_STL@@@_STL@@IAEXPAURva00366890Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva00366890Element, allocator<Rva00366890Element> >;

// ?_M_insert_overflow@?$vector@UGen_t_003b10a0_p48cd@@V?$allocator@UGen_t_003b10a0_p48cd@@@_STL@@@_STL@@IAEXPAUGen_t_003b10a0_p48cd@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Gen_t_003b10a0_p48cd, allocator<Gen_t_003b10a0_p48cd> >;

// ?_M_insert_overflow@?$vector@UGen_t_003b1050_p40cd@@V?$allocator@UGen_t_003b1050_p40cd@@@_STL@@@_STL@@IAEXPAUGen_t_003b1050_p40cd@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Gen_t_003b1050_p40cd, allocator<Gen_t_003b1050_p40cd> >;

// ?_M_insert_overflow@?$vector@UGen_t_001fa830_p12cd@@V?$allocator@UGen_t_001fa830_p12cd@@@_STL@@@_STL@@IAEXPAUGen_t_001fa830_p12cd@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Gen_t_001fa830_p12cd, allocator<Gen_t_001fa830_p12cd> >;

// ?_M_insert_overflow@?$vector@UGen_t_002e19c0_p12cd@@V?$allocator@UGen_t_002e19c0_p12cd@@@_STL@@@_STL@@IAEXPAUGen_t_002e19c0_p12cd@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Gen_t_002e19c0_p12cd, allocator<Gen_t_002e19c0_p12cd> >;

// ?_M_insert_overflow@?$vector@UGen_t_002e20c0_p12cd@@V?$allocator@UGen_t_002e20c0_p12cd@@@_STL@@@_STL@@IAEXPAUGen_t_002e20c0_p12cd@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Gen_t_002e20c0_p12cd, allocator<Gen_t_002e20c0_p12cd> >;
}
