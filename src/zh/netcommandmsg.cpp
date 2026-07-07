// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

#include "GameNetwork/NetCommandMsg.h"
#include "Common/GameState.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"

/**
 * Base constructor
 */
// ??0NetCommandMsg@@QAE@XZ present-unmatched
NetCommandMsg::NetCommandMsg() 
{
	//Added By Sadullah Nader
	//Initializations inserted
	m_executionFrame = 0;
	m_id = 0;
	m_playerID = 0;

	//
	m_timestamp = 0;
	m_referenceCount = 1; // start this off as 1.  This means that an "attach" is implied by creating a NetCommandMsg object.
	m_commandType = NETCOMMANDTYPE_UNKNOWN;
}

/**
 * Destructor
 */
// ??1NetCommandMsg@@MAE@XZ present-unmatched
NetCommandMsg::~NetCommandMsg() {
}

/**
 * Adds one to the reference count.
 */
// ?attach@NetCommandMsg@@QAEXXZ present-unmatched
void NetCommandMsg::attach() {
	++m_referenceCount;
}

/**
 * Subtracts one from the reference count. If the reference count is 0, the this object is destroyed.
 */
// ?detach@NetCommandMsg@@QAEXXZ present-unmatched
void NetCommandMsg::detach() {
	--m_referenceCount;
	if (m_referenceCount == 0) {
		deleteInstance();
		return;
	}
	DEBUG_ASSERTCRASH(m_referenceCount > 0, ("Invalid reference count for NetCommandMsg")); // Just to make sure...
	if (m_referenceCount < 0) {
		deleteInstance();
	}
}

/**
 * Returns the value by which this type of message should be sorted.
 */
// ?getSortNumber@NetCommandMsg@@UAEHXZ present-unmatched
Int NetCommandMsg::getSortNumber() {
	return m_id;
}

//-------------------------------
// NetGameCommandMsg
//-------------------------------

/**
 * Constructor with no argument, sets everything to default values.
 */
// ??0NetGameCommandMsg@@ present-unmatched
NetGameCommandMsg::NetGameCommandMsg() : NetCommandMsg() {
	//Added By Sadullah Nader
	//Initializations inserted
	m_argSize = 0;
	m_numArgs = 0;
	//

	m_type = (GameMessage::Type)0;
	m_commandType = NETCOMMANDTYPE_GAMECOMMAND;
	m_argList = NULL;
	m_argTail = NULL;
}

/**
 * Constructor with a GameMessage argument. Sets member variables appropriately for this GameMessage.
 * Also copies all the arguments.
 */
// ??0NetGameCommandMsg@@ present-unmatched
NetGameCommandMsg::NetGameCommandMsg(GameMessage *msg) : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_GAMECOMMAND;

	m_type = msg->getType();
	Int count = msg->getArgumentCount();
	for (Int i = 0; i < count; ++i) {
		addArgument(msg->getArgumentDataType(i), *(msg->getArgument(i)));
	}
}

/**
 * Destructor
 */
// ??1NetGameCommandMsg@@MAE@XZ present-unmatched
NetGameCommandMsg::~NetGameCommandMsg() {
	GameMessageArgument *arg = m_argList;
	while (arg != NULL) {
		m_argList = m_argList->m_next;
		arg->deleteInstance();
		arg = m_argList;
	}
}

/**
 * Add an argument to this command.
 */
// ?addArgument@NetGameCommandMsg@@QAEXW4GameMessageArgumentDataType@@TGameMessageArgumentType@@@Z present-unmatched
void NetGameCommandMsg::addArgument(const GameMessageArgumentDataType type, GameMessageArgumentType arg) 
{
	if (m_argTail == NULL) {
		m_argList = newInstance(GameMessageArgument);	
		m_argTail = m_argList;
		m_argList->m_data = arg;
		m_argList->m_type = type;
		m_argList->m_next = NULL;
		return;
	}

	GameMessageArgument *newArg = newInstance(GameMessageArgument);
	newArg->m_data = arg;
	newArg->m_type = type;
	newArg->m_next = NULL;
	m_argTail->m_next = newArg;
	m_argTail = newArg;
}

// here's where we figure out which slot corresponds to which player
static Int indexFromMask(UnsignedInt mask)
{
	Player *player = NULL;
	Int i;

	for( i = 0; i < MAX_PLAYER_COUNT; i++ )
	{
		player = ThePlayerList->getNthPlayer( i );
		if( player && player->getPlayerMask() == mask )
			return i;
	}  // end for i

	return -1;
}

/**
 * Construct a new GameMessage object from the data in this object.
 */
// ?constructGameMessage@NetGameCommandMsg@@QAEPAVGameMessage@@XZ present-unmatched
GameMessage *NetGameCommandMsg::constructGameMessage() 
{
	GameMessage *retval = newInstance(GameMessage)(m_type);

	AsciiString name;
	name.format("player%d", getPlayerID());
	retval->friend_setPlayerIndex( ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name))->getPlayerIndex());
