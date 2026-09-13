// cl: /ICode/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc

#include "string_base.h"

extern "C" __declspec(dllimport) int __cdecl strncmp(const char *left, const char *right, unsigned int count);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *str);

struct _iobuf;
typedef _iobuf FILE;
extern "C" __declspec(dllimport) FILE *__cdecl fopen(const char *name, const char *mode);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *buffer, unsigned int size, unsigned int count, FILE *file);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *file);
extern "C" __declspec(dllimport) int __cdecl fgetpos(FILE *file, long *position);

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

extern "C" int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

static int stringLength(const char *text)
{
	return (int)strlen(text);
}

enum
{
	TRUE = 1,
	FALSE = 0
};

enum
{
	MAX_SLOTS = 8
};

struct GenrepBuffer
{
	char prefix[4];
	char text[12];
};

// The BFME string headers expose the StringBase bodies at these call sites,
// while the object itself is still one data pointer.  Keep the forwarding
// classes local so this TU does not change the shared ZH-facing headers.
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
		return *this;
	}

	const char *str(void) const
	{
		return m_data ? &m_data->data[0] : (const char *)0x0107388B;
	}

	void concat(const char *text, int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	void concat(const char *text)
	{
		concat(text, text ? stringLength(text) : 0);
	}

};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &that) : StringBase<unsigned short>(that) {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	~UnicodeString() {}

	UnicodeString &operator=(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&that);
		return *this;
	}
};

struct RvaSystemTime
{
	unsigned short year;
	unsigned short month;
	unsigned short dayOfWeek;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	unsigned short second;
	unsigned short milliseconds;
};

struct RvaReplayIP
{
	UnsignedInt address;
	UnsignedInt port;
};

// The only named GameInfo slots needed by this body are the two leading
// BFME virtuals, reset, and startGame.  The field view places localIP at the
// witnessed GameInfo+0x34 offset (RecorderClass+0x54).
class GameSlot
{
public:
	virtual void unused(void);

	Int m_state;
	char m_bfmeGap[0x28];
	RvaReplayIP m_ip;

	Int getState(void) const { return m_state; }
};

class GameInfo
{
public:
	virtual void unused0(void);
	virtual void unused1(void);
	virtual void reset(void);
	virtual void startGame(Int unused);

	void enterGame(void);
	void endGame(void);
	GameSlot *getSlot(Int index);
	const GameSlot *getConstSlot(Int index) const;

	char m_bfmePrefix[0x30];
	RvaReplayIP m_localIP;
	char m_bfmeSuffix[0x1c];
};

class ReplayGameInfo : public GameInfo
{
	ReplayGameInfo(void);
	char m_bfmeSlots[8 * 0x44];
};

class Rva00099490RecorderClass;

// These declarations select the already matched Recorder and parser bodies;
// their BFME class storage is supplied by the mirror below.
class RecorderClass
{
public:
	static AsciiString getReplayDir(void);
	friend class Rva00099490RecorderClass;

	protected:
	AsciiString readAsciiString(void);
	UnicodeString readUnicodeString(void);
};

extern Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, Bool includeSlots) throw();

class SubsystemInterface
{
public:
	virtual void subsystemSlot0(void);
	Int m_state;
};

class Rva00099490RecorderClass : public SubsystemInterface
{
public:
	struct ReplayHeader
	{
		Int startTime;
		Int endTime;
		UnsignedInt frameDuration;
		Int networkCRCInterval;
		Int originalGameMode;
		Bool quitEarly;
		Bool playerDiscons[MAX_SLOTS];
		char m_bfmeGap[3];
		AsciiString gameOptions;
		Int localPlayerIndex;
		AsciiString filename;
		Bool forPlayback;
		UnicodeString replayName;
		RvaSystemTime timeVal;
		UnicodeString versionString;
		UnicodeString versionTimeString;
		UnsignedInt versionNumber;
		UnsignedInt exeCRC;
		UnsignedInt iniCRC;
		Bool desyncGame;
		char m_bfmeGap2[3];
		UnsignedInt headerTail;
	};

