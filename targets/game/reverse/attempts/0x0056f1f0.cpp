// ?prepareFinish@Rva56E070StateOwner@@QAEXXZ
// partial score=0.49 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
//
// BFME anonymous body 0x0056F1F0, 2286 bytes.  The finishCurrent caller and
// the 0x00006B3B ILT prove the prepareFinish identity.  The constructor at
// 0x0056A2F0 proves the list<AvailableGameInfo> header at this+0x284.
// NOT byte matched: 2289/2286 B, 1171 masked differing bytes, shape 0.970.
// 2026-09-28 opus-5.5 rewrite from the retail decode and the matched sibling
// GameState::populateSaveGameListbox (0x001121A0, same column order):
//   RecorderClass is 0x2B4 bytes (EH extent ebp-0x2C0..EH record; witness
//   m_doingAnalysis +0x2A8) -> frame 0x634 and every EH slot aligned;
//   columns are map/name/time/date, SetItemData(listbox,&back(),index);
//   availableGameInfo.filename = asciistr (not the description);
//   ReplayGameInfo has a real destructor (0x00099000, EH state 8);
//   the version temp lives inside the && (flag at ebp-0x62C);
//   set(const char*) is set(s, s ? strlen(s) : 0); concat(AsciiString) inline;
//   static STLport so the tree helpers are direct calls.
// Remaining: `this` in EDI (retail ESI, spilled to ebp-0x61C) and the
// isLastReplay/versionMatches BL-vs-[esp+0x13] swap, which turns the color
// select branchless; locals therefore sit on permuted slots.
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE

#include <list>
#include <new>
#include <set>

#include "string_base.h"
#include <string.h>
#pragma intrinsic(strlen)

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

enum
{
	TRUE = 1,
	FALSE = 0
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer();
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}

	AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&other);
		return *this;
	}

	void set(const char *text, Int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}

	void set(const char *text)
	{
		set(text, text ? (Int)strlen(text) : 0);
	}

	const char *str() const
	{
		return m_data ? (const char *)((char *)m_data + 8)
			: (const char *)0x0107388B;
	}

	Int getLength() const
	{
		return m_data ? *(const UnsignedShort *)((const char *)m_data + 4) : 0;
	}

	const char *reverseFind(char c) const
	{
		const char *first = str();
		const char *last = first + getLength();
		while (last != first)
		{
			--last;
			if (*last == c)
				return last;
		}
		return 0;
	}

	void concat(const char *text, Int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	void concat(const AsciiString &other)
	{
		concat(other.str(), other.getLength());
	}

	Int compareNoCase(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compareNoCase(
			*(const StringBase<char> *)&other);
	}

private:
	void *m_data;
};

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString()
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}

	void set(const char *text, Int length);

	void set(const char *text)
	{
		set(text, text ? (Int)strlen(text) : 0);
	}

	RetailLayoutString &operator=(const RetailLayoutString &other)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&other);
		return *this;
	}

	const char *str() const
	{
		return m_data ? (const char *)((char *)m_data + 8)
			: (const char *)0x0107388B;
	}

	Int getLength() const
	{
		return m_data ? *(const UnsignedShort *)((const char *)m_data + 4) : 0;
	}

	void concat(const char *text, Int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	void concat(const AsciiString &other)
	{
		concat(other.str(), other.getLength());
	}

	Int compareNoCase(const RetailLayoutString &other) const
	{
		return ((const StringBase<char> *)this)->compareNoCase(
			*(const StringBase<char> *)&other);
	}

	operator const AsciiString &() const
	{
		return *(const AsciiString *)this;
	}

private:
	void *m_data;
};

class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<UnsignedShort> *)this)->StringBase<UnsignedShort>::StringBase(
			*(const StringBase<UnsignedShort> *)&other);
	}
	~UnicodeString()
	{
		((StringBase<UnsignedShort> *)this)->releaseBuffer();
	}

	UnicodeString &operator=(const UnicodeString &other)
	{
		((StringBase<UnsignedShort> *)this)->set(
			*(const StringBase<UnsignedShort> *)&other);
		return *this;
	}

	void set(const UnicodeString &other)
	{
		((StringBase<UnsignedShort> *)this)->set(
			*(const StringBase<UnsignedShort> *)&other);
	}

	void translate(const AsciiString &other);

	Int compare(const UnicodeString &other) const
	{
		return ((const StringBase<UnsignedShort> *)this)->compare(
			*(const StringBase<UnsignedShort> *)&other);
	}

private:
	void *m_data;
};

namespace rts
{
	template <typename T>
	struct less_than_nocase
	{
		bool operator()(const T &, const T &) const;
	};
}

