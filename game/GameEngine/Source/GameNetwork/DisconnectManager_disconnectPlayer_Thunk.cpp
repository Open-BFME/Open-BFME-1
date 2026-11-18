// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?disconnectPlayer@DisconnectManager@@IAEXHPAVConnectionManager@@@Z: game/GameEngine/Source/GameNetwork/DisconnectManager.cpp

#include "../../Include/Common/ScalarTypes.h"


class UnicodeString;

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


enum PlayerLeaveCode
{
	PLAYERLEAVECODE_UNKNOWN
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	void markAsDisconnected()
	{
		m_disconnected = true;
	}

private:
	unsigned char m_unreconstructed_00[0x40];
	bool m_disconnected;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameSlot *getSlot(Int slot);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID();
	UnicodeString getPlayerName(Int playerNum);
	PlayerLeaveCode disconnectPlayer(Int slot);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	void logPlayerDisconnect(UnicodeString player, Int slot);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
class DisconnectMenu
{
public:
	void removePlayer(Int slot, UnicodeString playerName);
};

extern GameInfo *TheGameInfo;
extern RecorderClass *TheRecorder;
extern DisconnectMenu *TheDisconnectMenu;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
protected:
	void disconnectPlayer(Int slot, ConnectionManager *conMgr);
};

// BFME's slot record places m_disconnected four bytes later than Zero Hour's.
void DisconnectManager::disconnectPlayer(Int slot, ConnectionManager *conMgr)
{
	if (slot < 0 || slot >= 8)
		return;

	if (TheGameInfo)
	{
		GameSlot *gameSlot = TheGameInfo->getSlot(slot);
		if (gameSlot)
			gameSlot->markAsDisconnected();
	}

	Int localSlot = conMgr->getLocalPlayerID();
	Int translatedSlot;
	if (slot < localSlot)
		translatedSlot = slot;
	else if (slot == localSlot)
		return;
	else
		translatedSlot = slot - 1;

	if (translatedSlot != -1)
	{
		UnicodeString playerName = conMgr->getPlayerName(slot);
		TheRecorder->logPlayerDisconnect(playerName, slot);
		if (TheDisconnectMenu)
			TheDisconnectMenu->removePlayer(translatedSlot, playerName);
		conMgr->disconnectPlayer(slot);
	}
}