	// ?readReplayHeader@RecorderClass@@QAE_NAAUReplayHeader@1@@Z
	Bool readReplayHeader(ReplayHeader &header);
private:
	char m_bfmeHead[0x04];
	FILE *m_file;
	char m_bfmeGap[0x10];
	ReplayGameInfo m_gameInfo;
	Int m_networkCRCInterval;
	Int m_originalGameMode;
	Int m_numPlayers;
	Int m_seedOrDesync;
};

// ?readReplayHeader@RecorderClass@@QAE_NAAUReplayHeader@1@@Z
Bool Rva00099490RecorderClass::readReplayHeader(ReplayHeader &header)
{
	AsciiString filepath = RecorderClass::getReplayDir();
	filepath.concat(header.filename.str());
	m_file = fopen(filepath.str(), "rb");
	if (m_file == 0)
		return FALSE;

	GenrepBuffer genrep;
	fread(&genrep.text, sizeof(char), 8, m_file);
	genrep.text[8] = 0;
	if (strncmp(genrep.text, "BFMERE", 8) != 0)
	{
		fclose(m_file);
		m_file = 0;
		return FALSE;
	}

	fread(&header.startTime, sizeof(header.startTime), 1, m_file);
	fread(&header.endTime, sizeof(header.endTime), 1, m_file);
	fread(&header.frameDuration, sizeof(header.frameDuration), 1, m_file);
	fread(&header.networkCRCInterval, sizeof(header.networkCRCInterval), 1, m_file);
	m_networkCRCInterval = header.networkCRCInterval;
	fread(&header.originalGameMode, sizeof(header.originalGameMode), 1, m_file);
	m_originalGameMode = header.originalGameMode;
	fread(&header.quitEarly, sizeof(header.quitEarly), 1, m_file);
	for (Int i = 0; i < MAX_SLOTS; ++i)
		fread(&header.playerDiscons[i], sizeof(header.playerDiscons[i]), 1, m_file);

	header.replayName = reinterpret_cast<RecorderClass *>(this)->readUnicodeString();
	fread(&header.timeVal, sizeof(header.timeVal), 1, m_file);
	header.versionString = reinterpret_cast<RecorderClass *>(this)->readUnicodeString();
	header.versionTimeString = reinterpret_cast<RecorderClass *>(this)->readUnicodeString();
	fread(&header.versionNumber, sizeof(header.versionNumber), 1, m_file);
	fread(&header.exeCRC, sizeof(header.exeCRC), 1, m_file);
	fread(&header.iniCRC, sizeof(header.iniCRC), 1, m_file);
	fread(&header.desyncGame, sizeof(header.desyncGame), 1, m_file);
	fread(&header.headerTail, sizeof(header.headerTail), 1, m_file);
	{
		struct LocalFilePosition { long low; long high; } filePosition;
		fgetpos(m_file, ((long *)&filePosition) + 1);
	}
	header.gameOptions = reinterpret_cast<RecorderClass *>(this)->readAsciiString();

	GameInfo *gameInfo = &m_gameInfo;
	gameInfo->reset();
	gameInfo->enterGame();
	if (!ParseAsciiStringToGameInfo(gameInfo, header.gameOptions, TRUE))
	{
		fclose(m_file);
		m_file = 0;
		return FALSE;
	}

	gameInfo->startGame(0);
	AsciiString playerIndex = reinterpret_cast<RecorderClass *>(this)->readAsciiString();
	header.localPlayerIndex = atoi(playerIndex.str());
	if (header.localPlayerIndex < -1 || header.localPlayerIndex >= MAX_SLOTS)
	{
		gameInfo->endGame();
		gameInfo->reset();
		fclose(m_file);
		m_file = 0;
		return FALSE;
	}

	if (header.localPlayerIndex >= 0)
	{
		GameSlot *slot = gameInfo->getSlot(header.localPlayerIndex);
		m_gameInfo.m_localIP.address = slot->m_ip.address;
		m_gameInfo.m_localIP.port = slot->m_ip.port;
	}

	if (!header.forPlayback)
	{
		gameInfo->endGame();
		gameInfo->reset();
		fclose(m_file);
		m_file = 0;
	}

	m_numPlayers = 0;
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (gameInfo->getConstSlot(i)->getState() == 5)
			++m_numPlayers;
	}
	m_seedOrDesync = header.localPlayerIndex;
	return TRUE;
}
