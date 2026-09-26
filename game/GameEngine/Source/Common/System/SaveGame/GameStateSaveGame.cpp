// cl: /DNDEBUG /MD /EHsc
// Real-C++ reconstruction of GameState::saveGame at retail RVA 0x00110170.
//
// The named GameState::missionSave caller supplies a fifth stack byte to this
// body.  The ledger and object symbol use the proven five-argument ABI,
// replacing the old four-argument spelling attached to the naked dump.
// The save path also brackets xferSaveData with the retail Watchdog calls;
// those direct global loads and the neighboring xferSaveData body establish
// the GameState/XferFile identity without introducing a wrapper body.

typedef unsigned short UnsignedShort;
typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refs;
	UnsignedShort length;
	UnsignedShort capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

protected:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	BfmeStringData<T> *m_data;

private:
	StringBase(const T *text);
	void set(const StringBase<T> &other);
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void set(const AsciiString &other)
	{
		StringBase<char>::set(other);
	}

	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}

	void clear()
	{
		StringBase<char>::releaseBuffer();
	}

	int isEmpty() const
	{
		return m_data == 0 || m_data->length == 0;
	}

	const char *str() const
	{
		return m_data ? m_data->text : (const char *)0x0107388B;
	}
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<UnsignedShort>(other) {}
	~UnicodeString() {}

	void set(const UnicodeString &other)
	{
		StringBase<UnsignedShort>::set(other);
	}

	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}

	void translate(const AsciiString &value);
	void format(UnicodeString format, ...);

	const UnsignedShort *str() const
	{
		return m_data ? m_data->text : (const UnsignedShort *)0x0107388C;
	}
};

enum SaveFileType
{
	SAVE_FILE_TYPE_NORMAL,
	SAVE_FILE_TYPE_MISSION
};

enum SnapshotType
{
	SNAPSHOT_SAVELOAD,
	SNAPSHOT_DEEPCRC_LOGICONLY,
	SNAPSHOT_DEEPCRC,
	SNAPSHOT_MAX
};

// Retail returns 1 for the no-file path and 3 for an exception/open error.
enum SaveCode
{
	SC_OK = 0,
	SC_NO_FILE_AVAILABLE = 1,
	SC_ERROR = 3
};

struct SaveGameInfo
{
	AsciiString saveGameMapName;
	AsciiString pristineMapName;
	AsciiString mapLabel;
	unsigned char date[0x10];
	AsciiString campaignSide;
	int missionNumber;
	UnicodeString description;
	SaveFileType saveFileType;
	AsciiString missionMapName;
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *name;
};

class Xfer;

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class File
{
public:
	virtual ~File();
	virtual Bool open(const char *path, int mode);
	virtual void close();
};

class FileSystem
{
public:
	File *openFile(const char *path, int mode);
};

class CampaignManager
{
public:
	AsciiString getCurrentMap();
};

class Watchdog
{
public:
	void suppressTimeouts();
	void resumeTimeouts();
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void message(UnicodeString message, ...);
};

// The BFME vtable puts the string-manager-label overload at slot 12 and the
// Unicode overload at slot 13.  Keeping separate views prevents the compiler
// from reordering the two overloaded declarations in this TU.
class InGameUIAscii
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void message(AsciiString label, ...);
};

class BfmeActivationStream {};

class Gen009D6300
{
public:
	Bool bfmeTryActivate(BfmeActivationStream *stream, int enabled,
		Bool flags);
};

class Gen009D6DD0
{
public:
	void bfmeClose();
};

class Rva009D8630BlockWriter
{
public:
	Rva009D8630BlockWriter();
	virtual ~Rva009D8630BlockWriter();

private:
	unsigned char body[0x3c];
};

extern "C" __declspec(dllimport) int __stdcall CreateDirectoryA(
	const char *path, void *security);

class GameWindow;
GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body,
	void (*callback)(void));

#define TheFileSystem (*(FileSystem **)0x0134CB48)
#define TheCampaignManager (*(CampaignManager **)0x012F1028)
#define TheWatchdog (*(Watchdog **)0x012EF18C)
#define TheGameText (*(GameTextInterface **)0x012F147C)
#define TheInGameUI (*(InGameUI **)0x012F148C)
#define TheInGameUIAscii (*(InGameUIAscii **)0x012F148C)
#define TheWriterFlag (*(Bool *)0x012ED4DB)

