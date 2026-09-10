// ?populateSaveGameListbox@Rva00111DB0SaveList@@QAEXPAVGameWindow@@W4SaveLoadLayoutType@@@Z
// partial score=0.98 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Scratch reconstruction of the BFME save-list population body at RVA
// 0x00111DB0.  The address-derived owner is deliberate: PopupSaveLoad.cpp
// names the two callers and their ILT, but the existing GameState row at
// 0x001121A0 has a different ret 0x10 body, so this probe does not assert that
// unresolved class ownership.

typedef bool Bool;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;

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
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

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
	UnicodeString(const UnsignedShort *text)
		: StringBase<UnsignedShort>(text) {}
	~UnicodeString() {}

	Bool isEmpty() const
	{
		return m_data == 0 || m_data->length == 0;
	}

	void set(const UnicodeString &other)
	{
		StringBase<UnsignedShort>::set(other);
	}

	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}

	void format(UnicodeString format, ...);
};

class GameWindow;

Int GadgetListBoxGetNumColumns(GameWindow *listbox);
void GadgetListBoxSetColumnWidths(GameWindow *listbox, Int count,
	Int *widths);
void GadgetListBoxReset(GameWindow *listbox);
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Int color, Int row, Int column, Bool overwrite = true);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data,
	Int row, Int column = 0);
void GadgetListBoxSetSelected(GameWindow *listbox, Int selectIndex);

inline Int GameMakeColor(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha)
{
	return ((UnsignedInt)alpha << 24) | ((UnsignedInt)red << 16) |
		((UnsignedInt)green << 8) | blue;
}

class GameTextInterface
{
};

// The two overloads occupy adjacent but reversed slots in the BFME vtable as
// observed at this call site: the AsciiString overload is +0x24 and the
// const-char overload is +0x28.  Separate views keep those ABI facts explicit.
class GameTextAsciiView
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
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};

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

extern GameTextInterface *TheGameText;

struct SYSTEMTIME
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

UnicodeString getUnicodeDateBuffer(SYSTEMTIME timeVal);
UnicodeString getUnicodeTimeBuffer(SYSTEMTIME timeVal);

enum SaveLoadLayoutType
{
	SLLT_INVALID = 0,
	SLLT_SAVE_AND_LOAD,
	SLLT_LOAD_ONLY,
	SLLT_SAVE_ONLY,
	SLLT_NUM_TYPES
};

enum SaveFileType
{
	SAVE_FILE_TYPE_NORMAL,
	SAVE_FILE_TYPE_MISSION
};

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
	AsciiString saveGameMapName;
	AsciiString pristineMapName;
	AsciiString mapLabel;
	SaveDate date;
	AsciiString campaignSide;
	Int missionNumber;
	UnicodeString description;
	SaveFileType saveFileType;
	AsciiString missionMapName;
};

struct AvailableGameInfo
{
	AsciiString filename;
	SaveGameInfo saveGameInfo;
	AvailableGameInfo *next;
	AvailableGameInfo *prev;
};

typedef void (*IterateSaveFileCallback)(AsciiString filename, void *userData);

class GameState
{
public:
	void clearAvailableGames();
	void iterateSaveFiles(IterateSaveFileCallback callback, void *userData);
};

extern void addGameToAvailableList(AsciiString filename, void *userData);

class Rva00111DB0SaveList
{
public:
	void populateSaveGameListbox(GameWindow *listbox,
		SaveLoadLayoutType layoutType);

private:
	char m_pad[0x50];
	AvailableGameInfo *m_availableGames;
};

void Rva00111DB0SaveList::populateSaveGameListbox(
	GameWindow *listbox, SaveLoadLayoutType layoutType)
{
	Int index;

	if (listbox == 0)
		return;

	GadgetListBoxReset(listbox);
	if (GadgetListBoxGetNumColumns(listbox) < 3)
	{
		Int columnWidths[3] = { 60, 20, 20 };
		GadgetListBoxSetColumnWidths(listbox, 3, columnWidths);
	}

	if (layoutType != SLLT_LOAD_ONLY)
	{
		UnicodeString newGameText =
			((GameTextCharView *)TheGameText)->fetch("GUI:NewSaveGame");
		Int newGameColor = GameMakeColor(200, 200, 255, 255);

		index = GadgetListBoxAddEntryText(listbox, newGameText,
			newGameColor, -1, -1);
		GadgetListBoxSetItemData(listbox, 0, index);
	}

	reinterpret_cast<GameState *>(this)->clearAvailableGames();
	reinterpret_cast<GameState *>(this)->iterateSaveFiles(
		addGameToAvailableList, &m_availableGames);

	AvailableGameInfo *info;
	SaveGameInfo *saveGameInfo;
	SYSTEMTIME systemTime;
	UnsignedInt count = 0;
	for (info = m_availableGames; info; info = info->next, count++)
	{
		saveGameInfo = &info->saveGameInfo;
		systemTime.wYear = saveGameInfo->date.year;
		systemTime.wMonth = saveGameInfo->date.month;
		systemTime.wDayOfWeek = saveGameInfo->date.dayOfWeek;
		systemTime.wDay = saveGameInfo->date.day;
		systemTime.wHour = saveGameInfo->date.hour;
		systemTime.wMinute = saveGameInfo->date.minute;
		systemTime.wSecond = saveGameInfo->date.second;
		systemTime.wMilliseconds = saveGameInfo->date.milliseconds;

		UnicodeString displayDateBuffer = getUnicodeDateBuffer(systemTime);
		UnicodeString displayTimeBuffer = getUnicodeTimeBuffer(systemTime);

		UnicodeString displayLabel = saveGameInfo->description;
		if (displayLabel.isEmpty())
		{
			Bool exists = false;
			displayLabel = ((GameTextAsciiView *)TheGameText)->fetch(
				saveGameInfo->mapLabel,
				&exists);
			if (exists == false)
				displayLabel.format(L"%S", saveGameInfo->mapLabel.str());
		}

		Int color;
		if (saveGameInfo->saveFileType == SAVE_FILE_TYPE_MISSION)
			color = GameMakeColor(200, 255, 200, 255);
	else
		{
			color = ((((unsigned char)~count) & 1) | -2) << 14;
		}

		index = GadgetListBoxAddEntryText(listbox, displayLabel,
			color, -1, 0);
		GadgetListBoxAddEntryText(listbox, displayTimeBuffer,
			color, index, 1);
		GadgetListBoxAddEntryText(listbox, displayDateBuffer,
			color, index, 2);
		GadgetListBoxSetItemData(listbox, info, index);
	}

	GadgetListBoxSetSelected(listbox, 0);
}