//	retval->friend_setPlayerIndex(indexFromMask(ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name))->getPlayerMask()));

	GameMessageArgument *arg = m_argList;
	while (arg != NULL) {
//		retval->appendGenericArgument(arg->m_data);
		if (arg->m_type == ARGUMENTDATATYPE_INTEGER) {
			retval->appendIntegerArgument(arg->m_data.integer);
		} else if (arg->m_type == ARGUMENTDATATYPE_REAL) {
			retval->appendRealArgument(arg->m_data.real);
		} else if (arg->m_type == ARGUMENTDATATYPE_BOOLEAN) {
			retval->appendBooleanArgument(arg->m_data.boolean);
		} else if (arg->m_type == ARGUMENTDATATYPE_OBJECTID) {
			retval->appendObjectIDArgument(arg->m_data.objectID);
		} else if (arg->m_type == ARGUMENTDATATYPE_DRAWABLEID) {
			retval->appendDrawableIDArgument(arg->m_data.drawableID);
		} else if (arg->m_type == ARGUMENTDATATYPE_TEAMID) {
			retval->appendTeamIDArgument(arg->m_data.teamID);
		} else if (arg->m_type == ARGUMENTDATATYPE_LOCATION) {
			retval->appendLocationArgument(arg->m_data.location);
		} else if (arg->m_type == ARGUMENTDATATYPE_PIXEL) {
			retval->appendPixelArgument(arg->m_data.pixel);
		} else if (arg->m_type == ARGUMENTDATATYPE_PIXELREGION) {
			retval->appendPixelRegionArgument(arg->m_data.pixelRegion);
		} else if (arg->m_type == ARGUMENTDATATYPE_TIMESTAMP) {
			retval->appendTimestampArgument(arg->m_data.timestamp);
		} else if (arg->m_type == ARGUMENTDATATYPE_WIDECHAR) {
			retval->appendWideCharArgument(arg->m_data.wChar);
		}
		arg = arg->m_next;
	}
	return retval;
}

/**
 * Sets the type of game message
 */
// ?setGameMessageType@NetGameCommandMsg@@QAEXW4Type@GameMessage@@@Z present-unmatched
void NetGameCommandMsg::setGameMessageType(GameMessage::Type type) {
	m_type = type;
}

// ?getContentsAsAsciiString@NetGameCommandMsg@@UAE?AVAsciiString@@XZ present-unmatched
AsciiString NetGameCommandMsg::getContentsAsAsciiString(void)
{
	AsciiString ret;
	//AsciiString tmp;
	ret.format("Type:%s", GameMessage::getCommandTypeAsAsciiString((GameMessage::Type)m_type).str());

	return ret;
}

//-------------------------
// NetAckBothCommandMsg
//-------------------------
/**
 * Constructor.  Sets the member variables according to the given message.
 */
// ??0NetAckBothCommandMsg@@ present-unmatched
NetAckBothCommandMsg::NetAckBothCommandMsg(NetCommandMsg *msg) : NetCommandMsg() {
	m_commandID = msg->getID();
	m_commandType = NETCOMMANDTYPE_ACKBOTH;
	m_originalPlayerID = msg->getPlayerID();
}

/**
 * Constructor.  Sets the member variables to default values.
 */
// ??0NetAckBothCommandMsg@@ present-unmatched
NetAckBothCommandMsg::NetAckBothCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_ACKBOTH;
}

/**
 * Destructor.
 */
// ??1NetAckBothCommandMsg@@MAE@XZ present-unmatched
NetAckBothCommandMsg::~NetAckBothCommandMsg() {
}

/**
 * Returns the command ID of the command being ack'd.
 */
// ?getCommandID@NetAckBothCommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetAckBothCommandMsg::getCommandID() {
	return m_commandID;
}

/**
 * Set the command ID of the command being ack'd.
 */
// ?setCommandID@NetAckBothCommandMsg@@QAEXG@Z present-unmatched
void NetAckBothCommandMsg::setCommandID(UnsignedShort commandID) {
	m_commandID = commandID;
}

/**
 * Get the player id of the player who originally sent the command.
 */
// ?getOriginalPlayerID@NetAckBothCommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetAckBothCommandMsg::getOriginalPlayerID() {
	return m_originalPlayerID;
}

/**
 * Set the player id of the player who originally sent the command.
 */
// ?setOriginalPlayerID@NetAckBothCommandMsg@@QAEXE@Z present-unmatched
void NetAckBothCommandMsg::setOriginalPlayerID(UnsignedByte originalPlayerID) {
	m_originalPlayerID = originalPlayerID;
}

// ?getSortNumber@NetAckBothCommandMsg@@UAEHXZ present-unmatched
Int NetAckBothCommandMsg::getSortNumber() {
	return m_commandID;
}

//-------------------------
// NetAckStage1CommandMsg
//-------------------------
/**
 * Constructor.  Sets the member variables according to the given message.
 */
