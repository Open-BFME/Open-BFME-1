// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?amIHost@GameSpyStagingRoom@@: Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp

// Not in game, no host. Otherwise ask the first slot whether the local name is
// its player.
//
// The AsciiString comes from the shim rather than a hand-rolled stand-in: it is
// passed to isPlayer by value, and that only comes out in retail's order with
// the real StringBase-backed class. This row was parked on exactly that.
//
// Arguments evaluate right to left, which is why the string temporary is built
// before getConstSlot is called rather than after.
#include "Common/AsciiString.h"

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	Bool isPlayer(AsciiString name) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	const GameSlot *getConstSlot(Int which) const;

	virtual ~GameInfo();

private:
	unsigned char m_head[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom : public GameInfo
{
public:
	virtual Bool amIHost(void) const;

private:
	bool m_inGame;
	unsigned char m_gap0d[0x424 - 0x0D];
	AsciiString m_localName;
};

// ?amIHost@GameSpyStagingRoom@@UBE_NXZ
Bool GameSpyStagingRoom::amIHost(void) const
{
	if (!m_inGame)
		return false;

	return getConstSlot(0)->isPlayer(m_localName);
}
