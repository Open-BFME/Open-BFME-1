// STLport vector growth for the 16-byte payload at retail 0x00199B20.
// The retail copy and clear callees identify this instantiation.

// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

struct Gen_t_0019a890_p16cd
{
	int a[4];
	Gen_t_0019a890_p16cd();
	Gen_t_0019a890_p16cd(const Gen_t_0019a890_p16cd &);
	~Gen_t_0019a890_p16cd();
	Gen_t_0019a890_p16cd &operator=(const Gen_t_0019a890_p16cd &);
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

class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};

template <class Destination, class Source>
void __cdecl _Construct(Destination *destination, const Source &value);

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
			newStart = (Type *)operator new(bytes);
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

#pragma comment(linker, "/alternatename:?_M_clear@?$vector@UGen_t_0019a890_p16cd@@V?$allocator@UGen_t_0019a890_p16cd@@@_STL@@@_STL@@IAEXXZ=?j_000351cf@@YAXXZ")

template class _STL::vector<Gen_t_0019a890_p16cd,
	_STL::allocator<Gen_t_0019a890_p16cd> >;
