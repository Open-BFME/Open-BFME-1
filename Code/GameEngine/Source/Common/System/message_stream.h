#pragma once
#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

struct Coord3D;
struct ICoord2D;
struct IRegion2D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage {
public:
	enum Type { MSG_INVALID = 0 };
	GameMessage(Type type);
	virtual ~GameMessage() {}
	AsciiString getCommandTypeAsAsciiString(Type t);

	// Argument-list mutators: each allocates a new GameMessageArgument (via the
	// not-yet-converted allocArg(), REL32-pinned in reverse/symbols.csv) and
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

private:
	struct Argument;
	Argument *allocArg();
	Argument *m_argList;
	Argument *m_argTail;
	void *m_list;
	Type m_type;
	Int m_playerIndex;
	unsigned char m_argCount;
	unsigned char m_padding[3];
	Int m_reserved1;
	Int m_reserved2;
};
