// cl: /DNDEBUG /MD /EHsc
// readable body of ?open@CachedFileInputStream@@QAE_NVAsciiString@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp
// Open-BFME5: lift the retail cached-file open/decompression path to C++.

typedef int Int;
typedef bool Bool;
void *operator new[](unsigned int size);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();
	const char *str() const { return m_data ? m_data + 8 : ""; }
private:
	const char *m_data;
};

class File
{
public:
	virtual void reserved0();
	virtual void reserved1();
	virtual void close();
	virtual void reserved3();
	virtual void reserved4();
	virtual void reserved5();
	virtual void reserved6();
	virtual void reserved7();
	virtual void reserved8();
	virtual void reserved9();
	virtual void reserved10();
	virtual Int size();
	virtual void reserved12();
	virtual char *readEntireAndClose();
};

class FileSystem
{
public:
	File *openFile(const char *name, Int mode);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression/Compression.h
class CompressionManager
{
public:
	static Bool isDataCompressed(const void *data, Int size);
	static Int getUncompressedSize(const void *data, Int size);
	static Int decompressData(const void *data, Int size, void *output, Int outputSize);
};

extern FileSystem *TheFileSystem;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapReaderWriterInfo.h
class CachedFileInputStream
{
public:
	virtual Int read(void *, Int);
	virtual unsigned int tell();
	virtual Bool absoluteSeek(unsigned int);
	virtual Bool eof();
	Bool open(AsciiString path);
private:
	Int m_size;
	char *m_buffer;
	Int m_pos;
};

Bool CachedFileInputStream::open(AsciiString path)
{
	File *file = TheFileSystem->openFile(path.str(), 0x41);
	m_size = 0;
	if (file) {
		m_size = file->size();
		if (m_size) {
			m_buffer = file->readEntireAndClose();
			file = 0;
		}
		m_pos = 0;
	}

	if (CompressionManager::isDataCompressed(m_buffer, m_size)) {
		Int uncompLen = CompressionManager::getUncompressedSize(m_buffer, m_size);
		char *uncompBuffer = static_cast<char *>(::operator new[](uncompLen));
		Int actualLen = CompressionManager::decompressData(m_buffer, m_size, uncompBuffer, uncompLen);
		if (actualLen == uncompLen) {
			delete[] m_buffer;
			m_buffer = uncompBuffer;
			m_size = uncompLen;
		} else {
			delete[] uncompBuffer;
		}
	}

	if (file)
		file->close();
	return m_size != 0;
}
