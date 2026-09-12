// ?populateSaveGameListbox@GameState@@QAEXPAVGameWindow@@W4SaveLoadLayoutType@@@Z
// partial score=0.99456 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME dual save-game list builder, RVA001121A0, retail1286B.
// Partial reconstruction: exact size and seven non-relocation bytes differ.
// The counted wide loop decrements its count before advancing both pointers;
// retail advances both pointers first. Count-last source currently perturbs
// inlining/register allocation to1299B. No instruction patching is used.
// Caller0056FD30+3D reaches ILT000267F1 with four arguments and TheGameState;
// retail ret16 independently rejects the ledger's old two-argument ABI.
// Column0 is the map label, column1 the save description; do not swap them.
// Map metadata getter remains bound to existing ILT00042807 (body00450FC0),
// without inventing a new semantic callee pin.

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
		return m_data ? m_data->text : "";
	}
};

__declspec(dllimport) unsigned int __cdecl bfmeLenVGI(const unsigned short *);

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


static __forceinline int compareChars(const unsigned short *p,const unsigned short *other,int count) {while(count > 0) { if(*p == *other) {--count;++p;++other;} else return *p-*other; } return 0;}
    __forceinline int compare(const unsigned short *other) const
    {
        int otherLen = bfmeLenVGI(other);
        int myLen = m_data ? m_data->length : 0;
        const unsigned short *p = m_data ? m_data->text : (const unsigned short *)L"";
        int count = myLen < otherLen ? myLen : otherLen;
        int result = compareChars(p,other,count);
        return result ? result : myLen - otherLen;
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
    friend class BfmeGameStateSaveList;
private:
    void clearAvailableGames();
    void iterateSaveFiles(IterateSaveFileCallback callback, void *userData);
};

extern void addGameToAvailableList(AsciiString filename, void *userData);

class BfmeGameStateSaveList
{
public:
	void populateSaveGameListbox(GameWindow *normal, GameWindow *autosave, Bool newSave, int filter);

private:
	char m_pad[0x50];
	AvailableGameInfo *m_availableGames;
};


extern void j_00042807();
class MapMetaData {
public:
    UnicodeString displayName() const {
        typedef UnicodeString (MapMetaData::*Getter)() const;
        union { void (*entry)(); Getter method; } call;
        call.entry=j_00042807;
        return (this->*call.method)();
    }
};
class MapCache { public: const MapMetaData *findMap(AsciiString); };
extern MapCache *TheMapCache;

void BfmeGameStateSaveList::populateSaveGameListbox(GameWindow *normal, GameWindow *autosave, Bool newSave, int filter)
{
    if (!normal) return;
    GadgetListBoxReset(normal);
    if (autosave) GadgetListBoxReset(autosave);
    int widths[4] = {30,40,15,15};
    if (GadgetListBoxGetNumColumns(normal) < 4) GadgetListBoxSetColumnWidths(normal,4,widths);
    if (autosave && GadgetListBoxGetNumColumns(autosave) < 4) GadgetListBoxSetColumnWidths(autosave,4,widths);
    unsigned normalCount=0, autoCount=0;
    if (newSave) {
        UnicodeString newText=((GameTextCharView *)TheGameText)->fetch("GUI:NewSaveGame");
        int index=GadgetListBoxAddEntryText(normal,newText,GameMakeColor(200,200,200,255),-1,-1);
        GadgetListBoxSetItemData(normal,0,index);
        ++normalCount;
    }
    reinterpret_cast<GameState *>(this)->clearAvailableGames();
    reinterpret_cast<GameState *>(this)->iterateSaveFiles(addGameToAvailableList,&m_availableGames);
    for (AvailableGameInfo *info=m_availableGames; info; info=info->next) {
        SaveGameInfo *save=&info->saveGameInfo;
        if (filter==1) { if (save->saveFileType!=0 && save->saveFileType!=1) continue; }
        else if (filter==2) { if (save->saveFileType!=2) continue; }
        int result=save->description.compare((const unsigned short *)L"__AUTO#SAVE__"); GameWindow *list; if(result==0)list=autosave;else list=normal;
        if (!list) continue;
        _SYSTEMTIME systemTime;
        systemTime.wYear=save->date.year;
        systemTime.wMonth=save->date.month;
        systemTime.wDayOfWeek=save->date.dayOfWeek;
        systemTime.wDay=save->date.day;
        systemTime.wHour=save->date.hour;
        systemTime.wMinute=save->date.minute;
        systemTime.wSecond=save->date.second;
        systemTime.wMilliseconds=save->date.milliseconds;
        UnicodeString displayDate=getUnicodeDateBuffer(systemTime);
        UnicodeString displayTime=getUnicodeTimeBuffer(systemTime);
        UnicodeString label=save->description;
        if (list==autosave) label=((GameTextCharView *)TheGameText)->fetch("GUI:AutoSaveName");
        UnicodeString mapLabel((const unsigned short *)L"");
        if (TheMapCache) {
            const MapMetaData *map=TheMapCache->findMap(save->mapLabel);
            if (map) mapLabel=map->displayName();
        }
        if (mapLabel.isEmpty()) {
            Bool exists=false;
            mapLabel=((GameTextAsciiView *)TheGameText)->fetch(save->mapLabel,&exists);
            if (!exists) mapLabel.format((const unsigned short *)L"%S",save->mapLabel.str());
        }
        int color=save->saveFileType==1 ? 0xffefcc52 : 0xffffffff;
        int index=GadgetListBoxAddEntryText(list,mapLabel,color,-1,0);
        GadgetListBoxAddEntryText(list,label,color,index,1);
        GadgetListBoxAddEntryText(list,displayTime,color,index,2);
        GadgetListBoxAddEntryText(list,displayDate,color,index,3);
        GadgetListBoxSetItemData(list,info,index);
        if (list==autosave) ++autoCount; else ++normalCount;
    }
    if (normalCount>0) { GadgetListBoxSetSelected(normal,0); GadgetListBoxSetSelected(autosave,-1); }
    else if (autoCount>0) { GadgetListBoxSetSelected(normal,-1); GadgetListBoxSetSelected(autosave,0); }
    else { GadgetListBoxSetSelected(normal,-1); GadgetListBoxSetSelected(autosave,-1); }
}
