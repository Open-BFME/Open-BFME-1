// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DIN_ADDR=in_addr /MD /EHsc /Iinputs/reference/shims/nat /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: NAT.cpp /////////////////////////////////////////////////////////////////////////////////
// Author: Bryan Cleveland April 2002
// Props to Steve Tall for figuring all the NAT and Firewall behavior patterns out, making my job
// a LOT easier.
// Desc:   Resolves NAT'd IPs and port numbers for the other players in a game.
///////////////////////////////////////////////////////////////////////////////////////////////////

// This unit's GameSlot view defines setIP inline at another offset than
// retail's 0x000C8DB0 (+0x2C) and emits that COMDAT copy; rename it so only
// retail-equal copies carry the name. Inlined calls are unchanged.
#define setIP setIP_LocalView
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/NAT.h"
#include "GameNetwork/Transport.h"
#include "GameNetwork/NetworkDefs.h"
#include "GameClient/EstablishConnectionsMenu.h"
#include "GameNetwork/NetworkInterface.h"
#include "GameNetwork/GameInfo.h"
#include "GameNetwork/GameSpy/PeerThread.h"   // TU-scoped shim: BFME PeerRequest is 0x194, not 0x190 (and see the AsciiString shim)
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/GSConfig.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

/*
 * In case you're wondering, we do this weird connection pairing scheme
 * to speed up the negotiation process, especially in cases where there
 * are 4 or more players (nodes).  Take for example an 8 player game...
 * In an 8 player game there are 28 connections that need to be negotiated,
 * doing this pairing scheme thing, we can make those 28 connections in the
 * time it would normally take to make 7 connections.  Since each connection
 * could potentially take several seconds, this can be a HUGE time savings.

 * Right now you're probably wondering who this Bryan Cleveland guy is.
 * He's the network coder that got fired when this didn't work.

 * In case you're wondering, this did end up working and Bryan left by
 * his own choice.
 */
//										m_connectionPairs[num nodes]	[round]			 [node index]
/* static */ Int NAT::m_connectionPairs[MAX_SLOTS-1][MAX_SLOTS-1][MAX_SLOTS] = 
{
	{	// 2 nodes
		//	node 0	node 1	node 2	node 3	node 4	node 5	node 6	node 7
		{			1,			0,			-1,			-1,			-1,			-1,			-1,			-1},	// round 0
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 1
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 2
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 3
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 4
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 5
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1}		// round 6
	},
	{	// 3 nodes
		//	node 0	node 1	node 2	node 3	node 4	node 5	node 6	node 7
		{			1,			0,			-1,			-1,			-1,			-1,			-1,			-1},	// round 0
		{			2,			-1,			0,			-1,			-1,			-1,			-1,			-1},	// round 1
		{			-1,			2,			1,			-1,			-1,			-1,			-1,			-1},	// round 2
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 3
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 4
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 5
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1}		// round 6
	},
	{	// 4 nodes
		//	node 0	node 1	node 2	node 3	node 4	node 5	node 6	node 7
		{			1,			0,			3,			2,			-1,			-1,			-1,			-1},	// round 0
		{			2,			3,			0,			1,			-1,			-1,			-1,			-1},	// round 1
		{			3,			2,			1,			0,			-1,			-1,			-1,			-1},	// round 2
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 3
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 4
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 5
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1}		// round 6
	},
	{	// 5 nodes
		//	node 0	node 1	node 2	node 3	node 4	node 5	node 6	node 7
		{			2,			4,			0,			-1,			1,			-1,			-1,			-1},	// round 0
		{			-1,			3,			4,			1,			2,			-1,			-1,			-1},	// round 1
		{			3,			2,			1,			0,			-1,			-1,			-1,			-1},	// round 2
		{			4,			-1,			3,			2,			0,			-1,			-1,			-1},	// round 3
		{			1,			0,			-1,			4,			3,			-1,			-1,			-1},	// round 4
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 5
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1}		// round 6
	},
	{	// 6 nodes
		//	node 0	node 1	node 2	node 3	node 4	node 5	node 6	node 7
		{			3,			5,			4,			0,			2,			1,			-1,			-1},	// round 0
		{			2,			4,			0,			5,			1,			3,			-1,			-1},	// round 1
		{			4,			3,			5,			1,			0,			2,			-1,			-1},	// round 2
		{			1,			0,			3,			2,			5,			4,			-1,			-1},	// round 3
		{			5,			2,			1,			4,			3,			0,			-1,			-1},	// round 4
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1},	// round 5
		{			-1,			-1,			-1,			-1,			-1,			-1,			-1,			-1}		// round 6
	},
	{	// 7 nodes
		//	node 0	node 1	node 2	node 3	node 4	node 5	node 6	node 7
		{			-1,			6,			5,			4,			3,			2,			1,			-1},	// round 0
		{			2,			-1,			0,			6,			5,			4,			3,			-1},	// round 1
		{			4,			3,			-1,			1,			0,			6,			5,			-1},	// round 2
		{			6,			5,			4,			-1,			2,			1,			0,			-1},	// round 3
		{			1,			0,			6,			5,			-1,			3,			2,			-1},	// round 4
		{			3,			2,			1,			0,			6,			-1,			4,			-1},	// round 5
		{			5,			4,			3,			2,			1,			0,			-1,			-1}		// round 6
	},
	{	// 8 nodes
		//	node 0	node 1	node 2	node 3	node 4	node 5	node 6	node 7
		{			4,			5,			6,			7,			0,			1,			2,			3},		// round 0
		{			5,			4,			7,			6,			1,			0,			3,			2},		// round 1
		{			3,			6,			5,			0,			7,			2,			1,			4},		// round 2
		{			2,			7,			0,			5,			6,			3,			4,			1},		// round 3
		{			6,			3,			4,			1,			2,			7,			0,			5},		// round 4
		{			1,			0,			3,			2,			5,			4,			7,			6},		// round 5
		{			7,			2,			1,			4,			3,			6,			5,			0}		// round 6
	}
};

