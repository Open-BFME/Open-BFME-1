// cl: /DNDEBUG /MD /EHs-c-
// Both RAMFile open overloads, ported from their authentic Zero Hour bodies.
// Retail constructor 9D1980 installs table VA1143C58: slot 1 is open(name,
// access) at 9D1A00 and slot 17 is open(File*) at 9D2020. The matched
// LocalFile::convertToRAMFile body calls that constructor at 9D27C6 and then
// passes its File pointer through slot 17 at 9D27DE (a virtual caller).
// The
// File declaration carries BFME's two lock slots and the proven +0x14 RAMFile
// data layout so the virtual size/read calls retain their retail slots.

// Retail frees these arrays through operator delete[] (??_V@YAXPAX@Z,
// 0x00881EF0). Without the declaration cl falls back to scalar
// operator delete for the block, which is a different body at 0x00881EB0.
void __cdecl operator delete[](void *block);
typedef int Int;
typedef bool Bool;
typedef char Char;

void *operator new[](unsigned int bytes);

#define FALSE false
#define TRUE true
#define NULL 0

class AsciiString;

class File
{
public:
	virtual ~File();
	virtual Bool open(const Char *filename, Int access);
	virtual void close(void);
	virtual Int read(void *buffer, Int bytes) = 0;
	virtual Int write(const void *buffer, Int bytes) = 0;
	virtual Int seek(Int bytes, Int mode) = 0;
	virtual void nextLine(Char *buf, Int bufSize) = 0;
	virtual Bool scanInt(Int &newInt) = 0;
	virtual Bool scanReal(float &newReal) = 0;
	virtual Bool scanString(AsciiString &newString) = 0;
	virtual Bool print(const Char *format, ...);
	virtual Int size(void);
	virtual Int position(void);
	virtual char *readEntireAndClose(void) = 0;
	virtual File *convertToRAMFile(void) = 0;
	virtual void lock(void);
	virtual void unlock(void);

	const char *getName(void) const
	{
		const char *data = *(const char * const *)((const char *)this + 4);
		return data ? data + 8 : "";
	}

	Int getAccess(void) const
	{
		return *(const Int *)((const char *)this + 8);
	}

protected:
	unsigned char m_fileState[0x10];
};

class RAMFile : public File
{
public:
	virtual Bool open(const Char *filename, Int access);
	virtual Bool open(File *file);

protected:
	Char *m_data;
	Int m_pos;
	Int m_size;
};

// ?open@RAMFile@@UAE_NPAVFile@@@Z
Bool RAMFile::open(File *file)
{
	if (file == NULL)
		return FALSE;

	Int access = file->getAccess();

	if (!File::open(file->getName(), access))
		return FALSE;

	m_size = file->size();
	m_data = new Char[m_size];

	if (m_data == NULL)
		return FALSE;

	m_size = file->read(m_data, m_size);

	if (m_size < 0)
	{
		delete [] m_data;
		m_data = NULL;
		return FALSE;
	}

	m_pos = 0;
	return TRUE;
}

class FileSystem
{
public:
	File *openFile( const Char *filename, Int access );
};

extern FileSystem *TheFileSystem;

// ?open@RAMFile@@UAE_NPBDH@Z
Bool RAMFile::open( const Char *filename, Int access )
{
	File *file = TheFileSystem->openFile( filename, access );

	if ( file == NULL )
	{
		return FALSE;
	}

	Bool result = open( file );

	file->close();

	return result;
}
