// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME layout reconstruction for GameInfo::setMapCRC at 0x00621A20.
// The BFME map cache is a hand-rolled tree, not Zero Hour's std::map.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	MapCacheNode *bfmeFind(const AsciiString &mapName);

	MapCacheNode *m_head;
};

extern MapCache *TheMapCache;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
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
	void setMapCRC(unsigned int mapCRC);
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

void GameInfo::setMapCRC(unsigned int mapCRC)
{
	m_mapCRC = mapCRC;
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
