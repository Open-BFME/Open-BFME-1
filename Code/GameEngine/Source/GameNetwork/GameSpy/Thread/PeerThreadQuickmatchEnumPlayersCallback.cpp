// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//
// quickmatchEnumPlayersCallback is registered by PeerThreadClass::doQuickMatch
// through peerEnumPlayers at PeerThread.cpp:2011.  The retail callback body
// is the complete range 0x00648FF0-0x00649127 (312 bytes), including its
// cold return at 0x0064910A.  The PeerThread state and PeerResponse views are
// TU-local ABI declarations; all callback and callee names retain their
// source identities.

#include <string>

typedef void *PEER;
typedef int Int;
typedef bool Bool;
typedef int PEERBool;
typedef unsigned int UnsignedInt;

enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
};

class PeerThreadClass
{
	char m_beforeMatchFlags[0x3c8];
	Bool m_sawEndOfEnumPlayers;
	Bool m_sawMatchbot;
	char m_matchbotPadding[2];
	std::string m_matchbotName;

public:
	void sawEndOfEnumPlayers(void)
	{
		m_sawEndOfEnumPlayers = true;
	}

};

class Gen_00648B40
{
public:
	void bfmeSetString(std::string bot);
};

class PeerResponse
{
public:
	PeerResponse();
	~PeerResponse();
	int peerResponseType;

	std::string groupRoomName;
	std::string nick;
	std::string oldNick;
	std::wstring text;
	std::string locale;
	std::string stagingServerGameOptions;
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;
	std::string stagingRoomPlayerNames[8];
	std::string command;
	std::string commandOptions;

	union
	{
		struct
		{
			Int profileID;
			Int wins;
			Int losses;
			Int roomType;
			Int flags;
			UnsignedInt IP;
			Int rankPoints;
			Int side;
			Int preorder;
			char unknown[0x20c];
			Int rank1v1;
			Int rank2v2;
			Int lastLadder;
		} player;
		int words[143];
	};
};

typedef char PeerResponseSizeCheck[sizeof(PeerResponse) == 0x330 ? 1 : -1];

class PeerRequest;

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread(void) = 0;
	virtual void endThread(void) = 0;
	virtual bool isThreadRunning(void) = 0;
	virtual bool isConnected(void) = 0;
	virtual bool isConnecting(void) = 0;
	virtual void addRequest(const PeerRequest &) = 0;
	virtual bool getRequest(PeerRequest &) = 0;
	virtual void addResponse(const PeerResponse &) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern "C" void peerGetPlayerProfileIDA(PEER peer, const char *nick,
	void (*callback)(PEER, PEERBool, const char *, int, void *), void *param,
	PEERBool blocking);
extern void qmProfileIDCallback(PEER peer, PEERBool success, const char *nick,
	int profileID, void *param);

#define MATCHBOT_PROFILE_ID (*(Int *)0x012F750C)


#pragma optimize("y", on)
void quickmatchEnumPlayersCallback(PEER peer, PEERBool success, RoomType roomType,
	int index, const char *nick, int flags, void *param)
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t || !success || nick == NULL || nick[0] == '\0')
	{
		t->sawEndOfEnumPlayers();
		return;
	}

	Int id = 0;
	peerGetPlayerProfileIDA(peer, nick, qmProfileIDCallback, &id, true);
	if (id == MATCHBOT_PROFILE_ID)
		reinterpret_cast<Gen_00648B40 *>(t)->bfmeSetString(nick);

	PeerResponse resp;
	resp.peerResponseType = 10;
	resp.nick = nick;
	resp.player.roomType = roomType;
	resp.player.IP = 0;
	TheGameSpyPeerMessageQueue->addResponse(resp);
}
#pragma optimize("y", off)

