// cl: /EHs-c-

typedef int Int;

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

class GameSlot;

class GameInfo
{
public:
	GameInfo &operator=(const GameInfo &other);

private:
	void *m_vtable;
	Int m_preorderMask;
	Int m_crcInterval;
	unsigned char m_inGame;
	unsigned char m_inProgress;
	unsigned char m_surrendered;
	unsigned char m_padding0F;
	Int m_gameID;
	GameSlot *m_slots[8];
	unsigned int m_localIP;
	Int m_startingCash;
	AsciiString m_mapName;
	unsigned int m_mapCRC;
	unsigned int m_mapSize;
	Int m_mapContentsMask;
	Int m_seed;
	Int m_useStats;
	unsigned int m_gameRestrictions;
};

GameInfo &GameInfo::operator=(const GameInfo &other)
{
	m_preorderMask = other.m_preorderMask;
	m_crcInterval = other.m_crcInterval;
	m_inGame = other.m_inGame;
	m_inProgress = other.m_inProgress;
	m_surrendered = other.m_surrendered;
	m_gameID = other.m_gameID;
	for (int index = 0; index < 8; ++index)
		m_slots[index] = other.m_slots[index];
	m_localIP = other.m_localIP;
	m_startingCash = other.m_startingCash;
	m_mapName = other.m_mapName;
	m_mapCRC = other.m_mapCRC;
	m_mapSize = other.m_mapSize;
	m_mapContentsMask = other.m_mapContentsMask;
	m_seed = other.m_seed;
	m_useStats = other.m_useStats;
	m_gameRestrictions = other.m_gameRestrictions;
	return *this;
}