// ??0NetAckStage1CommandMsg@@ present-unmatched
NetAckStage1CommandMsg::NetAckStage1CommandMsg(NetCommandMsg *msg) : NetCommandMsg() {
	m_commandID = msg->getID();
	m_commandType = NETCOMMANDTYPE_ACKSTAGE1;
	m_originalPlayerID = msg->getPlayerID();
}

/**
 * Constructor.  Sets the member variables to default values.
 */
// ??0NetAckStage1CommandMsg@@ present-unmatched
NetAckStage1CommandMsg::NetAckStage1CommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_ACKSTAGE1;
}

/**
 * Destructor.
 */
// ??1NetAckStage1CommandMsg@@MAE@XZ present-unmatched
NetAckStage1CommandMsg::~NetAckStage1CommandMsg() {
}

/**
 * Returns the command ID of the command being ack'd.
 */
// ?getCommandID@NetAckStage1CommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetAckStage1CommandMsg::getCommandID() {
	return m_commandID;
}

/**
 * Set the command ID of the command being ack'd.
 */
// ?setCommandID@NetAckStage1CommandMsg@@QAEXG@Z present-unmatched
void NetAckStage1CommandMsg::setCommandID(UnsignedShort commandID) {
	m_commandID = commandID;
}

/**
 * Get the player id of the player who originally sent the command.
 */
// ?getOriginalPlayerID@NetAckStage1CommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetAckStage1CommandMsg::getOriginalPlayerID() {
	return m_originalPlayerID;
}

/**
 * Set the player id of the player who originally sent the command.
 */
// ?setOriginalPlayerID@NetAckStage1CommandMsg@@QAEXE@Z present-unmatched
void NetAckStage1CommandMsg::setOriginalPlayerID(UnsignedByte originalPlayerID) {
	m_originalPlayerID = originalPlayerID;
}

// ?getSortNumber@NetAckStage1CommandMsg@@UAEHXZ present-unmatched
Int NetAckStage1CommandMsg::getSortNumber() {
	return m_commandID;
}

//-------------------------
// NetAckStage2CommandMsg
//-------------------------
/**
 * Constructor.  Sets the member variables according to the given message.
 */
// ??0NetAckStage2CommandMsg@@ present-unmatched
NetAckStage2CommandMsg::NetAckStage2CommandMsg(NetCommandMsg *msg) : NetCommandMsg() {
	m_commandID = msg->getID();
	m_commandType = NETCOMMANDTYPE_ACKSTAGE2;
	m_originalPlayerID = msg->getPlayerID();
}

/**
 * Constructor.  Sets the member variables to default values.
 */
// ??0NetAckStage2CommandMsg@@ present-unmatched
NetAckStage2CommandMsg::NetAckStage2CommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_ACKSTAGE2;
}

/**
 * Destructor.
 */
// ??1NetAckStage2CommandMsg@@MAE@XZ present-unmatched
NetAckStage2CommandMsg::~NetAckStage2CommandMsg() {
}

/**
 * Returns the command ID of the command being ack'd.
 */
// ?getCommandID@NetAckStage2CommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetAckStage2CommandMsg::getCommandID() {
	return m_commandID;
}

/**
 * Set the command ID of the command being ack'd.
 */
// ?setCommandID@NetAckStage2CommandMsg@@QAEXG@Z present-unmatched
void NetAckStage2CommandMsg::setCommandID(UnsignedShort commandID) {
	m_commandID = commandID;
}

/**
 * Get the player id of the player who originally sent the command.
 */
// ?getOriginalPlayerID@NetAckStage2CommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetAckStage2CommandMsg::getOriginalPlayerID() {
	return m_originalPlayerID;
}

/**
 * Set the player id of the player who originally sent the command.
 */
// ?setOriginalPlayerID@NetAckStage2CommandMsg@@QAEXE@Z present-unmatched
void NetAckStage2CommandMsg::setOriginalPlayerID(UnsignedByte originalPlayerID) {
	m_originalPlayerID = originalPlayerID;
}

// ?getSortNumber@NetAckStage2CommandMsg@@UAEHXZ present-unmatched
Int NetAckStage2CommandMsg::getSortNumber() {
	return m_commandID;
}

//-------------------------
// NetFrameCommandMsg
//-------------------------
/**
 * Constructor.
 */
// ??0NetFrameCommandMsg@@QAE@XZ present-unmatched
NetFrameCommandMsg::NetFrameCommandMsg() : NetCommandMsg() {
	m_commandCount = 0;
	m_commandType = NETCOMMANDTYPE_FRAMEINFO;
}

/**
 * Destructor
 */
// ??1NetFrameCommandMsg@@MAE@XZ present-unmatched
NetFrameCommandMsg::~NetFrameCommandMsg() {
}

/**
 * Set the command count of this frame.
 */