/* static */ Int NAT::m_timeBetweenRetries = 500; // .5 seconds between retries sounds good to me.
/* static */ time_t NAT::m_manglerRetryTimeInterval = 300; // sounds good to me.
/* static */ Int NAT::m_maxAllowedManglerRetries = 25; // works for me.
/* static */ time_t NAT::m_keepaliveInterval = 15000; // 15 seconds between keepalive packets seems good.
/* static */ time_t NAT::m_timeToWaitForPort = 15000; // wait for 15 seconds for the other player's port number.
/* static */ time_t NAT::m_timeForRoundTimeout = 15000; // wait for at most 15 seconds for each connection round to finish.

NAT *TheNAT = NULL;

// ??1NAT@@UAE@XZ present-unmatched
NAT::~NAT() {
}

// if we're already finished, change to being idle
// if we are negotiating now, check to see if this round is done
// if it is, check to see if we're completely done with all rounds.
// if we are, set state to be done.
// if not go on to the next connection round.
// if we are negotiating still, call the connection update
// check to see if this connection is done for us, or if it has failed.
enum { MS_TO_WAIT_FOR_STATS = 5000 };
// The former NATUpdateThunk claim was a GameSpy chat filter timeout; NAT::update remains unmatched.
// ?update@NAT@@ present-unmatched
NATStateType NAT::update() {
	static UnsignedInt s_startStatWaitTime = 0;
	if (m_NATState == NATSTATE_DONE) {
		m_NATState = NATSTATE_IDLE;
	} else if (m_NATState == NATSTATE_WAITFORSTATS) {
		// check for all stats
		Bool gotAllStats = TRUE;
		Bool timedOut = FALSE;
		for (Int i=0; i<MAX_SLOTS; ++i)
		{
			const GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(i);
			if (slot && slot->isHuman())
			{
				PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(slot->getProfileID());
				if (stats.id == 0)
				{
					gotAllStats = FALSE;
					//DEBUG_LOG(("Failed to find stats for %ls(%d)\n", slot->getName().str(), slot->getProfileID()));
				}
			}
		}
		// check for timeout.  Timing out is not a fatal error - it just means we didn't get the other
		// player's stats.  We'll see 0/0 as his record, but we can still play him just fine.
		UnsignedInt now = timeGetTime();
		if (now > s_startStatWaitTime + MS_TO_WAIT_FOR_STATS)
		{
			DEBUG_LOG(("Timed out waiting for stats.  Let's just start the dang game.\n"));
			timedOut = TRUE;
		}
		if (gotAllStats || timedOut)
		{
			m_NATState = NATSTATE_DONE;
			TheEstablishConnectionsMenu->endMenu();
			if (TheFirewallHelper != NULL) {
				delete TheFirewallHelper;
				TheFirewallHelper = NULL;
			}
		}
	} else if (m_NATState == NATSTATE_DOCONNECTIONPATHS) {
		if (allConnectionsDoneThisRound() == TRUE) {
			// we finished this round, move on to the next one.
			++m_connectionRound;
//			m_roundTimeout = timeGetTime() + TheGameSpyConfig->getRoundTimeout();
			m_roundTimeout = timeGetTime() + m_timeForRoundTimeout;
			DEBUG_LOG(("NAT::update - done with connection round, moving on to round %d\n", m_connectionRound));

			// we finished that round, now check to see if we're done, or if there are more rounds to go.
			if (allConnectionsDone() == TRUE) {
				// we're all done, time to go back home.
				m_NATState = NATSTATE_WAITFORSTATS;

				// 2/19/03 BGC - we have successfully negotaited a NAT thingy, so our behavior must be correct
				// so therefore we don't need to refresh our NAT even if we previously thought we had to.
				TheFirewallHelper->flagNeedToRefresh(FALSE);

				s_startStatWaitTime = timeGetTime();
				DEBUG_LOG(("NAT::update - done with all connections, woohoo!!\n"));
				/*
				m_NATState = NATSTATE_DONE;
				TheEstablishConnectionsMenu->endMenu();
				if (TheFirewallHelper != NULL) {
					delete TheFirewallHelper;
					TheFirewallHelper = NULL;
				}
				*/
			} else {
				doThisConnectionRound();
			}
		}
		NATConnectionState state = connectionUpdate();

		if (timeGetTime() > m_roundTimeout) {
			DEBUG_LOG(("NAT::update - round timeout expired\n"));
			setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_FAILED);
			notifyUsersOfConnectionFailed(m_localNodeNumber);
		}

		if (state == NATCONNECTIONSTATE_FAILED) {
			// if we fail
			m_NATState = NATSTATE_FAILED;
			TheEstablishConnectionsMenu->endMenu();
			if (TheFirewallHelper != NULL) {
				// we failed NAT negotiation, perhaps we need to redetect our firewall settings.
				// We don't trust the user to do it for themselves so we force them to do it next time
				// the log in.
				// 2/19/03 - ok, we don't want to do this right away, if the user tries to play in another game
				// before they log out and log back in the game won't have a chance at working.
				// so we need to simply flag it so that when they log out the firewall behavior gets blown away.
				TheFirewallHelper->flagNeedToRefresh(TRUE);
//				TheWritableGlobalData->m_firewallBehavior = FirewallHelperClass::FIREWALL_TYPE_UNKNOWN;
//				TheFirewallHelper->writeFirewallBehavior();

				delete TheFirewallHelper;
				TheFirewallHelper = NULL;
			}
			// we failed to connect, so we don't have to pass on the transport to the network.
			if (m_transport != NULL) {
				delete m_transport;
				m_transport = NULL;
			}
		}
	}
	return m_NATState;
}


