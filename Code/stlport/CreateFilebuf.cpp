// cl: /O2 /EHsc /MD
// stlport
// STLport 4.5.3 _Stl_create_filebuf / _Stl_create_wfilebuf (src/iostream.cpp).

struct _iobuf {
	char *_ptr;
	int _cnt;
	char *_base;
	int _flag;
	int _file;
	int _charbuf;
	int _bufsiz;
	char *_tmpfname;
};
typedef struct _iobuf FILE;

namespace _STL {

class ios_base {
public:
	typedef int openmode;
};

class _Filebuf_base {
public:
	bool _M_open(int file_no, int mode);
	bool __is_open() const { return _M_is_open != 0; }

private:
	void *_M_file_id;
	void *_M_view_id;
	int _M_openmode;
	unsigned char _M_is_open;
	unsigned char _M_should_close;
	unsigned char _M_regular_file;
	unsigned char _M_pad;
};

inline int _FILE_fd(FILE *f) { return f->_file; }

template <class CharT> class char_traits {};

template <class CharT, class Traits>
class basic_filebuf {};

// Narrow: vptr + pad -> _M_base at +0x54; total size 0xB4.
template <>
class basic_filebuf<char, char_traits<char> > {
public:
	basic_filebuf();
	virtual ~basic_filebuf();

	bool is_open() const { return _M_base.__is_open(); }

	basic_filebuf *_M_open(int fd, ios_base::openmode mode)
	{
		return _M_base._M_open(fd, mode) ? this : 0;
	}

private:
	char m_streambuf[0x50];
	_Filebuf_base _M_base;
	char m_tail[0xB4 - 0x54 - sizeof(_Filebuf_base)];
};

// Wide (G): vptr + pad -> _M_base at +0x24; total size 0x8C.
template <>
class basic_filebuf<unsigned short, char_traits<unsigned short> > {
public:
	basic_filebuf();
	virtual ~basic_filebuf();

	bool is_open() const { return _M_base.__is_open(); }

	basic_filebuf *_M_open(int fd, ios_base::openmode mode)
	{
		return _M_base._M_open(fd, mode) ? this : 0;
	}

private:
	char m_streambuf[0x20];
	_Filebuf_base _M_base;
	char m_tail[0x8C - 0x24 - sizeof(_Filebuf_base)];
};

typedef basic_filebuf<char, char_traits<char> > filebuf;
typedef basic_filebuf<unsigned short, char_traits<unsigned short> > wfilebuf;

filebuf *_Stl_create_filebuf(FILE *f, ios_base::openmode mode)
{
	filebuf *result = new filebuf();
	result->_M_open(_FILE_fd(f), mode);
	if (!result->is_open()) {
		delete result;
		result = 0;
	}
	return result;
}

wfilebuf *_Stl_create_wfilebuf(FILE *f, ios_base::openmode mode)
{
	wfilebuf *result = new wfilebuf();
	result->_M_open(_FILE_fd(f), mode);
	if (!result->is_open()) {
		delete result;
		result = 0;
	}
	return result;
}

} // namespace _STL
