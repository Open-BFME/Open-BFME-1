// ?bfmeMapChanged@BfmeAptScreenLanLobby@@QAE_NPBVAsciiString@@@Z
// Retail 0x005175B0.  The LanLobby owner supplies this callback to the
// shared map selector at vtable slot 8.
// cl: /O2 /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/asciistring_downloadmanager

#include "Common/AsciiString.h"

class GameSlot
{
public:
	void setMapAvailability(bool hasMap);
};

class GameInfo
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void resetAccepted();
	virtual void resetStartSpots();
	virtual void adjustSlotsForMap();
	virtual void closeOpenSlots();

	void setMapForwarder(AsciiString mapName);
	void setMapCRC(unsigned int mapCRC);
	void setMapSize(unsigned int mapSize);
	GameSlot *getSlot(int slotNum);
};

class LANAPI
{
public:
	#define LANAPI_SLOT(N) virtual void slot##N();
	LANAPI_SLOT(00) LANAPI_SLOT(01) LANAPI_SLOT(02) LANAPI_SLOT(03)
	LANAPI_SLOT(04) LANAPI_SLOT(05) LANAPI_SLOT(06) LANAPI_SLOT(07)
	LANAPI_SLOT(08) LANAPI_SLOT(09) LANAPI_SLOT(10) LANAPI_SLOT(11)
	LANAPI_SLOT(12) LANAPI_SLOT(13) LANAPI_SLOT(14) LANAPI_SLOT(15)
	LANAPI_SLOT(16) LANAPI_SLOT(17) LANAPI_SLOT(18) LANAPI_SLOT(19)
	LANAPI_SLOT(20)
	virtual void requestSerializedGameInfo(bool unused, void *destination);
	LANAPI_SLOT(22) LANAPI_SLOT(23) LANAPI_SLOT(24) LANAPI_SLOT(25)
	LANAPI_SLOT(26) LANAPI_SLOT(27) LANAPI_SLOT(28) LANAPI_SLOT(29)
	LANAPI_SLOT(30) LANAPI_SLOT(31) LANAPI_SLOT(32) LANAPI_SLOT(33)
	LANAPI_SLOT(34) LANAPI_SLOT(35) LANAPI_SLOT(36) LANAPI_SLOT(37)
	LANAPI_SLOT(38) LANAPI_SLOT(39) LANAPI_SLOT(40) LANAPI_SLOT(41)
	LANAPI_SLOT(42) LANAPI_SLOT(43) LANAPI_SLOT(44) LANAPI_SLOT(45)
	LANAPI_SLOT(46) LANAPI_SLOT(47)
	virtual GameInfo *GetMyGame();
	#undef LANAPI_SLOT
};

class MapMetaData
{
private:
	char m_unmodelled[0x28];

public:
	unsigned int m_filesize;
	unsigned int m_CRC;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern LANAPI *TheLAN;
extern MapCache *TheMapCache;

class BfmeAptScreenLanLobby
{
public:
	bool bfmeMapChanged(const AsciiString *mapName);
};

bool BfmeAptScreenLanLobby::bfmeMapChanged(
	const AsciiString *mapName)
{
	GameInfo *game = reinterpret_cast<GameInfo *>(TheLAN->GetMyGame());
	if (!game)
		return false;

	AsciiString lowerMap = *mapName;
	lowerMap.toLower();
	game->setMapForwarder(lowerMap);
	const MapMetaData *map = TheMapCache->findMap(lowerMap);
	if (map)
	{
		game->getSlot(0)->setMapAvailability(true);
		game->setMapCRC(map->m_CRC);
		game->setMapSize(map->m_filesize);
		game->adjustSlotsForMap();
		game->closeOpenSlots();
		game->resetStartSpots();

		struct TransportAddress
		{
			unsigned int ip;
			unsigned short port;
		};
		TransportAddress address = { 0, 0 };
		TheLAN->requestSerializedGameInfo(true, &address);
	}
	return true;
}
