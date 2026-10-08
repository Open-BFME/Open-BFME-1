// Three matched callers pass the menu receiver, an integer and LadderInfo* through
// ILT 0x00035701, whose jump is five bytes long. The matched menu constructor
// at 0x00505830 identifies the receiver as BfmeAptScreenQuickMatchMenu. The
// callers do not identify this method, so it keeps its RVA in the name.
// Retail returns with ret 8 at +0x2D3 and starts INT3 padding at +0x2D6,
// confirming 726 bytes. The body fills the Quick Match side combo box from
// player templates and filters entries through LadderInfo.
// Retail passes the incoming li slot as the empty iterator tag to STLport's
// __find. STLport's __find does not read that tag. Rva005082D0ListArg views the
// same stack word as a pointer or tag.

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ob1 /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "string_base.h"
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
#include "ascii_string.h"
#include "unicode_string.h"
#include <list>
#include <set>
#include <vector>
#include <algorithm>



typedef int Int;
typedef int Color;
typedef bool Bool;

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}

inline UnicodeString::UnicodeString(const UnicodeString &that)
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
		*(const StringBase<wchar_t> *)&that);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<wchar_t> *)this)->releaseBuffer();
}

class GameWindow
{
public:
	Int winEnable(Bool enable);
};

class LadderInfo
{
public:
	char m_unmodelled[0x18];
	Bool randomMaps;
	Bool randomFactions;
	char m_unmodelled1a[0x2];
	std::list<AsciiString> validMaps;
	std::list<AsciiString> validFactions;
};

union Rva005082D0ListArg
{
	const LadderInfo *info;
	_STL::bidirectional_iterator_tag tag;
};

class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return m_side; }

	char m_unmodelled[0x8];
	AsciiString m_side;
	char m_unmodelled0c[0xbd - 0xc];
	Bool m_playableSide;
	char m_unmodelledbe[0x124 - 0xbe];
};

class PlayerTemplateStore
{
public:
	Int getPlayerTemplateCount() const { return m_playerTemplates.size(); }
	const PlayerTemplate *getNthPlayerTemplate(Int i) const;

	char m_unmodelled[0x8];
	std::vector<PlayerTemplate> m_playerTemplates;
};

class MultiplayerColorDefinition
{
public:
	Color getColor() const { return m_color; }

	char m_unmodelled[0x10];
	Color m_color;
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(Int which);
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
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

// Retail inlines std::find here but calls the list<AsciiString> __find body
// (0x00506180, through ILT 0x0004093A) out of line.
typedef std::list<AsciiString>::const_iterator FactionIterator;
namespace _STL {
template <> FactionIterator __find(FactionIterator first, FactionIterator last,
	const AsciiString &val, const input_iterator_tag &);
template <> inline FactionIterator find(FactionIterator first, FactionIterator last,
	const AsciiString &val)
{
	return __find(first, last, val, bidirectional_iterator_tag());
}
inline FactionIterator find(FactionIterator first, FactionIterator last,
	const AsciiString &val, const bidirectional_iterator_tag &tag)
{
	return __find(first, last, val, tag);
}
}

extern PlayerTemplateStore *ThePlayerTemplateStore;
extern MultiplayerSettings *TheMultiplayerSettings;
extern GameTextInterface *TheGameText;

enum { PLAYERTEMPLATE_RANDOM = -1 };

void GadgetComboBoxReset(GameWindow *comboBox);
Int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, Color color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, Int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontsend = false);

class BfmeAptScreenQuickMatchMenu
{
public:
	void rva005082D0(Int favSide, Rva005082D0ListArg li);

private:
	char m_unmodelled[0x254];
	GameWindow *m_comboBoxSide;
};

void BfmeAptScreenQuickMatchMenu::rva005082D0(Int favSide, Rva005082D0ListArg li)
{
	Int numPlayerTemplates = ThePlayerTemplateStore->getPlayerTemplateCount();
	UnicodeString playerTemplateName;

	GadgetComboBoxReset(m_comboBoxSide);

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(PLAYERTEMPLATE_RANDOM);
	Int newIndex = GadgetComboBoxAddEntry(m_comboBoxSide, TheGameText->fetch("GUI:Random"), def->getColor());
	GadgetComboBoxSetItemData(m_comboBoxSide, newIndex, (void *)PLAYERTEMPLATE_RANDOM);

	std::set<AsciiString> seenSides;

	Int entryToSelect = 0;

	for (Int c = 0; c < numPlayerTemplates; ++c)
	{
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(c);
		if (!fac)
			continue;

		if (!fac->m_playableSide)
			continue;

		AsciiString side;
		side.format("SIDE:%s", fac->getSide().str());
		std::set<AsciiString>::iterator foundSide = seenSides.find(side);
		if (foundSide != seenSides.end())
			continue;

		if (li.info)
		{
			if (_STL::find(li.info->validFactions.begin(), li.info->validFactions.end(), fac->getSide(), li.tag) == li.info->validFactions.end())
				continue;
		}

		seenSides.insert(side);

		newIndex = GadgetComboBoxAddEntry(m_comboBoxSide, TheGameText->fetch(side), def->getColor());
		GadgetComboBoxSetItemData(m_comboBoxSide, newIndex, (void *)c);

		if (c == favSide)
			entryToSelect = newIndex;
	}
	seenSides.clear();

	GadgetComboBoxSetSelectedPos(m_comboBoxSide, entryToSelect);
	if (li.info && li.info->randomFactions)
		m_comboBoxSide->winEnable(false);
	else
		m_comboBoxSide->winEnable(true);
}