typedef std::set<AsciiString, rts::less_than_nocase<AsciiString> > FilenameList;

class GameWindow;

Int GadgetListBoxGetNumColumns(GameWindow *listbox);
void GadgetListBoxSetColumnWidths(GameWindow *listbox, Int count, Int *widths);
void GadgetListBoxReset(GameWindow *listbox);
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Int color, Int row, Int column, Bool overwrite);
void GadgetListBoxSetSelected(GameWindow *listbox, Int selectIndex);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, Int row, Int column = 0);

class GameTextInterface
{
};

extern GameTextInterface *TheGameText;

class GameTextCharView
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

struct _SYSTEMTIME
{
	UnsignedShort wYear;
	UnsignedShort wMonth;
	UnsignedShort wDayOfWeek;
	UnsignedShort wDay;
	UnsignedShort wHour;
	UnsignedShort wMinute;
	UnsignedShort wSecond;
	UnsignedShort wMilliseconds;
};

UnicodeString getUnicodeDateBuffer(_SYSTEMTIME timeVal);
UnicodeString getUnicodeTimeBuffer(_SYSTEMTIME timeVal);

struct SaveDate
{
	UnsignedShort year;
	UnsignedShort month;
	UnsignedShort day;
	UnsignedShort dayOfWeek;
	UnsignedShort hour;
	UnsignedShort minute;
	UnsignedShort second;
	UnsignedShort milliseconds;
};

struct SaveGameInfo
{
	SaveGameInfo();
	~SaveGameInfo();

	AsciiString saveGameMapName;
	AsciiString pristineMapName;
	AsciiString mapLabel;
	SaveDate date;
	AsciiString campaignSide;
	Int missionNumber;
	UnicodeString description;
	Int saveFileType;
	AsciiString missionMapName;
};

struct AvailableGameInfo
{
	__forceinline AvailableGameInfo() : filename(), saveGameInfo() {}
	AvailableGameInfo(const AvailableGameInfo &other);
	~AvailableGameInfo();

	AsciiString filename;
	SaveGameInfo saveGameInfo;
	AvailableGameInfo *next;
	AvailableGameInfo *prev;
};

struct AvailableGameInfoStorage
{
	char bytes[0x3c];
};

struct RvaReplayIP
{
	UnsignedInt address;
	UnsignedInt port;
};

class GameSlot
{
public:
	virtual void unused();

	Int m_state;
	char m_bfmeGap[0x28];
	RvaReplayIP m_ip;
};

class GameInfo
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void reset();
	virtual void startGame(Int unused);

	void enterGame();
	void endGame();
	GameSlot *getSlot(Int index);
	const GameSlot *getConstSlot(Int index) const;
	AsciiString getMap() const;

	char m_bfmePrefix[0x30];
	RvaReplayIP m_localIP;
	AsciiString m_mapName;
	char m_bfmeSuffix[0x18];
};

class ReplayGameInfo : public GameInfo
{
public:
	ReplayGameInfo();
	~ReplayGameInfo();

	char m_bfmeSlots[8 * 0x44];
};

class SubsystemInterface
{
public:
	virtual void subsystemSlot0();
	Int m_state;
};

class RecorderClass : public SubsystemInterface
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
		Bool playerDiscons[8];
		char m_bfmeGap[3];
		AsciiString gameOptions;
		Int localPlayerIndex;
		RetailLayoutString filename;
		Bool forPlayback;
		UnicodeString replayName;
		_SYSTEMTIME timeVal;
		UnicodeString versionString;
		UnicodeString versionTimeString;
		UnsignedInt versionNumber;
		UnsignedInt exeCRC;
		UnsignedInt iniCRC;
		Bool desyncGame;
		char m_bfmeGap2[3];
		UnsignedInt headerTail;
		~ReplayHeader();
	};

	RecorderClass();
	virtual ~RecorderClass();
	Bool readReplayHeader(ReplayHeader &header);
	static AsciiString getReplayDir();
	static AsciiString getReplayExtention();
	AsciiString getLastReplayFileName();

private:
	char m_bfmeHead[4];
	void *m_file;
	char m_bfmeGap[0x10];
	ReplayGameInfo m_gameInfo;
	// BFME tail after the 0x278-byte m_gameInfo: the local's EH extent
	// (ebp-0x2C0 up to the EH record) makes the object 0x2B4 bytes, and the
	// layout witness puts m_doingAnalysis at +0x2A8.
	char m_rva298[0x10];
	Bool m_doingAnalysis;
	char m_rva2a9[0xb];
};

static AsciiString &replayHeaderGameOptions(RecorderClass::ReplayHeader &header)
{
	return *(AsciiString *)((char *)&header + 0x20);
}

