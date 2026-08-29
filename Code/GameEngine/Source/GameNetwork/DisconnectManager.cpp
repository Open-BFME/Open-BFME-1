// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/disconnectmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME's vote helpers take the live connection manager, overloads absent from the published ZH header.
#define countVotesForPlayer(slot) countVotesForPlayer(slot); \
	Int countVotesForPlayer(Int, ConnectionManager *); \
	Int getVotesNeededToKick(Int, ConnectionManager *)
#include "GameNetwork/DisconnectManager.h"
#undef countVotesForPlayer

#include "Common/Recorder.h"
#define showPlayerControls(slot) showPlayerControls(slot); \
	void _bfme_showPlayerControls(Int, Bool); \
	Bool _bfme_arePlayerControlsShown(Int); \
	void setPlayerTimeoutTime(Int, Int)
#include "GameClient/DisconnectMenu.h"
#undef showPlayerControls
#include "GameClient/InGameUI.h"
#include "GameLogic/GameLogic.h"
#include "GameNetwork/NetworkInterface.h"
#include "GameNetwork/NetworkUtil.h"
#include "GameNetwork/GameSpy/PingThread.h"
#include "GameNetwork/GameSpy/GSConfig.h"

// BFME adds this connection-state query; the published ZH class declaration does not expose it.
class BFMEConnectionManager : public ConnectionManager
{
public:
	Bool isPlayerInGame(Int slot);
	Bool isPlayerSlotActive(Int slot);
	void sendDisconnectFrameCommand();
	void resendFrameRangeToPlayer(Int playerID, UnsignedInt startFrame, UnsignedInt endFrame);
};

class BFMEDisconnectManager : public DisconnectManager
{
public:
	Bool hasPingSuccessRatioAtLeast(Real ratio);
};

// BFME keeps the packet-router fallback plan at this address in its expanded
// ConnectionManager.  The published header's member is not layout-compatible
// here, so keep this view private to the reconstructed accessor.
class BFMEConnectionRouterLayout
{
private:
	char m_bfmePad0[0x12030];

public:
	UnsignedInt m_packetRouterFallback[MAX_SLOTS];
};

// BFME's NetworkInterface puts voteForPlayerDisconnect at vtable slot 31.
class BFMENetworkVoteFacade
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void voteForPlayerDisconnect(Int slot);
};

// ?getNextPacketRouterSlot@ConnectionManager@@QAEII@Z		40 bytes
__declspec(noinline) UnsignedInt ConnectionManager::getNextPacketRouterSlot(UnsignedInt playerID)
{
	BFMEConnectionRouterLayout *layout = (BFMEConnectionRouterLayout *)this;
	Int index = 0;
	while ((index < (MAX_SLOTS - 1)) && (layout->m_packetRouterFallback[index] != playerID)) {
		++index;
	}
	++index;
	return layout->m_packetRouterFallback[index];
}

extern Int g_bfmeDisconnectPingResult;

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

DisconnectManager::DisconnectManager() 
{
	m_lastFrame = 0;
	m_lastFrameTime = 0;
	m_disconnectState = DISCONNECTSTATETYPE_SCREENON;
	m_lastKeepAliveSendTime = 0;
	// BFME packs this flag and adds tail state absent from the published ZH layout.
	*(Int *)((char *)this + 0x258) = 0;
	m_timeOfDisconnectScreenOn = 0;
	m_pingsSent = 0;
	m_pingsRecieved = 0;
	m_pingFrame = 0;
	*(Int *)((char *)this + 0x26c) = 0;
	*(UnsignedByte *)((char *)this + 0x270) = 0;

	Int i;
	for (i = 0; i < MAX_SLOTS - 1; ++i) {
		m_playerTimeouts[i] = 0;
	}

	for (i = 0; i < MAX_SLOTS; ++i) {
		for (Int j = 0; j < MAX_SLOTS; ++j) {
			m_playerVotes[i][j].vote = FALSE;
			m_playerVotes[i][j].frame = 0;
		}
		m_disconnectFrames[i] = 0;
		m_disconnectFramesReceived[i] = FALSE;
		((UnsignedShort *)((char *)this + 0x272))[i] = 0;
		((UnsignedByte *)((char *)this + 0x282))[i] = 0;
	}
}

// ??1DisconnectManager@@UAE@XZ present-unmatched
DisconnectManager::~DisconnectManager() {
}

void DisconnectManager::init() {
	m_lastFrame = 0;
	m_lastFrameTime = -1;
	m_lastKeepAliveSendTime = -1;
	*(Int *)((char *)this + 0x258) = 0;
	m_disconnectState = DISCONNECTSTATETYPE_SCREENOFF;
	m_timeOfDisconnectScreenOn = 0;
	m_pingFrame = 0;

	for (Int i = 0; i < MAX_SLOTS; ++i) {
		for (Int j = 0; j < MAX_SLOTS; ++j) {
			m_playerVotes[i][j].vote = FALSE;
			m_playerVotes[i][j].frame = 0;
		}
		m_disconnectFrames[i] = 0;
		m_disconnectFramesReceived[i] = FALSE;
		((UnsignedShort *)((char *)this + 0x272))[i] = 0;
		((UnsignedByte *)((char *)this + 0x282))[i] = 0;
	}

	*(Int *)((char *)this + 0x26c) = 0;
	m_pingsSent = 0;
	m_pingsRecieved = 0;
	*(UnsignedByte *)((char *)this + 0x270) = 0;
}

