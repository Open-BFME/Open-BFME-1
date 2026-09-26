// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Retail RVA 0x00674A40, reached from sendGameCommand via ILT 0x00042181.
// The upstream GameMessage constructor copies each typed argument; BFME also
// initializes the argument counters and linked-list ends before that copy.

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_GAMECOMMAND = 4
};

enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_UNKNOWN = 12
};

// The largest member is IRegion2D: two pairs of integer screen coordinates.
union GameMessageArgumentType
{
	int integer;
	float real;
	int pixelRegion[4];
};

class GameMessage
{
public:
	int getType() const { return m_type; }
	unsigned char getArgumentCount() const { return m_argCount; }
	const GameMessageArgumentType *getArgument(int index) const;
	GameMessageArgumentDataType getArgumentDataType(int index);

private:
	char m_unknown00[0x10];
	int m_type;
	char m_unknown14[4];
	unsigned char m_argCount;
};

class NetCommandMsg
{
public:
	NetCommandMsg()
	{
		m_executionFrame = -1;
		m_id = 0;
		m_playerID = 0;
		m_timestamp = 0;
		m_referenceCount = 1;
		m_commandType = NETCOMMANDTYPE_UNKNOWN;
	}
	virtual ~NetCommandMsg() {}

protected:
	unsigned int m_timestamp;
	unsigned int m_executionFrame;
	unsigned int m_playerID;
	unsigned short m_id;
	NetCommandType m_commandType;
	int m_referenceCount;
};

class GameMessageArgument;

class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg(GameMessage *msg);
	void addArgument(GameMessageArgumentDataType type, GameMessageArgumentType arg);

private:
	int m_numArgs;
	int m_argSize;
	int m_type;
	GameMessageArgument *m_argList;
	GameMessageArgument *m_argTail;
};

NetGameCommandMsg::NetGameCommandMsg(GameMessage *msg) : NetCommandMsg()
{
	m_numArgs = 0;
	m_argSize = 0;
	m_argList = 0;
	m_argTail = 0;
	m_commandType = NETCOMMANDTYPE_GAMECOMMAND;
	m_type = msg->getType();
	int count = msg->getArgumentCount();
	for (int i = 0; i < count; ++i)
		addArgument(msg->getArgumentDataType(i), *msg->getArgument(i));
}
