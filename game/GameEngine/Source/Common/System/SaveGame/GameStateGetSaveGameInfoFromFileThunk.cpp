// cl: /DNDEBUG /MD /EHsc
// Real C++ reconstruction of GameState::getSaveGameInfoFromFile at retail
// RVA 0x00111980.  The published addGameToAvailableList caller calls this
// body through ILT 0x000083D7 and tests AL, proving the BFME Bool ABI.
//
// The BFME reader uses the same WORD-length StringBase/AsciiString lifetime
// model as the landed save/load bodies.  Its file-header reader is the proven
// Gen009D8CA0/readAt009D89E0 pair; the Xfer block helpers are direct calls,
// while xferSnapshot and xferAsciiString retain their observed virtual slots.

typedef bool Bool;
typedef unsigned short UnsignedShort;

template <typename T> struct BfmeStringData
{
	int m_refs;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	T m_text[1];
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
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	Bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}

	int compareNoCase(const char *text) const;
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<UnsignedShort>(other) {}
	~UnicodeString() {}
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	void *m_name;
};

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

enum SnapshotType
{
	SNAPSHOT_SAVELOAD,
	SNAPSHOT_DEEPCRC_LOGICONLY,
	SNAPSHOT_DEEPCRC,
	SNAPSHOT_MAX
};

enum SaveCode
{
	SC_INVALID = -1,
	SC_OK,
	SC_NO_FILE_AVAILABLE,
	SC_FILE_NOT_FOUND,
	SC_UNABLE_TO_OPEN_FILE,
	SC_INVALID_XFER,
	SC_UNKNOWN_BLOCK,
	SC_INVALID_DATA,
	SC_ERROR
};

class SaveGameInfo
{
	public:
	unsigned char m_data[0x30];
};

class File
{
public:
	virtual ~File();
	virtual Bool open(const char *, int);
	virtual void close();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access);
};

#define TheFileSystem (*(FileSystem **)0x0134CB48)

// This is the BFME Xfer layout used by the neighboring landed body.  The
// three block operations below are qualified direct calls in this reader;
// only the two transfers shown in the retail body are dispatched virtually.
class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool IsStoring();
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
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
	unsigned char m_data[0x1c];
};

class Gen009D8CA0 : public Xfer
{
public:
	Gen009D8CA0(int first, int second, int third);
	~Gen009D8CA0();
	Bool readAt009D89E0(File *file, void *output);
};

class Rva009D8AA0
{
public:
	void apply();

private:
	unsigned char m_pad[0x14];
	void *m_stream;
};

class GameState : public SubsystemInterface, public Snapshot
{
public:
	GameState();
	virtual ~GameState();

	struct SnapshotBlock
	{
		Snapshot *snapshot;
		AsciiString blockName;
	};

	private:
	SnapshotBlock *findBlockInfoByToken(AsciiString token,
		SnapshotType which);

	public:
	SaveGameInfo *getSaveGameInfo()
	{
		return reinterpret_cast<SaveGameInfo *>(m_gameInfo);
	}
	Bool getSaveGameInfoFromFile(AsciiString filename,
		SaveGameInfo *saveGameInfo);

private:
	unsigned char m_snapshotLists[0x0c];
	unsigned char m_gameInfo[0x30];
	unsigned char m_tail[0x10];
};

// The assignment body is already matched at 0x0010CFF0.  This neutral ABI
// view avoids inventing a second SaveGameInfo operation or destructor.
class Rva0010CFF0
{
public:
	Rva0010CFF0 &operator=(const Rva0010CFF0 &other);
};

struct BfmeFormattedText
{
	void *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern "C" __declspec(dllimport) int __cdecl _stricmp(
	const char *left, const char *right);

static const char *SAVE_FILE_EOF = "SG_EOF";
extern "C" unsigned char bfmeStrBEYC[];

// ?getSaveGameInfoFromFile@GameState@@QAE_NVAsciiString@@PAVSaveGameInfo@@@Z
Bool GameState::getSaveGameInfoFromFile(AsciiString filename,
	SaveGameInfo *saveGameInfo)
{
	File *file;
	unsigned int version;
	Bool done = false;
	SnapshotBlock *blockInfo;
	BfmeFormattedText error;

	if (filename.isEmpty() || saveGameInfo == 0)
		return false;

	const char *path = filename.str();
	file = TheFileSystem->openFile(path, 0x41);
	if (file == 0)
		return false;

	Gen009D8CA0 xferLoad(0, 0, 0);
	if (!xferLoad.readAt009D89E0(file, &version))
	{
		file->close();
		return false;
	}

	if (version > 1)
	{
		file->close();
		return false;
	}

	while (done == false)
	{
		AsciiString token;

		// Retail releases the token before testing the next EOF state.
		static_cast<Xfer *>(&xferLoad)->xferAsciiString(&token);
		if (token.compareNoCase(SAVE_FILE_EOF) == 0)
			{
				done = true;
			}
			else
			{
				blockInfo = findBlockInfoByToken(token, SNAPSHOT_SAVELOAD);
				if (blockInfo == 0)
				{
					bfmeFormatText(&error, 0, 0);
					_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
				}

				if (_stricmp(token.str(), "CHUNK_GameState") == 0)
				{
					GameState tempGameState;
					try
					{
						xferLoad.Xfer::beginBlock((const char *)bfmeStrBEYC);
						static_cast<Xfer *>(&xferLoad)->xferSnapshot(
							&tempGameState);
						xferLoad.Xfer::endBlock();
					}
					catch (...)
					{
						throw;
					}

					reinterpret_cast<Rva0010CFF0 *>(saveGameInfo)->operator=(
						*reinterpret_cast<const Rva0010CFF0 *>(
							tempGameState.getSaveGameInfo()));
					done = true;
				}
				else
				{
					xferLoad.Xfer::skipBlock((const char *)bfmeStrBEYC);
				}
		}
	}

	reinterpret_cast<Rva009D8AA0 *>(&xferLoad)->apply();
	file->close();
	return true;
}
