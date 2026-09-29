// cl: /O2 /MD
// STLport 4.5.3 mismatch(istreambuf_iterator<unsigned short>, const unsigned short*)
// @ 0x0083E420 (99B), and money_get's __get_string over the same types
// @ 0x00848690 (75B), whose one call is that mismatch. Retail without
// /Zc:wchar_t (mangling G).

namespace _STL
{

template <class CharT>
class char_traits
{
};

template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
	pair(const T1 &a, const T2 &b) : first(a), second(b) {}
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
		_M_buf->sbumpc();
		_M_have_c = 0;
		return *this;
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

template <class InputIter1, class InputIter2>
pair<InputIter1, InputIter2> mismatch(
	InputIter1 first1, InputIter1 last1, InputIter2 first2)
{
	while (first1 != last1 && *first1 == *first2)
	{
		++first1;
		++first2;
	}
	return pair<InputIter1, InputIter2>(first1, first2);
}

template pair<istreambuf_iterator<unsigned short, char_traits<unsigned short> >, const unsigned short *> mismatch(
	istreambuf_iterator<unsigned short, char_traits<unsigned short> >,
	istreambuf_iterator<unsigned short, char_traits<unsigned short> >,
	const unsigned short *);

template <class T1, class T2>
inline pair<T1, T2> make_pair(const T1 &a, const T2 &b)
{
	return pair<T1, T2>(a, b);
}

// money_get's helper, _monetary.c: match a punctuation string at the input.
template <class InIt1, class InIt2>
pair<InIt1, bool> __get_string(InIt1 first, InIt1 last, InIt2 str_first, InIt2 str_last)
{
	pair<InIt1, InIt2> pr = mismatch(first, last, str_first);
	return make_pair(pr.first, pr.second == str_last);
}

template pair<istreambuf_iterator<unsigned short, char_traits<unsigned short> >, bool> __get_string(
	istreambuf_iterator<unsigned short, char_traits<unsigned short> >,
	istreambuf_iterator<unsigned short, char_traits<unsigned short> >,
	const unsigned short *, const unsigned short *);

} // namespace _STL
