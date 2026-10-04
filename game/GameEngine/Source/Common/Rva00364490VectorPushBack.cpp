// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

struct Rva00364490Element
{
	int m_value;
};

// Retail ILT thunk 0x0002634b: _STL::vector<>::_M_insert_overflow is called
// through it, so the call is written against the thunk directly.
extern void j_0002634b();

namespace _STL
{
struct __false_type
{
};

template <typename Type>
class allocator
{
};

template <typename Type, typename Allocator>
class vector
{
public:
	void push_back(const Type *value);

protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};

template <typename Type, typename Allocator>
void vector<Type, Allocator>::push_back(const Type *value)
{
	if (m_finish != m_end_of_storage)
	{
		if (m_finish != 0)
			*m_finish = *value;
		++m_finish;
	}
	else
	{
		typedef void (vector<Type, Allocator>::*InsertOverflow)(
			Type *, const Type &, const __false_type &, unsigned int, bool);
		union { void (*fn)(); InsertOverflow call; } u = { j_0002634b };
		(this->*u.call)(m_finish, *value,
			reinterpret_cast<const __false_type &>(value), 1, true);
	}
}
}

template class _STL::vector<Rva00364490Element,
	_STL::allocator<Rva00364490Element> >;
