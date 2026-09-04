// ?_M_xsputnc@?$basic_streambuf@DV?$char_traits@D@_STL@@@_STL@@MAEHDH@Z
// partial score=0.9 date=2026-09-04
// cl: /O2 /MD

// Open-BFME5: _STL::basic_streambuf<char>::_M_xsputnc @ 0x00840200 (178B)
// FILE*-specialized streambuf (STLport 4.5.3).

#include <cstring>

namespace _STL
{

template <class CharT>
class char_traits {};

template <>
class char_traits<char>
{
public:
	typedef int int_type;
	static int_type eof() { return -1; }
	static int_type to_int_type(const char &c) { return (unsigned char)c; }
	static bool eq_int_type(int_type a, int_type b) { return a == b; }
	static char *assign(char *p, size_t n, char c)
	{
		return (char *)memset(p, c, n);
	}
};

struct BfmeFileBuf
{
	char *_ptr;
	int _cnt;
	char *_base;
};

typedef int file_diff_t;

inline char *_FILE_O_next(const BfmeFileBuf *f) { return f->_ptr; }
inline file_diff_t _FILE_O_avail(const BfmeFileBuf *f) { return f->_cnt; }
inline void _FILE_O_bump(BfmeFileBuf *f, int n)
{
	f->_ptr += n;
	f->_cnt -= n;
}

template <class T>
inline const T &(min)(const T &a, const T &b)
{
	return a < b ? a : b;
}

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
	BfmeFileBuf _M_default_get;
	BfmeFileBuf _M_default_put;
};

int basic_streambuf<char, char_traits<char> >::_M_xsputnc(char_type c, int n)
{
	const int_type eofv = -1;
	int result = 0;

	while (result < n)
	{
		if (_FILE_O_avail(_M_put) > 0)
		{
			size_t chunk = (min)((size_t)(n - result), (size_t)_FILE_O_avail(_M_put));
			char_traits<char>::assign(_FILE_O_next(_M_put), chunk, c);
			result += (int)chunk;
			_FILE_O_bump(_M_put, (int)chunk);
		}
		else
		{
			int_type r = this->overflow(char_traits<char>::to_int_type(c));
			if (char_traits<char>::eq_int_type(r, eofv))
				break;
			++result;
		}
	}
	return result;
}

} // namespace _STL
