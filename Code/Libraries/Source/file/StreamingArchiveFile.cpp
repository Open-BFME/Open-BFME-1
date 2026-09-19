// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// BFME ABI reconstruction of StreamingArchiveFile::openFromArchive.
// The vendored Zero Hour headers omit File::lock()/unlock() and retain a
// duplicate StreamingArchiveFile size field; this TU keeps the proven BFME
// layout local while the real body remains at the official source path.

typedef int Int;
typedef bool Bool;
typedef char Char;
typedef float Real;

#define FALSE false
#define TRUE true
#define NULL 0

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;

	StringBase() : m_data(0) {}
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString &operator=(const AsciiString &other);

	const char *str() const
	{
		return m_data ? m_data->data : "";
	}
};

class File
{
public:
	enum access
	{
		READ = 0x0001,
		WRITE = 0x0002,
		APPEND = 0x0004,
		TRUNCATE = 0x0010,
		TEXT = 0x0020,
		BINARY = 0x0040,
		STREAMING = 0x0100
	};

	enum seekMode { START, CURRENT, END };

	virtual ~File();
	virtual Bool open(const Char *filename, Int access = 0);
	virtual void close(void);
	virtual Int read(void *buffer, Int bytes);
	virtual Int write(const void *buffer, Int bytes);
	virtual Int seek(Int bytes, seekMode mode = CURRENT);
	virtual void nextLine(Char *buf, Int bufSize);
	virtual Bool scanInt(Int &newInt);
	virtual Bool scanReal(Real &newReal);
	virtual Bool scanString(AsciiString &newString);
	virtual Bool print(const Char *format, ...);
	virtual Int size(void);
	virtual Int position(void);
	virtual Char *readEntireAndClose(void);
	virtual File *convertToRAMFile(void);
	virtual void lock(void);
	virtual void unlock(void);

protected:
	AsciiString m_nameStr;
	Int m_access;
	Bool m_open;
	Bool m_deleteOnClose;
	void *m_mutex;
};

class RAMFile : public File
{
protected:
	Char *m_data;
	Int m_pos;
	Int m_size;
};

class StreamingArchiveFile : public RAMFile
{
public:
	virtual Bool openFromArchive(File *archiveFile, const AsciiString &filename, Int offset, Int size);

protected:
	File *m_file;
	Int m_startingPos;
	Int m_curPos;
};

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04(void);
	virtual void Slot08(void);
	virtual void Slot0C(void);
	virtual void Slot10(void);
	virtual void Slot14(void);
	virtual void Slot18(void);
	virtual void Slot1C(void);
	virtual void Slot20(void);
	virtual void Slot24(void);
	virtual void Slot28(void);
	virtual void Slot2C(void);
	virtual void Slot30(void);
	virtual void Slot34(void);
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C(void);
	virtual void Slot40(void);
	virtual void Slot44(void);
	virtual void Slot48(void);
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(void); virtual void Slot04(void); virtual void Slot08(void); virtual void Slot0C(void);
	virtual void Slot10(void); virtual void Slot14(void); virtual void Slot18(void); virtual void Slot1C(void);
	virtual void Slot20(void); virtual void Slot24(void); virtual void Slot28(void); virtual void Slot2C(void);
	virtual void Slot30(void); virtual void Slot34(void); virtual void Slot38(void); virtual void Slot3C(void);
	virtual void Slot40(void); virtual void Slot44(void); virtual void Slot48(void); virtual void Slot4C(void);
	virtual void Slot50(void); virtual void Slot54(void); virtual void Slot58(void); virtual void Slot5C(void);
	virtual void Begin_Report(void);
	virtual void Slot64(void); virtual void Slot68(void);
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);

Bool StreamingArchiveFile::openFromArchive(File *archiveFile, const AsciiString &filename, Int offset, Int size)
{
	if (archiveFile == NULL) {
		return FALSE;
	}

	if (File::open(filename.str(), File::READ | File::BINARY | File::STREAMING) == FALSE) {
		return FALSE;
	}

	m_file = archiveFile;
	m_startingPos = offset;
	RAMFile::m_size = size;
	m_curPos = 0;

	if (m_file->seek(offset, File::START) != offset) {
		return FALSE;
	}

	if (m_file->seek(size) != m_startingPos + size) {
		return FALSE;
	}

	m_file->seek(offset, File::START);

	unsigned short compressionMarker = 0;
	if (m_file->read(&compressionMarker, 2) != 2) {
		return FALSE;
	}

	if (compressionMarker == 0x15fb) {
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEIndexBufferDebugStream *stream = g_BFMEIndexBufferDebug->Get_Stream(0, 0);
		stream->Put_String((const char *)0x01143cf8)->Finish(1);
	}

	m_file->seek(offset, File::START);

	m_nameStr = filename;
	return TRUE;
}
