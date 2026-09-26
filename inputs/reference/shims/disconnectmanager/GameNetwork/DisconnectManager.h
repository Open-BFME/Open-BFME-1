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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////


#pragma once

// TU-scoped stand-in for the real GameNetwork/DisconnectManager.h. BFME's
// DisconnectManager is 36 bytes smaller than this ZH reference: it drops
// m_packetRouterFallback[MAX_SLOTS] (32) and m_currentPacketRouterIndex (4)
// before m_playerTimeouts, and m_packetRouterTimeout (4) before m_playerVotes.
// That is the same edit that removed PACKETROUTERQUERY and PACKETROUTERACK from
// its command block -- retail processDisconnectCommand handles only 0x18..0x1c.
//
// Four independent retail bodies agree on the shifted tail:
//   m_playerTimeouts            ZH +0x38 -> BFME +0x14  (processDisconnectCommand
//                               0x0066C810 inlines a timeGetTime store there)
//   m_playerVotes               ZH +0x58 -> BFME +0x30  (applyDisconnectVote
//                               0x0066B910, resetPlayersVotes 0x0066B7B0,
//                               voteForPlayerDisconnect 0x0066BAE0, and the
//                               column clear in turnOffScreen 0x0066B270)
//   m_disconnectFrames          ZH +0x258 -> BFME +0x230 (processDisconnectFrame
//                               0x0066BD80, processDisconnectScreenOff 0x0066B890)
//   m_disconnectFramesReceived  ZH +0x278 -> BFME +0x250 (the same two)
// m_disconnectState stays at +0x0c: the matched allowedToContinue (0x0066B2C0)
// is `cmp dword ptr [ecx+0xc], 1`, so the class keeps its vptr.
//
// Scoped to this TU via a private /Ireference/shims/disconnectmanager include --
// every other TU still resolves GameNetwork/DisconnectManager.h to the real one.


#ifndef __DISCONNECTMANAGER_H
#define __DISCONNECTMANAGER_H

#include "GameNetwork/NetCommandRef.h"
#include "Lib/BaseType.h"
//#include "GameNetwork/ConnectionManager.h"

enum DisconnectStateType {
	DISCONNECTSTATETYPE_SCREENON,
	DISCONNECTSTATETYPE_SCREENOFF
//	DISCONNECTSTATETYPE_WAITINGFORPACKETROUTER
};

class ConnectionManager;

struct DisconnectVoteStruct {
	Bool vote;
	UnsignedInt frame;
};

class DisconnectManager 
{
public:
	DisconnectManager();
	virtual ~DisconnectManager();

	void init();
	void update(ConnectionManager *conMgr);

	void processDisconnectCommand(NetCommandRef *ref, ConnectionManager *conMgr);
	void allCommandsReady(UnsignedInt frame, ConnectionManager *conMgr, Bool waitForPacketRouter = TRUE);
	void nextFrame(UnsignedInt frame, ConnectionManager *conMgr);
	Bool allowedToContinue();			///< Allow the next frame to go through?
	void playerHasAdvancedAFrame(Int slot, UnsignedInt frame); ///< this player has advanced to that frame.

	void voteForPlayerDisconnect(Int slot, ConnectionManager *conMgr);

	// For disconnect blame assignment
	UnsignedInt getPingFrame();
	Int getPingsSent();
	Int getPingsRecieved();

protected:
	void sendKeepAlive(ConnectionManager *conMgr);
	void populateDisconnectScreen(ConnectionManager *conMgr);
	Int translatedSlotPosition(Int slot, Int localSlot);
	Int untranslatedSlotPosition(Int slot, Int localSlot);
	void resetPlayerTimeouts(ConnectionManager *conMgr);
	void resetPlayerTimeout(Int slot);
	void resetPacketRouterTimeout();
	void updateDisconnectStatus(ConnectionManager *conMgr);
	void disconnectPlayer(Int slot, ConnectionManager *conMgr);
	void sendDisconnectCommand(Int slot, ConnectionManager *conMgr);
	void sendVoteCommand(Int slot, ConnectionManager *conMgr);
	void updateWaitForPacketRouter(ConnectionManager *conMgr);
	void recalculatePacketRouterIndex(ConnectionManager *conMgr);
	Bool allOnSameFrame(ConnectionManager *conMgr); ///< returns true if all players are stuck on the same frame.
	Bool isLocalPlayerNextPacketRouter(ConnectionManager *conMgr); ///< returns true if the local player is next in line to be the packet router with all the players that have timed out being taken out of the picture.
	Bool hasPlayerTimedOut(Int slot); ///< returns true if this player has timed out.
	void sendPlayerDestruct(Int slot, ConnectionManager *conMgr); ///< send a destruct player network message.
	Bool isPlayerVotedOut(Int slot, ConnectionManager *conMgr);	///< returns true if this player has been voted out.
	Bool isPlayerInGame(Int slot, ConnectionManager *conMgr); ///< returns true if the player has neither timed out or been voted out.
	UnsignedInt getMaxDisconnectFrame();	///< returns the highest frame that people have got to.
	Int countVotesForPlayer(Int slot); ///< return the number of disconnect votes a player has.
	void resetPlayersVotes(Int playerID, UnsignedInt frame, ConnectionManager *conMgr); ///< reset the votes for this player.

	void turnOnScreen(ConnectionManager *conMgr); ///< This gets called when the disconnect screen is first turned on.
	// BFME-only, no ZH counterpart: hides the menu, sets m_disconnectState to
	// SCREENOFF, clears this player's whole column of votes and zeroes
	// m_timeOfDisconnectScreenOn. Body at 0x0066B270.
	void turnOffScreen(Int localSlot);

	void processDisconnectKeepAlive(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processPacketRouterQuery(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processPacketRouterAck(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectVote(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectFrame(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectScreenOff(NetCommandMsg *msg, ConnectionManager *conMgr);

	void applyDisconnectVote(Int slot, UnsignedInt frame, Int castingSlot, ConnectionManager *conMgr);

	UnsignedInt m_lastFrame;
	time_t m_lastFrameTime;
	DisconnectStateType m_disconnectState;

	// ZH's m_packetRouterFallback[MAX_SLOTS] and m_currentPacketRouterIndex are
	// absent in BFME -- 36 bytes, together with m_packetRouterTimeout below.

	time_t m_lastKeepAliveSendTime;				// this+0x10

	time_t m_playerTimeouts[MAX_SLOTS - 1];		// this+0x14

	DisconnectVoteStruct m_playerVotes[MAX_SLOTS][MAX_SLOTS];	// this+0x30, row stride 0x40
//	Bool m_myVotes[MAX_SLOTS - 1];

	UnsignedInt m_disconnectFrames[MAX_SLOTS];	// this+0x230
	Bool m_disconnectFramesReceived[MAX_SLOTS];	// this+0x250
	Bool m_haveNotifiedOtherPlayersOfCurrentFrame;

	time_t m_timeOfDisconnectScreenOn;
	Int m_pingsSent;
	Int m_pingsRecieved;
	UnsignedInt m_pingFrame;

	// BFME has none of these three. They stay declared, but after every pinned
	// field so they cannot shift one, because the ZH bodies in this TU that
	// still reference them -- updateWaitForPacketRouter and
	// isLocalPlayerNextPacketRouter -- are exactly the ones BFME rewrote and
	// are all still present-unmatched.
	UnsignedInt m_packetRouterFallback[MAX_SLOTS];
	UnsignedInt m_currentPacketRouterIndex;
	time_t m_packetRouterTimeout;
};


#endif // #ifndef __DISCONNECTMANAGER_H
