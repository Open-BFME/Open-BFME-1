// ?xfer@GameStateMap@@UAEXPAVXfer@@@Z
// partial score=0.64 date=2026-09-10
// Scratch-only BFME ABI probe for GameStateMap::xfer.  This file is not a
// production source or ledger claim.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define TRUE true
#define FALSE false
#define NULL 0
#define GAME_SKIRMISH 2
#define SC_INVALID_DATA 7

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

protected:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	void set(const StringBase<T> &other);
	void releaseBuffer();
	BfmeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<UnsignedShort>(other) {}
	~UnicodeString() {}
};

enum SaveFileType
{
	SAVE_FILE_TYPE_NORMAL,
	SAVE_FILE_TYPE_MISSION
};

struct SaveGameInfo
{
	AsciiString saveGameMapName;
	AsciiString pristineMapName;
	AsciiString mapLabel;
	unsigned char date[0x10];
	AsciiString campaignSide;
	Int missionNumber;
	UnicodeString description;
	SaveFileType saveFileType;
	AsciiString missionMapName;
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface() {}
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(void *xfer) = 0;
	virtual void xfer(void *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

struct BfmeGameStateMapXferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual Bool isStoring();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(BfmeGameStateMapXferVersion *version);
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
	virtual void slot27();
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

class GameLogic
{
public:
	void startNewGame(Bool loadSaveGame);
};

class GameClient {};

class GlobalData
{
	unsigned char m_pad[8];

public:
	AsciiString m_mapName;
};

class GameState
{
public:
	SaveGameInfo *getSaveGameInfo()
	{
		return reinterpret_cast<SaveGameInfo *>(
			reinterpret_cast<unsigned char *>(this) + 0x18);
	}

	AsciiString getMapLeafName(const AsciiString &path) const;
	AsciiString getFilePathInSaveDirectory(const AsciiString &filename) const;
	Bool isInSaveDirectory(const AsciiString &filename) const;
	AsciiString realMapPathToPortableMapPath(const AsciiString &path) const;
	AsciiString portableMapPathToRealMapPath(const AsciiString &path) const;
};

class GameStateMap : public SubsystemInterface, public Snapshot
{
public:
	virtual void xfer(Xfer *xfer);
};

class GameInfo
{
public:
	void init();
	virtual void reset();
	void clearSlotList();
};

class SkirmishGameInfo : public GameInfo
{
	unsigned char m_data[0x278];
};

extern GameState *TheGameState;
extern GameLogic *TheGameLogic;
extern GameClient *TheGameClient;
extern GlobalData *TheGlobalData;
extern GlobalData *TheWritableGlobalData;
extern SkirmishGameInfo *TheSkirmishGameInfo;

static void embedPristineMap(AsciiString map, Xfer *xfer);
static void embedInUseMap(AsciiString map, Xfer *xfer);
static void extractAndSaveMap(AsciiString map, Xfer *xfer);

static __forceinline void setLoading(GameLogic *logic, Bool value)
{
	*(Bool *)((unsigned char *)logic + 0x6A) = value;
}

static __forceinline Int gameMode(GameLogic *logic)
{
	return *(Int *)((unsigned char *)logic + 0x10C);
}

static __forceinline void setGameMode(GameLogic *logic, Int value)
{
	*(Int *)((unsigned char *)logic + 0x10C) = value;
}

static __forceinline Int objectID(GameLogic *logic)
{
	return *(Int *)((unsigned char *)logic + 0x108);
}

static __forceinline void setObjectID(GameLogic *logic, Int value)
{
	*(Int *)((unsigned char *)logic + 0x108) = value;
}

static __forceinline Int drawableID(GameClient *client)
{
	return *(Int *)((unsigned char *)client + 0x28);
}

static __forceinline void setDrawableID(GameClient *client, Int value)
{
	*(Int *)((unsigned char *)client + 0x28) = value;
}

void GameStateMap::xfer(Xfer *xfer)
{
	if (xfer->isLoading())
		setLoading(TheGameLogic, TRUE);

	BfmeGameStateMapXferVersion version = { 1, 2 };
	xfer->xferVersion(&version);

	SaveGameInfo *saveGameInfo = TheGameState->getSaveGameInfo();
	Bool firstSave = FALSE;
	if (xfer->isStoring())
	{
		AsciiString mapLeafName =
			TheGameState->getMapLeafName(TheGlobalData->m_mapName);
		saveGameInfo->saveGameMapName =
			TheGameState->getFilePathInSaveDirectory(mapLeafName);

		{
			AsciiString tmp = TheGameState->realMapPathToPortableMapPath(
				saveGameInfo->saveGameMapName);
			xfer->xferAsciiString(&tmp);
		}

		if (!TheGameState->isInSaveDirectory(TheGlobalData->m_mapName))
		{
			saveGameInfo->pristineMapName = TheGlobalData->m_mapName;
			firstSave = TRUE;
		}

		{
			AsciiString tmp = TheGameState->realMapPathToPortableMapPath(
				saveGameInfo->pristineMapName);
			xfer->xferAsciiString(&tmp);
		}

		if (version.m_currentVersion >= 2)
		{
			Int mode = gameMode(TheGameLogic);
			xfer->xferInt(&mode);
		}
	}
	else
	{
		AsciiString tmp;
		xfer->xferAsciiString(&tmp);
		saveGameInfo->saveGameMapName =
			TheGameState->portableMapPathToRealMapPath(tmp);
		if (!TheGameState->isInSaveDirectory(saveGameInfo->saveGameMapName))
			throw SC_INVALID_DATA;
		TheWritableGlobalData->m_mapName = saveGameInfo->saveGameMapName;
		xfer->xferAsciiString(&saveGameInfo->pristineMapName);
		saveGameInfo->pristineMapName =
			TheGameState->portableMapPathToRealMapPath(
				saveGameInfo->pristineMapName);
		if (version.m_currentVersion >= 2)
		{
			Int mode;
			xfer->xferInt(&mode);
			setGameMode(TheGameLogic, mode);
		}
	}

	if (xfer->isStoring())
	{
		if (firstSave)
			embedPristineMap(saveGameInfo->pristineMapName, xfer);
		else
			embedInUseMap(saveGameInfo->saveGameMapName, xfer);
	}
	else
	{
		extractAndSaveMap(saveGameInfo->saveGameMapName, xfer);
	}

	Int highObjectID = objectID(TheGameLogic);
	xfer->xferInt(&highObjectID);
	setObjectID(TheGameLogic, highObjectID);

	Int highDrawableID = drawableID(TheGameClient);
	xfer->xferInt(&highDrawableID);
	setDrawableID(TheGameClient, highDrawableID);

	if (gameMode(TheGameLogic) == GAME_SKIRMISH)
	{
		if (TheSkirmishGameInfo == NULL)
		{
			TheSkirmishGameInfo = new SkirmishGameInfo;
			TheSkirmishGameInfo->init();
			TheSkirmishGameInfo->clearSlotList();
			TheSkirmishGameInfo->reset();
		}
		xfer->xferSnapshot(reinterpret_cast<Snapshot *>(
			reinterpret_cast<unsigned char *>(TheSkirmishGameInfo) + 0x60));
	}
	else if (TheSkirmishGameInfo)
	{
		delete TheSkirmishGameInfo;
		TheSkirmishGameInfo = NULL;
	}

	if (xfer->isLoading())
	{
		TheGameLogic->startNewGame(TRUE);
		setLoading(TheGameLogic, FALSE);
	}
}

__declspec(noinline) static void embedPristineMap(AsciiString map, Xfer *xfer)
{
	if (xfer == 0)
		map.str();
}

__declspec(noinline) static void embedInUseMap(AsciiString map, Xfer *xfer)
{
	if (xfer == 0)
		map.str();
}

__declspec(noinline) static void extractAndSaveMap(AsciiString map, Xfer *xfer)
{
	if (xfer == 0)
		map.str();
}
