// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

class GameWindow;
class GameSlot;

void GadgetComboBoxGetSelectedPos(GameWindow *window, int *selected);
void *GadgetComboBoxGetItemData(GameWindow *window, int selected);

class GameSlot
{
public:
	int getColor(void) const { return m_color; }

private:
	unsigned char m_unmodelled[0x18];
	int m_color;
};

class GameInfo
{
public:
	AsciiString getMap(void) const;
	GameSlot *getSlot(int index);
};

class MapMetaData
{
public:
	unsigned char m_unmodelled[0x25];
	bool m_isMultiplayer;
};

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
	virtual void bfmeSlot2(void) = 0;
	virtual void bfmeSlot3(void) = 0;
	virtual void bfmeSlot4(void) = 0;
	virtual bool bfmeSetColor(GameSlot *slot, int color) = 0;
	virtual void bfmeSlot6(void) = 0;
	virtual void bfmeSlot7(void) = 0;
	virtual void bfmeSlot8(void) = 0;
	virtual bool bfmeContains(GameInfo *game) = 0;
};

class Gen_00525EE0
{
public:
	void bfmeRefresh(void);
	bool bfmeApplyColor(int index);

private:
	unsigned char m_unmodelled[4];
	Gen00525EE0Owner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	unsigned char m_unmodelled10[7];
	bool m_pending;
	unsigned char m_unmodelled18[0x90];
	GameWindow *m_colorCombos[8];
	unsigned char m_unmodelledC8[0x5C];
	bool m_isMultiplayer;
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
