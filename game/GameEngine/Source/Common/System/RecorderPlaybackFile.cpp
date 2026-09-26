// cl: /DNDEBUG /DWIN32 /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ?playbackFile@RecorderClass@@QAE_NVAsciiString@@@Z  retail 0x0009B150, 636 bytes.
// Identity: the matched callers reallyLoadReplay (0x004E08D0) and
// restartMissionMenu (0x00569E10) call RecorderClass::playbackFile(AsciiString)
// through its pinned ILT 0x00028B2D; the body is ZH Recorder.cpp playbackFile
// line for line plus BFME's saved GlobalData pair, which
// RecorderClass::restoreGlobalDataFields (0x00097360) puts back.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct _iobuf;
typedef _iobuf FILE;
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *, unsigned int, unsigned int, FILE *);

// ReplayHeader's UnicodeString slots: retail zeroes the pointer inline, while
// unicode_string.h declares the ctor out of line. ~ReplayHeader (0x00098450)
// releases them.
struct RvaUnicodeString
{
	void *m_data;
	RvaUnicodeString() : m_data(0) {}
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
	Int m_dword04;
	Int m_crcInterval;
	char m_gap0c[0x4c - 0x0c];
	UnsignedInt m_seed;
};

// ZH Recorder.cpp CRCInfo; the ctor body order is retail's store order.
class CRCInfo
{
public:
	CRCInfo()
	{
		m_localPlayer = ~0U;
		m_skippedOne = false;
		m_sawCRCMismatch = false;
	}
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

// Same spelling as the matched callers RestartMissionMenu, SoloMordorFade_LoadGame
// and FadeScreenRegionToMapBlack: the two-Bool GameLogic::clearGameData (0x00396B00)
// reached through ILT 0x0001C46D.
class BfmeGameLogicPause
{
public:
	void clearGameData(Bool showScoreScreen, Bool unknown);
};

class GlobalData
{
public:
	char m_head[0xB84];
	AsciiString m_pendingFile;
	char m_gapB88[0x11EC - 0xB88];
	unsigned char m_byte11EC;
	char m_gap11ED[3];
	Int m_dword11F0;
};

class SubsystemInterface
{
public:
	virtual void slot00();
	AsciiString m_name;
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
		AsciiString gameOptions;
		Int localPlayerIndex;
		AsciiString filename;
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

protected:
	void readNextFrame();

private:
	CRCInfo *m_crcInfo;
	FILE *m_file;
	char m_gap10[0x18 - 0x10];
	Int m_mode;
	AsciiString m_currentReplayFilename;
	GameInfo m_gameInfo;
	char m_gap70[0x2A8 - 0x70];
	Bool m_doingAnalysis;
	char m_gap2A9[3];
	Int m_dword2AC;
};

extern BfmeGameLogicPause *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
extern MessageStream *TheMessageStream;
extern Int REPLAY_CRC_INTERVAL;

// File statics of the recorder TU: nothing outside it takes their address, so
// MSVC schedules the GlobalData loads ahead of these stores as retail does.
static Int g_recorderSavedGlobalValue;
static unsigned char g_recorderSavedGlobalFlag;

void InitRandom(UnsignedInt seed);

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

	g_recorderSavedGlobalFlag = TheWritableGlobalData->m_byte11EC;
	g_recorderSavedGlobalValue = TheWritableGlobalData->m_dword11F0;
	TheWritableGlobalData->m_byte11EC = header.desyncGame;
	TheWritableGlobalData->m_dword11F0 = header.headerTail;
	TheWritableGlobalData->m_pendingFile = m_gameInfo.getMap();

	m_crcInfo = new CRCInfo;
	m_crcInfo->setLocalPlayer(header.localPlayerIndex);
	REPLAY_CRC_INTERVAL = m_gameInfo.getCRCInterval();

	Int difficulty = 0;
	fread(&difficulty, sizeof(difficulty), 1, m_file);
	fread(&m_dword2AC, sizeof(m_dword2AC), 1, m_file);
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