// ?setCommandCount@NetFrameCommandMsg@@QAEXG@Z present-unmatched
void NetFrameCommandMsg::setCommandCount(UnsignedShort commandCount) {
	m_commandCount = commandCount;
}

/**
 * Return the command count of this frame.
 */
// ?getCommandCount@NetFrameCommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetFrameCommandMsg::getCommandCount() {
	return m_commandCount;
}

//-------------------------
// NetPlayerLeaveCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetPlayerLeaveCommandMsg@@QAE@XZ present-unmatched
NetPlayerLeaveCommandMsg::NetPlayerLeaveCommandMsg() : NetCommandMsg() {
	m_leavingPlayerID = 0;
	m_commandType = NETCOMMANDTYPE_PLAYERLEAVE;
}

/**
 * Destructor
 */
// ??1NetPlayerLeaveCommandMsg@@MAE@XZ present-unmatched
NetPlayerLeaveCommandMsg::~NetPlayerLeaveCommandMsg() {
}

/**
 * Get the id of the player leaving the game.
 */
// ?getLeavingPlayerID@NetPlayerLeaveCommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetPlayerLeaveCommandMsg::getLeavingPlayerID() {
	return m_leavingPlayerID;
}

/**
 * Set the id of the player leaving the game.
 */
// ?setLeavingPlayerID@NetPlayerLeaveCommandMsg@@QAEXE@Z present-unmatched
void NetPlayerLeaveCommandMsg::setLeavingPlayerID(UnsignedByte id) {
	m_leavingPlayerID = id;
}

//-------------------------
// NetRunAheadMetricsCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetRunAheadMetricsCommandMsg@@QAE@XZ present-unmatched
NetRunAheadMetricsCommandMsg::NetRunAheadMetricsCommandMsg() : NetCommandMsg() {
	m_averageLatency = 0.0;
	m_averageFps = 0;
	m_commandType = NETCOMMANDTYPE_RUNAHEADMETRICS;
}

/**
 * Destructor
 */
// ??1NetRunAheadMetricsCommandMsg@@MAE@XZ present-unmatched
NetRunAheadMetricsCommandMsg::~NetRunAheadMetricsCommandMsg() {
}

/**
 * set the average latency
 */
// ?setAverageLatency@NetRunAheadMetricsCommandMsg@@QAEXM@Z present-unmatched
void NetRunAheadMetricsCommandMsg::setAverageLatency(Real avgLat) {
	m_averageLatency = avgLat;
}

/**
 * get the average latency
 */
// ?getAverageLatency@NetRunAheadMetricsCommandMsg@@QAEMXZ present-unmatched
Real NetRunAheadMetricsCommandMsg::getAverageLatency() {
	return m_averageLatency;
}

/**
 * set the average fps
 */
// ?setAverageFps@NetRunAheadMetricsCommandMsg@@QAEXH@Z present-unmatched
void NetRunAheadMetricsCommandMsg::setAverageFps(Int fps) {
	m_averageFps = fps;
}

/**
 * get the average fps
 */
// ?getAverageFps@NetRunAheadMetricsCommandMsg@@QAEHXZ present-unmatched
Int NetRunAheadMetricsCommandMsg::getAverageFps() {
	return m_averageFps;
}

//-------------------------
// NetRunAheadCommandMsg
//-------------------------
// ??0NetRunAheadCommandMsg@@QAE@XZ present-unmatched
NetRunAheadCommandMsg::NetRunAheadCommandMsg() : NetCommandMsg() {
	m_runAhead = min(max(20, MIN_RUNAHEAD), MAX_FRAMES_AHEAD/2);
	m_frameRate = 30;
	m_commandType = NETCOMMANDTYPE_RUNAHEAD;
}

// ??1NetRunAheadCommandMsg@@MAE@XZ present-unmatched
NetRunAheadCommandMsg::~NetRunAheadCommandMsg() {
}

// ?getRunAhead@NetRunAheadCommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetRunAheadCommandMsg::getRunAhead() {
	return m_runAhead;
}

// ?setRunAhead@NetRunAheadCommandMsg@@QAEXG@Z present-unmatched
void NetRunAheadCommandMsg::setRunAhead(UnsignedShort runAhead) {
	m_runAhead = runAhead;
}

// ?getFrameRate@NetRunAheadCommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetRunAheadCommandMsg::getFrameRate() {
	return m_frameRate;
}

// ?setFrameRate@NetRunAheadCommandMsg@@QAEXE@Z present-unmatched
void NetRunAheadCommandMsg::setFrameRate(UnsignedByte frameRate) {
	m_frameRate = frameRate;
}

//-------------------------
// NetDestroyPlayerCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetDestroyPlayerCommandMsg@@QAE@XZ present-unmatched
NetDestroyPlayerCommandMsg::NetDestroyPlayerCommandMsg() : NetCommandMsg()
{
	m_playerIndex = 0;
	m_commandType = NETCOMMANDTYPE_DESTROYPLAYER;
}