static AsciiString &replayHeaderFilename(RecorderClass::ReplayHeader &header)
{
	return *(AsciiString *)((char *)&header + 0x28);
}

static Bool &replayHeaderForPlayback(RecorderClass::ReplayHeader &header)
{
	return *(Bool *)((char *)&header + 0x2c);
}

static UnicodeString &replayHeaderName(RecorderClass::ReplayHeader &header)
{
	return *(UnicodeString *)((char *)&header + 0x30);
}

static _SYSTEMTIME &replayHeaderTime(RecorderClass::ReplayHeader &header)
{
	return *(_SYSTEMTIME *)((char *)&header + 0x34);
}

static UnicodeString &replayHeaderVersion(RecorderClass::ReplayHeader &header)
{
	return *(UnicodeString *)((char *)&header + 0x44);
}

static UnsignedInt &replayHeaderVersionNumber(RecorderClass::ReplayHeader &header)
{
	return *(UnsignedInt *)((char *)&header + 0x4c);
}

static UnsignedInt &replayHeaderExeCRC(RecorderClass::ReplayHeader &header)
{
	return *(UnsignedInt *)((char *)&header + 0x50);
}

static UnsignedInt &replayHeaderIniCRC(RecorderClass::ReplayHeader &header)
{
	return *(UnsignedInt *)((char *)&header + 0x54);
}

// The landed reader is object-symboled under the precise BFME storage view;
// route this canonical call to that existing implementation.
#pragma comment(linker, "/alternatename:??1ReplayGameInfo@@QAE@XZ=??1BfmeOwnerBU@@QAE@XZ")

extern RecorderClass *TheRecorder;

class FileSystem
{
public:
	void getFileListInDirectory(const AsciiString &, const AsciiString &,
		FilenameList &, bool) const;
};

extern FileSystem *TheFileSystem;

#pragma comment(linker, "/alternatename:?getFileListInDirectory@FileSystem@@QBEXABVAsciiString@@0AAV?$set@VAsciiString@@U?$less_than_nocase@VAsciiString@@@rts@@V?$allocator@VAsciiString@@@_STL@@@_STL@@_N@Z=?bfmeListAllEBC@@YGXABVBfmeStrEBC@@0PAXH@Z")

class MapMetaData
{
public:
	UnicodeString bfme_getBaseDisplayName();
};

class MapCache
{
public:
	void updateCache();
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

// BFME's version text accessor returns its own string wrapper (UnicodeStringAL,
// BfmeVersionTextAL.cpp); the object is the Version singleton.
class UnicodeStringAL : public UnicodeString
{
public:
	~UnicodeStringAL() {}
};

class Version
{
public:
	UnsignedInt getVersionNumber();
};

class BfmeVersionAL
{
public:
	UnicodeStringAL bfmeVersionTextAL();
};

extern Version *TheVersion;

class GlobalDataView
{
public:
	char m_pad0[0xbc8];
	UnsignedInt m_iniCRC;
	char m_pad0bcc[4];
	UnsignedInt m_exeCRC;
};

extern GlobalDataView *TheWritableGlobalData;

extern int Rva0009B4B0(int left, int right);
extern Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options,
	Bool includeSlots);

// Recorder member at 0x00098130, matched under an address-derived owner.
class BfmeThingUXB
{
public:
	void bfmeGoUXB();
};

inline Int GameMakeColor(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha)
{
	return ((UnsignedInt)alpha << 24) | ((UnsignedInt)red << 16) |
		((UnsignedInt)green << 8) | blue;
}

class BfmeThingME
{
public:
	int bfmeTestME();
};

class Rva56E070StateOwner : public BfmeThingME
{
public:
	char m_pad0[0x258];
	Int m_state;
	Int m_direction;
	char m_pad260[4];
	GameWindow *m_arg264;
	GameWindow *m_arg268;
	void *m_context26c;
	Int m_mode270;
	Int m_value274;
	Bool m_flag278;
	char m_pad279[3];
	Int m_auxiliaryState;
	Bool m_flag280;
	char m_pad281[3];
	std::list<AvailableGameInfo> m_availableGames;

	void prepareFinish();
};

