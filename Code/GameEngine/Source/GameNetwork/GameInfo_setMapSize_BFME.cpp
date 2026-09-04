// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME layout reconstruction for GameInfo::setMapSize at 0x00621B30.

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
	void toLower();

private:
	void *m_data;
};

struct MapCacheNode
{
	unsigned char m_prefix[0x40];
	unsigned int m_CRC;
};

class MapCache
{
public:
	MapCacheNode *bfmeFind(const AsciiString &mapName);
	MapCacheNode *m_head;
};

extern MapCache *TheMapCache;

class GameSlot
{
public:
	virtual void reset();

	void setMapAvailability(bool hasMap)
	{
		if (m_state == 5)
			m_hasMap = hasMap;
	}

private:
	int m_state;
	bool m_isAccepted;
	bool m_hasMap;
};

class GameInfo
{
public:
	virtual int bfmeSlot0();
	virtual int bfmeSlot1();
	virtual void reset();
	virtual void startGame(int gameID);
	virtual bool amIHost() const;
	virtual int getLocalSlotNum() const;

	GameSlot *getSlot(int slotNum);
	void setMapSize(unsigned int mapSize);

private:
	int m_preorderMask;
	int m_crcInterval;
	bool m_inGame;
	bool m_inProgress;
	bool m_surrendered;
	char m_pad0f;
	int m_gameID;
	GameSlot *m_slot[8];
	unsigned int m_localIP;
	int m_bfmeExtra38;
	AsciiString m_mapName;
	unsigned int m_mapCRC;
	unsigned int m_mapSize;
};

void GameInfo::setMapSize(unsigned int mapSize)
{
	m_mapSize = mapSize;
	if (!TheMapCache)
		return;

	if (m_inGame && getLocalSlotNum() >= 0)
	{
		AsciiString lowerMap = m_mapName;
		lowerMap.toLower();
		MapCache *cache = TheMapCache;
		MapCacheNode *it = cache->bfmeFind(lowerMap);
		if (it == cache->m_head)
		{
			getSlot(getLocalSlotNum())->setMapAvailability(false);
		}
		else if (m_mapCRC != it->m_CRC)
		{
			getSlot(getLocalSlotNum())->setMapAvailability(false);
		}
		else
		{
			getSlot(getLocalSlotNum())->setMapAvailability(true);
		}
	}
}
