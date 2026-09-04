// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

typedef int Int;
typedef char Char;
typedef bool Bool;

// BFME's AsciiString buffer has a 16-bit length at +4 and text at +8.  The
// visible inline-forwarding base is also what gives MSVC 7.1 retail's local
// by-value temporaries their EH and register order.
template <class T> struct StringInlineData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <class T> class StringBase
{
	friend class AsciiString;

public:
	void set(const T *text, int length);
	void set(const StringBase<T> &other);
	void concat(const T *text, int length);

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	Bool nextToken(AsciiString *token, const char *separators);
	AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*((const StringBase<char> *)&other));
		return *this;
	}
};

static inline Int bfmeLength(const AsciiString &s)
{
	const char *data = *(const char * const *)&s;
	return data ? *(const unsigned short *)(data + 4) : 0;
}

static inline const char *bfmeStr(const AsciiString &s)
{
	const char *data = *(const char * const *)&s;
	return data ? data + 8 : "";
}

static inline void bfmeSet(AsciiString &s, const char *value)
{
	((StringBase<char> *)&s)->set(value, value ? (Int)strlen(value) : 0);
}

static inline void bfmeConcat(AsciiString &s, const AsciiString &value)
{
	((StringBase<char> *)&s)->concat(bfmeStr(value), bfmeLength(value));
}

static inline void bfmeConcat(AsciiString &s, char value)
{
	((StringBase<char> *)&s)->concat(&value, 1);
}

static inline const char *bfmeFind(const AsciiString &s, char value)
{
	const char *p = bfmeStr(s);
	const char *end = p + bfmeLength(s);
	for (; p != end; ++p)
		if (*p == value)
			return p;
	return 0;
}

class File
{
public:
	enum { WRITE = 2, CURRENT = 1 };
	virtual ~File();
	virtual Bool open(const char *filename, Int access);
	virtual void close();
	virtual Int read(void *buffer, Int bytes);
	virtual Int write(const void *buffer, Int bytes);
	virtual Int seek(Int bytes, Int mode);

protected:
	void *m_nameData;
	Int m_access;
	bool m_open;
	bool m_deleteOnClose;
	unsigned short m_bfmePadding;
	Int m_mutex;

public:
	void deleteOnClose() { m_deleteOnClose = true; }
};

class Win32LocalFile : public File
{
public:
	Win32LocalFile();
	Int padding;
};

class Win32LocalFileSystem
{
public:
	virtual ~Win32LocalFileSystem();
	virtual void init();
	virtual File *openFile(const char *filename, Int access);
	virtual File *openFile(const char *filename, Int access, Int seekTo, Int a4);
	virtual Bool doesFileExist(const char *filename) const;
	virtual void getFileListInDirectory(const AsciiString &, const AsciiString &, const AsciiString &, void *, Bool) const;
	virtual Bool getFileInfo(const AsciiString &, void *) const;
	virtual Bool createDirectory(AsciiString directory);
};

File *Win32LocalFileSystem::openFile(const Char *filename, Int access, Int seekTo, Int a4)
{
	if (strlen(filename) <= 0)
		return 0;

	Win32LocalFile *file = new Win32LocalFile;

	if (access & File::WRITE) {
		AsciiString string;
		bfmeSet(string, filename);
		AsciiString token;
		AsciiString dirName;
		string.nextToken(&token, "\\/");
		dirName = token;
		while ((bfmeFind(token, '.') == 0) || (bfmeFind(string, '.') != 0)) {
			createDirectory(dirName);
			string.nextToken(&token, "\\/");
			bfmeConcat(dirName, '\\');
			bfmeConcat(dirName, token);
		}
	}

	if (file->open(filename, access) == 0) {
		file->close();
		delete file;
		file = 0;
	} else {
		file->deleteOnClose();
		if (seekTo != 0)
			file->seek(seekTo, File::CURRENT);
	}
	return file;
}
