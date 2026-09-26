// cl: /O2 /MD
// STLport 4.5.3 __copy_digits narrow istreambuf_iterator @ 0x00838A20 (184B).

namespace _STL
{

template <class CharT>
class char_traits
{
public:
	static void assign(CharT &d, CharT s) { d = s; }
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

	CharT *_M_start;
	CharT *_M_finish;
	CharT *_M_end_of_storage;

	size_type size() const { return (size_type)(_M_finish - _M_start); }
	void reserve(size_type);

	void push_back(CharT c)
	{
		if (this->_M_finish + 1 == this->_M_end_of_storage)
		{
			size_type __one = 1;
			size_type __old_size = size();
			size_type *__p = &__one;
			if (__old_size >= 1)
				__p = &__old_size;
			reserve(__old_size + *__p);
		}
		this->_M_finish[1] = CharT();
		Traits::assign(*(this->_M_finish), c);
		++this->_M_finish;
	}
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

inline bool __get_fdigit(char &c, const char *)
{
	return c >= '0' && c <= '9';
}

template <class InputIter, class CharT>
bool __copy_digits(
	InputIter &first, InputIter &last,
	basic_string<char, char_traits<char>, allocator<char> > &v,
	const CharT * /*digits*/)
{
	bool ok = false;
	for (; first != last; ++first)
	{
		CharT c = *first;
		if (__get_fdigit(c, 0))
		{
			v.push_back((char)c);
			ok = true;
		}
		else
			break;
	}
	return ok;
}

template bool __copy_digits(
	istreambuf_iterator<char, char_traits<char> > &,
	istreambuf_iterator<char, char_traits<char> > &,
	basic_string<char, char_traits<char>, allocator<char> > &,
	const char *);

} // namespace _STL
