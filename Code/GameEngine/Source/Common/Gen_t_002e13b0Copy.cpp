// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// STLport random-access __copy over a 12-byte record {int, AsciiString, char}.
// Retail 0x002E0040, 82 bytes. Magic 0x2AAAAAAB / sar 1 is a 12-byte stride.
// The string member assignment is the shared AsciiString::operator= body.

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

struct Gen_t_002e13b0_p12cd
{
	int a;
	AsciiString name;
	char flag;

	Gen_t_002e13b0_p12cd &operator=(const Gen_t_002e13b0_p12cd &other)
	{
		a = other.a;
		name = other.name;
		flag = other.flag;
		return *this;
	}
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	const random_access_iterator_tag &, Distance *)
{
	for (Distance n = last - first; n > 0; --n)
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

template Gen_t_002e13b0_p12cd *__copy<const Gen_t_002e13b0_p12cd *, Gen_t_002e13b0_p12cd *, int>(
	const Gen_t_002e13b0_p12cd *, const Gen_t_002e13b0_p12cd *, Gen_t_002e13b0_p12cd *,
	const random_access_iterator_tag &, int *);
}
