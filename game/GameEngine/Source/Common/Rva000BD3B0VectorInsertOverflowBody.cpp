// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: STLport reallocating insert for a 4-byte vector element, retail
// 0x000BD3B0, 328 bytes. The body carried only a machine byte-dump row and no name.
//
// The element type is not recoverable: all three phases reach one out-of-line
// _STL::_Construct through the ILT at 0x0002D30D (body 0x000BA5B0) and the
// teardown reaches _STL::_Destroy through the ILT at 0x000247E9 (body 0x000BB5D0),
// and the ledger holds neither under a real name. So the element is named for
// the address of the body it belongs to and modelled by width.
//
// Four bytes is what the bytes say: the size arithmetic shifts right by two and
// the allocator's byte count is a scale-4 lea. Unlike the wider elements in this
// family the old range is destroyed by a call before the block goes back to the
// allocator, and the free itself is still inlined.

struct Rva000BD3B0Element
{
	unsigned char m_data[4];
};

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

void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);
void __cdecl vectorLargeDeallocate(void *block);
void __cdecl vectorSmallDeallocate(void *block, unsigned int bytes);

// The old range is destroyed by an out-of-line _STL::_Destroy before the block
// goes back to the allocator; it takes the same trailing dispatch tag the rest
// of the family passes to its phase helpers.
void __cdecl BfmeRva000BD3B0Destroy(Rva000BD3B0Element *first, Rva000BD3B0Element *last,
	const __false_type &);

void __cdecl BfmeRva000BD3B0Construct(Rva000BD3B0Element *destination,
	const Rva000BD3B0Element &value);

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			BfmeRva000BD3B0Construct(result, *first);
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
		BfmeRva000BD3B0Construct(result, value);
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
		BfmeRva000BD3B0Construct(newFinish, value);
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n(newFinish, fillLength, value);
	}

	if (!atEnd)
		newFinish = uninitialized_copy(position, _M_finish, newFinish);

	BfmeRva000BD3B0Destroy(_M_start, _M_finish, reinterpret_cast<const __false_type &>(atEnd));

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
