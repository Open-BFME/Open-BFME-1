// ?prepareFinish@Rva56E070StateOwner@@QAEXXZ
// partial score=0.35 date=2026-09-18
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
//
// BFME anonymous body 0x0056F1F0, 2286 bytes.  The finishCurrent caller and
// the 0x00006B3B ILT prove the prepareFinish identity.  The constructor at
// 0x0056A2F0 proves the list<AvailableGameInfo> header at this+0x284.
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE

#include <list>
#include <new>
#include <set>

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

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
		const char *end = text;
		while (*end != 0)
			++end;
		set(text, (Int)(end - text));
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
		((StringBase<char> *)this)->concat(
			*(const StringBase<char> *)&other);
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
		const char *end = text;
		while (*end != 0)
			++end;
		set(text, (Int)(end - text));
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
void bfmeCall926A(void *listbox, void *data, void *row, Int column);

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
	__forceinline AvailableGameInfo()
		: filename(), saveGameInfo(), next(0), prev(0)
	{
		saveGameInfo.saveFileType = 3;
	}
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
	Int m_networkCRCInterval;
	Int m_originalGameMode;
	Int m_numPlayers;
	Int m_seedOrDesync;
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
#pragma comment(linker, "/alternatename:?readReplayHeader@RecorderClass@@QAE_NAAUReplayHeader@1@@Z=?readReplayHeader@Rva00099490RecorderClass@@QAE_NAAUReplayHeader@1@@Z")
#pragma comment(linker, "/alternatename:??1ReplayHeader@RecorderClass@@QAE@XZ=??1BfmeOwnVUL@@QAE@XZ")

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
};

