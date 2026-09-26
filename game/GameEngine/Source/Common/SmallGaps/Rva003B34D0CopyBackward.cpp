// ??$__copy_backward@PAUGen_t_003b3cf0_p128pod@@PAU1@H@_STL@@YAPAUGen_t_003b3cf0_p128pod@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

class UnicodeString
{
public:
	void set(const UnicodeString &that);

private:
	void *m_data;
};

struct Gen_t_003b3cf0_p128pod
{
	int m_unused0;
	UnicodeString m_a;
	UnicodeString m_b;
	UnicodeString m_c;
	char m_flag;

	Gen_t_003b3cf0_p128pod &operator=(const Gen_t_003b3cf0_p128pod &that)
	{
		m_a.set(that.m_a);
		m_b.set(that.m_b);
		m_c.set(that.m_c);
		m_flag = that.m_flag;
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
	{
		*result = *first;
	}
	return result;
}

template Gen_t_003b3cf0_p128pod *__copy_backward<
	Gen_t_003b3cf0_p128pod *, Gen_t_003b3cf0_p128pod *, int>(
	Gen_t_003b3cf0_p128pod *, Gen_t_003b3cf0_p128pod *,
	Gen_t_003b3cf0_p128pod *, const random_access_iterator_tag &, int *);
}
