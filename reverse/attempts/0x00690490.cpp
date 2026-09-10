// ?ParseGameOptionsString@@YA_NPAVLANGameInfo@@VAsciiString@@PADI@Z
// partial score=0.62 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// ?ParseGameOptionsString@@YA_NPAVLANGameInfo@@VAsciiString@@PADI@Z
// Retail 0x00690490, 954 bytes.  The BFME LAN announce parser preserves the
// login and host strings around either the bounded serialized game-info
// decoder or the three-argument text parser, then refreshes remote map state
// and stamps the surviving human slots.

#include "PreRTS.h"

#include "GameNetwork/LANGameInfo.h"
#include "GameNetwork/LANAPICallbacks.h"

extern Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options,
	Bool includeSlots);
extern Bool ParseAsciiStringToGameInfo(GameInfo *game, char *buffer,
	UnsignedInt length);
extern void processInactiveLanMessages(void);
extern void resetLanGameState(void);
extern Int (*g_bfmeNowVNH)(void);

Bool ParseGameOptionsString(LANGameInfo *game, AsciiString options,
	char *buffer, UnsignedInt length)
{
	if (!TheLAN || !game)
		return false;

	Int oldLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
	Bool wasInGame = oldLocalSlotNum >= 0;
	AsciiString oldMap = game->getMap();
	UnsignedInt oldMapCRC, newMapCRC;
	oldMapCRC = game->getMapCRC();

	std::map<UnicodeString, UnicodeString> oldLogins, oldMachines;
	std::map<UnicodeString, UnicodeString>::iterator mapIt;
	Int i;
	for (i = 0; i < MAX_SLOTS; ++i)
	{
		LANGameSlot *slot = game->getLANSlot(i);
		if (slot && slot->isHuman())
		{
			oldLogins[slot->getName()] = slot->getUser()->getLogin();
			oldMachines[slot->getName()] = slot->getUser()->getHost();
		}
	}

	Bool parsed;
	if (buffer && length)
		parsed = ParseAsciiStringToGameInfo(game, buffer, length);
	else
		parsed = ParseAsciiStringToGameInfo(game, options, TRUE);

	if (parsed)
	{
		Int newLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
		Bool isInGame = newLocalSlotNum >= 0;
		if (!TheLAN->AmIHost() && isInGame)
		{
			newMapCRC = game->getMapCRC();
			if ((oldMapCRC ^ newMapCRC) || (!wasInGame && isInGame))
			{
				TheLAN->RequestHasMap();
				processInactiveLanMessages();
				resetLanGameState();
			}
		}

		UnsignedInt now = g_bfmeNowVNH();
		for (i = 0; i < MAX_SLOTS; ++i)
		{
			LANGameSlot *slot = game->getLANSlot(i);
			if (slot->isHuman())
			{
				slot->setLastHeard(now);
				mapIt = oldLogins.find(slot->getName());
				if (mapIt != oldLogins.end())
					slot->setLogin(mapIt->second);
				mapIt = oldMachines.find(slot->getName());
				if (mapIt != oldMachines.end())
					slot->setHost(mapIt->second);
			}
		}

		return true;
	}

	return false;
}