class MapCache
{
public:
	void updateCache();
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

// The BFME map display helper is proven by the ILT pin at 0x00042807.  Its
// return type is the distinct AP string wrapper, not a guessed MapMetaData
// member name.
class UnicodeStringAP : public UnicodeString
{
public:
	UnicodeStringAP() : UnicodeString() {}
	UnicodeStringAP(const UnicodeStringAP &other)
		: UnicodeString(other) {}
	~UnicodeStringAP() {}
};

class BfmeEntryAP
{
public:
	UnicodeStringAP bfmeBaseNameAP();
};

class Version
{
public:
	UnsignedInt getVersionNumber();
};

class BfmeVersionAL
{
public:
	UnicodeStringAP bfmeVersionTextAL();
};

class GlobalDataView
{
public:
	char m_pad0[0xbc8];
	UnsignedInt m_iniCRC;
	char m_pad0bcc[4];
	UnsignedInt m_exeCRC;
};

extern BfmeVersionAL *TheBfmeVersion;
extern Version *TheVersionNumber;
extern GlobalDataView *TheWritableGlobalData;

extern int Rva0009B4B0(int left, int right);
extern Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options,
	Bool includeSlots) throw();

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
	if (TheMapCache == 0)
		return;

	GadgetListBoxReset(this->m_arg264);
	if (this->m_arg268 != 0)
		GadgetListBoxReset(this->m_arg268);

	this->m_availableGames.clear();

	Int widths[4] = { 30, 40, 15, 15 };
	if (GadgetListBoxGetNumColumns(this->m_arg264) < 4)
		GadgetListBoxSetColumnWidths(this->m_arg264, 4, widths);
	if (this->m_arg268 != 0 &&
		GadgetListBoxGetNumColumns(this->m_arg268) < 4)
		GadgetListBoxSetColumnWidths(this->m_arg268, 4, widths);

	RetailLayoutString asciistr;
	RetailLayoutString search;
	search.set((const char *)0x010892DC, 1);
	{
		AsciiString extension = RecorderClass::getReplayExtention();
		search.concat(extension.str(), extension.getLength());
	}

	FilenameList replayFilenames;
	register FilenameList::iterator it;
	TheFileSystem->getFileListInDirectory(RecorderClass::getReplayDir(), search,
		replayFilenames, TRUE);
	TheMapCache->updateCache();

	Int autoSaveIndex = 0;
	Int gameIndex = 0;
	if (this->m_mode270 == 3)
	{
		UnicodeString newReplayText =
			((GameTextCharView *)TheGameText)->fetch(
				(const char *)0x0110A818);
		Int row = GadgetListBoxAddEntryText(this->m_arg264, newReplayText,
			0xffc8c8c8, -1, -1, TRUE);
		bfmeCall926A(this->m_arg264, 0,
			(void *)(unsigned int)row, 0);
		gameIndex = 1;
	}

	for (it = replayFilenames.begin(); it != replayFilenames.end(); ++it)
	{
		asciistr.set((*it).reverseFind('\\') + 1);

		RecorderClass::ReplayHeader header;
		header.filename = asciistr;
		header.forPlayback = FALSE;

		RecorderClass recorder;
		if (TheMapCache == 0 ||
			!recorder.readReplayHeader(header))
			continue;

		ReplayGameInfo info;
		if (ParseAsciiStringToGameInfo(&info, header.gameOptions, TRUE))
		{

		register unsigned char isLastReplay = 0;
		AvailableGameInfo availableGameInfo;
		availableGameInfo.saveGameInfo.description = header.replayName;
		this->m_availableGames.push_back(availableGameInfo);

		UnicodeString replayNameToShow =
			availableGameInfo.saveGameInfo.description;
		AsciiString lastReplay = TheRecorder->getLastReplayFileName();
		AsciiString replayExtension = RecorderClass::getReplayExtention();
		lastReplay.concat(replayExtension.str(), replayExtension.getLength());
		if (((RetailLayoutString *)&lastReplay)->compareNoCase(asciistr) == 0)
		{
			isLastReplay = 1;
			replayNameToShow =
				((GameTextCharView *)TheGameText)->fetch(
					(const char *)0x01080448);
		}

		_SYSTEMTIME systemTime;
		systemTime.wYear = header.timeVal.wYear;
		systemTime.wMonth = header.timeVal.wMonth;
		systemTime.wDayOfWeek = header.timeVal.wDayOfWeek;
		systemTime.wDay = header.timeVal.wDay;
		systemTime.wHour = header.timeVal.wHour;
		systemTime.wMinute = header.timeVal.wMinute;
		systemTime.wSecond = header.timeVal.wSecond;
		systemTime.wMilliseconds = header.timeVal.wMilliseconds;
		UnicodeString displayTimeBuffer = getUnicodeTimeBuffer(systemTime);

		UnicodeString mapString;
		const MapMetaData *mapData = TheMapCache->findMap(info.getMap());
		if (mapData == 0)
		{
			mapString.translate(info.getMap());
		}
		else
		{
			UnicodeStringAP baseName =
				((BfmeEntryAP *)mapData)->bfmeBaseNameAP();
			mapString = *(const UnicodeString *)&baseName;
		}

		Bool versionMatches = false;
		UnicodeStringAP currentVersion = TheBfmeVersion->bfmeVersionTextAL();
		if (header.versionString.compare(
			*(const UnicodeString *)&currentVersion) == 0 &&
			header.versionNumber == TheVersionNumber->getVersionNumber())
		{
			UnsignedInt exeCRC = TheWritableGlobalData->m_exeCRC;
			versionMatches =
				header.exeCRC == (UnsignedInt)Rva0009B4B0(exeCRC, exeCRC) &&
				header.iniCRC == TheWritableGlobalData->m_iniCRC;
		}

		Int color = versionMatches ? -1 : (Int)0xff808080;
		GameWindow *listbox = isLastReplay ? this->m_arg268 : this->m_arg264;
		Int row = isLastReplay ? autoSaveIndex : gameIndex;
		Int index = GadgetListBoxAddEntryText(listbox, replayNameToShow,
			color, -1, 0, TRUE);
		GadgetListBoxAddEntryText(listbox, displayTimeBuffer,
			color, index, 1, TRUE);
		GadgetListBoxAddEntryText(listbox, header.versionString,
			color, index, 2, TRUE);
		GadgetListBoxAddEntryText(listbox, mapString,
			color, index, 3, TRUE);

		AvailableGameInfo *last = &this->m_availableGames.back();
		bfmeCall926A(listbox, (void *)last, (void *)(unsigned int)row, 0);
		if (isLastReplay)
			++autoSaveIndex;
		else
			++gameIndex;
		}
	}

	if (gameIndex != 0)
	{
		GadgetListBoxSetSelected(this->m_arg264, 0);
		GadgetListBoxSetSelected(this->m_arg268, -1);
	}
	else if (autoSaveIndex != 0)
	{
		GadgetListBoxSetSelected(this->m_arg264, -1);
		GadgetListBoxSetSelected(this->m_arg268, 0);
	}
	else
	{
		GadgetListBoxSetSelected(this->m_arg264, -1);
		GadgetListBoxSetSelected(this->m_arg268, -1);
	}
}
