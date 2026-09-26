// ?GadgetListBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.8945454545 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/displaystring /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
/* Banked native GadgetListBoxSystem, RVA004B9F10, full4400B.
 * Executable body4328B plus18x4 switch destinations; next INT3 at004BB040.
 * The original lifted claim is retained until this reconstruction is exact.
 * BFME behavior rebuilt from the aligned retail dispatcher and matched siblings:
 * no GGM_LEFT_DRAG arm; list messages4011..4021; pixel-scroll flag+10;
 * resize rewraps text cells when status4000 is clear, then recenters selection;
 * selection state+48 resets to-1; item-data operations validate column bounds;
 * array destruction clears deleted-row pointers; slider tracking delegates
 * clamping to the independently matched adjustDisplayByDelta helper.
 * Rva004B7DC0's existing native helper is visible to obtain its witnessed EAX
 * index/window+mode stack convention; SetTopVisibleEntry now calls it natively.
 * Existing helper row ownership is NOT changed by this evidence bank.
 * Retained full TU preserves private register conventions and real declarations.
 * Best probe:4400/4400,130relocs,464 masked positional differences(.894545),
 * no unresolved calls. This is NOT byte verified. Structural residue is resize
 * cell loop+03D3..0422, down-button operand allocation, two operand bytes+0FE2/+0FE6.
 * Nearly all positional differences come from the first loop's4B length drift.
 * Pointer/reference, local order/hoisting, array/address arithmetic, inline
 * cell accessors, guard/control-flow forms and G5/G6 compile the same residue;
 * G7 is worse. A new lever is needed. StringBase::set is used explicitly for
 * the invalid-text result; the ZH UnicodeString::set pin is a different body.
 * Other declarations/bodies in this bank are inherited context, not new claims.
 */
