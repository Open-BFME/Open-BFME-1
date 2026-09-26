// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: STLport reallocating insert for an 8-byte vector element, retail
// 0x001E9020, 306 bytes. The body carried only a machine byte-dump row and no name.
//
// The element type is not recoverable: all three phases reach the same
// out-of-line _STL::_Construct through the ILT at 0x00046AF1, whose body at
// 0x001E21F0 the ledger holds only under a synthetic
// pair<const int, Gen_p4pod> spelling. So the element is named for the address
// of the body it belongs to and modelled by width.
//
// Eight bytes is what the bytes say: the size arithmetic shifts the byte
// distance right by three, every copy loop strides by eight, and the new
// end-of-storage is a scale-8 lea. The teardown is inlined here rather than
// going through the vector's own clear, so the allocator pair shows up twice.

struct Rva001E9020Element
{
	unsigned char m_data[8];
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

void __cdecl BfmeRva001E9020Construct(Rva001E9020Element *destination,
	const Rva001E9020Element &value);

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			BfmeRva001E9020Construct(result, *first);
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
		BfmeRva001E9020Construct(result, value);
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
		BfmeRva001E9020Construct(newFinish, value);
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
				BfmeRva001E9020Construct(newFinish, *cur);
				++cur;
				++newFinish;
			}
			while (cur != last);
		}
	}

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

template class vector<Rva001E9020Element, allocator<Rva001E9020Element > >;
}
