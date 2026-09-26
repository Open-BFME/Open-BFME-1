// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?populateDisconnectScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z: game/GameEngine/Source/GameNetwork/DisconnectManager.cpp

typedef int Int;
typedef unsigned int UnsignedInt;

class UnicodeString;

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other)
	{
	}

	~UnicodeString() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	UnicodeString getPlayerName(Int player);
	UnsignedInt getLocalPlayerID();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
class DisconnectMenu
{
public:
	void setPlayerName(Int slot, UnicodeString name);
	void updateVotes(Int slot, Int votes);
};

extern DisconnectMenu *TheDisconnectMenu;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
protected:
	void populateDisconnectScreen(ConnectionManager *connectionManager);
	Int countVotesForPlayer(Int player, ConnectionManager *connectionManager);
};

// ?populateDisconnectScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z
void DisconnectManager::populateDisconnectScreen(ConnectionManager *connectionManager)
{
	if (!TheDisconnectMenu)
		return;

	for (Int player = 0; player < 8; ++player)
	{
		UnicodeString name = connectionManager->getPlayerName(player);
		Int localPlayer = connectionManager->getLocalPlayerID();
		Int slot;
		if (player < localPlayer)
			slot = player;
		else if (player == localPlayer)
			continue;
		else
			slot = player - 1;

		if (slot != -1)
		{
			TheDisconnectMenu->setPlayerName(slot, name);
			Int votes = countVotesForPlayer(player, connectionManager);
			TheDisconnectMenu->updateVotes(slot, votes);
		}
	}
}
