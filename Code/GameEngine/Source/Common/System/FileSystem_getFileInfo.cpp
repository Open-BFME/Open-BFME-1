// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// FileSystem::getFileInfo, retail 0x009C8C70, 332 bytes.
// ZH only asks local then archive. BFME prefixes the directory from byte_134CA48 the
// same way FileSystem::doesFileExist does, then tries local prefixed, local
// original, archive prefixed, archive original.

#include <cstring>

extern "C" int (__cdecl *__imp__sprintf)(char *, const char *, ...);
static inline int do_sprintf(char *b, const char *f, const char *a, const char *c)
{
	return (*__imp__sprintf)(b, f, a, c);
}

template <class T>
class StringBase
{
private:
	StringBase(const T *s);
	friend class AsciiString;

protected:
	T *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
	~AsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}

protected:
	void releaseBuffer();
};

struct FileInfo
{
	int sizeHigh;
	int sizeLow;
	int timestampHigh;
	int timestampLow;
};

class LocalFileSystem
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual bool getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const = 0;
};

class ArchiveFileSystem
{
public:
	bool getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const;
};

extern LocalFileSystem *TheLocalFileSystem;
extern ArchiveFileSystem *TheArchiveFileSystem;
extern char byte_134CA48[];

class FileSystem
{
public:
	bool getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const;
};

bool FileSystem::getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const
{
	char buf[0x200];
	if (fileInfo == NULL)
		return false;

	memset(fileInfo, 0, sizeof(*fileInfo));
	do_sprintf(buf, "%s\\%s", byte_134CA48, filename.str());

	bool found;
	{
		AsciiString prefixed(buf);
		found = TheLocalFileSystem->getFileInfo(prefixed, fileInfo);
	}
	if (found)
		return true;

	if (TheLocalFileSystem->getFileInfo(filename, fileInfo))
		return true;

	{
		AsciiString prefixed(buf);
		found = TheArchiveFileSystem->getFileInfo(prefixed, fileInfo);
	}
	if (found)
		return true;

	return TheArchiveFileSystem->getFileInfo(filename, fileInfo) ? true : false;
}
