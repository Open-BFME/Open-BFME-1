// cl: /O2 /MD
// STLport 4.5.3 __copy_sign<istreambuf_iterator<unsigned short>, unsigned short>
// @ 0x0083A780 (89B). Retail built without /Zc:wchar_t (mangling G).

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
	unsigned short sbumpc();
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
	const istreambuf_iterator<unsigned short, char_traits<unsigned short> > &a,
	const istreambuf_iterator<unsigned short, char_traits<unsigned short> > &b)
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

template istreambuf_iterator<unsigned short, char_traits<unsigned short> > __copy_sign(
	istreambuf_iterator<unsigned short, char_traits<unsigned short> >,
	istreambuf_iterator<unsigned short, char_traits<unsigned short> >,
	basic_string<char, char_traits<char>, allocator<char> > &,
	unsigned short, unsigned short);

} // namespace _STL
