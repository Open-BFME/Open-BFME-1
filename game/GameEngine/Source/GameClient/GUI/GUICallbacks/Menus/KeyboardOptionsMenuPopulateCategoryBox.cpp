// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
//
// The retail 0x004C90A0 body is the keyboard category-combo population
// helper.  The source-level owner is the standalone populateCategoryBox
// function from the upstream KeyboardOptionsMenu unit; this TU keeps the
// already-published initializer separate so its existing exact body remains
// immutable.

typedef unsigned short WideChar;
#include "../../../../../Include/Common/ScalarTypes.h"

typedef int Color;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

#include "../../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class GameWindow;

extern void GadgetComboBoxReset(GameWindow *comboBox);
extern Int GadgetComboBoxAddEntry(
	GameWindow *comboBox, UnicodeString text, Color color);
extern void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selected,
	Bool dontHide);

struct CategoryNameRecord
{
	const char *name;
	Int value;
};

static const CategoryNameRecord CategoryListName[] =
{
	{"CONTROL", 0},
	{"INFORMATION", 1},
	{"INTERFACE", 2},
	{"SELECTION", 3},
	{"TAUNT", 4},
	{"TEAM", 5},
	{"MISC", 6},
	{"DEBUG", 7}
};

extern GameWindow *g_012F3AC0;
#define comboBoxCategoryList g_012F3AC0

void populateCategoryBox()
{
	Int i;
	Int index;
	Color color = -1;
	AsciiString temp;
	UnicodeString str;

	GadgetComboBoxReset(comboBoxCategoryList);
	for (i = 0; i < 8; ++i)
	{
		temp.format("GUI:%s", CategoryListName[i]);
		str = TheGameText->fetch(temp);
		index = GadgetComboBoxAddEntry(
			comboBoxCategoryList, str, color);
	}

	GadgetComboBoxSetSelectedPos(comboBoxCategoryList, 0, false);
}
