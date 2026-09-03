// ?d_007e35e0@@YAXXZ
// partial score=0.78 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc-
// Retail 0x007E35E0.  This is the address-derived initializer paired with
// Rva007E3930StringState's constructor.  The object owns a StringBase<char>
// at +0, a File at +4, a mode at +8, and the parsed size at +0xC.

extern "C" unsigned int __cdecl strlen(const char *text);

typedef bool Bool;

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

class Rva007E3930StringState : public StringBase<char>
{
private:
	int m_value4;
	int m_mode;
	int m_valueC;

	bool _bfme_initialize_007E35E0(const char *text, int valueA, Bool valueB);
	bool _bfme_readHeader();
};

// ?_bfme_initialize_007E35E0@Rva007E3930StringState@@AAE_NPBDHH@Z
bool Rva007E3930StringState::_bfme_initialize_007E35E0(
	const char *text, int valueA, Bool valueB)
{
	Bool result = false;
	((StringBase<char> *)this)->set(text, text ? (int)strlen(text) : 0);

	if (valueA == 1)
	{
		const char *filename = m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
		if (!TheFileSystem->doesFileExist(filename))
		{
			m_mode = 5;
			return result;
		}

		filename = m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
		m_value4 = (int)TheFileSystem->openFile(filename, 0x141);
		m_valueC = ((File *)m_value4)->size();
		m_mode = 6;
		if (m_valueC < 8)
		{
			m_mode = 3;
			return result;
		}

		if (valueB != 0)
		{
			if (!_bfme_readHeader())
			{
				m_mode = 3;
				((Rva007E3110 *)this)->releaseNested();
				return result;
			}
		}

		if (m_mode == 6)
		{
			((File *)m_value4)->seek(0, 0);
		}
		return true;
	}

	if (valueA == 2)
	{
		m_value4 = (int)TheFileSystem->openFile(
			m_data ? (const char *)m_data + 8 : (const char *)0x0107388B, 0x5A);
		m_mode = 3;
		if (m_value4 == 0)
		{
			return result;
		}
		m_mode = 7;
		return true;
	}

	return result;
}
