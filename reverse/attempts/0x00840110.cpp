// ?uflow@?$basic_streambuf@DV?$char_traits@D@_STL@@@_STL@@MAEHXZ
// partial score=1.0 date=2026-09-04
// cl: /O2 /MD

// Open-BFME5: _STL::basic_streambuf<char>::uflow @ 0x00840110 (35B)
// FILE*-specialized. Currently claimed by placeholder bfmeGetHU.

namespace _STL
{

template <class CharT>
class char_traits {};

struct BfmeFileBuf
{
	char *_ptr;
	int _cnt;
};

template <class CharT, class Traits>
class basic_streambuf;

template <>
class basic_streambuf<char, char_traits<char> >
{
public:
	typedef char char_type;
	typedef int int_type;

protected:
	virtual ~basic_streambuf();
	virtual void *setbuf(char_type *, int);
	virtual void seekoff();
	virtual void seekpos();
	virtual int sync();
	virtual int showmanyc();
	virtual int xsgetn(char_type *s, int n);
	virtual int_type underflow();
	virtual int_type uflow();
	virtual int_type pbackfail(int_type);
	virtual int xsputn(const char_type *s, int n);
	virtual int _M_xsputnc(char_type c, int n);
	virtual int_type overflow(int_type c = -1);

private:
	BfmeFileBuf *_M_get;
	BfmeFileBuf *_M_put;
};

int basic_streambuf<char, char_traits<char> >::uflow()
{
	const int_type eofv = -1;
	int_type c = underflow();
	if (c == eofv)
		return c;
	BfmeFileBuf *get = _M_get;
	--get->_cnt;
	char *p = get->_ptr;
	get->_ptr = p + 1;
	return (unsigned char)*p;
}

} // namespace _STL
