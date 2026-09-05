// cl: /DNDEBUG /MD /EHsc
// readable body of ?FillBufferWithGameCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z:
// Code/GameEngine/Source/GameNetwork/NetPacket.cpp
//
// NetPacket::FillBufferWithGameCommand, 0x00676D00, 543 bytes.
//
// Reference's shape (NetPacket.cpp:861, present-unmatched) with the same BFME
// NetCommandRef view NetPacket.cpp's ack/frame helpers already use: the ref
// param carries the command pointer at +0x00 and the relay byte at +0x0C, not
// the reference header's +0x04/+0x10. Field offsets for GameMessage,
// GameMessageParser and GameMessageParserArgumentType match the ones
// NetPacket_readGameMessage.cpp / NetPacket_GetBufferSizeNeededForCommand.cpp /
// Recorder.cpp already proved (getType@+0x10, getArgumentCount@+0x18,
// getArgument ILT 0x00045AE3, getArgumentDataType ILT 0x0001A3D4,
// GameMessageParser ctor ILT 0x00009836, constructGameMessage ILT 0x000078F6).
// SQUADID (ordinal 6) has no serialize arm, matching the retail argument-write
// switch that skips it.

#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef float Real;
typedef unsigned short WideChar;

struct Coord3D { Real x, y, z; };
struct ICoord2D { Int x, y; };
struct IRegion2D { Int loX, loY, hiX, hiY; };

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

union GameMessageArgumentType
{
	Int integer;
	Real real;
	Bool boolean;
	UnsignedInt objectID;
	UnsignedInt drawableID;
	UnsignedInt teamID;
	Coord3D location;
	ICoord2D pixel;
	IRegion2D pixelRegion;
	UnsignedInt timestamp;
	WideChar wChar;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	typedef Int Type;

	virtual ~GameMessage();

	unsigned char m_unreconstructed_00[0x0c];
	Type m_type;						///< retail this+0x10
	Int m_playerIndex;					///< retail this+0x14
	UnsignedByte m_argCount;				///< retail this+0x18

	Type getType() const { return m_type; }
	UnsignedByte getArgumentCount() const { return m_argCount; }

