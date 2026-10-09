// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef int Color;

// The wide string this body handles by value. Retail inlines the default
// constructor (a null handle) and the destructor (a direct call to the private
// releaseBuffer, 0x008881D0); the copy constructor (0x00888400), set
// (0x00888530) and compare (0x0010EB40) stay out of line. Only the members
// this body reaches are declared.
template <>
class StringBase<unsigned short>
{
	friend class UnicodeString;

public:
	int compare(const unsigned short *str) const;
	void set(const StringBase<unsigned short> &src);

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

class WinInstanceData;
class GameWindow;
typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, unsigned int);

class GameWindow
{
public:
	void *winGetUserData(void);
	Int winSetTooltipFunc(GameWinTooltipFunc tooltip);
};

// 0x004B3C30: the value-returning form of GadgetComboBoxGetSelectedPos
// (-1 for a null window, else GCM_GET_SELECTION 0x402B); matched under this
// address-era name, which takes the window as an int.
int bfmeGo1022L(int window);
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, Int index);
void GadgetComboBoxReset(GameWindow *comboBox);
Int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, Color color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, Int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontHide);
void GadgetComboBoxSetText(GameWindow *comboBox, UnicodeString text);

// ILT 0x0002D727 -> 0x00524B40, the player-combo list-box tooltip callback
// (it scans the global skirmish state's eight player-type combos at
// +0x68..+0x88 for the hovered list box). Its body is still a dump, so the
// pushed address is claimed by its thunk placeholder.
void j_0002d727(void);

// The combo box user data; +0x28 is the drop-down list box, the window the
// tooltip callback above compares against.
struct Rva00527220ComboData
{
	unsigned char m_unmodelled[0x28];
	GameWindow *m_listBox;
};

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
	virtual void slot09() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

// One 0x14-byte record of the inline array at MapMetaData +0x44, bounded by
// the count at +0x20 (Zero Hour keeps m_numPlayers there). The byte at +0x11
// is OR-ed over every record; its meaning is not proven. Retail reads it
// through an inline accessor: reading the field directly moves the count
// load into ECX behind a compare against the zero register (one byte long).
struct Rva00527220MapSlot
{
	unsigned char m_unmodelled[0x11];
	Bool m_flag11;
	unsigned char m_unmodelled12[2];

	Bool getFlag11() const { return m_flag11; }
};

class MapMetaData
{
public:
	unsigned char m_unmodelled[0x20];
	Int m_numPlayers;
	unsigned char m_unmodelled24[0x20];
	Rva00527220MapSlot m_slots[1];
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};
extern MapCache *TheMapCache;

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual bool amIHost( void ) const = 0;
	virtual int getLocalSlotNum( void ) const = 0;

	AsciiString getMap( void ) const;
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

// Layout as in the matched SkirmishScreenStateHandlePlayerSelection.cpp.
class SkirmishScreenState
{
public:
	void refreshPlayerTypeCombo00527220(int index);

private:
	unsigned char m_vtable[4];
	SkirmishScreenOwner *m_owner;
	GameInfo *m_game;
	GameInfo *m_secondaryGame;
	unsigned char m_unmodelled10[0x58];
	GameWindow *m_playerTypeCombos[8];
	unsigned char m_unmodelled88[0x98];
	unsigned int m_flags120;
};

// The white entry colour every combo population in this screen passes.
// Retail VA 0x012B76F4 is a mutable four-byte colour cell initialized
// to FFFFFFFF (opaque white); the original BFME identifier is unproven.
Color g_012B76F4 = -1;
#define Rva012B76F4Color g_012B76F4

