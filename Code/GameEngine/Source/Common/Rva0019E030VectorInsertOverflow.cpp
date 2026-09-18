// cl: /O2 /DNDEBUG /MD /EHs-c-

struct Gen_t_0019e270_p12cd
{
	unsigned char m_data[12];
};

void *operator new(unsigned int bytes);

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};

struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Destination, class Source>
void __cdecl _Construct(Destination *destination, const Source &source);

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
		} while (first != last);
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

	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &,
	unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(m_finish - m_start);
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

	Type *newFinish = uninitialized_copy(m_start, position, newStart);

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
		newFinish = uninitialized_copy(position, m_finish, newFinish);

	_M_clear();

	m_finish = newFinish;
	m_start = newStart;
	m_end_of_storage = newStart + length;
}

}

template class _STL::vector<Gen_t_0019e270_p12cd,
	_STL::allocator<Gen_t_0019e270_p12cd> >;
