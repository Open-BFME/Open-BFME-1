// cl: /O2 /Ob0 /EHsc /MD

// Open-BFME5: _STL::basic_ios<char>::basic_ios(streambuf*) at 0x0083FA80
// (87 bytes) and the wchar twin at 0x0083FAE0 (88 bytes). Both call
// ios_base's constructor, zero fill/streambuf/tie, reseat the vptr, then
// call init. The char fill store is one byte; the wchar store is two.

namespace _STL
{

class ios_base
{
protected:
	ios_base();
	virtual ~ios_base();

private:
	char m_pad[0x50];
};

template <class CharT>
class char_traits {};

template <class CharT, class Traits>
class basic_streambuf {};

template <class CharT, class Traits>
class basic_ios : public ios_base
{
public:
	explicit basic_ios(basic_streambuf<CharT, Traits> *sb);

protected:
	void init(basic_streambuf<CharT, Traits> *sb);

private:
	CharT _M_fill;
	basic_streambuf<CharT, Traits> *_M_streambuf;
	void *_M_tied_ostream;
};

template <class CharT, class Traits>
basic_ios<CharT, Traits>::basic_ios(basic_streambuf<CharT, Traits> *sb)
	: ios_base(),
	  _M_fill(CharT()),
	  _M_streambuf(0),
	  _M_tied_ostream(0)
{
	init(sb);
}

template basic_ios<char, char_traits<char> >::basic_ios(basic_streambuf<char, char_traits<char> > *);
template basic_ios<unsigned short, char_traits<unsigned short> >::basic_ios(basic_streambuf<unsigned short, char_traits<unsigned short> > *);

}