// ?prepareFinish@Rva56E070StateOwner@@QAEXXZ
void Rva56E070StateOwner::prepareFinish()
{
	if (!TheMapCache)
		return;

	GadgetListBoxReset(m_arg264);
	if (m_arg268)
		GadgetListBoxReset(m_arg268);

	m_availableGames.clear();

	Int widths[4] = { 30, 40, 15, 15 };
	if (GadgetListBoxGetNumColumns(m_arg264) < 4)
		GadgetListBoxSetColumnWidths(m_arg264, 4, widths);
	if (m_arg268 && GadgetListBoxGetNumColumns(m_arg268) < 4)
		GadgetListBoxSetColumnWidths(m_arg268, 4, widths);

	RetailLayoutString asciistr;
	RetailLayoutString asciisearch;
	asciisearch.set("*");
	asciisearch.concat(RecorderClass::getReplayExtention());

	FilenameList replayFilenames;
	FilenameList::iterator it;

	TheFileSystem->getFileListInDirectory(RecorderClass::getReplayDir(), asciisearch,
		replayFilenames, TRUE);

	TheMapCache->updateCache();

	UnsignedInt normalCount = 0;
	UnsignedInt autoCount = 0;
	if (m_mode270 == 3)
	{
		UnicodeString newText = ((GameTextCharView *)TheGameText)->fetch("GUI:NewSaveReplayFile");
		Int index = GadgetListBoxAddEntryText(m_arg264, newText,
			GameMakeColor(200, 200, 200, 255), -1, -1, TRUE);
		GadgetListBoxSetItemData(m_arg264, 0, index);
		++normalCount;
	}

	for (it = replayFilenames.begin(); it != replayFilenames.end(); ++it)
	{
		asciistr.set((*it).reverseFind('\\') + 1);

		RecorderClass::ReplayHeader header;
		header.forPlayback = FALSE;
		header.filename = asciistr;
		RecorderClass recorder;
		if (TheMapCache && recorder.readReplayHeader(header))
		{
			ReplayGameInfo info;
			if (ParseAsciiStringToGameInfo(&info, header.gameOptions, TRUE))
			{
				Bool isLastReplay = FALSE;
				AvailableGameInfo availableGameInfo;
				availableGameInfo.filename = asciistr;
				availableGameInfo.saveGameInfo.saveFileType = 3;
				availableGameInfo.next = 0;
				availableGameInfo.prev = 0;
				m_availableGames.push_back(availableGameInfo);

				UnicodeString replayNameToShow = header.replayName;
				AsciiString lastReplayFName = TheRecorder->getLastReplayFileName();
				lastReplayFName.concat(RecorderClass::getReplayExtention());
				if (lastReplayFName.compareNoCase(asciistr) == 0)
				{
					replayNameToShow = ((GameTextCharView *)TheGameText)->fetch("GUI:LastReplay");
					isLastReplay = TRUE;
				}

				UnicodeString displayDate = getUnicodeDateBuffer(header.timeVal);
				UnicodeString displayTime = getUnicodeTimeBuffer(header.timeVal);

				UnicodeString mapStr;
				const MapMetaData *md = TheMapCache->findMap(info.getMap());
				if (!md)
					mapStr.translate(info.getMap());
				else
					mapStr = const_cast<MapMetaData *>(md)->bfme_getBaseDisplayName();

				Bool versionMatches =
					header.versionString.compare(((BfmeVersionAL *)TheVersion)->bfmeVersionTextAL()) == 0 &&
					header.versionNumber == TheVersion->getVersionNumber() &&
					header.exeCRC == (UnsignedInt)Rva0009B4B0(TheWritableGlobalData->m_exeCRC, TheWritableGlobalData->m_exeCRC) &&
					header.iniCRC == TheWritableGlobalData->m_iniCRC;

				Int color = versionMatches ? -1 : (Int)0xff808080;
				GameWindow *listbox = isLastReplay ? m_arg268 : m_arg264;

				Int index = GadgetListBoxAddEntryText(listbox, mapStr, color, -1, 0, TRUE);
				GadgetListBoxAddEntryText(listbox, replayNameToShow, color, index, 1, TRUE);
				GadgetListBoxAddEntryText(listbox, displayTime, color, index, 2, TRUE);
				GadgetListBoxAddEntryText(listbox, displayDate, color, index, 3, TRUE);
				GadgetListBoxSetItemData(listbox, &m_availableGames.back(), index);
				if (isLastReplay)
					++autoCount;
				else
					++normalCount;
			}
			((BfmeThingUXB *)&recorder)->bfmeGoUXB();
		}
	}

	if (normalCount > 0)
	{
		GadgetListBoxSetSelected(m_arg264, 0);
		GadgetListBoxSetSelected(m_arg268, -1);
	}
	else if (autoCount > 0)
	{
		GadgetListBoxSetSelected(m_arg264, -1);
		GadgetListBoxSetSelected(m_arg268, 0);
	}
	else
	{
		GadgetListBoxSetSelected(m_arg264, -1);
		GadgetListBoxSetSelected(m_arg268, -1);
	}
}
