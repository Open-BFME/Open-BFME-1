// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Retail identifies this 16-byte STLport vector growth body by its payload
// shape and its pinned construct, allocation, and clear calls.

struct Gen_t_0036a520_p16cd
{
	char m_body[0x10];
};

struct Elem16
{
	char m_body[0x10];
};

void __cdecl gen003685C0(
	Elem16 *destination, const Elem16 *value);

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

class __new_alloc
{
public:
	static void *__cdecl allocate(unsigned int bytes);
};

#pragma comment(linker, "/alternatename:?_M_clear@?$vector@UGen_t_0036a520_p16cd@@V?$allocator@UGen_t_0036a520_p16cd@@@_STL@@@_STL@@IAEXXZ=?_M_clear@?$vector@UGen_t_00369a60_p16cd@@V?$allocator@UGen_t_00369a60_p16cd@@@_STL@@@_STL@@IAEXXZ")

template <class Type>
__forceinline void construct(Type *destination, const Type &value)
{
	gen003685C0(
		reinterpret_cast<Elem16 *>(destination),
		reinterpret_cast<const Elem16 *>(&value));
}

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			construct(result, *first);
			++first;
			++result;
		}
		while (first != last);
	}
	return result;
}

template <class Type>
__forceinline Type *uninitialized_fill_n(
	Type *result, unsigned int count, const Type &value)
{
	for (; count > 0; --count)
	{
		construct(result, value);
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
		construct(newFinish, value);
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

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}
}

template class _STL::vector<Gen_t_0036a520_p16cd,
	_STL::allocator<Gen_t_0036a520_p16cd> >;