// update transport, check for PROBE packets from our target.
// check to see if its time to PROBE our target
// MANGLER:
// if we are talking to the mangler, check to see if we got a response
// if we didn't get a response, check to see if its time to send another packet to it
// ?connectionUpdate@NAT@@IAE?AW4NATConnectionState@@XZ: retail body is in NAT_connectionUpdate.cpp

// this is the function that starts the NAT/firewall negotiation process.
// after calling this, you should call the update function untill it returns
// NATSTATE_DONE.
// ?establishConnectionPaths@NAT@@QAEXXZ: retail body is in NAT_establishConnectionPaths.cpp

Int NAT::getSlotPort(Int slot) {
//	return (slot + m_startingPortNumber);
	if (m_slotList[slot] != NULL) {
		return m_slotList[slot]->getPort();
	}
	return 0;
}

// NAT::generatePortNumbers: retail body 0x00670A30 lives in NAT_generatePortNumbers.cpp.

// ?getTransport@NAT@@QAEPAVTransport@@XZ present-unmatched
Transport * NAT::getTransport() {
	return m_transport;
}

// figure out which port I'll be using.
// send the port number to our target for this round.
// init the m_connectionStates for all players.
// ?doThisConnectionRound@NAT@@IAEXXZ: retail body is in NAT_doThisConnectionRound_BFME.cpp

template<class CharT>
class NATProbeStringBase
{
public:
	NATProbeStringBase() : m_data(NULL) {}
	NATProbeStringBase(const CharT *text);
	~NATProbeStringBase() { releaseBuffer(); }

protected:
	void releaseBuffer();
	CharT *m_data;
};

class NATProbeString : public NATProbeStringBase<char>
{
public:
	NATProbeString() {}
	NATProbeString(const char *text) : NATProbeStringBase<char>(text) {}

	void __cdecl format(NATProbeString format, ...);

	const unsigned char *str() const
	{
		return m_data ? reinterpret_cast<unsigned char *>(m_data) + 8 : reinterpret_cast<const unsigned char *>("");
	}

	Int getLength() const
	{
		return m_data ? *reinterpret_cast<const UnsignedShort *>(reinterpret_cast<unsigned char *>(m_data) + 4) : 0;
	}
};

struct NATProbeAddress
{
	NATProbeAddress(UnsignedInt newIP, UnsignedShort newPort) : ip(newIP), port(newPort) {}

	UnsignedInt ip;
	UnsignedShort port;
};

class NATProbeTransport
{
public:
	void queueSend(const NATProbeAddress &address, const unsigned char *data, Int length);
	void doSend();
};

// ?sendAProbe@NAT@@IAEXIGH@Z
void NAT::sendAProbe(UnsignedInt ip, UnsignedShort port, Int fromNode)
{
	NATProbeString str;
	str.format("PROBE%d", fromNode);

	(*reinterpret_cast<NATProbeTransport **>(reinterpret_cast<unsigned char *>(this) + 4))->queueSend(
		NATProbeAddress(ip, port), str.str(), str.getLength() + 1);
	(*reinterpret_cast<NATProbeTransport **>(reinterpret_cast<unsigned char *>(this) + 4))->doSend();
}