// Retail 0x00527220 (911 B), reached through ILT 0x00029C35 from the matched
// SkirmishScreenState::refreshAllPlayerControls (once per slot) and ::apply.
// It rebuilds one slot's player-type combo: remember the current choice (its
// SlotState item data, or the typed text when nothing is selected), reset the
// combo, then add the local player's blank entry, or Open (unless flag 2 at
// +0x120 is set, which turns a remembered Open into Closed), Closed and, when
// the map allows it, the three AI levels, each tagged with its SlotState.
// The Zero Hour twin is the per-slot player combo population in
// SkirmishGameOptionsMenu.cpp; no evidence names this method, so it keeps
// its address.
// ?refreshPlayerTypeCombo00527220@SkirmishScreenState@@QAEXH@Z
void SkirmishScreenState::refreshPlayerTypeCombo00527220(int index)
{
	if (!m_playerTypeCombos[index])
		return;

	UnicodeString text;
	Int state = bfmeGo1022L((int)m_playerTypeCombos[index]);
	if (state == -1)
		text.set(GadgetComboBoxGetText(m_playerTypeCombos[index]));
	else
		state = (Int)GadgetComboBoxGetItemData(m_playerTypeCombos[index], state);

	GadgetComboBoxReset(m_playerTypeCombos[index]);
	Rva00527220ComboData *data =
		(Rva00527220ComboData *)m_playerTypeCombos[index]->winGetUserData();
	GameWindow *listBox = (data && data->m_listBox) ? data->m_listBox : 0;
	listBox->winSetTooltipFunc((GameWinTooltipFunc)j_0002d727);

	Bool allowAI = true;
	if (m_game && !m_owner->contains(m_game))
		m_game = 0;
	if (m_secondaryGame && !m_owner->contains(m_secondaryGame))
		m_secondaryGame = 0;

	if (m_game)
	{
		const MapMetaData *md = TheMapCache->findMap(m_game->getMap());
		if (md)
		{
			allowAI = false;
			for (Int i = 0; i < md->m_numPlayers; ++i)
				allowAI |= md->m_slots[i].getFlag11();
		}
	}

	Int selected = -1;
	if (m_game && m_game->getLocalSlotNum() == index)
	{
		UnicodeString name;
		Int entry = GadgetComboBoxAddEntry(m_playerTypeCombos[index], name, Rva012B76F4Color);
		GadgetComboBoxSetItemData(m_playerTypeCombos[index], entry, (void *)0);
	}
	else
	{
		Int entry;
		if (m_flags120 & 2)
		{
			if (state == SLOT_OPEN)
				state = SLOT_CLOSED;
		}
		else
		{
			entry = GadgetComboBoxAddEntry(m_playerTypeCombos[index],
				TheGameText->fetch("GUI:Open"), Rva012B76F4Color);
			GadgetComboBoxSetItemData(m_playerTypeCombos[index], entry, (void *)SLOT_OPEN);
			if (state == SLOT_OPEN)
				selected = entry;
		}

		entry = GadgetComboBoxAddEntry(m_playerTypeCombos[index],
			TheGameText->fetch("GUI:Closed"), Rva012B76F4Color);
		GadgetComboBoxSetItemData(m_playerTypeCombos[index], entry, (void *)SLOT_CLOSED);
		if (state == SLOT_CLOSED)
			selected = entry;

		if (allowAI)
		{
			entry = GadgetComboBoxAddEntry(m_playerTypeCombos[index],
				TheGameText->fetch("GUI:EasyAI"), Rva012B76F4Color);
			GadgetComboBoxSetItemData(m_playerTypeCombos[index], entry, (void *)SLOT_EASY_AI);
			if (state == SLOT_EASY_AI)
				selected = entry;

			entry = GadgetComboBoxAddEntry(m_playerTypeCombos[index],
				TheGameText->fetch("GUI:MediumAI"), Rva012B76F4Color);
			GadgetComboBoxSetItemData(m_playerTypeCombos[index], entry, (void *)SLOT_MED_AI);
			if (state == SLOT_MED_AI)
				selected = entry;

			entry = GadgetComboBoxAddEntry(m_playerTypeCombos[index],
				TheGameText->fetch("GUI:HardAI"), Rva012B76F4Color);
			GadgetComboBoxSetItemData(m_playerTypeCombos[index], entry, (void *)SLOT_BRUTAL_AI);
			if (state == SLOT_BRUTAL_AI)
				selected = entry;
		}
	}

	// Retail sets the text on both the "found" path and the non-empty-text
	// path through two call sites whose tails it merges.
	if (selected == -1)
	{
		if (text.compare(L"") != 0)
			GadgetComboBoxSetText(m_playerTypeCombos[index], text);
		else
			GadgetComboBoxSetSelectedPos(m_playerTypeCombos[index], 0, false);
	}
	else
		GadgetComboBoxSetText(m_playerTypeCombos[index], text);
}
