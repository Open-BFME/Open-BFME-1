// ?addEntry@@YAHPAVUnicodeString@@HHHPAVGameWindow@@_N@Z
// partial score=0.68 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// BFME addEntry body at 0x004B86B0.  The retail ListboxData layout is four
// bytes longer than the vendored ZH layout before columnWidth/listData.

typedef int Int;
typedef short Short;
typedef bool Bool;
typedef unsigned int UnsignedInt;

extern "C" void *memset(void *destination, int value, unsigned int count);

class GameFont;

template <typename Char>
class StringBase
{
	friend class UnicodeString;

private:
	StringBase(const StringBase<Char> &source);
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &source)
		: StringBase<unsigned short>(source)
	{
	}

	~UnicodeString()
	{
	}
};

class DisplayString
{
public:
	virtual void displayStringSlot0();
	virtual void setText(UnicodeString text);
	virtual void getText();
	virtual void getTextLength();
	virtual void notifyTextChanged();
	virtual void reset();
	virtual void setFont(GameFont *font);
	virtual GameFont *getFont();
	virtual void setWordWrap(Int width);
	virtual void setWordWrapCentered(Bool centered);
	virtual void draw(Int x, Int y, Int color, Int dropColor);
	virtual void drawWithDrop(Int x, Int y, Int color, Int dropColor,
		Int xDrop, Int yDrop);
	virtual void displayStringSlot12();
	virtual void displayStringSlot13();
	virtual void displayStringSlot14();
	virtual void getSize(Int *width, Int *height);
};

class DisplayStringManager
{
public:
	virtual void managerSlot0();
	virtual void managerSlot1();
	virtual void managerSlot2();
	virtual void managerSlot3();
	virtual void managerSlot4();
	virtual void managerSlot5();
	virtual void managerSlot6();
	virtual void managerSlot7();
	virtual void managerSlot8();
	virtual DisplayString *newDisplayString();
};

extern DisplayStringManager *TheDisplayStringManager;

class GameWindow
{
public:
	void *winGetUserData();
	UnsignedInt winGetStatus();
	GameFont *winGetFont();
};

struct _ListEntryCell
{
	Int cellType;
	Int color;
	void *data;
	void *userData;
	Int width;
	Int height;
};

struct _ListEntryRow
{
	Int listHeight;
	Int height;
	_ListEntryCell *cell;
};

typedef _ListEntryCell ListEntryCell;
typedef _ListEntryRow ListEntryRow;

struct _ListboxData
{
	Short listLength;
	Short columns;
	unsigned char m_unreconstructed_04[0x10];
	Int *columnWidth;
	ListEntryRow *listData;
	unsigned char m_unreconstructed_1c[0x0c];
	Int totalHeight;
	Short endPos;
	Short insertPos;
	unsigned char m_unreconstructed_30[4];
	Int selectPos;
	Int *selections;
};

typedef _ListboxData ListboxData;

enum
{
	LISTBOX_TEXT = 1,
	TEXT_WIDTH_OFFSET = 7,
	WIN_STATUS_ONE_LINE = 0x00004000
};

extern Int moveRowsDown(ListboxData *list, Int startingRow);
extern void adjustDisplay(GameWindow *window, Int adjustment, Bool updateSlider);
extern void computeTotalHeight(GameWindow *window);

// ?addEntry@@YAHPAVUnicodeString@@HHHPAVGameWindow@@_N@Z
Int addEntry(UnicodeString *string, Int color, Int row, Int column,
	GameWindow *window, Bool overwrite)
{
	ListboxData *list = (ListboxData *)window->winGetUserData();
	Int width;
	DisplayString *displayString;

	if (column >= list->columns || row >= list->listLength)
		return -1;

	if (row == -1)
	{
		row = list->insertPos;
		list->insertPos++;
		list->endPos++;
	}
	if (column == -1)
		column = 0;

	width = list->columnWidth[column] - TEXT_WIDTH_OFFSET;

	Int rowsAdded = 0;
	ListEntryRow *listRow = &list->listData[row];
	if (!listRow->cell)
	{
		listRow->cell = new ListEntryCell[list->columns];
		memset(listRow->cell, 0, list->columns * sizeof(ListEntryCell));
		rowsAdded = 1;
	}
	else if (!overwrite)
	{
		moveRowsDown(list, row);
		listRow->cell = new ListEntryCell[list->columns];
		memset(listRow->cell, 0, list->columns * sizeof(ListEntryCell));
		rowsAdded = 1;
	}

	listRow->cell[column].cellType = LISTBOX_TEXT;
	listRow->cell[column].color = color;

	if (!listRow->cell[column].data)
		listRow->cell[column].data = (void *)TheDisplayStringManager->newDisplayString();
	displayString = (DisplayString *)listRow->cell[column].data;
	if ((window->winGetStatus() & WIN_STATUS_ONE_LINE) == 0)
		displayString->setWordWrap(width);
	displayString->setText(*string);
	displayString->setFont(window->winGetFont());

	if (overwrite)
	{
		Int oldRowHeight = listRow->height;
		Int oldTotalHeight = listRow->listHeight;
		Int rowHeight;
		Int totalHeight;

		if (!oldTotalHeight && row)
			oldTotalHeight = list->listData[row - 1].listHeight;

		displayString->getSize(0, &rowHeight);
		if (rowHeight > oldRowHeight)
		{
			totalHeight = oldTotalHeight + (rowHeight - oldRowHeight);
			listRow->height = rowHeight;
			listRow->listHeight = totalHeight + rowsAdded;
			list->totalHeight += (rowHeight - oldRowHeight) + rowsAdded;
			adjustDisplay(window, 0, true);
		}
	}
	else
	{
		computeTotalHeight(window);
	}

	return row;
}
