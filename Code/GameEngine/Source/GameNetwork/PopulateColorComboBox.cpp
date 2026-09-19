// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME's lobby team list is the Zero Hour PopulateTeamComboBox shape with a
// fixed four-team loop and the BFME init guard.

typedef unsigned short WideChar;
typedef bool Bool;
typedef int Int;
typedef int Color;

#include <vector>

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
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void format(AsciiString format, ...);

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString() {}

	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}
};

class GameWindow;
class GameInfo;

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
	Int size() const
	{
		return m_size;
	}

	Int m_size;
	char m_unmodelled[4];
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

class GameSlot
{
public:
	Int getColor() const
	{
		return *(const Int *)((const char *)this + 0x0C);
	}
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slot);
};

extern GameTextInterface *TheGameText;
extern MultiplayerSettings *TheMultiplayerSettings;
extern int g_Va012F49D4;

extern void GadgetComboBoxReset(GameWindow *comboBox);
extern Int GadgetComboBoxGetLength(GameWindow *comboBox);
extern Int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text,
	Color color);
extern void GadgetComboBoxSetItemData(GameWindow *comboBox, Int item,
	void *data);
extern void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int item,
	Bool dontHide);

// ?PopulateColorComboBox@@YAXHQAPAVGameWindow@@PAVGameInfo@@_N@Z
void PopulateColorComboBox(Int comboBox, GameWindow *comboArray[],
	GameInfo *myGame, Bool isObserver)
{
	if (g_Va012F49D4)
		return;

	Int i;
	Int numColors = TheMultiplayerSettings->getNumColors();
	UnicodeString colorName;
	_STL::vector<bool> availableColors(numColors, true);
	Int newIndex;

	for (i = 0; i < 8; i++)
	{
		GameSlot *slot = myGame->getSlot(i);
		if (slot && (i != comboBox) && (slot->getColor() >= 0)
			&& (slot->getColor() < numColors))
		{
			availableColors[slot->getColor()] = false;
		}
	}

	Bool wasObserver = (GadgetComboBoxGetLength(comboArray[comboBox]) == 1);
	GadgetComboBoxReset(comboArray[comboBox]);

	MultiplayerColorDefinition *def =
		TheMultiplayerSettings->getColor(-1);
	newIndex = GadgetComboBoxAddEntry(comboArray[comboBox],
		isObserver ? TheGameText->fetch("GUI:None")
		           : TheGameText->fetch("GUI:???"),
		def->getColor());
	GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)-1);

	if (isObserver)
	{
		GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0, false);
		return;
	}

	for (Int c = 0; c < numColors; ++c)
	{
		def = TheMultiplayerSettings->getColor(c);
		if (!def || availableColors[c] == false)
			continue;

		colorName = TheGameText->fetch(def->getTooltipName().str());
		newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], colorName,
			def->getColor());
		GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)c);
	}

	if (wasObserver)
		GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0, false);
}

// ?PopulateTeamComboBox@@YAXHQAPAVGameWindow@@PAVGameInfo@@_N@Z
void PopulateTeamComboBox(Int comboBox, GameWindow *comboArray[],
	GameInfo *myGame, Bool isObserver)
{
	if (g_Va012F49D4)
		return;

	MultiplayerColorDefinition *def;
	UnicodeString teamName;
	Int newIndex;

	GadgetComboBoxReset(comboArray[comboBox]);

	def = TheMultiplayerSettings->getColor(-1);
	newIndex = GadgetComboBoxAddEntry(comboArray[comboBox],
		TheGameText->fetch("Team:0"), def->getColor());
	GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)-1);

	if (isObserver)
	{
		GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0, false);
		return;
	}

	for (Int c = 0; c < 4; ++c)
	{
		AsciiString teamStr;
		teamStr.format(AsciiString("Team:%d"), c + 1);
		teamName = TheGameText->fetch(teamStr.str());
		newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], teamName,
			def->getColor());
		GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)c);
	}

	GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0, false);
}
