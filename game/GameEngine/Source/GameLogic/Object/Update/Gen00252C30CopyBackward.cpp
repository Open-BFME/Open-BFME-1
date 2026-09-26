// cl: /DNDEBUG /MD /EHsc
// Open-BFME: STLport __copy_backward for the 0x2C-byte element whose copy
// ctor landed at 0x00252A50. Random-access form copies count elements forward.

class Rva0076F980Mid
{
public:
	Rva0076F980Mid &operator=(const Rva0076F980Mid &other);
	int a[3];
};

struct Gen00252C30Pod12
{
	int a[3];
};

struct Gen_t_00252ce0_p128pod
{
	int m_key;
	Rva0076F980Mid m_inner;
	int m_mid;
	Gen00252C30Pod12 m_block14;
	Gen00252C30Pod12 m_block20;

	Gen_t_00252ce0_p128pod &operator=(const Gen_t_00252ce0_p128pod &other)
	{
		m_key = other.m_key;
		m_inner = other.m_inner;
		m_mid = other.m_mid;
		m_block14 = other.m_block14;
		m_block20 = other.m_block20;
		return *this;
	}
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy_backward(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template Gen_t_00252ce0_p128pod *__copy_backward<Gen_t_00252ce0_p128pod *, Gen_t_00252ce0_p128pod *, int>(
	Gen_t_00252ce0_p128pod *, Gen_t_00252ce0_p128pod *, Gen_t_00252ce0_p128pod *,
	const random_access_iterator_tag &, int *);
}
