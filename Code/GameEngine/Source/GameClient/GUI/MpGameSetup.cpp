// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"
#include "../game_window.h"

class GameSlot;

void GadgetComboBoxGetSelectedPos(GameWindow *window, int *selected);
void *GadgetComboBoxGetItemData(GameWindow *window, int selected);
void GadgetComboBoxHideList(GameWindow *window);
void _bfme_closeAptScreen(const AsciiString &screenName);

// The embedded preview extent is witnessed by constructor 0x00520670
// (last four-byte store at +0x3C) and the next containing member at +0x68.
// Only raw storage is needed here; construction/destruction is not implied.
class AptMapPreview
{
public:
	void bfmeReset(void);
private:
	unsigned char m_unmodelled00[0x40];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	bool isAI(void) const;
	bool isHuman(void) const;
	int getStartPosition(void) const { return m_startPos; }
	int getPlayerTemplate(void) const { return m_playerTemplate; }
	int getTeamNumber(void) const { return m_teamNumber; }

private:
	unsigned char m_unmodelled[0x10];
	int m_startPos;
	int m_playerTemplate;
	int m_teamNumber;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void bfmeSlot1(void) = 0;
	virtual void bfmeSlot2(void) = 0;
	virtual void bfmeSlot3(void) = 0;
	virtual bool amIHost(void) const = 0;
	virtual int getLocalSlotNum(void) const = 0;

	AsciiString getMap(void) const;
	GameSlot *getSlot(int index);
	const GameSlot *getConstSlot(int index) const;

private:
	unsigned char m_unmodelled[0x38];
	AsciiString m_mapName;
};

// The retail BFME layout places m_mapName at this+0x3c, and the upstream
// implementation is the ordinary by-value copy getter.
AsciiString GameInfo::getMap(void) const
{
	return m_mapName;
}

