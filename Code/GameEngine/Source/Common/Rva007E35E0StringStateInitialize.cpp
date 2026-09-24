// cl: /DNDEBUG /MD /EHsc-
//
// Retail 0x007E35E0, reached through ILT 0x00005C0E from the constructor at
// 0x007E3930 and from the VP6 stream invoke at 0x007E55F0.  The object owns a
// StringBase<char> at +0, a File at +4, a mode at +8 and the file size at +0xC.
// Mode 1 opens an existing file for reading, mode 2 opens one for writing.
// The body reads only the low byte of its third argument (mov al,[esp+18h]),
// while both callers and the ILT pin declare it as int.

extern "C" unsigned int __cdecl strlen(const char *text);

typedef bool Bool;

extern char Rva006A16B0Empty[];

template <typename T>
class StringBase
{
public:
	void set(const T *text, int length);

protected:
	void *m_data;
};

class File
{
public:
	virtual ~File();
	virtual bool open(const char *filename, int access);
	virtual void close();
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, int mode);
	virtual void nextLine(char *buffer, int bufferSize);
	virtual bool scanInt(int &value);
	virtual bool scanReal(float &value);
	virtual bool scanString(void *value);
	virtual bool print(const char *format, ...);
	virtual int size();
	virtual int position();
	virtual char *readEntireAndClose();
	virtual File *convertToRAMFile();
	virtual void lock();
	virtual void unlock();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access);
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

class Rva007E3110
{
public:
	bool releaseNested();
};

class BfmeB996Range
{
public:
	char rva007e34c0();
};

class Rva007E3930StringState : public StringBase<char>
{
private:
	int m_value4;
	int m_mode;
	int m_valueC;

	char _bfme_initialize_007E35E0(const char *text, int valueA, int valueB);
};

// ?_bfme_initialize_007E35E0@Rva007E3930StringState@@AAEDPBDHH@Z
char Rva007E3930StringState::_bfme_initialize_007E35E0(
	const char *text, int valueA, int valueB)
{
	Bool result = false;
	set(text, text ? (int)strlen(text) : 0);

	if (valueA == 1)
	{
		if (!TheFileSystem->doesFileExist(m_data ? (const char *)m_data + 8 : Rva006A16B0Empty))
		{
			m_mode = 5;
		}
		else
		{
			m_value4 = (int)TheFileSystem->openFile(
				m_data ? (const char *)m_data + 8 : Rva006A16B0Empty, 0x141);
			m_valueC = ((File *)m_value4)->size();
			m_mode = 6;
			if (m_valueC >= 8)
			{
				if ((char)valueB && !((BfmeB996Range *)this)->rva007e34c0())
				{
					m_mode = 3;
					((Rva007E3110 *)this)->releaseNested();
				}
				else
				{
					if (m_mode == 6)
					{
						((File *)m_value4)->seek(0, 0);
					}
					result = true;
				}
			}
			else
			{
				m_mode = 3;
			}
		}
	}
	else if (valueA == 2)
	{
		m_value4 = (int)TheFileSystem->openFile(
			m_data ? (const char *)m_data + 8 : Rva006A16B0Empty, 0x5A);
		m_mode = 3;
		if (m_value4 != 0)
		{
			m_mode = 7;
			result = true;
		}
	}

	return result;
}
