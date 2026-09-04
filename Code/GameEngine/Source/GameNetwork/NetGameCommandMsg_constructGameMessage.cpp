// cl: /DNDEBUG /MD /EHsc

// NetGameCommandMsg::constructGameMessage, 0x00675ED0, 467 bytes.
//
// Named by GetGameCommandSize / addGameCommand, which both open with this call
// on the type-4 NetGameCommandMsg. The Zero Hour body formats "player%d" from
// getPlayerID(); BFME takes GameSlot+0x2C's AsciiString buffer (same slot-name
// walk Network::processDestroyPlayerCommand already landed) and returns NULL
// when findPlayerWithNameKey misses. Argument nodes are the BFME
// GameMessageArgument layout (vptr, next@+4, 16-byte union@+8, type@+0x18)
// with SQUADID occupying ordinal 6 so LOCATION..WIDECHAR sit at 7..11.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef float Real;

#define NULL 0

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	const char *str() const
	{
		return m_stringData ? m_stringData + 8 : "";
	}

	UnsignedByte m_bfmeHead[0x2C];
	const char *m_stringData;				// AsciiString::m_data at +0x2C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameSlot *getSlot(Int slot);				// ILT 0x0001EC18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);		// ILT 0x0003ADD7
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex(void) const { return m_playerIndex; }

	UnsignedByte m_bfmeHead[0x24];
	Int m_playerIndex;					// +0x24
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);	// body 0x000DF260
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	enum Type
	{
		MSG_INVALID = 0
	};

	GameMessage(Type type);					// ILT 0x000359E5
	void friend_setPlayerIndex(Int playerIndex) { m_playerIndex = playerIndex; }

	void appendIntegerArgument(Int arg);			// ILT 0x00001370
	void appendRealArgument(Real arg);			// ILT 0x00002608
	void appendBooleanArgument(Bool arg);			// ILT 0x000032AB
	void appendObjectIDArgument(UnsignedInt arg);		// ILT 0x0002BCEC
	void appendDrawableIDArgument(UnsignedInt arg);		// ILT 0x000154BF
	void appendTeamIDArgument(UnsignedInt arg);		// ILT 0x0000C522
	void appendLocationArgument(const Coord3D &arg);	// ILT 0x00037AD8
	void appendPixelArgument(const ICoord2D &arg);		// ILT 0x0002EA41
	void appendPixelRegionArgument(const IRegion2D &arg);	// ILT 0x00011DCE
	void appendTimestampArgument(UnsignedInt arg);		// ILT 0x0000D558
	void appendWideCharArgument(const WideChar &arg);	// ILT 0x000028C9

	UnsignedByte m_bfmeHead[0x14];
	Int m_playerIndex;					// +0x14
	UnsignedByte m_bfmeTail[0x24 - 0x18];
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

// upstream layout: Code/GameEngine/Source/Common/System/message_stream.cpp
struct GameMessageArgument
{
	void *m_vtbl;
	GameMessageArgument *m_next;
	GameMessageArgumentType m_data;
	GameMessageArgumentDataType m_type;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	virtual ~NetCommandMsg() {}

	UnsignedInt getPlayerID() { return m_playerID; }

	UnsignedInt m_timestamp;				// +0x04
	UnsignedInt m_executionFrame;				// +0x08
	UnsignedInt m_playerID;					// +0x0C
	UnsignedShort m_id;					// +0x10
	Int m_commandType;					// +0x14
	Int m_referenceCount;					// +0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetGameCommandMsg : public NetCommandMsg
{
public:
	GameMessage *constructGameMessage();

	Int m_numArgs;						// +0x1C
	Int m_argSize;						// +0x20
	GameMessage::Type m_type;				// +0x24
	GameMessageArgument *m_argList;				// +0x28
	GameMessageArgument *m_argTail;				// +0x2C
};

extern GameInfo *TheGameInfo;					// retail [0x012F708C]
extern NameKeyGenerator *TheNameKeyGenerator;			// retail [0x012ED600]
extern PlayerList *ThePlayerList;				// retail [0x012ED748]

// ?constructGameMessage@NetGameCommandMsg@@QAEPAVGameMessage@@XZ
GameMessage *NetGameCommandMsg::constructGameMessage()
{
	Player *player = ThePlayerList->findPlayerWithNameKey(
		TheNameKeyGenerator->nameToKey(
			TheGameInfo->getSlot((Int)getPlayerID())->str()));
	if (!player)
		return NULL;

	GameMessage *retval = new GameMessage(m_type);
	if (retval)
	{
		retval->friend_setPlayerIndex(player->getPlayerIndex());
		GameMessageArgument *arg = m_argList;
		while (arg != NULL)
		{
			if (arg->m_type == ARGUMENTDATATYPE_INTEGER)
			{
				retval->appendIntegerArgument(arg->m_data.integer);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_REAL)
			{
				retval->appendRealArgument(arg->m_data.real);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_BOOLEAN)
			{
				retval->appendBooleanArgument(arg->m_data.boolean);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_OBJECTID)
			{
				retval->appendObjectIDArgument(arg->m_data.objectID);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_DRAWABLEID)
			{
				retval->appendDrawableIDArgument(arg->m_data.drawableID);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_TEAMID)
			{
				retval->appendTeamIDArgument(arg->m_data.teamID);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_LOCATION)
			{
				Coord3D loc;
				loc.x = arg->m_data.location.x;
				loc.y = arg->m_data.location.y;
				loc.z = arg->m_data.location.z;
				retval->appendLocationArgument(loc);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_PIXEL)
			{
				ICoord2D pixel;
				pixel.x = arg->m_data.pixel.x;
				pixel.y = arg->m_data.pixel.y;
				retval->appendPixelArgument(pixel);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_PIXELREGION)
			{
				retval->appendPixelRegionArgument(arg->m_data.pixelRegion);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_TIMESTAMP)
			{
				retval->appendTimestampArgument(arg->m_data.timestamp);
			}
			else if (arg->m_type == ARGUMENTDATATYPE_WIDECHAR)
			{
				retval->appendWideCharArgument(arg->m_data.wChar);
			}
			arg = arg->m_next;
		}
	}
	return retval;
}
