// ??$__copy_backward@PAUGen_t_007762a0_p128pod@@PAU1@H@_STL@@YAPAUGen_t_007762a0_p128pod@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z
// partial score=0.49 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

namespace _STL
{
struct random_access_iterator_tag
{
};
}

struct Gen00774970Range
{
	int *m_begin;
	int *m_end;
	int *m_capacity;
	void assign(int *, int *, const _STL::random_access_iterator_tag &);
};

struct Gen_t_007762a0_p128pod
{
	Gen00774970Range m_first;
	Gen00774970Range m_second;
	Gen00774970Range m_third;
	int m_tail[2];

	Gen_t_007762a0_p128pod &operator=(const Gen_t_007762a0_p128pod &other)
	{
		_STL::random_access_iterator_tag category;
		if (&other.m_first != &m_first)
			m_first.assign(other.m_first.m_begin, other.m_first.m_end, category);
		if (&other.m_second != &m_second)
			m_second.assign(other.m_second.m_begin, other.m_second.m_end, category);
		if (&other.m_third != &m_third)
			m_third.assign(other.m_third.m_begin, other.m_third.m_end, category);
		m_tail[0] = other.m_tail[0];
		m_tail[1] = other.m_tail[1];
		return *this;
	}
};

namespace _STL
{
template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy_backward(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0;
		--count, ++first, ++result)
		*result = *first;
	return result;
}

template Gen_t_007762a0_p128pod *__copy_backward<
	Gen_t_007762a0_p128pod *, Gen_t_007762a0_p128pod *, int>(
	Gen_t_007762a0_p128pod *, Gen_t_007762a0_p128pod *,
	Gen_t_007762a0_p128pod *, const random_access_iterator_tag &, int *);
}
