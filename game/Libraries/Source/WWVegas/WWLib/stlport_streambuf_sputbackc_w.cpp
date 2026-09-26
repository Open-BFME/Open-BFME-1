// ?sputbackc@?$basic_streambuf@GV?$char_traits@G@_STL@@@_STL@@QAEGG@Z
// cl: /DNDEBUG /MD /EHsc
namespace _STL {
template <class T> class char_traits {};
template <class CharT, class Traits>
class basic_streambuf {
public:
	unsigned short sputbackc(unsigned short c);
protected:
	virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
	virtual unsigned short pbackfail(unsigned short c);
private:
	CharT* _M_gbegin;
	CharT* _M_gnext;
};
template <class CharT, class Traits>
unsigned short basic_streambuf<CharT, Traits>::sputbackc(unsigned short c)
{
	if (_M_gbegin < _M_gnext && c == _M_gnext[-1]) {
		--_M_gnext;
		return *_M_gnext;
	}
	return pbackfail(c);
}
template class basic_streambuf<unsigned short, char_traits<unsigned short> >;
}
