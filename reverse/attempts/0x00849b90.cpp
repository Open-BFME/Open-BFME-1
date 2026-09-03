// ?seekpos@stdio_streambuf_base@_SgI@@MAE?AV?$fpos@H@_STL@@V34@H@Z
// partial score=0.97 date=2026-09-03
// cl: /O2 /EHsc /MD
// STLport 4.5.3 stdio_streambuf_base::seekpos (src/stdio_streambuf.cpp).
// FILE* lives at +0x54 after the basic_streambuf<char> subobject.
// 81/81; only ecx vs edx on pos._M_st copy. Register-allocation wall.

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
typedef __int64 fpos_t;
typedef long streamoff;
typedef int mbstate_t;

extern "C" {
	__declspec(dllimport) int __cdecl fsetpos(FILE *, const fpos_t *);
}

namespace _STL {

template <class StateT> class fpos
{
public:
	fpos(streamoff pos) : _M_pos(pos), _M_st(0) {}
	fpos() : _M_pos(0), _M_st(0) {}
	operator streamoff() const { return _M_pos; }
	streamoff _M_pos;
	StateT _M_st;
};

}

namespace _SgI {

class stdio_streambuf_base {
protected:
	virtual _STL::fpos<mbstate_t> seekpos(_STL::fpos<mbstate_t> pos, int mode);

private:
	char m_streambuf[0x50];
	FILE *_M_file;
};

_STL::fpos<mbstate_t> stdio_streambuf_base::seekpos(_STL::fpos<mbstate_t> pos, int)
{
	FILE *f = _M_file;
	streamoff off = pos;
	fpos_t p(off);
	if (fsetpos(f, &p) == 0)
		return pos;
	return _STL::fpos<mbstate_t>(-1);
}

} // namespace _SgI
