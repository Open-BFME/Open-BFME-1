#pragma once
#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

class GameMessageList;
struct GameMessageArgument;

struct Coord3D;
struct ICoord2D;
struct IRegion2D;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage {
public:
	enum Type { MSG_INVALID = 0 };
	GameMessage(Type type);
	virtual ~GameMessage();
	static AsciiString getCommandTypeAsAsciiString(Type t);

	// Argument-list mutators: each allocates a new GameMessageArgument (via the
	// allocArg() below, matched at retail 0x0008AAE0) and
	// stores the value at m_data@+0x8 / m_type@+0x18 of the returned argument.
	void appendIntegerArgument(Int arg);
	void appendRealArgument(Real arg);
	void appendBooleanArgument(Bool arg);
	void appendObjectIDArgument(UnsignedInt arg);
	void appendDrawableIDArgument(UnsignedInt arg);
	void appendTeamIDArgument(UnsignedInt arg);
	void appendLocationArgument(const Coord3D &arg);
	void appendPixelArgument(const ICoord2D &arg);
	void appendPixelRegionArgument(const IRegion2D &arg);
	void appendTimestampArgument(UnsignedInt arg);
	void appendWideCharArgument(const WideChar &arg);

protected:
	// Retail 0x0008AAE0, ?allocArg@GameMessage@@IAEPAUGameMessageArgument@@XZ
	// (GameMessage_allocArg.cpp): protected, returning ZH's GameMessageArgument.
	GameMessageArgument *allocArg();

private:
	GameMessage *m_next;
	GameMessage *m_prev;
	GameMessageList *m_list;
	Type m_type;
	Int m_playerIndex;
	unsigned char m_argCount;
	unsigned char m_padding[3];
	GameMessageArgument *m_argList;
	GameMessageArgument *m_argTail;
};