	const GameMessageArgumentType *getArgument(Int index) const;	///< ILT 0x00045AE3
	int getArgumentDataType(Int index);				///< ILT 0x0001A3D4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParserArgumentType
{
public:
	GameMessageParserArgumentType *getNext() { return m_next; }
	GameMessageArgumentDataType getType() { return m_type; }
	Int getArgCount() { return m_argCount; }

	void *m_vptr;
	GameMessageParserArgumentType *m_next;				///< retail this+0x04
	GameMessageArgumentDataType m_type;				///< retail this+0x08
	Int m_argCount;						///< retail this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParser
{
public:
	GameMessageParser(GameMessage *msg);				///< body 0x00009836
	virtual ~GameMessageParser();

	UnsignedByte getNumTypes() const { return (UnsignedByte)m_argTypeCount; }
	GameMessageParserArgumentType *getFirstArgumentType() const { return (GameMessageParserArgumentType *)m_first; }

	void *m_first;						///< retail this+0x04
	void *m_last;						///< retail this+0x08
	Int m_argTypeCount;					///< retail this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	void *m_vptr;
	UnsignedInt m_timestamp;				///< retail this+0x04
	UnsignedInt m_executionFrame;				///< retail this+0x08
	UnsignedInt m_playerID;					///< retail this+0x0C
	UnsignedShort m_id;					///< retail this+0x10
	Int m_commandType;					///< retail this+0x14

	Int getNetCommandType() { return m_commandType; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetGameCommandMsg : public NetCommandMsg
{
public:
	GameMessage *constructGameMessage();			///< ILT 0x000078F6
};

// opaque: only used through the BFME view below, matches the mangled param type
class NetCommandRef;

// BFME's NetCommandRef holds the command pointer at +0x00 and the relay at
// +0x0C; the reference header puts them at +0x04 and +0x10 (see NetPacket.cpp's
// FillBufferWithAckCommand / FillBufferWithFrameCommand for the same view).
struct BfmeNetCommandRef
{
	NetGameCommandMsg *m_command;
	UnsignedByte m_unreconstructed_04[0x0c - 4];
	UnsignedByte m_relay;
};

class NetPacket
{
protected:
	static void FillBufferWithGameCommand(UnsignedByte *buffer, NetCommandRef *ref);
};

// ?FillBufferWithGameCommand@NetPacket@@KAXPAEPAVNetCommandRef@@@Z
void NetPacket::FillBufferWithGameCommand(UnsignedByte *buffer, NetCommandRef *ref)
{
	BfmeNetCommandRef *msg = (BfmeNetCommandRef *)ref;
	NetGameCommandMsg *cmdMsg = msg->m_command;
	UnsignedShort offset = 0;
	// get the game message from the NetCommandMsg
	GameMessage *gmsg = cmdMsg->constructGameMessage();

	// If necessary, put the NetCommandType into the packet.
	buffer[offset] = 'T';
	++offset;
	buffer[offset] = cmdMsg->getNetCommandType();
	offset += sizeof(UnsignedByte);

	// If necessary, put the execution frame into the packet.
	buffer[offset] = 'F';
	++offset;
	UnsignedInt newframe = cmdMsg->getExecutionFrame();
	memcpy(buffer+offset, &newframe, sizeof(UnsignedInt));
	offset += sizeof(UnsignedInt);

	// If necessary, put the relay into the packet.
	buffer[offset] = 'R';
	++offset;
	UnsignedByte newRelay = msg->m_relay;
	memcpy(buffer+offset, &newRelay, sizeof(UnsignedByte));
	offset += sizeof(UnsignedByte);

	// If necessary, put the playerID into the packet.
	buffer[offset] = 'P';
	++offset;
	buffer[offset] = cmdMsg->getPlayerID();
	offset += sizeof(UnsignedByte);

	// If necessary, specify the command ID of this command.
	buffer[offset] = 'C';
	++offset;
	UnsignedShort newID = cmdMsg->getID();
	memcpy(buffer + offset, &newID, sizeof(UnsignedShort));
	offset += sizeof(UnsignedShort);

	buffer[offset] = 'D';
	++offset;

	// Now copy the GameMessage type into the packet.
	GameMessage::Type newType = gmsg->getType();
	memcpy(buffer + offset, &newType, sizeof(GameMessage::Type));
	offset += sizeof(GameMessage::Type);

	GameMessageParser *parser = new GameMessageParser(gmsg);
	UnsignedByte numTypes = parser->getNumTypes();
	memcpy(buffer + offset, &numTypes, sizeof(numTypes));
	offset += sizeof(numTypes);

	GameMessageParserArgumentType *argType = parser->getFirstArgumentType();
	while (argType != 0) {
		UnsignedByte type = (UnsignedByte)(argType->getType());
		memcpy(buffer + offset, &type, sizeof(type));
		offset += sizeof(type);

		UnsignedByte argTypeCount = argType->getArgCount();
		memcpy(buffer + offset, &argTypeCount, sizeof(argTypeCount));
		offset += sizeof(argTypeCount);

		argType = argType->getNext();
	}

	Int numArgs = gmsg->getArgumentCount();
	for (Int i = 0; i < numArgs; ++i) {
		GameMessageArgumentDataType type = (GameMessageArgumentDataType)gmsg->getArgumentDataType(i);
		GameMessageArgumentType arg = *(gmsg->getArgument(i));

		if (type == ARGUMENTDATATYPE_INTEGER) {
			memcpy(buffer + offset, &(arg.integer), sizeof(arg.integer));
			offset += sizeof(arg.integer);
		} else if (type == ARGUMENTDATATYPE_REAL) {
			memcpy(buffer + offset, &(arg.real), sizeof(arg.real));
			offset += sizeof(arg.real);
		} else if (type == ARGUMENTDATATYPE_BOOLEAN) {
			memcpy(buffer + offset, &(arg.boolean), sizeof(arg.boolean));
			offset += sizeof(arg.boolean);
		} else if (type == ARGUMENTDATATYPE_OBJECTID) {
			memcpy(buffer + offset, &(arg.objectID), sizeof(arg.objectID));
			offset += sizeof(arg.objectID);
		} else if (type == ARGUMENTDATATYPE_DRAWABLEID) {
			memcpy(buffer + offset, &(arg.drawableID), sizeof(arg.drawableID));
			offset += sizeof(arg.drawableID);
		} else if (type == ARGUMENTDATATYPE_TEAMID) {
			memcpy(buffer + offset, &(arg.teamID), sizeof(arg.teamID));
			offset += sizeof(arg.teamID);
		} else if (type == ARGUMENTDATATYPE_LOCATION) {
			memcpy(buffer + offset, &(arg.location), sizeof(arg.location));
			offset += sizeof(arg.location);
		} else if (type == ARGUMENTDATATYPE_PIXEL) {
			memcpy(buffer + offset, &(arg.pixel), sizeof(arg.pixel));
			offset += sizeof(arg.pixel);
		} else if (type == ARGUMENTDATATYPE_PIXELREGION) {
			memcpy(buffer + offset, &(arg.pixelRegion), sizeof(arg.pixelRegion));
			offset += sizeof(arg.pixelRegion);
		} else if (type == ARGUMENTDATATYPE_TIMESTAMP) {
			memcpy(buffer + offset, &(arg.timestamp), sizeof(arg.timestamp));
			offset += sizeof(arg.timestamp);
		} else if (type == ARGUMENTDATATYPE_WIDECHAR) {
			memcpy(buffer + offset, &(arg.wChar), sizeof(arg.wChar));
			offset += sizeof(arg.wChar);
		}
	}

	delete parser;
	parser = 0;

	delete gmsg;
	gmsg = 0;
}
