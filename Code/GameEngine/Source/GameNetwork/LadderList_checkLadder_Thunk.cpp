// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME5: readable body of LadderList::checkLadder.

#define BFME_STLP_NODE_ALLOC
#include <list>
#include <string.h>

extern const char g_bfmeEmptyAscii[];

template <class T>
class StringBase
{
protected:
	void *m_data;

public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &source);
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString();

	const char *str() const
	{
		return m_data != 0 ? reinterpret_cast<const char *>(m_data) + 8 : g_bfmeEmptyAscii;
	}

	bool isEmpty() const
	{
		return m_data == 0 || *reinterpret_cast<const unsigned short *>(reinterpret_cast<const char *>(m_data) + 4) == 0;
	}

	void concat(const char *source, int length);

	void concat(const char *source)
	{
		concat(source, static_cast<int>(strlen(source)));
	}

};

class File
{
public:
	enum { READ = 1, TEXT = 0x20 };
	virtual ~File() {}
	virtual void open() = 0;
	virtual void close() = 0;
	virtual int read(void *, int) = 0;
	bool eof();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access);
};

extern FileSystem *TheFileSystem;

class LadderInfo
{
public:
	~LadderInfo();

	char m_pad0[0x1a];
	bool validQM;
	bool validCustom;
	std::list<AsciiString> validMaps;
	std::list<AsciiString> validFactions;
	AsciiString cryptedPassword;
	AsciiString address;
	unsigned short port;
	AsciiString homepageURL;
	bool submitReplay;
	int index;
};

typedef std::list<LadderInfo *> LadderInfoList;

class LadderList
{
private:
	void checkLadder(AsciiString, int);
	LadderInfoList m_localLadders;
};

LadderInfo *parseLadder(AsciiString);

// ?checkLadder@LadderList@@AAEXVAsciiString@@H@Z
void LadderList::checkLadder(AsciiString fname, int index)
{
	File *fp = TheFileSystem->openFile(fname.str(), File::READ | File::TEXT);
	char buf[1024];
	AsciiString rawData;
	if (fp)
	{
		int len;
		while (!fp->eof())
		{
			len = fp->read(buf, 1023);
			buf[len] = 0;
			buf[1023] = 0;
			rawData.concat(buf);
		}
		fp->close();
		fp = 0;
	}

	if (rawData.isEmpty())
		return;

	LadderInfo *li = parseLadder(rawData);
	if (!li)
		return;

	if (li->address.isEmpty())
	{
		delete li;
		return;
	}

	if (!li->port)
	{
		delete li;
		return;
	}

	if (li->validMaps.size() == 0)
	{
		delete li;
		return;
	}

	li->index = index;
	li->validQM = false;
	li->validCustom = false;
	m_localLadders.push_back(li);
}
