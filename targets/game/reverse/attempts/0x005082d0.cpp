// ?populateQMSideComboBox@BfmeAptScreenQuickMatchMenu@@QAEXHPBVLadderInfo@@@Z
// partial score=0.99 date=2026-09-28
// ?populateQMSideComboBox@BfmeAptScreenQuickMatchMenu@@QAEXHPBVLadderInfo@@@Z
// partial score=0.991(shape) date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ob1 /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x005082D0, 726 bytes (ret 8). ZH twin: WOLQuickMatchMenu.cpp
// populateQMSideComboBox, ported onto the BFME APT menu class (callers 0x005091F0
// init gadgets, 0x0050A470 system and 0x00508C80 populateLadderList all pass the
// menu in ECX); comboBoxSide is the window at +0x254.  BFME replaced ZH's
// starting-building and locked-general filters with the byte at PlayerTemplate+0xBD.
// Layout and header setup follow the matched neighbour
// WOLQuickMatchMenuPopulateMapSelectListbox.cpp (BFME ascii_string.h, STLport,
// _STLP_USE_STATIC_LIB).  Levers found: /Ob1 (retail keeps STL helpers out of
// line); TU-local inline StringBase<char>::str(); GameTextInterface fetch
// overloads declared const char* first (MSVC reverses overloaded virtuals:
// fetch(AsciiString)=+0x24, fetch(const char*)=+0x28); PlayerTemplateStore's
// vector at +8; std::find inlined over an out-of-line list<AsciiString> __find
// (0x00506180 via ILT 0x0004093A, a real AsciiString compare loop).
// probe: 734 vs 726 bytes, shape 0.991, 359 differing bytes.  Residue:
//  (1) frame 0x30 vs 0x2c: our bidirectional_iterator_tag temporary gets its own
//      byte slot where retail passes the address of the li parameter slot;
//  (2) `seenSides.find(side) != seenSides.end()` evaluates end() first into a
//      spilled temp (STLport's non-member operator!=), retail reads the header
//      after _M_find.  Comparing ._M_node fixes (2) but swaps the ebx/ebp roles
//      until (1) is fixed.
// Landing needs pins for this TU's __find<list<AsciiString>::const_iterator>
// (0x00506180), set<AsciiString> _M_find (0x0038C0E0) and _M_erase (0x00076A90),
// whose ledger names are other instantiations' spellings.

#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include <list>
#include <set>
#include <vector>
#include <algorithm>

template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

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

class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return m_side; }

	char m_unmodelled[0x8];
	AsciiString m_side;
	char m_unmodelled0c[0xbd - 0xc];
	Bool m_bfmeBD;
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
	void populateQMSideComboBox(Int favSide, const LadderInfo *li = 0);

private:
	char m_unmodelled[0x254];
	GameWindow *m_comboBoxSide;
};

void BfmeAptScreenQuickMatchMenu::populateQMSideComboBox(Int favSide, const LadderInfo *li)
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

		if (!fac->m_bfmeBD)
			continue;

		AsciiString side;
		side.format("SIDE:%s", fac->getSide().str());
		if (seenSides.find(side) != seenSides.end())
			continue;

		if (li)
		{
			if (std::find(li->validFactions.begin(), li->validFactions.end(), fac->getSide()) == li->validFactions.end())
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
	if (li && li->randomFactions)
		m_comboBoxSide->winEnable(false);
	else
		m_comboBoxSide->winEnable(true);
}
