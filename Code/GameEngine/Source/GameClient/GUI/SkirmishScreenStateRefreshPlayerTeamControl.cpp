// cl: /O2 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x005268F0 (544 bytes, thiscall, ret 8), reached through ILT
// 0x0002EA91 from the matched SkirmishScreenState::refreshAllPlayerControls,
// SkirmishScreenState::apply and 0x00529AE0.
//
// This rebuilds the TEAM combo: it fills the receiver's +0xA8 array, which
// the literal-named gadget callback 0x00525AB0 binds to "Team", with the
// "Team:0" and "Team:%d" labels. Zero Hour twin: PopulateTeamComboBox in
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameNetwork/GUIUtil.cpp.
// BFME adds the start-position team restriction (MpGameSetup's matched
// bfmeGetStartPositionInfo on the same receiver) and keeps the previous
// selection. The ILT was pinned as refreshPlayerFactionControl; the faction
// (+0xC8, "SIDE:%s") rebuild is 0x005294F0 behind ILT 0x0002D38A.

#include "string_base.h"

template <typename T> inline StringBase<T>::StringBase() : m_data(0) {}
template <typename T> inline StringBase<T>::~StringBase() { releaseBuffer(); }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	void __cdecl format(AsciiString fmt, ...);
	const char *str() const { return m_data ? m_data->data : ""; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}
};

class GameWindow;

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerColorDefinition
{
public:
	int getColor() const { return m_color; }

private:
	unsigned char m_unmodelled00[0x10];
	int m_color;
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int which);
};

extern MultiplayerSettings *TheMultiplayerSettings;

void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, int index, void *data);
void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, int *selectedIndex);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, int index);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int selectedIndex, bool dontHide);

// Only the +4 word is read here: when non-negative it is the one team index
// the slot's start position allows.
struct StartPositionInfo
{
	int m_value00;
	int m_value04;
};

class MpGameSetup
{
public:
	const StartPositionInfo *bfmeGetStartPositionInfo(int slotIndex);
};

class SkirmishScreenState
{
public:
	void refreshPlayerTeamControl(int index, bool isObserver);

private:
	unsigned char m_unmodelled00[0xA8];
	GameWindow *m_team[8];
};

// ?refreshPlayerTeamControl@SkirmishScreenState@@QAEXH_N@Z
void SkirmishScreenState::refreshPlayerTeamControl(int index, bool isObserver)
{
	UnicodeString teamName;
	int startTeam = -1;
	const StartPositionInfo *info = ((MpGameSetup *)this)->bfmeGetStartPositionInfo(index);
	if (info)
		startTeam = info->m_value04;

	// One variable receives both the old selection and each new entry index;
	// retail keeps it in the dead first-argument slot.
	int selectedTeam = -1;
	int newIndex;
	GadgetComboBoxGetSelectedPos(m_team[index], &newIndex);
	if (newIndex >= 0)
		selectedTeam = (int)GadgetComboBoxGetItemData(m_team[index], newIndex);

	GadgetComboBoxReset(m_team[index]);

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(-1);
	if (isObserver || startTeam < 0)
	{
		newIndex = GadgetComboBoxAddEntry(m_team[index], TheGameText->fetch("Team:0"), def->getColor());
		GadgetComboBoxSetItemData(m_team[index], newIndex, (void *)-1);
		if (isObserver)
		{
			GadgetComboBoxSetSelectedPos(m_team[index], 0, false);
			return;
		}
	}

	int selectPos = 0;
	for (int c = 0; c < 4; ++c)
	{
		if (startTeam >= 0 && startTeam != c)
			continue;

		AsciiString teamStr;
		teamStr.format("Team:%d", c + 1);
		teamName = TheGameText->fetch(teamStr.str());
		newIndex = GadgetComboBoxAddEntry(m_team[index], teamName, def->getColor());
		GadgetComboBoxSetItemData(m_team[index], newIndex, (void *)c);
		if (c == selectedTeam)
			selectPos = newIndex;
	}

	GadgetComboBoxSetSelectedPos(m_team[index], selectPos, false);
}
