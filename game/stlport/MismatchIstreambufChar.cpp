// cl: /O2 /MD
// STLport 4.5.3 mismatch(istreambuf_iterator<char>, const char*) @ 0x0083D640 (95B).

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
	const istreambuf_iterator<char, char_traits<char> > &a,
	const istreambuf_iterator<char, char_traits<char> > &b)
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

template pair<istreambuf_iterator<char, char_traits<char> >, const char *> mismatch(
	istreambuf_iterator<char, char_traits<char> >,
	istreambuf_iterator<char, char_traits<char> >,
	const char *);

} // namespace _STL