// ?update@DisconnectManager@@ present-unmatched
void DisconnectManager::update(ConnectionManager *conMgr) {
	if (m_lastFrameTime == -1) {
		m_lastFrameTime = timeGetTime();
	}

	// The game logic stalls on the frame we are currently waiting for commands on,
	// so we have to check for the current logic frame being one higher than
	// the last one we had the commands ready for.
	if (TheGameLogic->getFrame() == m_lastFrame) {
		time_t curTime = timeGetTime();
		if ((curTime - m_lastFrameTime) > TheGlobalData->m_networkDisconnectTime) {
			if (m_disconnectState == DISCONNECTSTATETYPE_SCREENOFF) {
				turnOnScreen(conMgr);
			}
			sendKeepAlive(conMgr);
		}
	} else {
		nextFrame(TheGameLogic->getFrame(), conMgr);
	}

	if (m_disconnectState != DISCONNECTSTATETYPE_SCREENOFF) {
		updateDisconnectStatus(conMgr);

		// check to see if we need to send pings
		if (m_pingFrame < TheGameLogic->getFrame())
		{
			time_t curTime = timeGetTime();
			if ((curTime - m_lastFrameTime) > 10000) /// @todo: plug in some better measure here
			{
				m_pingFrame = TheGameLogic->getFrame();
				m_pingsSent = 0;
				m_pingsRecieved = 0;

				// Send the pings
				if (ThePinger)
				{
					//use next ping server
					static int serverIndex = 0;
					serverIndex++;
					if( serverIndex >= TheGameSpyConfig->getPingServers().size() )
						serverIndex = 0;  //wrap back to first ping server

					std::list<AsciiString>::iterator it = TheGameSpyConfig->getPingServers().begin();
					for( int i = 0;  i < serverIndex;  i++ )
						it++;

					PingRequest req;
					req.hostname = it->str();
					req.repetitions = 5;
					req.timeout = 2000;
					m_pingsSent = req.repetitions;
					ThePinger->addRequest(req);
					DEBUG_LOG(("DisconnectManager::update() - requesting %d pings of %d from %s\n",
						req.repetitions, req.timeout, req.hostname.c_str()));
				}
			}
		}

		// update the ping thread, tracking pings if we are on the same frame
		if (ThePinger)
		{
			PingResponse resp;
			while (ThePinger->getResponse(resp))
			{
				if (m_pingFrame != TheGameLogic->getFrame())
				{
					// wrong frame - we're not pinging yet
					DEBUG_LOG(("DisconnectManager::update() - discarding ping of %d from %s (%d reps)\n",
						resp.avgPing, resp.hostname.c_str(), resp.repetitions));
				}
				else
				{
					// right frame
					DEBUG_LOG(("DisconnectManager::update() - keeping ping of %d from %s (%d reps)\n",
						resp.avgPing, resp.hostname.c_str(), resp.repetitions));
					if (resp.avgPing < 2000)
					{
						m_pingsRecieved += resp.repetitions;
					}
				}
			}
		}
	}
}

// ?getPingFrame@DisconnectManager@@QAEIXZ present-unmatched
UnsignedInt DisconnectManager::getPingFrame()
{
	return m_pingFrame;
}

Int DisconnectManager::getPingsSent()
{
	return m_pingsSent;
}

Int DisconnectManager::getPingsRecieved()
{
	return m_pingsRecieved;
}


void DisconnectManager::updateDisconnectStatus(ConnectionManager *conMgr) {
	Int i = 0;
	UnsignedShort *playerState = (UnsignedShort *)((char *)this + 0x272);
	for (; i < MAX_SLOTS; ++i, ++playerState) {
		if (conMgr->isPlayerConnected(i)) {
			Int slot = translatedSlotPosition(i, conMgr->getLocalPlayerID());
			if (slot != -1) {
				time_t curTime = timeGetTime();
				time_t newTime = *(UnsignedInt *)((char *)TheGlobalData + 0xcc0)
					- (curTime - m_playerTimeouts[slot]);

				if ((newTime < *(UnsignedInt *)((char *)TheGlobalData + 0xcc0) / 3)
					|| (isPlayerVotedOut(slot, conMgr) == TRUE)) {
					if (TheGameLogic->getFrame() != *(UnsignedInt *)((char *)this + 0x258)) {
						((BFMEConnectionManager *)conMgr)->sendDisconnectFrameCommand();
						*(UnsignedInt *)((char *)this + 0x258) = TheGameLogic->getFrame();
					}
				}

				if ((newTime < 0) || (isPlayerVotedOut(slot, conMgr) == TRUE)
					|| ((BFMEConnectionManager *)conMgr)->isPlayerInGame(i)
					|| (*playerState >= 5)) {
					newTime = 0;
					if ((allOnSameFrame(conMgr) == TRUE)
						&& (isLocalPlayerNextPacketRouter(conMgr) == TRUE)
						&& ((((BFMEConnectionManager *)conMgr)->isPlayerSlotActive(i) == FALSE)
							|| (i == conMgr->getPacketRouterSlot()))) {
						if ((m_pingsSent > 0)
							&& (((Real)m_pingsRecieved / (Real)m_pingsSent) < 0.1f)) {
							if (g_bfmeDisconnectPingResult != 1)
								g_bfmeDisconnectPingResult = 1;
						} else {
							BFMEDisconnectManager *bfmeManager = (BFMEDisconnectManager *)this;
							if ((bfmeManager->hasPingSuccessRatioAtLeast(0.25f) == FALSE)
								&& bfmeManager->hasPingSuccessRatioAtLeast(0.1f)) {
								*(Int *)((char *)TheGameLogic + 0x290) = 0;
							} else if (*(Int *)((char *)TheGameLogic + 0x290) == 0) {
								*(Int *)((char *)TheGameLogic + 0x290) = 2;
							}

							((BFMEConnectionManager *)conMgr)->sendDisconnectFrameCommand();
							sendDisconnectCommand(i, conMgr);
							disconnectPlayer(i, conMgr);
							sendPlayerDestruct(i, conMgr);
						}
					}
				}

				if (TheDisconnectMenu) {
					UnsignedInt timeout = *(UnsignedInt *)((char *)TheGlobalData + 0xcc0);
					if (timeout != 0)
						newTime = newTime * 100 / timeout;
					else
						newTime = 0;
					TheDisconnectMenu->setPlayerTimeoutTime(slot, (Int)newTime);

					if ((UnsignedInt)newTime < 90) {
						if (TheDisconnectMenu->_bfme_arePlayerControlsShown(slot) == FALSE)
							TheDisconnectMenu->_bfme_showPlayerControls(slot, TRUE);
					} else if ((UnsignedInt)newTime > 95) {
						if (TheDisconnectMenu->_bfme_arePlayerControlsShown(slot))
							TheDisconnectMenu->_bfme_showPlayerControls(slot, FALSE);
					}

					if ((newTime == 0) && (isPlayerVotedOut(slot, conMgr) == FALSE)) {
						((BFMENetworkVoteFacade *)TheNetwork)->voteForPlayerDisconnect(i);
					}
				}
			}
		}
	}
}

