// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: the out-of-line body of _STL::__copy over ProductionPrerequisite,
// retail 0x00753280, 99 bytes. The name sat on the 5-byte incremental-link
// thunk at 0x000181A1 and the body it jumps to carried only a machine byte-dump
// row.
//
// The element is 24 bytes and the count is a signed divide-by-twenty-four, so
// the empty range returns the result argument straight off the stack. The
// element layout is the loop itself: StringBase<char>::set on the member at +0,
// a single byte copied at +4, then four dwords from +8 to +0x14 -- so an
// AsciiString, a Bool with its three bytes of padding, and four words.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &);

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	AsciiString m_name;
	bool m_flag;
	int m_words[4];
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

template ProductionPrerequisite *__copy<ProductionPrerequisite *, ProductionPrerequisite *, int>(
	ProductionPrerequisite *, ProductionPrerequisite *, ProductionPrerequisite *,
	const random_access_iterator_tag &, int *);
}
