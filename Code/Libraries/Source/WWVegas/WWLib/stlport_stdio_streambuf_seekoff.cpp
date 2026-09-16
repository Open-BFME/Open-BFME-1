// cl: /O2 /EHsc /MD
// STLport 4.5.3 stdio_streambuf_base::seekoff (src/stdio_streambuf.cpp).
//
// Slot 2 of the vtable at VA 0x0112FBDC, whose RTTI complete object locator
// spells '.?AVstdio_streambuf_base@_SgI@@'.  The seekpos body one slot later
// already places the FILE* at +0x54, and this body reads the same field.
// Retail turns the seekdir into the whence code with dec, dec, sub 2, so the
// three cases are 1, 2 and 4, which is how STLport numbers beg, cur and end.

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
	__declspec(dllimport) int __cdecl fseek(FILE *, long, int);
	__declspec(dllimport) int __cdecl fgetpos(FILE *, fpos_t *);
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
	virtual _STL::fpos<mbstate_t> seekoff(streamoff off, int dir, int mode);

private:
	char m_streambuf[0x50];
	FILE *_M_file;
};

_STL::fpos<mbstate_t> stdio_streambuf_base::seekoff(streamoff off, int dir, int)
{
	int whence;

	switch (dir)
	{
	case 1:
		whence = 0;
		break;
	case 2:
		whence = 1;
		break;
	case 4:
		whence = 2;
		break;
	default:
		return _STL::fpos<mbstate_t>(-1);
	}

	if (fseek(_M_file, off, whence) == 0)
	{
		fpos_t pos;
		fgetpos(_M_file, &pos);
		return _STL::fpos<mbstate_t>((streamoff)pos);
	}
	return _STL::fpos<mbstate_t>(-1);
}

} // namespace _SgI
