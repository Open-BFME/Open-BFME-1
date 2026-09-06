// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME: STLport vector insertion body, retail 0x003B0D00, 235 bytes.

struct Gen_t_003b4b60_p16cd
{
	void *m_vtable;
	int m_at04;
	unsigned char m_at08;
	char m_pad09[3];
	int m_at0c;
};

struct Gen_t_003acce0_p16cd
{
	void *m_vtable;
	int m_at04;
	unsigned char m_at08;
	char m_pad09[3];
	int m_at0c;
};

struct Gen_t_003acd30_p16cd
{
	void *m_vtable;
	int m_at04;
	unsigned char m_at08;
	char m_pad09[3];
	int m_at0c;
};

extern int R2Data010EC760;

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

template <class Input, class Output>
Output __uninitialized_copy(Input first, Input last, Output result,
	const __false_type &tag);

template <class Output, class Size, class Value>
Output __uninitialized_fill_n(Output result, Size count, const Value &value,
	const __false_type &tag);

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &tag, unsigned int fillLength, bool atEnd);
	void _M_clear();

	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &tag,
	unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(
		*reinterpret_cast<Type **>((char *)this + 4) -
		*reinterpret_cast<Type **>((char *)this));
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

	Type *newFinish = reinterpret_cast<Type *>(
		__uninitialized_copy(
			reinterpret_cast<const Gen_t_003acce0_p16cd *>(
				m_start),
			reinterpret_cast<const Gen_t_003acce0_p16cd *>(
				position),
			reinterpret_cast<Gen_t_003acce0_p16cd *>(newStart),
			reinterpret_cast<const __false_type &>(atEnd)));

	if (fillLength == 1)
	{
		if (newFinish != 0)
		{
			newFinish->m_vtable = &R2Data010EC760;
			newFinish->m_at04 = value.m_at04;
			newFinish->m_at08 = value.m_at08;
			newFinish->m_at0c = value.m_at0c;
		}
		++newFinish;
	}
	else
	{
		newFinish = reinterpret_cast<Type *>(
			__uninitialized_fill_n(
				reinterpret_cast<Gen_t_003acd30_p16cd *>(newFinish), fillLength,
				*reinterpret_cast<const Gen_t_003acd30_p16cd *>(&value),
				reinterpret_cast<const __false_type &>(atEnd)));
	}

	if (!atEnd)
		newFinish = reinterpret_cast<Type *>(
			__uninitialized_copy(
				reinterpret_cast<const Gen_t_003acce0_p16cd *>(
					position),
				reinterpret_cast<const Gen_t_003acce0_p16cd *>(
					m_finish),
				reinterpret_cast<Gen_t_003acce0_p16cd *>(newFinish),
				reinterpret_cast<const __false_type &>(atEnd)));

	_M_clear();

	m_start = newStart;
	m_finish = newFinish;
	m_endOfStorage = newStart + length;
}
}

template class _STL::vector<Gen_t_003b4b60_p16cd,
	_STL::allocator<Gen_t_003b4b60_p16cd> >;
