// cl: /O2 /MD

// Open-BFME5: _STL::basic_streambuf<char> xsgetn @ 0x00840050 (166B)
// and xsputn @ 0x00840150 (172B). FILE*-specialized streambuf.

#include <cstring>

namespace _STL
{

template <class CharT>
class char_traits {};

struct BfmeFileBuf
{
	char *_ptr;
	int _cnt;
};

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
};

int basic_streambuf<char, char_traits<char> >::xsgetn(char_type *s, int n)
{
	int result = 0;
	const int eofv = -1;

	while (result < n)
	{
		BfmeFileBuf *get = _M_get;
		int cnt = get->_cnt;
		if (cnt > 0)
		{
			size_t chunk = (min)((size_t)(n - result), (size_t)cnt);
			if (chunk != 0)
				memcpy(s, get->_ptr, chunk);
			result += (int)chunk;
			s += chunk;
			get = _M_get;
			get->_ptr += chunk;
			get->_cnt -= (int)chunk;
		}
		else
		{
			int_type c = uflow();
			if (c == eofv)
				break;
			*s = (char_type)c;
			++result;
			++s;
		}
	}
	return result;
}

int basic_streambuf<char, char_traits<char> >::xsputn(const char_type *s, int n)
{
	int result = 0;
	const int eofv = -1;

	while (result < n)
	{
		BfmeFileBuf *put = _M_put;
		int cnt = put->_cnt;
		if (cnt > 0)
		{
			size_t chunk = (min)((size_t)(n - result), (size_t)cnt);
			if (chunk != 0)
				memcpy(put->_ptr, s, chunk);
			result += (int)chunk;
			s += chunk;
			put = _M_put;
			put->_ptr += chunk;
			put->_cnt -= (int)chunk;
		}
		else
		{
			int_type c = overflow((unsigned char)*s);
			if (c == eofv)
				break;
			++result;
			++s;
		}
	}
	return result;
}

} // namespace _STL