// ?updateWaitForPacketRouter@DisconnectManager@@IAEXPAVConnectionManager@@@Z present-unmatched
void DisconnectManager::updateWaitForPacketRouter(ConnectionManager *conMgr) {
/*
	time_t curTime = timeGetTime();
	time_t newTime = TheGlobalData->m_networkPlayerTimeoutTime - (curTime - m_packetRouterTimeout);
	if (newTime < 0) {
		newTime = 0;

		// The guy that we were hoping would be the new packet router isn't.  We're screwed, get out of the game.

		DEBUG_LOG(("DisconnectManager::updateWaitForPacketRouter - timed out waiting for new packet router, quitting game\n"));
		TheNetwork->quitGame();
	}
	TheDisconnectMenu->setPacketRouterTimeoutTime(newTime);
*/
}

// BFME body @ 0x66C810/145 (queue 0x66C9FB is INSIDE FUN_00a6c8d0 mega-fn).
// Retail: *(NetCommandMsg**)ref (m_msg@+0 quirk, same as processWrapper); types
// 0x18..0x1c only (KA inline, Player, Vote, Frame, ScreenOff) — no QUERY/ACK;
// KA inlines translatedSlotPosition + resetPlayerTimeout; m_playerTimeouts is
// at +0x14 in BFME, which is why this TU uses the disconnectmanager shim.
void DisconnectManager::processDisconnectCommand(NetCommandRef *ref, ConnectionManager *conMgr) {
	// BFME quirk: retail reads *(void**)ref (m_msg@+0), not getCommand() ([ref+4]).
	// Load msg before any other work so MSVC keeps it in eax like retail.
	NetCommandMsg *msg = *(NetCommandMsg **)ref;
	Int cmdType = (Int)msg->getNetCommandType();
	if (cmdType == 0x18) {
		// Inlined KeepAlive: translatedSlotPosition + resetPlayerTimeout @ +0x14
		// Shape must match retail: one getLocalPlayerID, then jl/je/dec on slot.
		Int slot = (Int)msg->getPlayerID();
		Int localSlot = (Int)conMgr->getLocalPlayerID();
		if (slot >= localSlot) {
			if (slot == localSlot) {
				return;
			}
			--slot;
		}
		if (slot != -1) {
			m_playerTimeouts[slot] = timeGetTime();
		}
	} else if (cmdType == 0x19) {
		processDisconnectPlayer(msg, conMgr);
	} else if (cmdType == 0x1a) {
		processDisconnectVote(msg, conMgr);
	} else if (cmdType == 0x1b) {
		processDisconnectFrame(msg, conMgr);
	} else if (cmdType == 0x1c) {
		processDisconnectScreenOff(msg, conMgr);
	}
}

void DisconnectManager::processDisconnectKeepAlive(NetCommandMsg *msg, ConnectionManager *conMgr) {
	NetDisconnectKeepAliveCommandMsg *cmdMsg = (NetDisconnectKeepAliveCommandMsg *)msg;
	Int slot = translatedSlotPosition(cmdMsg->getPlayerID(), conMgr->getLocalPlayerID());
	if (slot != -1) {
		resetPlayerTimeout(slot);
	}
}

void DisconnectManager::processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr) {
	NetDisconnectPlayerCommandMsg *cmdMsg = (NetDisconnectPlayerCommandMsg *)msg;
	sendPlayerDestruct(cmdMsg->getDisconnectSlot(), conMgr);

	if ((m_pingsSent > 0)
		&& (((Real)m_pingsRecieved / (Real)m_pingsSent) < 0.1f)) {
		*(Int *)((char *)TheGameLogic + 0x290) = 1;
		return;
	}

	if ((m_pingsSent > 0)
		&& (((Real)m_pingsRecieved / (Real)m_pingsSent) < 0.25f)
		&& (*(Int *)((char *)TheGameLogic + 0x290) != 1)) {
		*(Int *)((char *)TheGameLogic + 0x290) = 0;
	}
}

// ?processPacketRouterQuery@DisconnectManager@@IAEXPAVNetCommandMsg@@PAVConnectionManager@@@Z present-unmatched
void DisconnectManager::processPacketRouterQuery(NetCommandMsg *msg, ConnectionManager *conMgr) {
	NetPacketRouterQueryCommandMsg *cmdMsg = (NetPacketRouterQueryCommandMsg *)msg;
	DEBUG_LOG(("DisconnectManager::processPacketRouterQuery - got a packet router query command from player %d\n", msg->getPlayerID()));

	if (conMgr->getPacketRouterSlot() == conMgr->getLocalPlayerID()) {
		NetPacketRouterAckCommandMsg *ackmsg = newInstance(NetPacketRouterAckCommandMsg);
		ackmsg->setPlayerID(conMgr->getLocalPlayerID());
		if (DoesCommandRequireACommandID(ackmsg->getNetCommandType()) == TRUE) {
			ackmsg->setID(GenerateNextCommandID());
		}
		DEBUG_LOG(("DisconnectManager::processPacketRouterQuery - We are the new packet router, responding with an packet router ack. Local player is %d\n", ackmsg->getPlayerID()));
		conMgr->sendLocalCommandDirect(ackmsg, 1 << cmdMsg->getPlayerID());
		ackmsg->detach();
	} else {
		DEBUG_LOG(("DisconnectManager::processPacketRouterQuery - We are NOT the new packet router, these are not the droids you're looking for.\n"));
	}
}

