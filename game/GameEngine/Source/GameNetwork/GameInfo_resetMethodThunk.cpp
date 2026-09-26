// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?reset@GameInfo@@UAEXXZ: game/GameEngine/Source/GameNetwork/GameInfo.cpp
// Open-BFME5: retail GameInfo reset in C++.

extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount();

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	virtual void reset();
};

extern int OpenBFME5_netCRCInterval;

class __declspec(novtable) GameInfo
{
public:
	virtual void reset();
private:
	int m_preorderMask;
	int m_crcInterval;
	unsigned char m_inGame;
	unsigned char m_inProgress;
	unsigned char m_oldFactionsOnly;
	unsigned char m_padding0f;
	int m_gameID;
	GameSlot *m_slots[8];
	unsigned int m_localIP;
	unsigned int m_padding38;
	AsciiString m_mapName;
	unsigned int m_mapCRC;
	unsigned int m_mapSize;
	int m_mapMask;
	int m_seed;
	int m_useStats;
};

void GameInfo::reset()
{
	m_crcInterval = OpenBFME5_netCRCInterval;
	m_inGame = 0;
	m_inProgress = 0;
	m_gameID = 0;
	{
		AsciiString mapName("NOMAP");
		m_mapName = mapName;
	}
	m_mapMask = 0;
	m_seed = (int)GetTickCount();
	m_useStats = -1;
	m_oldFactionsOnly = 0;
	m_mapCRC = 0;
	m_mapSize = 0;
	for (int i = 0; i < 8; ++i) {
		if (m_slots[i])
			m_slots[i]->reset();
	}
	m_preorderMask = 0;
}
