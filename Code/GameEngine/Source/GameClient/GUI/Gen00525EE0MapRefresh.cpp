// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

class GameWindow;
class GameSlot;

void GadgetComboBoxGetSelectedPos(GameWindow *window, int *selected);
void *GadgetComboBoxGetItemData(GameWindow *window, int selected);
void _bfme_closeAptScreen(const AsciiString &screenName);

class Gen005207C0Member
{
public:
	void bfmeReset(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	bool isAI(void) const;
	bool isHuman(void) const;
	int getStartPosition(void) const { return m_startPosition; }
	int getPlayerTemplate(void) const { return m_playerTemplate; }
	int getColor(void) const { return m_color; }

private:
	unsigned char m_unmodelled[0x10];
	int m_startPosition;
	int m_playerTemplate;
	int m_color;
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
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapMetaData
{
public:
	unsigned char m_unmodelled[0x25];
	bool m_isMultiplayer;
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
	virtual bool bfmeSetColor(GameSlot *slot, int color) = 0;
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

class Gen_00525EE0
{
public:
	void bfmeRefresh(void);
	void bfmeShutdown(void);
	void bfmeDispatchWindow(GameWindow *window);
	int bfmeFindRepresentativeSlot(void);
	int bfmeFindAvailableStartPosition(int firstIndex);
	bool bfmeApplyStartPosition(int index, int startPosition);
	bool bfmeApplyPlayerTemplate(int index);
	bool bfmeApplyColor(int index);
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
	Gen005207C0Member m_previewState;
	unsigned char m_unmodelled29[0x7F];
	GameWindow *m_colorCombos[8];
	GameWindow *m_playerTemplateCombos[8];
	unsigned char m_unmodelledE8[0x3C];
	bool m_isMultiplayer;
	unsigned char m_unmodelled125[7];
	bool m_ready[8];
};

// The enclosing type has no exposed retail spelling; the real GameInfo,
// MapCache, and MapMetaData identities are established independently.
// ?bfmeRefresh@Gen_00525EE0@@QAEXXZ
void Gen_00525EE0::bfmeRefresh(void)
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
// ?bfmeShutdown@Gen_00525EE0@@QAEXXZ
void Gen_00525EE0::bfmeShutdown(void)
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
// ?bfmeDispatchWindow@Gen_00525EE0@@QAEXPAVGameWindow@@@Z
void Gen_00525EE0::bfmeDispatchWindow(GameWindow *window)
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
// ?bfmeFindRepresentativeSlot@Gen_00525EE0@@QAEHXZ
int Gen_00525EE0::bfmeFindRepresentativeSlot(void)
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
// ?bfmeFindAvailableStartPosition@Gen_00525EE0@@QAEHH@Z
int Gen_00525EE0::bfmeFindAvailableStartPosition(int firstIndex)
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
// ?bfmeApplyStartPosition@Gen_00525EE0@@QAE_NHH@Z
bool Gen_00525EE0::bfmeApplyStartPosition(int index, int startPosition)
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
// ?bfmeApplyPlayerTemplate@Gen_00525EE0@@QAE_NH@Z
bool Gen_00525EE0::bfmeApplyPlayerTemplate(int index)
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

// The controller validates both cached game records before applying a combo
// box selection. The member layout is shared with bfmeRefresh above.
// ?bfmeApplyColor@Gen_00525EE0@@QAE_NH@Z
bool Gen_00525EE0::bfmeApplyColor(int index)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (!m_first)
		return false;

	m_pending = false;
	GameWindow *combo = m_colorCombos[index];
	int selected;
	GadgetComboBoxGetSelectedPos(combo, &selected);
	int color = (int)GadgetComboBoxGetItemData(combo, selected);
	GameSlot *slot = m_first->getSlot(index);
	if (!slot)
		return false;
	if (color == slot->getColor())
		return false;

	return m_owner->bfmeSetColor(slot, color);
}

// Count the ready, playable human slots in the validated game record.
// ?bfmeCountReadyPlayers@Gen_00525EE0@@QAEGXZ
unsigned short Gen_00525EE0::bfmeCountReadyPlayers(void)
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
