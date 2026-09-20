// ?playbackFile@RecorderClass@@QAE_NVAsciiString@@@Z
// partial score=0.92 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "string_base.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct _iobuf;
typedef _iobuf FILE;
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *, unsigned int, unsigned int, FILE *);

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
		return *this;
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	~UnicodeString() {}
};

struct RvaAsciiString
{
	volatile void *m_data;
	__forceinline RvaAsciiString() : m_data(0) {}
	RvaAsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
		return *this;
	}
};

struct RvaUnicodeString
{
	volatile void *m_data;
	__forceinline RvaUnicodeString() : m_data(0) {}
};

struct RvaSystemTime
{
	unsigned short values[8];
};

class GameInfo
{
public:
	AsciiString getMap() const;
	Int getCRCInterval() const { return m_crcInterval; }
	UnsignedInt getSeed() const { return m_seed; }

private:
	void *m_vtable;
	Int m_state;
	Int m_crcInterval;
	char m_gap0c[0x4c - 0x0c];
	UnsignedInt m_seed;
};

class CRCInfo
{
public:
	CRCInfo() : m_sawCRCMismatch(false), m_skippedOne(false), m_localPlayer(~0U) {}
	void setLocalPlayer(UnsignedInt value) { m_localPlayer = value; }

private:
	Bool m_sawCRCMismatch;
	Bool m_skippedOne;
	std::list<UnsignedInt> m_data;
	UnsignedInt m_localPlayer;
};

class GameMessage
{
public:
	void appendIntegerArgument(Int value);
};

class MessageStream
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual GameMessage *appendMessage(Int type);
};

class GameLogic
{
public:
	void clearGameData(Bool keepObjects, Bool keepPlayers);
};

class GlobalData
{
public:
	char m_head[0xB84];
	AsciiString m_pendingFile;
	char m_gapB88[0x11EC - 0xB88];
	unsigned char m_replayFlag;
	char m_gap11ED[3];
	Int m_replayValue;
};

class SubsystemInterface
{
public:
	virtual void slot00();
	Int m_state;
};

class RecorderClass : public SubsystemInterface
{
public:
	struct ReplayHeader
	{
		~ReplayHeader();
		Int startTime;
		Int endTime;
		UnsignedInt frameDuration;
		Int networkCRCInterval;
		Int originalGameMode;
		Bool quitEarly;
		Bool playerDiscons[8];
		char gap1[3];
		RvaAsciiString gameOptions;
		Int localPlayerIndex;
		RvaAsciiString filename;
		Bool forPlayback;
		RvaUnicodeString replayName;
		RvaSystemTime timeVal;
		RvaUnicodeString versionString;
		RvaUnicodeString versionTimeString;
		UnsignedInt versionNumber;
		UnsignedInt exeCRC;
		UnsignedInt iniCRC;
		Bool desyncGame;
		char gap2[3];
		UnsignedInt headerTail;
	};

	Bool playbackFile(AsciiString filename);
	Bool readReplayHeader(ReplayHeader &header);
	void readNextFrame();

private:
	CRCInfo *m_crcInfo;
	FILE *m_file;
	AsciiString m_fileName;
	Int m_currentFilePosition;
	Int m_mode;
	AsciiString m_currentReplayFilename;
	GameInfo m_gameInfo;
	char m_gameInfoTail[0x278 - sizeof(GameInfo)];
	Int m_networkCRCInterval;
	Int m_originalGameMode;
	Int m_nextFrame;
	Int m_seedOrDesync;
	Bool m_doingAnalysis;
	char m_pad2A9[3];
	Int m_gameMode;
};

extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
extern MessageStream *TheMessageStream;
extern Int g_recorderSavedGlobalValue;
extern unsigned char g_recorderSavedGlobalFlag;
extern Int REPLAY_CRC_INTERVAL;

void InitRandom(UnsignedInt seed);

// The retail target currently has an address-derived ledger name.  The matched
// callers prove that this body is GameLogic::clearGameData(Bool, Bool).
#pragma comment(linker, "/alternatename:?clearGameData@GameLogic@@QAEX_N0@Z=?push@U4Sink0060D3B0@@QAEX_N0@Z")
#pragma comment(linker, "/alternatename:??1ReplayHeader@RecorderClass@@QAE@XZ=??1BfmeOwnVUL@@QAE@XZ")

Bool RecorderClass::playbackFile(AsciiString filename)
{
	if (!m_doingAnalysis)
		TheGameLogic->clearGameData(false, false);

	m_mode = 1;
	ReplayHeader header;
	header.forPlayback = true;
	header.filename = filename;
	Bool success = readReplayHeader(header);
	if (!success)
		return false;

	g_recorderSavedGlobalFlag = TheWritableGlobalData->m_replayFlag;
	g_recorderSavedGlobalValue = TheWritableGlobalData->m_replayValue;
	TheWritableGlobalData->m_replayFlag = header.desyncGame;
	TheWritableGlobalData->m_replayValue = header.headerTail;
	TheWritableGlobalData->m_pendingFile = m_gameInfo.getMap();

	m_crcInfo = new CRCInfo;
	m_crcInfo->setLocalPlayer(header.localPlayerIndex);
	REPLAY_CRC_INTERVAL = m_gameInfo.getCRCInterval();

	Int difficulty = 0;
	fread(&difficulty, sizeof(difficulty), 1, m_file);
	fread(&m_gameMode, sizeof(m_gameMode), 1, m_file);
	Int rankPoints = 0;
	fread(&rankPoints, sizeof(rankPoints), 1, m_file);
	Int maxFPS = 0;
	fread(&maxFPS, sizeof(maxFPS), 1, m_file);
	readNextFrame();

	if (!m_doingAnalysis)
	{
		GameMessage *message = TheMessageStream->appendMessage(0x1E);
		message->appendIntegerArgument(3);
		message->appendIntegerArgument(difficulty);
		message->appendIntegerArgument(rankPoints);
		if (maxFPS != 0)
			message->appendIntegerArgument(maxFPS);
		InitRandom(m_gameInfo.getSeed());
	}

	m_currentReplayFilename = filename;
	return true;
}
