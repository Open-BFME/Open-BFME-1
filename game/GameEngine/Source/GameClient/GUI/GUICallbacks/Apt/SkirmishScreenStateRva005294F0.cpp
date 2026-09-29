// ?rva005294F0@SkirmishScreenState@@QAEXH@Z
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// SkirmishScreenState::rva005294F0(Int), retail 0x005294F0, 1214 bytes, RET 4.
// BFME form of Zero Hour's PopulatePlayerTemplateComboBox (GUIUtil.cpp) for the
// slot's player-template combo at +0xC8. Callers (refreshAllPlayerControls,
// handlePlayerSelection, apply via ILT 0x0002D38A) declare it refreshPlayerTeamControl,
// which this body contradicts (it fills SIDE:%s faction entries), so the name keeps
// the address (identity_evidence/005294f0-player-template-combo.md).
// The side label is tested with `if (!exists) continue;` as in the matched
// PopulatePlayerTemplateComboBox (0x006247B0): the nested `if (exists) {}` form
// compiles to the same code but weights def above sideName and the count, which
// rotated those three stack slots. The set's header node comes from the
// out-of-line node allocator (0x0082E540), so the TU keeps STLport's default
// allocator rather than _STLP_USE_NEWALLOC, which inlines operator new.
#include <set>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef int Color;

template <>
class StringBase<unsigned short>
{
	friend class UnicodeString;
private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<unsigned short> &src);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	void *m_data;
};
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &that) : StringBase<unsigned short>(that) {}
	~UnicodeString() {}
};

class GameWindow;
void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, Int *selectedIndex);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, Int index);
void GadgetComboBoxReset(GameWindow *comboBox);
Int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, Color color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, Int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontHide);
void GadgetComboBoxSetMaxDisplay(GameWindow *comboBox, Int maxDisplay);

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class MultiplayerColorDefinition
{
public:
	Color getColor() const { return m_color; }
	unsigned char m_unmodelled000[0x10];
	Color m_color;
};
class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(Int which);
};
extern MultiplayerSettings *TheMultiplayerSettings;

enum { PLAYERTEMPLATE_RANDOM = -1, PLAYERTEMPLATE_OBSERVER = -2 };

class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return m_side; }
	Bool isObserver() const { return m_observer; }
	Bool isPlayableSide() const { return m_playableSide; }
private:
	unsigned char m_beforeSide[0x08];
	AsciiString m_side;
	unsigned char m_beforeObserver[0xbc - 0x0c];
	Bool m_observer;
	Bool m_playableSide;
	unsigned char m_afterPlayableSide[0x124 - 0xbe];
};
class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(Int index) const;
	Int getPlayerTemplateCount() const { return (Int)(m_end - m_begin); }
private:
	unsigned char m_beforeTemplates[0x08];
	PlayerTemplate *m_begin;
	PlayerTemplate *m_end;
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

class GameSlot
{
public:
	Bool isAI() const;
};
class GameInfo
{
public:
	GameSlot *getSlot(Int index);
};

// The start-position record retail passes on to the map-key helper at 0x005293E0.
class Gen005293E0Object
{
public:
	unsigned char m_unmodelled000[0x0c];
	Int m_ready;
};
Bool bfmeGen005293E0(Gen005293E0Object *startPos, void *side);
inline Bool startPositionHasSide(Gen005293E0Object *startPos, const AsciiString &side)
{
	return bfmeGen005293E0(startPos, (void *)&side);
}
struct StartPositionInfo;
class MpGameSetup
{
public:
	const StartPositionInfo *bfmeGetStartPositionInfo(Int index);
};

class SkirmishScreenOwner
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual Bool contains(GameInfo *game) = 0;
};

