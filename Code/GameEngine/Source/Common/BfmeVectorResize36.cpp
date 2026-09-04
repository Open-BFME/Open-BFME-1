// cl: /O2

struct Gen_t_0074d9c0_p128pod
{
	char m_bytes[36];
};

namespace _STL
{
template <class Type>
class allocator
{
};

struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *);
}

namespace _STL
{
template <class Type, class Allocator>
class vector
{
public:
	void resize(unsigned n, Type value);
	void _M_fill_insert(Type *pos, unsigned n, const Type &value);
	unsigned size() const { return (unsigned)(m_finish - m_start); }

private:
	Type *m_start;
	Type *m_finish;
	Type *m_end;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::resize(unsigned n, Type value)
{
	if (n < size())
	{
		Type *dest = m_start + n;
		m_finish = _STL::__copy(m_finish, m_finish, dest,
			*reinterpret_cast<_STL::random_access_iterator_tag *>(&n),
			(int *)0);
	}
	else
		_M_fill_insert(m_finish, n - size(), value);
}

template void vector<Gen_t_0074d9c0_p128pod,
	allocator<Gen_t_0074d9c0_p128pod> >::resize(
	unsigned, Gen_t_0074d9c0_p128pod);
}
