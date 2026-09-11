// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 narrow __put_integer specialization, retail 0x00835230.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *, const void *,
	unsigned int);

namespace _STL
{

typedef int ptrdiff_t;
typedef int streamsize;

template <class CharT> class char_traits {};
template <class ValueT> class allocator {};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	bool empty() const { return m_begin == m_end; }

private:
	CharT *m_begin;
	CharT *m_end;
	CharT *m_capacity;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

template <class CharT>
class numpunct
{
public:
	virtual void slot0() = 0;
	virtual CharT decimal_point() const = 0;
	virtual CharT thousands_sep() const = 0;
};

class ios_base
{
public:
	typedef int fmtflags;
	enum {
		left = 1,
		right = 2,
		internal = 4,
		adjustfield = left | right | internal,
		oct = 0x20,
		hex = 0x10,
		basefield = 0x38,
		showbase = 0x200
	};

	void *_M_numpunct_facet() const { return m_numpunct; }
	const string &_M_grouping() const { return m_grouping; }
	streamsize width(streamsize value)
	{
		streamsize old = m_width;
		m_width = value;
		return old;
	}

private:
	char m_padding0[0x1C];
	streamsize m_width;
	char m_padding1[0x24];
	numpunct<char> *m_numpunct;
	string m_grouping;
};

template <class CharT, class Traits>
class ostreambuf_iterator
{
private:
	void *m_buffer;
	bool m_ok;
};

struct __true_type {};

template <class CharT, class OutputIter>
OutputIter __cdecl __copy_integer_and_fill(const CharT *, ptrdiff_t,
	OutputIter, ios_base::fmtflags, streamsize, CharT, CharT, CharT);

ptrdiff_t __cdecl __insert_grouping(char *, char *, const string &,
	char, char, char, int);

// STLport keeps this specialization out of line in the original numeric TU.
// Besides being the ILT-routed helper called below, its visible body makes the
// caller reuse the empty tag's incoming stack slot exactly as retail does.
template <class InputIter, class OutputIter>
__declspec(noinline) OutputIter __cdecl __copy_aux(InputIter first,
	InputIter last, OutputIter output, const __true_type &)
{
	return (last == first) ? output :
		(OutputIter)((char *)memmove(output, first,
			(const char *)last - (const char *)first) +
			((const char *)last - (const char *)first));
}

template <class InputIter, class OutputIter>
inline OutputIter copy(InputIter first, InputIter last, OutputIter output)
{
	__true_type trivial_copy;
	return __copy_aux(first, last, output, trivial_copy);
}

template <class OutputIter>
OutputIter __cdecl __put_integer(char *buffer, char *end,
	OutputIter output, ios_base &stream, ios_base::fmtflags flags,
	char fill)
{
	ptrdiff_t length = end - buffer;
	const numpunct<char> &punct =
		*(const numpunct<char> *)stream._M_numpunct_facet();
	const string &grouping = stream._M_grouping();

	if (!grouping.empty())
	{
		int base_chars;
		if (flags & ios_base::showbase)
		{
			switch (flags & ios_base::basefield)
			{
			case ios_base::hex:
				base_chars = 2;
				break;
			case ios_base::oct:
				base_chars = 1;
				break;
			default:
				base_chars = 0;
			}
		}
		else
		{
			base_chars = 0;
		}

		char grouped_buffer[64];
		copy(buffer, end, (char *)grouped_buffer);
		buffer = grouped_buffer;
		end = grouped_buffer + length;
		length = __insert_grouping(buffer, end, grouping,
			punct.thousands_sep(), '+', '-', base_chars);
	}

	return __copy_integer_and_fill(buffer, length, output, flags,
		stream.width(0), fill, '+', '-');
}

typedef ostreambuf_iterator<char, char_traits<char> > NarrowOutputIter;

template NarrowOutputIter __cdecl __put_integer<NarrowOutputIter>(
	char *, char *, NarrowOutputIter, ios_base &, ios_base::fmtflags, char);

} // namespace _STL
