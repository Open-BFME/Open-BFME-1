// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/stringbaseunicode /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
//
// The retail 0x004C90A0 body is the keyboard category-combo population
// helper.  The source-level owner is the standalone populateCategoryBox
// function from the upstream KeyboardOptionsMenu unit; this TU keeps the
// already-published initializer separate so its existing exact body remains
// immutable.

typedef unsigned short WideChar;
typedef bool Bool;
typedef int Int;
typedef int Color;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	StringInlineData<T> *m_data;

public:
	void set(const StringBase<T> &other);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void format(AsciiString format, ...);
};

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

#define comboBoxCategoryList (*(GameWindow **)0x012F3AC0)

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