#define Matrix4x4 Matrix4  // BFME renamed it
// Adapted from Electronic Arts GPL-3.0 GeneralsMD GadgetListBox.cpp.
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "Common/AudioEventRTS.h"
#include "Common/Language.h"
#include "Common/Debug.h"
#include "Common/GameAudio.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/Keyboard.h"
#include "string_base.h"
inline UnicodeString::UnicodeString( const UnicodeString &stringSrc )
{
	((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(
		*(const StringBase<WideChar> *)&stringSrc );
}
void operator delete[]( void *block );
struct Rva004B8230ListboxData
{
	unsigned char m_prefix[2];
	short m_columns;
	int *m_columnWidthPercentage;
	unsigned char m_gap08[0x0c];
	int *m_columnWidth;
	unsigned char m_gap18[0x0c];
	GameWindow *m_slider;
};
struct Rva004B8230Coord
{
	int x;
	int y;
};
extern void GadgetListBoxSetColumnWidths(GameWindow *listbox, int count,
	int *widths);
void Rva004B8230UpdateColumnWidths(GameWindow *listbox)
{
	if (listbox == 0)
		return;
	Rva004B8230ListboxData *data =
		(Rva004B8230ListboxData *)listbox->winGetUserData();
	if (data == 0)
		return;
	int width;
	int height;
	listbox->winGetSize(&width, &height);
	if (data->m_columns == 1)
	{
		data->m_columnWidth = new int[1];
		data->m_columnWidth[0] = width;
		if (data->m_slider == 0)
			return;
		Rva004B8230Coord sliderSize;
		data->m_slider->winGetSize(&sliderSize.x, &sliderSize.y);
		data->m_columnWidth[0] += -2 - sliderSize.x;
		return;
	}
	if (data->m_columnWidthPercentage == 0)
	{
		GadgetListBoxSetColumnWidths(listbox, data->m_columns, 0);
		return;
	}
	if (data->m_columnWidth != 0)
	{
		delete [] data->m_columnWidth;
		data->m_columnWidth = 0;
	}
	data->m_columnWidth = new int[(int)data->m_columns];
	int totalWidth = width;
	if (data->m_slider != 0)
	{
		Rva004B8230Coord sliderSize;
		data->m_slider->winGetSize(&sliderSize.x, &sliderSize.y);
		totalWidth += -2 - sliderSize.x;
	}
	for (int i = 0; i < data->m_columns; ++i)
		data->m_columnWidth[i] =
			data->m_columnWidthPercentage[i] * totalWidth / 100;
}
#ifdef _INTERNAL
#endif
static UnsignedInt doubleClickTime = GetDoubleClickTime();
typedef struct _AddMessageStruct
{
	Int row;
	Int column;
	const void *data;
	Int type;
	Bool overwrite;
	Int width;
	Int height;
} AddMessageStruct;
typedef struct _TextAndColor
{
	UnicodeString string;
	Color color;
} TextAndColor;
static void doAudioFeedback(GameWindow *window)
{
	if (!window)
		return;
	ListboxData *lData = (ListboxData *)window->winGetUserData();
	if (!lData)
		return;
	if (lData->audioFeedback)
	{
		AudioEventRTS buttonClick("GUIComboBoxClick");
		if( TheAudio )
		{
			TheAudio->addAudioEvent( &buttonClick );
		}
	}
}
static Int getListboxEntryBasedOnCoord(GameWindow *window, Int x, Int y, Int &row, Int &column)
{
	Int pos;
	Int winx, winy, i;
	WinInstanceData *instData = window->winGetInstanceData();
	ListboxData *list = (ListboxData *)window->winGetUserData();
	window->winGetScreenPosition( &winx, &winy );
	if( instData->getTextLength() )
		winy += TheWindowManager->winFontHeight( instData->getFont() ) + 1;
	pos = -2;
	for( i=0; ; i++ )
	{
		if( i > 0 )
			if( (*(ListEntryRow **)((char *)list + 0x18))[ i - 1 ].listHeight >
					(*(Short *)((char *)list + 0x3C) + *(Short *)((char *)list + 0x44) ) )
			{
				pos = -1;
				break;
			}
		if( i == *(Short *)((char *)list + 0x2C) )
		{
			pos = -1;
			break;
		}
		if( (*(ListEntryRow **)((char *)list + 0x18))[i].listHeight > (y - winy + *(Short *)((char *)list + 0x44)) )
			break;
	}
	column = -1;
	if( pos == -2 )
	{
		pos = i;
		Int total = 0;
		for( i = 0; i < list->columns ;i++)
		{
			total += (*(Int **)((char *)list + 0x14))[i];
			if(x - winx < total)
			{
				column = i;
				break;
			}
		}
	}
	row = pos;
	return pos;
}
Int GadgetListBoxGetEntryBasedOnXY( GameWindow *listbox, Int x, Int y, Int &row, Int &column)
{
	return getListboxEntryBasedOnCoord( listbox, x, y, row, column  );
}
#pragma pack(push, 1)
struct BFMEListboxTopLayout
{
	unsigned char pad0[0x18];
	ListEntryRow *listData;
	unsigned char pad1[0x10];
	Short endPos;
	unsigned char pad2[0x16];
	Short displayPos;
};
#pragma pack(pop)
__declspec(noinline) static Int getListboxTopEntry( ListboxData *list )
{
	Int entry;
	const BFMEListboxTopLayout *retail = reinterpret_cast<const BFMEListboxTopLayout *>(list);
	for( entry=0; ; entry++ )
	{
		if( retail->listData[entry].listHeight > retail->displayPos )
			return entry;
		if( entry >= retail->endPos )
			return 0;
	}
	return 0;
}
static Int getListboxBottomEntry( ListboxData *list )
{
	Int entry;
	for( entry=list->endPos - 1; ; entry-- )
	{
		if( list->listData[entry].listHeight == list->displayPos + list->displayHeight )
			return entry;
		if( list->listData[entry].listHeight < list->displayPos + list->displayHeight && entry != list->endPos - 1)
			return entry + 1;
		if( list->listData[entry].listHeight < list->displayPos + list->displayHeight)
			return entry;
		if( entry < 0 )
			return 0;
	}
	return 0;
}
static void removeSelection( ListboxData *list, Int i )
{
	memcpy( &(*(Int **)((char *)list + 0x38))[i],
						&(*(Int **)((char *)list + 0x38))[(i+1)],
						((list->listLength - i) * sizeof(Int)) );
	(*(Int **)((char *)list + 0x38))[(list->listLength - 1)] = -1;
}
void adjustDisplay( GameWindow *window, Int adjustment, Bool updateSlider );
struct BFMEAdjustDisplayListboxData
{
	unsigned char m_prefix[0x11];
	Bool updateScrollButtons;
	unsigned char m_pad12[0x12];
	GameWindow *slider;
	Int totalHeight;
	unsigned char m_pad2c[0x10];
	Short displayHeight;
	unsigned char m_pad3e[6];
	Short displayPos;
};
class BfmeObjEBN;
char bfmeGoEBNb(BfmeObjEBN *object);
extern Real g_bfmeDefaultBU;
void Rva004B7A10SetScrollButtonsHidden(GameWindow *window, Bool hide);
__declspec(noinline) void __cdecl adjustDisplay( GameWindow *window, Bool updateSlider )
{
	BFMEAdjustDisplayListboxData *list =
		(BFMEAdjustDisplayListboxData *)window->winGetUserData();
	if( list->slider != NULL )
	{
		SliderData *sData;
		ICoord2D sliderSize, sliderChildSize;
		GameWindow *child;
		sData = (SliderData *)list->slider->winGetUserData();
		list->slider->winGetSize( &sliderSize.x, &sliderSize.y );
		sData->minVal = 0;
		sData->maxVal = list->totalHeight - list->displayHeight;
		if( sData->maxVal < 0 )
			sData->maxVal = 0;
		child = list->slider->winGetChild();
		child->winGetSize( &sliderChildSize.x, &sliderChildSize.y );
		if( bfmeGoEBNb( (BfmeObjEBN *)child ) )
		{
			Real scale = (Real)list->displayHeight / list->totalHeight;
			if( scale > g_bfmeDefaultBU )
				scale = g_bfmeDefaultBU;
			Int childHeight = (Int)((Real)sliderSize.y * scale);
			if( childHeight < 10 )
				childHeight = 10;
			child->winSetSize( sliderChildSize.x, childHeight );
		}
		sData->numTicks = (float)((sliderSize.y - sliderChildSize.y) / (float)sData->maxVal);
		if( updateSlider )
		{
			Int position = sData->maxVal - list->displayPos;
			if( position < 0 )
				position = 0;
			TheWindowManager->winSendSystemMsg( list->slider,
				0x400D,
				position,
				0 );
		}
		if( list->updateScrollButtons )
			Rva004B7A10SetScrollButtonsHidden( window,
				list->totalHeight <= list->displayHeight );
	}
}
static void adjustDisplayByDelta( GameWindow *window, Int adjustment,
																 Bool updateSlider )
{
	BFMEAdjustDisplayListboxData *list =
		(BFMEAdjustDisplayListboxData *)window->winGetUserData();
	list->displayPos += adjustment;
	if( list->displayPos > list->totalHeight - list->displayHeight + 1 )
		list->displayPos = list->totalHeight - list->displayHeight + 1;
	if( list->displayPos < 0 )
		list->displayPos = 0;
	adjustDisplay( window, updateSlider );
}
void forceAdjustDisplayByDelta( GameWindow *window, Int adjustment,
																 Bool updateSlider )
{
	adjustDisplayByDelta( window, adjustment, updateSlider );
}
static __declspec(noinline) void computeTotalHeight( GameWindow *window )
{
	Int i, height = 0;
	Int tempHeight;
	ListboxData *list = (ListboxData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	typedef void (DisplayString::*BFMEGetSizeFn)( Int *, Int * );
	for( i=0; i<*(Short *)((char *)list + 0x2C); i++ )
	{
		if(!(*(ListEntryRow **)((char *)list + 0x18))[i].cell)
			continue;
		tempHeight = 0;
		for (Int j = 0; j < list->columns; j++)
		{
			Int cellHeight = 0;
			if((*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].cellType == LISTBOX_TEXT)
			{
				if( BitTest( window->winGetStatus(), WIN_STATUS_ONE_LINE ) == TRUE )
				{
					cellHeight = TheWindowManager->winFontHeight( instData->getFont() );
				}
				else
				{
					DisplayString *displayString = (DisplayString *)(*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].data;
					if(displayString)
						(displayString->*(*(BFMEGetSizeFn *)&(*(void ***)displayString)[15]))( NULL, &cellHeight );
				}
			}
			else if((*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].cellType == LISTBOX_IMAGE)
			{
				if((*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].height > 0)
					cellHeight = (*(ListEntryRow **)((char *)list + 0x18))[i].cell[j].height + 1;
				else
					cellHeight = TheWindowManager->winFontHeight( instData->getFont() );
			}
			if(cellHeight > tempHeight)
				tempHeight = cellHeight;
		}
		*(Int *)((char *)(*(ListEntryRow **)((char *)list + 0x18) + i) + 4) = tempHeight;
		height += (*(Int *)((char *)(*(ListEntryRow **)((char *)list + 0x18) + i) + 4) + 1);
		(*(ListEntryRow **)((char *)list + 0x18))[i].listHeight = height;
	}
	*(Int *)((char *)list + 0x28) = height;
	adjustDisplay( window, TRUE );
}
struct BFMEAddImageEntryListboxData
{
	Short listLength;
	Short columns;
	UnsignedByte pad04[0x14];
	ListEntryRow *listData;
	UnsignedByte pad1c[0x10];
	Short endPos;
	Short insertPos;
};
class BFMEAddImageEntryDisplayStringManager
{
public:
	virtual void pad00() = 0;
	virtual void pad04() = 0;
	virtual void pad08() = 0;
	virtual void pad0c() = 0;
	virtual void pad10() = 0;
	virtual void pad14() = 0;
	virtual void pad18() = 0;
	virtual void pad1c() = 0;
	virtual void pad20() = 0;
	virtual void pad24() = 0;
	virtual void freeDisplayString(DisplayString *string) = 0;
};
static Int addImageEntry( const Image *image, Color color, Int row, Int column, GameWindow *window, Int width, Int height )
{
	BFMEAddImageEntryListboxData *list = (BFMEAddImageEntryListboxData *)window->winGetUserData();
	Int scaledWidth = *(Int *)((UnsignedByte *)TheGlobalData + 0x2C) * width / 1024;
	Int scaledHeight = *(Int *)((UnsignedByte *)TheGlobalData + 0x30) * height / 768;
	if( column >= list->columns  || row >= list->listLength )
	{
		DEBUG_ASSERTCRASH(false, ("Tried to add Image to Listbox at invalid position"));
		return -1;
	}
	if (row == -1)
	{
		row = list->insertPos;
		list->insertPos++;
		list->endPos++;
	}
	if( column == -1 )
		column = 0;
	ListEntryRow *listRow = &list->listData[row];
	if(!listRow->cell)
	{
		listRow->cell = NEW ListEntryCell[list->columns];
		memset(listRow->cell,0,list->columns * sizeof(ListEntryCell));
	}
	if(listRow->cell[column].cellType == LISTBOX_TEXT)
	{
		reinterpret_cast<BFMEAddImageEntryDisplayStringManager *>(TheDisplayStringManager)->freeDisplayString((DisplayString *)listRow->cell[column].data);
	}
	listRow->cell[column].cellType = LISTBOX_IMAGE;
	listRow->cell[column].data = (void *)image;
	listRow->cell[column].color = color;
	listRow->cell[column].height = scaledHeight;
	listRow->cell[column].width = scaledWidth;
	computeTotalHeight( window );
	return (row);
}
struct BFMEAddEntryCell
{
	Int cellType;
	Int color;
	void *data;
	void *userData;
	Int width;
	Int height;
};
struct BFMEAddEntryRow
{
	Int listHeight;
	Int height;
	BFMEAddEntryCell *cell;
};
struct BFMEAddEntryListboxData
{
	Short listLength;
	Short columns;
	UnsignedByte m_unreconstructed_04[0x10];
	Int *columnWidth;
	BFMEAddEntryRow *listData;
	UnsignedByte m_unreconstructed_1c[0x0c];
	Int totalHeight;
	Short endPos;
	Short insertPos;
	UnsignedByte m_unreconstructed_30[4];
	Int selectPos;
	Int *selections;
};
static Int moveRowsDown(ListboxData *list, Int startingRow)
{
	BFMEAddEntryListboxData *bfme = (BFMEAddEntryListboxData *)list;
	Int copyLen = (bfme->endPos - startingRow) * sizeof(BFMEAddEntryRow);
	char *buf = new char[copyLen];
	memcpy(buf, bfme->listData + startingRow, copyLen);
	memcpy(bfme->listData + startingRow + 1, buf, copyLen);
	delete [] buf;
	bfme->endPos++;
	bfme->insertPos = bfme->endPos;
	bfme->listData[startingRow].cell = 0;
	bfme->listData[startingRow].height = 0;
	bfme->listData[startingRow].listHeight = 0;
	if (*(Bool *)((char *)bfme + 0x0b))
	{
		Int i = 0;
		while (bfme->selections[i] >= 0)
		{
			if (startingRow <= bfme->selections[i])
				bfme->selections[i]++;
			i++;
		}
	}
	else
	{
		if (bfme->selectPos >= startingRow)
			bfme->selectPos++;
	}
	return 1;
}
class BFMEAddEntryDisplayString
{
public:
	virtual void displayStringSlot0() = 0;
	virtual void setText(UnicodeString text) = 0;
	virtual void getText() = 0;
	virtual void getTextLength() = 0;
	virtual void notifyTextChanged() = 0;
	virtual void reset() = 0;
	virtual void setFont(GameFont *font) = 0;
	virtual GameFont *getFont() = 0;
	virtual void setWordWrap(Int width) = 0;
	virtual void setWordWrapCentered(Bool centered) = 0;
	virtual void draw(Int x, Int y, Int color, Int dropColor) = 0;
	virtual void drawWithDrop(Int x, Int y, Int color, Int dropColor,
		Int xDrop, Int yDrop) = 0;
	virtual void displayStringSlot12() = 0;
	virtual void displayStringSlot13() = 0;
	virtual void displayStringSlot14() = 0;
	virtual void getSize(Int *width, Int *height) = 0;
};
class BFMEAddEntryDisplayStringManager
{
public:
	virtual void managerSlot0() = 0;
	virtual void managerSlot1() = 0;
	virtual void managerSlot2() = 0;
	virtual void managerSlot3() = 0;
	virtual void managerSlot4() = 0;
	virtual void managerSlot5() = 0;
	virtual void managerSlot6() = 0;
	virtual void managerSlot7() = 0;
	virtual void managerSlot8() = 0;
	virtual DisplayString *newDisplayString() = 0;
};
static __declspec(noinline) Int addEntry(UnicodeString *string, Int color, Int row, Int column,
	GameWindow *window, Bool overwrite)
{
	BFMEAddEntryListboxData *list = (BFMEAddEntryListboxData *)window->winGetUserData();
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
	BFMEAddEntryRow *listRow = &list->listData[row];
	if (!listRow->cell)
	{
		listRow->cell = (BFMEAddEntryCell *)operator new[](list->columns * sizeof(BFMEAddEntryCell));
		memset(listRow->cell, 0, list->columns * sizeof(BFMEAddEntryCell));
		rowsAdded = 1;
	}
	else if (!overwrite)
	{
		moveRowsDown((ListboxData *)list, row);
		listRow->cell = (BFMEAddEntryCell *)operator new[](list->columns * sizeof(BFMEAddEntryCell));
		memset(listRow->cell, 0, list->columns * sizeof(BFMEAddEntryCell));
		rowsAdded = 1;
	}
	listRow->cell[column].cellType = LISTBOX_TEXT;
	listRow->cell[column].color = color;
	if (!listRow->cell[column].data)
		listRow->cell[column].data = (void *)((BFMEAddEntryDisplayStringManager *)TheDisplayStringManager)->newDisplayString();
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
		((BFMEAddEntryDisplayString *)displayString)->getSize(0, &rowHeight);
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
WindowMsgHandledType GadgetListBoxInput( GameWindow *window, UnsignedInt msg,
												 WindowMsgData mData1, WindowMsgData mData2 )
{
	ListboxData *list = (ListboxData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	switch (msg)
	{
		case GWM_CHAR:
		{
			switch (mData1)
			{
				case KEY_ENTER:
				case KEY_SPACE:
				{
					if( BitTest( mData2, KEY_STATE_UP ) )
					{
						doAudioFeedback(window);
						TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																								GLM_DOUBLE_CLICKED,
																								(WindowMsgData)window,
																								list->selectPos );
					}
					break;
				}
				case KEY_DOWN:
				{
					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						if( list->selectPos == -1 )
						{
							list->selectPos = 0;
							adjustDisplay( window, 0, TRUE );
						}
						else if( list->selectPos < list->endPos - 1 )
						{
							list->selectPos++;
							while (1)
							{
								Int cellBottom = list->listData[list->selectPos].listHeight;
								Int cellTop = cellBottom - list->listData[list->selectPos].height;
								Int displayTop = list->displayPos;
								Int displayBottom = list->displayPos + list->displayHeight - 1;
								if ( cellTop < displayTop )
								{
									adjustDisplay(window, -1, TRUE );
								}
								else if ( cellBottom < displayBottom )
								{
									adjustDisplay(window, 0, TRUE );
									break;
								}
								else
								{
									adjustDisplay(window, 1, TRUE );
								}
							}
						}
						TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																								GLM_SELECTED,
																								(WindowMsgData)window,
																								list->selectPos );
					}
					break;
				}
				case KEY_UP:
				{
					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						if( list->selectPos == -1 )
						{
							list->selectPos = 0;
							adjustDisplay( window, 0, TRUE );
						}
						else if( list->selectPos > 0 )
						{
							list->selectPos--;
							while (1)
							{
								if( list->listData[list->selectPos].listHeight - list->listData[list->selectPos].height < list->displayPos )
								{
									list->displayPos = list->listData[list->selectPos].listHeight +1;
									adjustDisplay( window, -1, TRUE );
								}
								else if( list->listData[list->selectPos].listHeight > list->displayPos  + list->displayHeight)
								{
									list->displayPos = list->listData[list->selectPos].listHeight - list->displayHeight;
									adjustDisplay(window, 1, TRUE);
								}
								else
								{
									adjustDisplay(window, 0, TRUE);
									break;
								}
							}
						}
						TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																								GLM_SELECTED,
																								(WindowMsgData)window,
																								list->selectPos );
					}
					break;
				}
				case KEY_RIGHT:
				case KEY_TAB:
					if( BitTest( mData2, KEY_STATE_DOWN ) )
						TheWindowManager->winNextTab(window);
					break;
				case KEY_LEFT:
					if( BitTest( mData2, KEY_STATE_DOWN ) )
						TheWindowManager->winPrevTab(window);
					break;
				default:
					{
						Bool foundIt = false;
						if( BitTest( mData2, KEY_STATE_DOWN ) )
						{
							Int position = list->selectPos;
							for(Int i = 0; i < list->endPos; ++i)
							{
								++position;
								if( position >= list->endPos)
									position = 0;
								ListEntryCell *cell = NULL;
								for(Int j = 0; j < list->columns; ++j)
								{
									cell = &list->listData[position].cell[j];
									if(cell && cell->cellType == LISTBOX_TEXT && cell->data)
									{
										break;
									}
								}
								if(!cell || cell->cellType != LISTBOX_TEXT)
									continue;
								DisplayString *dString = (DisplayString *)cell->data;
								if(!dString)
									continue;
								for(j = 0; j < TheKeyboard->MAX_KEY_STATES; ++j)
								{
									if(dString->getText().getCharAt(0) == TheKeyboard->getPrintableKey(mData1, j))
									{
										list->selectPos = position;
										Int prevPos = getListboxTopEntry(list);
										adjustDisplay(window, position - prevPos, TRUE);
										foundIt = TRUE;
										break;
									}
								}
								if(foundIt)
								{
									doAudioFeedback(window);
									break;
								}
							}
						}
						if (!foundIt)
							return MSG_IGNORED;
					}
			}
			break;
		}
		case GWM_WHEEL_DOWN:
		{
			if( list->endPos <= 0)
				break;
			if (list->listData[list->endPos - 1].listHeight > list->displayHeight + list->displayPos)
				adjustDisplay( window, 1, TRUE );
			break;
		}
		case GWM_WHEEL_UP:
		{
			if( list->endPos <= 0)
			 break;
			adjustDisplay( window, -1, TRUE );
			break;
		}
		case GWM_LEFT_UP:
		{
			TheWindowManager->winSetFocus( window );
			Int mousey = mData1 >> 16;
			Int x, y, i;
			Int oldPos = list->selectPos;
			window->winGetScreenPosition( &x, &y );
			if( instData->getTextLength() )
				y += TheWindowManager->winFontHeight( instData->getFont() ) + 1;
			list->selectPos = -2;
			for( i=0; ; i++ )
			{
				if( i > 0 )
					if( list->listData[ i - 1 ].listHeight >
							(list->displayPos + list->displayHeight) )
					{
						list->selectPos = -1;
						break;
					}
				if( i == list->endPos )
				{
					list->selectPos = -1;
					break;
				}
				if( list->listData[i].listHeight > (mousey - y + list->displayPos) )
					break;
			}
			if( list->doubleClickTime + doubleClickTime > timeGetTime() &&
					(i == oldPos || (oldPos == -1 && ( i>=0 && i<list->endPos ) )) )
			{
				int temp;
				list->doubleClickTime = 0;
				if( oldPos == -1 )
					temp = i;
				else
					temp = oldPos;
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																					GLM_DOUBLE_CLICKED,
																					(WindowMsgData)window,
																					temp );
			}
			if( (i == oldPos) && (list->forceSelect == FALSE) )
			{
				list->selectPos = -1;
			}
			if( (list->selectPos == -2) && (i < list->endPos) )
			{
				list->selectPos = i;
			}
			if( (list->selectPos < 0) && (list->forceSelect) )
			{
				list->selectPos = oldPos;
			}
			list->doubleClickTime = timeGetTime();
			TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																					GLM_SELECTED,
																					(WindowMsgData)window,
																					list->selectPos );
			break;
		}
		case GWM_RIGHT_DOWN:
			doAudioFeedback(window);
			break;
		case GWM_RIGHT_UP:
		{
			TheWindowManager->winSetFocus( window );
			Int pos;
			Int mousex = mData1 & 0xFFFF;
			Int mousey = mData1 >> 16;
			Int x, y, i;
			RightClickStruct rc;
			window->winGetScreenPosition( &x, &y );
			if( instData->getTextLength() )
				y += TheWindowManager->winFontHeight( instData->getFont() ) + 1;
			pos = -2;
			for( i=0; ; i++ )
			{
				if( i > 0 )
					if( list->listData[ i - 1 ].listHeight >
							(list->displayPos + list->displayHeight ) )
					{
						pos = -1;
						break;
					}
				if( i == list->endPos )
				{
					pos = -1;
					break;
				}
				if( list->listData[i].listHeight > (mousey - y + list->displayPos) )
					break;
			}
			if( pos == -2 )
				pos = i;
			rc.pos = pos;
			rc.mouseX = mousex;
			rc.mouseY = mousey;
			TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																					GLM_RIGHT_CLICKED,
																					(WindowMsgData)window,
																					(WindowMsgData)&rc );
			break;
		}
		case GWM_MOUSE_ENTERING:
		{
			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
			{
				BitSet( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																						GBM_MOUSE_ENTERING,
																						(WindowMsgData)window,
																						0 );
			}
			break;
		}
		case GWM_MOUSE_LEAVING:
		{
			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ))
			{
				BitClear( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																						GBM_MOUSE_LEAVING,
																						(WindowMsgData)window,
																						0 );
			}
			break;
		}
		case GWM_LEFT_DRAG:
			if (BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																						GGM_LEFT_DRAG,
																						(WindowMsgData)window,
																						0 );
			break;
		case GWM_LEFT_DOWN:
			doAudioFeedback(window);
			return MSG_HANDLED;
		default:
			return MSG_IGNORED;
	}
	return MSG_HANDLED;
}
WindowMsgHandledType GadgetListBoxMultiInput(GameWindow *, UnsignedInt, UnsignedInt, UnsignedInt);
struct Rva004B9F10Row
{
    int listHeight;
    int height;
    ListEntryCell *cell;
};
struct Rva004B9F10List
{
    short listLength, columns;
    int *columnWidthPercentage;
    bool autoScroll, autoPurge, scrollBar, multiSelect;
    bool forceSelect, scrollIfAtEnd, audioFeedback, m_byte0f;
    bool m_byte10, m_byte11, m_byte12, m_byte13;
    int *columnWidth;
    Rva004B9F10Row *listData;
    GameWindow *upButton, *downButton, *slider;
    int totalHeight;
    short endPos, insertPos;
    int m_at30;
    int selectPos;
    int *selections;
    short displayHeight;
    unsigned int doubleClickTime;
    short displayPos;
    int m_at48;
};
__declspec(noinline) static void Rva004B7DC0(GameWindow *window, int index, int mode)
{
    if (index < 0)
        return;
    Rva004B9F10List *list = (Rva004B9F10List *)window->winGetUserData();
    if (index >= list->endPos)
        return;
    Rva004B9F10Row *rows = list->listData;
    Rva004B9F10Row *row = &rows[index];
    int y;
    switch (mode)
    {
    case 1:
        y = row->listHeight - row->height;
        break;
    default:
        y = (2 * row->listHeight - list->displayHeight - row->height) / 2;
        break;
    }
    list->displayPos = 0;
    int entry = 0;
    while (list->listData[entry].listHeight - list->listData[entry].height < y)
        ++entry;
    while (entry > 0 && list->totalHeight < rows[entry - 1].listHeight - rows[entry - 1].height +
                                                list->displayHeight)
        --entry;
    list->displayPos = rows[entry].listHeight - rows[entry].height;
    if (rows[list->endPos - 1].listHeight < list->displayPos + list->displayHeight)
        list->totalHeight = list->displayPos + list->displayHeight;
    adjustDisplay(window, true);
}
struct Rva004B9F10InstanceFont { char m_prefix[0x184]; GameFont *font; GameFont *getFont() { return font; } };
WindowMsgHandledType GadgetListBoxSystem( GameWindow *window, UnsignedInt msg,
													WindowMsgData mData1, WindowMsgData mData2 )
{
	Rva004B9F10List *list = (Rva004B9F10List *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	ICoord2D *pos;
	switch( msg )
	{
		case GGM_SET_LABEL:
		{
			instData->setText(*(UnicodeString*)mData1);
			break;
		}
		case 0x401a:
		{
			pos = (ICoord2D *)mData1;
			TextAndColor *tAndC = (TextAndColor *)mData2;
			if(pos->x >= list->columns || pos->y >= list->listLength ||
					list->listData[pos->y].cell[pos->x].cellType != LISTBOX_TEXT)
			{
				((StringBase<WideChar> *)&tAndC->string)->set(*(const StringBase<WideChar> *)&UnicodeString::TheEmptyString);
				tAndC->color = 0;
			}
			else
			{
				tAndC->string = ((DisplayString *)list->listData[ pos->y ].cell[pos->x].data)->getText();
				tAndC->color = list->listData[ pos->y ].cell[pos->x].color;
			}
		break;
		}
		case GBM_SELECTED:
		{
            if (list->m_byte10)
            {
                Int amount = 20;
                if (window->winGetFont())
                    amount = window->winGetFont()->height;
                if ((GameWindow *)mData1 == list->upButton)
                    adjustDisplayByDelta(window, -amount, TRUE);
                else if ((GameWindow *)mData1 == list->downButton)
                    adjustDisplayByDelta(window, amount, TRUE);
                break;
            }
			if( (GameWindow *)mData1 == list->upButton )
			{
				if( list->displayPos > 0 )
					adjustDisplay( window, -1, TRUE );
			}
			else if( (GameWindow *)mData1 == list->downButton )
			{
				if( list->displayPos + list->displayHeight < list->totalHeight )
					adjustDisplay( window, 1, TRUE );
			}
			break;
		}
		case 0x4013:
		{
			for( Int i = 0; i < list->listLength; i++ )
			{
				ListEntryCell *cells = list->listData[i].cell;
				for (int j = list->columns - 1; j >=0; j-- )
				{
					if(!cells)
						break;
					if( cells[j].cellType == LISTBOX_TEXT )
					{
						if ( cells[j].data )
						{
							((BFMEAddImageEntryDisplayStringManager *)TheDisplayStringManager)->freeDisplayString((DisplayString *) cells[j].data );
						}
					}
					cells[j].userData = NULL;
					cells[j].data = NULL;
				}
				delete[](list->listData[i].cell);
				list->listData[i].cell = NULL;
			}
			memset(list->listData,0,list->listLength * sizeof(Rva004B9F10Row));
			if( mData1 != GP_DONT_UPDATE )
			{
				list->displayPos = 0;
			}
			if( list->multiSelect )
				memset( list->selections, -1, list->listLength * sizeof( Int ) );
			else
				list->selectPos = -1;
			list->insertPos = 0;
			list->endPos = 0;
			list->totalHeight = 0;
			adjustDisplay( window, 0, TRUE );
			break;
		}
		case 0x4012:
		{
			Int i;
			if( list->endPos <= (Int)mData1 )
				break;
			ListEntryCell *cells = list->listData[mData1].cell;
			if(cells)
				for( i = 0; i <= list->columns; i ++ )
				{
					if( cells[i].cellType == LISTBOX_TEXT && cells[i].data )
						((BFMEAddImageEntryDisplayStringManager *)TheDisplayStringManager)->freeDisplayString((DisplayString *) cells[i].data );
					cells[i].data = NULL;
					cells[i].userData = NULL;
				}
			delete [](list->listData[mData1].cell);
            list->listData[mData1].cell = NULL;
			memcpy( &list->listData[mData1], &list->listData[(mData1+1)],
							(list->endPos - mData1 - 1) * sizeof(Rva004B9F10Row) );
			list->endPos--;
			list->insertPos = list->endPos;
			if( list->multiSelect )
			{
				i = 0;
				while( list->selections[i] >= 0 )
				{
					if( (Int)mData1 < list->selections[i] )
						list->selections[i]--;
					else if ( (Int)mData1 == list->selections[i] )
					{
						removeSelection( (ListboxData *)list, i );
						i--;
					}
					i++;
				}
			}
			else
			{
				if( (Int)mData1 < list->selectPos )
					list->selectPos--;
				else if ( (Int)mData1 == list->selectPos )
					list->selectPos = -1;
			}
			computeTotalHeight( window );
			break;
		}
		case 0x4011:
		{
			Bool success = TRUE;
			Int addedIndex = -1;
			AddMessageStruct *addInfo = (AddMessageStruct*)mData1;
			if (addInfo->row >= list->insertPos)
				addInfo->row = -1;
			Int row = addInfo->row;
			if( addInfo->row == -1 && list->insertPos == list->listLength )
			{
				row = list->insertPos;
				if( list->insertPos == list->listLength )
				{
					if( list->autoPurge )
						TheWindowManager->winSendSystemMsg( window, 0x401e, 1, 0 );
					else
						success = FALSE;
				}
			}
			else if (addInfo->row != -1 && !addInfo->overwrite && list->insertPos == list->listLength)
			{
				if( list->autoPurge )
					TheWindowManager->winSendSystemMsg( window, 0x401e, 1, 0 );
				else
					success = FALSE;
			}
			if(success)
			{
				if( addInfo->type == LISTBOX_TEXT )
				{
					addedIndex = addEntry( (UnicodeString *)addInfo->data, mData2, addInfo->row, addInfo->column, window, addInfo->overwrite );
				}
				else if ( addInfo->type == LISTBOX_IMAGE )
				{
					addedIndex = addImageEntry( (const Image *)addInfo->data, mData2, addInfo->row, addInfo->column, window, addInfo->width, addInfo->height );
				}
				else
					success = FALSE;
			}
			if( success )
			{
				if( list->autoScroll )
				{
					while( TRUE )
					{
						if( row == -1 )
						{
							if( list->listData[(list->insertPos - 1)].listHeight >=
									(list->displayPos + list->displayHeight) )
								adjustDisplay( window, 1, TRUE );
							else
								break;
						}
						else
						{
							if( list->listData[( row )].listHeight >=
									(list->displayPos + list->displayHeight) )
								adjustDisplay( window, 1, TRUE );
							else
								break;
						}
					}
				}
				if( list->multiSelect )
				{
					Int i = 0;
					while( list->selections[i] >= 0 )
					{
						if( (row = list->selections[i]) != 0 )
							list->selections[i] = -1;
						i++;
					}
				}
				else
				{
					if( row == list->selectPos )
						list->selectPos = -1;
                    adjustDisplay(window, TRUE);
				}
			}
			return((WindowMsgHandledType) addedIndex );
		}
		case 0x4019:
		{
			if( (Int)mData1 < 0 )
			{
				if( list->multiSelect )
					memset( list->selections, -1, list->listLength * sizeof(Int) );
				else
				{
				}
				break;
			}
			if( !list->listData[ mData1 ].cell )
				break;
			if( list->multiSelect )
			{
				Int i = 0;
				Bool removed = FALSE;
				while( list->selections[i] >= 0 )
				{
					if( list->selections[i] == (Int)mData1 )
					{
						removeSelection( (ListboxData *)list, i );
						removed = TRUE;
						break;
					}
					i++;
				}
				if( removed == FALSE )
				{
					list->selections[i] = (Int)mData1;
					list->selections[i+1] = -1;
				}
			}
			else
			{
			}
			break;
		}
		case 0x4017:
		{
			const Int *selectList = (const Int *)mData1;
            list->m_at48 = -1;
			Int selectCount = (Int)mData2;
			DEBUG_ASSERTCRASH( list->multiSelect || selectCount == 1, ("Bad selection size"));
			if( selectList[0] < 0 || list->listLength <= selectList[0] )
			{
				if( list->multiSelect )
					memset( list->selections, -1, list->listLength * sizeof(Int) );
				else
					list->selectPos = -1;
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																						0x4014,
																						(WindowMsgData)window,
																						list->selectPos );
				break;
			}
			if( list->multiSelect )
			{
				for (Int i=0; i<selectCount && i<list->endPos; ++i)
				{
					if (list->listLength <= selectList[i])
					{
						break;
					}
					if( !list->listData[ selectList[i] ].cell )
					{
						break;
					}
					list->selections[i] = selectList[i];
				}
				list->selections[i] = -1;
			}
			else
			{
				if( !list->listData[ selectList[0] ].cell )
				{
					break;
				}
				list->selectPos = selectList[0];
                GameWindow *parent = window->winGetParent();
                if (parent && BitTest(parent->winGetStyle(), GWS_COMBO_BOX))
                {
                    TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4014,
                        (WindowMsgData)window, list->selectPos);
                    break;
                }
                Rva004B7DC0(window, list->selectPos, 0);
			}
			break;
		}
		case 0x401e:
		{
			if( list->endPos < (Int)mData1 )
				break;
			ListEntryCell *cells = NULL;
			for (Int i = 0; i < (Int)mData1; i++)
			{
				cells = list->listData[i].cell;
				if(cells)
					for( Int j = 0; j < list->columns; j++ )
					{
						if( cells[j].cellType == LISTBOX_TEXT && cells[j].data )
							((BFMEAddImageEntryDisplayStringManager *)TheDisplayStringManager)->freeDisplayString((DisplayString *) cells[j].data );
						cells[j].data = NULL;
						cells[j].userData = NULL;
						cells[j].color = 0;
						cells[j].cellType = 0;
					}
				delete[](list->listData[i].cell);
				list->listData[i].cell = NULL;
			}
			memcpy(list->listData, &list->listData[mData1],
						(list->endPos - mData1) * sizeof(Rva004B9F10Row) );
			list->endPos -= mData1;
			list->insertPos = list->endPos;
			for(i = 0; i < (Int)mData1; i ++)
			{
				list->listData[list->endPos + i].cell = NULL;
			}
			if( list->multiSelect )
			{
				Int i = 0;
				while( list->selections[i] >= 0 )
				{
					if( (Int)mData1 >= list->selections[i] )
						list->selections[i] -= (Int)mData1;
					else
					{
						removeSelection( (ListboxData *)list, i );
						i--;
					}
					i++;
				}
			}
			else
			{
				if( list->selectPos > 0 )
					list->selectPos -= mData1;
			}
			if( list->displayPos > 0 )
				adjustDisplay( window, (-1 * mData1), TRUE );
			computeTotalHeight( window );
			break;
		}
		case 0x4018:
		{
			if( list->multiSelect )
				*(Int*)mData2 = (Int)list->selections;
			else
				*(Int*)mData2 = list->selectPos;
			break;
		}
		case 0x401b:
			list->upButton = (GameWindow *)mData1;
			break;
		case 0x401c:
			list->downButton = (GameWindow *)mData1;
			break;
		case 0x401d:
			list->slider = (GameWindow *)mData1;
			break;
		case GWM_CREATE:
			break;
		case GGM_RESIZED:
		{
			Int width = (Int)mData1;
			Int height = (Int)mData2;
			ICoord2D downSize = {0, 0};
			ICoord2D upSize = {0, 0};
			ICoord2D sliderSize = {0, 0};
			GameWindow *child = NULL;
			ICoord2D sliderChildSize = {0, 0};
			if (list->downButton)
				list->downButton->winGetSize( &downSize.x, &downSize.y );
			if (list->upButton)
				list->upButton->winGetSize( &upSize.x, &upSize.y );
			if (list->slider)
			{
				list->slider->winGetSize( &sliderSize.x, &sliderSize.y );
				child = list->slider->winGetChild();
				if (child)
					child->winGetSize( &sliderChildSize.x, &sliderChildSize.y );
			}
			if( list->upButton )
			{
				list->upButton->winSetPosition( width - upSize.x - 2, 2 );
			}
			if( list->downButton )
			{
				list->downButton->winSetPosition( width - downSize.x - 2,
																					height - downSize.y - 2 );
			}
			if( list->slider )
			{
				list->slider->winSetSize( sliderSize.x,
																	height - (2 * upSize.y) -6 );
				list->slider->winSetPosition( width - sliderSize.x -2, upSize.y + 3 );
			}
			list->displayHeight = height;
			if( instData->getTextLength() )
			{
				list->displayHeight -= TheWindowManager->winFontHeight( ((Rva004B9F10InstanceFont *)instData)->getFont() );
			}
			if( list->columns == 1 )
			{
				list->columnWidth[0] = width;
				if( list->slider )
				{
					ICoord2D sliderSize;
					list->slider->winGetSize( &sliderSize.x, &sliderSize.y );
					list->columnWidth[0] -= sliderSize.x;
				}
			}
			else
			{
				if (list->columnWidthPercentage && list->columnWidth)
                {
				Int totalWidth = width;
				if( list->slider )
				{
					ICoord2D sliderSize;
					list->slider->winGetSize( &sliderSize.x, &sliderSize.y );
					totalWidth -= sliderSize.x;
				}
				for(Int i = 0; i < list->columns; i++ )
				{
					list->columnWidth[i] = list->columnWidthPercentage[i] * totalWidth / 100;
				}
                }
			}
            if (!(window->winGetStatus() & 0x4000))
            {
                for (Int rowIndex = 0; rowIndex < list->endPos; ++rowIndex)
                {
                    Rva004B9F10Row *row = &list->listData[rowIndex];
                    for (Int column = 0; column < list->columns; ++column)
                    {
                        ListEntryCell &cell = row->cell[column];
                        if (cell.cellType == LISTBOX_TEXT)
                        {
                            DisplayString *text = (DisplayString *)cell.data;
                            if (text)
                                text->setWordWrap(list->columnWidth[column] - 7);
                        }
                    }
                }
            }
            computeTotalHeight(window);
            if (list->multiSelect)
                adjustDisplay(window, 0, TRUE);
            else if (list->selectPos >= 0)
                Rva004B7DC0(window, list->selectPos, 0);
            else
                adjustDisplay(window, TRUE);
            break;
		}
		case 0x401f:
		{
			if( mData1 > 0 )
				list->displayPos = list->listData[(mData1 - 1)].listHeight + 1;
			else
				list->displayPos = 0;
			if( list->displayPos + list->displayHeight >= list->totalHeight )
			{
				list->displayPos = list->totalHeight - list->displayHeight;
			}
			adjustDisplay( window, 0, TRUE );
			break;
		}
		case GWM_DESTROY:
		{
			Int i;
			for( i = 0; i < list->listLength; i++ )
			{
				ListEntryCell *cells = list->listData[i].cell;
				for (int j = list->columns - 1; j >=0; j-- )
				{
					if(!cells)
						break;
					if( cells[j].cellType == LISTBOX_TEXT )
					{
						if ( cells[j].data )
						{
							((BFMEAddImageEntryDisplayStringManager *)TheDisplayStringManager)->freeDisplayString((DisplayString *) cells[j].data );
						}
					}
					cells[j].userData = NULL;
					cells[j].data = NULL;
				}
				delete[](list->listData[i].cell);
				list->listData[i].cell = NULL;
			}
			delete[]( list->listData );
			if( list->columnWidth	)
				delete[]( list->columnWidth );
			if( list->columnWidthPercentage	)
				delete[]( list->columnWidthPercentage );
			if( list->multiSelect )
				delete[]( list->selections );
			delete( list );
			break;
		}
		case GWM_INPUT_FOCUS:
		{
			if( mData1 == FALSE )
			{
				BitClear( instData->m_state, WIN_STATE_HILITED );
			}
			else
			{
				BitSet( instData->m_state, WIN_STATE_HILITED );
			}
			TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																					GGM_FOCUS_CHANGE,
																					mData1,
																					window->winGetWindowId() );
			*(Bool*)mData2 = TRUE;
			break;
		}
        case 0x400c:
        {
            SliderData *sData = (SliderData *)list->slider->winGetUserData();
            list->displayPos = sData->maxVal - mData2;
            adjustDisplayByDelta(window, 0, FALSE);
            break;
        }
		case 0x4021:
		{
			void *data = (void *)mData2;
			pos = (ICoord2D *)mData1;
			if (pos->y >= 0 && pos->y < list->endPos && list->listData[pos->y].cell && pos->x >= 0 && pos->x < list->columns)
				list->listData[pos->y].cell[pos->x].userData = data;
			break;
		}
		case 0x4020:
		{
			pos = (ICoord2D *)mData1;
			void **data = (void **)mData2;
			*data = NULL;
			if (pos->y >= 0 && pos->y < list->endPos && list->listData[pos->y].cell && pos->x >= 0 && pos->x < list->columns)
				*data = list->listData[pos->y].cell[pos->x].userData;
			break;
		}
		default:
			return MSG_IGNORED;
	}
	return MSG_HANDLED;
}
void GadgetListBoxSetColors_ZHReference( GameWindow *listbox,
														 Color enabledColor,
														 Color enabledBorderColor,
														 Color enabledSelectedItemColor,
														 Color enabledSelectedItemBorderColor,
														 Color disabledColor,
														 Color disabledBorderColor,
														 Color disabledSelectedItemColor,
														 Color disabledSelectedItemBorderColor,
														 Color hiliteColor,
														 Color hiliteBorderColor,
														 Color hiliteSelectedItemColor,
														 Color hiliteSelectedItemBorderColor )
{
	ListboxData *listboxData = (ListboxData *)listbox->winGetUserData();
	GadgetListBoxSetEnabledColor( listbox, enabledColor );
	GadgetListBoxSetEnabledBorderColor( listbox, enabledBorderColor );
	GadgetListBoxSetEnabledSelectedItemColor( listbox, enabledSelectedItemColor );
	GadgetListBoxSetEnabledSelectedItemBorderColor( listbox, enabledSelectedItemBorderColor );
	GadgetListBoxSetDisabledColor( listbox, disabledColor );
	GadgetListBoxSetDisabledBorderColor( listbox, disabledBorderColor );
	GadgetListBoxSetDisabledSelectedItemColor( listbox, disabledSelectedItemColor );
	GadgetListBoxSetDisabledSelectedItemBorderColor( listbox, disabledSelectedItemBorderColor );
	GadgetListBoxSetHiliteColor( listbox, hiliteColor );
	GadgetListBoxSetHiliteBorderColor( listbox, hiliteBorderColor );
	GadgetListBoxSetHiliteSelectedItemColor( listbox, hiliteSelectedItemColor );
	GadgetListBoxSetHiliteSelectedItemBorderColor( listbox, hiliteSelectedItemBorderColor );
	GameWindow *slider = listboxData->slider;
	if( slider )
	{
		GameWindow *upButton = listboxData->upButton;
		GameWindow *downButton = listboxData->downButton;
		GadgetSliderSetEnabledColor( slider, GadgetListBoxGetEnabledColor( listbox ) );
		GadgetSliderSetEnabledBorderColor( slider, GadgetListBoxGetEnabledBorderColor( listbox ) );
		GadgetSliderSetDisabledColor( slider, GadgetListBoxGetDisabledColor( listbox ) );
		GadgetSliderSetDisabledBorderColor( slider, GadgetListBoxGetDisabledBorderColor( listbox ) );
		GadgetSliderSetHiliteColor( slider, GadgetListBoxGetHiliteColor( listbox ) );
		GadgetSliderSetHiliteBorderColor( slider, GadgetListBoxGetHiliteBorderColor( listbox ) );
		GadgetButtonSetEnabledColor( upButton, GadgetSliderGetEnabledColor( slider ) );
		GadgetButtonSetEnabledBorderColor( upButton, GadgetSliderGetEnabledBorderColor( slider ) );
		GadgetButtonSetEnabledSelectedColor( upButton, GadgetSliderGetEnabledSelectedThumbColor( slider ) );
		GadgetButtonSetEnabledSelectedBorderColor( upButton, GadgetSliderGetEnabledSelectedThumbBorderColor( slider ) );
		GadgetButtonSetDisabledColor( upButton, GadgetSliderGetDisabledColor( slider ) );
		GadgetButtonSetDisabledBorderColor( upButton, GadgetSliderGetDisabledBorderColor( slider ) );
		GadgetButtonSetDisabledSelectedColor( upButton, GadgetSliderGetDisabledSelectedThumbColor( slider ) );
		GadgetButtonSetDisabledSelectedBorderColor( upButton, GadgetSliderGetDisabledSelectedThumbBorderColor( slider ) );
		GadgetButtonSetHiliteColor( upButton, GadgetSliderGetHiliteColor( slider ) );
		GadgetButtonSetHiliteBorderColor( upButton, GadgetSliderGetHiliteBorderColor( slider ) );
		GadgetButtonSetHiliteSelectedColor( upButton, GadgetSliderGetHiliteSelectedThumbColor( slider ) );
		GadgetButtonSetHiliteSelectedBorderColor( upButton, GadgetSliderGetHiliteSelectedThumbBorderColor( slider ) );
		GadgetButtonSetEnabledColor( downButton, GadgetSliderGetEnabledColor( slider ) );
		GadgetButtonSetEnabledBorderColor( downButton, GadgetSliderGetEnabledBorderColor( slider ) );
		GadgetButtonSetEnabledSelectedColor( downButton, GadgetSliderGetEnabledSelectedThumbColor( slider ) );
		GadgetButtonSetEnabledSelectedBorderColor( downButton, GadgetSliderGetEnabledSelectedThumbBorderColor( slider ) );
		GadgetButtonSetDisabledColor( downButton, GadgetSliderGetDisabledColor( slider ) );
		GadgetButtonSetDisabledBorderColor( downButton, GadgetSliderGetDisabledBorderColor( slider ) );
		GadgetButtonSetDisabledSelectedColor( downButton, GadgetSliderGetDisabledSelectedThumbColor( slider ) );
		GadgetButtonSetDisabledSelectedBorderColor( downButton, GadgetSliderGetDisabledSelectedThumbBorderColor( slider ) );
		GadgetButtonSetHiliteColor( downButton, GadgetSliderGetHiliteColor( slider ) );
		GadgetButtonSetHiliteBorderColor( downButton, GadgetSliderGetHiliteBorderColor( slider ) );
		GadgetButtonSetHiliteSelectedColor( downButton, GadgetSliderGetHiliteSelectedThumbColor( slider ) );
		GadgetButtonSetHiliteSelectedBorderColor( downButton, GadgetSliderGetHiliteSelectedThumbBorderColor( slider ) );
	}
}
UnicodeString GadgetListBoxGetText( GameWindow *listbox, Int row, Int column)
{
	Color color;
	return GadgetListBoxGetTextAndColor( listbox,&color,row,column );
}
UnicodeString GadgetListBoxGetTextAndColor( GameWindow *listbox, Color *color, Int row, Int column)
{
	*color = 0;
	if( listbox == NULL  || row == -1 || column == -1)
		return UnicodeString::TheEmptyString;
	if( BitTest( listbox->winGetStyle(), GWS_SCROLL_LISTBOX ) == FALSE )
		return UnicodeString::TheEmptyString;
	TextAndColor tAndC;
	ICoord2D pos;
	pos.x = column;
	pos.y = row;
	TheWindowManager->winSendSystemMsg( listbox, 0x401A, (WindowMsgData)&pos, (WindowMsgData)&tAndC );
		*color = tAndC.color;
		return tAndC.string;
}
Int GadgetListBoxAddEntryImage( GameWindow *listbox, const Image *image,
															 Int row, Int column,
															 Int hight, Int width,
															 Bool overwrite, Color color )
{
	Int index;
	AddMessageStruct addInfo;
	addInfo.row = row;
	addInfo.column = column;
	addInfo.type = LISTBOX_IMAGE;
	addInfo.data = image;
	addInfo.overwrite = overwrite;
	addInfo.height = hight;
	addInfo.width = width;
	index = (Int) TheWindowManager->winSendSystemMsg( listbox, 0x4011, (WindowMsgData)&addInfo, color );
	return (index);
}
Int GadgetListBoxAddEntryImage( GameWindow *listbox, const Image *image,
															 Int row, Int column,
															 Bool overwrite, Color color )
{
	return GadgetListBoxAddEntryImage(listbox, image, row, column,  -1, -1, overwrite, color);
}
void GadgetListBoxSetFont( GameWindow *g, GameFont *font )
{
	ListboxData *listData = (ListboxData *)g->winGetUserData();
	DisplayString *dString;
	typedef void (DisplayString::*BFMESetFontFn)( GameFont * );
	dString = g->winGetInstanceData()->getTextDisplayString();
	if( dString )
		(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );
	dString = g->winGetInstanceData()->getTooltipDisplayString();
	if( dString )
		(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );
	if( listData )
		for( Int i = 0; i < listData->listLength; i++ )
		{
			if((*(ListEntryRow **)((char *)listData + 0x18))[i].cell)
				for( Int j = 0; j < listData->columns; j++ )
				{
					if( (*(ListEntryRow **)((char *)listData + 0x18))[i].cell[j].cellType == LISTBOX_TEXT &&
						(*(ListEntryRow **)((char *)listData + 0x18))[i].cell[j].data )
					{
						dString = (DisplayString *)(*(ListEntryRow **)((char *)listData + 0x18))[i].cell[j].data;
						(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );
					}
				}
		}
}
void GadgetListboxCreateScrollbar( GameWindow *listbox )
{
	ListboxData *listData = (ListboxData *)listbox->winGetUserData();
	WinInstanceData winInstData;
	SliderData sData = { 0 };
	Int buttonWidth, buttonHeight;
	Int sliderButtonWidth, sliderButtonHeight;
	Int fontHeight;
	Int top;
	Int bottom;
	UnsignedInt status = listbox->winGetStatus();
	Bool title = FALSE;
	Int width, height;
	listbox->winGetSize( &width, &height );
	if( listbox->winGetTextLength() )
		title = TRUE;
	status &= ~(WIN_STATUS_BORDER | WIN_STATUS_HIDDEN | WIN_STATUS_NO_INPUT);
	fontHeight = TheWindowManager->winFontHeight( listbox->winGetFont() );
	top = title ? (fontHeight + 1):0;
	bottom = title ? (height - (fontHeight + 1)):height;
	winInstData.init();
	buttonWidth = 21;
	buttonHeight = 22;
	status |= WIN_STATUS_IMAGE;
	winInstData.m_owner = listbox;
	winInstData.m_style = GWS_PUSH_BUTTON;
	if( BitTest( listbox->winGetStyle(), GWS_MOUSE_TRACK ) )
		BitSet( winInstData.m_style, GWS_MOUSE_TRACK );
	listData->upButton =
		 TheWindowManager->gogoGadgetPushButton( listbox,
																						 status | WIN_STATUS_ACTIVE | WIN_STATUS_ENABLED,
																						 width - buttonWidth -2, top+2,
																						 buttonWidth, buttonHeight,
																						 &winInstData, NULL, TRUE );
	winInstData.init();
	winInstData.m_style = GWS_PUSH_BUTTON;
	winInstData.m_owner = listbox;
	if( BitTest( listbox->winGetStyle(), GWS_MOUSE_TRACK ) )
		BitSet( winInstData.m_style, GWS_MOUSE_TRACK );
	listData->downButton =
			 TheWindowManager->gogoGadgetPushButton( listbox,
																							 status | WIN_STATUS_ACTIVE | WIN_STATUS_ENABLED,
																							 width - buttonWidth -2,
																							 (top + bottom - buttonHeight -2),
																							 buttonWidth, buttonHeight,
																							 &winInstData, NULL, TRUE );
	sliderButtonWidth = buttonWidth;
	sliderButtonHeight = GADGET_SIZE;
	winInstData.init();
	winInstData.m_style = GWS_VERT_SLIDER;
	winInstData.m_owner = listbox;
	if( BitTest( listbox->winGetStyle(), GWS_MOUSE_TRACK ) )
		BitSet( winInstData.m_style, GWS_MOUSE_TRACK );
	memset( &sData, 0, sizeof(SliderData) );
	listData->slider =
			TheWindowManager->gogoGadgetSlider( listbox,
																					status | WIN_STATUS_ACTIVE | WIN_STATUS_ENABLED,
																					width - sliderButtonWidth - 2,
																					(top + buttonHeight + 3),
																					sliderButtonWidth, bottom - (2 * buttonHeight) - 6,
																					&winInstData, &sData, NULL, TRUE );
	listData->scrollBar = TRUE;
}
void GadgetListBoxAddMultiSelect( GameWindow *listbox )
{
	ListboxData *listboxData = (ListboxData *)listbox->winGetUserData();
	if( !listboxData )
		return;
	if( listboxData->multiSelect )
		return;
	Int **selections = (Int **)((char *)listboxData + 0x38);
	*selections = NEW Int [listboxData->listLength];
	if( *selections == NULL )
	{
		ListEntryRow **listData = (ListEntryRow **)((char *)listboxData + 0x18);
		delete [] ( *listData );
		return;
	}
	memset( *selections, -1,
		      listboxData->listLength * sizeof(Int) );
	listboxData->multiSelect = TRUE;
	listbox->winSetInputFunc( GadgetListBoxMultiInput );
}
void GadgetListBoxRemoveMultiSelect( GameWindow *listbox )
{
	ListboxData *listData = (ListboxData *)listbox->winGetUserData();
	if( listData->multiSelect )
	{
		Int **selections = (Int **)((char *)listData + 0x38);
		if( *selections )
		{
			delete [] ( *selections );
			*selections = NULL;
		}
		listData->multiSelect = FALSE;
		listbox->winSetInputFunc( GadgetListBoxInput );
	}
}
struct Rva004BB8E0ListboxData
{
	Short listLength;
	Short columns;
	UnsignedByte m_pad04[7];
	Bool multiSelect;
	UnsignedByte m_pad0c[0x0c];
	ListEntryRow *listData;
	GameWindow *upButton;
	GameWindow *downButton;
	GameWindow *slider;
	Int totalHeight;
	Short endPos;
	Short insertPos;
	UnsignedByte m_pad30[4];
	Int selectPos;
	Int *selections;
	Short displayHeight;
	UnsignedByte m_pad3e[2];
	UnsignedInt doubleClickTime;
	Short displayPos;
};
class Rva004BB8E0DisplayStringManager
{
public:
	virtual void pad00() = 0;
	virtual void pad04() = 0;
	virtual void pad08() = 0;
	virtual void pad0c() = 0;
	virtual void pad10() = 0;
	virtual void pad14() = 0;
	virtual void pad18() = 0;
	virtual void pad1c() = 0;
	virtual void pad20() = 0;
	virtual void pad24() = 0;
	virtual void freeDisplayString(DisplayString *string) = 0;
};
void GadgetListBoxSetListLength( GameWindow *listbox, Int newLength )
{
	Rva004BB8E0ListboxData *listboxData =
		(Rva004BB8E0ListboxData *)listbox->winGetUserData();
	DEBUG_ASSERTCRASH(listboxData, ("We don't have our needed listboxData!"));
	if( !listboxData )
		return;
	DEBUG_ASSERTCRASH(listboxData->columns > 0,("We need at least one Column in the listbox"));
	if( listboxData->columns < 1 )
		return;
  Int columns = listboxData->columns;
	ListEntryRow *newData = NEW ListEntryRow[ newLength ];
	DEBUG_ASSERTCRASH(newData, ("Unable to allocate new data structures for the Listbox"));
	if( !newData )
		return;
	Int i;
	memset( newData, 0, newLength  * sizeof( ListEntryRow ) );
	if(newLength >= listboxData->listLength)
	{
		memcpy(newData,listboxData->listData,listboxData->listLength * sizeof( ListEntryRow ) );
	}
	else
	{
		if( listboxData->displayPos >newLength)
			listboxData->displayPos = newLength;
		if(listboxData->selectPos > newLength || listboxData->multiSelect)
			listboxData->selectPos = -1;
    if(listboxData->insertPos > newLength)
			listboxData->insertPos = newLength;
    listboxData->endPos = newLength;
		memcpy(newData,listboxData->listData,newLength * sizeof( ListEntryRow ) );
	}
	for( i = 0; i < listboxData->listLength; i++ )
	{
		ListEntryCell *cells = listboxData->listData[i].cell;
		for (int j = columns - 1; j >=0; j-- )
		{
			if(!cells)
				break;
			if ( i >= newLength )
			{
				if( cells[j].cellType == LISTBOX_TEXT  && i >= newLength)
				{
					if ( cells[j].data )
					{
						reinterpret_cast<Rva004BB8E0DisplayStringManager *>(TheDisplayStringManager)->freeDisplayString((DisplayString *) cells[j].data );
					}
				}
			}
		}
		if ( i >= newLength )
			delete [] (listboxData->listData[i].cell);
		listboxData->listData[i].cell = NULL;
	}
	listboxData->listLength = newLength;
	if( listboxData->listData )
		delete [] ( listboxData->listData );
	listboxData->listData = newData;
	computeTotalHeight(listbox);
	if( listboxData->listData == NULL )
	{
		DEBUG_LOG(( "Unable to allocate listbox data pointer\n" ));
		assert( 0 );
		return;
	}
	if( listboxData->multiSelect )
	{
		GadgetListBoxRemoveMultiSelect( listbox );
		GadgetListBoxAddMultiSelect( listbox );
	}
}
Int GadgetListBoxGetListLength( GameWindow *listbox )
{
	ListboxData *listboxData = (ListboxData *)listbox->winGetUserData();
	if (listboxData->multiSelect)
	{
		return listboxData->listLength;
	}
	else
	{
		return 1;
	}
}
Int GadgetListBoxGetNumEntries( GameWindow *listbox )
{
	if (!listbox)
		return 0;
	ListboxData *listboxData = (ListboxData *)listbox->winGetUserData();
	if (listboxData)
		return *(Short *)((char *)listboxData + 0x2C);
	return 0;
}
void GadgetListBoxGetSelected( GameWindow *listbox, Int *selectList )
{
	if( listbox == NULL )
		return;
	TheWindowManager->winSendSystemMsg( listbox, 0x4018, 0, (WindowMsgData)selectList );
}
void GadgetListBoxSetSelected( GameWindow *listbox, Int selectIndex )
{
	if( listbox == NULL )
		return;
	TheWindowManager->winSendSystemMsg( listbox, 0x4017, (WindowMsgData)(&selectIndex), 1 );
}
void GadgetListBoxSetSelected( GameWindow *listbox, const Int *selectList, Int selectCount )
{
	if( listbox == NULL )
		return;
	TheWindowManager->winSendSystemMsg( listbox, 0x4017, (WindowMsgData)selectList, selectCount );
}
void GadgetListBoxReset( GameWindow *listbox )
{
	if( listbox == NULL )
		return;
	TheWindowManager->winSendSystemMsg( listbox, 0x4013, 0, 0 );
}
void GadgetListBoxSetItemData( GameWindow *listbox, void *data, Int row, Int column )
{
	ICoord2D pos;
	pos.x = column;
	pos.y = row;
	if (listbox)
		TheWindowManager->winSendSystemMsg( listbox, 0x4021, (WindowMsgData)&pos, (WindowMsgData)data);
}
void *GadgetListBoxGetItemData( GameWindow *listbox, Int row, Int column)
{
	void *data = NULL;
	ICoord2D pos;
	pos.x = column;
	pos.y = row;
	if (listbox)
	{
		TheWindowManager->winSendSystemMsg( listbox, 0x4020, (WindowMsgData)&pos, (WindowMsgData)&data);
	}
	return (data);
}
Int GadgetListBoxGetBottomVisibleEntry( GameWindow *window )
{
	if (!window)
		return 0;
	ListboxData *listData = (ListboxData *)window->winGetUserData();
	if (!listData)
		return 0;
	return getListboxBottomEntry(listData);
}
bool GadgetListBoxIsFull(GameWindow *window)
{
	if (!window)
		return FALSE;
	ListboxData *listData = (ListboxData *)window->winGetUserData();
	if (!listData)
		return FALSE;
	Int entry = getListboxBottomEntry(listData);
	if((*(ListEntryRow **)((char *)listData + 0x18))[entry].listHeight >=
	   *(Short *)((char *)listData + 0x44) + *(Short *)((char *)listData + 0x3C) - 5)
		return TRUE;
	else
		return FALSE;
}
void GadgetListBoxSetBottomVisibleEntry( GameWindow *window, Int newPos )
{
	if (!window)
		return;
	ListboxData *listData = (ListboxData *)window->winGetUserData();
	if (!listData)
		return;
	int prevPos = GadgetListBoxGetBottomVisibleEntry( window );
	adjustDisplay(window, newPos - prevPos + 1, true);
}
Int GadgetListBoxGetTopVisibleEntry( GameWindow *window )
{
	if (!window)
		return 0;
	ListboxData *listData = (ListboxData *)window->winGetUserData();
	if (!listData)
		return 0;
	return getListboxTopEntry(listData);
}
void GadgetListBoxSetTopVisibleEntry( GameWindow *window, Int newPos )
{
	if( !window || !window->winGetUserData() )
		return;
	Rva004B7DC0(window, newPos, 1);
}
void GadgetListBoxSetAudioFeedback( GameWindow *listbox, Bool enable )
{
	if (!listbox)
		return;
	ListboxData *listboxData = (ListboxData *)listbox->winGetUserData();
	if (!listboxData)
		return;
	listboxData->audioFeedback = enable;
}
Int GadgetListBoxGetNumColumns( GameWindow *listbox )
{
	if (!listbox)
		return 0;
	ListboxData *listboxData = (ListboxData *)listbox->winGetUserData();
	if (!listboxData)
		return 0;
	return listboxData->columns;
}
Int GadgetListBoxGetColumnWidth( GameWindow *listbox, Int column )
{
	if (!listbox)
		return 0;
	ListboxData *listboxData = (ListboxData *)listbox->winGetUserData();
	if (!listboxData)
		return 0;
	if (listboxData->columns <= column || column < 0)
		return 0;
	return (*(Int **)((char *)listboxData + 0x14))[column];
}