// find the next mangled source port, and then send it to the other player.
// if this requires talking to the mangler, we'll have to wait till a later update
// to send our port out.
void NAT::sendMangledSourcePort() {
	UnsignedShort sourcePort = getSlotPort(m_connectionNodes[m_localNodeNumber].m_slotIndex);

	FirewallHelperClass::tFirewallBehaviorType fwType = m_slotList[m_connectionNodes[m_localNodeNumber].m_slotIndex]->getNATBehavior();
	GameSlot *targetSlot = m_slotList[m_connectionNodes[m_targetNodeNumber].m_slotIndex];
	DEBUG_ASSERTCRASH(targetSlot != NULL, ("NAT::sendMangledSourcePort - targetSlot is NULL"));
	if (targetSlot == NULL) {
		DEBUG_LOG(("NAT::sendMangledSourcePort - targetSlot is NULL, failed this connection\n"));
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_FAILED);
		return;
	}

	GameSlot *localSlot = m_slotList[m_connectionNodes[m_localNodeNumber].m_slotIndex];
	DEBUG_ASSERTCRASH(localSlot != NULL, ("NAT::sendMangledSourcePort - localSlot is NULL, WTF?"));
	if (localSlot == NULL) {
		DEBUG_LOG(("NAT::sendMangledSourcePort - localSlot is NULL, failed this connection\n"));
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_FAILED);
		return;
	}

	// check to see if the target and I are behind the same NAT
	if (targetSlot->getIP() == localSlot->getIP()) {
#if defined(DEBUG_LOGGING)
		UnsignedInt localip = localSlot->getIP();
		UnsignedInt targetip = targetSlot->getIP();
#endif
		DEBUG_LOG(("NAT::sendMangledSourcePort - target and I are behind the same NAT, no mangling\n"));
		DEBUG_LOG(("NAT::sendMangledSourcePort - I am %ls, target is %ls, my IP is %d.%d.%d.%d, target IP is %d.%d.%d.%d\n", localSlot->getName().str(), targetSlot->getName().str(),
								localip >> 24, (localip >> 16) & 0xff, (localip >> 8) & 0xff, localip & 0xff,
								targetip >> 24, (targetip >> 16) & 0xff, (targetip >> 8) & 0xff, targetip & 0xff));

		sendMangledPortNumberToTarget(sourcePort, targetSlot);
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT);
		// In case you're wondering, we don't set the m_previousSourcePort here because this will be a different source
		// address than what other nodes will likely see (unless of course there are more than
		// two of us behind the same NAT, but we won't worry about that cause theres no mangling
		// in that case anyways)
		return;
	}

	// check to see if we are NAT'd at all.
	if ((fwType == 0) || (fwType == FirewallHelperClass::FIREWALL_TYPE_SIMPLE)) {
		// no mangling, just return the source port
		DEBUG_LOG(("NAT::sendMangledSourcePort - no mangling, just using the source port\n"));
		sendMangledPortNumberToTarget(sourcePort, targetSlot);
		m_previousSourcePort = sourcePort;
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT);
		return;
	}

	// check to see if our NAT keeps the same source port for different destinations.
	// if this is the case, and we've already worked out what our mangled port number is
	// then we don't have to figure it out again.
	if (((fwType & FirewallHelperClass::FIREWALL_TYPE_DESTINATION_PORT_DELTA) == 0) &&
			((fwType & FirewallHelperClass::FIREWALL_TYPE_SMART_MANGLING) == 0)) {
		DEBUG_LOG(("NAT::sendMangledSourcePort - our firewall doesn't NAT based on destination address, checking for old connections from this address\n"));
		if (m_previousSourcePort != 0) {
			DEBUG_LOG(("NAT::sendMangledSourcePort - Previous source port was %d, using that one\n", m_previousSourcePort));
			sendMangledPortNumberToTarget(m_previousSourcePort, targetSlot);
			m_slotList[m_connectionNodes[m_localNodeNumber].m_slotIndex]->setPort(m_previousSourcePort);
			setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT);
			return;
		} else {
			DEBUG_LOG(("NAT::sendMangledSourcePort - Previous source port not found\n"));
		}
	}

	// At this point we know that our NAT uses some kind of relative port mapping scheme, so we
	// need to talk to the mangler to find out where we are now so we can find out where we'll be on the
	// next port allocation.

	// get the address of the mangler we need to talk to.
	Char manglerName[256];
	FirewallHelperClass::getManglerName(1, manglerName);
	DEBUG_LOG(("NAT::sendMangledSourcePort - about to call gethostbyname for mangler at %s\n", manglerName));
	struct hostent *hostInfo = gethostbyname(manglerName);

	if (hostInfo == NULL) {
		DEBUG_LOG(("NAT::sendMangledSourcePort - gethostbyname failed for mangler address %s\n", manglerName));
		// can't find the mangler, we're screwed so just send the source port.
		sendMangledPortNumberToTarget(sourcePort, targetSlot);
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT);
		return;
	}

	memcpy(&m_manglerAddress, &(hostInfo->h_addr_list[0][0]), 4);
	m_manglerAddress = ntohl(m_manglerAddress);
	DEBUG_LOG(("NAT::sendMangledSourcePort - mangler %s address is %d.%d.%d.%d\n", manglerName, 
							m_manglerAddress >> 24, (m_manglerAddress >> 16) & 0xff, (m_manglerAddress >> 8) & 0xff, m_manglerAddress & 0xff));

	DEBUG_LOG(("NAT::sendMangledSourcePort - NAT behavior = 0x%08x\n", fwType));