struct StartPositionInfo
{
	unsigned char m_data[20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapMetaData
{
public:
	unsigned char m_unmodelled[0x20];
	int m_startPositionCount;
	unsigned char m_unmodelled24;
	bool m_isMultiplayer;
	unsigned char m_unmodelled26[0x2e];
	StartPositionInfo m_startPositions[1];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

class Gen00525EE0Owner
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void bfmeSlot1(void) = 0;
	virtual void bfmeDispatchWindow(GameWindow *window, bool active) = 0;
	virtual void bfmeSlot3(void) = 0;
	virtual unsigned char bfmeSetPlayerTemplate(GameSlot *slot, int playerTemplate) = 0;
	virtual bool bfmeSetTeam(GameSlot *slot, int teamNumber) = 0;
	virtual void bfmeSlot6(void) = 0;
	virtual bool bfmeSetStartPosition(GameSlot *slot, int startPosition) = 0;
	virtual void bfmeSlot8(void) = 0;
	virtual bool bfmeContains(GameInfo *game) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual bool bfmeShouldRestoreBackground(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSetBackgroundVisible(bool visible) = 0;
	virtual void bfmeRestoreBackground(void) = 0;
};

class MpGameSetup
{
public:
	void bfmeRefresh(void);
	const StartPositionInfo *bfmeGetStartPositionInfo(int slotIndex);
	void bfmeShutdown(void);
	void bfmeDispatchWindow(GameWindow *window);
	int bfmeFindRepresentativeSlot(void);
	int bfmeFindAvailableStartPosition(int firstIndex);
	bool bfmeApplyStartPosition(int index, int startPosition);
	bool bfmeApplyPlayerTemplate(int index);
	bool bfmeApplyTeam(int index);
	unsigned short bfmeCountReadyPlayers(void);

private:
	unsigned char m_unmodelled[4];
	Gen00525EE0Owner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	unsigned char m_unmodelled10[3];
	bool m_startPositionChanged;
	bool m_multiplayerStartPositionChanged;
	unsigned char m_unmodelled15[2];
	bool m_pending;
	bool m_backgroundVisible;
	unsigned char m_unmodelled19[0x0F];
	AptMapPreview m_previewState;
	unsigned char m_unmodelled68[0x40];
	GameWindow *m_teamCombos[8];
	GameWindow *m_playerTemplateCombos[8];
	unsigned char m_unmodelledE8[0x3C];
	bool m_isMultiplayer;
	unsigned char m_unmodelled125[7];
	bool m_ready[8];
};

class Gen_004b5a60 { public: void *m(void *value); };
class Gen_004b5a70 { public: void m(); };
class Rva004B5C90 { public: void invoke(bool hide); };

class Rva00526660Body
{
public:
	void run(int enable, int slotIndex);

private:
	char m_00[4];
	Gen00525EE0Owner *m_04;
	GameInfo *m_08;
	GameInfo *m_0C;
	char m_10[0x2c];
	GameWindow *m_3C[8];
	char m_5C[0x0c];
	GameWindow *m_68[8];
	void *m_88[8];
	GameWindow *m_A8[8];
	GameWindow *m_C8[8];
	char m_E8[0x3c];
	bool m_124;
};

struct Rva00526660Adapter
{
	GameWindow *m_00;
	Rva00526660Adapter(void *value) { ((Gen_004b5a60 *)this)->m(value); }
	void invoke(bool hide) { ((Rva004B5C90 *)this)->invoke(hide); }
	~Rva00526660Adapter() { ((Gen_004b5a70 *)this)->m(); }
};

// ?run@Rva00526660Body@@QAEXHH@Z
void Rva00526660Body::run(int enable, int slotIndex)
{
	if (m_08 && !m_04->bfmeContains(m_08))
		m_08 = 0;
	if (m_0C && !m_04->bfmeContains(m_0C))
		m_0C = 0;
	if (m_08 == 0)
		return;

	if (slotIndex == -1 || slotIndex >= 8)
		slotIndex = m_08->getLocalSlotNum();

	bool currentEnable;
	currentEnable = *(bool *)&enable;
	if (m_124 && ((MpGameSetup *)this)->bfmeGetStartPositionInfo(slotIndex) == 0)
		currentEnable = 0;

	bool empty;
	empty = m_08->getConstSlot(slotIndex)->getPlayerTemplate() == -2;
	Rva00526660Adapter adapter(&m_88[slotIndex]);
	if (adapter.m_00)
	{
		if (empty)
			adapter.invoke(true);
		adapter.m_00->winEnable(((char)enable) && !empty);
	}

	if (m_C8[slotIndex])
		m_C8[slotIndex]->winEnable(currentEnable);
	if (m_A8[slotIndex])
	{
		if (empty)
			GadgetComboBoxHideList(m_A8[slotIndex]);
		m_A8[slotIndex]->winEnable(currentEnable && !empty);
	}

	empty = !empty || m_124;
	for (int index = 0; index < 8 && !empty && m_08->amIHost(); ++index)
	{
		if (m_08->getConstSlot(index) && m_08->getConstSlot(index)->isAI())
			empty = true;
	}

	if (slotIndex == m_08->getLocalSlotNum())
	{
		const GameSlot *localSlot = m_08->getConstSlot(m_08->getLocalSlotNum());
		GameWindow * volatile *preview = (GameWindow * volatile *)((char *)this + 0x3c);
		if (*(const unsigned char *)((const char *)localSlot + 9))
		{
			for (int index = 0; index < 8; ++index)
			{
				GameWindow *window = preview[index];
				if (window)
					window->winEnable(((char)enable) && empty);
			}
		}
		else
		{
			for (int index = 0; index < 8; ++index)
			{
				GameWindow *window = preview[index];
				if (window)
					window->winEnable(false);
			}
		}
	}
}

// MpGameSetup owner proof: vtable 0x0110B030 (installed by 0x0057DA50)
// routes slots 12/13 to 0x0057D110/0x00579390. Both pass their receiver+0x25C
// to named MpGameSetup::GadgetInit (0x00527050) and bfmeShutdown (0x005249B0).
// Slots 2/5 and their unchanged-receiver call chains reach the other methods
// here. GadgetInit's literal registration names the owner, not field guesses.
// Layout below is an observed member view, not a claim of total object size.
// ?bfmeRefresh@MpGameSetup@@QAEXXZ
void MpGameSetup::bfmeRefresh(void)
{
	m_isMultiplayer = false;

	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (m_first)
	{
		const MapMetaData *map = TheMapCache->findMap(m_first->getMap());
		if (map && map->m_isMultiplayer)
			m_isMultiplayer = true;
	}
}

// Tear down the preview state and close the setup APT screen.
// ?bfmeShutdown@MpGameSetup@@QAEXXZ
void MpGameSetup::bfmeShutdown(void)
{
	if (m_backgroundVisible)
	{
		m_backgroundVisible = false;
		m_owner->bfmeSetBackgroundVisible(false);
		if (m_owner->bfmeShouldRestoreBackground())
			m_owner->bfmeRestoreBackground();
	}

	m_previewState.bfmeReset();
	AsciiString screenName("MpGameSetup::GadgetInit");
	_bfme_closeAptScreen(screenName);
}

// Restore the owner background state before dispatching the active window.
// ?bfmeDispatchWindow@MpGameSetup@@QAEXPAVGameWindow@@@Z
void MpGameSetup::bfmeDispatchWindow(GameWindow *window)
{
	if (m_backgroundVisible)
	{
		m_backgroundVisible = false;
		m_owner->bfmeSetBackgroundVisible(false);
		if (m_owner->bfmeShouldRestoreBackground())
			m_owner->bfmeRestoreBackground();
	}
	m_owner->bfmeDispatchWindow(window, true);
}

// Prefer the local slot, except that a hosting observer is represented by the
// first AI slot when one exists.
// ?bfmeFindRepresentativeSlot@MpGameSetup@@QAEHXZ
int MpGameSetup::bfmeFindRepresentativeSlot(void)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (!m_first)
		return 0;

	const GameSlot *local = m_first->getConstSlot(m_first->getLocalSlotNum());
	if (m_first->amIHost() && (!local || local->getPlayerTemplate() == -2))
	{
		for (int index = 0; index < 8; ++index)
		{
			const GameSlot *slot = m_first->getConstSlot(index);
			if (slot && slot->isAI())
				return index;
		}
		return m_first->getLocalSlotNum();
	}
	return m_first->getLocalSlotNum();
}

// Find the next unassigned local/AI slot whose start position can be changed.
// ?bfmeFindAvailableStartPosition@MpGameSetup@@QAEHH@Z
int MpGameSetup::bfmeFindAvailableStartPosition(int firstIndex)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (!m_first)
		return -1;
	if (!m_first->amIHost())
		return -1;

	for (int index = firstIndex; index < 8; ++index)
	{
		GameSlot *slot = m_first->getSlot(index);
		if (slot && slot->getStartPosition() == -1)
		{
			if (index == m_first->getLocalSlotNum() &&
				m_first->getConstSlot(index)->getPlayerTemplate() != -2)
				return index;
			if (slot->isAI())
				return index;
		}
	}
	return -1;
}

// Apply a unique start position and remember changes that need propagation.
// ?bfmeApplyStartPosition@MpGameSetup@@QAE_NHH@Z
bool MpGameSetup::bfmeApplyStartPosition(int index, int startPosition)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (!m_first)
		return false;

