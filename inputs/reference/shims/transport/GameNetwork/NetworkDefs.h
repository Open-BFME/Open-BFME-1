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

// TU-scoped stand-in for the real GameNetwork/NetworkDefs.h for Transport.cpp,
// carrying BFME's four-byte TransportMessageHeader and BFME's
// NetCommandType numbering. Recovered from the type-to-string mapper at
// 0x00683020, which names 24 of the values outright; the ordering below is
// exactly what that function tests.
//
// Three edits separate it from the reference, and each one corroborates a
// finding made elsewhere in this tree:
//   * RUNAHEADMETRICS and RUNAHEAD (ZH 6 and 7) are gone, replaced by the
//     GameSpy stats-authkey pair -- BFME has no run-ahead command at all, which
//     is why its delay is a frame ceiling instead (reverse/network_delay).
//   * PACKETROUTERQUERY and PACKETROUTERACK are gone, which is the same edit
//     that made DisconnectManager 36 bytes smaller (reference/shims/disconnectmanager).
//   * MANGLERQUERY, MANGLERRESPONSE and FRAMERESENDREQUEST are gone, and
//     REQUESTPLAYERLEAVE, INFORMPLAYERLEAVEFRAME and REQUESTFRAMEDATA are new --
//     the three that carry BFME's frame-data resend handshake.
//
// Values 22 and 23 are not named by the mapper; ZH has DISCONNECTSTART there and
// they are left as placeholders rather than guessed at.


#ifndef __NETWORKDEFS_H
#define __NETWORKDEFS_H

#include "Lib/BaseType.h"
#include "Common/MessageStream.h"

static const Int WOL_NAME_LEN = 64;

/// Max number of commands per frame
static const Int MAX_COMMANDS = 256;

extern Int MAX_FRAMES_AHEAD;
extern Int MIN_RUNAHEAD;

// FRAME_DATA_LENGTH needs to be MAX_FRAMES_AHEAD+1 because a player on a different
// computer can send commands for a frame that is one beyond twice the max runahead.
extern Int FRAME_DATA_LENGTH;
extern Int FRAMES_TO_KEEP;

// This is the connection numbering: 1-8 are for players, 9 is a broadcast con.
enum ConnectionNumbers
{
	MAX_PLAYER = 7,			// The index of the highest possible player number.  This is 0 based, so the most players allowed in a game is MAX_PLAYER+1.
	NUM_CONNECTIONS
};

static const Int MAX_SLOTS = MAX_PLAYER+1;

// UDP (8 bytes) + IP header (28 bytes) = 36 bytes total.  We want a total packet size of 512, so 512 - 36 = 476
static const Int MAX_PACKET_SIZE = 476;

/**
 * Command packet - contains frame #, total # of commands, and each command.  This is what gets sent
 * to each player every frame
 */
#define MAX_MESSAGE_LEN 1024
#define MAX_MESSAGES 128
static const Int numCommandsPerCommandPacket = (MAX_MESSAGE_LEN - sizeof(UnsignedInt) - sizeof(UnsignedShort))/sizeof(GameMessage);
#pragma pack(push, 1)
struct CommandPacket
{
	UnsignedInt m_frame;
	UnsignedShort m_numCommands;
	unsigned char m_commands[numCommandsPerCommandPacket * sizeof(GameMessage)];
};
#pragma pack(pop)

#define MAX_TRANSPORT_STATISTICS_SECONDS 30

#pragma pack(push, 1)
struct TransportMessageHeader
{
	// BFME's header is the CRC and nothing else -- four bytes. Three independent
	// reads of the retail transport agree: queueSend copies the payload to
	// msg+4 (lea edi,[edx+4]), the m_outBuffer stride is 0x40E = 4 + 1024 + 4 +
	// 4 + 2, and doSend passes length+4 to UDP::Write as
	// `length + sizeof(TransportMessageHeader)`. The magic number the reference
	// stamps here is gone, along with the isGeneralsPacket check that read it.
	UnsignedInt crc;											///< packet-level CRC (must be first in packet)
};
#pragma pack(pop)

/**
 * Transport message - encapsulating info kept by the transport layer about each
 * packet.  These structs make up the in/out buffers at the transport layer.
 */
