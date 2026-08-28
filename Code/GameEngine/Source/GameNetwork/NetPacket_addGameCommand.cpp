// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?addGameCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?isRoomForGameMessage@NetPacket@@IAE_NPAVNetCommandRef@@PAVGameMessage@@@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket::addGameCommand, 0x0067CA00, 855 bytes -- addCommand's jump-table
// arm for command type 4, and the biggest of the family.
//
// The reference's body, with one BFME addition: constructGameMessage returning
// NULL is an early return TRUE here, where the reference would carry the null
// straight into isRoomForGameMessage. That is the same kind of hardening
// readGameMessage got with its message-type range check.
//
// Two callee names come out of this body and are pinned rather than owned:
//
//   0x00675ED0  constructGameMessage@NetGameCommandMsg -- the first call the
//               body makes, on msg->getCommand(), which is exactly how the
//               reference opens.
//   0x006785A0  isRoomForGameMessage@NetPacket -- the two-argument guard the
//               body calls on itself with (msg, gmsg). Every other add* opens
//               with its own isRoomFor, and the reference declares this one
//               with exactly that pair.
//
// What the bytes pin beyond the reference:
//   - GameMessage::getArgumentCount is a BYTE at +0x18, read signed-compared,
//     and getType is the dword at +0x10.
//   - GameMessageParser is 0x10 bytes (retail's allocation) and its
//     getNumTypes is the +0x0C count, not a separate field --  the same layout
//     NetPacket_readGameMessage.cpp already pins from the other direction.
//   - GameMessageArgumentType is a 16-byte union: the argument loop copies four
//     dwords straight from getArgument's result into the outgoing argument
//     slot.
//   - deleteInstance on both the parser and the game message is a virtual slot-0
//     call with flag 1, i.e. plain `delete` through a virtual destructor.
//
// Layouts otherwise are NetPacket_isRoomForFrameFamily.cpp's, unchanged.

extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

#define NULL 0
#define TRUE 1
#define FALSE 0

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef float Real;
typedef UnsignedInt ObjectID;
typedef UnsignedInt DrawableID;
typedef unsigned short WideChar;
enum { MAX_PACKET_SIZE = 0x1DC };

typedef Int GameMessageType;

enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_INTEGER = 0,
	ARGUMENTDATATYPE_REAL,
	ARGUMENTDATATYPE_BOOLEAN,
	ARGUMENTDATATYPE_OBJECTID,
	ARGUMENTDATATYPE_DRAWABLEID,
	ARGUMENTDATATYPE_TEAMID,
	ARGUMENTDATATYPE_SQUADID,
	ARGUMENTDATATYPE_LOCATION,
	ARGUMENTDATATYPE_PIXEL,
	ARGUMENTDATATYPE_PIXELREGION,
	ARGUMENTDATATYPE_TIMESTAMP,
	ARGUMENTDATATYPE_WIDECHAR
};

struct Coord3D { Real x, y, z; };
struct ICoord2D { Int x, y; };
struct IRegion2D { Int loX, loY, hiX, hiY; };

union GameMessageArgumentType
{
	Int integer;
	UnsignedInt objectID;
	UnsignedByte raw[16];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	virtual ~GameMessage();

	GameMessageType getType(void) const { return m_type; }
	Int getArgumentCount(void) const { return m_argCount; }

	GameMessageArgumentDataType getArgumentDataType(Int argIndex);		// ILT thunk 0x0001A3D4
	const GameMessageArgumentType *getArgument(Int argIndex) const;		// ILT thunk 0x00045AE3

