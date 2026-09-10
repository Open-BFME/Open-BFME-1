// ?gogoGadgetTextEntry@GameWindowManager@@UAEPAVGameWindow@@PAURva0047FCF0FactoryInput@@PAURva0047FCF0EntryData@@PAVGameFont@@_N@Z
// partial score=0.88 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0047FCF0 is the BFME text-entry factory.  The BFME gadget path
// passes a creation record, not a GameWindow, and the record's instance-data
// pointer is at +0x30.  This TU keeps that ABI and the 0x28-byte EntryData
// layout local to the reconstructed factory.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef short Short;
typedef bool Bool;

extern "C" void *memcpy(void *, const void *, unsigned int);
extern "C" void *memset(void *, int, unsigned int);

class GameWindow;
class GameFont;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase();
	StringBase(const StringBase<T> &that);
	void releaseBuffer();

protected:
	void *data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &that) : StringBase<unsigned short>(that) {}
	~UnicodeString() { releaseBuffer(); }

	Int getLength() const
	{
		return data ? *(UnsignedShort *)((char *)data + 4) : 0;
	}
};

class WinInstanceData
{
public:
	char padBeforeStyle[0xc];
	UnsignedInt style;
	char padBeforeTextLabel[0x178];
	AsciiString textLabel;
	char padAfterTextLabel[0x1c];

	WinInstanceData();
	void init();
	~WinInstanceData();
};

class DisplayString
{
public:
	virtual void v00();
	virtual void setText(UnicodeString);
	virtual UnicodeString getText();
	virtual Int getTextLength();
};

class DisplayStringManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual DisplayString *newDisplayString();
};

// The copy is observed as 40 bytes at 0x0047FCF0.  The two bytes at +0x1c
// and +0x20 are the character positions, and constructList is at +0x18.
// The intervening bytes are retained explicitly rather than borrowing the
// upstream header's smaller EntryData layout.
struct Rva0047FCF0EntryData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	unsigned char optionBytes[4];
	Short maxTextLen;
	unsigned char internalBytes[6];
	GameWindow *constructList;
	UnsignedShort charPos;
	UnsignedShort unusedCharPos;
	UnsignedShort conCharPos;
	unsigned char tail[6];
};

typedef char Rva0047FCF0EntryDataSizeCheck[
	(sizeof(Rva0047FCF0EntryData) == 0x28) ? 1 : -1];

// The record is the object consumed by the BFME creation factories.  The
// twelve-byte coordinate prefix is followed by a retail-proven 0x18-byte
// gap before instanceData at +0x30.
struct Rva0047FCF0FactoryInput
{
	GameWindow *owner;
	UnsignedInt status;
	Int x;
	Int y;
	Int width;
	Int height;
	char padBeforeInstanceData[0x18];
	WinInstanceData *instanceData;
};

struct Rva0047FCF0ListboxData
{
	Short listLength;
	Short columns;
	Int *columnWidthPercentage;
	Bool autoScroll;
	Bool autoPurge;
	Bool scrollBar;
	Bool multiSelect;
	Bool forceSelect;
	Bool scrollIfAtEnd;
	Bool audioFeedback;
	Int *columnWidth;
	void *listData;
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
	Int totalHeight;
	Short endPos;
	Short insertPos;
	Int selectPos;
	Int *selections;
	Short displayHeight;
	UnsignedInt doubleClickTime;
	Short displayPos;
	char bfmeTail[0x0c];
};

typedef char Rva0047FCF0ListboxDataSizeCheck[
	(sizeof(Rva0047FCF0ListboxData) == 0x4c) ? 1 : -1];

class GameWindow
{
public:
	GameWindow *owner;
	char pad[0x2c];
	WinInstanceData *instanceData;

	Int winSetOwner(GameWindow *owner);
	void winSetUserData(void *data);
};

class GameWindowManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual GameWindow *gogoGadgetListBox(Rva0047FCF0FactoryInput *,
		Rva0047FCF0ListboxData *, GameFont *, Bool);
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void assignDefaultGadgetLook(GameWindow *, GameFont *, Bool);
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual GameWindow *create(Rva0047FCF0FactoryInput *);
	virtual void winDestroy(GameWindow *);
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual UnicodeString winTextLabelToText(AsciiString);
	virtual GameWindow *gogoGadgetTextEntry(Rva0047FCF0FactoryInput *,
		Rva0047FCF0EntryData *, GameFont *, Bool);
};