class SkirmishScreenState
{
public:
	void rva005294F0(Int index);
private:
	unsigned char m_vtable[4];
	SkirmishScreenOwner *m_owner;
	GameInfo *m_game;
	GameInfo *m_secondaryGame;
	unsigned char m_flags10[0xc8 - 0x10];
	GameWindow *m_playerTemplateCombos[8];		// +0xC8
	unsigned char m_unmodelledE8[0x10c - 0xe8];
	unsigned char m_member10c[0x120 - 0x10c];
	unsigned int m_flags120;
	Bool m_rva124;
};

void SkirmishScreenState::rva005294F0(Int index)
{
	Int newIndex;
	if (m_game && !m_owner->contains(m_game))
		m_game = 0;
	if (m_secondaryGame && !m_owner->contains(m_secondaryGame))
		m_secondaryGame = 0;
	if (!m_game)
		return;
	GameSlot *slot = m_game->getSlot(index);
	if (!slot)
		return;

	Bool allowObservers = !slot->isAI() && !(m_flags120 & 4);
	Gen005293E0Object *startPos = (Gen005293E0Object *)((MpGameSetup *)this)->bfmeGetStartPositionInfo(index);
	Int selectedData = -1;
	GadgetComboBoxGetSelectedPos(m_playerTemplateCombos[index], &newIndex);
	if (newIndex >= 0)
		selectedData = (Int)GadgetComboBoxGetItemData(m_playerTemplateCombos[index], newIndex);

	Int numPlayerTemplates = ThePlayerTemplateStore->getPlayerTemplateCount();
	UnicodeString playerTemplateName;
	GadgetComboBoxReset(m_playerTemplateCombos[index]);

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(PLAYERTEMPLATE_RANDOM);
	if ((!m_rva124 && (!startPos || startPos->m_ready != 1)) || (m_rva124 && startPos && startPos->m_ready != 1))
	{
		newIndex = GadgetComboBoxAddEntry(m_playerTemplateCombos[index], TheGameText->fetch("GUI:Random"), def->getColor());
		GadgetComboBoxSetItemData(m_playerTemplateCombos[index], newIndex, (void *)PLAYERTEMPLATE_RANDOM);
	}

	Int selectPos = 0;
	std::set<AsciiString> seenSides;
	if (!m_rva124 || startPos)
	{
		for (Int c = 0; c < numPlayerTemplates; ++c)
		{
			const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(c);
			if (!fac || !fac->isPlayableSide() || fac->isObserver())
				continue;

			AsciiString side;
			side.format("SIDE:%s", fac->getSide().str());
			std::set<AsciiString>::iterator it = seenSides.find(side);
			if (it != seenSides.end())
				continue;
			seenSides.insert(side);

			if (!startPos || startPositionHasSide(startPos, AsciiString(fac->getSide().str())))
			{
				Bool exists;
				UnicodeString sideName = TheGameText->fetch(side, &exists);
				if (!exists)
					continue;
				newIndex = GadgetComboBoxAddEntry(m_playerTemplateCombos[index], TheGameText->fetch(side), def->getColor());
				GadgetComboBoxSetItemData(m_playerTemplateCombos[index], newIndex, (void *)c);
				if (selectedData == c)
					selectPos = newIndex;
			}
		}
	}
	seenSides.clear();

	if (!startPos && allowObservers)
	{
		def = TheMultiplayerSettings->getColor(PLAYERTEMPLATE_OBSERVER);
		newIndex = GadgetComboBoxAddEntry(m_playerTemplateCombos[index], TheGameText->fetch("GUI:Observer"), def->getColor());
		GadgetComboBoxSetItemData(m_playerTemplateCombos[index], newIndex, (void *)PLAYERTEMPLATE_OBSERVER);
		if (selectedData == PLAYERTEMPLATE_OBSERVER)
			selectPos = newIndex;
	}
	GadgetComboBoxSetSelectedPos(m_playerTemplateCombos[index], selectPos, false);
	GadgetComboBoxSetMaxDisplay(m_playerTemplateCombos[index], 10);
}