//	m_manglerRetryTime = TheGameSpyConfig->getRetryInterval() + timeGetTime();
	m_manglerRetryTime = m_manglerRetryTimeInterval + timeGetTime();
	m_manglerRetries = 0;

	if (TheFirewallHelper != NULL) {
		m_spareSocketPort = TheFirewallHelper->getNextTemporarySourcePort(0);
		TheFirewallHelper->openSpareSocket(m_spareSocketPort);
		TheFirewallHelper->sendToManglerFromPort(m_manglerAddress, m_spareSocketPort, m_packetID);
//		m_manglerRetryTime = TheGameSpyConfig->getRetryInterval() + timeGetTime();
		m_manglerRetryTime = m_manglerRetryTimeInterval + timeGetTime();
	}

	setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_WAITINGFORMANGLERRESPONSE);
}

void NAT::processManglerResponse(UnsignedShort mangledPort) {
	DEBUG_LOG(("NAT::processManglerResponse - Work out what my NAT'd port will be\n"));

	GameSlot *targetSlot = m_slotList[m_connectionNodes[m_targetNodeNumber].m_slotIndex];
	DEBUG_ASSERTCRASH(targetSlot != NULL, ("NAT::processManglerResponse - targetSlot is NULL"));
	if (targetSlot == NULL) {
		DEBUG_LOG(("NAT::processManglerResponse - targetSlot is NULL, failed this connection\n"));
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_FAILED);
		return;
	}

	Short delta = TheGlobalData->m_firewallPortAllocationDelta;
	UnsignedShort sourcePort = getSlotPort(m_connectionNodes[m_localNodeNumber].m_slotIndex);
	UnsignedShort returnPort = 0;

	FirewallHelperClass::tFirewallBehaviorType fwType = m_slotList[m_connectionNodes[m_localNodeNumber].m_slotIndex]->getNATBehavior();

	if ((fwType & FirewallHelperClass::FIREWALL_TYPE_SIMPLE_PORT_ALLOCATION) != 0) {
		returnPort = mangledPort + delta;
	} else {
		// to steal a line from Steve Tall...
		// Rats. It's a relative mangler. This is much harder. Damn NAT32 guy.
		if (delta == 100) {
			// Special NAT32 section.
			// NAT32 mangles source UDP port by ading 1700 + 100*NAT table index.
			returnPort = mangledPort - m_spareSocketPort;
			returnPort -= 1700;

			returnPort += delta;
			returnPort += sourcePort;
			returnPort += 1700;

		} else if (delta == 0) {
			returnPort = sourcePort;
		} else {
			returnPort = mangledPort / delta;
			returnPort = returnPort * delta;

			returnPort += (sourcePort % delta);
			returnPort += delta;
		}
	}

	// This bit is probably doomed.
	if (returnPort > 65535) {
		returnPort -= 65535;
	}
	if (returnPort < 1024) {
		returnPort += 1024;
	}

	DEBUG_LOG(("NAT::processManglerResponse - mangled port is %d\n", returnPort));
	m_previousSourcePort = returnPort;

	sendMangledPortNumberToTarget(returnPort, targetSlot);
	// BFME stores the mangled port on the local GameSlot here, where the
	// reference records it in m_sourcePorts[m_targetNodeNumber].
	m_slotList[m_connectionNodes[m_localNodeNumber].m_slotIndex]->setPort(returnPort);
	if (targetSlot->getPort() == 0) {
		// we haven't got the target's mangled port number yet, wait for it.
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT);
	} else {
		// in this case we should have already sent a PROBE, so we'll just change the state
		// and leave it at that.
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_WAITINGFORRESPONSE);
	}
}

// check to see if we've completed all the rounds
// this is kind of a cheesy way to check, but it works.
Bool NAT::allConnectionsDone() {
	if (m_numNodes == 2) {
		if (m_connectionRound >= 1) {
			return TRUE;
		}
	} else if (m_numNodes == 3) {
		if (m_connectionRound >= 3) {
			return TRUE;
		}
	} else if (m_numNodes == 4) {
		if (m_connectionRound >= 3) {
			return TRUE;
		}
	} else if (m_numNodes == 5) {
		if (m_connectionRound >= 5) {
			return TRUE;
		}
	} else if (m_numNodes == 6) {
		if (m_connectionRound >= 5) {
			return TRUE;
		}
	} else if (m_numNodes == 7) {
		if (m_connectionRound >= 7) {
			return TRUE;
		}
	} else if (m_numNodes == 8) {
		if (m_connectionRound >= 7) {
			return TRUE;
		}
	}
	return FALSE;
}

Bool NAT::allConnectionsDoneThisRound() {
	Bool retval = TRUE;
	for (Int i = 0; (i < m_numNodes) && (retval == TRUE); ++i) {
		if ((m_connectionStates[i] != NATCONNECTIONSTATE_DONE) && (m_connectionStates[i] != NATCONNECTIONSTATE_FAILED)) {
			retval = FALSE;
		}
	}
	return retval;
}

