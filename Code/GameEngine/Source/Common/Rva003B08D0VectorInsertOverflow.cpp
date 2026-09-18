// Open-BFME5: STLport vector<T>::_M_insert_overflow for the 32-byte
// Gen_003B1A30 payload vector. The retail body reallocates storage, copies
// the prefix, constructs the inserted run, copies the suffix, destroys the
// old storage, and rewrites the three vector pointers.

struct Gen_t_003b11e0_p32cd
{
	char m_body[ 32 ];
};

struct P6Elem003B1A30;
void __cdecl Bfme003B1A30Construct(P6Elem003B1A30 *, const P6Elem003B1A30 &);
class Gen_003AFDA0 { public: void bfmeDestroy(); };

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
__forceinline void BfmeElementConstruct(Type *destination, const Type &value)
{
	Bfme003B1A30Construct(reinterpret_cast<P6Elem003B1A30 *>(destination), reinterpret_cast<const P6Elem003B1A30 &>(value));
}

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
			newFinish = uninitialized_copy(position, last, newFinish);
	}

	reinterpret_cast<Gen_003AFDA0 *>(this)->bfmeDestroy();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

// ?_M_insert_overflow@?$vector@UGen_t_003b11e0_p32cd@@V?$allocator@UGen_t_003b11e0_p32cd@@@_STL@@@_STL@@IAEXPAUGen_t_003b11e0_p32cd@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Gen_t_003b11e0_p32cd, allocator<Gen_t_003b11e0_p32cd> >;
}
