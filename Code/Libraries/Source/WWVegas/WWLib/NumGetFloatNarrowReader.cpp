// cl: /O2 /MD
// stlport
// STLport 4.5.3 _M_read_float<istreambuf_iterator<char>> at 0x00838670 (419B).
//
// This is the narrow counterpart of NumGetFloatWideReader.cpp.  The narrow
// STLport _Initialize_get_float overload uses literal ASCII atoms, so the
// temporary locale returned by getloc is retained for the retail lifetime
// shape but no ctype facet dispatch is needed here.

#define _STLP_BEGIN_NAMESPACE namespace _STL {
#define _STLP_END_NAMESPACE }
#define _STLP_CALL __cdecl

_STLP_BEGIN_NAMESPACE

template <class CharT>
class char_traits
{
};

template <class CharT>
class allocator
{
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;

	CharT *m_start;
	CharT *m_finish;
	CharT *m_end_of_storage;

	size_type size() const { return (size_type)(m_finish - m_start); }
	void push_back(CharT);
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class _Locale_impl
{
public:
	virtual ~_Locale_impl() __declspec(nothrow);
	virtual void add_reference() __declspec(nothrow);
	virtual void release_reference() __declspec(nothrow);
};

class locale
{
public:
	class facet
	{
	public:
		virtual ~facet();
	};

	~locale() __declspec(nothrow)
	{
		m_impl->release_reference();
	}

	_Locale_impl *m_impl;
};

template <class CharT>
class numpunct : public locale::facet
{
public:
	CharT decimal_point() const { return do_decimal_point(); }
	CharT thousands_sep() const { return do_thousands_sep(); }

protected:
	virtual CharT do_decimal_point() const;
	virtual CharT do_thousands_sep() const;
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	int sbumpc();
};

class ios_base
{
public:
	typedef int iostate;

	virtual ~ios_base();
	locale getloc() const;
	const locale::facet *_M_numpunct_facet() const
	{
		return m_cached_numpunct;
	}
	const string &_M_grouping() const { return m_cached_grouping; }

private:
	char m_prefix[0x40];
	locale::facet *m_cached_numpunct;
	string m_cached_grouping;
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	typedef CharT char_type;

	istreambuf_iterator(basic_streambuf<CharT, Traits> * = 0);
	bool equal(const istreambuf_iterator &other) const;
	void _M_getc() const;

	char_type operator*() const
	{
		_M_getc();
		return m_c;
	}

	istreambuf_iterator &operator++()
	{
		m_buf->sbumpc();
		m_have_c = 0;
		return *this;
	}

	basic_streambuf<CharT, Traits> *m_buf;
	mutable CharT m_c;
	mutable unsigned char m_eof;
	mutable unsigned char m_have_c;
};

template <class CharT, class Traits>
inline bool operator!=(const istreambuf_iterator<CharT, Traits> &left,
	const istreambuf_iterator<CharT, Traits> &right)
{
	return !left.equal(right);
}

template <class InputIter, class CharT>
InputIter _STLP_CALL __copy_sign(
	InputIter first, InputIter last,
	string &value, CharT xplus, CharT xminus);

template <class InputIter, class CharT>
bool _STLP_CALL __copy_digits(
	InputIter &first, InputIter &last,
	string &value, const CharT *digits);

template <class InputIter, class CharT>
bool _STLP_CALL __copy_grouped_digits(
	InputIter &first, InputIter &last,
	string &value, const CharT *digits, CharT separator,
	const string &grouping, bool &grouping_ok);

template <class InputIter, class CharT>
__declspec(nothrow) bool _STLP_CALL _M_read_float(
	string &buffer, InputIter &input, InputIter &end,
	ios_base &stream, CharT *)
{
	bool digits_before_dot;
	bool digits_after_dot = false;
	bool ok;
	bool grouping_ok = true;
	volatile char padding[8];

	// The narrow STLport overload obtains and immediately releases this
	// locale temporary, even though narrow atom initialization needs no facet.
	{
		locale narrow_locale = stream.getloc();
	}

	const numpunct<CharT> &np =
		*(const numpunct<CharT> *)stream._M_numpunct_facet();
	const string &grouping = stream._M_grouping();

	CharT dot = np.decimal_point();
	CharT separator = np.thousands_sep();
	CharT digits[10];
	CharT xplus;
	CharT xminus;
	CharT pow_e;
	CharT pow_E;

	xplus = '+';
	xminus = '-';
	pow_e = 'e';
	pow_E = 'E';
	// The narrow helper bodies prove that this array is not read: the
	// __copy_digits implementation ignores its parameter, and grouped parsing
	// reaches the same __get_fdigit predicate after separator handling.

	input = __copy_sign(input, end, buffer, xplus, xminus);

	if (grouping.size() != 0)
		digits_before_dot = __copy_grouped_digits(
			input, end, buffer, digits, separator, grouping, grouping_ok);
	else
		digits_before_dot = __copy_digits(input, end, buffer, digits);

	if (input != end && *input == dot)
	{
		buffer.push_back('.');
		++input;
		digits_after_dot = __copy_digits(input, end, buffer, digits);
	}

	ok = digits_before_dot || digits_after_dot;

	if (ok)
	{
		if (input.m_buf)
			input._M_getc();
		if (end.m_buf)
			end._M_getc();
		if (input.m_eof != end.m_eof)
		{
			if (*input == pow_e || *input == pow_E)
			{
				buffer.push_back('e');
				++input;
				input = __copy_sign(input, end, buffer, xplus, xminus);
				ok = __copy_digits(input, end, buffer, digits);
			}
		}
	}

	return ok;
}

typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;

template bool _M_read_float<NarrowIterator, char>(
	string &, NarrowIterator &, NarrowIterator &, ios_base &, char *);

_STLP_END_NAMESPACE