// ?processPacketRouterAck@DisconnectManager@@IAEXPAVNetCommandMsg@@PAVConnectionManager@@@Z present-unmatched
void DisconnectManager::processPacketRouterAck(NetCommandMsg *msg, ConnectionManager *conMgr) {
	NetPacketRouterAckCommandMsg *cmdMsg = (NetPacketRouterAckCommandMsg *)msg;
	DEBUG_LOG(("DisconnectManager::processPacketRouterAck - got packet router ack command from player %d\n", msg->getPlayerID()));

	if (conMgr->getPacketRouterSlot() == cmdMsg->getPlayerID()) {
		DEBUG_LOG(("DisconnectManager::processPacketRouterAck - packet router command is from who it should be.\n"));
		resetPacketRouterTimeout();
		Int currentPacketRouterSlot = conMgr->getPacketRouterSlot();
		Int currentPacketRouterIndex = 0;
		while ((currentPacketRouterSlot != conMgr->getPacketRouterFallbackSlot(currentPacketRouterIndex)) && (currentPacketRouterIndex < MAX_SLOTS)) {
			++currentPacketRouterIndex;
		}
		DEBUG_ASSERTCRASH((currentPacketRouterIndex < MAX_SLOTS), ("Invalid packet router index"));

		DEBUG_LOG(("DisconnectManager::processPacketRouterAck - New packet router confirmed, resending pending commands\n"));
		conMgr->resendPendingCommands();
		m_currentPacketRouterIndex = currentPacketRouterIndex;
		DEBUG_LOG(("DisconnectManager::processPacketRouterAck - Setting disconnect state to screen on.\n"));
		m_disconnectState = DISCONNECTSTATETYPE_SCREENON; ///< set it to screen on so that the next call to AllCommandsReady can set up everything for the next frame properly.
	}
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/DisconnectManagerProcessDisconnectVoteThunk.cpp
// ?processDisconnectVote@DisconnectManager@@IAEXPAVNetCommandMsg@@PAVConnectionManager@@@Z present-unmatched
void DisconnectManager::processDisconnectVote(NetCommandMsg *msg, ConnectionManager *conMgr) {
	NetDisconnectVoteCommandMsg *cmdMsg = (NetDisconnectVoteCommandMsg *)msg;
	DEBUG_LOG(("DisconnectManager::processDisconnectVote - Got a disconnect vote for player %d command from player %d\n", cmdMsg->getSlot(), cmdMsg->getPlayerID()));
	Int transSlot = translatedSlotPosition(msg->getPlayerID(), conMgr->getLocalPlayerID());

	if (isPlayerInGame(transSlot, conMgr) == FALSE) {
		// if they've been timed out, voted out, disconnected, don't count their vote.
		return;
	}

	applyDisconnectVote(cmdMsg->getSlot(), cmdMsg->getVoteFrame(), cmdMsg->getPlayerID(), conMgr);
}

void DisconnectManager::processDisconnectFrame(NetCommandMsg *msg, ConnectionManager *conMgr) {
	NetDisconnectFrameCommandMsg *cmdMsg = (NetDisconnectFrameCommandMsg *)msg;
	UnsignedInt playerID = cmdMsg->getPlayerID();
	if (m_disconnectFrames[playerID] >= cmdMsg->getDisconnectFrame()) {
		return;
	}

	resetPlayersVotes(playerID, cmdMsg->getDisconnectFrame() - 1, conMgr);
	m_disconnectFrames[playerID] = cmdMsg->getDisconnectFrame();
	m_disconnectFramesReceived[playerID] = TRUE;
	conMgr->sendFrameDataToPlayer(playerID, cmdMsg->getDisconnectFrame());

	BFMEConnectionManager *bfmeConMgr = (BFMEConnectionManager *)conMgr;
	if (playerID == conMgr->getLocalPlayerID()) {
		for (Int i = 0; i < MAX_SLOTS; ++i) {
			if (i != playerID) {
				Int transSlot = translatedSlotPosition(i, conMgr->getLocalPlayerID());
				if ((isPlayerInGame(transSlot, conMgr) == TRUE)
					&& (m_disconnectFrames[i] < m_disconnectFrames[playerID])
					&& (m_disconnectFramesReceived[i] == TRUE)) {
					bfmeConMgr->resendFrameRangeToPlayer(
						i, m_disconnectFrames[i], TheGameLogic->getFrame());
				}
			}
		}
	} else if ((m_disconnectFrames[playerID]
			< m_disconnectFrames[conMgr->getLocalPlayerID()])
		&& (m_disconnectFramesReceived[playerID] == TRUE)) {
		bfmeConMgr->resendFrameRangeToPlayer(
			playerID, m_disconnectFrames[playerID], TheGameLogic->getFrame());
	}
}

__declspec(noinline) void DisconnectManager::processDisconnectScreenOff(NetCommandMsg *msg, ConnectionManager *conMgr) {
	NetDisconnectScreenOffCommandMsg *cmdMsg = (NetDisconnectScreenOffCommandMsg *)msg;
	UnsignedInt playerID = cmdMsg->getPlayerID();

	DEBUG_LOG(("DisconnectManager::processDisconnectScreenOff - got a screen off command from player %d for frame %d\n", cmdMsg->getPlayerID(), cmdMsg->getNewFrame()));

	if ((playerID < 0) || (playerID >= MAX_SLOTS)) {
		return;
	}

	UnsignedInt newFrame = cmdMsg->getNewFrame();
	if (newFrame >= m_disconnectFrames[playerID]) {
		DEBUG_LOG(("DisconnectManager::processDisconnectScreenOff - resetting the disconnect screen status for player %d\n", playerID));
		m_disconnectFramesReceived[playerID] = FALSE;
		m_disconnectFrames[playerID] = newFrame; // just in case we get packets out of order and the disconnect screen off message gets here before the disconnect frame message.

		DEBUG_LOG(("DisconnectManager::processDisconnectScreenOff - about to call resetPlayersVotes for player %d\n", playerID));
		resetPlayersVotes(playerID, cmdMsg->getNewFrame(), conMgr);
	}

	// BFME addition: the screen comes down whether or not the frame was new.
	turnOffScreen(conMgr->getLocalPlayerID());
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/DisconnectManager_applyDisconnectVote_Thunk.cpp
// ?applyDisconnectVote@DisconnectManager@@IAEXHIHPAVConnectionManager@@@Z present-unmatched
void DisconnectManager::applyDisconnectVote(Int slot, UnsignedInt frame, Int fromSlot, ConnectionManager *conMgr) {
	m_playerVotes[slot][fromSlot].vote = TRUE;
	m_playerVotes[slot][fromSlot].frame = frame;
	Int numVotes = countVotesForPlayer(slot);
	DEBUG_LOG(("DisconnectManager::applyDisconnectVote - added a vote to disconnect slot %d, from slot %d, for frame %d, current votes are %d\n", slot, fromSlot, frame, numVotes));
	Int transSlot = translatedSlotPosition(slot, conMgr->getLocalPlayerID());
	if (transSlot != -1) {
		TheDisconnectMenu->updateVotes(transSlot, numVotes);
	}
}

// ?nextFrame@DisconnectManager@@QAEXIPAVConnectionManager@@@Z present-unmatched
void DisconnectManager::nextFrame(UnsignedInt frame, ConnectionManager *conMgr) {
	m_lastFrame = frame;
	m_lastFrameTime = timeGetTime();
	resetPlayerTimeouts(conMgr);
}

// ?allCommandsReady@DisconnectManager@@QAEXIPAVConnectionManager@@_N@Z present-unmatched
void DisconnectManager::allCommandsReady(UnsignedInt frame, ConnectionManager *conMgr, Bool waitForPacketRouter) {
		if (m_disconnectState != DISCONNECTSTATETYPE_SCREENOFF) {
			DEBUG_LOG(("DisconnectManager::allCommandsReady - setting screen state to off.\n"));

			TheDisconnectMenu->hideScreen();
			m_disconnectState = DISCONNECTSTATETYPE_SCREENOFF;
			TheNetwork->notifyOthersOfNewFrame(frame);

			// reset the votes since we're moving to a new frame.
			for (Int i = 0; i < MAX_SLOTS; ++i) {
				m_playerVotes[i][conMgr->getLocalPlayerID()].vote = FALSE;
			}

			DEBUG_LOG(("DisconnectManager::allCommandsReady - resetting m_timeOfDisconnectScreenOn\n"));
			m_timeOfDisconnectScreenOn = 0;
		}
}

Bool DisconnectManager::allowedToContinue() {
	if (m_disconnectState != DISCONNECTSTATETYPE_SCREENOFF) {
		return FALSE;
	}
	return TRUE;
}

void DisconnectManager::sendKeepAlive(ConnectionManager *conMgr) {
	// Unsigned: retail compares the elapsed span with `ja`, not `jg`, so the
	// subtraction is done in unsigned arithmetic. With the reference's signed
	// time_t the compiler emits the signed branch and the bodies differ by that
	// one byte.
	UnsignedInt curTime = timeGetTime();

	if (((curTime - m_lastKeepAliveSendTime) > 500) || (m_lastKeepAliveSendTime == -1)) {
		NetDisconnectKeepAliveCommandMsg *msg = newInstance(NetDisconnectKeepAliveCommandMsg);
		msg->setPlayerID(conMgr->getLocalPlayerID());
		if (DoesCommandRequireACommandID(msg->getNetCommandType()) == TRUE) {
			msg->setID(GenerateNextCommandID());
		}
		conMgr->sendLocalCommandDirect(msg, 0xff ^ (1 << msg->getPlayerID()));
		msg->detach();

		m_lastKeepAliveSendTime = curTime;
	}
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/DisconnectManager_populateDisconnectScreen_Thunk.cpp
// ?populateDisconnectScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z present-unmatched
void DisconnectManager::populateDisconnectScreen(ConnectionManager *conMgr) {
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		UnicodeString name = conMgr->getPlayerName(i);
		Int slot = translatedSlotPosition(i, conMgr->getLocalPlayerID());
		if (slot != -1) {
			TheDisconnectMenu->setPlayerName(slot, name);

			Int numVotes = countVotesForPlayer(i);
			TheDisconnectMenu->updateVotes(slot, numVotes);
		}
	}
}

// ?translatedSlotPosition@DisconnectManager@@IAEHHH@Z present-unmatched
Int DisconnectManager::translatedSlotPosition(Int slot, Int localSlot) {
	if (slot < localSlot) {
		return slot;
	}

	if (slot == localSlot) {
		return -1;
	}

	return (slot - 1);
}

// ?untranslatedSlotPosition@DisconnectManager@@IAEHHH@Z present-unmatched
Int DisconnectManager::untranslatedSlotPosition(Int slot, Int localSlot) {
	if (slot == -1) {
		return localSlot;
	}

	if (slot < localSlot) {
		return slot;
	}

	return (slot + 1);
}

void DisconnectManager::resetPlayerTimeouts(ConnectionManager *conMgr) {
	// reset the player timeouts.
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		Int slot = translatedSlotPosition(i, conMgr->getLocalPlayerID());
		if (slot != -1) {
			resetPlayerTimeout(slot);
		}
	}
}

void DisconnectManager::resetPlayerTimeout(Int slot) {
	m_playerTimeouts[slot] = timeGetTime();
}

// ?resetPacketRouterTimeout@DisconnectManager@@IAEXXZ present-unmatched
void DisconnectManager::resetPacketRouterTimeout() {
	m_packetRouterTimeout = timeGetTime();
}

// BFME calls a free function to take the disconnect screen down, not
// TheDisconnectMenu->hideScreen(): retail's call site sets up no `this`, and the
// menu pointer is loaded inside the callee at 0x0050E5A0 instead. Its retail
// name is unknown, so this one is descriptive.
extern void HideDisconnectWindow(void);

// BFME-only, no ZH counterpart: the disconnect screen comes down here.
// processDisconnectScreenOff calls it unconditionally, and the DISCONNECTSCREENOFF
// sender at 0x00663A60 pairs with it on the outgoing side.
void DisconnectManager::turnOffScreen(Int localSlot) {
	if (m_disconnectState == DISCONNECTSTATETYPE_SCREENOFF) {
		return;
	}

	HideDisconnectWindow();
	m_disconnectState = DISCONNECTSTATETYPE_SCREENOFF;

	// Clear this player's whole column of votes.
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		m_playerVotes[i][localSlot].vote = FALSE;
	}

	m_timeOfDisconnectScreenOn = 0;
}