/**
 * Destructor
 */
// ??1NetDestroyPlayerCommandMsg@@MAE@XZ present-unmatched
NetDestroyPlayerCommandMsg::~NetDestroyPlayerCommandMsg()
{
}

/**
 * set the CRC
 */
// ?setPlayerIndex@NetDestroyPlayerCommandMsg@@QAEXI@Z present-unmatched
void NetDestroyPlayerCommandMsg::setPlayerIndex( UnsignedInt playerIndex )
{
	m_playerIndex = playerIndex;
}

/**
 * get the average CRC
 */
// ?getPlayerIndex@NetDestroyPlayerCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetDestroyPlayerCommandMsg::getPlayerIndex( void )
{
	return m_playerIndex;
}

//-------------------------
// NetKeepAliveCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetKeepAliveCommandMsg@@QAE@XZ present-unmatched
NetKeepAliveCommandMsg::NetKeepAliveCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_KEEPALIVE;
}

// ??1NetKeepAliveCommandMsg@@MAE@XZ present-unmatched
NetKeepAliveCommandMsg::~NetKeepAliveCommandMsg() {
}

//-------------------------
// NetDisconnectKeepAliveCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetDisconnectKeepAliveCommandMsg@@QAE@XZ present-unmatched
NetDisconnectKeepAliveCommandMsg::NetDisconnectKeepAliveCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_DISCONNECTKEEPALIVE;
}

// ??1NetDisconnectKeepAliveCommandMsg@@MAE@XZ present-unmatched
NetDisconnectKeepAliveCommandMsg::~NetDisconnectKeepAliveCommandMsg() {
}

//-------------------------
// NetDisconnectPlayerCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetDisconnectPlayerCommandMsg@@QAE@XZ present-unmatched
NetDisconnectPlayerCommandMsg::NetDisconnectPlayerCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_DISCONNECTPLAYER;
	m_disconnectSlot = 0;
}

/**
 * Destructor
 */
// ??1NetDisconnectPlayerCommandMsg@@MAE@XZ present-unmatched
NetDisconnectPlayerCommandMsg::~NetDisconnectPlayerCommandMsg() {
}

/**
 * Returns the disconnecting slot number
 */
// ?getDisconnectSlot@NetDisconnectPlayerCommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetDisconnectPlayerCommandMsg::getDisconnectSlot() {
	return m_disconnectSlot;
}

/**
 * Sets the disconnecting slot number
 */
// ?setDisconnectSlot@NetDisconnectPlayerCommandMsg@@QAEXE@Z present-unmatched
void NetDisconnectPlayerCommandMsg::setDisconnectSlot(UnsignedByte slot) {
	m_disconnectSlot = slot;
}

/**
 * Sets the disconnect frame
 */
// ?setDisconnectFrame@NetDisconnectPlayerCommandMsg@@QAEXI@Z present-unmatched
void NetDisconnectPlayerCommandMsg::setDisconnectFrame(UnsignedInt frame) {
	m_disconnectFrame = frame;
}

/**
 * returns the disconnect frame
 */
// ?getDisconnectFrame@NetDisconnectPlayerCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetDisconnectPlayerCommandMsg::getDisconnectFrame() {
	return m_disconnectFrame;
}

//-------------------------
// NetPacketRouterQueryCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetPacketRouterQueryCommandMsg@@QAE@XZ present-unmatched
NetPacketRouterQueryCommandMsg::NetPacketRouterQueryCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_PACKETROUTERQUERY;
}

/**
 * Destructor
 */
// ??1NetPacketRouterQueryCommandMsg@@MAE@XZ present-unmatched
NetPacketRouterQueryCommandMsg::~NetPacketRouterQueryCommandMsg() {
}

//-------------------------
// NetPacketRouterAckCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetPacketRouterAckCommandMsg@@QAE@XZ present-unmatched
NetPacketRouterAckCommandMsg::NetPacketRouterAckCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_PACKETROUTERACK;
}

/**
 * Destructor
 */
// ??1NetPacketRouterAckCommandMsg@@MAE@XZ present-unmatched
NetPacketRouterAckCommandMsg::~NetPacketRouterAckCommandMsg() {
}

//-------------------------
// NetDisconnectChatCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetDisconnectChatCommandMsg@@QAE@XZ present-unmatched
NetDisconnectChatCommandMsg::NetDisconnectChatCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_DISCONNECTCHAT;
}

/**
 * Destructor
 */
// ??1NetDisconnectChatCommandMsg@@MAE@XZ present-unmatched
NetDisconnectChatCommandMsg::~NetDisconnectChatCommandMsg() {
}

/**
 * Set the chat text for this message.
 */
// ?setText@NetDisconnectChatCommandMsg@@QAEXVUnicodeString@@@Z present-unmatched
void NetDisconnectChatCommandMsg::setText(UnicodeString text) {
	m_text = text;
}

