// cl: /O2 /EHsc /MD
// STLport 4.5.3 stdio_istreambuf::showmanyc (src/stdio_streambuf.cpp).
// FILE* lives at +0x54 after the basic_streambuf<char> subobject.

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

struct BfmeStat {
	unsigned int st_dev;
	unsigned short st_ino;
	unsigned short st_mode;
	short st_nlink;
	short st_uid;
	short st_gid;
	unsigned int st_rdev;
	long st_size;
	long st_atime;
	long st_mtime;
	long st_ctime;
};

extern "C" {
	__declspec(dllimport) int __cdecl feof(FILE *);
	__declspec(dllimport) int __cdecl _fstat(int, BfmeStat *);
	__declspec(dllimport) long __cdecl ftell(FILE *);
}

namespace _SgI {

class stdio_istreambuf {
protected:
	virtual int showmanyc();

private:
	char m_streambuf[0x50];
	FILE *_M_file;
};

static int remaining_after_tell(long size, long pos)
{
	if (pos < 0 || size <= pos)
		return 0;
	size -= pos;
	return (int)size;
}

int stdio_istreambuf::showmanyc()
{
	if (feof(_M_file))
		return -1;

	FILE *f = _M_file;
	int fd = f->_file;
	BfmeStat buf;
	long size;
	if (_fstat(fd, &buf) == 0 && (buf.st_mode & 0x8000)) {
		long n = buf.st_size;
		size = n > 0 ? n : 0;
	} else {
		size = 0;
	}
	return remaining_after_tell(size, ftell(_M_file));
}

} // namespace _SgI
