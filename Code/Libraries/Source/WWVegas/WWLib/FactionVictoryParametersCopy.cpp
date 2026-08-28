// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME: the out-of-line STLport __copy over FactionVictoryParameters,
// retail 0x001DE760, 99 bytes.  VictorySystem stores these 0x18-byte records
// in its parameter vector; the first member is an AsciiString and the five
// following members are scalar values.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &);

private:
	void *m_data;
};

struct FactionVictoryParameters
{
	AsciiString m_name;
	int m_values[5];
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
	for (Distance count = last - first; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template FactionVictoryParameters *__copy<FactionVictoryParameters *, FactionVictoryParameters *, int>(
	FactionVictoryParameters *, FactionVictoryParameters *, FactionVictoryParameters *,
	const random_access_iterator_tag &, int *);
}