// this node's connection for this round has been completed.
// ?connectionComplete@NAT@@IAEXH@Z present-unmatched
void NAT::connectionComplete(Int slotIndex) {
}

// this node's connection for this round has failed.
// ?connectionFailed@NAT@@IAEXH@Z present-unmatched
void NAT::connectionFailed(Int slotIndex) {
}

// I have been probed by the target.
void NAT::probed(Int nodeNumber) {
	GameSlot *localSlot = m_slotList[m_connectionNodes[m_localNodeNumber].m_slotIndex];
	DEBUG_ASSERTCRASH(localSlot != NULL, ("NAT::probed - localSlot is NULL, WTF?"));
	if (localSlot == NULL) {
		DEBUG_LOG(("NAT::probed - localSlot is NULL, failed this connection\n"));
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_FAILED);
		return;
	}

	if (m_beenProbed == FALSE) {
		m_beenProbed = TRUE;
		DEBUG_LOG(("NAT::probed - just got probed for the first time.\n"));
		if ((localSlot->getNATBehavior() & FirewallHelperClass::FIREWALL_TYPE_NETGEAR_BUG) != 0) {
			DEBUG_LOG(("NAT::probed - we have a NETGEAR and we were just probed for the first time\n"));
			GameSlot *targetSlot = m_slotList[m_connectionNodes[m_targetNodeNumber].m_slotIndex];
			DEBUG_ASSERTCRASH(targetSlot != NULL, ("NAT::probed - targetSlot is NULL"));
			if (targetSlot == NULL) {
				DEBUG_LOG(("NAT::probed - targetSlot is NULL, failed this connection\n"));
				setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_FAILED);
				return;
			}

			// BFME addition: do nothing if we are still waiting on the mangler.
			if (m_connectionStates[m_localNodeNumber] == NATCONNECTIONSTATE_WAITINGFORMANGLERRESPONSE) {
				return;
			}

			if (targetSlot->getPort() == 0) {
				setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT);
				DEBUG_LOG(("NAT::probed - still waiting for mangled port\n"));
			} else {
				DEBUG_LOG(("NAT::probed - sending a probe to %ls\n", targetSlot->getName().str()));
				sendAProbe(targetSlot->getIP(), targetSlot->getPort(), m_localNodeNumber);
				notifyTargetOfProbe(targetSlot);
				setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_WAITINGFORRESPONSE);
			}
		}
	}
}

// got the mangled port for our target for this round.
// BFME adds two guards this reference body lacks, and it is 24 bytes away from
// matching because of them. The first wraps targetSlot->setPort(mangledPort) in
// a test of a byte at NAT+0xC4. The second is the same early-out that probed()
// has: when m_connectionStates[m_localNodeNumber] is
// NATCONNECTIONSTATE_WAITINGFORMANGLERRESPONSE it skips the whole probe section.
// Landing it needs NAT+0xC4 named first.
// ?gotMangledPort@NAT@@IAEXHG@Z: retail body is in NAT_gotMangledPort_Thunk.cpp

void NAT::gotInternalAddress(Int nodeNumber, UnsignedInt address) {
	GameSlot *targetSlot = m_slotList[m_connectionNodes[nodeNumber].m_slotIndex];
	DEBUG_ASSERTCRASH(targetSlot != NULL, ("NAT::gotInternalAddress - targetSlot is NULL"));
	if (targetSlot == NULL) {
		return;
	}

	GameSlot *localSlot = m_slotList[m_connectionNodes[m_localNodeNumber].m_slotIndex];
	DEBUG_ASSERTCRASH(localSlot != NULL, ("NAT::gotInternalAddress - localSlot is NULL, WTF?"));
	if (localSlot == NULL) {
		return;
	}

	if (nodeNumber != m_targetNodeNumber) {
		DEBUG_LOG(("NAT::gotInternalAddress - got a internal address for someone that isn't my target. node = %d, target node = %d\n", nodeNumber, m_targetNodeNumber));
		return;
	}

	if (localSlot->getIP() == targetSlot->getIP()) {
		// we have the same IP address, i.e. we are behind the same NAT.
		// I need to talk directly to his internal address.
		DEBUG_LOG(("NAT::gotInternalAddress - target and local players have same external address, using internal address.\n"));
		targetSlot->setIP(address); // use the slot's internal address from now on
	}
}

// The ledger used to claim this at 0x006718BC via a MASM dump. That address is
// 28 bytes INTO sendMangledPortNumberToTarget, whose body starts at 0x006718A0
// with an SEH prologue and ends in `ret 8` for its two arguments. The real body
// is 0x00671100: it starts with its own SEH prologue, ends in `ret 4` for the
// single GameSlot*, and it is the function that references "PROBED%d". A byte
// dump matches whatever bytes it was cut from, so the wrong claim verified
// cleanly -- and comparing the C++ against those wrong bytes is what produced
// the old note here about BFME's PeerRequest being a dword larger than the
// reference's. It is not; the layout is the reference's.

