// cl: /O2 /MD

// Open-BFME5: _STL::basic_streambuf<char>::_M_snextc_aux @ 0x008402D0 (94B)
// FILE*-specialized streambuf (STLport 4.5.3): _M_get at +4.

namespace _STL
{

template <class CharT>
class char_traits {};

struct BfmeFileBuf
{
	char *_ptr;
	int _cnt;
	char *_base;
};

inline char *_FILE_I_begin(BfmeFileBuf *f) { return f->_base; }
inline char *_FILE_I_next(BfmeFileBuf *f) { return f->_ptr; }
inline char *_FILE_I_end(BfmeFileBuf *f) { return f->_ptr + f->_cnt; }
inline int _FILE_I_avail(BfmeFileBuf *f) { return f->_cnt; }
inline void _FILE_I_set(BfmeFileBuf *f, char *begin, char *next, char *end)
{
	f->_base = begin;
	f->_ptr = next;
	f->_cnt = (int)(end - next);
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

	char_type *eback() const { return _FILE_I_begin(_M_get); }
	char_type *gptr() const { return _FILE_I_next(_M_get); }
	char_type *egptr() const { return _FILE_I_end(_M_get); }
	void setg(char_type *gb, char_type *gn, char_type *ge)
	{ _FILE_I_set(_M_get, gb, gn, ge); }

private:
	int_type _M_snextc_aux();

	BfmeFileBuf *_M_get;
	BfmeFileBuf *_M_put;

public:
	int_type sgetc()
	{
		if (_FILE_I_avail(_M_get) > 0)
			return (unsigned char)*_FILE_I_next(_M_get);
		return underflow();
	}
};

int basic_streambuf<char, char_traits<char> >::_M_snextc_aux()
{
	const int_type eofv = -1;
	if (_FILE_I_avail(_M_get) == 0)
	{
		int_type c = uflow();
		if (c == eofv)
			return c;
		return sgetc();
	}
	else
	{
		setg(eback(), egptr(), egptr());
		return underflow();
	}
}

} // namespace _STL
