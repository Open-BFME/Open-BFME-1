// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

typedef unsigned short wchar_t;

namespace _STL
{

class locale
{
public:
	~locale();

private:
	void *m_impl;
};

template <class CharT>
class char_traits {};

template <class CharT, class Traits>
class basic_streambuf;

template <>
class basic_streambuf<char, char_traits<char> >
{
public:
	virtual ~basic_streambuf();

private:
	char m_stdioState[72];
	locale m_locale;
};

template <>
class basic_streambuf<wchar_t, char_traits<wchar_t> >
{
public:
	virtual ~basic_streambuf();

private:
	char m_bufferPointers[24];
	locale m_locale;
};

basic_streambuf<char, char_traits<char> >::~basic_streambuf()
{
}

basic_streambuf<wchar_t, char_traits<wchar_t> >::~basic_streambuf()
{
}

} // namespace _STL
