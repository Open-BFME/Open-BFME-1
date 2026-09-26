// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// The retail body at 0x001D8410 is STLport vector growth for a 12-byte,
// non-POD AnimSet element. The pin and parseAnimSet caller prove this
// instantiation, while the element's semantic fields remain unnamed.

struct Gen_t_001da8b0_p12cd
{
	int m_words[3];
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

template <class Type1, class Type2>
void __cdecl _Construct(Type1 *destination, const Type2 &value);

class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};

#pragma comment(linker, "/alternatename:?_M_clear@?$vector@UGen_t_001da8b0_p12cd@@V?$allocator@UGen_t_001da8b0_p12cd@@@_STL@@@_STL@@IAEXXZ=?j_0000d0fd@@YAXXZ")

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
__forceinline Type *uninitialized_fill_n(Type *result, unsigned int count,
	const Type &value)
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
			newStart = (Type *)::operator new(bytes);
		else
			newStart = (Type *)__new_alloc::allocate(bytes);
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

template class vector<Gen_t_001da8b0_p12cd,
	allocator<Gen_t_001da8b0_p12cd> >;
}