// BFME's show-screen helper is called with NO receiver: it loads
// TheDisconnectMenu itself and creates the DisconnectScreen.apt layout
// internally, so the reference's TheDisconnectMenu->showScreen() passes a `this'
// retail does not. BFME also makes no hidePacketRouterTimeout call here at all.
extern void bfmeShowDisconnectScreen(void);				///< retail 0x0050e9a0

struct BfmeDisconnectScreenFields
{
	char m_unreconstructed_00[0x0C];
	Int m_disconnectState;						///< retail this+0x0c
	Int m_lastKeepAliveSendTime;					///< retail this+0x10
	char m_unreconstructed_14[0x258 - 0x14];
	Int m_haveNotifiedOtherPlayersOfCurrentFrame;			///< retail this+0x258
	Int m_timeOfDisconnectScreenOn;					///< retail this+0x25c
};

// ?turnOnScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z
void DisconnectManager::turnOnScreen(ConnectionManager *conMgr) {
	BfmeDisconnectScreenFields *self = (BfmeDisconnectScreenFields *)this;

	bfmeShowDisconnectScreen();
	self->m_disconnectState = DISCONNECTSTATETYPE_SCREENON;
	self->m_lastKeepAliveSendTime = -1;
	populateDisconnectScreen(conMgr);
	resetPlayerTimeouts(conMgr);

	self->m_haveNotifiedOtherPlayersOfCurrentFrame = FALSE;

	self->m_timeOfDisconnectScreenOn = timeGetTime();
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/DisconnectManager_disconnectPlayer_Thunk.cpp
// ?disconnectPlayer@DisconnectManager@@IAEXHPAVConnectionManager@@@Z present-unmatched
void DisconnectManager::disconnectPlayer(Int slot, ConnectionManager *conMgr) {
	DEBUG_LOG(("DisconnectManager::disconnectPlayer - Disconnecting slot number %d on frame %d\n", slot, TheGameLogic->getFrame()));
	DEBUG_ASSERTCRASH((slot >= 0) && (slot < MAX_SLOTS), ("Attempting to disconnect an invalid slot number"));
	if ((slot < 0) || (slot >= (MAX_SLOTS))) {
		return;
	}

	if (TheGameInfo)
	{
		GameSlot *gSlot = TheGameInfo->getSlot( slot );
		if (gSlot)
		{
			gSlot->markAsDisconnected();
		}
	}

	Int transSlot = translatedSlotPosition(slot, conMgr->getLocalPlayerID());

	if (transSlot != -1) {
		// Ignore any disconnect commands that tell us to disconnect ourselves.

		// Get the disconnecting player off the disconnect window.
		UnicodeString uname = conMgr->getPlayerName(slot);
		TheRecorder->logPlayerDisconnect(uname, slot);
		TheDisconnectMenu->removePlayer(transSlot, uname);

		PlayerLeaveCode retcode = conMgr->disconnectPlayer(slot);
		DEBUG_ASSERTCRASH((retcode != PLAYERLEAVECODE_UNKNOWN), ("Invalid player leave code"));

		if (retcode == PLAYERLEAVECODE_PACKETROUTER) {
			DEBUG_LOG(("DisconnectManager::disconnectPlayer - disconnecting player was packet router.\n"));

			conMgr->resendPendingCommands();
		}
	}
}

void DisconnectManager::sendDisconnectCommand(Int slot, ConnectionManager *conMgr) {
	DEBUG_LOG(("DisconnectManager::sendDisconnectCommand - Sending disconnect command for slot number %d\n", slot));
	DEBUG_ASSERTCRASH((slot >= 0) && (slot < MAX_SLOTS), ("Attempting to send a disconnect command for an invalid slot number"));
	if ((slot < 0) || (slot >= (MAX_SLOTS))) {
		return;
	}

	UnsignedInt disconnectFrame = getMaxDisconnectFrame();

	// Need to do the NetDisconnectPlayerCommandMsg creation and sending here.
	NetDisconnectPlayerCommandMsg *msg = newInstance(NetDisconnectPlayerCommandMsg);
	msg->setDisconnectSlot(slot);
	msg->setDisconnectFrame(disconnectFrame);
	msg->setPlayerID(conMgr->getLocalPlayerID());
	if (DoesCommandRequireACommandID(msg->getNetCommandType())) {
		msg->setID(GenerateNextCommandID());
	}

	conMgr->sendLocalCommand(msg);

	DEBUG_LOG(("DisconnectManager::sendDisconnectCommand - Sending disconnect command for slot number %d for frame %d\n", slot, disconnectFrame));

	msg->detach();
}

void DisconnectManager::sendVoteCommand(Int slot, ConnectionManager *conMgr) {
	NetDisconnectVoteCommandMsg *msg = newInstance(NetDisconnectVoteCommandMsg);

	msg->setPlayerID(conMgr->getLocalPlayerID());
	msg->setSlot(slot);
	msg->setVoteFrame(TheGameLogic->getFrame());
	if (DoesCommandRequireACommandID(msg->getNetCommandType()) == TRUE) {
		msg->setID(GenerateNextCommandID());
	}

	conMgr->sendLocalCommandDirect(msg, 0xff & ~(1 << conMgr->getLocalPlayerID()));

	msg->detach();
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/DisconnectManager_voteForPlayerDisconnect_Thunk.cpp
// ?voteForPlayerDisconnect@DisconnectManager@@QAEXHPAVConnectionManager@@@Z present-unmatched
void DisconnectManager::voteForPlayerDisconnect(Int slot, ConnectionManager *conMgr) {
	Int transSlot = untranslatedSlotPosition(slot, conMgr->getLocalPlayerID());

	if (m_playerVotes[transSlot][conMgr->getLocalPlayerID()].vote == FALSE) {
		m_playerVotes[transSlot][conMgr->getLocalPlayerID()].vote = TRUE;

		sendVoteCommand(transSlot, conMgr);

		// we use the game logic frame cause we might not have sent out our own disconnect frame yet.
		applyDisconnectVote(transSlot, TheGameLogic->getFrame(), conMgr->getLocalPlayerID(), conMgr);
	}
}

// ?recalculatePacketRouterIndex@DisconnectManager@@IAEXPAVConnectionManager@@@Z present-unmatched
void DisconnectManager::recalculatePacketRouterIndex(ConnectionManager *conMgr) {
	Int currentPacketRouterSlot = conMgr->getPacketRouterSlot();
	m_currentPacketRouterIndex = 0;
	while ((currentPacketRouterSlot != conMgr->getPacketRouterFallbackSlot(m_currentPacketRouterIndex)) && (m_currentPacketRouterIndex < MAX_SLOTS)) {
		++m_currentPacketRouterIndex;
	}
	DEBUG_ASSERTCRASH((m_currentPacketRouterIndex < MAX_SLOTS), ("Invalid packet router index"));
}

// BFME asks TWO more questions per slot before it will hold that slot to the
// frame check. Both are per-slot predicates on the connection manager that the
// reference class does not declare, and both are shape-only names: one reads the
// state word at conMgr+0x12080 and answers whether it is in range, the other
// answers true immediately for the local slot at conMgr+0x12028. The reference
// copy checks only connected-and-in-game, so it holds slots to the frame check
// that retail excludes.
class BfmeSlotStateConnectionManager
{
public:
	Bool _bfme_slotStateInRange( Int slot );			///< retail ILT 0x000486b2
	Bool _bfme_slotIsLocalOrLive( Int slot );			///< retail ILT 0x0001f136
};

struct BfmeDisconnectFrameFields
{
	char m_unreconstructed_000[0x230];
	Int m_disconnectFrames[MAX_SLOTS];				///< retail this+0x230
	Bool m_disconnectFramesReceived[MAX_SLOTS];			///< retail this+0x250
};

// ?allOnSameFrame@DisconnectManager@@IAE_NPAVConnectionManager@@@Z
Bool DisconnectManager::allOnSameFrame(ConnectionManager *conMgr) {
	BfmeDisconnectFrameFields *self = (BfmeDisconnectFrameFields *)this;
	BfmeSlotStateConnectionManager *slots = (BfmeSlotStateConnectionManager *)conMgr;

	Bool retval = TRUE;
	for (Int i = 0; (i < MAX_SLOTS) && (retval == TRUE); ++i) {
		Int transSlot = translatedSlotPosition(i, conMgr->getLocalPlayerID());
		if (transSlot == -1) {
			continue;
		}
		if ((conMgr->isPlayerConnected(i) == TRUE) && (isPlayerInGame(transSlot, conMgr) == TRUE)
				&& (slots->_bfme_slotStateInRange(i) == FALSE) && slots->_bfme_slotIsLocalOrLive(i)) {
			// ok, i is someone who is in the game and hasn't timed out yet or been voted out.
			if (self->m_disconnectFramesReceived[i] == FALSE) {
				// we don't know what frame they are on yet.
				retval = FALSE;
			}
			if ((self->m_disconnectFramesReceived[i] == TRUE) && (self->m_disconnectFrames[conMgr->getLocalPlayerID()] != self->m_disconnectFrames[i])) {
				// We know their frame, but they aren't on the same frame as us.
				retval = FALSE;
			}
		}
	}
	return retval;
}

Bool DisconnectManager::isLocalPlayerNextPacketRouter(ConnectionManager *conMgr) {
	UnsignedInt localSlot = conMgr->getLocalPlayerID();
	UnsignedInt packetRouterSlot = conMgr->getPacketRouterSlot();
	Int transSlot = translatedSlotPosition(packetRouterSlot, localSlot);

	// A connected peer can still be ineligible after a vote, timeout, or leave-state transition.
	while ((transSlot != -1)
		&& ((isPlayerInGame(transSlot, conMgr) == FALSE)
			|| ((BFMEConnectionManager *)conMgr)->isPlayerSlotActive(packetRouterSlot))) {
		packetRouterSlot = conMgr->getNextPacketRouterSlot(packetRouterSlot);
		if ((packetRouterSlot >= MAX_SLOTS) || (packetRouterSlot < 0)) {
			// don't know who the next packet router is going to be,
			// so this game is not going to go anywhere anymore.
			DEBUG_CRASH(("no more players left to be the packet router, this shouldn't happen."));
			return FALSE;
		}
		transSlot = translatedSlotPosition(packetRouterSlot, localSlot);
	}

	if (packetRouterSlot == localSlot) {
		return TRUE;
	}

	return FALSE;
}

// BFME measures this against m_networkDisconnectScreenNotifyTime rather than the
// reference's m_networkPlayerTimeoutTime, and compares the elapsed time directly
// instead of forming the reference's signed remainder.
Bool DisconnectManager::hasPlayerTimedOut(Int slot) {
	if (slot == -1) {
		return FALSE;
	}

	if (TheGlobalData->m_networkDisconnectScreenNotifyTime
		<= (timeGetTime() - m_playerTimeouts[slot])) {
		return TRUE;
	}
	return FALSE;
}

// this function assumes that we are the packet router. (or at least that 
// we will be after everyone is getting disconnected)
// BFME: DESTROYPLAYER enum is 11 (0x0b), not ZH's 8; no setExecutionFrame.
// True body @ 0x66B550 (159B); drift 0x9F2463 is a mislocated neighbor.
void DisconnectManager::sendPlayerDestruct(Int slot, ConnectionManager *conMgr) {
	UnsignedShort currentID = 0;
	if (DoesCommandRequireACommandID((NetCommandType)11))
	{
		currentID = GenerateNextCommandID();
	}

	NetDestroyPlayerCommandMsg *netmsg = newInstance(NetDestroyPlayerCommandMsg);	
	netmsg->setPlayerID(conMgr->getLocalPlayerID());
	netmsg->setID(currentID);
	netmsg->setPlayerIndex(slot);
	conMgr->sendLocalCommandDirect(netmsg, 0xff);
	netmsg->detach();
}

// the 'slot' variable is supposed to be a translated slot position. (translated slot meaning
// that it is the player's position in the disconnect menu)
Bool DisconnectManager::isPlayerVotedOut(Int slot, ConnectionManager *conMgr) {
	if (slot == -1) {
		// we can't vote out ourselves.
		return FALSE;
	}
	Int transSlot = untranslatedSlotPosition(slot, conMgr->getLocalPlayerID());
	Int numVotes = countVotesForPlayer(transSlot, conMgr);
	if (numVotes >= getVotesNeededToKick(transSlot, conMgr)) {
		return TRUE;
	}
	return FALSE;
}

UnsignedInt DisconnectManager::getMaxDisconnectFrame() {
	UnsignedInt retval = 0;
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_disconnectFrames[i] > retval) {
			retval = m_disconnectFrames[i];
		}
	}
	return retval;
}

