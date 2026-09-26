// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport reallocating insert for a 28-byte vector element, retail
// 0x00583330, 342 bytes. The body carried only a machine byte-dump row and no name.
//
// The element type is not recoverable: the only named-shaped callee is the tail
// move's __uninitialized_copy at 0x00581C50, reached through the ILT at 0x00015019,
// and the ledger has no real name for it. So the element is named for the
// address of the body it belongs to and modelled by width.
//
// 28 bytes is what the bytes say: the element is trivially copied, so the two
// leading phases inline into 7-dword rep movsd runs behind the placement-new
// null check while the tail move stays out of line. Retail hands that helper's
// empty dispatch tag the address of its own trailing bool argument rather than
// spending a frame slot on it.

class Rva00583330Element
{
private:
	unsigned char m_data[28];
};

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

struct __false_type
{
};

// The tail move is the one phase retail leaves out of line; it reaches the
// __uninitialized_copy body at 0x00581C50 through the ILT at 0x00015019.
Rva00583330Element *__cdecl BfmeRva00583330TailCopy(
	Rva00583330Element *first, Rva00583330Element *last, Rva00583330Element *result,
	const __false_type &);

template <class Type>
class allocator {};

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
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
__forceinline Type *uninitialized_fill_n(Type *result, unsigned int count, const Type &value)
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
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n(newFinish, fillLength, value);
	}

	if (!atEnd)
		newFinish = BfmeRva00583330TailCopy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

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

template class vector<Rva00583330Element, allocator<Rva00583330Element> >;
}
