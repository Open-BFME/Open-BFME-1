// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?readGameMessage@NetPacket@@KAPAVNetCommandMsg@@PAEAAH@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// NetPacket::readGameMessage, 0x0067E3F0, 433 bytes.
//
// The reference's shape with two BFME changes.
//
// The first is a range check the reference does not have: the game message type
// is read out of the packet before anything else, and if it is not strictly
// inside (0, 0x7EB) the half-built command is destroyed and the reader returns
// NULL. That is a hardening against a malformed or hostile packet steering the
// message dispatch, and it is the only validation in the whole reader family.
//
// The second is the argument reader's signature: BFME passes the game message
// type along as a fifth parameter, where the reference passes four.
//
// The parser's accessors are all inlined -- the argument type list is walked
// through +0x04, +0x08 and +0x0C directly -- so only the constructor and
// addArgType survive as calls.

#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define NULL 0

enum { ARGUMENTDATATYPE_UNKNOWN = 12 };
enum { GAMEMESSAGE_TYPE_LIMIT = 0x7EB };

typedef Int GameMessageType;

enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_INTEGER = 0
};

class NetCommandMsg;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetGameCommandMsg
{
public:
	NetGameCommandMsg();
	virtual ~NetGameCommandMsg();

	void setGameMessageType(GameMessageType type);

	// 0x30 bytes: the 0x1C-byte NetCommandMsg base plus the game message's own
	// type and argument list. Only the size matters here -- retail's allocation
	// pins it and nothing in this reader touches the fields.
	UnsignedInt m_baseFields[6];					// this+0x04 .. +0x1B
	UnsignedInt m_gameMessageFields[5];				// this+0x1C .. +0x2F
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParserArgumentType
{
public:
	GameMessageParserArgumentType *getNext() { return m_next; }
	GameMessageArgumentDataType getType() { return m_type; }
	Int getArgCount() { return m_argCount; }

	void *m_vptr;
	GameMessageParserArgumentType *m_next;			// this+0x04
	GameMessageArgumentDataType m_type;				// this+0x08
	Int m_argCount;									// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParser
{
public:
	GameMessageParser();
	virtual ~GameMessageParser();

	void addArgType(GameMessageArgumentDataType type, Int count);
	GameMessageParserArgumentType *getFirstArgumentType() { return m_first; }

	GameMessageParserArgumentType *m_first;			// this+0x04
	GameMessageParserArgumentType *m_last;			// this+0x08
	Int m_argTypeCount;								// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
protected:
	static NetCommandMsg *readGameMessage(UnsignedByte *data, Int &i);
	static void readGameMessageArgumentFromPacket(GameMessageArgumentDataType type,
			NetGameCommandMsg *msg, UnsignedByte *data, Int &i, GameMessageType msgType);
};

NetCommandMsg *NetPacket::readGameMessage(UnsignedByte *data, Int &i)
{
	NetGameCommandMsg *msg = new NetGameCommandMsg;

	// Get the GameMessage command type.
	GameMessageType newType;
	memcpy(&newType, data + i, sizeof(GameMessageType));
	i += sizeof(GameMessageType);

	if ((newType <= 0) || (newType >= GAMEMESSAGE_TYPE_LIMIT)) {
		if (msg != NULL) {
			delete msg;
		}
		return NULL;
	}

	msg->setGameMessageType(newType);

	// Get the number of argument types
	UnsignedByte numArgTypes = 0;
	memcpy(&numArgTypes, data + i, sizeof(numArgTypes));
	i += sizeof(numArgTypes);

	// Get the types and the number of arguments of those types.
	Int totalArgCount = 0;
	GameMessageParser *parser = new GameMessageParser;
	for (Int j = 0; j < numArgTypes; ++j) {
		UnsignedByte type = (UnsignedByte)ARGUMENTDATATYPE_UNKNOWN;
		memcpy(&type, data + i, sizeof(type));
		i += sizeof(type);

		UnsignedByte argCount = 0;
		memcpy(&argCount, data + i, sizeof(argCount));
		i += sizeof(argCount);

		parser->addArgType((GameMessageArgumentDataType)type, argCount);
		totalArgCount += argCount;
	}

	GameMessageParserArgumentType *parserArgType = parser->getFirstArgumentType();
	GameMessageArgumentDataType lasttype = (GameMessageArgumentDataType)ARGUMENTDATATYPE_UNKNOWN;
	Int argsLeftForType = 0;
	if (parserArgType != NULL) {
		lasttype = parserArgType->getType();
		argsLeftForType = parserArgType->getArgCount();
	}

	for (Int k = 0; k < totalArgCount; ++k) {
		readGameMessageArgumentFromPacket(lasttype, msg, data, i, newType);

		--argsLeftForType;
		if (argsLeftForType == 0) {
			if (parserArgType == NULL) {
				return NULL;
			}

			parserArgType = parserArgType->getNext();
			if (parserArgType != NULL) {
				argsLeftForType = parserArgType->getArgCount();
				lasttype = parserArgType->getType();
			}
		}
	}

	delete parser;

	return (NetCommandMsg *)msg;
}