Bool DisconnectManager::isPlayerInGame(Int slot, ConnectionManager *conMgr) {
	Int transSlot = untranslatedSlotPosition(slot, conMgr->getLocalPlayerID());
	DEBUG_ASSERTCRASH((transSlot >= 0) && (transSlot < MAX_SLOTS), ("invalid slot number"));
	if (((transSlot < 0) || (transSlot >= MAX_SLOTS)) || conMgr->isPlayerConnected(transSlot) == FALSE) {
		return FALSE;
	}
	
	if (isPlayerVotedOut(slot, conMgr) == TRUE) {
		return FALSE;
	}
	
	if (hasPlayerTimedOut(slot) == TRUE) {
		return FALSE;
	}

	return TRUE;
}

void DisconnectManager::playerHasAdvancedAFrame(Int slot, UnsignedInt frame) {
	// if they have advanced beyond the frame they had been previously disconnecting on.
	if (frame >= m_disconnectFrames[slot]) {
		m_disconnectFrames[slot] = frame; // just in case we get a disconnect frame command after this is called.
		m_disconnectFramesReceived[slot] = FALSE;
	}
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/DisconnectManagerCountVotesForPlayerThunk.cpp
// ?countVotesForPlayer@DisconnectManager@@IAEHH@Z present-unmatched
Int DisconnectManager::countVotesForPlayer(Int slot) {
	if ((slot < 0) || (slot >= MAX_SLOTS)) {
		return 0;
	}

	Int retval = 0;
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		// using TheGameLogic->getFrame() cause we might not have sent our disconnect frame yet.
		if ((m_playerVotes[slot][i].vote == TRUE) && (m_playerVotes[slot][i].frame == TheGameLogic->getFrame())) {
			++retval;
		}
	}

	return retval;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/DisconnectManager_resetPlayersVotes_Thunk.cpp
// ?resetPlayersVotes@DisconnectManager@@IAEXHIPAVConnectionManager@@@Z present-unmatched
void DisconnectManager::resetPlayersVotes(Int playerID, UnsignedInt frame, ConnectionManager *conMgr) {
	DEBUG_LOG(("DisconnectManager::resetPlayersVotes - resetting player %d's votes on frame %d\n", playerID, frame));

	// we need to reset this player's votes that happened before or on the given frame.
	for(Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_playerVotes[i][playerID].frame <= frame) {
			DEBUG_LOG(("DisconnectManager::resetPlayersVotes - resetting player %d's vote for player %d from frame %d on frame %d\n", playerID, i, m_playerVotes[i][playerID].frame, frame));
			m_playerVotes[i][playerID].vote = FALSE;
		}
	}

	Int numVotes = countVotesForPlayer(playerID);
	DEBUG_LOG(("DisconnectManager::resetPlayersVotes - after adjusting votes, player %d has %d votes\n", playerID, numVotes));
	Int transSlot = translatedSlotPosition(playerID, conMgr->getLocalPlayerID());
	if (transSlot != -1) {
		TheDisconnectMenu->updateVotes(transSlot, numVotes);
	}
}
