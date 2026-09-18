// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport vector<unsigned short> reallocating insert, retail
// 0x003C16A0, 282 bytes. The name sat on the 5-byte incremental-link thunk at
// 0x0000791E and the body it jumps to carried only a machine byte-dump row.
//
// The element is 2 bytes: the size arithmetic shifts the byte distance right by
// one, the copy loops stride by two, and the new end-of-storage is formed with
// a scale-2 lea. The allocator pair is the same one every STLport vector body
// reaches -- above 128 bytes the plain block allocator, at or below it the node
// allocator -- and the teardown reaches their deallocating twins.

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);
void __cdecl vectorLargeDeallocate(void *block);
void __cdecl vectorSmallDeallocate(void *block, unsigned int bytes);

struct __true_type {};

template <class Type>
class allocator {};

template <class Type>
inline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			new (result) Type(*first);
			++first;
			++result;
		}
		while (first != last);
	}
	return result;
}

template <class Type>
inline Type *uninitialized_fill_n(Type *result, unsigned int count, const Type &value)
{
	for (; count > 0; --count)
	{
		new (result) Type(value);
		++result;
	}
	return result;
}

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __true_type &, unsigned int fillLength, bool atEnd);

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __true_type &,
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
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n(newFinish, fillLength, value);
	}

	if (!atEnd)
		newFinish = uninitialized_copy(position, _M_finish, newFinish);

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

template class vector<unsigned short, allocator<unsigned short> >;
}

class Rva0000791EVectorOverflowThunk
	: public _STL::vector<unsigned short, _STL::allocator<unsigned short> >
{
public:
	void forward(unsigned short *position, const unsigned short &value,
		const _STL::__true_type &tag, unsigned int fillLength, bool atEnd);
};

void Rva0000791EVectorOverflowThunk::forward(
	unsigned short *position, const unsigned short &value,
	const _STL::__true_type &tag, unsigned int fillLength, bool atEnd)
{
	_M_insert_overflow(position, value, tag, fillLength, atEnd);
}
