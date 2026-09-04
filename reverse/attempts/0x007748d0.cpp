// ??$__copy@PAUGen_t_00777e90_p32cd@@PAU1@H@_STL@@YAPAUGen_t_00777e90_p32cd@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z
// partial score=0.976 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: out-of-line STLport range copy at retail 0x007748D0.

namespace _STL
{
struct __declspec(align(4)) random_access_iterator_tag
{
};
}

struct Gen007748D0Range
{
	int *m_begin;
	int *m_end;
	int *m_capacity;
	void assign(int *first, int *last,
		const _STL::random_access_iterator_tag &category);
};

struct Gen_t_00777e90_p32cd
{
	struct Tail3
	{
		int words[3];
	};

	int m_first;
	Gen007748D0Range m_range;
	Tail3 m_tail;
	int m_last;

	Gen_t_00777e90_p32cd &operator=(const Gen_t_00777e90_p32cd &other)
	{
		const _STL::random_access_iterator_tag category =
			_STL::random_access_iterator_tag();
		m_first = other.m_first;
		if (&other.m_range != &m_range)
		{
			m_range.assign(other.m_range.m_begin, other.m_range.m_end, category);
		}
		m_tail = other.m_tail;
		m_last = other.m_last;
		return *this;
	}
};

namespace _STL
{
template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator volatile last,
	OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0;
		--count, ++first, ++result)
		*result = *first;
	return result;
}

template Gen_t_00777e90_p32cd *__copy<Gen_t_00777e90_p32cd *,
	Gen_t_00777e90_p32cd *, int>(Gen_t_00777e90_p32cd *,
	Gen_t_00777e90_p32cd *, Gen_t_00777e90_p32cd *,
	const random_access_iterator_tag &, int *);
}
