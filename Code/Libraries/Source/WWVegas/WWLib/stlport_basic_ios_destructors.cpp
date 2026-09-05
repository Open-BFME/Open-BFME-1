// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

typedef unsigned short wchar_t;

namespace _STL
{

class ios_base
{
public:
	virtual ~ios_base();
};

template <class CharT>
class char_traits {};

template <class CharT, class Traits>
class basic_ios : public ios_base
{
public:
	virtual ~basic_ios();
};

template <class CharT, class Traits>
basic_ios<CharT, Traits>::~basic_ios()
{
}

template class basic_ios<char, char_traits<char> >;
template class basic_ios<wchar_t, char_traits<wchar_t> >;

} // namespace _STL
