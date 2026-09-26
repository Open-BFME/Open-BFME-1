// cl: /DNDEBUG /MD /EHsc
// Canonical MapUtil CRC helper, retail 0x00450560.

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef int Int;

extern "C" char *__cdecl strcpy(char *, const char *);
extern "C" unsigned int __cdecl strlen(const char *);
extern "C" void *__cdecl memset(void *, int, unsigned int);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *, const char *, unsigned int);
unsigned long __cdecl CRC_Memory(const unsigned char *buffer, unsigned long length, unsigned long crc);

template <typename T> class StringBase
{
	friend class AsciiString;
private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
	~StringBase();
	void set(const StringBase &other);
	struct Data { Int refs; unsigned short length, capacity; T text[1]; };
	Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other) { set(other); return *this; }
	const char *str() const { return m_data ? m_data->text : ""; }
};

class File
{
public:
	virtual void destroy();
	virtual bool open(const char *filename, Int access);
	virtual void close();
	virtual Int read(void *buffer, Int bytes) = 0;
};

class FileSystem
{
public:
	File *openFile(const char *filename, Int access);
};

extern FileSystem *TheFileSystem;

UnsignedInt calcCRC(AsciiString dirName, AsciiString fname)
{
	AsciiString asciiFile;
	char tempBuf[260];
	char filenameBuf[260];
	Int length = 0;
	strcpy(tempBuf, fname.str());
	length = strlen(tempBuf);
	if (length >= 4)
	{
		memset(filenameBuf, 0, 260);
		strncpy(filenameBuf, tempBuf, length - 4);
	}

	asciiFile = fname;
	File *fp = TheFileSystem->openFile(asciiFile.str(), 1);
	if (!fp)
		return 0;

	UnsignedInt theCRC = 0;
	UnsignedByte buf[4096];
	Int num;
	while ((num = fp->read(buf, 4096)) > 0)
		theCRC = CRC_Memory(buf, num, theCRC);

	fp->close();
	return theCRC;
}