/**
 * Get the chat text for this message.
 */
// ?getText@NetDisconnectChatCommandMsg@@QAE?AVUnicodeString@@XZ present-unmatched
UnicodeString NetDisconnectChatCommandMsg::getText() {
	return m_text;
}

//-------------------------
// NetChatCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetChatCommandMsg@@QAE@XZ present-unmatched
NetChatCommandMsg::NetChatCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_CHAT;
	//added by Sadullah Nader
	//Initializations inserted
	m_playerMask = 0;
	//
}

/**
 * Destructor
 */
// ??1NetChatCommandMsg@@MAE@XZ present-unmatched
NetChatCommandMsg::~NetChatCommandMsg()
{
}

/**
 * Set the chat text for this message.
 */
// ?setText@NetChatCommandMsg@@QAEXVUnicodeString@@@Z present-unmatched
void NetChatCommandMsg::setText(UnicodeString text)
{
	m_text = text;
}

/**
 * Get the chat text for this message.
 */
// ?getText@NetChatCommandMsg@@QAE?AVUnicodeString@@XZ present-unmatched
UnicodeString NetChatCommandMsg::getText()
{
	return m_text;
}

/**
 * Get the bitmask of chat recipients from this message.
 */
// ?getPlayerMask@NetChatCommandMsg@@QAEHXZ present-unmatched
Int NetChatCommandMsg::getPlayerMask()
{
	return m_playerMask;
}

/**
 * Set a bitmask of chat recipients in this message.
 */
// ?setPlayerMask@NetChatCommandMsg@@QAEXH@Z present-unmatched
void NetChatCommandMsg::setPlayerMask( Int playerMask )
{
	m_playerMask = playerMask;
}

//-------------------------
// NetDisconnectVoteCommandMsg
//-------------------------
/**
 * Constructor
 */
// ??0NetDisconnectVoteCommandMsg@@QAE@XZ present-unmatched
NetDisconnectVoteCommandMsg::NetDisconnectVoteCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_DISCONNECTVOTE;
	m_slot = 0;
}

/**
 * Destructor
 */
// ??1NetDisconnectVoteCommandMsg@@MAE@XZ present-unmatched
NetDisconnectVoteCommandMsg::~NetDisconnectVoteCommandMsg() {
}

/**
 * Set the slot that is being voted for.
 */
// ?setSlot@NetDisconnectVoteCommandMsg@@QAEXE@Z present-unmatched
void NetDisconnectVoteCommandMsg::setSlot(UnsignedByte slot) {
	m_slot = slot;
}

/**
 * Get the slot that is being voted for.
 */
// ?getSlot@NetDisconnectVoteCommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetDisconnectVoteCommandMsg::getSlot() {
	return m_slot;
}

/**
 * Get the vote frame.
 */
// ?getVoteFrame@NetDisconnectVoteCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetDisconnectVoteCommandMsg::getVoteFrame() {
	return m_voteFrame;
}

/**
 * Set the vote frame.
 */
// ?setVoteFrame@NetDisconnectVoteCommandMsg@@QAEXI@Z present-unmatched
void NetDisconnectVoteCommandMsg::setVoteFrame(UnsignedInt voteFrame) {
	m_voteFrame = voteFrame;
}

//-------------------------
// NetProgressCommandMsg
//-------------------------
// ??0NetProgressCommandMsg@@QAE@XZ present-unmatched
NetProgressCommandMsg::NetProgressCommandMsg( void ) : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_PROGRESS;
	m_percent = 0;
}

// ??1NetProgressCommandMsg@@MAE@XZ present-unmatched
NetProgressCommandMsg::~NetProgressCommandMsg( void ) {}
		
// ?getPercentage@NetProgressCommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetProgressCommandMsg::getPercentage()
{
	return m_percent;
}

// ?setPercentage@NetProgressCommandMsg@@QAEXE@Z present-unmatched
void NetProgressCommandMsg::setPercentage( UnsignedByte percent )
{
	m_percent = percent;
}

//-------------------------
// NetWrapperCommandMsg
//-------------------------
// ??0NetWrapperCommandMsg@@QAE@XZ present-unmatched
NetWrapperCommandMsg::NetWrapperCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_WRAPPER;
	m_numChunks = 0;
	m_data = NULL;
	m_totalDataLength = 0;
	m_chunkNumber = 0;
	m_dataLength = 0;
	m_dataOffset = 0;
	m_wrappedCommandID = 0;
}

NetWrapperCommandMsg::~NetWrapperCommandMsg() {
	if (m_data != NULL) {
		delete m_data;
		m_data = NULL;
	}
}

// ?getData@NetWrapperCommandMsg@@QAEPAEXZ present-unmatched
UnsignedByte * NetWrapperCommandMsg::getData() {
	return m_data;
}