class GameState : public SubsystemInterface, public Snapshot
{
	AsciiString findNextSaveFilename(UnicodeString description);
	void xferSaveData(Xfer *xfer, SnapshotType which);

	public:
	AsciiString getSaveDirectory() const;
	AsciiString getFilePathInSaveDirectory(const AsciiString &filename) const;
	SaveCode saveGame(AsciiString filename, UnicodeString desc,
		SaveFileType saveType, SnapshotType which, Bool showMessage);

private:
	unsigned char snapshotBlocks[0x0c];
	SaveGameInfo gameInfo;
};

// CampaignManager::getCurrentMap is an incremental-link thunk whose hidden
// return buffer is visibly the GameState pristineMapName field in retail.
// This call view keeps that proven thunk and its direct destination.
extern void j_0000d5d0();
struct CurrentMapCallTarget
{
	void getCurrentMap(AsciiString *result);
};
typedef void (CurrentMapCallTarget::*CurrentMapCall)(AsciiString *result);

// ?saveGame@GameState@@QAE?AW4SaveCode@@VAsciiString@@VUnicodeString@@W4SaveFileType@@W4SnapshotType@@_N@Z
SaveCode GameState::saveGame(AsciiString filename, UnicodeString desc,
	SaveFileType saveType, SnapshotType which, Bool showMessage)
{
	if (filename.isEmpty())
		filename = findNextSaveFilename(desc);
	if (filename.isEmpty())
		return SC_NO_FILE_AVAILABLE;

	CreateDirectoryA(getSaveDirectory().str(), 0);
	AsciiString filepath = getFilePathInSaveDirectory(filename);
	gameInfo.description = desc;

	File *file = TheFileSystem->openFile(filepath.str(), 0x4a);
	if (file == 0)
	{
		TheInGameUIAscii->message(AsciiString("GUI:Error"));
		return SC_ERROR;
	}

	Rva009D8630BlockWriter xferSave;
	try
	{
		reinterpret_cast<Gen009D6300 *>(&xferSave)->bfmeTryActivate(
			reinterpret_cast<BfmeActivationStream *>(file), 1, TheWriterFlag);
	}
	catch (...)
	{
		TheInGameUIAscii->message(AsciiString("GUI:Error"));
		file->close();
		return SC_ERROR;
	}

	gameInfo.saveFileType = saveType;
	if (saveType == SAVE_FILE_TYPE_MISSION)
	{
		union
		{
			void (*asFunction)();
			CurrentMapCall asMember;
		} currentMapCast;
		currentMapCast.asFunction = j_0000d5d0;
		(reinterpret_cast<CurrentMapCallTarget *>(TheCampaignManager)->*
			currentMapCast.asMember)(&gameInfo.pristineMapName);
	}
	else
		gameInfo.missionMapName.clear();

	if (TheWatchdog != 0)
		TheWatchdog->suppressTimeouts();
	try
	{
		xferSaveData(reinterpret_cast<Xfer *>(&xferSave), which);
	}
	catch (...)
	{
		UnicodeString ufilepath;
		ufilepath.translate(filepath);
		UnicodeString message;
		message.format(TheGameText->fetch("GUI:ErrorSavingGame"),
			ufilepath.str());
		MessageBoxOk(TheGameText->fetch("GUI:Error"), message, 0);
		reinterpret_cast<Gen009D6DD0 *>(&xferSave)->bfmeClose();
		file->close();
		if (TheWatchdog != 0)
			TheWatchdog->resumeTimeouts();
		return SC_ERROR;
	}

	reinterpret_cast<Gen009D6DD0 *>(&xferSave)->bfmeClose();
	file->close();
	if (showMessage)
	{
		UnicodeString message = TheGameText->fetch("GUI:GameSaveComplete");
		TheInGameUI->message(message);
	}
	if (TheWatchdog != 0)
		TheWatchdog->resumeTimeouts();
	return SC_OK;
}
