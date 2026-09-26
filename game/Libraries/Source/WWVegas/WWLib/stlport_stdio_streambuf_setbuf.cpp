// cl: /O2 /EHsc /MD
// STLport 4.5.3 stdio_streambuf_base::setbuf and stdio_ostreambuf::showmanyc
// (src/stdio_streambuf.cpp).
//
// The vtable at VA 0x0112FBDC sits behind an RTTI complete object locator
// spelling '.?AVstdio_streambuf_base@_SgI@@' and 0x0112F2B8 spells
// '.?AVstdio_ostreambuf@_SgI@@'.  Slot 1 is setbuf and slot 5 is showmanyc,
// the order inputs/vendor/stlport/stl/_streambuf.h gives basic_streambuf.  The
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
typedef int streamsize;

extern "C" {
	__declspec(dllimport) int __cdecl setvbuf(FILE *, char *, int, unsigned int);
}

#define BFME_IOFBF 0
#define BFME_IONBF 4

namespace _STL {

template <class CharT> class char_traits;
template <class CharT, class Traits> class basic_streambuf;

}

namespace _SgI {

class stdio_streambuf_base {
protected:
	virtual _STL::basic_streambuf<char, _STL::char_traits<char> > *
	setbuf(char *s, streamsize n);

private:
	char m_streambuf[0x50];
	FILE *_M_file;
};

class stdio_ostreambuf : public stdio_streambuf_base {
protected:
	virtual streamsize showmanyc();
};

_STL::basic_streambuf<char, _STL::char_traits<char> > *
stdio_streambuf_base::setbuf(char *s, streamsize n)
{
	setvbuf(_M_file, s, (s == 0 && n == 0) ? BFME_IONBF : BFME_IOFBF,
	        (unsigned int)n);
	return (_STL::basic_streambuf<char, _STL::char_traits<char> > *)this;
}

streamsize stdio_ostreambuf::showmanyc()
{
	return -1;
}

} // namespace _SgI