	UnsignedInt m_head[3];							// this+0x04 .. +0x0F
	GameMessageType m_type;							// this+0x10
	UnsignedInt m_pad;							// this+0x14
	UnsignedByte m_argCount;						// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParserArgumentType
{
public:
	GameMessageParserArgumentType *getNext() { return m_next; }
	GameMessageArgumentDataType getType() { return m_type; }
	Int getArgCount() { return m_argCount; }

	void *m_vptr;
	GameMessageParserArgumentType *m_next;					// this+0x04
	GameMessageArgumentDataType m_type;					// this+0x08
	Int m_argCount;								// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParser
{
public:
	GameMessageParser(GameMessage *msg);					// retail 0x006236D0
	virtual ~GameMessageParser();

	Int getNumTypes() { return m_argTypeCount; }
	GameMessageParserArgumentType *getFirstArgumentType() { return m_first; }

	GameMessageParserArgumentType *m_first;					// this+0x04
	GameMessageParserArgumentType *m_last;					// this+0x08
	Int m_argTypeCount;							// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }

	void *m_vptr;								// this+0x00
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;						// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;							// this+0x10
	Int m_commandType;							// this+0x14
	Int m_referenceCount;							// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetGameCommandMsg : public NetCommandMsg
{
public:
	GameMessage *constructGameMessage(void);				// retail 0x00675ED0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);					// ILT thunk 0x000079E6
	~NetCommandRef();							// ILT thunk 0x00038960

	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedByte m_relay;							// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	virtual ~NetPacket();

protected:
	Bool isRoomForGameMessage(NetCommandRef *msg, GameMessage *gmsg);	// retail 0x006785A0
	void writeGameMessageArgumentToPacket(GameMessageArgumentDataType type,
			GameMessageArgumentType arg);				// retail 0x00678430
	Bool addGameCommand(NetCommandRef *msg);

public:
	UnsignedByte m_packet[0x1DC];						// this+0x004
	Int m_packetLen;							// this+0x1E0
	NetPacketAddress m_dest;						// this+0x1E4
	Int m_numCommands;							// this+0x1EC
	NetCommandRef *m_lastCommand;						// this+0x1F0
	UnsignedInt m_lastFrame;						// this+0x1F4
	UnsignedShort m_lastCommandID;						// this+0x1F8
	UnsignedByte m_lastPlayerID;						// this+0x1FA
	UnsignedByte m_lastCommandType;						// this+0x1FB
	UnsignedByte m_lastRelay;						// this+0x1FC
};

Bool NetPacket::isRoomForGameMessage(NetCommandRef *msg, GameMessage *gmsg) {
	Int msglen = 0;
	NetGameCommandMsg *cmdMsg = (NetGameCommandMsg *)(msg->getCommand());
	Bool needNewCommandID = FALSE;
	if (m_lastFrame != cmdMsg->getExecutionFrame()) {
		msglen += sizeof(UnsignedInt) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID()) {
		msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
		needNewCommandID = TRUE;
	}
	if (m_lastRelay != msg->getRelay()) {
		msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastCommandType != cmdMsg->getNetCommandType()) {
		msglen += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
		msglen += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}
	GameMessageParser *parser = new GameMessageParser(gmsg);
	++msglen;
	msglen += sizeof(GameMessageType);
	msglen += sizeof(UnsignedByte);
	GameMessageParserArgumentType *arg = parser->getFirstArgumentType();
	while (arg != NULL) {
		msglen += 2 * sizeof(UnsignedByte);
		GameMessageArgumentDataType type = arg->getType();
		if (type == ARGUMENTDATATYPE_INTEGER) {
			msglen += arg->getArgCount() * sizeof(Int);
		} else if (type == ARGUMENTDATATYPE_REAL) {
			msglen += arg->getArgCount() * sizeof(Real);
		} else if (type == ARGUMENTDATATYPE_BOOLEAN) {
			msglen += arg->getArgCount() * sizeof(Bool);
		} else if (type == ARGUMENTDATATYPE_OBJECTID) {
			msglen += arg->getArgCount() * sizeof(ObjectID);
		} else if (type == ARGUMENTDATATYPE_DRAWABLEID) {
			msglen += arg->getArgCount() * sizeof(DrawableID);
		} else if (type == ARGUMENTDATATYPE_TEAMID) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_LOCATION) {
			msglen += arg->getArgCount() * sizeof(Coord3D);
		} else if (type == ARGUMENTDATATYPE_PIXEL) {
			msglen += arg->getArgCount() * sizeof(ICoord2D);
		} else if (type == ARGUMENTDATATYPE_PIXELREGION) {
			msglen += arg->getArgCount() * sizeof(IRegion2D);
		} else if (type == ARGUMENTDATATYPE_TIMESTAMP) {
			msglen += arg->getArgCount() * sizeof(UnsignedInt);
		} else if (type == ARGUMENTDATATYPE_WIDECHAR) {
			msglen += arg->getArgCount() * sizeof(WideChar);
		}
		arg = arg->getNext();
	}
	delete parser;
	parser = NULL;
	if (msglen > (MAX_PACKET_SIZE - m_packetLen)) {
		return FALSE;
	}
	return TRUE;
}

Bool NetPacket::addGameCommand(NetCommandRef *msg) {
	Bool retval = FALSE;
	NetGameCommandMsg *cmdMsg = (NetGameCommandMsg *)(msg->getCommand());
	// get the game message from the NetCommandMsg
	GameMessage *gmsg = cmdMsg->constructGameMessage();

	if (gmsg == NULL) {
		return TRUE;
	}

	if (isRoomForGameMessage(msg, gmsg)) {
		// Now we know there is enough room, put the new game message into the packet.

		Bool needNewCommandID = FALSE;

		// If necessary, put the NetCommandType into the packet.
		if (m_lastCommandType != cmdMsg->getNetCommandType()) {
			m_packet[m_packetLen] = 'T';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getNetCommandType();
			m_packetLen += sizeof(UnsignedByte);

			m_lastCommandType = cmdMsg->getNetCommandType();
		}

		// If necessary, put the execution frame into the packet.
		if (m_lastFrame != cmdMsg->getExecutionFrame()) {
			m_packet[m_packetLen] = 'F';
			++m_packetLen;
			UnsignedInt newframe = cmdMsg->getExecutionFrame();
			memcpy(m_packet + m_packetLen, &newframe, sizeof(UnsignedInt));
			m_packetLen += sizeof(UnsignedInt);

			m_lastFrame = newframe;
		}

		// If necessary, put the relay into the packet.
		if (m_lastRelay != msg->getRelay()) {
			m_packet[m_packetLen] = 'R';
			++m_packetLen;
			UnsignedByte newRelay = msg->getRelay();
			memcpy(m_packet + m_packetLen, &newRelay, sizeof(UnsignedByte));
			m_packetLen += sizeof(UnsignedByte);

			m_lastRelay = newRelay;
		}

		// If necessary, put the playerID into the packet.
		if (m_lastPlayerID != cmdMsg->getPlayerID()) {
			m_packet[m_packetLen] = 'P';
			++m_packetLen;
			m_packet[m_packetLen] = cmdMsg->getPlayerID();
			m_packetLen += sizeof(UnsignedByte);
			needNewCommandID = TRUE;

			m_lastPlayerID = cmdMsg->getPlayerID();
		}

		// If necessary, specify the command ID of this command.
		if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) || (needNewCommandID == TRUE)) {
			m_packet[m_packetLen] = 'C';
			++m_packetLen;
			UnsignedShort newID = cmdMsg->getID();
			memcpy(m_packet + m_packetLen, &newID, sizeof(UnsignedShort));
			m_packetLen += sizeof(UnsignedShort);
		}
		m_lastCommandID = cmdMsg->getID();

		m_packet[m_packetLen] = 'D';
		++m_packetLen;

		// Now copy the GameMessage type into the packet.
		GameMessageType newType = gmsg->getType();
		memcpy(m_packet + m_packetLen, &newType, sizeof(GameMessageType));
		m_packetLen += sizeof(GameMessageType);

		GameMessageParser *parser = new GameMessageParser(gmsg);
		UnsignedByte numTypes = parser->getNumTypes();
		memcpy(m_packet + m_packetLen, &numTypes, sizeof(numTypes));
		m_packetLen += sizeof(numTypes);

		GameMessageParserArgumentType *argType = parser->getFirstArgumentType();
		while (argType != NULL) {
			UnsignedByte type = (UnsignedByte)(argType->getType());
			memcpy(m_packet + m_packetLen, &type, sizeof(type));
			m_packetLen += sizeof(type);

			UnsignedByte argTypeCount = argType->getArgCount();
			memcpy(m_packet + m_packetLen, &argTypeCount, sizeof(argTypeCount));
			m_packetLen += sizeof(argTypeCount);

			argType = argType->getNext();
		}

		Int numArgs = gmsg->getArgumentCount();
		for (Int i = 0; i < numArgs; ++i) {
			GameMessageArgumentDataType type = gmsg->getArgumentDataType(i);
			GameMessageArgumentType arg = *(gmsg->getArgument(i));
			writeGameMessageArgumentToPacket(type, arg);
		}

		delete parser;
		parser = NULL;

		++m_numCommands;

		if (m_lastCommand != NULL) {
			delete m_lastCommand;
			m_lastCommand = NULL;
		}
		m_lastCommand = new NetCommandRef(msg->getCommand());
		m_lastCommand->setRelay(msg->getRelay());

		retval = TRUE;
	}

	delete gmsg;

	return retval;
}
