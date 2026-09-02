// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
private:
	void *m_data;
};

class GameSlot
{
public:
	int getStartPosition(void) const { return m_startPosition; }
private:
	unsigned char m_unmodelled[0x10];
	int m_startPosition;
};

class GameInfo
{
public:
	AsciiString getMap(void) const;
	GameSlot *getSlot(int index);
};

struct StartPositionInfo
{
	unsigned char m_data[20];
};

class MapMetaData
{
public:
	unsigned char m_unmodelled[0x20];
	int m_startPositionCount;
	unsigned char m_unmodelled24[0x30];
	StartPositionInfo m_startPositions[1];
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
	virtual void bfmeSlot5(void) = 0;
	virtual void bfmeSlot6(void) = 0;
	virtual void bfmeSlot7(void) = 0;
	virtual void bfmeSlot8(void) = 0;
	virtual bool bfmeContains(GameInfo *game) = 0;
};

class Gen_00525EE0
{
public:
	const StartPositionInfo *bfmeGetStartPositionInfo(int slotIndex);
private:
	unsigned char m_unmodelled[4];
	Gen00525EE0Owner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
};

// Resolve the selected slot's start-position record in the current map.
// ?bfmeGetStartPositionInfo@Gen_00525EE0@@QAEPBUStartPositionInfo@@H@Z
const StartPositionInfo *Gen_00525EE0::bfmeGetStartPositionInfo(int slotIndex)
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
