// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 __copy_integer_and_fill specialization for char and
// ostreambuf_iterator<char>, retail 0x00835310. The explicit inlining
// boundaries below reproduce those selected in the original numeric-facet TU.

namespace _STL
{

typedef int ptrdiff_t;
typedef int streamsize;

class ios_base
{
public:
	typedef int fmtflags;
	enum {
		left = 1,
		right = 2,
		internal = 4,
		adjustfield = left | right | internal,
		hex = 0x10,
		basefield = 0x38,
		showbase = 0x200
	};
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
inline OutputIter copy(InputIter first, InputIter last,
	OutputIter output)
{
	random_access_iterator_tag category;
	return __copy(first, last, output, category, (int *)0);
}

// VC7 inlined this random-access copy loop only in the showbase and fallback
// arms; the other arms retained the canonical STLport __copy specialization.
template <class InputIter, class OutputIter>
__forceinline OutputIter copy_through_random_access_helper(InputIter first,
	InputIter last, OutputIter output)
{
	random_access_iterator_tag category;
	return __copy(first, last, output, category, (int *)0);
}

template <class InputIter, class OutputIter>
__forceinline OutputIter copy_inlined_random_access(InputIter first,
	InputIter last, OutputIter output)
{
	ptrdiff_t count = last - first;
	for (; count > 0; --count, ++first, ++output)
		*output = *first;
	return output;
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
OutputIter __cdecl __copy_integer_and_fill(const CharT *buffer,
	ptrdiff_t length, OutputIter output, ios_base::fmtflags flags,
	streamsize width, CharT fill, CharT plus, CharT minus)
{
	if (length >= width)
		return copy(buffer, buffer + length, output);

	ptrdiff_t padding = width - length;
	ios_base::fmtflags direction = flags & ios_base::adjustfield;

	if (direction == ios_base::left)
	{
		output = copy(buffer, buffer + length, output);
		return fill_n(output, padding, fill);
	}
	else if (direction == ios_base::internal && length != 0 &&
		(buffer[0] == plus || buffer[0] == minus))
	{
		*output++ = buffer[0];
		output = fill_n(output, padding, fill);
		return copy_through_random_access_helper(buffer + 1,
			buffer + length, output);
	}
	else if (direction == ios_base::internal && length >= 2 &&
		(flags & ios_base::showbase) &&
		(flags & ios_base::basefield) == ios_base::hex)
	{
		*output++ = buffer[0];
		*output++ = buffer[1];
		output = fill_n(output, padding, fill);
		return copy_inlined_random_access(buffer + 2,
			buffer + length, output);
	}
	else
	{
		output = fill_n(output, padding, fill);
		return copy_inlined_random_access(buffer,
			buffer + length, output);
	}
}

typedef ostreambuf_iterator<char, char_traits<char> > NarrowOutputIter;

template NarrowOutputIter __cdecl
__copy_integer_and_fill<char, NarrowOutputIter>(const char *,
	ptrdiff_t, NarrowOutputIter, ios_base::fmtflags, streamsize,
	char, char, char);

} // namespace _STL
