// cl: /DNDEBUG /MD /EHs-c-
// BFME's RAMFile::open(File *) body, ported from the Zero Hour twin.  The
// File declaration carries BFME's two lock slots and the proven +0x14 RAMFile
// data layout so the virtual size/read calls retain their retail slots.

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
