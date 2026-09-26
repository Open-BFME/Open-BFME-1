// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

struct UnicodeStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
};

#include "string_base.h"

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const unsigned short *text)
		: StringBase<unsigned short>(text)
	{
	}

	UnicodeString(const UnicodeString &source)
		: StringBase<unsigned short>(source)
	{
	}

	~UnicodeString()
	{
	}

	bool isEmpty() const
	{
		return m_data == 0 || ((UnicodeStringData *)m_data)->m_length == 0;
	}

	UnicodeString &operator=(const UnicodeString &source)
	{
		set(*(const StringBase<unsigned short> *)&source);
		return *this;
	}
};

class GameWindow
{
public:
	void *winGetUserData();
};

struct _ListboxData
{
	short listLength;
	short columns;
	unsigned char m_unmodelled_04[9];
	Bool scrollIfAtEnd;
	unsigned char m_unmodelled_0e[0x1e];
	short endPos;
};

typedef struct _ListboxData ListboxData;

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

class GameWindowManager
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_2C() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void _bfme_pad_38() = 0;
	virtual void _bfme_pad_3C() = 0;
	virtual void _bfme_pad_40() = 0;
	virtual void _bfme_pad_44() = 0;
	virtual void _bfme_pad_48() = 0;
	virtual void _bfme_pad_4C() = 0;
	virtual void _bfme_pad_50() = 0;
	virtual void _bfme_pad_54() = 0;
	virtual void _bfme_pad_58() = 0;
	virtual void _bfme_pad_5C() = 0;
	virtual void _bfme_pad_60() = 0;
	virtual void _bfme_pad_64() = 0;
	virtual void _bfme_pad_68() = 0;
	virtual void _bfme_pad_6C() = 0;
	virtual void _bfme_pad_70() = 0;
	virtual void _bfme_pad_74() = 0;
	virtual void _bfme_pad_78() = 0;
	virtual void _bfme_pad_7C() = 0;
	virtual void _bfme_pad_80() = 0;
	virtual void _bfme_pad_84() = 0;
	virtual void _bfme_pad_88() = 0;
	virtual void _bfme_pad_8C() = 0;
	virtual void _bfme_pad_90() = 0;
	virtual void _bfme_pad_94() = 0;
	virtual void _bfme_pad_98() = 0;
	virtual void _bfme_pad_9C() = 0;
	virtual void _bfme_pad_A0() = 0;
	virtual void _bfme_pad_A4() = 0;
	virtual void _bfme_pad_A8() = 0;
	virtual void _bfme_pad_AC() = 0;
	virtual void _bfme_pad_B0() = 0;
	virtual void _bfme_pad_B4() = 0;
	virtual void _bfme_pad_B8() = 0;
	virtual void _bfme_pad_BC() = 0;
	virtual void _bfme_pad_C0() = 0;
	virtual void _bfme_pad_C4() = 0;
	virtual void _bfme_pad_C8() = 0;
	virtual void _bfme_pad_CC() = 0;
	virtual void _bfme_pad_D0() = 0;
	virtual Int winSendSystemMsg(GameWindow *window, UnsignedInt message,
		WindowMsgData data1, WindowMsgData data2) = 0;
};

extern GameWindowManager *TheWindowManager;

int __fastcall getListboxBottomEntry(ListboxData *listData);
bool GadgetListBoxIsFull(GameWindow *window);
void GadgetListBoxSetBottomVisibleEntry(GameWindow *window, Int newPos);

// The vtable slot, caller data layout, and retail address identify this as
// the BFME listbox text insertion body.
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Int color, Int row, Int column, Bool overwrite)
{
	if (!listbox)
		return -1;

	if (text.isEmpty())
		text = UnicodeString((const unsigned short *)0x01084c34);

	Int index;
	AddMessageStruct addInfo;
	addInfo.row = row;
	addInfo.column = column;
	addInfo.type = 1;
	addInfo.data = &text;
	addInfo.overwrite = overwrite;
	addInfo.height = -1;
	addInfo.width = -1;

	ListboxData *listData = (ListboxData *)listbox->winGetUserData();
	Bool wasFull = listData->listLength <= listData->endPos;
	Int newEntryOffset = wasFull ? 0 : 1;

	ListboxData *bottomData = (ListboxData *)listbox->winGetUserData();
	Int oldBottomIndex;
	if (bottomData == 0)
		oldBottomIndex = 0;
	else
		oldBottomIndex = getListboxBottomEntry(bottomData);

	index = TheWindowManager->winSendSystemMsg(listbox, 0x4011,
		(WindowMsgData)&addInfo, (WindowMsgData)color);

	if (listData->scrollIfAtEnd && index - oldBottomIndex == newEntryOffset &&
		GadgetListBoxIsFull(listbox))
		GadgetListBoxSetBottomVisibleEntry(listbox, index);

	return index;
}
