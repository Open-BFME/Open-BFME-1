// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME7: out-of-line STLport copy-backward helper at retail 0x003AECC0.
// Byte-identical near-twin of the pinned 0x003B3720 instantiation (same
// 20-byte element shape, same folded UnicodeString::set callee 0x00887C90):
// offset0 field untouched by the generated operator=, two ints at +4/+8, an
// embedded UnicodeString at +0xc, a bool at +0x10, stride 0x14.

class UnicodeString
{
	void *m_data;
public:
	void set(const UnicodeString &);
};

struct Gen_t_003aecc0_p128pod
{
	int m_pad0;
	int m_a;
	int m_b;
	UnicodeString m_str;
	bool m_flag;

	Gen_t_003aecc0_p128pod &operator=(const Gen_t_003aecc0_p128pod &other)
	{
		m_a = other.m_a;
		m_b = other.m_b;
		m_str.set(other.m_str);
		m_flag = other.m_flag;
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

template Gen_t_003aecc0_p128pod *__copy_backward<Gen_t_003aecc0_p128pod *, Gen_t_003aecc0_p128pod *, int>(
	Gen_t_003aecc0_p128pod *, Gen_t_003aecc0_p128pod *, Gen_t_003aecc0_p128pod *,
	const random_access_iterator_tag &, int *);
}
