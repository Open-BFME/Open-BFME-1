// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T>
class StringBase
{
friend class BFMERetailAsciiString;

protected:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);

private:
	void releaseBuffer();
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
};

class RetailLayoutString
{
public:
	void set(const char *text, int length);
};

class INILineBuffer
{
public:
	void clear();

private:
	char m_storage[0x14];
};

class INI
{
public:
	bool load(BFMERetailAsciiString file, BFMERetailAsciiString block,
		BFMERetailAsciiString name, int loadType, int reload);

protected:
	void prepFile(BFMERetailAsciiString file, int loadType);
	void readLine();
	void parseLine(BFMERetailAsciiString file);
	inline void unPrepFile();

private:
	void *m_file;
	RetailLayoutString m_filename;
	unsigned m_lineNum;
	unsigned m_lineCount;
	char m_buffer[0x404];
	const char *m_seps;
	const char *m_sepsPercent;
	const char *m_sepsColon;
	const char *m_sepsQuote;
	const char *m_blockEndToken;
	const char *m_endScriptToken;
	unsigned char m_endOfFile;
	char m_padding[0x407];
	INILineBuffer m_lines;
};

extern void setFPMode();
extern bool __cdecl rva00851BF0(BFMERetailAsciiString block,
	BFMERetailAsciiString name, const char *line);

inline void INI::unPrepFile()
{
	m_lines.clear();
	m_filename.set("None", 4);
	m_lineNum = 0;
	m_lineCount = 0;
	m_endOfFile = 0;
	*(void **)0x0130CE54 = 0;
}

bool INI::load(BFMERetailAsciiString file, BFMERetailAsciiString block,
	BFMERetailAsciiString name, int loadType, int reload)
{
	setFPMode();
	*(void **)0x0130CE54 = (void *)reload;
	prepFile(file, loadType);
	bool eof = false;

	try
	{
		while (m_endOfFile == eof)
		{
			readLine();
			if (rva00851BF0(block, name, m_buffer))
			{
				parseLine(file);
				return true;
			}
		}
	}
	catch (...)
	{
		unPrepFile();
		throw;
	}

	unPrepFile();
	return false;
}
