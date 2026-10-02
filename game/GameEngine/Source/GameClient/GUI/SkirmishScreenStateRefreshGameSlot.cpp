// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

// The wide string this body handles by value, as in the matched
// SkirmishScreenStateRefreshPlayerTypeCombo.cpp: the default constructor and
// the destructor inline (the latter a direct call to the private
// releaseBuffer, 0x008881D0); the copy constructor (0x00888400) and compare
// (0x0005FFA0) stay out of line.
template <>
class StringBase<unsigned short>
{
	friend class UnicodeString;

public:
	int compare(const StringBase<unsigned short> &str) const;

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

enum
{
	WIN_STATUS_ENABLED = 0x00000008
};

class GameWindow
{
public:
	unsigned int winGetStatus(void);
	Int winEnable(Bool enable);
};

UnicodeString GadgetComboBoxGetText(GameWindow *comboBox);
void GadgetComboBoxSetText(GameWindow *comboBox, UnicodeString text);
Int GadgetComboBoxGetLength(GameWindow *comboBox);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, Int index);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontHide);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	Bool isHuman(void) const;
	Bool isAI(void) const;
	UnicodeString getName(void) const;

	Int getState(void) const { return m_state; }
	Bool isAccepted(void) const { return m_isAccepted; }
	Bool hasMap(void) const { return m_hasMap; }
	Int getColor(void) const { return *(const Int *)((const char *)this + 0x0C); }
	Int getPlayerTemplate(void) const { return m_playerTemplate; }
	Int getTeamNumber(void) const { return *(const Int *)((const char *)this + 0x18); }

private:
	unsigned char m_unmodelled0[4];
	Int m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	unsigned char m_unmodelled0A[2];
	Int m_color;
	Int m_startPos;
	Int m_playerTemplate;
	Int m_teamNumber;
};

class GameInfo
{
public:
	virtual void slot0(void) = 0;
	virtual void slot1(void) = 0;
	virtual void slot2(void) = 0;
	virtual void slot3(void) = 0;
	virtual Bool amIHost(void) const = 0;
	virtual Int getLocalSlotNum(void) const = 0;

	GameSlot *getSlot(Int slotNum);
};

Bool WouldMapTransfer(GameInfo *game);

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

// Image combo-box adapter methods, each matched under an address-derived
// owner (see SkirmishScreenStateRebuildColorCombo.cpp). The adapter is the
// state's colour-combo slot itself: one GameWindow pointer.
class BfmeThing925D { public: void bfmeGo925D(void *value); };
class BfmeThing925E { public: Int bfmeGo925E(); };
class BfmeThingCCH { public: Int bfmeGoCCH(void *value); };
class BfmeC1040 { public: Int bfmeGo1040C(); };
class Rva004B5C90 { public: void invoke(Bool value); };

struct Rva00528B60Combo
{
	GameWindow *m_window;

	Int getLength() { return ((BfmeThing925E *)this)->bfmeGo925E(); }
	Int getItemData(Int item) { return ((BfmeThingCCH *)this)->bfmeGoCCH((void *)item); }
	Int getSelected() { return ((BfmeC1040 *)this)->bfmeGo1040C(); }
	void invoke(Bool value) { ((Rva004B5C90 *)this)->invoke(value); }
	void setSelected(Int item) { ((BfmeThing925D *)this)->bfmeGo925D((void *)item); }
};

// Sibling SkirmishScreenState methods matched under address-derived owners.
// Retail's ledger owner spells the two-word helper as run(int, int).
class Rva00526660Body { public: void run(int enable, int slotIndex); };
class Rva00525080SkirmishScreenState { public: void rva00525080(int index, int state); };
class Rva00523460Owner { public: void rva00523460(int index, int data); };

// Layout as in the matched SkirmishScreenStateRefreshPlayerTypeCombo.cpp and
// SkirmishScreenStateRebuildColorCombo.cpp.
class SkirmishScreenState
{
public:
	virtual void slot00() = 0;