// ?notifyTargetOfProbe@NAT@@IAEXPAVGameSlot@@@Z present-unmatched
// 374 bytes of the right instructions in the right order except for two local
// schedule swaps: retail writes the EH object slot before taking the
// temporary's address (mov [esp+0x18],esp / mov ecx,esp; this source emits them
// the other way round), and it pushes both of id's assign pointers before
// loading its `this`. Everything between re-converges. Three things had to be
// right to get this far, and all three are worth keeping:
//   - PeerRequest is 0x194, not the reference's 0x190 (see the PeerThread shim);
//   - AsciiString's const char* constructor has to be out of line, or the
//     format temporary cannot be built in its pushed argument slot;
//   - retail passes format's AsciiString overload. Both overloads exist in
//     BFME, so the by-value one is a source choice, not a missing declaration.
// peerRequestType is 13 here and 13 again in notifyUsersOfConnectionFailed,
// where the reference writes PEERREQUEST_UTMPLAYER (12) in both. Two
// independent sites agreeing is what settles it: BFME's enum gained a value
// ahead of UTMPLAYER rather than both call sites switching to UTMROOM. See the
// PeerThread shim.
// ?notifyTargetOfProbe@NAT@@IAEXPAVGameSlot@@@Z: retail body is in NAT_notifyTargetOfProbe.cpp


// byte-exact reconstruction: game/GameEngine/Source/Common/NAT_notifyUsersOfConnectionDoneMethodThunk.cpp
// ?notifyUsersOfConnectionDone@NAT@@IAEXH@Z present-unmatched
void NAT::notifyUsersOfConnectionDone(Int nodeIndex) {
	GameSlot *localSlot = m_slotList[m_connectionNodes[m_localNodeNumber].m_slotIndex];
	DEBUG_ASSERTCRASH(localSlot != NULL, ("NAT::notifyUsersOfConnectionDone - localSlot is NULL, WTF?"));
	if (localSlot == NULL) {
		DEBUG_LOG(("NAT::notifyUsersOfConnectionDone - localSlot is NULL, failed this connection\n"));
		setConnectionState(m_localNodeNumber, NATCONNECTIONSTATE_FAILED);
		return;
	}

	PeerRequest req;
	AsciiString options;
	options.format("CONNDONE%d %d", nodeIndex, m_localNodeNumber);

	req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
	req.UTM.isStagingRoom = TRUE;
	req.id = "NAT";
	AsciiString names;
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		if (m_connectionNodes[m_localNodeNumber].m_slotIndex == i) {
			continue;
		}

		if ((m_slotList[i] == NULL) || (m_slotList[i]->isHuman() == FALSE)) {
			continue;
		}

		AsciiString name;
		name.translate(m_slotList[i]->getName());
		if (names.isNotEmpty())
		{
			names.concat(',');
		}
		names.concat(name);
	}
	req.nick = names.str();
	req.options = options.str();

	DEBUG_LOG(("NAT::notifyUsersOfConnectionDone - sending %s to %s\n", options.str(), names.str()));
	TheGameSpyPeerMessageQueue->addRequest(req);
}

// ?notifyUsersOfConnectionFailed@NAT@@IAEXH@Z present-unmatched
// Real body 0x006715C0, 581 bytes -- unblocked by removing the setGameOptions
// dump that claimed 383 bytes from the middle of it. Same remaining blocker as
// notifyTargetOfProbe: retail writes the EH object slot before taking the
// format temporary's address and this source emits those two the other way
// round. Five source arrangements were tried against that pair (explicit vs
// implicit conversion, declaring the const char* overload away, swapping the
// PeerRequest and AsciiString declarations); none moves it, so it is not
// reachable from the source side.
// ?notifyUsersOfConnectionFailed@NAT@@IAEXH@Z: retail body is in NAT_notifyUsersOfConnectionFailed.cpp

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/NATSendMangledPortNumberToTargetThunk.cpp
// ?sendMangledPortNumberToTarget@NAT@@IAEXGPAVGameSlot@@@Z present-unmatched
void NAT::sendMangledPortNumberToTarget(UnsignedShort mangledPort, GameSlot *targetSlot) {
	PeerRequest req;
	AsciiString options;
	options.format("PORT%d %d %08X", m_localNodeNumber, mangledPort, m_localIP);

	req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
	req.UTM.isStagingRoom = TRUE;
	req.id = "NAT/";
	AsciiString hostName;
	hostName.translate(targetSlot->getName());
	req.nick = hostName.str();
	req.options = options.str();
	DEBUG_LOG(("NAT::sendMangledPortNumberToTarget - sending \"%s\" to %s\n", options.str(), hostName.str()));
	TheGameSpyPeerMessageQueue->addRequest(req);
}

