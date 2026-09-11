// ?d_001107b0@@YAXXZ
// partial score=0.35 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc
// TU-local BFME ABI mirror for the compiler-split loadGame entry at 0x001107B0.

typedef bool Bool;
typedef int Int;
typedef unsigned char UnsignedByte;

template <typename T> struct BfmeStringData
{
	Int refs;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

protected:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	BfmeStringData<T> *m_data;

private:
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->text : (const char *)0x0107388B;
	}
};

class File
{
public:
	virtual ~File();
	virtual Bool open(const char *, Int);
	virtual void close();
};

class FileSystem
{
public:
	File *openFile(const char *filename, Int access);
};

#define TheFileSystem (*(FileSystem **)0x0134CB48)

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isStoring();
	virtual void slot03();
	virtual void slot04();
	virtual Int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void xferSnapshot(void *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString *value);

private:
	UnsignedByte m_data[0x1C];
};

class Gen009D8CA0 : public Xfer
{
public:
	Gen009D8CA0(Int first, Int second, Int third);
	~Gen009D8CA0();
	Bool readAt009D89E0(File *file, void *output);
};

class Rva001107B0GameLogic
{
public:
	Bool isInGame();
	void clearGameData(Bool first, Bool second);
	UnsignedByte pad00[0x1A0];
	Int loadCount;
};

#define RVA001107B0_GAME_LOGIC (*(Rva001107B0GameLogic **)0x012F0898)

class Rva001107B0GameStateMap
{
public:
	void clearScratchPadMaps();
};

#define RVA001107B0_GAME_STATE_MAP (*(Rva001107B0GameStateMap **)0x012EF194)

class Rva001107B0GameEngine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void reset();
};

#define RVA001107B0_GAME_ENGINE (*(Rva001107B0GameEngine **)0x012ED524)

class Rva001107B0GhostManager
{
public:
	UnsignedByte pad00[9];
	Bool locked;
};

#define RVA001107B0_GHOST_MANAGER (*(Rva001107B0GhostManager **)0x012EF4FC)

class Rva001107B0GlobalData
{
public:
	UnsignedByte pad00[0x30];
	AsciiString pendingFile;
};

#define RVA001107B0_GLOBAL_DATA (*(Rva001107B0GlobalData **)0x012ED5C8)

class Rva001107B0Message
{
public:
	void appendIntegerArgument(Int value);
};

class Rva001107B0MessageStream
{
public:
	Rva001107B0Message *appendMessage(Int messageType);
};

#define RVA001107B0_MESSAGE_STREAM (*(Rva001107B0MessageStream **)0x012ED668)

class Rva001107B0CampaignManager
{
public:
	Int getGameDifficulty();
	Int getRankPoints();
};

#define RVA001107B0_CAMPAIGN_MANAGER (*(Rva001107B0CampaignManager **)0x012F147C)

class Rva001107B0GameText
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
};

#define RVA001107B0_GAME_TEXT (*(Rva001107B0GameText **)0x012F147C)

class UnicodeString
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &other);
	~UnicodeString();
	void translate(const AsciiString &text);
	void format(const UnicodeString &formatString, const UnicodeString &text);
	const unsigned short *str() const;
};

extern void InitRandom(Int seed);
extern void setFPMode();
extern void MessageBoxOk(const UnicodeString &title, const UnicodeString &message, void *callback);

template <typename T> class LatchRestore
{
protected:
	T valueToRestore;
	T &whereToRestore;

public:
	LatchRestore(T &dest, const T &src) : whereToRestore(dest)
	{
		valueToRestore = dest;
		dest = src;
	}

	virtual ~LatchRestore()
	{
		whereToRestore = valueToRestore;
	}
};

enum Rva001107B0SaveCode
{
	RVA001107B0_SC_OK = 1,
	RVA001107B0_SC_FILE_NOT_FOUND = 3,
	RVA001107B0_SC_UNABLE_TO_OPEN_FILE = 4,
	RVA001107B0_SC_INVALID_DATA = 7
};

struct Rva001107B0AvailableGameInfo
{
	void *filenameData;
	UnsignedByte saveGameInfo[0x30];
	Int saveFileType;
	void *tail;
};

struct Rva001107B0SaveGameInfo
{
	UnsignedByte data[0x30];
};

class Rva001107B0GameState
{
public:
	Rva001107B0SaveCode loadGame(Rva001107B0AvailableGameInfo gameInfo);
	Bool doesSaveGameExist(AsciiString filename);
	AsciiString getFilePathInSaveDirectory(const AsciiString &leaf);
	void xferSaveData(Gen009D8CA0 *xfer, Int snapshotType);
	void gameStatePostProcessLoad();
	Rva001107B0SaveGameInfo *getSaveGameInfo()
	{
		return (Rva001107B0SaveGameInfo *)((char *)this + 0x40);
	}

	UnsignedByte pad00[0x54];
	Bool m_isInLoadGame;
};

// ?loadGame@GameState@@QAE?AW4SaveCode@@UAvailableGameInfo@@@Z
Rva001107B0SaveCode Rva001107B0GameState::loadGame(
	Rva001107B0AvailableGameInfo gameInfo)
{
	Rva001107B0GameState *self = this;
	Int zero = 0;
	Rva001107B0GameLogic *gameLogic = RVA001107B0_GAME_LOGIC;
	Int *loadCount = &gameLogic->loadCount;
	Int count = *loadCount;
	if (count == zero)
		setFPMode();
	++*loadCount;

	AsciiString filename = *(const AsciiString *)&gameInfo;
	if (self->doesSaveGameExist(filename) == false)
		return RVA001107B0_SC_FILE_NOT_FOUND;

	if (gameInfo.saveFileType == 1)
	{
		RVA001107B0_GAME_LOGIC->clearGameData(false, false);
	}

	RVA001107B0_GAME_STATE_MAP->clearScratchPadMaps();
	AsciiString filepath = self->getFilePathInSaveDirectory(
		*(const AsciiString *)&gameInfo);
	File *file = TheFileSystem->openFile(filepath.str(), 0x41);
	if (file == 0)
		return RVA001107B0_SC_UNABLE_TO_OPEN_FILE;

	RVA001107B0_GAME_ENGINE->reset();
	RVA001107B0_GHOST_MANAGER->locked = true;
	LatchRestore<Bool> inLoadGame(self->m_isInLoadGame, true);
	Bool error = false;
	try
	{
		Gen009D8CA0 xferLoad(0x510790, (Int)this, 0x50F100);
		self->xferSaveData(&xferLoad, 0);
	}
	catch (...)
	{
		error = true;
	}

	file->close();
	RVA001107B0_GHOST_MANAGER->locked = false;
	try
	{
		self->gameStatePostProcessLoad();
	}
	catch (...)
	{
		error = true;
	}

	if (error)
		return RVA001107B0_SC_INVALID_DATA;

	if (getSaveGameInfo()->data[0x2C] == 1)
	{
		InitRandom(0);
		RVA001107B0_GLOBAL_DATA->pendingFile =
			*(const AsciiString *)((const char *)getSaveGameInfo() + 0x2C);
		Rva001107B0Message *message =
			RVA001107B0_MESSAGE_STREAM->appendMessage(0);
		message->appendIntegerArgument(0);
		message->appendIntegerArgument(
			RVA001107B0_CAMPAIGN_MANAGER->getGameDifficulty());
		message->appendIntegerArgument(
			RVA001107B0_CAMPAIGN_MANAGER->getRankPoints());
		getSaveGameInfo()->data[0x2C] = 0;
	}

	return RVA001107B0_SC_OK;
}