extern DisplayStringManager *TheDisplayStringManager;
extern Int OurLanguage;
extern void GadgetTextEntrySetText(GameWindow *, UnicodeString);

enum
{
	LANGUAGE_ID_JAPANESE = 6,
	LANGUAGE_ID_KOREAN = 8,
	ENTRY_TEXT_LEN = 0x100,
	GWS_ENTRY_FIELD = 0x40,
	GWS_SCROLL_LISTBOX = 0x20,
	GWS_MOUSE_TRACK = 0x400
};

// Preserve the retail incremental-link call sites for the already identified
// helpers.  These are declarations of existing symbols, not new callbacks.
#pragma comment(linker, "/alternatename:?winSetOwner@GameWindow@@QAEHPAV1@@Z=?j_00047230@@YAXXZ")
#pragma comment(linker, "/alternatename:?winSetUserData@GameWindow@@QAEXPAX@Z=?j_00002e69@@YAXXZ")
#pragma comment(linker, "/alternatename:?GadgetTextEntrySetText@@YAXPAVGameWindow@@VUnicodeString@@@Z=?j_0000c874@@YAXXZ")
#pragma comment(linker, "/alternatename:??0WinInstanceData@@QAE@XZ=?j_0001d845@@YAXXZ")
#pragma comment(linker, "/alternatename:?init@WinInstanceData@@QAEXXZ=?j_00021431@@YAXXZ")
#pragma comment(linker, "/alternatename:??1WinInstanceData@@QAE@XZ=?j_00021431@@YAXXZ")

GameWindow *GameWindowManager::gogoGadgetTextEntry(
	Rva0047FCF0FactoryInput *input, Rva0047FCF0EntryData *entryData,
	GameFont *defaultFont, Bool defaultVisual)
{
	Rva0047FCF0EntryData *data;
	GameWindow *entry;

	if ((input->instanceData->style & GWS_ENTRY_FIELD) == 0)
		return 0;

	entry = create(input);
	if (entry == 0)
		return 0;

	entry->winSetOwner(input->owner);

	if (entryData->text)
		entryData->charPos = entryData->text->getTextLength();
	else
		entryData->charPos = 0;
	entryData->conCharPos = 0;
	entryData->internalBytes[3] = 0;
	if (entryData->maxTextLen >= ENTRY_TEXT_LEN)
		entryData->maxTextLen = ENTRY_TEXT_LEN;

	data = new Rva0047FCF0EntryData;
	memcpy(data, entryData, sizeof(Rva0047FCF0EntryData));
	data->text = TheDisplayStringManager->newDisplayString();
	data->sText = TheDisplayStringManager->newDisplayString();
	data->constructText = TheDisplayStringManager->newDisplayString();

	if (entryData->text)
		data->text->setText(entryData->text->getText());
	if (entryData->sText)
		data->sText->setText(entryData->sText->getText());

	entry->winSetUserData(data);
	data->constructList = 0;

	if (OurLanguage == LANGUAGE_ID_KOREAN ||
		OurLanguage == LANGUAGE_ID_JAPANESE)
	{
		WinInstanceData boxInstData;
		Rva0047FCF0ListboxData listData;
		Rva0047FCF0FactoryInput listInput;

		boxInstData.init();
		memset(&listData, 0, sizeof(Rva0047FCF0ListboxData));
		listData.listLength = 128;
		listData.autoScroll = 0;
		listData.columns = 1;
		listData.autoPurge = 1;
		listData.scrollBar = 1;
		listData.scrollIfAtEnd = 0;
		listData.multiSelect = 0;
		listData.listData = 0;
		boxInstData.style = GWS_SCROLL_LISTBOX | GWS_MOUSE_TRACK;

		data->constructList = gogoGadgetListBox(
			&listInput, &listData, 0, 1);
		if (data->constructList == 0)
		{
			winDestroy(entry);
			return 0;
		}
	}

	assignDefaultGadgetLook(entry, defaultFont, defaultVisual);
	UnicodeString text = winTextLabelToText(input->instanceData->textLabel);
	if (text.getLength())
		GadgetTextEntrySetText(entry, text);
	return entry;
}