	m_pending = false;
	GameSlot *slot = m_first->getSlot(index);
	if (!slot)
		return false;
	if (startPosition == slot->getStartPosition())
		return false;

	if (startPosition >= 0)
	{
		for (int otherIndex = 0; otherIndex < 8; ++otherIndex)
		{
			if (otherIndex == index)
				continue;
			GameSlot *other = m_first->getSlot(otherIndex);
			if (other && other->getStartPosition() == startPosition)
				return false;
		}
	}

	bool changed = m_owner->bfmeSetStartPosition(slot, startPosition);
	if (changed)
	{
		m_startPositionChanged = true;
		if (m_isMultiplayer)
			m_multiplayerStartPositionChanged = true;
	}
	return changed;
}

// Apply the selected player-template value when it differs from the slot.
// ?bfmeApplyPlayerTemplate@MpGameSetup@@QAE_NH@Z
bool MpGameSetup::bfmeApplyPlayerTemplate(int index)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (!m_first)
		return false;

	m_pending = false;
	GameWindow *combo = m_playerTemplateCombos[index];
	int selected;
	GadgetComboBoxGetSelectedPos(combo, &selected);
	int playerTemplate = (int)GadgetComboBoxGetItemData(combo, selected);
	if (playerTemplate < -2)
		return false;
	GameSlot *slot = m_first->getSlot(index);
	if (!slot)
		return false;
	if (playerTemplate == slot->getPlayerTemplate())
		return false;

	return m_owner->bfmeSetPlayerTemplate(slot, playerTemplate);
}

// Named callback 0x00525AB0 binds the Team literal to this+0xA8; Color
// uses +0x88 instead. This body compares GameSlot+0x18 and calls owner slot 5.
// LAN slot 5 at 0x00516F00 writes that field and serializes "Team=%d".
// bfmeApplyTeam describes the witnessed behavior, not an original spelling.
// ?bfmeApplyTeam@MpGameSetup@@QAE_NH@Z
bool MpGameSetup::bfmeApplyTeam(int index)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (!m_first)
		return false;

	m_pending = false;
	GameWindow *combo = m_teamCombos[index];
	int selected;
	GadgetComboBoxGetSelectedPos(combo, &selected);
	int teamNumber = (int)GadgetComboBoxGetItemData(combo, selected);
	GameSlot *slot = m_first->getSlot(index);
	if (!slot)
		return false;
	if (teamNumber == slot->getTeamNumber())
		return false;

	return m_owner->bfmeSetTeam(slot, teamNumber);
}

// Count the ready, playable human slots in the validated game record.
// ?bfmeCountReadyPlayers@MpGameSetup@@QAEGXZ
unsigned short MpGameSetup::bfmeCountReadyPlayers(void)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (!m_first)
		return 0;

	int count = 0;
	volatile bool *ready = m_ready;
	int index = 0;
	int remaining = 8;
	do
	{
		GameSlot *slot = m_first->getSlot(index);
		if (slot && slot->isHuman() && slot->getPlayerTemplate() != -2 && *ready)
			++count;
		++index;
		++ready;
	}
	while (--remaining);

	return (unsigned short)count;
}

// Resolve the selected slot's start-position record in the current map.
// ?bfmeGetStartPositionInfo@MpGameSetup@@QAEPBUStartPositionInfo@@H@Z
const StartPositionInfo *MpGameSetup::bfmeGetStartPositionInfo(int slotIndex)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;
	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;
	if (m_first)
	{
		const MapMetaData *map = TheMapCache->findMap(m_first->getMap());
		if (map)
		{
			GameSlot *slot = m_first->getSlot(slotIndex);
			if (slot)
			{
				int position = slot->getStartPosition();
				if (position >= 0 && position < map->m_startPositionCount)
					return &map->m_startPositions[position];
			}
		}
	}
	return 0;
}
