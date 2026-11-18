// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// BFME text-entry factory; decoded creation-record ABI and native string cleanup.

#include "../../../Include/Common/ScalarTypes.h"





extern "C" void *memcpy(void *, const void *, unsigned int);
extern "C" void *memset(void *, int, unsigned int);

class GameWindow;
class GameFont;

#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Language.h"

inline UnicodeString::UnicodeString(const UnicodeString &that)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that);
}

inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

class Rva0047FCF0TempString : public UnicodeString
{
public:
    // ??0Rva0047FCF0TempString@@QAE@ABV0@@Z absent-from-retail
    Rva0047FCF0TempString(const Rva0047FCF0TempString &that) : UnicodeString(that) {}
};

class WinInstanceData
{
public:
	char padBeforeStyle[8];
	UnsignedInt style;
	char padBeforeTextLabel[0x178];
	AsciiString textLabel;
	char padAfterTextLabel[0x1c];

	// ?getStyle@WinInstanceData@@QAEIXZ absent-from-retail
	UnsignedInt getStyle() { return style; }

	WinInstanceData();
	void init();
	virtual ~WinInstanceData();
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

struct Rva0047FCF0FactoryInput
{
	GameWindow *owner;
	UnsignedInt status;
	Int x;
	Int y;
	Int width;
	Int height;
	UnsignedInt padBeforeInstanceData[6];
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
	Int winSetOwner(GameWindow *owner);
	void winSetUserData(void *data);
};

class Rva0047FCF0GameWindowManager
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
	virtual GameWindow *gogoGadgetTextEntry(Rva0047FCF0FactoryInput *,
		Rva0047FCF0EntryData *, GameFont *, Bool);
	virtual void v24();
	virtual void assignDefaultGadgetLook(GameWindow *, GameFont *, Bool);
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual GameWindow *create(Rva0047FCF0FactoryInput *);
	virtual Int winDestroy(GameWindow *);
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
	virtual void v71();
};

extern DisplayStringManager *TheDisplayStringManager;
extern void GadgetTextEntrySetText(GameWindow *, UnicodeString);

enum
{
	ENTRY_TEXT_LEN = 0x100,
	GWS_ENTRY_FIELD = 0x40,
	GWS_SCROLL_LISTBOX = 0x20,
	GWS_MOUSE_TRACK = 0x400
};

//-------------------------------------------------------------------------------------------------
/** Does all generic window creation, calls appropriate entry field create
	* function to set up specific data */
//-------------------------------------------------------------------------------------------------
// ?gogoGadgetTextEntry@Rva0047FCF0GameWindowManager@@UAEPAVGameWindow@@PAURva0047FCF0FactoryInput@@PAURva0047FCF0EntryData@@PAVGameFont@@_N@Z
GameWindow *Rva0047FCF0GameWindowManager::gogoGadgetTextEntry(
	Rva0047FCF0FactoryInput *input, Rva0047FCF0EntryData *entryData,
	GameFont *defaultFont, Bool defaultVisual)
{
	Rva0047FCF0EntryData *data;
	GameWindow *entry;
	if ((input->instanceData->getStyle() & GWS_ENTRY_FIELD) == 0)
	{
		return 0;
	}  // end if

	// create the window
	entry = create(input);
	if (entry == 0)
	{
		return 0;
	}  // end if

	// set owner of this control
	entry->winSetOwner(input->owner);

	// zero entry data
//	memset( entryData->text, 0, ENTRY_TEXT_LEN );
//	memset( entryData->constructText, 0, ENTRY_TEXT_LEN );

	// initialize character positions, legths etc
	if (entryData->text)
		entryData->charPos = entryData->text->getTextLength();
	else
		entryData->charPos = 0;
	entryData->conCharPos = 0;
	entryData->internalBytes[3] = 0;
	if (entryData->maxTextLen >= ENTRY_TEXT_LEN)
		entryData->maxTextLen = ENTRY_TEXT_LEN;

	// allocate entry data
	data = new Rva0047FCF0EntryData;

	// copy over data control
	memcpy(data, entryData, sizeof(Rva0047FCF0EntryData));

	// allocate new text display string
	data->text = TheDisplayStringManager->newDisplayString();
	data->sText = TheDisplayStringManager->newDisplayString();
	data->constructText = TheDisplayStringManager->newDisplayString();

	// set the max for the text lengths
//	data->text->allocateFixed( ENTRY_TEXT_LEN );
//	data->sText->allocateFixed( ENTRY_TEXT_LEN );

	// do any real display string copies
	if (entryData->text)
		data->text->setText(entryData->text->getText());
	if (entryData->sText)
		data->sText->setText(entryData->sText->getText());

	// set data into window
	entry->winSetUserData(data);

	// asian languages get to have list box kanji character completion
	data->constructList = 0;

	if (OurLanguage == LANGUAGE_ID_KOREAN ||
		OurLanguage == LANGUAGE_ID_JAPANESE)
	{
		// we need to create the construct listbox
		WinInstanceData boxInstData;
		Rva0047FCF0ListboxData listData;
		Rva0047FCF0FactoryInput listInput;

			// intialize instData
		boxInstData.init();

		// define display region
		memset(&listData, 0, sizeof(Rva0047FCF0ListboxData));
		listData.listLength = 128;
		listData.autoScroll = 0;
		listData.scrollIfAtEnd = 0;
		listData.autoPurge = 1;
		listData.scrollBar = 1;
		listData.multiSelect = 0;
		listData.columns = 1;
		listData.listData = 0;
		boxInstData.style = GWS_SCROLL_LISTBOX | GWS_MOUSE_TRACK;
		listInput.owner = 0;
		listInput.x = 0;
		listInput.y = input->height;
		listInput.padBeforeInstanceData[0] = 0;
		listInput.padBeforeInstanceData[1] = 0;
		listInput.padBeforeInstanceData[2] = 0;
		listInput.padBeforeInstanceData[3] = 0;
		listInput.padBeforeInstanceData[4] = 0;
		listInput.padBeforeInstanceData[5] = 0;
		listInput.status = 0x4430;
		listInput.width = 0x6e;
		listInput.height = 0x77;
		listInput.instanceData = &boxInstData;

		data->constructList = gogoGadgetListBox(
			&listInput, &listData, 0, 1);
		if (data->constructList == 0)
		{
			winDestroy(entry);
			return 0;
		}  // end if
	}  // end, korean or japanese

	// assign the default images/colors
	assignDefaultGadgetLook(entry, defaultFont, defaultVisual);

	// assign text from label
	UnicodeString text = winTextLabelToText(input->instanceData->textLabel);
	if (text.getLength())
		GadgetTextEntrySetText(entry, text);
	return entry;
}  // end gogoGadgetTextEntry