void NetWrapperCommandMsg::setData(UnsignedByte *data, UnsignedInt dataLength) 
{
	if (m_data != NULL) {
		delete m_data;
		m_data = NULL;
	}

	m_data = NEW UnsignedByte[dataLength];	// pool[]ify
	memcpy(m_data, data, dataLength);
	m_dataLength = dataLength;
}

// ?getDataLength@NetWrapperCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetWrapperCommandMsg::getDataLength() {
	return m_dataLength;
}

// ?getDataOffset@NetWrapperCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetWrapperCommandMsg::getDataOffset() {
	return m_dataOffset;
}

// ?setDataOffset@NetWrapperCommandMsg@@QAEXI@Z present-unmatched
void NetWrapperCommandMsg::setDataOffset(UnsignedInt offset) {
	m_dataOffset = offset;
}

// ?getChunkNumber@NetWrapperCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetWrapperCommandMsg::getChunkNumber() {
	return m_chunkNumber;
}

// ?setChunkNumber@NetWrapperCommandMsg@@QAEXI@Z present-unmatched
void NetWrapperCommandMsg::setChunkNumber(UnsignedInt chunkNumber) {
	m_chunkNumber = chunkNumber;
}

// ?getNumChunks@NetWrapperCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetWrapperCommandMsg::getNumChunks() {
	return m_numChunks;
}

// ?setNumChunks@NetWrapperCommandMsg@@QAEXI@Z present-unmatched
void NetWrapperCommandMsg::setNumChunks(UnsignedInt numChunks) {
	m_numChunks = numChunks;
}

// ?getTotalDataLength@NetWrapperCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetWrapperCommandMsg::getTotalDataLength() {
	return m_totalDataLength;
}

// ?setTotalDataLength@NetWrapperCommandMsg@@QAEXI@Z present-unmatched
void NetWrapperCommandMsg::setTotalDataLength(UnsignedInt totalDataLength) {
	m_totalDataLength = totalDataLength;
}

// ?getWrappedCommandID@NetWrapperCommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetWrapperCommandMsg::getWrappedCommandID() {
	return m_wrappedCommandID;
}

// ?setWrappedCommandID@NetWrapperCommandMsg@@QAEXG@Z present-unmatched
void NetWrapperCommandMsg::setWrappedCommandID(UnsignedShort wrappedCommandID) {
	m_wrappedCommandID = wrappedCommandID;
}

//-------------------------
// NetFileCommandMsg
//-------------------------
// ??0NetFileCommandMsg@@QAE@XZ present-unmatched
NetFileCommandMsg::NetFileCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_FILE;
	m_data = NULL;
	m_portableFilename.clear();
	m_dataLength = 0;
}

// ??1NetFileCommandMsg@@MAE@XZ present-unmatched
NetFileCommandMsg::~NetFileCommandMsg() {
	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
	}
}

// ?getRealFilename@NetFileCommandMsg@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString NetFileCommandMsg::getRealFilename() 
{
	return TheGameState->portableMapPathToRealMapPath(m_portableFilename);
}

// ?setRealFilename@NetFileCommandMsg@@QAEXVAsciiString@@@Z present-unmatched
void NetFileCommandMsg::setRealFilename(AsciiString filename) 
{
	m_portableFilename = TheGameState->realMapPathToPortableMapPath(filename);
}

// ?getFileLength@NetFileCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetFileCommandMsg::getFileLength() {
	return m_dataLength;
}

// ?getFileData@NetFileCommandMsg@@QAEPAEXZ present-unmatched
UnsignedByte * NetFileCommandMsg::getFileData() {
	return m_data;
}

void NetFileCommandMsg::setFileData(UnsignedByte *data, UnsignedInt dataLength) 
{
	m_dataLength = dataLength;
	m_data = NEW UnsignedByte[dataLength];	// pool[]ify
	memcpy(m_data, data, dataLength);
}

//-------------------------
// NetFileAnnounceCommandMsg
//-------------------------
// ??0NetFileAnnounceCommandMsg@@QAE@XZ present-unmatched
NetFileAnnounceCommandMsg::NetFileAnnounceCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_FILEANNOUNCE;
	m_portableFilename.clear();
	m_fileID = 0;
	m_playerMask = 0;
}

// ??1NetFileAnnounceCommandMsg@@MAE@XZ present-unmatched
NetFileAnnounceCommandMsg::~NetFileAnnounceCommandMsg() {
}

// ?getRealFilename@NetFileAnnounceCommandMsg@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString NetFileAnnounceCommandMsg::getRealFilename() 
{
	return TheGameState->portableMapPathToRealMapPath(m_portableFilename);
}

// ?setRealFilename@NetFileAnnounceCommandMsg@@QAEXVAsciiString@@@Z present-unmatched
void NetFileAnnounceCommandMsg::setRealFilename(AsciiString filename) 
{
	m_portableFilename = TheGameState->realMapPathToPortableMapPath(filename);
}

// ?getFileID@NetFileAnnounceCommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetFileAnnounceCommandMsg::getFileID() {
	return m_fileID;
}

