// cl: /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /ICode/Libraries/Source/WWVegas/WWLib
#include "message_stream.h"
struct BFMEPlayer
{
	Int getPlayerIndex() const
	{
		return *(const Int *)((const unsigned char *)this + 0x24);
	}
};

struct BFMEPlayerList
{
	BFMEPlayer *getLocalPlayer() const
	{
		return *(BFMEPlayer **)((const unsigned char *)this + 0x0C);
	}
};

extern BFMEPlayerList *ThePlayerList;

GameMessage::GameMessage(Type type)
{
	m_playerIndex = ThePlayerList->getLocalPlayer()->getPlayerIndex();
	m_type = type;
	m_reserved1 = 0;
	m_reserved2 = 0;
	m_argCount = 0;
	m_list = 0;
	m_argList = 0;
	m_argTail = 0;
}

// Layout of the retail GameMessageArgument (a MemoryPoolObject subclass we have
// not converted): vtbl@0, m_next@0x4, m_data@0x8 (16-byte union, widest member
// is the 4-int IRegion2D), m_type@0x18. Mirrors reference ZH GameMessageArgument
// (Common/MessageStream.h) with the BFME-retail arg-type ordinal shift proven by
// the append* bodies below (SQUADID slotted in at 6, pushing LOCATION..WIDECHAR
// to 7..11).
struct GameMessageLocationRaw { Real x, y, z; };
struct GameMessagePixelRegionRaw { Int x_min, y_min, x_max, y_max; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
struct GameMessage::Argument {
	void *m_vtbl;
	Argument *m_next;
	union {
		Int integer;
		Real real;
		Bool boolean;
		UnsignedInt objectID;
		UnsignedInt drawableID;
		UnsignedInt teamID;
		GameMessageLocationRaw location;
		struct { Int x, y; } pixel;
		GameMessagePixelRegionRaw pixelRegion;
		UnsignedInt timestamp;
		WideChar wChar;
	} m_data;
	Int m_type;
};

void GameMessage::appendIntegerArgument(Int arg)
{
	Argument *a = allocArg();
	a->m_data.integer = arg;
	a->m_type = 0;
}

void GameMessage::appendRealArgument(Real arg)
{
	Argument *a = allocArg();
	a->m_data.real = arg;
	a->m_type = 1;
}

void GameMessage::appendBooleanArgument(Bool arg)
{
	Argument *a = allocArg();
	a->m_data.boolean = arg;
	a->m_type = 2;
}

void GameMessage::appendObjectIDArgument(UnsignedInt arg)
{
	Argument *a = allocArg();
	a->m_data.objectID = arg;
	a->m_type = 3;
}

void GameMessage::appendDrawableIDArgument(UnsignedInt arg)
{
	Argument *a = allocArg();
	a->m_data.drawableID = arg;
	a->m_type = 4;
}

void GameMessage::appendTeamIDArgument(UnsignedInt arg)
{
	Argument *a = allocArg();
	a->m_data.teamID = arg;
	a->m_type = 5;
}

void GameMessage::appendLocationArgument(const Coord3D &arg)
{
	Argument *a = allocArg();
	a->m_data.location = *(const GameMessageLocationRaw *)&arg;
	a->m_type = 7;
}

void GameMessage::appendPixelArgument(const ICoord2D &arg)
{
	const Int *src = (const Int *)&arg;
	Argument *a = allocArg();
	a->m_data.pixel.x = src[0];
	a->m_data.pixel.y = src[1];
	a->m_type = 8;
}

void GameMessage::appendPixelRegionArgument(const IRegion2D &arg)
{
	Argument *a = allocArg();
	a->m_data.pixelRegion = *(const GameMessagePixelRegionRaw *)&arg;
	a->m_type = 9;
}

void GameMessage::appendTimestampArgument(UnsignedInt arg)
{
	Argument *a = allocArg();
	a->m_data.timestamp = arg;
	a->m_type = 10;
}

void GameMessage::appendWideCharArgument(const WideChar &arg)
{
	Argument *a = allocArg();
	a->m_data.wChar = arg;
	a->m_type = 11;
}

