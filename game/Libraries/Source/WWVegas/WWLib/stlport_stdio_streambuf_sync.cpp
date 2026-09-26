// cl: /O2 /EHsc /MD
// STLport 4.5.3 stdio_streambuf_base::sync (src/stdio_streambuf.cpp).
//
// The vtable at VA 0x0112FBDC sits behind an RTTI complete object locator
// spelling '.?AVstdio_streambuf_base@_SgI@@'.  Slot 4 is sync, the order
// inputs/vendor/stlport/stl/_streambuf.h gives basic_streambuf and the order slots 1,
// 2 and 3 already follow with the landed setbuf, seekoff and seekpos.  The
// FILE* sits at +0x54, after the basic_streambuf<char> subobject, which the
// seekpos body in StdioStreambufBaseSeekpos.cpp already witnesses.

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

extern "C" {
	__declspec(dllimport) int __cdecl fflush(FILE *);
}

namespace _SgI {

class stdio_streambuf_base {
protected:
	virtual int sync();

private:
	char m_streambuf[0x50];
	FILE *_M_file;
};

int stdio_streambuf_base::sync()
{
	return fflush(_M_file) == 0 ? 0 : -1;
}

} // namespace _SgI