// ?setFileID@NetFileAnnounceCommandMsg@@QAEXG@Z present-unmatched
void NetFileAnnounceCommandMsg::setFileID(UnsignedShort fileID) {
	m_fileID = fileID;
}

// ?getPlayerMask@NetFileAnnounceCommandMsg@@QAEEXZ present-unmatched
UnsignedByte NetFileAnnounceCommandMsg::getPlayerMask(void) {
	return m_playerMask;
}

// ?setPlayerMask@NetFileAnnounceCommandMsg@@QAEXE@Z present-unmatched
void NetFileAnnounceCommandMsg::setPlayerMask(UnsignedByte playerMask) {
	m_playerMask = playerMask;
}


//-------------------------
// NetFileProgressCommandMsg
//-------------------------
// ??0NetFileProgressCommandMsg@@QAE@XZ present-unmatched
NetFileProgressCommandMsg::NetFileProgressCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_FILEPROGRESS;
	m_fileID = 0;
	m_progress = 0;
}

// ??1NetFileProgressCommandMsg@@MAE@XZ present-unmatched
NetFileProgressCommandMsg::~NetFileProgressCommandMsg() {
}

// ?getFileID@NetFileProgressCommandMsg@@QAEGXZ present-unmatched
UnsignedShort NetFileProgressCommandMsg::getFileID() {
	return m_fileID;
}

// ?setFileID@NetFileProgressCommandMsg@@QAEXG@Z present-unmatched
void NetFileProgressCommandMsg::setFileID(UnsignedShort val) {
	m_fileID = val;
}

// ?getProgress@NetFileProgressCommandMsg@@QAEHXZ present-unmatched
Int NetFileProgressCommandMsg::getProgress() {
	return m_progress;
}

// ?setProgress@NetFileProgressCommandMsg@@QAEXH@Z present-unmatched
void NetFileProgressCommandMsg::setProgress(Int val) {
	m_progress = val;
}

//-------------------------
// NetDisconnectFrameCommandMsg
//-------------------------
// ??0NetDisconnectFrameCommandMsg@@QAE@XZ present-unmatched
NetDisconnectFrameCommandMsg::NetDisconnectFrameCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_DISCONNECTFRAME;
	m_disconnectFrame = 0;
}

// ??1NetDisconnectFrameCommandMsg@@MAE@XZ present-unmatched
NetDisconnectFrameCommandMsg::~NetDisconnectFrameCommandMsg() {
}

// ?getDisconnectFrame@NetDisconnectFrameCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetDisconnectFrameCommandMsg::getDisconnectFrame() {
	return m_disconnectFrame;
}

// ?setDisconnectFrame@NetDisconnectFrameCommandMsg@@QAEXI@Z present-unmatched
void NetDisconnectFrameCommandMsg::setDisconnectFrame(UnsignedInt disconnectFrame) {
	m_disconnectFrame = disconnectFrame;
}

//-------------------------
// NetDisconnectScreenOffCommandMsg
//-------------------------
// ??0NetDisconnectScreenOffCommandMsg@@QAE@XZ present-unmatched
NetDisconnectScreenOffCommandMsg::NetDisconnectScreenOffCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_DISCONNECTSCREENOFF;
	m_newFrame = 0;
}

// ??1NetDisconnectScreenOffCommandMsg@@MAE@XZ present-unmatched
NetDisconnectScreenOffCommandMsg::~NetDisconnectScreenOffCommandMsg() {
}

// ?getNewFrame@NetDisconnectScreenOffCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetDisconnectScreenOffCommandMsg::getNewFrame() {
	return m_newFrame;
}

// ?setNewFrame@NetDisconnectScreenOffCommandMsg@@QAEXI@Z present-unmatched
void NetDisconnectScreenOffCommandMsg::setNewFrame(UnsignedInt newFrame) {
	m_newFrame = newFrame;
}

//-------------------------
// NetFrameResendRequestCommandMsg
//-------------------------
// ??0NetFrameResendRequestCommandMsg@@QAE@XZ present-unmatched
NetFrameResendRequestCommandMsg::NetFrameResendRequestCommandMsg() : NetCommandMsg() {
	m_commandType = NETCOMMANDTYPE_FRAMERESENDREQUEST;
	m_frameToResend = 0;
}

// ??1NetFrameResendRequestCommandMsg@@MAE@XZ present-unmatched
NetFrameResendRequestCommandMsg::~NetFrameResendRequestCommandMsg() {
}

// ?getFrameToResend@NetFrameResendRequestCommandMsg@@QAEIXZ present-unmatched
UnsignedInt NetFrameResendRequestCommandMsg::getFrameToResend() {
	return m_frameToResend;
}

// ?setFrameToResend@NetFrameResendRequestCommandMsg@@QAEXI@Z present-unmatched
void NetFrameResendRequestCommandMsg::setFrameToResend(UnsignedInt frame) {
	m_frameToResend = frame;
}