	void refreshGameSlot(Int index);
	Bool rebuildColorCombo005284F0(Int index);

private:
	SkirmishScreenOwner *m_owner;
	GameInfo *m_game;
	GameInfo *m_secondaryGame;
	unsigned char m_unmodelled10[0x58];
	GameWindow *m_playerTypeCombos[8];
	Rva00528B60Combo m_colorCombos[8];
	GameWindow *m_teamCombos[8];
};

// Retail 0x00528B60 (683 B), reached through ILT 0x00018C1E from the matched
// SkirmishScreenState::refreshGameSlots (0x005291F0), which names it
// refreshGameSlot and calls it once per slot. The Zero Hour twin is the loop
// body of GUIUtil.cpp UpdateSlotList: enable the slot's accept controls,
// copy a human's name into the player combo (or select an AI/open state),
// disable the player combo for a non-host, rebuild and select the colour,
// select the team, then select the player template.
// ?refreshGameSlot@SkirmishScreenState@@QAEXH@Z
void SkirmishScreenState::refreshGameSlot(Int index)
{
	if (m_game && !m_owner->contains(m_game))
		m_game = 0;

	if (m_secondaryGame && !m_owner->contains(m_secondaryGame))
		m_secondaryGame = 0;

	if (!m_game)
		return;

	GameSlot *slot = m_game->getSlot(index);
	if (m_game->amIHost() && slot && slot->isAI())
	{
		((Rva00526660Body *)this)->run(true, index);
	}
	else if (slot && m_game->getLocalSlotNum() == index)
	{
		if (slot->isAccepted() && !m_game->amIHost())
		{
			((Rva00526660Body *)this)->run(false, -1);
		}
		else if (slot->hasMap())
		{
			((Rva00526660Body *)this)->run(true, -1);
		}
		else
		{
			Bool willTransfer = WouldMapTransfer(m_game);
			((Rva00526660Body *)this)->run(*(int *)&willTransfer, -1);
		}
	}
	else if (m_game->amIHost())
	{
		((Rva00526660Body *)this)->run(false, index);
	}

	if (slot)
	{
		if (slot->isHuman())
		{
			UnicodeString newName = slot->getName();
			UnicodeString oldName = GadgetComboBoxGetText(m_playerTypeCombos[index]);
			if (m_playerTypeCombos[index] && newName.compare(oldName))
				GadgetComboBoxSetText(m_playerTypeCombos[index], newName);
		}
		else
		{
			((Rva00525080SkirmishScreenState *)this)->rva00525080(index, slot->getState());
		}
	}

	if (!m_game->amIHost())
	{
		if (m_playerTypeCombos[index])
			m_playerTypeCombos[index]->winEnable(false);
	}

	Bool rebuilt = false;
	if (m_colorCombos[index].m_window
		&& (m_colorCombos[index].m_window->winGetStatus() & WIN_STATUS_ENABLED))
		rebuilt = rebuildColorCombo005284F0(index);

	Rva00528B60Combo &combo = m_colorCombos[index];
	if (combo.m_window)
	{
		Int max = combo.getLength();
		Int idx;
		for (idx = 0; idx < max; ++idx)
		{
			Int color = combo.getItemData(idx);
			if (color == slot->getColor())
				break;
		}
		if (idx == max)
			idx = 0;

		Int selected = combo.getSelected();
		if (rebuilt || selected != idx)
		{
			combo.invoke(true);
			combo.setSelected(idx);
		}
	}

	if (m_teamCombos[index])
	{
		Int max = GadgetComboBoxGetLength(m_teamCombos[index]);
		for (Int idx = 0; idx < max; ++idx)
		{
			Int team = (Int)GadgetComboBoxGetItemData(m_teamCombos[index], idx);
			if (team == slot->getTeamNumber())
			{
				GadgetComboBoxSetSelectedPos(m_teamCombos[index], idx, true);
				break;
			}
		}
	}

	((Rva00523460Owner *)this)->rva00523460(index, slot->getPlayerTemplate());
}