/**
 * BFME passes an address and port around as one object rather than as two
 * scalars: Transport::init takes a pointer to this (ret 4, not ret 8) and
 * dereferences [ptr] as the address and [ptr+4] as a 16-bit port, and
 * Transport::queueSend does the same. NAT::sendAProbe builds one on its own
 * stack to make the call. The layout is pinned by those three; the *name* is
 * not -- a POD with no RTTI leaves nothing to recover it from, so this one is
 * inferred and the mangled names that embed it are inferred with it.
 */
#pragma pack(push, 1)
struct TransportAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TransportMessage
{
	TransportMessageHeader header;
	UnsignedByte data[MAX_MESSAGE_LEN];
	Int length;
	UnsignedInt addr;
	UnsignedShort port;
};
#pragma pack(pop)

#if defined(_DEBUG) || defined(_INTERNAL)
#pragma pack(push, 1)
struct DelayedTransportMessage
{
	UnsignedInt deliveryTime;
	TransportMessage message;
};
#pragma pack(pop)
#endif

/**
 * Message types
 */
enum NetMessageFlag {
	MSG_ACK = 1,
	MSG_NEEDACK = 2,
	MSG_SEQUENCED = 4,
	MSG_SUPERCEDING = 8
};
typedef UnsignedByte NetMessageFlags;

enum NetCommandType {
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2,
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_GAMECOMMAND = 4,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY = 5,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY = 6,
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE = 7,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_DESTROYPLAYER = 11,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTCHAT = 13,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_PROGRESS = 15,
	NETCOMMANDTYPE_LOADCOMPLETE = 16,
	NETCOMMANDTYPE_TIMEOUTSTART = 17,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILE = 19,
	NETCOMMANDTYPE_FILEANNOUNCE = 20,
	NETCOMMANDTYPE_FILEPROGRESS = 21,

	// Disconnect menu command section. 22 and 23 are unnamed by the mapper.
	NETCOMMANDTYPE_DISCONNECTSTART = 23,
	NETCOMMANDTYPE_DISCONNECTKEEPALIVE = 24,
	NETCOMMANDTYPE_DISCONNECTPLAYER = 25,
	NETCOMMANDTYPE_DISCONNECTVOTE = 26,
	NETCOMMANDTYPE_DISCONNECTFRAME = 27,
	NETCOMMANDTYPE_DISCONNECTSCREENOFF = 28,
	NETCOMMANDTYPE_DISCONNECTEND,

	NETCOMMANDTYPE_MAX
};

enum NetLocalStatus {
	NETLOCALSTATUS_PREGAME = 0,
	NETLOCALSTATUS_INGAME,
	NETLOCALSTATUS_LEAVING,
	NETLOCALSTATUS_LEFT,
	NETLOCALSTATUS_POSTGAME
};

enum PlayerLeaveCode {
	PLAYERLEAVECODE_CLIENT = 0,
	PLAYERLEAVECODE_LOCAL,
	PLAYERLEAVECODE_PACKETROUTER,
	PLAYERLEAVECODE_UNKNOWN
};

// Magic number for identifying a Generals packet.
static const UnsignedShort GENERALS_MAGIC_NUMBER = 0xF00D;

// The number of fps history entries.
//static const Int NETWORK_FPS_HISTORY_LENGTH = 30;

// The number of ping history entries.
//static const Int NETWORK_LATENCY_HISTORY_LENGTH = 200;

// The number of miliseconds between run ahead metrics things
//static const Int NETWORK_RUN_AHEAD_METRICS_TIME = 5000;

// The number of cushion values to keep.
//static const Int NETWORK_CUSHION_HISTORY_LENGTH = 10;

// The amount of slack in the run ahead value.  This is the percentage of the calculated run ahead that is added.
//static const Int NETWORK_RUN_AHEAD_SLACK = 20;

// The number of seconds between when the connections to each player send a keep-alive packet.
// This should be less than 30 just to keep firewall ports open.
//static const Int NETWORK_KEEPALIVE_DELAY = 20;

// The number of milliseconds between when the game gets stuck on a frame for a network stall and
// and when the disconnect dialog comes up.
//static const Int NETWORK_DISCONNECT_TIME = 5000;

// The number of miliseconds between when a player's last disconnect keep alive command
// was recieved and when they are considered disconnected from the game.
//static const Int NETWORK_PLAYER_TIMEOUT_TIME = 60000;

// The base port number used for the transport socket.  A players slot number is added to this
// value to get their actual port number.
static const Int NETWORK_BASE_PORT_NUMBER = 8088;

// the singleton
class NetworkInterface;
extern NetworkInterface *TheNetwork;


#endif
