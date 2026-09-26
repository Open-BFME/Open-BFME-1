// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

struct Rva00364490Element
{
	int m_value;
};

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
		_M_insert_overflow(m_finish, *value,
			reinterpret_cast<const __false_type &>(value), 1, true);
	}
}
}

#pragma comment(linker, "/alternatename:?_M_insert_overflow@?$vector@URva00364490Element@@V?$allocator@URva00364490Element@@@_STL@@@_STL@@IAEXPAURva00364490Element@@ABU3@ABU__false_type@2@I_N@Z=?j_0002634b@@YAXXZ")

template class _STL::vector<Rva00364490Element,
	_STL::allocator<Rva00364490Element> >;