void NAT::processGlobalMessage(Int slotNum, const char *options) {
	const char *ptr = options;
	// skip preceding whitespace.
	while (isspace(*ptr)) {
		++ptr;
	}
	DEBUG_LOG(("NAT::processGlobalMessage - got message from slot %d, message is \"%s\"\n", slotNum, ptr));
	if (!strncmp(ptr, "PROBED", strlen("PROBED"))) {
		// format: PROBED<node number>
		// a probe has been sent at us, if we are waiting because of a netgear or something, we
		// should start sending our own probes.
		Int node = atoi(ptr + strlen("PROBED"));
		if (node == m_targetNodeNumber) {
			// make sure we're being probed by who we're supposed to be probed by.
			probed(node);
		} else {
			DEBUG_LOG(("NAT::processGlobalMessage - probed by node %d, not our target\n", node));
		}
	} else if (!strncmp(ptr, "CONNDONE", strlen("CONNDONE"))) {
		// format: CONNDONE<node number>
		// we should get the node number of the player who's connection is done from the options
		// and mark that down as part of the connectionStates.
		const char *c = ptr + strlen("CONNDONE");
/*		while (*c != ' ') {
			++c;
		}
		while (*c == ' ') {
			++c;
		}
*/		Int node;
		Int sendingNode;
		sscanf(c, "%d %d\n", &node, &sendingNode);

		// BFME keeps the pairing cursor at +0xB0; the reference NAT layout places
		// the same field at +0xC0 after its larger connection-state arrays.
		const Int connectionPairIndex = *reinterpret_cast<const Int *>(
			reinterpret_cast<const UnsignedByte *>(this) + 0xB0);
		if (m_connectionPairs[connectionPairIndex][m_connectionRound][node] == sendingNode) {
//			Int node = atoi(ptr + strlen("CONNDONE"));
			DEBUG_LOG(("NAT::processGlobalMessage - got a CONNDONE message for node %d\n", node));
			if ((node >= 0) && (node <= m_numNodes)) {
				DEBUG_LOG(("NAT::processGlobalMessage - node %d's connection is complete, setting connection state to done\n", node));
				setConnectionState(node, NATCONNECTIONSTATE_DONE);
			}
		} else {
			DEBUG_LOG(("NAT::processGlobalMessage - got a connection done message that isn't from this round. node: %d sending node: %d\n", node, sendingNode));
		}
	} else if (!strncmp(ptr, "CONNFAILED", strlen("CONNFAILED"))) {
		// format: CONNFAILED<node number>
		// we should get the node number of the player who's connection failed from the options
		// and mark that down as part of the connectionStates.
		Int node = atoi(ptr + strlen("CONNFAILED"));
		if ((node >= 0) && (node < m_numNodes)) {
			DEBUG_LOG(("NAT::processGlobalMessage - node %d's connection failed, setting connection state to failed\n", node));
			setConnectionState(node, NATCONNECTIONSTATE_FAILED);
			m_NATState = NATSTATE_FAILED;
		}
	} else if (!strncmp(ptr, "PORT", strlen("PORT"))) {
		// format: PORT<node number> <port number> <internal IP>
		// we should get the node number and the mangled port number of the client we
		// are supposed to be communicating with and start probing them. No, that was not
		// meant to be a phallic reference, you sicko.
		const char *c = ptr + strlen("PORT");
		Int node = atoi(c);
		while (*c != ' ') {
			++c;
		}
		while (*c == ' ') {
			++c;
		}
		UnsignedInt intport = 0;
		UnsignedInt addr = 0;
		sscanf(c, "%d %X", &intport, &addr);
		UnsignedShort port = (UnsignedShort)intport;

		DEBUG_LOG(("NAT::processGlobalMessage - got port message from node %d, port: %d, internal address: %d.%d.%d.%d\n", node, port,
								addr >> 24, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr & 0xff));

		if ((node >= 0) && (node < m_numNodes)) {
			if (port < 1024) {
				// it has to be less than 65535 cause its a short duh.
				DEBUG_ASSERTCRASH(port >= 1024, ("Was passed an invalid port number"));
				port += 1024;
			}
			gotInternalAddress(node, addr);
			gotMangledPort(node, port);
		}
	}
}

void NAT::setConnectionState(Int nodeNumber, NATConnectionState state) {
	m_connectionStates[nodeNumber] = state;

	if (nodeNumber != m_localNodeNumber) {
		return;
	}

	// if this is the case we are starting a new round and we don't know
	// who we're connecting to yet.
	if (m_localNodeNumber == m_targetNodeNumber) {
		return;
	}

	// if this is the start of a new connection round we don't have a
	// target yet.
	if (m_targetNodeNumber == -1) {
		return;
	}

	// find the menu slot of the target node.
	Int slotIndex = m_connectionNodes[m_targetNodeNumber].m_slotIndex;
	Int slot = 0;
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (m_slotList[i] != NULL) {
			if (m_slotList[i]->isHuman()) {
				if (i != m_connectionNodes[m_localNodeNumber].m_slotIndex) {
					if (i == slotIndex) {
					 break;
					}
					++slot;
				}
			}
		}
	}
	if (i == MAX_SLOTS) {
		DEBUG_ASSERTCRASH(i < MAX_SLOTS, ("Didn't find the node number in the slot list"));
		return;
	}
	TheEstablishConnectionsMenu->setPlayerStatus(slot, state);
}
