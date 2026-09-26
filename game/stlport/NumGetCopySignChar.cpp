// cl: /O2 /MD
// STLport 4.5.3 __copy_sign<istreambuf_iterator<char>, char> @ 0x008388A0 (86B).
// equal and _M_getc stay out-of-line (retail TU shape); _M_bumpc is inlined.

namespace _STL
{

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
	void push_back(CharT);
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	int sbumpc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	typedef CharT char_type;

	bool equal(const istreambuf_iterator &) const;
	void _M_getc() const;

	char_type operator*() const
	{
		_M_getc();
		return _M_c;
	}

	istreambuf_iterator &operator++()
	{
		_M_bumpc();
		return *this;
	}

private:
	void _M_bumpc()
	{
		_M_buf->sbumpc();
		_M_have_c = 0;
	}

	basic_streambuf<CharT, Traits> *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

inline bool operator!=(
	const istreambuf_iterator<char, char_traits<char> > &a,
	const istreambuf_iterator<char, char_traits<char> > &b)
{
	return !a.equal(b);
}

template <class InputIter, class CharT>
InputIter __copy_sign(
	InputIter first, InputIter last,
	basic_string<char, char_traits<char>, allocator<char> > &v,
	CharT xplus, CharT xminus)
{
	if (first != last)
	{
		CharT c = *first;
		if (c == xplus)
			++first;
		else if (c == xminus)
		{
			v.push_back('-');
			++first;
		}
	}
	return first;
}

template istreambuf_iterator<char, char_traits<char> > __copy_sign(
	istreambuf_iterator<char, char_traits<char> >,
	istreambuf_iterator<char, char_traits<char> >,
	basic_string<char, char_traits<char>, allocator<char> > &,
	char, char);

} // namespace _STL
