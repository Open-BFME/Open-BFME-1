// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 narrow __copy_float_and_fill specialization.
// Retail address: 0x0083B9B0, size: 300 bytes.

namespace _STL
{

typedef int ptrdiff_t;
typedef int streamsize;

class ios_base
{
public:
	typedef int fmtflags;
	enum { left = 1, right = 2, internal = 4,
		adjustfield = left | right | internal };
};

template <class CharT> class char_traits {};

template <class CharT, class Traits>
class ostreambuf_iterator
{
public:
	ostreambuf_iterator &operator=(CharT);
	ostreambuf_iterator &operator*() { return *this; }
	ostreambuf_iterator &operator++() { return *this; }
	ostreambuf_iterator &operator++(int) { return *this; }

private:
	void *m_buffer;
	bool m_ok;
};

struct random_access_iterator_tag {};

template <class InputIter, class OutputIter, class Distance>
OutputIter __cdecl __copy(InputIter, InputIter, OutputIter,
	const random_access_iterator_tag &, Distance *);

template <class InputIter, class OutputIter>
__forceinline OutputIter copy(InputIter first, InputIter last,
	OutputIter output)
{
	random_access_iterator_tag category;
	return __copy(first, last, output, category, (int *)0);
}

template <class OutputIter, class Size, class Value>
__forceinline OutputIter fill_n(OutputIter output, Size count,
	const Value &value)
{
	for (; count > 0; --count, ++output)
		*output = value;
	return output;
}

template <class CharT, class OutputIter>
OutputIter __cdecl __copy_float_and_fill(
	const CharT *first, const CharT *last, OutputIter output,
	ios_base::fmtflags flags, streamsize width, CharT fill,
	CharT plus, CharT minus)
{
	if (width <= last - first)
		return copy(first, last, output);
	else
	{
		streamsize padding = width - (last - first);
		ios_base::fmtflags direction = flags & ios_base::adjustfield;
		if (direction == ios_base::left)
		{
			OutputIter result = copy(first, last, output);
			return fill_n(result, padding, fill);
		}
		else if (direction == ios_base::internal && first != last &&
			(*first == plus || *first == minus))
		{
			*output++ = *first++;
			OutputIter result = output;
			result = fill_n(result, padding, fill);
			return copy(first, last, result);
		}
		else
		{
			OutputIter result = fill_n(output, padding, fill);
			return copy(first, last, result);
		}
	}
}

typedef ostreambuf_iterator<char, char_traits<char> >
	BfmeNarrowFloatFillIterator;

template BfmeNarrowFloatFillIterator __cdecl
__copy_float_and_fill<char, BfmeNarrowFloatFillIterator>(
	const char *, const char *, BfmeNarrowFloatFillIterator,
	ios_base::fmtflags, streamsize, char, char, char);

} // namespace _STL
