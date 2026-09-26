// ?open@?$basic_filebuf@GV?$char_traits@G@_STL@@@_STL@@QAEPAV12@HH@Z
// cl: /DNDEBUG /MD /EHsc
namespace _STL {
class _Filebuf_base {
public:
	bool _M_open(int fd, int mode);
	bool _M_write(char* p, int n);
};
template <class T> class char_traits {};
template <class CharT, class Traits>
class basic_filebuf {
public:
	basic_filebuf* open(int fd, int mode);
	bool _M_write(char* p, int n);
private:
	char m_pad[0x54];
	_Filebuf_base _M_base;
};
template <class CharT, class Traits>
basic_filebuf<CharT, Traits>* basic_filebuf<CharT, Traits>::open(int fd, int mode)
{
	return _M_base._M_open(fd, mode) ? this : 0;
}
template <class CharT, class Traits>
bool basic_filebuf<CharT, Traits>::_M_write(char* p, int n)
{
	return _M_base._M_write(p, n);
}
template class basic_filebuf<unsigned short, char_traits<unsigned short> >;
}
