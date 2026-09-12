// cl: /DNDEBUG /MD /EHsc
// Byte-exact reconstruction of the file-local default-font parser.

class GameFont;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString() { freeBytes(); }

private:
	void freeBytes();
	void *m_data;
};

class File
{
public:
	virtual ~File() = 0;
	virtual void open() = 0;
	virtual void close() = 0;
	virtual int read(void *, int) = 0;
	virtual int write(const void *, int) = 0;
	virtual int seek(int, int) = 0;
	virtual void nextLine(char *, int) = 0;
	virtual bool scanInt(int &) = 0;
	virtual bool scanReal(float &) = 0;
	virtual bool scanString(AsciiString &) = 0;
};

void readUntilSemicolon(File *, char *, int);

// ?parseDefaultFont@@YA_NPAVGameFont@@PAVFile@@PAD@Z
static bool parseDefaultFont(GameFont *, File *inFile, char *buffer)
{
	AsciiString str;
	inFile->scanString(str);
	readUntilSemicolon(inFile, buffer, 0x800);
	return true;
}

bool parseDefaultFontCall(File *inFile)
{
	return parseDefaultFont(0, inFile, 0);
}
