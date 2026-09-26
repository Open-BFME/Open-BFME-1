// cl: /DNDEBUG /MD /EHsc
//
// QuickMatch color population.  The ZH source routine is a static helper, but
// BFME's APT port calls this extracted body with the surrounding
// BfmeAptScreenQuickMatchMenu in ECX and the preferences object on the stack.
// The +0x25c color gadget is the member established by the menu constructor
// and its init-gadgets caller; this TU keeps that ABI view local.

typedef unsigned short WideChar;
typedef bool Bool;
typedef int Int;
typedef int Color;

template <typename T> struct Rva006239C0StringData
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
	Rva006239C0StringData<T> *m_data;

public:
	void set(const StringBase<T> &other);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
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

class GameWindow {};

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
	virtual void slot24() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

class MultiplayerColorDefinition
{
public:
	Color getColor() const
	{
		return *(const Color *)((const char *)this + 0x10);
	}

	AsciiString getTooltipName() const;
};

class MultiplayerColorList
{
public:
	Int size() const { return *(const Int *)this; }

private:
	Int m_size;
	Int m_tree;
};

class MultiplayerSettings
{
public:
	Int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = m_colorList.size();
		return m_numColors;
	}

	MultiplayerColorDefinition *getColor(Int which);

private:
	char m_unmodelled[0x34];
	MultiplayerColorList m_colorList;
	Int m_numColors;
};

class QuickMatchPreferences
{
public:
	Int getColor();
};

class __declspec(novtable) BfmeAptScreenQuickMatchMenu
{
public:
	virtual void slot0();
	void populateQMColorComboBox(QuickMatchPreferences &pref);

private:
	char m_unmodelled[0x258];
	GameWindow *m_color;
};

extern GameTextInterface *TheGameText;
extern MultiplayerSettings *TheMultiplayerSettings;

extern void GadgetComboBoxReset(GameWindow *comboBox);
extern Int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text,
	Color color);
extern void GadgetComboBoxSetItemData(GameWindow *comboBox, Int item,
	void *data);
extern void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int item,
	Bool dontHide = false);

// AptScreenFactories.cpp still declares the helper in the source-authentic
// static form.  Keep that call spelling routed to this member body without
// putting a second implementation in the large WOL TU.
#pragma comment(linker, "/alternatename:?populateQMColorComboBox@@YAXAAVQuickMatchPreferences@@@Z=?populateQMColorComboBox@BfmeAptScreenQuickMatchMenu@@QAEXAAVQuickMatchPreferences@@@Z")

// ?populateQMColorComboBox@BfmeAptScreenQuickMatchMenu@@QAEXAAVQuickMatchPreferences@@@Z present-unmatched
void BfmeAptScreenQuickMatchMenu::populateQMColorComboBox(
	QuickMatchPreferences &pref)
{
	Int numColors = TheMultiplayerSettings->getNumColors();
	UnicodeString colorName;

	GadgetComboBoxReset(m_color);

	MultiplayerColorDefinition *def =
		TheMultiplayerSettings->getColor(-1);
	Int newIndex = GadgetComboBoxAddEntry(m_color,
		TheGameText->fetch("GUI:???"), def->getColor());
	GadgetComboBoxSetItemData(m_color, newIndex, (void *)-1);

	for (Int c = 0; c < numColors; ++c)
	{
		def = TheMultiplayerSettings->getColor(c);
		if (!def)
			continue;

		colorName = TheGameText->fetch(def->getTooltipName().str());
		newIndex = GadgetComboBoxAddEntry(m_color, colorName,
			def->getColor());
		GadgetComboBoxSetItemData(m_color, newIndex, (void *)c);
	}

	GadgetComboBoxSetSelectedPos(m_color, pref.getColor());
}
