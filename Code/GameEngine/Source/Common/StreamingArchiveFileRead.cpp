// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean C++ conversion of BFME StreamingArchiveFile::read at retail RVA 0x009D21F0.

typedef int Int;
typedef int Bool;
class AsciiString;

class File
{
public:
	enum seekMode { START, CURRENT, END };
	virtual ~File();
	virtual Bool open(const char *filename, Int access = 0);
	virtual void close();
	virtual Int read(void *buffer, Int bytes);
	virtual Int write(const void *buffer, Int bytes);
	virtual Int seek(Int bytes, Int mode);
	virtual void nextLine(char *buf, Int bufSize);
	virtual Bool scanInt(Int &newInt);
	virtual Bool scanReal(float &newReal);
	virtual Bool scanString(AsciiString &newString);
	virtual Bool print(const char *format, ...);
	virtual Int size();
	virtual Int position();
	virtual char *readEntireAndClose();
	virtual File *convertToRAMFile();
	virtual void lock();
	virtual void unlock();
protected:
	void *m_nameStr;
	Int m_access;
	Bool m_flags;
	void *m_mutex;
};

class RAMFile : public File
{
protected:
	char *m_data;
	Int m_pos;
	Int m_size;
};

class StreamingArchiveFile : public RAMFile
{
public:
	virtual Int read(void *buffer, Int bytes);
protected:
	File *m_file;
	Int m_startingPos;
	Int m_curPos;
};

Int StreamingArchiveFile::read(void *buffer, Int bytes)
{
	if (!m_file)
		return 0;
	m_file->lock();
	m_file->seek(m_startingPos + m_curPos, File::START);
	if (bytes + m_curPos > m_size)
		bytes = m_size - m_curPos;
	Int bytesRead = m_file->read(buffer, bytes);
	m_file->unlock();
	m_curPos += bytesRead;
	return bytesRead;
}
