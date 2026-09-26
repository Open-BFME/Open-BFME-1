// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: STLport vector<pair<ObjectID, ObjectID> > reallocating insert,
// retail 0x00771870, 268 bytes. The name sat on the 5-byte incremental-link
// thunk at 0x00022AF7 and the body it jumps to carried only a machine byte-dump
// row.
//
// The element is 8 bytes -- two enums -- so the size arithmetic shifts the byte
// distance right by three, every copy loop strides by eight, and the new
// end-of-storage is a scale-8 lea. Unlike the trivially copied element types,
// this one keeps its per-element copy out of line: all three phases reach
// _STL::_Construct through the ILT at 0x0001FA1E, and the teardown is the
// vector's own _M_clear through the ILT at 0x0002F4D2 rather than an inline
// allocator call.

enum ObjectID
{
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

void __cdecl BfmeElementConstruct(pair<ObjectID, ObjectID> *destination,
	const pair<ObjectID, ObjectID> &value);

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
	{
		Type *last = _M_finish;
		if (position != last)
		{
			Type *cur = position;
			do
			{
				BfmeElementConstruct(newFinish, *cur);
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

template class vector<pair<ObjectID, ObjectID>, allocator<pair<ObjectID, ObjectID> > >;
}
