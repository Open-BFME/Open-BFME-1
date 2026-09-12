// ??$__copy_backward@PAUGen_t_003b3da0_p128pod@@PAU1@H@_STL@@YAPAUGen_t_003b3da0_p128pod@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z
// partial score=0.14 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME7: out-of-line STLport copy-backward helper at retail 0x003B3560.
// 32-byte element: five ints at +0/+4/+8/+0xc/+0x10, a byte at +0x14, an
// untouched 7-byte gap, then one more int at +0x1c. See reverse/symbols.csv
// for the pinned callers (__copy_backward_ptrs false_type at 0x003B3DA0).

struct Gen_t_003b3da0_p128pod
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	unsigned char m_f;
	unsigned char m_pad[7];
	int m_g;

	Gen_t_003b3da0_p128pod &operator=(const Gen_t_003b3da0_p128pod &other)
	{
		m_a = other.m_a;
		m_b = other.m_b;
		m_c = other.m_c;
		m_d = other.m_d;
		m_e = other.m_e;
		m_f = other.m_f;
		m_g = other.m_g;
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
	Distance count = last - first;
	if (count >= 4)
	{
		Distance groups = ((count - 4) >> 2) + 1;
		Distance done = groups;
		do
		{
			result[0] = first[0];
			result[1] = first[1];
			result[2] = first[2];
			result[3] = first[3];
			first += 4;
			result += 4;
		} while (--done);
		count -= groups << 2;
	}
	while (count-- > 0)
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

template Gen_t_003b3da0_p128pod *__copy_backward<Gen_t_003b3da0_p128pod *, Gen_t_003b3da0_p128pod *, int>(
	Gen_t_003b3da0_p128pod *, Gen_t_003b3da0_p128pod *, Gen_t_003b3da0_p128pod *,
	const random_access_iterator_tag &, int *);
}
